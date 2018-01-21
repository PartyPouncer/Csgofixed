#include "Cheat.h"

CAntiAim* AntiAim = new CAntiAim;

void CAntiAim::Run(CUserCmd *pCmd, bool &bSendPacket)
{
	if (G::UserCmd->buttons & IN_ATTACK || G::UserCmd->buttons & IN_USE)
		return;

	if (G::LocalPlayer->GetMoveType() == MOVETYPE_LADDER || G::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	CBaseEntity* pWeapon = reinterpret_cast<CBaseEntity*>(G::LocalPlayer->GetWeapon());
	ClientClass* pWeaponClass = pWeapon->GetClientClass();
	if (pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CKnife) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CHEGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CFlashbang) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CSmokeGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CDecoyGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CIncendiaryGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CMolotovGrenade))
		return;

	DoAntiAim(pCmd, bSendPacket);
}

namespace AntiAims
{

	void JitterPitch(CUserCmd *pCmd)
	{
		static bool up = true;
		if (up)
		{
			pCmd->viewangles.x = 45;
			up = !up;
		}
		else
		{
			pCmd->viewangles.x = 89;
			up = !up;
		}
	}

	void FakePitch(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < 1)
		{
			G::SendPacket = false;
			pCmd->viewangles.x = 89;
		}
		else
		{
			G::SendPacket = true;
			pCmd->viewangles.x = 51;
			ChokedPackets = -1;
		}
	}

	void StaticJitter(CUserCmd *pCmd)
	{
		static bool down = true;
		if (down)
		{
			pCmd->viewangles.x = 179.0f;
			down = !down;
		}
		else
		{
			pCmd->viewangles.x = 89.0f;
			down = !down;
		}
	}

	// Yaws

	void FastSpin(CUserCmd *pCmd)
	{
		static int y2 = -179;
		int spinBotSpeedFast = 100;

		y2 += spinBotSpeedFast;

		if (y2 >= 179)
			y2 = -179;

		pCmd->viewangles.y = y2;
	}
	void BackJitter(CUserCmd *pCmd)
	{
		int random = rand() % 100;

		if (random < 98)

			pCmd->viewangles.y -= 180;

		if (random < 15)
		{
			float change = -70 + (rand() % (int)(140 + 1));
			pCmd->viewangles.y += change;
		}
		if (random == 69)
		{
			float change = -90 + (rand() % (int)(180 + 1));
			pCmd->viewangles.y += change;
		}
	}

	void FakeSideways(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < 1)
		{
			G::SendPacket = false;
			pCmd->viewangles.y += 90;
		}
		else
		{
			G::SendPacket = true;
			pCmd->viewangles.y -= 180;
			ChokedPackets = -1;
		}
	}

	void FastSpint(CUserCmd *pCmd)
	{
		int r1 = rand() % 100;
		int r2 = rand() % 1000;

		static bool dir;
		static float current_y = pCmd->viewangles.y;

		if (r1 == 1) dir = !dir;

		if (dir)
			current_y += 15 + rand() % 10;
		else
			current_y -= 15 + rand() % 10;

		pCmd->viewangles.y = current_y;

		if (r1 == r2)
			pCmd->viewangles.y += r1;
	}

	void BackwardJitter(CUserCmd *pCmd)
	{
		static bool flip;
		flip = !flip;
		pCmd->viewangles.y += 180.f;

		if (flip)
		{
			pCmd->viewangles.y -= U::RandomFloat(35,-35);
		}
		else
		{
			pCmd->viewangles.y += U::RandomFloat(35, -35);
		}
	}

	void Jitter(CUserCmd *pCmd)
	{
		static int jitterangle = 0;

		if (jitterangle <= 1)
		{
			pCmd->viewangles.y += 90;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			pCmd->viewangles.y -= 90;
		}

		int re = rand() % 4 + 1;


		if (jitterangle <= 1)
		{
			if (re == 4)
				pCmd->viewangles.y += 180;
			jitterangle += 1;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			if (re == 4)
				pCmd->viewangles.y -= 180;
			jitterangle += 1;
		}
		else
		{
			jitterangle = 0;
		}
	}

	void FakeStatic(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < 1)
		{
			G::SendPacket = false;
			static int y2 = -179;
			int spinBotSpeedFast = 360.0f / 1.618033988749895f;

			y2 += spinBotSpeedFast;

			if (y2 >= 179)
				y2 = -179;

			pCmd->viewangles.y = y2;
		}
		else
		{
			G::SendPacket = true;
			pCmd->viewangles.y -= 180;
			ChokedPackets = -1;
		}
	}

	void TJitter(CUserCmd *pCmd)
	{
		static bool Turbo = true;
		if (Turbo)
		{
			pCmd->viewangles.y -= 90;
			Turbo = !Turbo;
		}
		else
		{
			pCmd->viewangles.y += 90;
			Turbo = !Turbo;
		}
	}

	void TFake(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < 1)
		{
			G::SendPacket = false;
			pCmd->viewangles.y = -90;
		}
		else
		{
			G::SendPacket = true;
			pCmd->viewangles.y = 90;
			ChokedPackets = -1;
		}
	}

	void FakeJitter(CUserCmd* pCmd, bool &bSendPacket)
	{
		static int jitterangle = 0;

		if (jitterangle <= 1)
		{
			pCmd->viewangles.y += 135;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			pCmd->viewangles.y += 225;
		}

		static int iChoked = -1;
		iChoked++;
		if (iChoked < 1)
		{
			G::SendPacket = false;
			if (jitterangle <= 1)
			{
				pCmd->viewangles.y += 45;
				jitterangle += 1;
			}
			else if (jitterangle > 1 && jitterangle <= 3)
			{
				pCmd->viewangles.y -= 45;
				jitterangle += 1;
			}
			else
			{
				jitterangle = 0;
			}
		}
		else
		{
			G::SendPacket = true;
			iChoked = -1;
		}
	}


	void Up(CUserCmd *pCmd)
	{
		pCmd->viewangles.x = -89.0f;
	}

	void Zero(CUserCmd *pCmd)
	{
		pCmd->viewangles.x = 0.f;
	}

	void Static(CUserCmd *pCmd)
	{
		static bool aa1 = false;
		aa1 = !aa1;
		if (aa1)
		{
			static bool turbo = false;
			turbo = !turbo;
			if (turbo)
			{
				pCmd->viewangles.y -= 90;
			}
			else
			{
				pCmd->viewangles.y += 90;
			}
		}
		else
		{
			pCmd->viewangles.y -= 180;
		}
	}

	void fakelowerbody(CUserCmd *pCmd, bool &bSendPacket)
	{
		static bool f_flip = true;
		f_flip = !f_flip;

		if (f_flip)
		{
			pCmd->viewangles.y -= G::LocalPlayer->GetLowerBodyTarget() + 90.00f;
			G::SendPacket = false;
		}
		else if (!f_flip)
		{
			pCmd->viewangles.y += G::LocalPlayer->GetLowerBodyTarget() - 90.00f;
			G::SendPacket = true;
		}
	}

	void FakeSideLBY(CUserCmd *pCmd, bool &bSendPacket)
	{
		int i = 0; i < I::ClientEntList->GetHighestEntityIndex(); ++i;
		CBaseEntity *pEntity = I::ClientEntList->GetClientEntity(i);
		CBaseEntity *pLocal = I::ClientEntList->GetClientEntity(I::Engine->GetLocalPlayer());

		static bool isMoving;
		float PlayerIsMoving = abs(pLocal->GetVelocity().Length2D());
		if (PlayerIsMoving > 0.1) isMoving = true;
		else if (PlayerIsMoving <= 0.1) isMoving = false;

		int flip = (int)floorf(I::Globals->curtime / 1.1) % 2;
		static bool bFlipYaw;
		float flInterval = I::Globals->interval_per_tick;
		float flTickcount = pCmd->tick_count;
		float flTime = flInterval * flTickcount;
		if (std::fmod(flTime, 1) == 0.f)
			bFlipYaw = !bFlipYaw;

		if (PlayerIsMoving <= 0.1)
		{
			if (G::SendPacket)
			{
				pCmd->viewangles.y += 180.f;
			}
			else
			{
				if (flip)
				{
					pCmd->viewangles.y += bFlipYaw ? 90.f : -90.f;

				}
				else
				{
					pCmd->viewangles.y -= G::LocalPlayer->GetLowerBodyTarget() + bFlipYaw ? 90.f : -90.f;
				}
			}
		}
		else if (PlayerIsMoving > 0.1)
		{
			if (G::SendPacket)
			{
				pCmd->viewangles.y += 180.f;
			}
			else
			{
				pCmd->viewangles.y += 90.f;
			}
		}
	}

	void LBYJitter(CUserCmd* cmd, bool& packet)
	{
		static bool ySwitch;
		static bool jbool;
		static bool jboolt;
		ySwitch = !ySwitch;
		jbool = !jbool;
		jboolt = !jbool;
		if (ySwitch)
		{
			if (jbool)
			{
				if (jboolt)
				{
					cmd->viewangles.y = G::LocalPlayer->GetLowerBodyTarget() - 90.f;
					G::SendPacket = false;
				}
				else
				{
					cmd->viewangles.y = G::LocalPlayer->GetLowerBodyTarget() + 90.f;
					G::SendPacket = false;
				}
			}
			else
			{
				if (jboolt)
				{
					cmd->viewangles.y = G::LocalPlayer->GetLowerBodyTarget() - 125.f;
					G::SendPacket = false;
				}
				else
				{
					cmd->viewangles.y = G::LocalPlayer->GetLowerBodyTarget() + 125.f;
					G::SendPacket = false;
				}
			}
		}
		else
		{
			cmd->viewangles.y = G::LocalPlayer->GetLowerBodyTarget();
			G::SendPacket = true;
		}
	}

	void LBYSpin(CUserCmd *pCmd, bool &bSendPacket)
	{
		CBaseEntity* pLocal = G::LocalPlayer;
		static int skeet = 179;
		int SpinSpeed = 100;
		static int ChokedPackets = -1;
		ChokedPackets++;
		skeet += SpinSpeed;

		if
			(pCmd->command_number % 9)
		{
			G::SendPacket = true;
			if (skeet >= G::LocalPlayer->GetLowerBodyTarget() + 180);
			skeet = G::LocalPlayer->GetLowerBodyTarget() - 0;
			ChokedPackets = -1;
		}
		else if
			(pCmd->command_number % 9)
		{
			G::SendPacket = false;
			pCmd->viewangles.y += 179;
			ChokedPackets = -1;
		}
		pCmd->viewangles.y = skeet;
	}

	void SlowSpin(CUserCmd *pCmd)
	{
		int r1 = rand() % 100;
		int r2 = rand() % 1000;

		static bool dir;
		static float current_y = pCmd->viewangles.y;

		if (r1 == 1) dir = !dir;

		if (dir)
			current_y += 4 + rand() % 10;
		else
			current_y -= 4 + rand() % 10;

		pCmd->viewangles.y = current_y;

		if (r1 == r2)
			pCmd->viewangles.y += r1;
	}
	void LBYBreak1(CUserCmd *pCmd)
	{
		{
			static bool fliplol;
			INetChannelInfo *nci = I::Engine->GetNetChannelInfo();
			float flCurrentTime = I::Globals->curtime;
			static float oldcurtime;
			if (G::LocalPlayer->GetVelocity().Length2D() > 0.1 && G::LocalPlayer->GetFlags() & FL_ONGROUND)
			{
				oldcurtime = I::Globals->curtime;

			}
			if (G::LocalPlayer->GetVelocity().Length2D() < 0.1 && G::LocalPlayer->GetFlags() & FL_ONGROUND && flCurrentTime >= oldcurtime + 1.1 - nci->GetAvgLatency(0))
			{
				if (fliplol)
				{
					pCmd->viewangles.y -= U::RandomFloat(+180, -180);
				}
				else
				{
					pCmd->viewangles.y = U::RandomFloat(+180, -180);
				}
				oldcurtime = I::Globals->curtime;
				fliplol = !fliplol;
			}
			if (G::LocalPlayer->GetVelocity().Length2D() < 0.1 && G::LocalPlayer->GetFlags() & FL_ONGROUND && flCurrentTime < oldcurtime + 1.1 - nci->GetAvgLatency(0))
			{
				pCmd->viewangles.y = U::RandomFloat(170, 190);
			}
		}
	}
}

float GetLatency()
{
	INetChannelInfo *nci = I::Engine->GetNetChannelInfo();
	if (nci)
	{
		float Latency = nci->GetAvgLatency(FLOW_OUTGOING) + nci->GetAvgLatency(FLOW_INCOMING);
		return Latency;
	}
	else
	{
		return 0.0f;
	}
}

float GetOutgoingLatency()
{
	INetChannelInfo *nci = I::Engine->GetNetChannelInfo();
	if (nci)
	{
		float OutgoingLatency = nci->GetAvgLatency(FLOW_OUTGOING);
		return OutgoingLatency;
	}
	else
	{
		return 0.0f;
	}
}

float GetIncomingLatency()
{
	INetChannelInfo *nci = I::Engine->GetNetChannelInfo();
	if (nci)
	{
		float IncomingLatency = nci->GetAvgLatency(FLOW_INCOMING);
		return IncomingLatency;
	}
	else
	{
		return 0.0f;
	}
}

float OldLBY;
float LBYBreakerTimer;
float LastLBYUpdateTime;
bool bSwitch;

float CurrentVelocity(CBaseEntity* LocalPlayer)
{
	int vel = LocalPlayer->GetVelocity().Length2D();
	return vel;
}

bool NextLBYUpdate()
{
	CBaseEntity* LocalPlayer = G::LocalPlayer;

	float flServerTime = (float)(LocalPlayer->GetTickBase()  * I::Globals->interval_per_tick);


	if (OldLBY != LocalPlayer->GetLowerBodyTarget())
	{
		LBYBreakerTimer++;
		OldLBY = LocalPlayer->GetLowerBodyTarget();
		bSwitch = !bSwitch;
		LastLBYUpdateTime = flServerTime;
	}

	if (CurrentVelocity(LocalPlayer) > 0.5)
	{
		LastLBYUpdateTime = flServerTime;
		return false;
	}

	if ((LastLBYUpdateTime + 1 - (GetLatency() * 2) < flServerTime) && (LocalPlayer->GetFlags() & FL_ONGROUND))
	{
		if (LastLBYUpdateTime + 1.1 - (GetLatency() * 2) < flServerTime)
		{
			LastLBYUpdateTime += 1.1;
		}
		return true;
	}
	return false;
}

void DoLBYBreak(CUserCmd * pCmd, CBaseEntity* pLocal, bool& bSendPacket)
{
	if (!G::SendPacket)
	{
		if (NextLBYUpdate())
			pCmd->viewangles.y += 90;
		else
			pCmd->viewangles.y -= 90;
	}
	else
	{
		if (NextLBYUpdate())
			pCmd->viewangles.y -= 90;
		else
			pCmd->viewangles.y += 90;
	}
}

void DoLBYBreakReal(CUserCmd * pCmd, CBaseEntity* pLocal, bool& bSendPacket)
{
	if (!G::SendPacket)
	{
		if (NextLBYUpdate())
			pCmd->viewangles.y -= 90;
		else
			pCmd->viewangles.y += 90;
	}
	else
	{
		if (NextLBYUpdate())
			pCmd->viewangles.y += 90;
		else
			pCmd->viewangles.y -= 90;
	}
}

void DoRealAA(CUserCmd* pCmd, CBaseEntity* pLocal, bool& bSendPacket)
{
	float yaw;
	static int state = 0;
	static bool bFlip = false;

	float flCurTime = I::Globals->curtime;
	static float flTimeUpdate = 1.09f;
	static float flNextTimeUpdate = flCurTime + flTimeUpdate;
	if (flCurTime >= flNextTimeUpdate)
	{
		bFlip = !bFlip;
		state = 0;
	}

	if (flNextTimeUpdate < flCurTime || flNextTimeUpdate - flCurTime > 10.f)
		flNextTimeUpdate = flCurTime + flTimeUpdate;

	static bool switch2;

	if (!Vars.Ragebot.Antiaim.Enabled)
		return;
	switch (Vars.Ragebot.Antiaim.RealYaw)
	{
	case 0:
		break;
	case 1:
		// Fast Spin
		AntiAims::FastSpint(pCmd);
		break;
	case 2:
		// Slow Spin
		AntiAims::SlowSpin(pCmd);
		break;
	case 3:
		AntiAims::Jitter(pCmd);
		break;
	case 4:
		// 180 Jitter
		AntiAims::BackJitter(pCmd);
		break;
	case 5:
		//backwards
		pCmd->viewangles.y -= 180;
		break;
	case 6:
		AntiAims::BackwardJitter(pCmd);
		break;
	case 7:
		//Sideways-switch
		if (switch2)
			pCmd->viewangles.y = 90;
		else
			pCmd->viewangles.y = -90;

		switch2 = !switch2;
		break;
	case 8:
		//Sideways
		pCmd->viewangles.y -= 90;
		break;
	case 9:
		pCmd->viewangles.y += 90;
		break;
	case 10:
		pCmd->viewangles.y = pLocal->GetLowerBodyTarget() + rand() % 180 - rand() % 50;
		break;
	case 11:
		AntiAims::LBYJitter(pCmd, G::SendPacket);
		break;
	case 12:
		AntiAims::FakeSideLBY(pCmd, G::SendPacket);
		break;
	case 13:
		AntiAims::LBYSpin(pCmd, G::SendPacket);
		break;
	case 14:
		DoLBYBreakReal(pCmd, pLocal, G::SendPacket);
		break;
	case 15:
		AntiAims::LBYBreak1(pCmd);
		break;
	}
}

void DoFakeAA(CUserCmd* pCmd, bool& bSendPacket, CBaseEntity* pLocal)
{
	float yaw;
	static int state = 0;
	static bool bFlip = false;

	float flCurTime = I::Globals->curtime;
	static float flTimeUpdate = 1.09f;
	static float flNextTimeUpdate = flCurTime + flTimeUpdate;
	if (flCurTime >= flNextTimeUpdate)
	{
		bFlip = !bFlip;
		state = 0;
	}

	if (flNextTimeUpdate < flCurTime || flNextTimeUpdate - flCurTime > 10.f)
		flNextTimeUpdate = flCurTime + flTimeUpdate;

	static bool switch2;

	if (!Vars.Ragebot.Antiaim.Enabled)
		return;

	switch (Vars.Ragebot.Antiaim.FakeYaw)
	{
	case 0:
		break;
	case 1:
		// Fast Spin 
		AntiAims::FastSpint(pCmd);
		break;
	case 2:
		// Slow Spin 
		AntiAims::SlowSpin(pCmd);
		break;
	case 3:
		AntiAims::Jitter(pCmd);
		break;
	case 4:
		// 180 Jitter 
		AntiAims::BackJitter(pCmd);
		break;
	case 5:
		//backwards
		pCmd->viewangles.y -= 180;
		break;
	case 6:
		AntiAims::BackwardJitter(pCmd);
		break;
	case 7:
		//Sideways-switch
		if (switch2)
			pCmd->viewangles.y = 90;
		else
			pCmd->viewangles.y = -90;

		switch2 = !switch2;
		break;
	case 8:
		pCmd->viewangles.y -= 90;
		break;
	case 9:
		pCmd->viewangles.y += 90;
		break;
	case 10:
		pCmd->viewangles.y = pLocal->GetLowerBodyTarget() + rand() % 180 - rand() % 50;
		break;
	case 11:
		AntiAims::LBYJitter(pCmd, G::SendPacket);
		break;
	case 12:
		AntiAims::FakeSideLBY(pCmd, G::SendPacket);
		break;
	case 13:
		AntiAims::LBYSpin(pCmd, G::SendPacket);
		break;
	case 14:
		DoLBYBreak(pCmd, pLocal, G::SendPacket);
		break;
	case 15:
		AntiAims::LBYBreak1(pCmd);
		break;
	}
}

void CAntiAim::DoAntiAim(CUserCmd *pCmd, bool &bSendPacket)
{
	CBaseEntity* pLocal = G::LocalPlayer;

	if (Vars.Ragebot.Antiaim.AimAtPlayer)
		aimAtPlayer();

	static bool up = true;
	up = !up;

	switch (Vars.Ragebot.Antiaim.Pitch)
	{
	case 0:
		break;
	case 1://middle up
		pCmd->viewangles.x = 45.f;
		break;
	case 2://jitter up
	
		if (up)
			pCmd->viewangles.x = 45;
		else
			pCmd->viewangles.x = 89;

		break;
	case 3://down
		pCmd->viewangles.x = 89.0f;
		break;
	case 4://up
		pCmd->viewangles.x = -89.0f;
		break;
	case 5://Zero
		pCmd->viewangles.x = 0.f;
		break;

	}

	static bool send_packet_flip = false;

	if (!Vars.Misc.fakelag)
	{
		send_packet_flip = !send_packet_flip;
		G::SendPacket = send_packet_flip;
	}


	static float last_time = 0.0f;
	float flServerTime = (float)(pLocal->GetTickBase()  * I::Globals->interval_per_tick);

	bool lower_body_flip = false;
	if (pLocal->GetVelocity().Length2D() > 0.1)
	{
		last_time = flServerTime + 0.22f;
		lower_body_flip = true;
	}
	else {
		if (last_time >= flServerTime)//=
		{
			last_time = flServerTime + 1.1f;
			lower_body_flip = true;
		}
	}

	if (G::SendPacket || (lower_body_flip && Vars.Ragebot.Antiaim.FakeEdge))//fake or lowerbody (visible)
	{
		bool flip_fake = false;
		flip_fake = !flip_fake;

		switch (Vars.Ragebot.Antiaim.FakeYaw)//fake yaws
		{
		case 0://nothing
			break;
		case 1:
			pCmd->viewangles.y += 180.0f;//backwards
			break;
		case 2:
			pCmd->viewangles.y += (flip_fake) ? -112.0f : 112.0f;//jitter
			break;
		case 3:
			pCmd->viewangles.y += (flip_fake) ? -90 : 90;//sideways
			break;
		}
	}
	else//real (invisible)
	{
		static bool flip_real;
		flip_real = !flip_real;

		int tick = pCmd->tick_count % 360;

		switch (Vars.Ragebot.Antiaim.RealYaw)//real yaws	
		{
		case 0://nothing
			break;
		case 1://backwards
			pCmd->viewangles.y += 180.0f;
			break;
		case 2://lby flip 180
			pCmd->viewangles.y = pLocal->GetLowerBodyTarget() + 180.0f;
			break;
		case 3://lby jitter
			pCmd->viewangles.y = pLocal->GetLowerBodyTarget() + (flip_real) ? -112.0f : 112.0f;
			break;
		case 4://lby sideways
			pCmd->viewangles.y = pLocal->GetLowerBodyTarget() + (flip_real) ? -90.0f : 90.0f;
			break;
		case 5://delta
			pCmd->viewangles.y = (pLocal->GetLowerBodyTarget() - pLocal->GetEyeAngles().y) + 60.0f;
			break;
		case 6://delta jitter
			pCmd->viewangles.y = (pLocal->GetLowerBodyTarget() - pLocal->GetEyeAngles().y) + (flip_real) ? -112.0f : 112.0f;
			break;
		case 7://delta uff
			pCmd->viewangles.y = tick * (pLocal->GetLowerBodyTarget() - pLocal->GetEyeAngles().y) + 35.0f;
			break;
		case 8://uffjaonetab
			pCmd->viewangles.y = tick * (pLocal->GetLowerBodyTarget() - pLocal->GetEyeAngles().y) + 35.0f;
			break;
		}

		if (Vars.Ragebot.Antiaim.Shuffle)
		{
			if (pLocal->GetLowerBodyTarget() == pCmd->viewangles.y)
			{
				pCmd->viewangles.y += U::RandomFloat(33.983148f, -33.983148f);
			}
		}
	}
}

void CAntiAim::aimAtPlayer()
{
	if (!G::LocalPlayer || !G::LocalPlayer->GetWeapon() || !G::LocalPlayer->GetWeapon()->GetCSWpnData())
		return;

	Vector eye_position = G::LocalPlayer->GetEyePosition();

	float best_dist = G::LocalPlayer->GetWeapon()->GetCSWpnData()->flRange;

	CBaseEntity* target = I::ClientEntList->GetClientEntity(G::BestTarget);

	if (target == NULL)
		return;

	if (target == G::LocalPlayer)
		return;

	if ((target->GetTeam() == G::LocalPlayer->GetTeam()) || target->GetDormant() || !target->GetAlive() || target->GetHealth() <= 0)
		return;

	Vector target_position = target->GetEyePosition();

	float temp_dist = eye_position.Dist(target_position);

	if (best_dist > temp_dist)
	{
		best_dist = temp_dist;
		G::UserCmd->viewangles = M::CalcAngle(eye_position, target_position);
	}
}