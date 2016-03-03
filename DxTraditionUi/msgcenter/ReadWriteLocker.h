#pragma once

#include <Windows.h>

class CReadWriteLocker
{
public:
	CReadWriteLocker(void);
	~CReadWriteLocker(void);


	void WaitToRead();   // call this to gain shared read access
	void WaitToWrite();  // call  to gain exclusive write access

	void Done();		 //Call when done accessing the resouce

private:
	CRITICAL_SECTION  m_cs;

	HANDLE  m_hSemReaders;
	HANDLE  m_hSemWriters;

	int m_nWaitingReaders;
	int m_nWaitingWriters;

	int m_nActive;  //(0 = no threads, >0 = #of readers, -1=1 writer)
};
