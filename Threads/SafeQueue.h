#ifndef ____SAFEQUEUE___
#define ____SAFEQUEUE___

#include <queue>
#include <mutex>
//#include <atomic>
#include <condition_variable>

// ********************************************************************
// Safe queue
// ********************************************************************
template<typename T>
class CSafeQueue
{
private:
	mutable std::mutex      m_mutex;
	std::queue<T>           m_data_queue;
	std::condition_variable m_data_cond;
	bool										m_bUnlocked;
	//std::atomic_bool				m_bUnlocked;

public:
	CSafeQueue() { m_bUnlocked = false;  }

	// ******************************************************
	CSafeQueue(CSafeQueue const& other)
	{
		std::lock_guard<std::mutex> lk(other.m_mutex);
		m_data_queue = other.m_data_queue;
		m_bUnlocked = false;
	}

	// ******************************************************
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_data_queue.push(new_value);
		m_data_cond.notify_one();
	}

	// ******************************************************
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(m_mutex);
		m_data_cond.wait(lk, [this]
			{ 
				return (m_bUnlocked || !m_data_queue.empty()); 
			});

		if (!m_bUnlocked && !m_data_queue.empty()) // Para controlar el desbloqueo de la espera
		{
			value = m_data_queue.front();
			m_data_queue.pop();
		}
	}

	// ******************************************************
	bool try_pop(T& value)
	{
		bool bRet = false;
		std::lock_guard<std::mutex> lk(m_mutex);
		if (!m_data_queue.empty())
		{
			value = m_data_queue.front();
			m_data_queue.pop();
			bRet = true;
		}
		return bRet;
	}

	// ******************************************************
	bool empty() const
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		return m_data_queue.empty();
	}

	// ******************************************************
	// Para desbloquear los hilos que estén esperando en la cola
	// y permitir que estos puedan terminar correctamente
	// ******************************************************
	void unLock()
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_bUnlocked = true;

		m_data_cond.notify_all();
	}
};

#endif