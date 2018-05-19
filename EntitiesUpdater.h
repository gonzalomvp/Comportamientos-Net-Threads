#ifndef ___ENTITIESUPDATER___
#define ___ENTITIESUPDATER___

// assignment operator could not be generated para CTaskEcxec (por la refencia)
#pragma warning (disable : 4512)

#include "./Threads/ThreadsPool.h"
#include <atomic>
#include "./Threads/Task.h"

class CLogicEntity;
class CEntitiesUpdater
{
public:
	CEntitiesUpdater(CThreadsPool &pool, std::vector<CLogicEntity *> &entities);

	void setDelta(float fDelta);

	virtual void exec();

private:

	class CTaskEcxec : public CTask
	{
		public:
			CTaskEcxec(float fDelta, CEntitiesUpdater& updater, std::function<void(int)> func) : 
				m_fDelta(fDelta), CTask(func), m_updater(updater) {}
			virtual void exec();
		private:
			CEntitiesUpdater& m_updater;
			float             m_fDelta;
	};

	void      subTaskFinished(int iRet);
	bool      finished       () const;
	CLogicEntity * getEntity      ();

	// *********************************
private:
	CThreadsPool&						  m_threadsPool;
	std::vector<CLogicEntity *>&   m_vEntities;
	std::condition_variable   m_condVar;
	int												m_numFinishedSubTasks;
	std::atomic_int						m_numSubTasks;
	std::atomic_bool					m_bFinished;
	mutable std::mutex				m_mutexTaskFinished;
	std::mutex				        m_mutexGetEntity;
	int                       m_iCurrIdx;
	float										  m_fDelta;

};

#endif