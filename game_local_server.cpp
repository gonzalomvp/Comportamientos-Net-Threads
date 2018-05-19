#include "game_local_server.h"
#include "logic_entity_horse.h"
#include "logic_entity_turtle.h"
#include "message.h"

void CGameLocalServer::initGame() {
	CGameServer::initGame();
	CLogicEntityHorse* horse = new CLogicEntityHorse(this, m_width, 10, 1);
	addEntity(horse);
	CLogicEntityTurtle* turtle = new CLogicEntityTurtle(this, 0, 20, 2);
	addEntity(turtle);
}

void CGameLocalServer::update() {
	if (!m_isPaused) {
		m_entitiesUpdater.exec();

		for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
			(*it)->saveState();
	}	
}

void CGameLocalServer::managePlayerCommand(const CMessage& msg) {
	switch (msg.m_type) {
		case CMessage::ECommandPause:
			m_isPaused = true;
			break;
		case CMessage::ECommandResume:
			m_isPaused = false;
			break;
	}
}