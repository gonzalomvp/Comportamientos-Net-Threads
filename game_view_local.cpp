#include "game_view_local.h"
#include "message.h"
#include "view_entity_horse.h"
#include "view_entity_turtle.h"
#include "logic_entity.h"
#include "consola.h"
#include "game_server.h"

void CGameViewLocal::update() {
	//Process input
	//check input
	int key = NULL;
	if (_kbhit()) {
		key = _getch();
	}

	switch (key) {
		case 'p':
			m_gameServer->managePlayerCommand(CMessagePause());
			break;
		case 'u':
			m_gameServer->managePlayerCommand(CMessageResume());
			break;
	}

	//Render
	clear();
	auto it = m_entities.begin();
	for (it = m_entities.begin(); it != m_entities.end(); ++it)
		(*it)->update();
}

void CGameViewLocal::stateChanged(const CMessage& msg) {
	switch (msg.m_type) {
		case CMessage::EEntityAdded: {
			CMessageEntityAdded msgAdded = static_cast<const CMessageEntityAdded&>(msg);

			switch (msgAdded.m_entity->getType()) {
				case CLogicEntity::EHorse: {
					CViewEntityHorse* horse = new CViewEntityHorse(msgAdded.m_entity->getPosX(), msgAdded.m_entity->getPosY(), msgAdded.m_entity->getId());
					m_entities.push_back(horse);
					break;
				}
				case CLogicEntity::ETurtle: {
					CViewEntityTurtle* turtle = new CViewEntityTurtle(msgAdded.m_entity->getPosX(), msgAdded.m_entity->getPosY(), msgAdded.m_entity->getId());
					m_entities.push_back(turtle);
					break;
				}
			}
			break;
		}
		case CMessage::EEntityMoved: {
			CMessageEntityMoved msgAMoved = static_cast<const CMessageEntityMoved&>(msg);
			for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
				if ((*it)->getId() == msgAMoved.m_entity->getId()) {
					(*it)->setPos(msgAMoved.m_entity->getPosX(), msgAMoved.m_entity->getPosY());
					break;
				}
			}
			break;
		}
	}
}