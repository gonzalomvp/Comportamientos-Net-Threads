#ifndef ____THREADSPOOL___
#define ____THREADSPOOL___
// assignment operator could not be generated para CThreadsPool (por la refencia)
#pragma warning (disable : 4512)
#include <vector>
#include "SafeQueue.h"

class CTask;
class CWorkerThread;

class CThreadsPool
{
public:
	CThreadsPool();
	~CThreadsPool();

	int getNumWorkers() const;
	void addTask(CTask *pTask);

private:
	std::vector<CWorkerThread *> m_vThreads;
	CSafeQueue<CTask *>					 m_qTask;
};

#endif