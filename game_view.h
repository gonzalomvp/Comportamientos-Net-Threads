#pragma once

#include <vector>

class CGameServer;
class CMessage;

class CGameView {
public:
	CGameView(CGameServer* gameServer);
	virtual void update() = 0;
	virtual void stateChanged(const CMessage& msg) = 0;

protected:
	CGameServer * m_gameServer;
};