#pragma once

#include "./Threads/SafeQueue.h"

class CGameServer;
class CMessage;

class CLogicEntity {
public:
	//Sacar este enum a un lugar comun porque lo comparten las entidades logicas y visuales
	enum TType
	{
		EHorse,
		ETurtle,
	};

	CLogicEntity(CGameServer* gameServer, TType type, int posX, int posY, unsigned int id) : m_gameServer(gameServer), m_position{ posX , posY }, m_readPosition{ posX , posY }, m_type(type), m_id(id) {}
	virtual void update() = 0;
	void setPos(int x, int y);
	TType getType() { return m_type; }
	int getPosX() { return m_position.m_posX; }
	int getPosY() { return m_position.m_posY; }
	unsigned int getId() { return m_id; }
	
	//Threads
	virtual void manageMessage(const CMessage& msg) {}
	virtual void manageReadMessage(const CMessage& msg) {}
	virtual void saveState();

protected:
	struct TPosition
	{
		int m_posX;
		int m_posY;
	};

	TPosition m_readPosition;
	TPosition m_position;

	unsigned int m_id;
	TType m_type;
	CGameServer* m_gameServer;

	//Threads (falta implementar el uso de la cola de mensajes)
	CSafeQueue<CMessage *> m_msgQueue;
};