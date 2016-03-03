#include "readwritelocker.h"

CReadWriteLocker::CReadWriteLocker(void)
:m_nWaitingReaders(0),m_nWaitingWriters(0),m_nActive(0)
{
   m_hSemReaders = CreateSemaphore(NULL,0,MAXLONG, NULL);
   m_hSemWriters = CreateSemaphore(NULL, 0, MAXLONG, NULL);

   ::InitializeCriticalSection(&m_cs);
}

CReadWriteLocker::~CReadWriteLocker(void)
{
#ifdef _DEBUG
	if(m_nActive != 0)
		DebugBreak();
#endif

	m_nWaitingReaders = m_nWaitingReaders = m_nActive = 0;

	if(m_hSemReaders)
		CloseHandle(m_hSemReaders);

	if(m_hSemWriters)
		CloseHandle(m_hSemWriters);
}
void CReadWriteLocker::WaitToRead()
{
	EnterCriticalSection(&m_cs);

	bool bRessourceWritePending  = (m_nWaitingWriters || (m_nActive <  0));
	if(bRessourceWritePending)
	{
		m_nWaitingReaders ++;
	}
	else
	{
		m_nActive++;
	}
	LeaveCriticalSection(&m_cs);

	if(bRessourceWritePending){
		WaitForSingleObject(m_hSemReaders, INFINITE);
	}
}

void CReadWriteLocker::WaitToWrite()
{
	EnterCriticalSection(&m_cs);

	bool bResourceOwned = (m_nActive != 0);

	if(bResourceOwned)
	{
		m_nWaitingWriters ++;
	}
	else
	{
		m_nActive  = -1;
	}

	LeaveCriticalSection(&m_cs);

	if(bResourceOwned)
	{
		WaitForSingleObject(m_hSemWriters, INFINITE);
	}
}
void CReadWriteLocker::Done()
{
	EnterCriticalSection(&m_cs);
	if(m_nActive >  0)
	{
		m_nActive --;
	}
	else
	{
		m_nActive ++;
	}

	HANDLE hSem  = NULL;
	long lCount  = 1;   //assume only 1 waiter wakes; always true for writes

    if(m_nActive  == 0)
	{
		if(m_nWaitingWriters >  0)
		{
			m_nActive  = -1;
			m_nWaitingWriters --;
			hSem  = m_hSemWriters;
		}
		else if(m_nWaitingReaders >  0)
		{
			m_nActive = m_nWaitingReaders;
			m_nWaitingReaders = 0;
			hSem  = m_hSemReaders;
			lCount  = m_nActive;
		}
		else
		{
			//there are no threads waiting at all; no semaphore get released;	
		}
	}
	LeaveCriticalSection(&m_cs);

	if(hSem != NULL)
	{
		ReleaseSemaphore(hSem, lCount, NULL);
	}
}
