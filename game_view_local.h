#pragma once

#include "game_view.h"

class CViewEntity;

class CGameViewLocal : public CGameView {
public:
	CGameViewLocal(CGameServer* gameServer) : CGameView(gameServer) {}
	virtual void update();
	virtual void stateChanged(const CMessage& msg);
private:
	//cambiar a map
	std::vector<CViewEntity *> m_entities;
};