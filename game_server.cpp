#include "game_server.h"
#include "game_view.h"
#include "message.h"


void CGameServer::initGame() {

}

void CGameServer::update() {
	auto it = m_entities.begin();
	for (it = m_entities.begin(); it != m_entities.end(); ++it)
		(*it)->update();
}

void CGameServer::stateChanged(const CMessage& msg) {
	auto it = m_views.begin();
	for (it = m_views.begin(); it != m_views.end(); ++it)
		(*it)->stateChanged(msg);
}

void CGameServer::registerView(CGameView* gameView) {
	m_views.push_back(gameView);
}

void CGameServer::addEntity(CLogicEntity* entity) {
	m_entities.push_back(entity);

	CMessageEntityAdded message(entity);
	stateChanged(message);
}

void CGameServer::removeEntity(CLogicEntity* entity) {
	m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entity));
}