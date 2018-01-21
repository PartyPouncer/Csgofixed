#pragma once

#include "SDK.h"

COffsets offsets;

void Offsets::GrabOffsets( )
{
	offsets.m_iHealth = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iHealth" ) );
	offsets.m_iTeamNum = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iTeamNum" ) );
	offsets.m_ArmorValue = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_ArmorValue" ) );
	offsets.m_bHasHelmet = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_bHasHelmet" ) );
	offsets.m_iClass = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iClass" ) );
	offsets.m_bDormant = 0xE9;
	offsets.m_hConstraintEntity = U::NetVars->GetOffset(charenc("DT_BasePlayer"), charenc("m_hConstraintEntity"));
	offsets.m_bGunGameImmunity = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_bGunGameImmunity" ) );
	offsets.m_lifeState = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_lifeState" ) );
	offsets.m_fFlags = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_fFlags" ) );
	offsets.m_Local =  U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_Local" ) );
	offsets.m_nTickBase = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_nTickBase" ) );
	offsets.m_nForceBone = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_nForceBone" ) );
	offsets.m_angEyeAngles = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_angEyeAngles" ) );
	offsets.m_angEyeAnglesX = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_angEyeAngles[0]"));
	offsets.m_angEyeAnglesY = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_angEyeAngles[1]"));
	offsets.m_flFlashDuration = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_flFlashDuration" ) );
	offsets.m_iGlowIndex = offsets.m_flFlashDuration + 0x18;
	offsets.m_mBoneMatrix = offsets.m_nForceBone + 0x1C;
	offsets.m_nModelIndex = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_nModelIndex" ) );
	offsets.m_viewPunchAngle = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_viewPunchAngle" ) );
	offsets.m_aimPunchAngle = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_aimPunchAngle" ) );
	offsets.m_vecOrigin = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_vecOrigin" ) );
	offsets.m_vecViewOffset = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_vecViewOffset[0]" ) );
	offsets.m_vecVelocity = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_vecVelocity[0]" ) );
	offsets.m_szLastPlaceName = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_szLastPlaceName" ) );
	offsets.m_hActiveWeapon = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_hActiveWeapon" ) );
	offsets.m_fAccuracyPenalty = U::NetVars->GetOffset( charenc( "DT_WeaponCSBase" ), charenc( "m_fAccuracyPenalty" ) );
	offsets.m_Collision = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_Collision" ) );
	offsets.m_CollisionGroup = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_CollisionGroup" ) );
	offsets.m_iShotsFired = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iShotsFired" ) );
	offsets.m_iWeaponID = U::NetVars->GetOffset(charenc("DT_WeaponCSBase"), charenc("m_iItemDefinitionIndex"));
	offsets.m_hOwnerEntity = U::NetVars->GetOffset( charenc( "DT_BaseEntity" ), charenc( "m_hOwnerEntity" ) );
	offsets.m_nMoveType = U::NetVars->GetOffset(charenc("DT_BasePlayer"), charenc("m_flAnimTime")) - 0x4;
	offsets.m_nHitboxSet = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_nHitboxSet" ) );
	offsets.m_bIsScoped = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_bIsScoped"));
	offsets.m_bIsBroken = U::NetVars->GetOffset( charenc( "DT_BreakableSurface" ), charenc( "m_bIsBroken" ) );
	offsets.m_flC4Blow = U::NetVars->GetOffset( charenc( "DT_PlantedC4" ), charenc( "m_flC4Blow" ) );

	offsets.m_szCustomName = U::NetVars->GetOffset(charenc("DT_BaseCombatWeapon"), charenc("m_szCustomName"));
	offsets.m_bReloadVisuallyComplete = U::NetVars->GetOffset( charenc( "DT_WeaponCSBase" ), charenc( "m_bReloadVisuallyComplete" ) );
	offsets.m_flNextPrimaryAttack = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_flNextPrimaryAttack" ) );
	offsets.m_nFallbackPaintKit = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_nFallbackPaintKit" ) );
	offsets.m_nFallbackSeed = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_nFallbackSeed" ) );
	offsets.m_flFallbackWear = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_flFallbackWear" ) );
	offsets.m_nFallbackStatTrak = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_nFallbackStatTrak" ) );
	offsets.m_AttributeManager = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_AttributeManager" ) );
	offsets.m_Item = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_Item" ) );
	offsets.m_iEntityLevel = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iEntityLevel" ) );
	offsets.m_iItemIDHigh = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iItemIDHigh" ) );
	offsets.m_iItemIDLow = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iItemIDLow" ) );
	offsets.m_iAccountID = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iAccountID" ) );
	offsets.m_iEntityQuality = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iEntityQuality" ) );
	offsets.m_iClip1 = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iClip1" ) );
	offsets.m_OriginalOwnerXuidLow = U::NetVars->GetOffset( charenc( "DT_BaseAttributableItem" ), charenc( "m_OriginalOwnerXuidLow" ) );
	offsets.m_OriginalOwnerXuidHigh = U::NetVars->GetOffset( charenc( "DT_BaseAttributableItem" ), charenc( "m_OriginalOwnerXuidHigh" ) );
	offsets.m_iItemDefinitionIndex = U::NetVars->GetOffset( charenc( "DT_BaseAttributableItem" ), charenc( "m_iItemDefinitionIndex" ) );
	offsets.m_hMyWeapons = U::NetVars->GetOffset(charenc("DT_BaseAttributableItem"), charenc("m_hMyWeapons"));
	offsets.m_hViewModel = U::NetVars->GetOffset(charenc("DT_BasePlayer"), charenc("m_hViewModel"));
	offsets.m_flLowerBodyYawTarget = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_flLowerBodyYawTarget"));
	offsets.m_flAbsYaw = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_flAbsYaw"));
	offsets.m_flDeathYaw = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_flDeathYaw"));

	offsets.m_iCompetitiveRanking = U::NetVars->GetOffset(charenc("DT_CSPlayerResource"), charenc("m_iCompetitiveRanking"));
	offsets.m_iCompetitiveWins = U::NetVars->GetOffset(charenc("DT_CSPlayerResource"), charenc("m_iCompetitiveWins"));
	offsets.m_flSimulationTime = U::NetVars->GetOffset(charenc("DT_BasePlayer"), charenc("m_flSimulationTime"));
	offsets.m_nWritableBones = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_nForceBone")) + 0x20;
	offsets.dwDeadFlag = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("deadflag"));
	offsets.smoke = U::NetVars->GetOffset(charenc("DT_SmokeGrenadeProjectile"), charenc("m_bDidSmokeEffect"));
	offsets.ArmorValue = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_ArmorValue"));
	offsets.HasHeavyArmor = U::NetVars->GetOffset(charenc("DT_CSPlayer"), charenc("m_bHasHeavyArmor"));
	offsets.m_clrRender = U::NetVars->GetOffset(charenc("DT_BaseEntity"), charenc("m_clrRender"));
	offsets.m_flPostponeFireReadyTime = U::NetVars->GetOffset(charenc("DT_WeaponCSBase"), charenc("m_flPostponeFireReadyTime"));
	offsets.m_bSpotted = U::NetVars->GetOffset(charenc("DT_BaseEntity"), charenc("m_bSpotted"));


	offsets.m_dwOcclusionArray = *(uintptr_t*)(U::FindPattern("client.dll", "A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8") + 0x1);
	offsets.m_bDidCheckForOcclusion = *(uintptr_t*)(U::FindPattern("client.dll", "A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8") + 0x7);
	offsets.CalcPlayerView = U::FindPattern(strenc("client.dll"), strenc(" 84 C0 75 08 57 8B CE E8 ?? ?? ?? ?? 8B 06"));
	offsets.GlowManager = *(DWORD *)(U::FindPattern(("client.dll"), ("0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00")) + 0x3);
	offsets.d3d9Device = **(DWORD**)(U::FindPattern(strenc("shaderapidx9.dll"), strenc("A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C")) + 1);
	offsets.LoadFromBufferEx = U::FindPattern(strenc("client.dll"), strenc("55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04"));
	offsets.InitKeyValuesEx = U::FindPattern(strenc("client.dll"), strenc("55 8B EC 51 33 C0 C7 45"));
	offsets.ServerRankRevealAllEx = U::FindPattern(strenc("client.dll"), strenc("55 8B EC 8B 0D ? ? ? ? 68"));
	offsets.IsReadyEx = U::FindPattern(strenc("client.dll"), strenc("55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE"));
	offsets.ChangeClanTag = U::FindPattern(strenc("engine.dll"), strenc("53 56 57 8B DA 8B F9 FF 15"));
	offsets.dwBulletHandler = U::FindPatternAlt(strenc("client.dll"), (BYTE*)"\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF8\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\x83\xEC\x78\x8B\x53\x14","xxxxxxxxxxxxxxxxxxxxxxxxxxxx",0,0);
	/*offsets.GameResources = *(DWORD*)(U::FindPattern("client.dll", (PBYTE)"8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7") + 0x1A44);*/
} 