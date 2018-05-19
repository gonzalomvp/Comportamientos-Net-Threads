#pragma once

class CViewEntity {
public:
	CViewEntity(int posX, int posY, unsigned int id) : m_posX(posX), m_posY(posY), m_id(id) {}
	virtual void update() = 0;
	void stateChanged();
	void setPos(int x, int y);
	unsigned int getId() { return m_id; }
protected:
	int m_posX;
	int m_posY;
	unsigned int m_id;
};