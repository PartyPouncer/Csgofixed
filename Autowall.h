#pragma once

struct FireBulletData
{
	Vector          src;
	trace_t         enter_trace;
	Vector          direction;
	CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};

class CAutowall
{
public:
	/*float GetHitgroupDamageMultiplier(int iHitGroup);
	void ScaleDamage(int hitgroup, CBaseEntity * enemy, float weapon_armor_ratio, float & current_damage);
	bool DidHitNonWorldEntity(CBaseEntity * m_pEnt);
	bool TraceToExit(Vector & end, trace_t & tr, float x, float y, float z, float x2, float y2, float z2, trace_t * trace);
	bool HandleBulletPenetration(WeaponInfo_t * wpn_data, FireBulletData & data);
	bool SimulateFireBullet(CBaseCombatWeapon * pWeapon, FireBulletData & data);
	float GetDamage(const Vector & point);*/
	/*float GetDamage2(Vector& vecPoint,CBaseEntity* ent);*/
/*

	float GetDamage(const Vector& point);
	float GetDamage(Vector & point, CBaseEntity * ent);
	bool SimulateFireBullet(CBaseCombatWeapon* pWeapon, FireBulletData &data);
	bool HandleBulletPenetration(WeaponInfo_t *wpn_data, FireBulletData &data);
	bool TraceToExit(Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace);
	bool DidHitNonWorldEntity(CBaseEntity* m_pEnt);
	void ScaleDamage(int hitgroup, CBaseEntity *enemy, float weapon_armor_ratio, float &current_damage);
	float GetHitgroupDamageMultiplier(int iHitGroup);*/

		float GetDamage2(Vector & vecPoint, CBaseEntity * ent);

};

extern CAutowall* AutoWall;

//bool CanAutowall(CBaseEntity * other, const Vector & _startpos, Vector & endpos, float * damage, CAutowall * ScaleDamage);
