#include "logic_entity_horse.h"
#include "game_server.h"
#include "message.h"

void CLogicEntityHorse::update() {
	int posX = m_position.m_posX - 2;
	if (posX < 0)
		posX = m_gameServer->m_width;
	setPos(posX, m_position.m_posY);
}

void CLogicEntityHorse::manageMessage(const CMessage& msg) {

}

void CLogicEntityHorse::manageReadMessage(const CMessage& msg) {
	switch (msg.m_type) {
		case CMessage::EEntityGetPosition: {
			CMessageEntityGetPosition msgPos = static_cast<const CMessageEntityGetPosition&>(msg);
			msgPos.x = m_readPosition.m_posX;
			msgPos.y = m_readPosition.m_posY;
			break;
		}
	}
}