#include "ThreadsPool.h"

#include <thread>
#include "WorkerThread.h"

// ******************************************************************
// Constructor
// ******************************************************************
CThreadsPool::CThreadsPool()
{
	unsigned int uNumCores = std::thread::hardware_concurrency();
	if (!uNumCores)
		uNumCores = 1;
	for (unsigned int i = 0; i < uNumCores; i++)
		m_vThreads.push_back(new CWorkerThread(m_qTask));
}

// ******************************************************************
// Destructor
// ******************************************************************
CThreadsPool::~CThreadsPool()
{
	int iNumThreads = m_vThreads.size();
	for (int i = 0; i < iNumThreads; i++)
		m_vThreads[i]->end();
	m_qTask.unLock();
	for (int i = 0; i < iNumThreads; i++)
		m_vThreads[i]->join();
}

// ******************************************************************
// getNumWorkers
// ******************************************************************
int CThreadsPool::getNumWorkers() const
{
	return m_vThreads.size();
}

// ******************************************************************
// addTask
// ******************************************************************
void CThreadsPool::addTask(CTask *pTask)
{
	if (pTask)
		m_qTask.push(pTask);
}
