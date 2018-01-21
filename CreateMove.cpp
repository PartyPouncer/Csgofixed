#include "Cheat.h"
#define JUNKS \
__asm _emit 0x79 \
__asm _emit 0x04 \
__asm _emit 0x68 \
__asm _emit 0x32 \
__asm _emit 0x74 \
__asm _emit 0x24 \
__asm _emit 0x45 \
__asm _emit 0x24 \
__asm _emit 0x82 \
__asm _emit 0x83 \
// Don't change this!
#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:


CreateMoveFn oCreateMove;

int iTickBaseBackup;
int iFlagsBackup;
int iButtonsBackup;
int* m_pSetPredictionPlayer;
static char* cMoveData = nullptr;

void EnginePrediction(CUserCmd* cmd)
{
	_JUNK_BLOCK(jmp_label1)
	//Nullptr'ing is fun!
	if (!I::g_pMoveHelper || !cmd || !G::LocalPlayer)
		return;

	//We need to cast g_LocalPlayer to C_BasePlayer so we can use it in our code
	auto localplayer = G::LocalPlayer;
	CMoveData C_MoveData;

	//Let's back things up for later use
	iFlagsBackup = localplayer->GetFlags();
	iButtonsBackup = cmd->buttons;

	//Set m_pCurrentCommand to cmd. We'll set this to nullptr later.
	//localplayer->m_pCurrentCommand() = cmd;
	*(CUserCmd**)((DWORD)localplayer + offsets.m_hConstraintEntity - 0xC) = cmd;
	//Let's get some signatures now
	if (!m_pSetPredictionPlayer)
	{//89 3D ? ? ? ? F3 0F 10 47 ? + 0x2
		m_pSetPredictionPlayer = *reinterpret_cast<int**>(U::FindPattern("client.dll", "89 35 ? ? ? ? F3 0F 10 48 20") + 2);
	}

	//We don't want to be calling this every tick, bad for framerate.
	//Thanks, zbe and Heep
	if (!cMoveData)
		cMoveData = (char*)(calloc(1, sizeof(CMoveData)));

	//Let's set it up so that it predicts ourselves
	I::g_pMoveHelper->SetHost(localplayer);
	//*m_pPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
	*m_pSetPredictionPlayer = uintptr_t(localplayer);

	//Let's set some global variables
	I::Globals->curtime = localplayer->GetTickBase() * I::Globals->interval_per_tick;
	I::Globals->frametime = I::Globals->interval_per_tick;

	//Don't know is for exactly, but here's the relevant IDA picture of it. https://i.imgur.com/hT6caQV.png
	cmd->buttons |= *reinterpret_cast< uint8_t* >(uintptr_t(localplayer) + 0x3310);

	//This is for flashlights in older Source games, Thanks, friendly for the info
	if (cmd->impulse)
		*reinterpret_cast< uint8_t* >(uintptr_t(localplayer) + 0x31EC) = cmd->impulse;

	//Here we're doing CBasePlayer::UpdateButtonState
	C_MoveData.m_nButtons = cmd->buttons;
	int buttonsChanged = cmd->buttons ^ *reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E8);
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31DC) = (uintptr_t(localplayer) + 0x31E8);
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E8) = cmd->buttons;
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E0) = cmd->buttons & buttonsChanged;  //m_afButtonPressed ~ The changed ones still down are "pressed"
	*reinterpret_cast<int*>(uintptr_t(localplayer) + 0x31E4) = buttonsChanged & ~cmd->buttons; //m_afButtonReleased ~ The ones not down are "released"

	I::g_pMovement->StartTrackPredictionErrors(localplayer);

	iTickBaseBackup = localplayer->GetTickBase();

	I::Prediction->SetupMove(localplayer, cmd, I::g_pMoveHelper, reinterpret_cast< CMoveData* >(cMoveData));
	I::g_pMovement->ProcessMovement(localplayer, reinterpret_cast< CMoveData* >(cMoveData));
	I::Prediction->FinishMove(localplayer, cmd, reinterpret_cast< CMoveData* >(cMoveData));

	//Let's override our tickbase with the backed up tickbase
	*(int*)((DWORD)localplayer + offsets.m_nTickBase) = iTickBaseBackup;



	I::g_pMovement->FinishTrackPredictionErrors(localplayer);

	//Let's nullify these here
	//localplayer->m_pCurrentCommand() = nullptr;

	*(CUserCmd**)((DWORD)localplayer + offsets.m_hConstraintEntity - 0xC) = nullptr;

	//*m_pPredictionRandomSeed = -1;
	*m_pSetPredictionPlayer = 0;
	I::g_pMoveHelper->SetHost(0);

	//Last but not least, set these to their backups 
	*(int*)((DWORD)localplayer + offsets.m_fFlags) = iFlagsBackup;
	//localplayer->m_fFlags() = iFlagsBackup;
	cmd->buttons = iButtonsBackup;
}

bool __stdcall Hooks::CreateMove( float flInputSampleTime, CUserCmd* cmd )
{
	_JUNK_BLOCK(jmp_label2)

	static CPredictionSystem PredictionSystem;
	G::isAutowalling = false;
	G::LocalPlayer = U::GetLocalPlayer();
	G::UserCmd = cmd;
	G::SendPacket = true;

	CBaseEntity* pEntity;

	if (G::PressedKeys[VK_END])
		E::Misc->Panic();


	if (Vars.Misc.ChatSpam)
		E::Misc->Chatspam();

	if (Vars.Misc.Ranks && G::PressedKeys[VK_TAB])
		U::ServerRankRevealAll();

	E::Misc->ForceThirdPerson();

	if( Vars.Ragebot.Enabled ) Vars.Legitbot.Aimbot.Enabled = false;
	else if( Vars.Legitbot.Aimbot.Enabled ) Vars.Ragebot.Enabled = false;

	if( cmd->command_number == 0 || !I::Engine->IsInGame() )
		return false;

	if (Vars.Misc.LocationSpam)
		E::Misc->LocationSpam();

	if (Vars.Misc.NameStealer)
		E::Misc->NameSteal();

	if (Vars.Visuals.Removals.Postprocess)
		E::Misc->postprozess();

	if (Vars.Misc.aniclantag)
		E::Misc->aniclantag();

	if( !G::LocalPlayer || !G::LocalPlayer->GetAlive() )
		return G::Return;

	DWORD* framePointer;
	__asm mov framePointer, ebp;

	_JUNK_BLOCK(jmp_label3)

	if( !G::Aimbotting || !G::InAntiAim )
		G::LastAngle = cmd->viewangles;

	if (Vars.Misc.AutoStrafe)
		E::Misc->AutoStrafe();

	if (Vars.Misc.RageAutoStrafe)
		E::Misc->RageAutoStrafe(cmd);

	if (Vars.Misc.moonwalk)
		E::Misc->moonwalk();

	if (Vars.Misc.FakeWalk)
		E::Misc->FakeWalk(cmd, G::SendPacket);

	if (Vars.Visuals.Removals.Scope)
		E::Misc->RemoveScope();

	//PredictionSystem.StartPrediction();//

	EnginePrediction(G::UserCmd);

	if (Vars.Legitbot.Aimbot.Enabled && Vars.Legitbot.Aimbot.LegitBacktrack)
		LegitBacktracking::CM();

	if (Vars.Legitbot.Aimbot.Enabled)
	    E::LegitBot->Run();

	if (Vars.Ragebot.Enabled)
		E::RageBot->Run(cmd, G::SendPacket);

	//PredictionSystem.EndPrediction();//

	
	_JUNK_BLOCK(jmp_label4)

	if (Vars.Misc.fakelag)
		E::Misc->fakelag();

    G::VisualAngle = cmd->viewangles;

	*(bool*)(*framePointer - 0x1C) = G::SendPacket;

	if (Vars.Misc.Bhop)
		E::Misc->Bunnyhop();

	if( Vars.Misc.AirStuck )
		E::Misc->AirStuck();

	if (Vars.Misc.AutoRevovler)
		E::Misc->AutoRevolver();

	if (Vars.Misc.AutoPistol)
		E::Misc->AutoPistol();

	if (Vars.Misc.NameHide)
		E::Misc->NameHide();

	if (Vars.Misc.NameSpammer)
		E::Misc->NameSpammer();

	if (Vars.Misc.NameSpammer2)
		E::Misc->NameSpammer2();

	if (Vars.Misc.Teleport)
		E::Misc->Teleport();

	if (Vars.Misc.MTeleport)
		E::Misc->MTeleport();

	if (Vars.Misc.AutoBlocker)
		E::Misc->AutoBlocker(cmd);

	if (Vars.Misc.SetClanTag)
		E::Misc->SetClanTag(charenc("[VALV\xE1\xB4\xB1]"), charenc( "Valve"));

	if (Vars.Misc.Walkbot)
		E::Misc->Walkbot(cmd, U::GetLocalPlayer());

	if (Vars.Misc.svcheats )
		E::Misc->svcheats();

	if( Vars.Ragebot.UntrustedCheck )
		cmd->viewangles.Clamp();

	_JUNK_BLOCK(jmp_label5)

	if ((Vars.Visuals.Removals.VisualRecoil && Vars.Legitbot.Aimbot.RCS && Vars.Legitbot.Aimbot.Enabled) || (Vars.Ragebot.Silent && Vars.Ragebot.Enabled))
		return false;
	 
	if (!Vars.Legitbot.Aimbot.Faceitmode && Vars.Legitbot.Aimbot.Enabled && !Vars.Legitbot.Aimbot.Silent && !Vars.Legitbot.Aimbot.legitaa)
		I::Engine->SetViewAngles(G::UserCmd->viewangles);

	/*G::Lby = G::LocalPlayer->GetLowerBodyTarget();

	if (!G::SendPacket)
	{
		G::RealAngle = cmd->viewangles;
	}
	else if (G::SendPacket)
	{
		G::FakeAngle = cmd->viewangles;
	}*/

	cmd->viewangles.Clamp();

	return false;
}