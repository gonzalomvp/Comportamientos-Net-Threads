#pragma once

#include "game_server.h"
#include "EntitiesUpdater.h"

extern CThreadsPool *g_pThreadsPool;

class CGameLocalServer : public CGameServer {
public:
	CGameLocalServer(unsigned int width, unsigned int height) : CGameServer(width, height), m_isPaused(false), m_entitiesUpdater(*g_pThreadsPool, m_entities) {}

	virtual void initGame();
	virtual void update();
	virtual void managePlayerCommand(const CMessage& msg);
private:
	bool m_isPaused;
	CEntitiesUpdater m_entitiesUpdater;
};