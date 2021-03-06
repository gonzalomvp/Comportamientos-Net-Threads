// juegoEnRed.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include "game_local_server.h"
#include "game_view_local.h"
#include "./Threads/ThreadsPool.h"

CThreadsPool *g_pThreadsPool;

int main()
{
	g_pThreadsPool = new CThreadsPool();
	CGameServer* gameServer = new CGameLocalServer(80, 30);
	CGameView* gameView = new CGameViewLocal(gameServer);

	gameServer->initGame();

	while (true) {
		gameServer->update();
		gameView->update();
		Sleep(500);
	}
    return 0;
}

