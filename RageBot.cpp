#include "Cheat.h"
#define TIME_TO_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / I::Globals->interval_per_tick ) )
#define JUNKS \
__asm _emit 0x19 \
__asm _emit 0x63 \
__asm _emit 0x20 \
__asm _emit 0x32 \
__asm _emit 0x52 \
__asm _emit 0x51 \
__asm _emit 0x68 \
__asm _emit 0x10 \
__asm _emit 0x97 \
__asm _emit 0x63 \
// Don't change this!
#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:

std::string GetWeapbyIDRage(int id)
{
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

std::string WeapRage = "++1";

void CRageBot::ChangeSetRage()
{
	std::string weaprage = G::LocalPlayer->GetWeapon()->GetWeaponName();

		if (I::Engine->IsInGame() && G::LocalPlayer->GetAlive())
		{
			WeapRage = "++1";

			WritePrivateProfileString(weaprage.c_str(), "Aimbot.AutoFire", std::to_string(Vars.Ragebot.AutoFire).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.Hold", std::to_string(Vars.Ragebot.Hold).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.HoldKey", std::to_string(Vars.Ragebot.HoldKey).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.Silent", std::to_string(Vars.Ragebot.Silent).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.Hitbox", std::to_string(Vars.Ragebot.Hitbox).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.PreferHitbox", std::to_string(Vars.Ragebot.PreferHitbox).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.AutoStop", std::to_string(Vars.Ragebot.AutoStop).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.AutoScope", std::to_string(Vars.Ragebot.AutoScope).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.AutoRevovler", std::to_string(Vars.Misc.AutoRevovler).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.AutoCrouch", std::to_string(Vars.Ragebot.AutoCrouch).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.AutoWall", std::to_string(Vars.Ragebot.AutoWall).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.AutoWallDmg", std::to_string(Vars.Ragebot.AutoWallDmg).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.SmartHitbox", std::to_string(Vars.Ragebot.SmartHitbox).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.SmartHitboxHealth", std::to_string(Vars.Ragebot.SmartHitboxHealth).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.HitChance", std::to_string(Vars.Ragebot.HitChance).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.FakeLagfix", std::to_string(Vars.Ragebot.FakeLagfix).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.HitChanceAmt", std::to_string(Vars.Ragebot.HitChanceAmt).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.Multipoint", std::to_string(Vars.Ragebot.Multipoint).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.Multipointscale", std::to_string(Vars.Ragebot.Multipointscale).c_str(), "C:\\SettingsRage.ini");
			WritePrivateProfileString(weaprage.c_str(), "Aimbot.Pseudonospread", std::to_string(Vars.Ragebot.Pseudonospread).c_str(), "C:\\SettingsRage.ini");
		}
}

void ReadSettingsRage(std::string weaprage)
{
		if (WeapRage != weaprage)
		{
			WeapRage = weaprage;

			char* tmp = new char[32];

			Vars.Ragebot.AutoFire = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.AutoFire", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.Hold = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.Hold", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.HoldKey = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.HoldKey", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.Silent = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.Silent", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.PreferHitbox = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.PreferHitbox", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.AutoStop = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.AutoStop", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.AutoScope = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.AutoScope", 0, "C:\\SettingsRage.ini");
			Vars.Misc.AutoRevovler = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.AutoRevovler", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.AutoCrouch = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.AutoCrouch", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.AutoWall = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.AutoWall", 0, "C:\\SettingsRage.ini");
			GetPrivateProfileString(weaprage.c_str(), "Aimbot.AutoWallDmg", "0.0", tmp, 32, "C:\\SettingsRage.ini");
			Vars.Ragebot.AutoWallDmg = atof(tmp);
			Vars.Ragebot.SmartHitbox = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.SmartHitbox", 0, "C:\\SettingsRage.ini");
			GetPrivateProfileString(weaprage.c_str(), "Aimbot.SmartHitboxHealth", "0.0", tmp, 32, "C:\\SettingsRage.ini");
			Vars.Ragebot.SmartHitboxHealth = atof(tmp);
			Vars.Ragebot.HitChance = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.HitChance", 0, "C:\\SettingsRage.ini");
			Vars.Ragebot.FakeLagfix = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.FakeLagfix", 0, "C:\\SettingsRage.ini");
			GetPrivateProfileString(weaprage.c_str(), "Aimbot.HitChanceAmt", "0.0", tmp, 32, "C:\\SettingsRage.ini");
			Vars.Ragebot.HitChanceAmt = atof(tmp);
			Vars.Ragebot.Multipoint = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.Multipoint", 0, "C:\\SettingsRage.ini");
			GetPrivateProfileString(weaprage.c_str(), "Aimbot.Multipointscale", "0.0", tmp, 32, "C:\\SettingsRage.ini");
			Vars.Ragebot.Multipointscale = atof(tmp);
			Vars.Ragebot.Pseudonospread = GetPrivateProfileInt(weaprage.c_str(), "Aimbot.Pseudonospread", 0, "C:\\SettingsRage.ini");
		}
}

void CRageBot::Run(CUserCmd *pCmd, bool &bSendPacket)
{
	_JUNK_BLOCK(jmp_label1)
		if (Vars.Ragebot.WeaponCFGRage)
		{
			std::string strWeaponName = G::LocalPlayer->GetWeapon()->GetWeaponName();
			ReadSettingsRage(strWeaponName);
		}
	CFixMove fixMove;
	fixMove.Start();

	if (Vars.Ragebot.Antiaim.Enabled) 
	{
		G::InAntiAim = true;
		AntiAim->Run(pCmd, G::SendPacket);
	}
	else
	{
		G::InAntiAim = false;
	}
	fixMove.End();
	
	G::Aimbotting = false;

	if (Vars.Ragebot.Hold && !G::PressedKeys[Vars.Ragebot.HoldKey]) {
		return;
	}

	if (!G::LocalPlayer->GetWeapon()->IsGun() || G::LocalPlayer->GetWeapon()->IsEmpty()) {
		return;
	}

	if (G::UserCmd->buttons & IN_RELOAD)
		return;

	CBaseEntity* target;

	if (Vars.Ragebot.AutoWall)
		target = FindTarget();
	else
		target = WasFuerAwallFindTarget();

	if (target)
	{
		this->GoToTarget(target);
		G::BestTarget = target->index;
	}

	return;
}

bool CRageBot::GetHitBoxCenter(CBaseEntity* ClientEntity, int iHitBox, Vector* vOut)
{
	_JUNK_BLOCK(jmp_label2)
	Vector vMin, vMax;
	const model_t* model = ClientEntity->GetModel();
	if (!model)
		return false;
	studiohdr_t *pStudioHdr = I::ModelInfo->GetStudioModel(model);
	if (pStudioHdr == NULL)
		return false;
	matrix3x4a_t matrix[MAXSTUDIOBONES];
	if (!ClientEntity->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, meme_resolvenz::get_instance()->ret_last_time(ClientEntity->GetIndex())))
		return false;
	mstudiohitboxset_t *set = pStudioHdr->pHitboxSet(ClientEntity->GetHitboxSet());
	if (!set)
		return false;
	mstudiobbox_t* pbox = set->pHitbox(iHitBox);
	if (!pbox)
		return false;

	//https://www.unknowncheats.me/forum/1450379-post8.html

	Vector eye_position = G::LocalPlayer->GetEyePosition();
	Vector target_position = ClientEntity->GetEyePosition();
	QAngle temp = M::CalcAngle(eye_position, target_position);

	float cs = cos(DEG2RAD(temp.y));
	float sn = sin(DEG2RAD(temp.y));

	float mod1 = pbox->radius != -1.f ? pbox->radius : 0.f;
	Vector mod = { mod1,mod1,mod1 };

	Vector mins;
	M::VectorTransform(pbox->bbmin - mod, matrix[pbox->bone], mins);
	Vector maxs;
	M::VectorTransform(pbox->bbmax + mod, matrix[pbox->bone], maxs);
	Vector center = (mins + maxs) * 0.5f;

	Vector points[6];

	points[0] = Vector(center.x, center.y, center.z); //oben
	points[1] = Vector(center.x, center.y, center.z);//unten
	points[2] = Vector(center.x, center.y, center.z); //left
	points[3] = Vector(center.x, center.y, center.z);//right
	points[4] = Vector(center.x, center.y, center.z);
	//	points[5] = center;

	if (iHitBox == HITBOX_LOWER_NECK || iHitBox == HITBOX_NECK)
	{
		return false;
	}

	float scale = Vars.Ragebot.Multipointscale;
	float scalefeet = 0.70f;//0.80

	if (iHitBox == HITBOX_LEFT_FOOT || iHitBox == HITBOX_RIGHT_FOOT)
	{
		//rotate = false;
		points[2] = Vector(center.x + (pbox->radius * 2), center.y, center.z); //left
		points[3] = Vector(center.x + (pbox->radius * 2), center.y, center.z);//right
	}
	else {
		points[0] = Vector(center.x, center.y, center.z + pbox->radius * (scalefeet + 0.15)); //oben
		points[1] = Vector(center.x, center.y, center.z - pbox->radius * scalefeet);//unten
	}

	for (int index = 0; index <= 6; ++index)
	{


		if (index == 2)
		{
			points[index].x += cs + (pbox->radius * scale) * sn;
			points[index].y += sn - (pbox->radius * scale) * cs;
		}
		else if (index == 3)
		{
			points[index].x += cs - (pbox->radius * scale) * sn;
			points[index].y += sn + (pbox->radius * scale) * cs;
		}

		vOut[index] = points[index];


		if (Vars.Visuals.DrawMultipints)
		{
			Vector vBonePos1;

			if (D::WorldToScreen(vOut[index], vBonePos1))
				D::DrawRect(vBonePos1.x, vBonePos1.y, 4, 4, Color(255, 255, 255));


		}
	}

	return true;


}
//
//float LagFix()
//{
//	float updaterate = I::Cvar->FindVar("cl_updaterate")->fValue;
//	ConVar* minupdate = I::Cvar->FindVar("sv_minupdaterate");
//	ConVar* maxupdate = I::Cvar->FindVar("sv_maxupdaterate");
//
//	if (minupdate && maxupdate)
//		updaterate = maxupdate->fValue;
//
//	float ratio = I::Cvar->FindVar("cl_interp_ratio")->fValue;
//
//	if (ratio == 0)
//		ratio = 1.0f;
//
//	float lerp = I::Cvar->FindVar("cl_interp")->fValue;
//	ConVar* cmin = I::Cvar->FindVar("sv_client_min_interp_ratio");
//	ConVar* cmax = I::Cvar->FindVar("sv_client_max_interp_ratio");
//
//	if (cmin && cmax && cmin->fValue != 1)
//		ratio = U::Clamp(ratio, cmin->fValue, cmax->fValue);
//
//	return max(lerp, ratio / updaterate);
//}

//bool CRageBot::GetHitBoxCenter(CBaseEntity* ClientEntity, int iHitBox, Vector* vOut)
//{
//	Vector vMin, vMax;
//	const model_t* model = ClientEntity->GetModel();
//	if (!model)
//		return false;
//	studiohdr_t *pStudioHdr = I::ModelInfo->GetStudioModel(model);
//	if (pStudioHdr == NULL)
//		return false;
//	matrix3x4a_t matrix[MAXSTUDIOBONES];
//	if (!ClientEntity->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
//		return false;
//	mstudiohitboxset_t *set = pStudioHdr->pHitboxSet(ClientEntity->GetHitboxSet());
//	if (!set)
//		return false;
//	mstudiobbox_t* pbox = set->pHitbox(iHitBox);
//	if (!pbox)
//		return false;
//	auto mod = pbox->radius != -1.f ? pbox->radius : 0.f;
//
//	Vector Rad;
//	Rad[0] = pbox->radius;
//	Rad[1] = pbox->radius;
//	Rad[2] = pbox->radius;
//
//	Vector Center = (pbox->bbmin + pbox->bbmax) * .5f;
//
//	Vector vBonePos1;
//	Vector points[9];
//
//	Rad.x = Rad.x * 0.95;
//
//	if (iHitBox == HITBOX_NECK || iHitBox == HITBOX_LOWER_NECK)
//		return false;
//
//
//	if (iHitBox == HITBOX_HEAD)
//	{
//		points[0] = Center;
//		points[0].x -= Rad.x  * 0.25; //links unten
//
//		points[1] = Center;
//		points[1].x += Rad.x;//links oben
//
//		points[2] = Center;
//		points[2].x -= Rad.x * 0.25; //rechts unten
//
//		points[3] = Center;
//		points[3].x += Rad.x; //rechts oben
//
//		points[4] = Center;
//		points[4].x += Rad.x * 1.9; //hoch
//
//		points[5] = Center;
//		points[5].x -= Rad.x * 0.65;//runter 
//	}
//	else if (iHitBox == HITBOX_LEFT_FOOT || iHitBox == HITBOX_RIGHT_FOOT)
//	{
//		points[0] = Center;
//		points[0].x -= Rad.x  * 0.25; //links unten
//
//		points[1] = Center;
//		points[1].x += Rad.x;//links oben
//
//		points[2] = Center;
//		points[2].x -= Rad.x * 0.25; //rechts unten
//
//		points[3] = Center;
//		points[3].x += Rad.x; //rechts oben
//
//		points[4] = Center;
//		points[4].x += Rad.x * 1.9; //hoch
//
//		points[5] = Center;
//		points[5].x -= Rad.x * 1.9;//runter 
//	}
//	else {
//		points[0] = Center;
//		points[0].x -= Rad.x  * 0.25; //links unten
//
//		points[1] = Center;
//		points[1].x += Rad.x;//links oben
//
//		points[2] = Center;
//		points[2].x -= Rad.x * 0.25; //rechts unten
//
//		points[3] = Center;
//		points[3].x += Rad.x; //rechts oben
//
//		points[4] = Center;
//		points[4].x += Rad.x * 1.9; //hoch
//
//		points[5] = Center;
//		points[5].x -= Rad.x * 1.9;//runter 
//	}
//
//
//	for (int index = 0; index <= 6; ++index)
//	{
//		if (index != 0)
//		{
//			points[index] = ((((points[index] + points[0]) * .5f) + points[index]) * .5f);
//		}
//		M::VectorTransform(points[index], matrix[pbox->bone], vOut[index]);
//
//
//	}
//
//
//	Vector eye_position = G::LocalPlayer->GetEyePosition();
//	Vector target_position = ClientEntity->GetEyePosition();
//
//	QAngle temp = M::CalcAngle(eye_position, target_position);
//
//	for (int index = 0; index <= 6; ++index)
//	{
//
//		float cs = cos(DEG2RAD(temp.y));
//		float sn = sin(DEG2RAD(temp.y));
//
//		float fx;
//		float fy;
//
//		bool waw = false;
//
//		fx = vOut[index].x - vOut[index].x; // x = 50 - 50 egal ging ent ohne
//		fy = vOut[index].y - vOut[index].y;
//
//		if (index == 4 || index == 5)
//			waw = true;
//
//		if (!waw)
//		{
//			fy += Rad.x * 0.90;
//			fx += Rad.x * 0.90;
//		}
//
//
//		waw = false;
//
//		float result_x;
//		float result_y;
//
//		if (index == 2 || index == 3)
//			waw = true;
//
//		if (!waw)
//		{//links
//			result_x = fx  * cs - fy  * sn;
//			result_y = fx  * sn + fy  * cs;//
//		}
//		else
//		{//rechts
//			result_x = fx  * cs + fy  * sn;//
//			result_y = fx  * sn - fy  * cs;//
//		}
//
//		result_x += vOut[index].x;
//		result_y += vOut[index].y;
//
//		vOut[index].x = result_x;
//		vOut[index].y = result_y;
//
//		if (D::WorldToScreen(vOut[index], vBonePos1))
//			if (Vars.Visuals.DrawMultipints)
//			{
//				D::DrawRect(vBonePos1.x, vBonePos1.y, 4, 4, Color(255, 255, 255));
//			}
//	}
//
//	return true;
//}

//bool  CRageBot::GetMultiPointHitboxPosition(CBaseEntity* ClientEntity, int iHitBox, Vector* vOut)//corner stuff stolen from kiro
//{
////	matrix3x4_t pmatrix[128];
//
//	Vector vMin, vMax;
//
//	const model_t* model = ClientEntity->GetModel();
//
//	if (!model)
//		return false;
//
//	studiohdr_t *pStudioHdr = I::ModelInfo->GetStudioModel(model);
//
//	if (pStudioHdr == NULL)
//		return false;
//
//	//if (!ClientEntity->SetupBones(pmatrix, 128, 0x100, 0))
//	//	return false;
//
//	matrix3x4a_t matrix[MAXSTUDIOBONES];
//	if (!ClientEntity->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
//		return false;
//
//	mstudiohitboxset_t *set = pStudioHdr->pHitboxSet(ClientEntity->GetHitboxSet());
//
//	if (!set)
//		return false;
//
//	mstudiobbox_t* pbox = set->pHitbox(iHitBox);
//
//	if (!pbox)
//		return false;
//
//	// center and all the points of the hitbox
//	Vector points[9] = { ((pbox->bbmin + pbox->bbmax) * 0.5f), // center
//		Vector(pbox->bbmin.x, pbox->bbmin.y, pbox->bbmin.z), // left bottom back corner
//		Vector(pbox->bbmin.x, pbox->bbmax.y, pbox->bbmin.z), // left bottom front corner
//		Vector(pbox->bbmax.x, pbox->bbmax.y, pbox->bbmin.z), // left top front corner
//		Vector(pbox->bbmax.x, pbox->bbmin.y, pbox->bbmin.z), // left top back corner
//		Vector(pbox->bbmax.x, pbox->bbmax.y, pbox->bbmax.z), // right top front corner
//		Vector(pbox->bbmin.x, pbox->bbmax.y, pbox->bbmax.z), // right bottom front corner
//		Vector(pbox->bbmin.x, pbox->bbmin.y, pbox->bbmax.z), // right bottom back corner
//		Vector(pbox->bbmax.x, pbox->bbmin.y, pbox->bbmax.z)  // right top back corner
//	};
//
//	for (int index = 0; index <= 8; ++index)
//	{
//		if (index != 0)
//		{
//			// scale down the hitbox size
//			points[index] = ((((points[index] + points[0]) * .5f) + points[index]) * .5f);
//		}
//
//		// transform the vector
//		M::VectorTransform(points[index], matrix[pbox->bone], vOut[index]);
//
//	}
//
//	return true;
//}


Vector CRageBot::GetHitboxPosition(int Hitbox, CBaseEntity* ent)
{
	_JUNK_BLOCK(jmp_label3)
	if (!ent)
		return Vector(0, 0, 0);

	const model_t* model = ent->GetModel();
	if (!model)
		return Vector(0, 0, 0);

	studiohdr_t* hdr = I::ModelInfo->GetStudioModel(model);
	if (!hdr)
		return Vector(0, 0, 0);

	matrix3x4a_t matrix[MAXSTUDIOBONES];
	if (!ent->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, meme_resolvenz::get_instance()->ret_last_time(ent->GetIndex())))
		return Vector(0, 0, 0);

	mstudiohitboxset_t *set = hdr->pHitboxSet(ent->GetHitboxSet());
	if (!set)
		return Vector(0, 0, 0);

	mstudiobbox_t* box = set->pHitbox(Hitbox);

	if (!box)
		return Vector(0, 0, 0);

	Vector points[] = { ((box->bbmin + box->bbmax) * .5f),
		Vector(box->bbmin.x, box->bbmax.y, box->bbmin.z),
		Vector(box->bbmin.x, box->bbmax.y, box->bbmin.z),
		Vector(box->bbmax.x, box->bbmax.y, box->bbmin.z),
		Vector(box->bbmax.x, box->bbmin.y, box->bbmin.z),
		Vector(box->bbmax.x, box->bbmax.y, box->bbmax.z),
		Vector(box->bbmin.x, box->bbmax.y, box->bbmax.z),
		Vector(box->bbmin.x, box->bbmin.y, box->bbmax.z),
		Vector(box->bbmax.x, box->bbmin.y, box->bbmax.z) };



	

	Vector center = ((box->bbmin + box->bbmax) * .5f);
	Vector hitboxpos;
	M::VectorTransform(center, matrix[box->bone], hitboxpos);
	

	return hitboxpos;
}
//
//bool elefix(bool prot)
//{
//	static bool bfirstime = false;
//
//	if (!bfirstime)
//	{
//		bfirstime = !bfirstime;
//		DWORD flold;
//		VirtualProtect((void*)0x1019DBDC, 6, PAGE_READWRITE, &flold);
//		for (int lo = 0; lo < 5; lo++)
//		{
//			*(byte*)(0x1019DBDC + lo) = 0xE8;
//		}
//		VirtualProtect((void*)0x1019DBDC, 6, flold, &flold);
//	}
//	return false;
//}

CBaseEntity* CRageBot::FindTarget()
{
	_JUNK_BLOCK(jmp_label4)
	float flDistance = 8192.f;

	CBaseEntity* bestTarget = NULL;

	float bestDamage = 0.f;

	for (int i = 0; i <= I::Globals->maxClients; i++)
	{
		CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);
		player_info_t pInfo;
		I::Engine->GetPlayerInfo(i, &pInfo);

		if (!Entity)
			continue;

		if (Entity == G::LocalPlayer)
			continue;

		if (Entity->GetDormant())
			continue;

		if (!Entity->IsPlayer())
			continue;

		if (!Entity->GetAlive())
			continue;

		if (!strcmp(pInfo.guid, "STEAM_0:1:181981776"))
			return false;

		if (!Vars.Ragebot.FriendlyFire)
		{
			if (G::LocalPlayer->GetTeam() == Entity->GetTeam())
				continue;
		}	
		
		if (Entity->GetImmune())
			continue;


		//pvs fix
		int* array = reinterpret_cast<int*>(offsets.m_dwOcclusionArray);
		*(int*)((uintptr_t)Entity + offsets.m_nWritableBones) = 0;
		*(int*)((uintptr_t)Entity + offsets.m_bDidCheckForOcclusion) = array[1];


		float dist = G::LocalPlayer->GetEyePosition().Dist(Entity->GetOrigin());

		
		if (!Vars.Ragebot.HitScanPerformance)
		{
			Vector hitboxPos = this->GetHitboxPosition(Vars.Ragebot.Hitbox, Entity);
			float temp_damage = AutoWall->GetDamage2(hitboxPos,Entity);



			if (temp_damage >= bestDamage && temp_damage >= Vars.Ragebot.AutoWallDmg )
			{
				bestDamage = temp_damage;
				bestTarget = Entity;
				this->hitboxID = Vars.Ragebot.Hitbox;
			}

			continue;
		}

		//Hitscan
		for (int i = Hitboxes::HITBOX_LEFT_FOREARM; i >= Hitboxes::HITBOX_HEAD; i--)
		{
			Vector hitboxPos[9];

			if (Vars.Ragebot.Multipoint)
			{
					if (!GetHitBoxCenter(Entity, i, hitboxPos))
						continue;
			}
			else 
			{
				 hitboxPos[0] = this->GetHitboxPosition(i, Entity);

			}

			/*Vector hitboxPos = this->GetHitboxPosition(i, Entity);*/

			if (Vars.Ragebot.Multipoint)
			{

				if (i == Vars.Ragebot.Hitbox && Vars.Ragebot.PreferHitbox)
				{
					float temp_damage = AutoWall->GetDamage2(hitboxPos[i], Entity);

					if (temp_damage >= Vars.Ragebot.AutoWallDmg && temp_damage)
					{
						bestDamage = temp_damage;
						bestTarget = Entity;
						this->hitboxID = i;
						this->curpoint = 0;

						break;

					}

		

				
				}


				for (int ix = 0; ix < 5; ix++)
				{
				float temp_damage = AutoWall->GetDamage2(hitboxPos[ix],Entity);

				if (temp_damage >= Vars.Ragebot.AutoWallDmg)
				{
					
		

					if (Vars.Ragebot.PreferHitbox)
						if (i == Vars.Ragebot.Hitbox)
						{
							bestDamage = temp_damage;
							bestTarget = Entity;
							this->hitboxID = i;
							this->curpoint = ix;

							break;
						}


					if (Vars.Ragebot.SmartHitbox)
					{
						if (Entity->GetHealth() < Vars.Ragebot.SmartHitboxHealth)
						{

						if (i == HITBOX_PELVIS || i == HITBOX_BODY || i == HITBOX_THORAX || i == HITBOX_CHEST || i == HITBOX_UPPER_CHEST  )
						{
							bestDamage = temp_damage;
							bestTarget = Entity;
							this->hitboxID = i;
							this->curpoint = ix;
							break;
						}
						}
					}

					if (temp_damage >= bestDamage)
					{
						bestDamage = temp_damage;
						bestTarget = Entity;
						this->hitboxID = i;
						this->curpoint = ix;

					}
				}
				}
			}
			else {
				float temp_damage = AutoWall->GetDamage2(hitboxPos[0],Entity);

				if (temp_damage >= Vars.Ragebot.AutoWallDmg)
				{


					if (Vars.Ragebot.PreferHitbox)
						if (i == Vars.Ragebot.Hitbox)
						{
							bestDamage = temp_damage;
							bestTarget = Entity;
							this->hitboxID = i;
							break;
						}

					if (Vars.Ragebot.SmartHitbox)
					{
						if (Entity->GetHealth() < Vars.Ragebot.SmartHitboxHealth)
						{

							if (i == HITBOX_PELVIS || i == HITBOX_BODY || i == HITBOX_THORAX || i == HITBOX_CHEST || i == HITBOX_UPPER_CHEST)
							{
								bestDamage = temp_damage;
								bestTarget = Entity;
								this->hitboxID = i;
								break;
							}
						}
					}


					if (temp_damage >= bestDamage)
					{
						bestDamage = temp_damage;
						bestTarget = Entity;
						this->hitboxID = i;
					}
				}
			}

		}
	}

	return bestTarget;
}


CBaseEntity* CRageBot::WasFuerAwallFindTarget()
{
	_JUNK_BLOCK(jmp_label5)
	CBaseEntity* bestTarget = NULL;
	float bestDamage = 0.f;

	for (int i = 0; i <= I::Globals->maxClients; i++)
	{
		CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);

		if (!Entity)
			continue;

		if (Entity == G::LocalPlayer)
			continue;

		if (Entity->GetDormant())
			continue;

		if (!Entity->IsPlayer())
			continue;

		if (!Entity->GetAlive())
			continue;

		if (!Vars.Ragebot.FriendlyFire)
		{
			if (G::LocalPlayer->GetTeam() == Entity->GetTeam())
				continue;
		}

		if (Entity->GetImmune())
			continue;

		if (!Vars.Ragebot.HitScanPerformance)
		{
			Vector hitboxPos = this->GetHitboxPosition(Vars.Ragebot.Hitbox, Entity);
			float temp_damage = AutoWall->GetDamage2(hitboxPos,Entity);

			if (temp_damage >= bestDamage && temp_damage >= Vars.Ragebot.AutoWallDmg)
			{
				bestDamage = temp_damage;
				bestTarget = Entity;
				this->hitboxID = Vars.Ragebot.Hitbox;
			}

			continue;
		}

		//Hitscan
		for (int i = Hitboxes::HITBOX_LEFT_FOREARM; i >= Hitboxes::HITBOX_HEAD; i--)
		{
			Vector hitboxPos = this->GetHitboxPosition(i, Entity);

			if (!Entity->IsVisible(hitboxPos))
				continue;

					bestDamage = 1.0f;
					bestTarget = Entity;
					this->hitboxID = i;

					if (Vars.Ragebot.PreferHitbox)
						if (i == Vars.Ragebot.Hitbox)
						{
							break;
						}

		}
	}

	return bestTarget;
}

CBaseEntity* CRageBot::FindTargetNoAwall()
{
	_JUNK_BLOCK(jmp_label6)
	CBaseEntity* bestTarget = NULL;
	float bestDistance = 0xFFFFFF;

	for (int i = 0; i <= I::Globals->maxClients; i++)
	{
		CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);

		if (!Entity)
			continue;

		if (Entity == G::LocalPlayer)
			continue;

		if (Entity->GetDormant())
			continue;

		if (!Entity->IsPlayer())
			continue;

		if (!Entity->GetAlive())
			continue;

		if (!Vars.Ragebot.FriendlyFire)
		{
			if (G::LocalPlayer->GetTeam() == Entity->GetTeam())
				continue;
		}

		if (Entity->GetImmune())
			continue;

		if (!Vars.Ragebot.HitScanPerformance)
		{
			Vector hitboxPos = this->GetHitboxPosition(Vars.Ragebot.Hitbox, Entity);
			
			if (!Entity->IsVisible(hitboxPos))
				continue;

			float temp_distance = G::LocalPlayer->GetEyePosition().Dist(hitboxPos);
			
			if (temp_distance >= bestDistance)
			{
				bestDistance = temp_distance;
				bestTarget = Entity;
				this->hitboxID = Vars.Ragebot.Hitbox;
			}

			continue;
		}

		//Hitscan
		for (int i = Hitboxes::HITBOX_LEFT_FOREARM; i >= Hitboxes::HITBOX_HEAD; i--)
		{
			Vector hitboxPos = this->GetHitboxPosition(i, Entity);

			if (!Entity->IsVisible(hitboxPos))
				continue;

			float temp_distance = G::LocalPlayer->GetEyePosition().Dist(hitboxPos);

			if (temp_distance >= bestDistance)
			{
				bestDistance = temp_distance;
				bestTarget = Entity;
				this->hitboxID = i;
			}
		}
	}

	return bestTarget;
}

bool IsAbleToShoot(CBaseEntity* pLocal)
{
	_JUNK_BLOCK(jmp_label7)
	CBaseCombatWeapon* pWeapon = pLocal->GetWeapon();
	if (!pLocal)return false;
	if (!pWeapon)return false;
	float flServerTime = pLocal->GetTickBase() * I::Globals->interval_per_tick;
	return (!(pWeapon->GetNextPrimaryAttack() > flServerTime));
}

void CRageBot::GoToTarget(CBaseEntity* target)
{
	_JUNK_BLOCK(jmp_label8)
		auto pWeapon = G::LocalPlayer->GetWeapon();
	auto iClip = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pWeapon) + offsets.m_iClip1);
	if (!(iClip > 0)) return;

	if (!G::LocalPlayer->GetWeapon()->IsGun() || G::LocalPlayer->GetWeapon()->IsEmpty() || G::LocalPlayer->GetWeapon()->IsReloading())
		return;

	bool auto_shoot = false;
	bool can_shoot = false;
	bool reloading = false;

	float flServerTime = (float)G::LocalPlayer->GetTickBase() *  I::Globals->interval_per_tick;
	float flNextPrimaryAttack = G::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();
	if (flNextPrimaryAttack <= flServerTime || !Vars.Ragebot.Silent)
		can_shoot = true;

	Vector hitboxPos;

	if (Vars.Ragebot.Multipoint)
	{
		Vector xhitboxPos[9];
		{
			GetHitBoxCenter(target, this->hitboxID, xhitboxPos);
		}

		hitboxPos = xhitboxPos[this->curpoint];
	}
	else
	{
		hitboxPos = this->GetHitboxPosition(this->hitboxID, target);
	}

	//hitboxPos = target->GetPredicted(hitboxPos);*///extra prediction lul

	QAngle aim_angle = M::CalcAngle(G::LocalPlayer->GetEyePosition(), hitboxPos);
	QAngle AimPunch = G::LocalPlayer->GetPunch();
	if (AimPunch.Length() > 0 && AimPunch.Length() < 150)
		aim_angle -= G::LocalPlayer->GetPunch() * 2.0f;

	// fixmove for silentaim
	CFixMove fixMove;
	if (Vars.Ragebot.Silent)
		fixMove.Start();

	auto flSpread = G::LocalPlayer->GetWeapon()->GetInaccuracy();
	float hitchance = Vars.Ragebot.HitChanceAmt / 1000.f >= flSpread;

	if (can_shoot && (!Vars.Ragebot.HitChance || (hitchance >= flSpread)))
	{
		if (Vars.Ragebot.Aimstep)
		{
			G::Aimbotting = true;

			QAngle angNextAngle;
			bool bFinished = Aimstep(G::LastAngle, aim_angle, angNextAngle, Vars.Ragebot.AimstepAmount);
			G::UserCmd->viewangles = angNextAngle;

			if (!Vars.Ragebot.Silent)
				I::Engine->SetViewAngles(aim_angle);

			G::LastAngle = angNextAngle;
			if (bFinished) auto_shoot = true;
		}
		else
		{
			G::Aimbotting = true;

			if (!Vars.Ragebot.Silent)
				I::Engine->SetViewAngles(aim_angle);

			G::UserCmd->viewangles = aim_angle;
			auto_shoot = true;
		}
	}

	if (Vars.Ragebot.Silent)
		fixMove.End();

	static bool IsStopped;

	if (Vars.Ragebot.Pseudonospread)
	{
		if (!G::LocalPlayer->GetWeapon())return;
		auto flMaxSpeed = G::LocalPlayer->GetWeapon()->GetCSWpnData()->flMaxPlayerSpeed * 0.34;
		auto flVel = G::LocalPlayer->GetVelocity().Length();
		if (flVel > flMaxSpeed)
		{
			IsStopped = false;
			G::UserCmd->forwardmove = flMaxSpeed - 20.f;
			G::UserCmd->sidemove = 0.f;
		}
		else
		{
			IsStopped = true;
		}
	}
	if (Vars.Ragebot.AutoStop && can_shoot)
	{
		Vector velocity = G::LocalPlayer->GetVelocity();
		QAngle direction;
		M::VectorAngles(velocity, direction);
		float speed = velocity.Length2D();

		direction.y = G::UserCmd->viewangles.y - direction.y;
		QAngle Nega;
		Nega.x = direction.x * -speed;
		Nega.y = direction.y * -speed;
		Nega.z = direction.z * -speed;
		Vector negated_direction;
		M::AngleVectors(Nega, &negated_direction);

		G::UserCmd->forwardmove = negated_direction.x;
		G::UserCmd->sidemove = negated_direction.y;
	}
	if (Vars.Ragebot.AutoCrouch)
		G::UserCmd->buttons |= IN_DUCK;

	if (auto_shoot && can_shoot && Vars.Ragebot.AutoFire && (!Vars.Ragebot.HitChance || (hitchance >= flSpread))) {
		if (Vars.Ragebot.AutoScope)
		{
			CBaseEntity* pWeapon = reinterpret_cast<CBaseEntity*>(G::LocalPlayer->GetWeapon());
			ClientClass* pWeaponClass = pWeapon->GetClientClass();
			if (pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponAWP) ||
				pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponSSG08) ||
				pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponSCAR20) ||
				pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponG3SG1)) /*||*/
				/*pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponAug) ||
				pWeaponClass->m_ClassID == static_cast<int>(CSGOClassID::CWeaponSG556))*/

				if (G::LocalPlayer->IsScoped())
					G::UserCmd->buttons |= IN_ATTACK;
				else
					G::UserCmd->buttons |= IN_ATTACK2;
			else
				G::UserCmd->buttons |= IN_ATTACK;
		}
		else
			G::UserCmd->buttons |= IN_ATTACK;
	}

	if (Vars.Playerlist.use)
	{
		if (meme_resolvenz::get_instance()->get_best_tick(target->GetIndex()) != 0)
			G::UserCmd->tick_count = meme_resolvenz::get_instance()->get_best_tick(target->GetIndex());
		else
			G::UserCmd->tick_count = TIME_TO_TICKS(target->GetSimulationTime());
	}
	if (IsAbleToShoot(G::LocalPlayer) && G::UserCmd->buttons & IN_ATTACK) G::Shots += 1;
}


bool CRageBot::Aimstep(QAngle src, QAngle dst, QAngle& out, int steps)
{
	_JUNK_BLOCK(jmp_label9)
	QAngle delta_angle = (dst - src).Normalized();;
	bool x_finished = false;
	bool y_finished = false;

	if (delta_angle.x > steps)
		src.x += steps;

	else if (delta_angle.x < -steps)
		src.x -= steps;

	else
	{
		x_finished = true;
		src.x = dst.x;
	}

	if (delta_angle.y > steps)
		src.y += steps;

	else if (delta_angle.y < -steps)
		src.y -= steps;

	else
	{
		y_finished = true;
		src.y = dst.y;
	}

	src.Normalized();

	out = src;
	return x_finished && y_finished;
}

void CLegitBot::CFixMove::Start()
{
	_JUNK_BLOCK(jmp_label10)
	m_oldangle = G::UserCmd->viewangles;
	m_oldforward = G::UserCmd->forwardmove;
	m_oldsidemove = G::UserCmd->sidemove;
}

void CLegitBot::CFixMove::End()
{
	_JUNK_BLOCK(jmp_label11)
	float yaw_delta = G::UserCmd->viewangles.y - m_oldangle.y;
	float f1;
	float f2;

	if (m_oldangle.y < 0.f)
		f1 = 360.0f + m_oldangle.y;
	else
		f1 = m_oldangle.y;

	if (G::UserCmd->viewangles.y < 0.0f)
		f2 = 360.0f + G::UserCmd->viewangles.y;
	else
		f2 = G::UserCmd->viewangles.y;

	if (f2 < f1)
		yaw_delta = abs(f2 - f1);
	else
		yaw_delta = 360.0f - abs(f1 - f2);
	yaw_delta = 360.0f - yaw_delta;

	G::UserCmd->forwardmove = cos(DEG2RAD(yaw_delta)) * m_oldforward + cos(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
	G::UserCmd->sidemove = sin(DEG2RAD(yaw_delta)) * m_oldforward + sin(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
}

void CRageBot::CFixMove::Start()
{
	_JUNK_BLOCK(jmp_label12)
	m_oldangle = G::UserCmd->viewangles;
	m_oldforward = G::UserCmd->forwardmove;
	m_oldsidemove = G::UserCmd->sidemove;
}

void CRageBot::CFixMove::End()
{
	_JUNK_BLOCK(jmp_label13)
	float yaw_delta = G::UserCmd->viewangles.y - m_oldangle.y;
	float f1;
	float f2;

	if (m_oldangle.y < 0.f)
		f1 = 360.0f + m_oldangle.y;
	else
		f1 = m_oldangle.y;

	if (G::UserCmd->viewangles.y < 0.0f)
		f2 = 360.0f + G::UserCmd->viewangles.y;
	else
		f2 = G::UserCmd->viewangles.y;

	if (f2 < f1)
		yaw_delta = abs(f2 - f1);
	else
		yaw_delta = 360.0f - abs(f1 - f2);
	yaw_delta = 360.0f - yaw_delta;

	G::UserCmd->forwardmove = cos(DEG2RAD(yaw_delta)) * m_oldforward + cos(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
	G::UserCmd->sidemove = sin(DEG2RAD(yaw_delta)) * m_oldforward + sin(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
}
//
//void CPredictionSystem::StartPrediction() 
//{
//	int iFlags = G::LocalPlayer->GetFlags();
//	m_flOldCurtime = I::Globals->curtime;
//	m_flOldFrametime = I::Globals->frametime;
//	I::Globals->curtime = G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick;
//	I::Globals->frametime = I::Globals->interval_per_tick;
//	/*I::g_pMovement->StartTrackPredictionErrors(G::LocalPlayer);*/
//	I::g_pMoveHelper->SetHost(G::LocalPlayer);
//	memset(&m_MoveData, 0, sizeof(m_MoveData));
//	I::g_pMoveHelper->SetHost(G::LocalPlayer);
//	I::Prediction->SetupMove(G::LocalPlayer, G::UserCmd, nullptr, &m_MoveData);
//	I::g_pMovement->ProcessMovement(G::LocalPlayer, &m_MoveData);
//	I::Prediction->FinishMove(G::LocalPlayer, G::UserCmd, &m_MoveData);
//	*(int*)((DWORD)G::LocalPlayer + offsets.m_fFlags) = iFlags;
//}
//
//void CPredictionSystem::EndPrediction()
//{
//	int iFlags = G::LocalPlayer->GetFlags();
//	/*I::g_pMovement->FinishTrackPredictionErrors(G::LocalPlayer);*/
//	I::g_pMoveHelper->SetHost(0);
//	I::Globals->curtime = m_flOldCurtime;
//	I::Globals->frametime = m_flOldFrametime;
//	*(int*)((DWORD)G::LocalPlayer + offsets.m_fFlags) = iFlags;
//}
