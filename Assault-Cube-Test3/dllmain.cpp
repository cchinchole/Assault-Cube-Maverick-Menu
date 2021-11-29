/* GuidedHacking.com World2Screen function */
/* Reclass player sdk */

#include "pch.h"
#include <iostream>
#include <string>
#include <gl\gl.h>
#include <detours.h>
#include "Console.h"
#include "SDK.h"
#include "Hack.h"
#include "Aimbot.h"
#include "Esp.h"
#include "glut.h"
#include "Menu.h"

#pragma comment( lib, "detours.lib" )
#pragma comment(lib, "user32.lib")

/* Frame buffer and window hooks */
typedef BOOL(WINAPI* twglSwapBuffers) (_In_ HDC hDc);
twglSwapBuffers owglSwapBuffers;
BOOL __stdcall hwglSwapBuffers(_In_ HDC hDc);
HMODULE glMod;
HMODULE myModule = NULL;

Aimbot aimbotHack(std::string("Aimbot"));
Esp espHack(std::string("ESP"));
bool setupFinished = false;
bool keepAlive = true;

/* This will enable the developer console */
bool debugMode = true;

Menu menu;

void checkKeys()
{

	if (GetAsyncKeyState(VK_DELETE))
	{
		keepAlive = false;
		/* Detach OpenGL */
		DetourTransactionBegin();
		DetourDetach(&(PVOID&)owglSwapBuffers, hwglSwapBuffers);
		if (DetourTransactionCommit())
		{
			MessageBoxA(NULL, "Unloaded!", "Assault Cube", MB_OK);
		}
		else
		{
			MessageBoxA(NULL, "Failed to unload!", "Assault Cube", MB_OK);
		}
		delete _Console;
		FreeLibraryAndExitThread(myModule, NULL);
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		menu.moveLeft();
	}

	else if (GetAsyncKeyState(VK_RIGHT))
	{
		menu.moveRight();
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		menu.moveUp();
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		menu.moveDown();
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		menu.selectOption();
	}
}

void updateHacks()
{
	while(keepAlive)
	{
		if(setupFinished)
		for(MenuTab tab : menu.tabArray)
			for (MenuOption option : tab.optionArray)
			{
				Hack* hack = option.hack;
					if (hack != NULL)
					{
						hack->onUpdate();
					}
			}
	}
}



BOOL __stdcall hwglSwapBuffers(_In_ HDC hDc)
{
	if (setupFinished)
	{
	int width = *(DWORD*)Offsets::SCRWidth;
	int height = *(DWORD*)Offsets::SCHeight;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	for (MenuTab tab : menu.tabArray)
		for (MenuOption option : tab.optionArray)
		{
			Hack* hack = option.hack;
			if (hack != NULL)
			{
				hack->onRender();
			}
		}
	

	
	DrawMenu(menu);
	}
	return owglSwapBuffers(hDc);
}


void HookSwapBuffers()
{
	glMod = GetModuleHandle("opengl32.dll");

	if (glMod)
	{
		owglSwapBuffers = (twglSwapBuffers)(DWORD)GetProcAddress(glMod, "wglSwapBuffers");
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)owglSwapBuffers, hwglSwapBuffers);
		DetourTransactionCommit();
	}
	else
	{
		MessageBoxA(NULL, "Unable to load opengl!", "Assault-Cube Hack", MB_OK);
	}
	HDC currentHDC = wglGetCurrentDC();
}

void BuildMenu()
{
	/* unlocalized name, then localized name*/
	menu.menuName = "Maverick V2";
	menu.addTab("tab1", "Tab 1");
	menu.addTab("tab2", "Tab 2");
	menu.addTab("tab3", "Tab 3");
	menu.addOption("tab1", &aimbotHack);
	menu.addOption("tab1", &espHack);
	menu.addOption("tab1", &aimbotHack);
	menu.addOption("tab1", &aimbotHack);
}


void MainLoop()
{
	_Console = new Console(true);
	
	BuildFonts();
	BuildMenu();

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HookSwapBuffers, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)updateHacks, 0, 0, 0);

	setupFinished = true;
	while(keepAlive)
	{
		checkKeys();
		Sleep(50);
	}
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		myModule = hModule;
		MessageBoxA(NULL, "Loaded!", "Assault-Cube Hack", MB_OK);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainLoop, hModule, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
