#include "EntitiesUpdater.h"
#include "./Threads/Task.h"
#include "logic_entity.h"
#include <iostream>
#include <thread>

// **************************************************************************
// Constructor
// **************************************************************************
CEntitiesUpdater::CEntitiesUpdater(CThreadsPool &pool, std::vector<CLogicEntity *> &entities) :
	m_threadsPool(pool), m_vEntities(entities)
{
	m_numFinishedSubTasks = 0;
	m_bFinished						= false;
	m_iCurrIdx						= 0;
	m_fDelta              = 0;
}

// **************************************************************************
// PUBLIC: exec
// **************************************************************************
void CEntitiesUpdater::exec()
{
	m_iCurrIdx            = 0;
	m_bFinished           = false;
	m_numFinishedSubTasks = 0;

	m_numSubTasks = m_threadsPool.getNumWorkers();
	for (int i = 0; i < m_numSubTasks; i++)
	{
		std::function<void(int)> func = std::bind(&CEntitiesUpdater::subTaskFinished, this, std::placeholders::_1);
		m_threadsPool.addTask(new CTaskEcxec(m_fDelta, *this, func));
	}

	std::unique_lock<std::mutex> lock(m_mutexTaskFinished);
	m_condVar.wait(lock, [this]
		{
			bool bFinished = finished();
			return bFinished;
		});
}

// **************************************************************************
// PUBLIC: exec
// **************************************************************************
void CEntitiesUpdater::setDelta(float fDelta)
{
	m_fDelta = fDelta;
}

// **************************************************************************
// PUBLIC: subTaskFinished
// **************************************************************************
void CEntitiesUpdater::subTaskFinished(int iRet)
{
	std::lock_guard<std::mutex> lk(m_mutexTaskFinished);
	m_numFinishedSubTasks++;
	if (m_numFinishedSubTasks >= m_numSubTasks)
	{
		m_bFinished = true;
		m_condVar.notify_one();
	}
}

// **************************************************************************
// PUBLIC: finished
// **************************************************************************
bool CEntitiesUpdater::finished() const
{
	return m_bFinished;
}

// **************************************************************************
// PUBLIC: getEntity
// **************************************************************************
CLogicEntity *CEntitiesUpdater::getEntity()
{
	CLogicEntity *pRet = nullptr;
	std::lock_guard<std::mutex> lk(m_mutexGetEntity);

	if ((size_t)m_iCurrIdx < m_vEntities.size())
	{
		pRet = m_vEntities[m_iCurrIdx];
		m_iCurrIdx++;
	}

	return pRet;
}

// **************************************************************************
// PUBLIC: CTaskEcxec::exec
// **************************************************************************
void CEntitiesUpdater::CTaskEcxec::exec()
{
	CLogicEntity *pEntity = m_updater.getEntity();
	while (pEntity)
	{
		pEntity->update();
		pEntity = m_updater.getEntity();
	}
	if (m_funcResult)
		m_funcResult(0);
}