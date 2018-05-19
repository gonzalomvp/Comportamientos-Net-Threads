#include "ThreadsPool.h"

#include "Task.h"
#include <iostream>
#include <condition_variable>
#include <atomic>
#include <mutex>

// ***************************************************************************
// testTask
// ***************************************************************************
class CTest_TaskSet
{
public:
	CTest_TaskSet(CThreadsPool &pool, std::function<void(int)> func) :
		m_threadsPool(pool), m_funcSetFinished(func), m_numFinishedSubTasks(0) 
	{
		m_bFinished = false;
	}

	// *********************************
	void exec()
	{
		m_numSubTasks = m_threadsPool.getNumWorkers();
		for (int i = 0; i < m_numSubTasks; i++)
		{
			std::function<void(int)> func = std::bind(&CTest_TaskSet::subTaskFinished, this, std::placeholders::_1);
			m_threadsPool.addTask(new CTask(func));
		}		
	}

	// *********************************
	void subTaskFinished(int iRet)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		bool bFinished = false;
		m_numFinishedSubTasks++;
		if (m_numFinishedSubTasks >= m_numSubTasks)
		{
			m_bFinished = true;
			bFinished = m_bFinished;
		}

		if (m_bFinished && m_funcSetFinished)
		{
			// Desbloquemos el mutex cuando vamos a llamar a una función
			// externa que no sabemos lo que hará.
			lk.unlock();
			m_funcSetFinished(iRet);
		}
	}

	bool finished() 
	{ 
		bool bRet = m_bFinished;
		return m_bFinished; 
	}

	// *********************************

	// *********************************
private:
	CThreadsPool&						  m_threadsPool;
	std::function<void(int)>  m_funcSetFinished;
	int												m_numFinishedSubTasks;
	std::atomic_int						m_numSubTasks;         // ¿Por qué está como atómica?
	std::atomic_bool					m_bFinished;					 // ¿Por qué está como atómica?
	std::mutex								m_mutex;
};

// ***************************************************************************
// test_Threads
// ***************************************************************************
void test_Threads()
{
	std::condition_variable condVar;
	CThreadsPool            pool;
	CTest_TaskSet           set(pool, [&](int iRet)
		{ 
			condVar.notify_one();  
		});

	set.exec();

	std::mutex mx;
	std::unique_lock<std::mutex> lock(mx);
	condVar.wait(lock, [&]
		{ 
			return set.finished(); 
		});

	std::cout << "TAREAS FINALIZADAS\n";
}