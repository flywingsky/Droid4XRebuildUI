#pragma once
#include <windows.h>
#include "imsgobsever.h"
#include "ReadWriteLocker.h"

#include <map>
#include <set>
#include <queue>
using namespace std;

typedef struct MsgItem
{
	UINT m_iMsgId;
    void *m_pWParam;
    void *m_pLParam;
	UINT m_lWParamLen;
	UINT m_lLParamLen;

	MsgItem()
	{
		m_iMsgId = (UINT)-2;
		m_pWParam = NULL;
		m_pLParam = NULL;
		m_lWParamLen = 0;
		m_lLParamLen = 0;
	}
} STRU_MSG_ITEM;

//CUIMsgMgr 使用了单例模式
//注意对象生成的时机(不要在Main函数之前创建[构造函数造成api调用！])

class CUIMsgMgr :
	public IMsgMgr
{
public:
	static IMsgMgr* GetMsgMgr();

    static long Send(unsigned int auMsgID,void *apWParam,void *apLParam);
    static void Post(unsigned int auMsgID,void *apWParam,void *apLParam);

public:
	
	~CUIMsgMgr(void);

	//添加/移除消息映射
    virtual bool RegMsg(unsigned int auMsgID,IMsgObsever *apObsever,bool abReg);

	//发送消息
    virtual long SendMsg(unsigned int auMsgID,void *apWParam,void *apLParam);
	
    virtual void PostMsg(unsigned int auMsgID,void *apWParam,void *apLParam);


protected:
	CUIMsgMgr(void);

    long DoNotify(unsigned int auMsgID,void *apWParam,void *apLParam);

	static DWORD WINAPI MsgDispachProc(LPVOID apParam);
	
	DWORD DispatchAppMsg();

	void StopMsgDispach();
private:
	typedef set<IMsgObsever *> IObseverList;
	map<unsigned int,IObseverList> m_mapObseverList;

	queue<STRU_MSG_ITEM> m_qMsg;


	CReadWriteLocker m_RegSWMR;        //用于控制 m_mapObseverList;
	CReadWriteLocker m_DispachSWMR;    //用于控制m_qMsg;

	HANDLE m_hDispatchLoopExitEvent; //退出消息派遣循环的事件
	HANDLE m_hMsgComingEvent;        //消息到来事件


	HANDLE			m_hDispachThread;

	static CUIMsgMgr* m_pInstance;
};
