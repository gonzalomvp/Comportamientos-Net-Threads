#ifndef ____WORKERTHREAD___
#define ____WORKERTHREAD___

#include <thread>
#include <atomic>
#include "SafeQueue.h"

class CTask;

class CWorkerThread
{
public:
	CWorkerThread(CSafeQueue<CTask *> &queue);
	~CWorkerThread();

	void join();
	void end();

private:
	void run();

	//std::thread          m_thread;
	std::thread *        m_pThread;
	CSafeQueue<CTask *> &m_queueTasks;
	std::atomic_bool		 m_exit;
};

#endif