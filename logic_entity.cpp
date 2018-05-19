#include "logic_entity.h"
#include "game_server.h"
#include "message.h"

void CLogicEntity::setPos(int x, int y) {
	m_position.m_posX = x;
	m_position.m_posY = y;
	CMessageEntityMoved msg(this);
	m_gameServer->stateChanged(msg);
}

void CLogicEntity::saveState() {
	 m_readPosition = m_position;
}