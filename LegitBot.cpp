#include "Cheat.h"
#define JUNKS \
__asm _emit 0x75 \
__asm _emit 0x98 \
__asm _emit 0x36 \
__asm _emit 0x97 \
__asm _emit 0x23 \
__asm _emit 0x09 \
__asm _emit 0x43 \
__asm _emit 0x87 \
__asm _emit 0x78 \
__asm _emit 0x27 \
__asm _emit 0x73 \
__asm _emit 0x33 \
__asm _emit 0x96 \
__asm _emit 0x77 \
// Don't change this!
#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:

CLegitBot* LegitBot;

float m_fbestfov = 20.0f;
int m_ibesttargetlegit = -1;

float deltaTime;
float curAimTime;

int bestHitboxTarget = -1;
#define TICK_INTERVAL			(I::Globals->interval_per_tick)

#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )


std::string GetWeapbyID(int id)
{
	_JUNK_BLOCK(jmp_label1)
	switch (id)
	{
	case WEAPON_DEAGLE:
		return strenc("Desert Eagle");
	case WEAPON_ELITE:
		return strenc("Dual Berettas");
	case WEAPON_FIVESEVEN:
		return strenc("Five-SeveN");
	case WEAPON_GLOCK:
		return strenc("Glock-18");
	case WEAPON_AK47:
		return strenc("AK-47");
	case WEAPON_AUG:
		return strenc("AUG");
	case WEAPON_AWP:
		return strenc("AWP");
	case WEAPON_FAMAS:
		return strenc("FAMAS");
	case WEAPON_G3SG1:
		return strenc("G3SG1");
	case WEAPON_GALILAR:
		return strenc("Galil");
	case WEAPON_M249:
		return strenc("M249");
	case WEAPON_M4A1:
		return strenc("M4A1");
	case WEAPON_MAC10:
		return strenc("MAC-10");
	case WEAPON_P90:
		return strenc("P90");
	case WEAPON_UMP45:
		return strenc("UMP-45");
	case WEAPON_XM1014:
		return strenc("XM1014");
	case WEAPON_BIZON:
		return strenc("PP-Bizon");
	case WEAPON_MAG7:
		return strenc("MAG-7");
	case WEAPON_NEGEV:
		return strenc("Negev");
	case WEAPON_SAWEDOFF:
		return strenc("Sawed-Off");
	case WEAPON_TEC9:
		return strenc("Tec-9");
	case WEAPON_TASER:
		return strenc("Taser");
	case WEAPON_HKP2000:
		return strenc("P2000");
	case WEAPON_MP7:
		return strenc("MP7");
	case WEAPON_MP9:
		return strenc("MP9");
	case WEAPON_NOVA:
		return strenc("Nova");
	case WEAPON_P250:
		return strenc("P250");
	case WEAPON_SCAR20:
		return strenc("SCAR-20");
	case WEAPON_SG556:
		return strenc("SG 553");
	case WEAPON_SSG08:
		return strenc("SSG 08");
	case WEAPON_KNIFE:
		return strenc("Knife");
	case WEAPON_FLASHBANG:
		return strenc("Flashbang");
	case WEAPON_HEGRENADE:
		return strenc("HE Grenade");
	case WEAPON_SMOKEGRENADE:
		return strenc("Smoke Grenade");
	case WEAPON_MOLOTOV:
		return strenc("Molotov");
	case WEAPON_DECOY:
		return strenc("Decoy");
	case WEAPON_INCGRENADE:
		return strenc("Incendiary Grenade");
	case WEAPON_C4:
		return strenc("C4");
	case WEAPON_KNIFE_T:
		return strenc("Knife");
	case WEAPON_M4A1_SILENCER:
		return strenc("M4A1-S");
	case WEAPON_USP_SILENCER:
		return strenc("USP-S");
	case WEAPON_CZ75A:
		return strenc("CZ75-Auto");
	case WEAPON_REVOLVER:
		return strenc("R8 Revolver");
	default:
		return strenc("Knife");
	}
}

std::string Weap = "++1";

void CLegitBot::ChangeSet()
{
	std::string weap = G::LocalPlayer->GetWeapon()->GetWeaponName();

	_JUNK_BLOCK(jmp_label2)
	if (I::Engine->IsInGame() && G::LocalPlayer->GetAlive())
	{
		Weap = "++1";

		WritePrivateProfileString(weap.c_str(), "Aimbot.Silent", std::to_string(Vars.Legitbot.Aimbot.Silent).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.MaxSpeed", std::to_string(Vars.Legitbot.Aimbot.MaxSpeed).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.Key", std::to_string(Vars.Legitbot.Aimbot.Key).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.OnKey", std::to_string(Vars.Legitbot.Aimbot.OnKey).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.Filter", std::to_string(Vars.Legitbot.Aimbot.Filter).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.RCS", std::to_string(Vars.Legitbot.Aimbot.RCS).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.RCSAmount", std::to_string(Vars.Legitbot.Aimbot.RCSAmount).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.RCSAMT", std::to_string(Vars.Legitbot.Aimbot.RCSAMT).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.Speed", std::to_string(Vars.Legitbot.Aimbot.Speed).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.Hitbox", std::to_string(Vars.Legitbot.Aimbot.Hitbox).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.FOV", std::to_string(Vars.Legitbot.Aimbot.FOV).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.AlwaysOn", std::to_string(Vars.Legitbot.Aimbot.AlwaysOn).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.FriendlyFire", std::to_string(Vars.Legitbot.Aimbot.FriendlyFire).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.Faceitmode", std::to_string(Vars.Legitbot.Aimbot.Faceitmode).c_str(), "C:\\settings.ini");
		WritePrivateProfileString(weap.c_str(), "Aimbot.Smokecheck", std::to_string(Vars.Legitbot.Aimbot.Smokecheck).c_str(), "C:\\settings.ini");
	}

}

void ReadSettings(std::string weap)
{	
	_JUNK_BLOCK(jmp_label3)
	 if (Weap != weap)
	 {
		 Weap = weap;

		char* tmp = new char[32];

		 Vars.Legitbot.Aimbot.Silent = GetPrivateProfileInt(weap.c_str(), "Aimbot.Silent", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.MaxSpeed = GetPrivateProfileInt(weap.c_str(), "Aimbot.MaxSpeed", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.Key = GetPrivateProfileInt(weap.c_str(), "Aimbot.Key", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.OnKey = GetPrivateProfileInt(weap.c_str(), "Aimbot.OnKey", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.Filter = GetPrivateProfileInt(weap.c_str(), "Aimbot.Filter", 0, "C:\\settings.ini");

		 GetPrivateProfileString(weap.c_str(), "Aimbot.RCS", "0.0", tmp, 32, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.RCS = atof(tmp);

		 GetPrivateProfileString(weap.c_str(), "Aimbot.RCSAmount", "0.0", tmp, 32, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.RCSAmount = atof(tmp);

		 GetPrivateProfileString(weap.c_str(), "Aimbot.RCSAMT", "0.0", tmp, 32, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.RCSAMT = atof(tmp);

		 GetPrivateProfileString(weap.c_str(), "Aimbot.Speed", "0.0", tmp, 32, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.Speed = atof(tmp);

		 GetPrivateProfileString(weap.c_str(), "Aimbot.FOV", "0.0", tmp, 32, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.FOV = atof(tmp);

		 Vars.Legitbot.Aimbot.VisCheck = GetPrivateProfileInt(weap.c_str(), "Aimbot.VisCheck", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.Hitbox = GetPrivateProfileInt(weap.c_str(), "Aimbot.Hitbox", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.AlwaysOn = GetPrivateProfileInt(weap.c_str(), "Aimbot.AlwaysOn", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.FriendlyFire = GetPrivateProfileInt(weap.c_str(), "Aimbot.FriendlyFire", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.Faceitmode = GetPrivateProfileInt(weap.c_str(), "Aimbot.Faceitmode", 0, "C:\\settings.ini");
		 Vars.Legitbot.Aimbot.Smokecheck = GetPrivateProfileInt(weap.c_str(), "Aimbot.Smokecheck", 0, "C:\\settings.ini");

	 }

	

}
class CFixMove
{
public:
	void Start();
	void End();
private:
	float m_oldforward, m_oldsidemove;
	QAngle m_oldangle;
};
void CLegitBot::Run()
{
	CFixMove fixMove;
	fixMove.Start();
	DropTarget();
	_JUNK_BLOCK(jmp_label4)
	if (Vars.Legitbot.Aimbot.Weaponcfg)
	{
		std::string strWeaponName = G::LocalPlayer->GetWeapon()->GetWeaponName();
		ReadSettings(strWeaponName);
	}

	static float oldServerTime = (float)G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick;
	float serverTime = (float)G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick;
	deltaTime = serverTime - oldServerTime;
	oldServerTime = serverTime;

	if (!G::LocalPlayer->GetWeapon()->IsGun() || G::LocalPlayer->GetWeapon()->IsEmpty() || G::LocalPlayer->GetWeapon()->IsReloading())
		return;

	if ((G::PressedKeys[Vars.Legitbot.Triggerbot.Key] || Vars.Legitbot.Triggerbot.AutoFire) && Vars.Legitbot.Triggerbot.Enabled)
		Triggerbot();

	if ((!(G::UserCmd->buttons & IN_ATTACK) || m_ibesttargetlegit == -1) && Vars.Legitbot.Aimbot.Enabled)
		FindTarget();

	if (m_ibesttargetlegit != -1 && (Vars.Legitbot.Aimbot.AlwaysOn) && !Vars.Legitbot.Aimbot.Faceitmode || (!Vars.Legitbot.Aimbot.Faceitmode) && (Vars.Legitbot.Aimbot.OnKey && G::PressedKeys[Vars.Legitbot.Aimbot.Key]))
		GoToTarget();

	if (Vars.Legitbot.Aimbot.Faceitmode && (m_ibesttargetlegit != -1 && (Vars.Legitbot.Aimbot.AlwaysOn) || (Vars.Legitbot.Aimbot.OnKey && G::PressedKeys[Vars.Legitbot.Aimbot.Key])))
		GoToTargetMouseEvent();


	if (!Vars.Visuals.Removals.VisualRecoil && Vars.Legitbot.Aimbot.RCS && Vars.Legitbot.Aimbot.Enabled)
		RCS();

	if (Vars.Visuals.Removals.VisualRecoil && Vars.Legitbot.Aimbot.RCS && Vars.Legitbot.Aimbot.Enabled)
	{
		G::UserCmd->viewangles -= G::LocalPlayer->GetPunch() * (Vars.Legitbot.Aimbot.RCSAMT / 50.f);
	}

	if (Vars.Legitbot.Aimbot.legitaa)
		legitaa();
	fixMove.End();



	if (Vars.Legitbot.Aimbot.Fastzoom)
	{
		if (G::UserCmd->buttons & IN_ATTACK)
		{
			CBaseEntity* pWeapon = reinterpret_cast<CBaseEntity*>(G::LocalPlayer->GetWeapon());
			ClientClass* pWeaponClass = pWeapon->GetClientClass();
			if (pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponAWP) ||
				pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponSSG08) ||
				pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponSCAR20) ||
				pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponG3SG1))
			{

				if (!G::LocalPlayer->IsScoped())
				{
					G::UserCmd->buttons &= ~IN_ATTACK;
					G::UserCmd->buttons |= IN_ZOOM;
				}
			}
		}
	}
	CBaseEntity* pWeapon = reinterpret_cast<CBaseEntity*>(G::LocalPlayer->GetWeapon());
	ClientClass* pWeaponClass = pWeapon->GetClientClass();
	if ((G::UserCmd->buttons & IN_ATTACK) && Vars.Legitbot.Aimbot.FastzoomSwitch && (pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponAWP) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponSSG08)))
	{
		I::Engine->ExecuteClientCmd("lastinv");
	}
}


				
		

void CLegitBot::FindTarget()
{
	m_fbestfov = Vars.Legitbot.Aimbot.FOV;

	for (int i = 0; i <= I::Globals->maxClients; i++)
	{
		if (!EntityIsValid(i))
			continue;

		CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);
		_JUNK_BLOCK(jmp_label5)
		if (!Entity)
			continue;


		//QAngle viewangles = G::UserCmd->viewangles + G::LocalPlayer->GetPunch() * 2.f;
		QAngle AimPunch = G::LocalPlayer->GetPunch();

			QAngle punchAngles = G::LocalPlayer->GetPunch() * 2.f;

		Vector hitboxPos = this->GetHitboxPosition(bestHitboxTarget, Entity);

		if (Vars.Legitbot.Aimbot.Smokecheck)
		{
			typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);

			static uint32_t GoesThroughSmokeOffset = (uint32_t)U::FindPattern(strenc("client.dll"), ("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
			static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

			Vector ang;
			ang[0] = G::LocalPlayer->GetEyePosition().x;
			ang[1] = G::LocalPlayer->GetEyePosition().y;
			ang[2] = G::LocalPlayer->GetEyePosition().z;

			if (GoesThroughSmokeFunction(ang, hitboxPos))
				continue;
		}
		float fov = M::GetFov(G::UserCmd->viewangles, M::CalcAngle(G::LocalPlayer->GetEyePosition(), hitboxPos) - punchAngles, G::LocalPlayer->GetEyePosition().Dist(hitboxPos));
		if (fov < m_fbestfov)
		{
			m_fbestfov = fov;
			m_ibesttargetlegit = i;
		}
	}
}

void CLegitBot::GoToTargetMouseEvent()//P Faceit profenz
{
	CBaseEntity* Entity = I::ClientEntList->GetClientEntity(m_ibesttargetlegit);
	_JUNK_BLOCK(jmp_label6)
	if (!Entity)
		return;

	Vector predicted = Entity->GetPredicted(this->GetHitboxPosition(bestHitboxTarget, Entity));

	QAngle dst = M::CalcAngle(G::LocalPlayer->GetEyePosition(), predicted);
	QAngle src = G::UserCmd->viewangles;
		dst -= G::LocalPlayer->GetPunch() * (Vars.Legitbot.Aimbot.RCSAmount / 50.f);

		QAngle delta = dst - src;

		delta.Clamp();
		if (!Vars.Legitbot.Aimbot.MaxSpeed)
			if (!delta.IsZero())
			{
				float finalTime = delta.Length() / (Vars.Legitbot.Aimbot.Speed / 10);

				curAimTime += deltaTime;

				if (curAimTime > finalTime)
					curAimTime = finalTime;

				float percent = curAimTime / finalTime;

				delta *= percent;
			}
	QAngle pixels = delta.Clamp() / (0.022f * 1.21 * 1);   //1,21 mouse sens ingame
	
	mouse_event(MOUSEEVENTF_MOVE, -pixels.y, pixels.x, NULL, NULL);
	
}

void CLegitBot::GoToTarget()
{
	auto pWeapon = G::LocalPlayer->GetWeapon();
	auto iClip = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pWeapon) + offsets.m_iClip1);
	if (!(iClip > 0)) return;

	CBaseEntity* Entity = I::ClientEntList->GetClientEntity(m_ibesttargetlegit);

	if (!Entity)
		return;

	Vector predicted = Entity->GetPredicted(this->GetHitboxPosition(bestHitboxTarget, Entity));
	QAngle dst = M::CalcAngle(G::LocalPlayer->GetEyePosition(), predicted);
	QAngle src = G::UserCmd->viewangles;
	dst -= G::LocalPlayer->GetPunch() * (Vars.Legitbot.Aimbot.RCSAmount / 50.f);

	QAngle delta = dst - src;

	delta.Clamp();
	_JUNK_BLOCK(jmp_label7)
	if(!Vars.Legitbot.Aimbot.Silent)
	if (!delta.IsZero())
	{
		float finalTime = delta.Length() / (Vars.Legitbot.Aimbot.Speed /10);

		curAimTime += deltaTime;

		if (curAimTime > finalTime)
			curAimTime = finalTime;

		float percent = curAimTime / finalTime;

		delta *= percent;
		dst = src + delta;
	}

	bool can_shoot = true;

	float flServerTime = (float)G::LocalPlayer->GetTickBase() *  I::Globals->interval_per_tick;
	float flNextPrimaryAttack = G::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();
	if (flNextPrimaryAttack > flServerTime)
		can_shoot = false;

	if (Vars.Legitbot.Aimbot.Silent)
	{
		if (!can_shoot)
			return;
	}

	G::UserCmd->viewangles = dst.Clamp();
}

void CLegitBot::DropTarget()
{
	_JUNK_BLOCK(jmp_label8)
	if (!EntityIsValid(m_ibesttargetlegit))
	{
		m_ibesttargetlegit = -1;
		curAimTime = 0.f;
	}

}

 Vector  CLegitBot::GetHitboxPosition(int Hitbox, CBaseEntity* ent)
{
	 _JUNK_BLOCK(jmp_label9)
	if (!ent)
		return Vector(0, 0, 0);

	const model_t* model = ent->GetModel();
	if (!model)
		return Vector(0, 0, 0);

	studiohdr_t* hdr = I::ModelInfo->GetStudioModel(model);
	if (!hdr)
		return Vector(0, 0, 0);

	matrix3x4a_t matrix[MAXSTUDIOBONES];
	if (!ent->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, I::Engine->GetLastTimeStamp()))
		return Vector(0, 0, 0);

	mstudiohitboxset_t *set = hdr->pHitboxSet(ent->GetHitboxSet());
	if (!set)
		return Vector(0, 0, 0);

	mstudiobbox_t* box = set->pHitbox(Hitbox);

	if (!box)
		return Vector(0, 0, 0);

	Vector center = ((box->bbmin + box->bbmax) * .5f);
	Vector hitboxpos;
	M::VectorTransform(center, matrix[box->bone], hitboxpos);

	return hitboxpos;
}


bool CLegitBot::EntityIsValid(int i)
{
	CBaseEntity* pEntity = I::ClientEntList->GetClientEntity(i);
	_JUNK_BLOCK(jmp_label10)
	if (!pEntity)
		return false;
	if (pEntity == G::LocalPlayer)
		return false;
	if (!pEntity->IsPlayer())
		return false;
	if (!pEntity->GetAlive())
		return false;
	if (pEntity->GetImmune())
		return false;
	if (pEntity->GetDormant())
		return false;
	if (pEntity->GetTeam() == G::LocalPlayer->GetTeam() && !Vars.Legitbot.Aimbot.FriendlyFire)
		return false;

	bool visible = false;

	for (int i = 19; i >= 0; i--)
	{
		if (pEntity->IsVisible(this->GetHitboxPosition(i, pEntity)))
		{
			if (i == Vars.Legitbot.Aimbot.Hitbox)
			{
				visible = true;
				bestHitboxTarget = i;
				break;
			}
			visible = true;
			bestHitboxTarget = i;
		}
	}

	if (!visible)
		return false;

	QAngle punchAngles = G::LocalPlayer->GetPunch() * 2.f;

	Vector hitboxPos = this->GetHitboxPosition(bestHitboxTarget, pEntity);

	if (M::GetFov(G::UserCmd->viewangles, M::CalcAngle(G::LocalPlayer->GetEyePosition(), hitboxPos) - punchAngles, G::LocalPlayer->GetEyePosition().Dist(hitboxPos)) > Vars.Legitbot.Aimbot.FOV)
		return false;

	return true;
}

void CLegitBot::Triggerbot()
{
	CBaseEntity* localplayer = G::LocalPlayer;
	if (!localplayer || !localplayer->GetAlive())
		return;
	_JUNK_BLOCK(jmp_label11)
	if (!localplayer->GetWeapon()->IsGun())
		return;

	Vector traceStart, traceEnd;
	trace_t tr;

	QAngle viewAngles;
	I::Engine->GetViewAngles(viewAngles);
	QAngle viewAngles_rcs = viewAngles + localplayer->GetPunch() * 2.0f;

	M::AngleVectors(viewAngles_rcs, &traceEnd);

	traceStart = localplayer->GetEyePosition();
	traceEnd = traceStart + (traceEnd * 8192.0f);

	Ray_t ray;
	ray.Init(traceStart, traceEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	I::EngineTrace->TraceRay(ray, 0x46004003, &traceFilter, &tr);

	CBaseEntity* player = tr.m_pEnt;

	if (!tr.m_pEnt)
		return;

	int hitgroup = tr.hitgroup;
	bool didHit = false;

	if (Vars.Legitbot.Triggerbot.Filter.Head && hitgroup == HITGROUP_HEAD)
		didHit = true;
	if (Vars.Legitbot.Triggerbot.Filter.Chest && hitgroup == HITGROUP_CHEST)
		didHit = true;
	if (Vars.Legitbot.Triggerbot.Filter.Stomach && hitgroup == HITGROUP_STOMACH)
		didHit = true;
	if (Vars.Legitbot.Triggerbot.Filter.Arms && (hitgroup == HITGROUP_LEFTARM || hitgroup == HITGROUP_RIGHTARM))
		didHit = true;
	if (Vars.Legitbot.Triggerbot.Filter.Legs && (hitgroup == HITGROUP_LEFTLEG || hitgroup == HITGROUP_RIGHTLEG))
		didHit = true;


	Vector hitboxPos = this->GetHitboxPosition(bestHitboxTarget, tr.m_pEnt);

	typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);
	if (Vars.Legitbot.Aimbot.Smokecheck)
	{
		static uint32_t GoesThroughSmokeOffset = (uint32_t)U::FindPattern(strenc("client.dll"), ("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F"));
		static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

		Vector ang;
		ang[0] = G::LocalPlayer->GetEyePosition().x;
		ang[1] = G::LocalPlayer->GetEyePosition().y;
		ang[2] = G::LocalPlayer->GetEyePosition().z;

		if (GoesThroughSmokeFunction(ang, hitboxPos))
			return;
	}
	if ((Vars.Legitbot.Triggerbot.Filter.Friendly || tr.m_pEnt->GetTeam() != G::LocalPlayer->GetTeam()) && tr.m_pEnt->GetHealth() > 0 && !tr.m_pEnt->GetImmune() && didHit)
	{
		auto flSpread = G::LocalPlayer->GetWeapon()->GetInaccuracy();
		float hitchance = Vars.Legitbot.Triggerbot.HitChanceAmt / 1000.f >= flSpread;
		if (didHit && (!Vars.Legitbot.Triggerbot.HitChance || (hitchance >= flSpread)))
			G::UserCmd->buttons |= IN_ATTACK;
	}
} 

QAngle m_oldangle;

void CLegitBot::RCS()
{
	_JUNK_BLOCK(jmp_label12)
	if (G::UserCmd->buttons & IN_ATTACK && G::LocalPlayer->GetShotsFired() >= 2)
	{
		QAngle aimpunch = G::LocalPlayer->GetPunch() * (Vars.Legitbot.Aimbot.RCSAMT / 50.f);
		G::UserCmd->viewangles += (m_oldangle - aimpunch);

		m_oldangle = aimpunch;

		G::UserCmd->viewangles.Normalize();
	}
	else 
	{
		m_oldangle.x = m_oldangle.y = m_oldangle.z = 0;
		G::UserCmd->viewangles.Normalize();
	}
}

void CLegitBot::legitaa()
{
	_JUNK_BLOCK(jmp_label13)
	if (G::LocalPlayer->GetMoveType() == MOVETYPE_LADDER || G::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (G::UserCmd->buttons & IN_ATTACK || G::UserCmd->buttons & IN_USE)
		return;

	CBaseEntity* pWeapon = reinterpret_cast<CBaseEntity*>(G::LocalPlayer->GetWeapon());
	ClientClass* pWeaponClass = pWeapon->GetClientClass();
	if (pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CHEGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CFlashbang) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CSmokeGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CDecoyGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CIncendiaryGrenade) ||
		pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CMolotovGrenade))
		return;

	static bool yFake = false;
	static bool yFlip = true;
	QAngle oldAngle = G::UserCmd->viewangles;
	float oldForward = G::UserCmd->forwardmove;
	float oldSide = G::UserCmd->sidemove;
	if (!yFake)
	{
		G::SendPacket = false;
		if (yFlip)
		{
			G::UserCmd->viewangles.y += 90.f;
			yFlip = false;
		}
		else
		{
			G::UserCmd->viewangles.y -= 90.f;
			yFlip = true;
		}
		yFake = true;
	}
	else
	{
		G::SendPacket= true;
		yFake = false;
	}
}




namespace LegitBacktracking
{
	std::vector<BacktrackingRecord> PlayerRecords[64];


	Vector GetHitboxPosition(int Hitbox, matrix3x4a_t* Matrix, CBaseEntity* ent)
	{
		if (!ent)
			return Vector(0, 0, 0);

		const model_t* model = ent->GetModel();
		if (!model)
			return Vector(0, 0, 0);
		_JUNK_BLOCK(jmp_label14)
		studiohdr_t* hdr = I::ModelInfo->GetStudioModel(model);
		if (!hdr)
			return Vector(0, 0, 0);

		mstudiohitboxset_t *set = hdr->pHitboxSet(ent->GetHitboxSet());
		if (!set)
			return Vector(0, 0, 0);

		mstudiobbox_t* box = set->pHitbox(Hitbox);

		if (!box)
			return Vector(0, 0, 0);

		Vector center = ((box->bbmin + box->bbmax) * .5f);
		Vector hitboxpos;
		M::VectorTransform(center, Matrix[box->bone], hitboxpos);

		return hitboxpos;
	}

	void CM(void)
	{

		float flBestFov = FLT_MAX;
		int   iBestTarget = -1;

		for(int x = 0; x < 64; x++)
		{

			CBaseEntity* Enemy = I::ClientEntList->GetClientEntity(x);

			if (!Enemy)
				continue;
			if (Enemy == G::LocalPlayer)
				continue;
			if (!Enemy->IsPlayer())
				continue;
			if (!Enemy->GetAlive())
				continue;
			if (Enemy->GetImmune())
				continue;
			if (Enemy->GetDormant())
				continue;
			if (Enemy->GetTeam() == G::LocalPlayer->GetTeam())
				continue;

			int iIndex = Enemy->GetIndex();

			while (true)
			{
				if (PlayerRecords[iIndex].size() > static_cast<size_t>(Vars.Legitbot.Aimbot.Ticks))
				{
					PlayerRecords[iIndex].pop_back();
				}
				else
				{
					break;
				}
			}
			_JUNK_BLOCK(jmp_label15)
			if (!PlayerRecords[iIndex].empty())
			{
				if (PlayerRecords[iIndex].front().Tick == G::UserCmd->tick_count)
					continue;
			}

			matrix3x4a_t Matrix[128];
			if (!Enemy->SetupBones(Matrix, 128, 256, 0))
				continue;

			Vector vPoint;
	
			vPoint = GetHitboxPosition(0, Matrix, Enemy);

			BacktrackingRecord CurRecord = BacktrackingRecord(G::UserCmd->tick_count, vPoint, Matrix);
			PlayerRecords[iIndex].insert(PlayerRecords[iIndex].begin(), CurRecord);

			QAngle CalcAngled = M::CalcAngle(G::LocalPlayer->GetEyePosition(), vPoint);
			CalcAngled -= G::LocalPlayer->GetPunch() * 2.f;


			float fov = M::GetFov(G::UserCmd->viewangles, CalcAngled, 0.0f);
			if (fov < flBestFov)
			{
				flBestFov = fov;
				iBestTarget = Enemy->GetIndex();
			}
		}

		CBaseCombatWeapon* activeWeapon = G::LocalPlayer->GetWeapon();
		if (!activeWeapon)
			return;

		float flServerTime = (float)G::LocalPlayer->GetTickBase() *  I::Globals->interval_per_tick;
		float flNextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();
		if (flNextPrimaryAttack > flServerTime)
			return;

		if (!(G::UserCmd->buttons & IN_ATTACK))
			return;

		//Get best Point to backtrack
		if (iBestTarget != -1)
		{
			float Temp = FLT_MAX;
			for (auto tick : PlayerRecords[iBestTarget])
			{
				QAngle CalcAngled = M::CalcAngle(G::LocalPlayer->GetEyePosition(), tick.Position);
				CalcAngled -= G::LocalPlayer->GetPunch()  * (Vars.Legitbot.Aimbot.RCSAMT / 50.f);


				float fov = M::GetFov(G::UserCmd->viewangles, CalcAngled,0.0f);
				if (fov < Temp)
				{
					Temp = fov;
					G::UserCmd->tick_count = tick.Tick;
				}
			}
		}
	}

	void PT(void)
	{
		for (int x = 0; x < 64;x++)
		{
			CBaseEntity* Enemy = I::ClientEntList->GetClientEntity(x);

			if (PlayerRecords[x].empty() || !Enemy)
				continue;

			studiohdr_t* pStudioModel = I::ModelInfo->GetStudioModel(Enemy->GetModel());
			if (!pStudioModel)
				continue;

			if (!G::LocalPlayer->GetAlive())
				continue;

			if (!Enemy)
				continue;
			if (Enemy == G::LocalPlayer)
				continue;
			if (!Enemy->IsPlayer())
				continue;
			if (!Enemy->GetAlive())
				continue;
			if (Enemy->GetImmune())
				continue;
			if (Enemy->GetDormant())
				continue;
			if (Enemy->GetTeam() == G::LocalPlayer->GetTeam())
				continue;
			_JUNK_BLOCK(jmp_label16)
			for (auto tick : PlayerRecords[x])
			{
				for (int i = 0; i < pStudioModel->numbones; i++)
				{
					mstudiobone_t* pBone = pStudioModel->pBone(i);
					if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
						continue;

					Vector vBonePos1;
					if (!D::WorldToScreen(Vector(tick.Matrix[i][0][3], tick.Matrix[i][1][3], tick.Matrix[i][2][3]), vBonePos1))
						continue;

					Vector vBonePos2;
					if (!D::WorldToScreen(Vector(tick.Matrix[pBone->parent][0][3], tick.Matrix[pBone->parent][1][3], tick.Matrix[pBone->parent][2][3]), vBonePos2))
						continue;
					if(G::LocalPlayer->GetAlive())
					D::DrawLine((int)vBonePos1.x, (int)vBonePos1.y, (int)vBonePos2.x, (int)vBonePos2.y, Color(250,250,250,12));
				}
			}
		}
	}

	void FN(void)
	{

	}
}