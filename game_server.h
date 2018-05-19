#pragma once

#include <vector>

#include "logic_entity.h"

class CGameView;
class CMessage;

class CGameServer {
public:
	CGameServer(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}
	virtual void initGame();
	virtual void update();
	virtual void managePlayerCommand(const CMessage& msg) = 0;
	void stateChanged(const CMessage& msg);
	void registerView(CGameView* gameView);

	void addEntity(CLogicEntity* entity);
	void removeEntity(CLogicEntity* entity);

	unsigned int m_width;
	unsigned int m_height;

protected:
	std::vector<CLogicEntity *> m_entities;
	std::vector<CGameView *> m_views;
};