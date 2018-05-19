#include "WorkerThread.h"
#include "Task.h"
#include <iostream>

// *************************************************************************
// CWorkerThread
// *************************************************************************
// OJO Con el orden de inicialización de las variables, el thread podría empezar
// a ejecutarse antes de qe se haya inicializado correctamente el resto
/*
CWorkerThread::CWorkerThread(CSafeQueue<CTask *> &queue) :
	m_thread(&CWorkerThread::run, this), 	m_queueTasks(queue)
*/
CWorkerThread::CWorkerThread(CSafeQueue<CTask *> &queue) : m_queueTasks(queue)
{
	m_exit    = false;
	m_pThread = new std::thread(&CWorkerThread::run, this);
}

CWorkerThread::~CWorkerThread()
{
	delete m_pThread; m_pThread = nullptr;
}

// *************************************************************************
// run
// *************************************************************************
void CWorkerThread::run()
{
	CTask *pTask = nullptr;
	while (!m_exit)
	{
		m_queueTasks.wait_and_pop(pTask);
		if (!m_exit && pTask)
		{
			pTask->exec();
			delete pTask;
		}
	}
	std::cout << "THREAD TERMINADO\n";
}

// *************************************************************************
// end
// *************************************************************************
void CWorkerThread::end()
{
	m_exit = true;
}

// *************************************************************************
// end
// *************************************************************************
void CWorkerThread::join()
{
	if (m_pThread)
		m_pThread->join();
}
