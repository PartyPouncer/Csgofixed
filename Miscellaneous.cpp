#include "Cheat.h"
#include <sstream>
#include <fstream>

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

void CMiscellaneous::Initialize()
{
	if ( m_bInitialized )
		return;
}

void CMiscellaneous::Run()
{
	_JUNK_BLOCK(jmp_label1)
	Bunnyhop();
}

void CMiscellaneous::Think()
{

}

void CMiscellaneous::Bunnyhop()
{
	static bool bLastJumped = false;
	static bool bShouldFake = false;

	if( !bLastJumped && bShouldFake ) 
	{
		bShouldFake = false;
		G::UserCmd->buttons |= IN_JUMP;
	}
	else if( G::UserCmd->buttons & IN_JUMP ) 
	{
		if( G::LocalPlayer->GetFlags() & FL_ONGROUND ) 
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else 
		{
			G::UserCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else 
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}

template<class T, class U>
T Clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}

void CMiscellaneous::AutoStrafe()
{
	_JUNK_BLOCK(jmp_label2)
	if (G::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || G::LocalPlayer->GetMoveType() == MOVETYPE_LADDER) return;
	if ((G::LocalPlayer->GetFlags() & FL_ONGROUND)) return;
	static float move = 650.f;
	float s_move = move * 0.5065f;

	G::UserCmd->forwardmove = move * 0.015f;
	G::UserCmd->sidemove += static_cast<float>(((G::UserCmd->tick_count % 2) * 2) - 1) * s_move;

	if (G::UserCmd->mousedx)
		G::UserCmd->sidemove = static_cast<float>(Clamp(G::UserCmd->mousedx, -1, 1)) * s_move;

	static auto strafe = G::UserCmd->viewangles.y;

	float rt = G::UserCmd->viewangles.y, rotation;
	rotation = strafe - rt;

	if (rotation < -I::Globals->interval_per_tick)
		G::UserCmd->sidemove = -s_move;

	if (rotation > I::Globals->interval_per_tick)
		G::UserCmd->sidemove = s_move;

	strafe = rt;
}

void CMiscellaneous::RageAutoStrafe(CUserCmd* pCmd)
{
	_JUNK_BLOCK(jmp_label3)
	if (G::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || G::LocalPlayer->GetMoveType() == MOVETYPE_LADDER) return;
	if ((G::LocalPlayer->GetFlags() & FL_ONGROUND)) return;

	if (GetAsyncKeyState(0x57)//W 
		|| GetAsyncKeyState(0x41)//A
		|| GetAsyncKeyState(0x53)//S
		|| GetAsyncKeyState(0x44))//D
		return;

	if (GetAsyncKeyState(VK_SPACE) && (G::LocalPlayer->GetFlags() & FL_ONGROUND)
		&& G::LocalPlayer->GetVelocity().Length() <= 60.f)
	{
		pCmd->forwardmove = 450.f;
	}
	auto Delta = 0.f;
	if (G::LocalPlayer->GetVelocity().Length() > 60.f)
	{
		auto x = 45.f;
		auto z = x / G::LocalPlayer->GetVelocity().Length();
		z = fabsf(z);
		auto a = x * z;
		Delta = a;
	}
	if (GetAsyncKeyState(VK_SPACE) && !(G::LocalPlayer->GetFlags() & FL_ONGROUND))
	{
		if (pCmd->mousedx < 0)
			pCmd->sidemove = -450;
		if (pCmd->mousedx > 0)
			pCmd->sidemove = 450;
		if (pCmd->tick_count % 2)
		{
			pCmd->sidemove = -450;
		}
		else
		{
			pCmd->viewangles.y += Delta;
			pCmd->sidemove = 450;
		}
	}
}

size_t linenum = 0;

void CMiscellaneous::Chatspam()
{
	_JUNK_BLOCK(jmp_label4)
	static float nextTime = 0.f;
	float flServerTime = I::Globals->curtime * 0.5f;
	
	if ( m_spamlines.empty() )
		return;

	if( Vars.Misc.ChatSpamMode == 0 )
		linenum = rand() % m_spamlines.size() - 1;

	if (nextTime > flServerTime)
		return;

	nextTime = flServerTime + 0.5f;

	char str[512];
	strcpy( str, charenc( "say " ) );
	strcat( str, m_spamlines[ linenum ].c_str() );

	I::Engine->ClientCmd_Unrestricted(( str ),0);

	if( Vars.Misc.ChatSpamMode == 1 )
	{
		linenum++;

		if( linenum >= m_spamlines.size() )
			linenum = 0;
	}
}

void CMiscellaneous::ReadChatspam( const char* fileName )
{
	_JUNK_BLOCK(jmp_label5)
	m_spamlines.clear();

	std::ifstream spamfile( fileName );
	if ( spamfile.good() )
	{
		std::string line;

		while ( std::getline( spamfile, line ) )
			m_spamlines.push_back( line );

		linenum = 0;

		spamfile.close();

		U::PrintMessage(charenc( "%s%s%s\n"), charenc( " Spam file " ), fileName, charenc( " Loaded! " ) );
	}
}

void CMiscellaneous::ChangeName( const char* name )
{
	_JUNK_BLOCK(jmp_label6)
	ConVar* nameConvar = I::Cvar->FindVar( charenc( "name" ) );
	*( int* )( ( DWORD )&nameConvar->fnChangeCallback + 0xC ) = NULL;
	nameConvar->SetValue(name);//name
}


void CMiscellaneous::AirStuck()
{
	_JUNK_BLOCK(jmp_label7)
	static bool rdy;

	if (G::LocalPlayer->GetWeapon()->GetNextPrimaryAttack() - (G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick) < 0 && G::UserCmd->buttons & IN_ATTACK)
	{
		return;
	}
	if (G::PressedKeys[Vars.Misc.AirStuckKey])
		G::UserCmd->tick_count = 174522396;
}

void CMiscellaneous::AutoPistol()
{
	_JUNK_BLOCK(jmp_label8)
	CBaseEntity* pWeapon = reinterpret_cast<CBaseEntity*>(G::LocalPlayer->GetWeapon());
	if (pWeapon != NULL)
	{
		ClientClass* pWeaponClass = pWeapon->GetClientClass();

		if ((G::UserCmd->buttons & IN_ATTACK) && (G::LocalPlayer->GetWeapon()->GetNextPrimaryAttack()
			- ((float)G::LocalPlayer->GetTickBase()
				* I::Globals->interval_per_tick) > 0) &&
				(pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponElite) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponFiveSeven) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponP228) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponGlock) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponUSP) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CDEagle) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponP250) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponTec9) ||
					pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponHKP2000)))
			G::UserCmd->buttons &= ~IN_ATTACK;
	}

}

void CMiscellaneous::MTeleport()
{
	_JUNK_BLOCK(jmp_label9)
		G::UserCmd->tick_count = 174522396;
}

void CMiscellaneous::moonwalk()
{
	_JUNK_BLOCK(jmp_label10)
	if (G::LocalPlayer->GetMoveType() == MOVETYPE_LADDER || G::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (G::UserCmd->buttons & IN_FORWARD)
	{
		G::UserCmd->forwardmove = 450;
		G::UserCmd->buttons &= ~IN_FORWARD;
		G::UserCmd->buttons |= IN_BACK;
	}
	else if (G::UserCmd->buttons & IN_BACK)
	{
		G::UserCmd->forwardmove = -450;
		G::UserCmd->buttons &= ~IN_BACK;
		G::UserCmd->buttons |= IN_FORWARD;
	}

	if (G::UserCmd->buttons & IN_MOVELEFT)
	{
		G::UserCmd->sidemove = -450;
		G::UserCmd->buttons &= ~IN_MOVELEFT;
		G::UserCmd->buttons |= IN_MOVERIGHT;
	}
	else if (G::UserCmd->buttons & IN_MOVERIGHT)
	{
		G::UserCmd->sidemove = 450;
		G::UserCmd->buttons &= ~IN_MOVERIGHT;
		G::UserCmd->buttons |= IN_MOVELEFT;
	}
}

void CMiscellaneous::NameHide()
{
	_JUNK_BLOCK(jmp_label11)
	ConVar* nameConvar = I::Cvar->FindVar(charenc("name"));
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = NULL;
	nameConvar->SetValue("\n\xAD\xAD\xAD");//namesteal fix
}

void CMiscellaneous::NameSpammer()
{
	_JUNK_BLOCK(jmp_label12)
	static bool steal = false;
	ConVar* nameConvar = I::Cvar->FindVar(charenc("name"));
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = NULL;
	
	if (nameConvar)
	{
		if (steal)
		{
			nameConvar->SetValue(charenc("->FH4x<-"));
		}
		else
		{
			nameConvar->SetValue(charenc("<-FH4x->"));
		}

		steal = !steal;
	}
}

void CMiscellaneous::NameSpammer2()
{
	_JUNK_BLOCK(jmp_label13)
	static bool steal = false;
	ConVar* nameConvar = I::Cvar->FindVar(charenc("name"));
	*(int*)((DWORD)&nameConvar->fnChangeCallback + 0xC) = NULL;

	if (nameConvar)
	{
		if (steal)
		{
			nameConvar->SetValue(charenc("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n----------------------------YOUR AYYWARE PASTE HAS CRASHED----------------------------"));
		}
		else
		{
			nameConvar->SetValue(charenc("<-FH4x->"));
		}

		steal = !steal;
	}
}

void CMiscellaneous::NameSteal() 
{
	_JUNK_BLOCK(jmp_label14)
	static float nextTime = 0.f;
	float flServerTime = I::Globals->curtime * 0.5f;
	static ConVar* name = I::Cvar->FindVar("name");
	char* szName = NULL;

	while (!szName)
	{
		player_info_t pInfo;
		I::Engine->GetPlayerInfo(RandomInt(0, I::ClientEntList->GetHighestEntityIndex()), &pInfo);

		if (strcmp(pInfo.name, "") != 0 && !(strcmp(pInfo.name, "GOTV") == 0)) szName = pInfo.name;
	}
	

	char nameChar[64];
	sprintf(nameChar, "%s ", szName);
/*
	if (nextTime > flServerTime)
		return;

	nextTime = flServerTime + 0.5f;*/
	name->SetValue(nameChar);
}

//bool bTeleportSwitch;
//BYTE byteCorrupt[] = { 0xBE, 0x120 };
//BYTE byteDeCorrupt[] = { 0xBE, 0x20 };

void CMiscellaneous::Teleport()
{
	_JUNK_BLOCK(jmp_label15)
	if (G::PressedKeys[Vars.Misc.TeleportKey]&& !Vars.Ragebot.UntrustedCheck)
	{
		G::UserCmd->viewangles.z = FLT_MAX;
		/*BYTE* nulldata;
		static DWORD dwAddr = U::FindPatternAlt("client.dll", (PBYTE)"\xBE\x00\x00\x00\x00\x2B\xF1\x3B\xF3\x7D\x1F\x8B\x55\x0C\x8B\xC3", "x????xxxxxxxxxxx", NULL, NULL);
		auto bByte = bTeleportSwitch ? byteCorrupt : byteDeCorrupt;
		DWORD virtualProtect;
		VirtualProtect((LPVOID)(dwAddr), 4, PAGE_READWRITE, &virtualProtect);
		memcpy((LPVOID)(dwAddr), bByte, sizeof(bByte));
		VirtualProtect(re+pret_cast<void*>(dwAddr), 4, virtualProtect, &virtualProtect);
		bTeleportSwitch = !bTeleportSwitch;*/
	}
}

void CMiscellaneous::LocationSpam()
{
	_JUNK_BLOCK(jmp_label16)
	static auto iDelay = 0;
	iDelay++;

	for (int i = 0; i <= I::Globals->maxClients; i++)
	{

		CBaseEntity* pEntity = I::ClientEntList->GetClientEntity(i);



		if (!pEntity)
			continue;

		if (pEntity == G::LocalPlayer)
			continue;

		if (!pEntity->IsPlayer())
			continue;

		if (pEntity->GetTeam() == G::LocalPlayer->GetTeam())
			continue;

		if (pEntity->GetDormant())
			continue;

		if (!pEntity->GetAlive())
			continue;


		auto wep = pEntity->GetWeapon();
		auto weaponID = *reinterpret_cast<int*>(DWORD(wep) + offsets.m_iItemDefinitionIndex);
		auto Location = reinterpret_cast<char*>(DWORD(pEntity) + offsets.m_szLastPlaceName);
		auto Health = *reinterpret_cast<int*>(DWORD(pEntity) + offsets.m_iHealth);

		player_info_t info;
		info = pEntity->GetPlayerInfo();


		int xiDelay = 450;

		if (iDelay > xiDelay)
			iDelay = 0;

		if (iDelay == xiDelay)
		{
			char pszBuffer[6969];
			sprintf_s(pszBuffer, "say_team %s | %d HP | %s | %s", info.name, Health, Location, pEntity->GetWeapon()->GetWeaponName().c_str());

			I::Engine->ClientCmd(pszBuffer);
		}
	}
}

void CMiscellaneous::AutoBlocker(CUserCmd* cmd)
{
	_JUNK_BLOCK(jmp_label17)
	float bestdist = 250.f;
	int index = -1;

	if (G::PressedKeys[Vars.Misc.AutoblockerKey])
	for (int i = 0; i < I::Globals->maxClients; i++)
	{
		CBaseEntity* entity = I::ClientEntList->GetClientEntity(i);

		if (!entity)
			continue;

		if (!entity->GetAlive() || entity->GetDormant() || entity == G::LocalPlayer)
			continue;

		float dist = M::VectorDistance(G::LocalPlayer->GetOrigin(), entity->GetOrigin());

		if (dist < bestdist)
		{
			bestdist = dist;
			index = i;
		}
	}

	if (index == -1)
		return;

	CBaseEntity* target = I::ClientEntList->GetClientEntity(index);

	if (!target)
		return;

	QAngle angles = M::CalcAngle(G::LocalPlayer->GetOrigin(), target->GetOrigin());

	angles.y -= G::LocalPlayer->GetEyeAngles().y;
	angles.Normalized();

	if (angles.y < 0.0f)
		cmd->sidemove = 450.f;
	else if (angles.y > 0.0f)
		cmd->sidemove = -450.f;
}

void CMiscellaneous::SetClanTag(const char* tag, const char* name)
{
	_JUNK_BLOCK(jmp_label18)
	SetClanTagFn SetClanTagEx = reinterpret_cast<SetClanTagFn >(offsets.ChangeClanTag);
	SetClanTagEx(tag, name);
}

void CMiscellaneous::Walkbot(CUserCmd* pCmd, CBaseEntity* Local)
{
	_JUNK_BLOCK(jmp_label19)
	bool walkbotBefore = false;


	QAngle viewangles;
	I::Engine->GetViewAngles(viewangles);

	auto fDistanceToWall = [&](Vector diff = Vector(0, 0, 0))->float
	{
		Vector src, dst, forward;
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		QAngle viewangle = G::UserCmd->viewangles;
		M::AngleVectors(viewangle, &forward);
		forward *= G::LocalPlayer->GetWeapon()->GetCSWpnData()->flRange;
		filter.pSkip = G::LocalPlayer;
		src = G::LocalPlayer->GetEyePosition();
		dst = src + forward;

		ray.Init(src, dst);

		I::EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
		return (src - tr.endpos).LengthSqr();
	};
	static float old1, old2, old3;
	if (Local->GetVelocity().Length() < 3)
	{
		viewangles.y += 15.f;
	}


	if (fDistanceToWall() < 110)
	{

		float negativeDist = fDistanceToWall(Vector(0, -1, 0)), positiveDist = fDistanceToWall(Vector(0, 1, 0));
		if (abs(negativeDist - positiveDist) < 1.0f)
		{

			viewangles.y += 15.f;
		}
		else
		{

			viewangles.y += positiveDist < negativeDist ? -1 : 1;

		}
	}
	G::UserCmd->viewangles.Clamp();

	I::Engine->SetViewAngles(viewangles);

	if (!walkbotBefore)
	{
		if(Vars.Ragebot.Enabled)
		G::UserCmd->forwardmove = -450;
		else
			G::UserCmd->forwardmove = +450;

		walkbotBefore = true;
	}

	else if (walkbotBefore)
	{
		walkbotBefore = false;

		if (Vars.Ragebot.Enabled)
		G::UserCmd->forwardmove = 450;
		else
			G::UserCmd->forwardmove = -450;
	}
}


void CMiscellaneous::fakelag()
{
	_JUNK_BLOCK(jmp_label20)
	if (G::UserCmd->buttons & IN_ATTACK || Vars.Legitbot.Aimbot.legitaa)
		return;

	static int lagSwitch = -Vars.Misc.fakelagsend;

	if (Vars.Misc.fakelagchoke > 0 && Vars.Misc.fakelagsend > 0)
	{
		if (lagSwitch < 0)
		{
			G::SendPacket = true;
		}
		else {
			if (lagSwitch >= Vars.Misc.fakelagchoke)
			{
				lagSwitch = -Vars.Misc.fakelagsend;
			}
			G::SendPacket = false;
		}
		lagSwitch++;
	}
}

void CMiscellaneous::svcheats()
{
	_JUNK_BLOCK(jmp_label21)
	auto svcheats = I::Cvar->FindVar("sv_cheats");
	auto svcheatsspoof = new SpoofedConvar(svcheats);
	svcheatsspoof->SetInt(1);
}


void CMiscellaneous::ForceThirdPerson()
{
	_JUNK_BLOCK(jmp_label22)
	if (I::Engine->IsInGame() && G::LocalPlayer)

	{
		if (G::LocalPlayer->GetAlive() && Vars.Misc.thirdperson || GetAsyncKeyState(0x04) & 0x1)
		{
			I::Engine->ExecuteClientCmd("thirdperson");
		}
		else
			if (!Vars.Misc.thirdperson && !GetAsyncKeyState(0x04) & 0x1 || !G::LocalPlayer->GetAlive())
			{
				I::Engine->ExecuteClientCmd("firstperson");
			}
	}
}


unsigned int vguiPanel;
void CMiscellaneous::RemoveScope()
{
	_JUNK_BLOCK(jmp_label23)
	if (Vars.Visuals.Removals.Scope && G::LocalPlayer->IsScoped() && G::LocalPlayer->GetAlive())
	{
		    ConVar* postprocess = I::Cvar->FindVar("mat_postprocess_enable");
			postprocess->SetValue(0);
			int Width;
			int Height;
			I::Engine->GetScreenSize(Width, Height);
			Color cColor = Color(0, 0, 0, 255);
			D::DrawLine(Width / 2, 0, Width / 2, Height, cColor);
			D::DrawLine(0, Height / 2, Width, Height / 2, cColor);
	}
}

void CMiscellaneous::postprozess()
{
	_JUNK_BLOCK(jmp_label24)
	ConVar* postprocess = I::Cvar->FindVar("mat_postprocess_enable");

	if (Vars.Visuals.Removals.Postprocess)
	{
		postprocess->SetValue(0);
	}
	else if(!Vars.Visuals.Removals.Postprocess)
	{
		postprocess->SetValue(1);
	}
}

void CMiscellaneous::FakeWalk(CUserCmd* pCmd, bool &bSendPacket)
{
	_JUNK_BLOCK(jmp_label25)
	CBaseEntity* pLocal = G::LocalPlayer;

	if (G::PressedKeys[Vars.Misc.FakewalkKey])
	{
		static int iChoked = -1;
		iChoked++;

		if (iChoked < 1)
		{
			bSendPacket = false;

			pCmd->tick_count += 10;
			pCmd->command_number += 7 + pCmd->tick_count % 2 ? 0 : 1;

			pCmd->buttons |= pLocal->GetMoveType() == IN_BACK;
			pCmd->forwardmove = pCmd->sidemove = 0.f;
		}
		else
		{
			bSendPacket = true;
			iChoked = -1;

			I::Globals->frametime *= (pLocal->GetVelocity().Length2D()) / 1.f;
			pCmd->buttons |= pLocal->GetMoveType() == IN_FORWARD;
		}
	}
}

std::string clan_tag_meme(const std::string src_org,const std::string custom_keys_org,int interval,int end_interval)
{
	_JUNK_BLOCK(jmp_label26)
	std::string src = src_org.data();
	std::string custom_keys = custom_keys_org.data();

	if (src.empty() || custom_keys.empty())
		return "";

	std::string new_tag;
	static bool is_last_char = false;
	static int cur_string_pos, cur_key_pos, old_string_size, set_time;
	set_time++;

	if (old_string_size != src.size())
	{
		old_string_size = src.size();
		cur_string_pos = 0;
		cur_key_pos = 0;
		is_last_char = false;
	}

	if (is_last_char)
	{
		if (set_time >= end_interval)
		{
			set_time = 0;
			cur_string_pos = 0;
			cur_key_pos = 0;
			is_last_char = false;
		}
		return src;
	}
		
	for (int x = 0; x < cur_string_pos + 1; x++)
		new_tag.push_back(src.at(x));

	new_tag.at(cur_string_pos) = custom_keys.at(cur_key_pos);

	if (set_time >= interval)
	{
		set_time = 0;
		cur_key_pos++;
	}

	if (cur_key_pos >= custom_keys.size())
	{
		cur_key_pos = 0;
		cur_string_pos++;

		if (cur_string_pos >= src.size())
		{
				is_last_char = true;
		}
			
	}
		
	return new_tag;
}

void CMiscellaneous::aniclantag()
{
	_JUNK_BLOCK(jmp_label27)
	//std::string clantag = "->FH4x<-";
	//static int index;
	//static bool reverse;

	//// Every 16 user commands we will update our tag
	//if (G::UserCmd->command_number % 32 == 0) {
	//	// Add or subtract depending on the direction we're going
	//	index += reverse ? -1 : 1;
	//	// If we reach the end of our tag or the beginning, reverse the operation
	//	if (index > clantag.length() - 1 || index < 1) {
	//		reverse = !reverse;
	//	}

	//	// Make sure the index doesn't exceed the length of the string
	//	index = index, 0, clantag.length();
	//	// Set the clan tag
	//	E::Misc->SetClanTag(clantag.substr(0, index).c_str(), clantag.c_str());
	//}

	E::Misc->SetClanTag(clan_tag_meme(Vars.Misc.clantagbuffer, Vars.Misc.tag_chars, Vars.Misc.interval, Vars.Misc.interval_end).c_str(), "FH4x");

	//ORIGINAL CODENZ
	/*static int ClanCounter = (float)G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick;
	static int ClanState = 10;
	int ServerTime = (float)G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick;

	if (ClanCounter % 1== 0)
		ClanState++;
	int TimeValue = ServerTime % 22;
	switch (TimeValue) 
	{
	case 0:E::Misc->SetClanTag(" ", "FH4x"); break; 
	case 1:E::Misc->SetClanTag("/", "FH4x"); break;
	case 2:E::Misc->SetClanTag("-", "FH4x"); break;
	case 3:E::Misc->SetClanTag("\\", "FH4x"); break;
	case 4:E::Misc->SetClanTag("|", "FH4x"); break;
	case 5:E::Misc->SetClanTag("F/", "FH4x"); break;
	case 6:E::Misc->SetClanTag("F-", "FH4x"); break;
	case 7:E::Misc->SetClanTag("F\\", "FH4x"); break;
	case 8:E::Misc->SetClanTag("F|", "FH4x"); break;
	case 9:E::Misc->SetClanTag("FH/", "FH4x"); break;
	case 10:E::Misc->SetClanTag("FH-", "FH4x"); break;
	case 11:E::Misc->SetClanTag("FH\\", "FH4x"); break;
	case 12:E::Misc->SetClanTag("FH|", "FH4x"); break;
	case 13:E::Misc->SetClanTag("FH4/", "FH4x"); break;
	case 14:E::Misc->SetClanTag("FH4-", "FH4x"); break;
	case 15:E::Misc->SetClanTag("FH4\\", "FH4x"); break;
	case 16:E::Misc->SetClanTag("FH4|", "FH4x"); break;
	case 17:E::Misc->SetClanTag("FH4x", "FH4x"); break;
	case 18:E::Misc->SetClanTag("    ", "FH4x"); break;
	case 19:E::Misc->SetClanTag("FH4x", "FH4x"); break;
	case 20:E::Misc->SetClanTag("    ", "FH4x"); break;
	case 21:E::Misc->SetClanTag("FH4x", "FH4x"); break;
	}
	ClanCounter++;*/
}

void CMiscellaneous::AutoRevolver()
{
	_JUNK_BLOCK(jmp_label28)
	/*if (G::LocalPlayer->GetWeapon()->IsRevolver())
	{
			G::UserCmd->buttons |= IN_ATTACK;
			float flPostponeFireReady = G::LocalPlayer->GetWeapon()->GetflPostponeFireReadyTime();
			if (flPostponeFireReady > 0 && flPostponeFireReady - 1.f < I::Globals->curtime)
			{
				G::UserCmd->buttons &= ~IN_ATTACK;
			}	*/
			if (G::LocalPlayer->GetWeapon()->IsRevolver() && I::Globals->curtime - G::LocalPlayer->GetWeapon()->GetflPostponeFireReadyTime() < 0.0f)
				G::UserCmd->buttons |= IN_ATTACK;
	/*}*/
}


void CMiscellaneous::Panic()
{
	if (!G::PressedKeys[VK_END])
		return;
	_JUNK_BLOCK(jmp_label29)
	I::Engine->ClientCmd_Unrestricted(charenc("cl_mouseenable 1"), 0);
	I::Engine->ClientCmd_Unrestricted(charenc("crosshair 1"), 0);

	H::ModelRender->UnHook();
	H::VPanel->UnHook();
	H::ClientMode->UnHook();
	H::Client->UnHook();
	H::Surface->UnHook();
	H::D3D9->UnHook();
	SetWindowLongPtr(G::Window, GWL_WNDPROC, (LONG_PTR)Hooks::oldWindowProc);
	FreeLibraryAndExitThread(G::Dll, 0);
	exit(0);
}