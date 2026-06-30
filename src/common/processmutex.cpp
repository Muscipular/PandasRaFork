// Copyright (c) Pandas Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "processmutex.hpp"

#ifdef _WIN32
#include <Windows.h>
#else
#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <ctime>
#include <unistd.h>
#endif // _WIN32

ProcessMutex::ProcessMutex(const char* mutexName)
{
	m_MutexName = mutexName != nullptr ? mutexName : "PANDAS_PROCESS_MUTEX";
#ifdef _WIN32
	m_pMutex = CreateMutexA(nullptr, false, m_MutexName.c_str());
#else
	m_pSem = sem_open(m_MutexName.c_str(), O_RDWR | O_CREAT, 0644, 1);
#endif // _WIN32
}

bool ProcessMutex::lock()
{
#ifdef _WIN32
	if (m_pMutex == nullptr) {
		return false;
	}

	DWORD ret = WaitForSingleObject(m_pMutex, INFINITE);
	return ret == WAIT_OBJECT_0;
#else
	if (m_pSem == SEM_FAILED) {
		return false;
	}

	return sem_wait(m_pSem) == 0;
#endif // _WIN32
}

bool ProcessMutex::unlock()
{
#ifdef _WIN32
	if (m_pMutex == nullptr) {
		return false;
	}

	return ReleaseMutex(m_pMutex) != 0;
#else
	if (m_pSem == SEM_FAILED) {
		return false;
	}

	return sem_post(m_pSem) == 0;
#endif // _WIN32
}

int ProcessMutex::wait(long millisecond)
{
#ifdef _WIN32
	if (m_pMutex == nullptr) {
		return 2;
	}

	DWORD ret = WaitForSingleObject(m_pMutex, static_cast<DWORD>(millisecond));
	switch (ret) {
	case WAIT_OBJECT_0:
		return 0;
	case WAIT_TIMEOUT:
		return 1;
	default:
		return 2;
	}
#else
	if (m_pSem == SEM_FAILED) {
		return 2;
	}

	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);

	long secs = millisecond / 1000;
	millisecond = millisecond % 1000;
	millisecond = millisecond * 1000 * 1000 + ts.tv_nsec;
	ts.tv_sec += secs + millisecond / (1000 * 1000 * 1000);
	ts.tv_nsec = millisecond % (1000 * 1000 * 1000);

	int ret = sem_timedwait(m_pSem, &ts);
	switch (ret) {
	case 0:
		return 0;
	case -1:
		return errno == ETIMEDOUT ? 1 : 2;
	default:
		return 2;
	}
#endif // _WIN32
}

ProcessMutex::~ProcessMutex()
{
#ifdef _WIN32
	if (m_pMutex != nullptr) {
		CloseHandle(m_pMutex);
	}
#else
	if (m_pSem != SEM_FAILED) {
		int ret = sem_close(m_pSem);
		if (ret != 0) {
			std::printf("sem_close error %d\n", ret);
		}
		sem_unlink(m_MutexName.c_str());
	}
#endif // _WIN32
}
