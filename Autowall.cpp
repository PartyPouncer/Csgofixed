#include "Cheat.h"

CAutowall* AutoWall = new CAutowall;

//float CAutowall::GetHitgroupDamageMultiplier(int iHitGroup)
//{
//
//
//	switch (iHitGroup)
//	{
//	case HITGROUP_GENERIC:
//		return 0.5f;
//	case HITGROUP_HEAD:
//		return 4.0f;
//	case HITGROUP_CHEST:
//		return 2.5f;
//	case HITGROUP_STOMACH:
//		return 2.f;
//	case HITGROUP_LEFTARM:
//		return 1.0f;
//	case HITGROUP_RIGHTARM:
//		return 1.0f;
//	case HITGROUP_LEFTLEG:
//		return 0.75f;
//	case HITGROUP_RIGHTLEG:
//		return 0.75f;
//	/*case HITGROUP_GEAR:
//		return 0.25f;*/
//	}
//	return 1.0f;
//}
//
//void CAutowall::ScaleDamage(int hitgroup, CBaseEntity *enemy, float weapon_armor_ratio, float &current_damage)
//{
//	current_damage *= GetHitgroupDamageMultiplier(hitgroup);
//
//	int armor = enemy->GetArmor();
//	int helmet = enemy->HasHelmet();
//
//	if (armor > 0)
//	{
//		if (hitgroup == HITGROUP_HEAD)
//		{
//			if (helmet)
//				current_damage *= (weapon_armor_ratio * .5f);
//		}
//		else
//		{
//			current_damage *= (weapon_armor_ratio * .5f);
//		}
//	}
//}
//
//bool CAutowall::DidHitNonWorldEntity(CBaseEntity* m_pEnt)
//{
//	//U::PrintMessage("m_pEnt: %s\n I::ClientEntList->GetClientEntity( 0 ): %s\n", &m_pEnt->GetName(), I::ClientEntList->GetClientEntity(0)->GetName());
//	return m_pEnt != NULL && m_pEnt == I::ClientEntList->GetClientEntity(G::BestTarget);
//}
//
//bool CAutowall::TraceToExit(Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace)
//{
//	typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);
//	static TraceToExitFn TraceToExit = (TraceToExitFn)U::FindPattern("client.dll", "55 8B EC 83 EC 30 F3 0F 10 75");
//
//	if (!TraceToExit)
//	{
//		return false;
//		U::PrintMessage(charenc("TraceToExit not found\n"));
//	}
//	_asm
//	{
//		push trace
//		push z2
//		push y2
//		push x2
//		push z
//		push y
//		push x
//		mov edx, tr
//		mov ecx, end
//		call TraceToExit
//		add esp, 0x1C
//	}
//}
//
//bool CAutowall::HandleBulletPenetration(WeaponInfo_t *wpn_data, FireBulletData &data)
//{
//	surfacedata_t *enter_surface_data = I::Physprops->GetSurfaceData(data.enter_trace.surface.surfaceProps);
//	int enter_material = enter_surface_data->game.material;
//	float enter_surf_penetration_mod = *(float*)((DWORD)enter_surface_data + 76);
//
//	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
//	data.current_damage *= pow((wpn_data->flRangeModifier), (data.trace_length * 0.002));
//
//	if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
//		data.penetrate_count = 0;
//
//	if (data.penetrate_count <= 0)
//		return false;
//
//	Vector dummy;
//	trace_t trace_exit;
//	if (!TraceToExit(dummy, data.enter_trace, data.enter_trace.endpos.x, data.enter_trace.endpos.y, data.enter_trace.endpos.z, data.direction.x, data.direction.y, data.direction.z, &trace_exit))
//		return false;
//
//
//
//
//	surfacedata_t *exit_surface_data = I::Physprops->GetSurfaceData(trace_exit.surface.surfaceProps);
//	int exit_material = exit_surface_data->game.material;
//
//	float exit_surf_penetration_mod = *(float*)((DWORD)exit_surface_data + 76);
//	float final_damage_modifier = 0.16f;
//	float combined_penetration_modifier = 0.0f;
//
//	if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
//	{
//		combined_penetration_modifier = 3.0f;
//		final_damage_modifier = 0.05f;
//	}
//	else
//	{
//		combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
//	}
//
//	if (enter_material == exit_material)
//	{
//		if (exit_material == 87 || exit_material == 85)
//			combined_penetration_modifier = 3.0f;
//		else if (exit_material == 76)
//			combined_penetration_modifier = 2.0f;
//	}
//
//	float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
//	float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->flPenetration) * 1.25f);
//	float thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();
//
//	thickness *= thickness;
//	thickness *= v34;
//	thickness /= 24.0f;
//
//	float lost_damage = fmaxf(0.0f, v35 + thickness);
//
//	if (lost_damage > data.current_damage)
//		return false;
//
//	if (lost_damage >= 0.0f)
//		data.current_damage -= lost_damage;
//
//	if (data.current_damage < 1.0f)
//		return false;
//
//	data.src = trace_exit.endpos;
//	data.penetrate_count--;
//
//	return true;
//}
//
//bool CAutowall::SimulateFireBullet(CBaseCombatWeapon* pWeapon, FireBulletData &data)
//{
//	data.penetrate_count = 4;
//	data.trace_length = 0.0f;
//	WeaponInfo_t* weaponData = G::LocalPlayer->GetWeapon()->GetCSWpnData();
//
//	if (weaponData == NULL)
//		return false;
//
//	data.current_damage = (float)weaponData->iDamage;
//
//	while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
//	{
//		data.trace_length_remaining = weaponData->flRange - data.trace_length;
//
//		Vector end = data.src + data.direction * data.trace_length_remaining;
//
//		//data.enter_trace
//		U::TraceLine(data.src, end, 0x4600400B, G::LocalPlayer, &data.enter_trace);
//
//		Ray_t ray;
//		ray.Init(data.src, end + data.direction*40.f);
//
//		I::EngineTrace->TraceRay(ray, 0x4600400B, &data.filter, &data.enter_trace);
//
//		U::TraceLine(data.src, end + data.direction*40.f, 0x4600400B, G::LocalPlayer, &data.enter_trace);
//
//		if (data.enter_trace.fraction == 1.0f)
//			break;
//
//		if ((data.enter_trace.hitgroup <= 7) && (data.enter_trace.hitgroup > 0))
//		{
//			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
//			data.current_damage *= pow(weaponData->flRangeModifier, data.trace_length * 0.002);
//
//
//			//TEST
//			data.current_damage *= GetHitgroupDamageMultiplier(data.enter_trace.hitgroup);
//			//ScaleDamage(data.enter_trace.hitgroup, data.enter_trace.m_pEnt, weaponData->m_flArmorRatio, data.current_damage);
//
//			return true;
//		}
//
//		if (!HandleBulletPenetration(weaponData, data))
//			break;
//	}
//
//	return false;
//}
//
//float CAutowall::GetDamage(const Vector& point)
//{
//	float damage = 0.f;
//	Vector dst = point;
//	FireBulletData data;
//	data.src = G::LocalPlayer->GetEyePosition();
//	data.filter.pSkip = G::LocalPlayer;
//
//	QAngle angles = M::CalcAngle(data.src, dst);
//	M::AngleVectors(angles, &data.direction);
//	Vector dataNormalized;
//
//	data.direction.Normalize();
//
//	CBaseCombatWeapon* pWeap = G::LocalPlayer->GetWeapon();
//	if (SimulateFireBullet(pWeap, data))
//	{
//		if (G::LocalPlayer->GetTeam() == data.enter_trace.m_pEnt->GetTeam())
//			return 0.f;
//
//		damage = data.current_damage;
//	}
//
//	return damage;
//}



#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10			// alerts NPC, but doesn't do damage or bleed (1/100th damage)

float GetHitgroupDamageMultiplier(int iHitGroup)
{
	switch (iHitGroup)
	{
	case HITGROUP_GENERIC:
	{
		return 0.50f;
	}
	case HITGROUP_HEAD:
	{
		return 4.0f;
	}
	case HITGROUP_CHEST:
	case HITGROUP_LEFTARM:
	case HITGROUP_RIGHTARM:
	{
		return 1.0f;
	}
	case HITGROUP_STOMACH:
	{
		return 1.25f;
	}
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
	{
		return 0.75f;
	}
	}
	return 1.0f;
}
bool CanAutowall(CBaseEntity *other, const Vector &_startpos, Vector &endpos, float *damage)
{
	Ray_t ray;
	CGameTrace ntr;

	CBaseEntity* me = G::LocalPlayer;
	auto* pWeapon = me->GetWeapon();

	if (!other || !me || !pWeapon)
		return false;

	auto* data = pWeapon->GetCSWpnData();

	if (!data)
		return false;

	*damage = (float)data->iDamage;

	static bool(__thiscall *BulletHandler)(CBaseEntity *me, float &penetration, int &SurfaceMat, int *usestaticvalues, CGameTrace *ray, Vector *normaldelta,
		float _setto0f_8, float surfacepenetration, float damagemultiplier, int unknown, int _setto0x1002_12, float penetration2, int *hitsleft,
		Vector *ResultPos, float hitx, float hity, float *damage) = 0;

	if (!BulletHandler)
		BulletHandler = (decltype(BulletHandler))offsets.dwBulletHandler;

	int usestaticvalues = 0;

	Vector normal = endpos - me->GetEyePosition();

	normal.NormalizeInPlace();
//	float lengthleft = (endpos - me->GetEyePosition()).Length();

	int hitsleft = 4;
	Vector result(me->GetEyePosition());

	do
	{
		CTraceFilterSimple filter;
		filter.pSkip = me;

		Vector mePos = me->GetEyePosition();
		Vector otherPos = other->GetEyePosition();

		ray.Init(result, endpos);

		I::EngineTrace->TraceRay(ray, 0x4600400B, &filter, &ntr);

		if (ntr.hitgroup != 0)
			break;

		surfacedata_t *entersurf = I::Physprops->GetSurfaceData(ntr.surface.surfaceProps);
		int material = entersurf->game.material;
		float penVal = data->flPenetration;

		if (BulletHandler(me, penVal, material, &usestaticvalues, &ntr, &normal, 0.f, entersurf->game.penetrationmodifier, entersurf->game.damagemodifier, 0, 0x1002, penVal, &hitsleft, &result, 0.f, 0.f, damage))
		{
			break;
		}

	} while (hitsleft > 0);


	*damage *= powf(data->flRangeModifier, (_startpos - result).Length() * (float)0.002);
	GetHitgroupDamageMultiplier(ntr.hitgroup);

	*damage *= GetHitgroupDamageMultiplier(ntr.hitgroup);
	
		int armor = other->GetArmor();
		int helmet = other->HasHelmet();
	
		if (armor > 0)
		{
			if (ntr.hitgroup == HITGROUP_HEAD)
			{
				if (helmet)
					*damage *= (data->flArmorRatio * 1.5f);
			}
			else
			{
				*damage *= (data->flArmorRatio  * 0.5f);
			}
		}

	if (ntr.hitgroup != 0)
		return ntr.m_pEnt && ntr.m_pEnt == other;

	return false;
}

float CAutowall::GetDamage2(Vector& vecPoint, CBaseEntity* ent)
{
	float damage;

	G::isAutowalling = true;
	if (CanAutowall(ent, G::LocalPlayer->GetEyePosition(), vecPoint, &damage))
	{
			return damage;
	}
	return 0.0f;
}


