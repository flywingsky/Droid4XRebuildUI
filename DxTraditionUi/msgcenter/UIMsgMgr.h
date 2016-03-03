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

//CUIMsgMgr ʹ���˵���ģʽ
//ע��������ɵ�ʱ��(��Ҫ��Main����֮ǰ����[���캯�����api���ã�])

class CUIMsgMgr :
	public IMsgMgr
{
public:
	static IMsgMgr* GetMsgMgr();
	
public:
	
	~CUIMsgMgr(void);

	//���/�Ƴ���Ϣӳ��
	virtual bool RegMsg(unsigned int auMsgID,IMsgObsever *apObsever,bool abReg);

	//������Ϣ
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


	CReadWriteLocker m_RegSWMR;        //���ڿ��� m_mapObseverList;
	CReadWriteLocker m_DispachSWMR;    //���ڿ���m_qMsg;

	HANDLE m_hDispatchLoopExitEvent; //�˳���Ϣ��ǲѭ�����¼�
	HANDLE m_hMsgComingEvent;        //��Ϣ�����¼�


	HANDLE			m_hDispachThread;

	static CUIMsgMgr* m_pInstance;
};
