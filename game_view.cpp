#include "game_view.h"
#include "game_server.h"

CGameView::CGameView(CGameServer* gameServer) : m_gameServer(gameServer) {
	m_gameServer->registerView(this);
}
