#include "Cheat.h"

#define JUNKS \
__asm _emit 0x86 \
__asm _emit 0x28 \
__asm _emit 0x20 \
__asm _emit 0x05 \
__asm _emit 0x47 \
__asm _emit 0x44 \
__asm _emit 0x87 \
__asm _emit 0x75 \
__asm _emit 0x79 \
__asm _emit 0x71 \
// Don't change this!
#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:

void CheatThread()
{
	_JUNK_BLOCK(jmp_label1)
	/*auto BuildNumber = I::Engine->GetEngineBuildNumber();
	if (BuildNumber != 13615)
	{
		MessageBox(0, "Update Detected, please Contact Ferrity", "FH4x", MB_OK);
		I::Engine->ClientCmd_Unrestricted("cl_mouseenable 1", 0);
		I::Engine->ClientCmd_Unrestricted("crosshair 1", 0);
		I::Engine->ClientCmd_Unrestricted("clear", 0);
		exit(0);
	}
	else*/
	{
		_JUNK_BLOCK(jmp_label2)
		FLASHWINFO fi;
		fi.cbSize = sizeof( FLASHWINFO );
		fi.hwnd = G::Window;
		fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
		fi.uCount = 0;
		fi.dwTimeout = 0;
		FlashWindowEx( &fi );
		_JUNK_BLOCK(jmp_label3)
		if (GetForegroundWindow() != G::Window)
			ShowWindow(G::Window, SW_RESTORE);
		SetActiveWindow(G::Window);
		/*MessageBox(0, "FH4x Private CS:GO Bot", "Enjoy", MB_OK);*/
		_JUNK_BLOCK(jmp_label4)
		U::Setup();
		/*AllocConsole();*/
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		SetConsoleTitle("FH4x Debug Console");

        I::Engine->ClientCmd_Unrestricted("toggleconsole", 0);
		/*I::Engine->ClientCmd_Unrestricted("net_graph 1", 0);*/
		Sleep(100);
		I::Engine->ClientCmd_Unrestricted("clear", 0);
		I::Engine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		I::Engine->ClientCmd_Unrestricted("echo FH4x DEV-LOG | Updated: 31.12.17", 0);
		I::Engine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		I::Engine->ClientCmd_Unrestricted("echo  ", 0);
		I::Engine->ClientCmd_Unrestricted("echo + Added pAutostop", 0);
		I::Engine->ClientCmd_Unrestricted("echo  ", 0);
		I::Engine->ClientCmd_Unrestricted("echo + Added New Antiaim System", 0);
		I::Engine->ClientCmd_Unrestricted("echo  ", 0);
		I::Engine->ClientCmd_Unrestricted("echo + Compiled by Nertigel##5391", 0);
		I::Engine->ClientCmd_Unrestricted("echo  ", 0);
		I::Engine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Sleep(100);
		I::Engine->ClientCmd_Unrestricted("crosshair 1", 0);
		_JUNK_BLOCK(jmp_label5)


		while (!G::PressedKeys[VK_END])
		{

			E::Misc->Panic();

			Sleep(1000);
		}

	}
	
}


DWORD WINAPI DllMain( HMODULE hDll, DWORD dwReason, LPVOID lpReserved )
{
	_JUNK_BLOCK(jmp_label6)
	switch( dwReason )
	{
	case DLL_PROCESS_ATTACH:
	{
		/*Beep(659, 200);
		Beep(659, 200);
		Sleep(200);
		Beep(659, 200);
		Sleep(100);
		Beep(523, 200);
		Beep(659, 200);
		Sleep(200);
		Beep(783, 200);
		Sleep(400);
		Beep(391, 200);*/
		_JUNK_BLOCK(jmp_label7)
		DisableThreadLibraryCalls(hDll);
		_JUNK_BLOCK(jmp_label8)

		_JUNK_BLOCK(jmp_label9)
		while( !( G::Window = FindWindowA( charenc( "Valve001" ), NULL ) ) ) Sleep( 200 );

		Hooks::oldWindowProc = ( WNDPROC )SetWindowLongPtr( G::Window, GWL_WNDPROC, ( LONG_PTR )Hooks::WndProc );

		CreateThread( NULL, NULL, ( LPTHREAD_START_ROUTINE )CheatThread, NULL, NULL, NULL );

		G::Dll = hDll;

		return TRUE;
	}
	case DLL_PROCESS_DETACH:
	{
		return TRUE;
	}

	return FALSE;
	}
}