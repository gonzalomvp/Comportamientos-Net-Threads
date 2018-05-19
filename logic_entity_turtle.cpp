#include "logic_entity_turtle.h"
#include "game_server.h"

void CLogicEntityTurtle::update() {
	int posX = m_position.m_posX + 1;
	if (posX >= m_gameServer->m_width)
		posX = 0;
	setPos(posX, m_position.m_posY);
}