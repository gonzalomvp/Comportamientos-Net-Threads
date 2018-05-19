#include <stdio.h>

#include "view_entity_horse.h"
#include "consola.h"


void CViewEntityHorse::update() {
	hidecursor();
	gotoxy(m_posX, m_posY);
	printf("HHHHH");
}