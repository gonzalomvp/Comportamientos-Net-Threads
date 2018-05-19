#pragma once

class CLogicEntity;

class CMessage {
public:
	enum TType
	{
		EEntityAdded,
		EEntityMoved,
		EEntityGetPosition,
		EEntityMutate,
		ECommandPause,
		ECommandResume,
	};

	CMessage(TType type) : m_type(type) {}

	TType m_type;
};

class CMessageEntityAdded : public CMessage {
public:
	//no se puede usar el puntero porque no se pude usar al eviarlo por red
	CMessageEntityAdded(CLogicEntity* entity) : CMessage(EEntityAdded), m_entity(entity) {}
	
	CLogicEntity* m_entity;
};

class CMessageEntityMoved : public CMessage {
public:
	CMessageEntityMoved(CLogicEntity* entity) : CMessage(EEntityMoved), m_entity(entity) {}

	CLogicEntity* m_entity;
};

class CMessagePause : public CMessage {
public:
	CMessagePause() : CMessage(ECommandPause) {}
};

class CMessageResume : public CMessage {
public:
	CMessageResume() : CMessage(ECommandResume) {}
};

class CMessageEntityGetPosition : public CMessage {
public:
	CMessageEntityGetPosition() : CMessage(EEntityGetPosition) {}
	int x;
	int y;
};

class CMessageEntityMutation : public CMessage {
public:
	CMessageEntityMutation() : CMessage(EEntityMutate) {}
};