#include <stdio.h>

#include "view_entity_turtle.h"
#include "consola.h"

void CViewEntityTurtle::update() {
	hidecursor();
	gotoxy(m_posX, m_posY);
	printf("o");
}