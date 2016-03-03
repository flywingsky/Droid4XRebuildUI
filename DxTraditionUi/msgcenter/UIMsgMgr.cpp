#include "UIMsgMgr.h"
#include <tchar.h>


CUIMsgMgr* CUIMsgMgr::m_pInstance = NULL;

CUIMsgMgr::CUIMsgMgr(void)
{
	m_hMsgComingEvent		= ::CreateEvent(NULL,TRUE, FALSE, /*L"MsgComing"*/NULL);
	m_hDispatchLoopExitEvent= ::CreateEvent(NULL, TRUE, FALSE, /*L"DipatchLoopExit"*/NULL);

	DWORD ldwThreadId = 0;
	m_hDispachThread = 
		::CreateThread(NULL,0,&CUIMsgMgr::MsgDispachProc,NULL,0,&ldwThreadId);
}


CUIMsgMgr::~CUIMsgMgr(void)
{
	if (m_hDispachThread)
	{
		::CloseHandle(m_hDispachThread);
		m_hDispachThread = NULL;
	}

	if (m_hDispatchLoopExitEvent)
	{
		::CloseHandle(m_hDispatchLoopExitEvent);
		m_hDispatchLoopExitEvent = NULL;
	}

	if (m_hMsgComingEvent)
	{
		::CloseHandle(m_hMsgComingEvent);
		m_hMsgComingEvent = NULL;
	}

	//�з���,һ��Ҫȷ��û����Ϣ�����˲ų���CUIMsgMgr����
	map<unsigned int,IObseverList>::iterator litor = m_mapObseverList.begin();
	for(;  litor != m_mapObseverList.end(); ++ litor)
		litor->second.clear();
	m_mapObseverList.clear();
}

//���/�Ƴ���Ϣӳ��
bool CUIMsgMgr::RegMsg(unsigned int auMsgID,IMsgObsever *apObsever,bool abReg)
{
	bool lbRet = false;
	if (apObsever)
	{
		if (abReg)
		{
			m_RegSWMR.WaitToWrite();
			// �����Ϣӳ��
			map<unsigned int,IObseverList>::iterator litor = m_mapObseverList.find(auMsgID);
			if (litor == m_mapObseverList.end())
			{
				IObseverList llistObsevers;
				llistObsevers.insert(apObsever);
				m_mapObseverList[auMsgID] = llistObsevers;
			}
			else
			{
				litor->second.insert(apObsever);
			}

			m_RegSWMR.Done();
		}
		else
		{
            m_RegSWMR.WaitToWrite();
			// �Ƴ���Ϣӳ��
			map<unsigned int,IObseverList>::iterator litor = m_mapObseverList.find(auMsgID);
			if (litor != m_mapObseverList.end())
			{
				m_mapObseverList[auMsgID].erase(apObsever);
				if (m_mapObseverList[auMsgID].empty())
				{
					m_mapObseverList.erase(litor);
				}
			}

			m_RegSWMR.Done();
		}
		lbRet = true;
	}
	return lbRet;
}

//����UI����
void CUIMsgMgr::PostMsg(unsigned int auMsgID,void *apWParam,void *apLParam)
{
	//DoNotify(aiMsg,awParam,alParam);
	STRU_MSG_ITEM loMsg;
	loMsg.m_iMsgId = auMsgID;
	loMsg.m_pWParam = apWParam;
	loMsg.m_pLParam = apLParam;

	m_DispachSWMR.WaitToWrite();
	m_qMsg.push(loMsg);
	::SetEvent(m_hMsgComingEvent);

//	long llMsgNum = m_qMsg.size();
//	if (llMsgNum > 300)
//	{
//		if (m_hDispachThread)
//		{
//			DWORD ldwExitCode = 0;
//			if (::GetExitCodeThread(m_hDispachThread,&ldwExitCode))
//			{
//				if (STILL_ACTIVE == ldwExitCode)
//				{
//					TCHAR lsInfo[512] = { 0 };
//					_stprintf(lsInfo,TEXT("��Ϣ�ַ��̻߳������У�������Ϣ��:%d"),llMsgNum);
//					::OutputDebugString(lsInfo);
//				}
//				else
//				{
//					TCHAR lsInfo[512] = { 0 };
//					_stprintf(lsInfo,TEXT("��Ϣ�ַ��߳����˳�:%d"),ldwExitCode);
//					::OutputDebugString(lsInfo);
//				}
//			}
//		}
//	}

	m_DispachSWMR.Done();
   
	
}
	

long CUIMsgMgr::DoNotify(unsigned int auMsgID,void *apWParam,void *apLParam)
{
	long llRet = -1;

	m_RegSWMR.WaitToRead();
	map<unsigned int,IObseverList>::iterator litor = m_mapObseverList.find(auMsgID);
	if (litor != m_mapObseverList.end())
	{
		IObseverList loObsevers = litor->second;
		IObseverList::iterator litPos = loObsevers.begin();
		for ( ; litPos != loObsevers.end(); litPos++)
		{
			IMsgObsever *lpObsever = *litPos;
			if (lpObsever)
			{
				llRet = lpObsever->Notify(auMsgID,apWParam,apLParam);
			}
		}
	}
	m_RegSWMR.Done();

	return llRet;
}

IMsgMgr* CUIMsgMgr::GetMsgMgr()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CUIMsgMgr();
	}
	return (IMsgMgr*)m_pInstance;
}

//������Ϣ
long CUIMsgMgr::SendMsg(unsigned int auMsgID,void *apWParam,void *apLParam)
{
	long llRet = DoNotify(auMsgID,apWParam,apLParam);
	return llRet;
}

DWORD CUIMsgMgr::DispatchAppMsg()
{
	const int kSize  = 2;
	HANDLE hEvents[kSize] = {m_hDispatchLoopExitEvent, m_hMsgComingEvent};

	while(true)
	{
		DWORD dwWait = ::WaitForMultipleObjects(kSize,hEvents,FALSE, INFINITE);
        
		if(dwWait == WAIT_OBJECT_0)
			break;   //quite

		if(dwWait == (WAIT_OBJECT_0 + 1))
		{
			m_DispachSWMR.WaitToWrite();
			::ResetEvent(m_hMsgComingEvent);
			m_DispachSWMR.Done();

			while(true)
			{
				bool bGet = false;
				STRU_MSG_ITEM loMsg;

				m_DispachSWMR.WaitToWrite();
				if(!m_qMsg.empty())
				{
					bGet = true;
					loMsg = m_qMsg.front();
					m_qMsg.pop();
				}
				m_DispachSWMR.Done();
				
				Sleep(0);

				if(bGet)
				{
					DoNotify(loMsg.m_iMsgId,loMsg.m_pWParam, loMsg.m_pLParam);					
				}
				else
					break;  //��Ϣ���д���ɾ�������
			}
		}

		Sleep(0);
   }
	
	return 0;
}
DWORD CUIMsgMgr::MsgDispachProc(LPVOID apParam)
{
	DWORD dwRet  = 0;
	if(m_pInstance){
		dwRet  = m_pInstance->DispatchAppMsg();
	}

	return dwRet;
}

void CUIMsgMgr::StopMsgDispach()
{
	if(m_hDispachThread == NULL || m_hDispatchLoopExitEvent == NULL)
		return;

	::SetEvent(m_hDispatchLoopExitEvent);
	if(WaitForSingleObject(m_hDispatchLoopExitEvent, 500) == WAIT_TIMEOUT)
	{
		//�������鷢���ˣ�������
		::TerminateThread(m_hDispachThread, -1);
	}

}

