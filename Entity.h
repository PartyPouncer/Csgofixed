#pragma once

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

class CBaseCombatWeapon;
class CBaseViewModel;

class CBaseEntity
{
public:
	char				__pad[0x64];
	int					index;
	int					GetHealth();
	int					GetTeam();
	int					GetFlags();
	int					GetTickBase();
	int					GetShotsFired();
	float m_flPostponeFireReadyTime();
	int					GetMoveType();
	int					GetModelIndex();
	int					GetHitboxSet();
	int					GetUserID();
	int					GetArmor();
	int					GetCollisionGroup();
	int                 GetIndex();
	int					PhysicsSolidMaskForEntity();
	int					GetOwner();
	int					GetGlowIndex();
	float               lowerbodyyaw();
	bool				GetAlive();
	bool				GetDormant();
	float               GetLowerBodyTarget();
	QAngle *            GetHeadRotation();
	bool				GetImmune();
	bool				IsEnemy();
	bool				IsVisible( int bone );
	bool				IsVisible(Vector pos);
	bool				m_visible;
	bool				IsScoped();
	bool				IsBroken();
	bool				HasHelmet();
	bool				IsFlashed();
	bool				IsTargetingLocal();
	float				GetFlashDuration();
	float				GetBombTimer();
	QAngle				GetViewPunch();
	QAngle				GetPunch();
	QAngle				GetEyeAngles();
	Vector				GetOrigin();
	Vector				GetEyePosition();
	Vector				GetBonePosition( int iBone );
	bool				SetupBones( matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime );
	Vector				GetVelocity();
	Vector				GetPredicted( Vector p0 );
	ICollideable*		GetCollideable();
	player_info_t		GetPlayerInfo();
	const model_t*			GetModel();
	std::string			GetName();
	std::string			GetSteamID();
	std::string			GetLastPlace();
	CBaseCombatWeapon*	GetWeapon();
	UINT*				GetWeapons();
	ClientClass*		GetClientClass();
	bool				IsPlayer();
	CBaseViewModel*		GetViewModel();
	float GetSimulationTime();
	DWORD GetOBS();
	void SetAngle2(Vector wantedang);
};



class CBaseViewModel {
public:
	int GetModelIndex();
	DWORD GetOwner();
	DWORD GetWeapon();
	void SetWeaponModel(const char* Filename, CBaseEntity* Weapon);
};


class CHudTexture
{
public:
	char type[64]; //0x0000
	char subtype[64]; //0x0040
	char unknowndata00[2]; //0x0080
	char charinFont; //0x0082
	char unknowndata01[1]; //0x0083
};//Size=0x00AC

	class WeaponInfo_t
	{
	public:
		char pad_0x0000[4]; // 0x0000
		char* consoleName; // 0x0004
		char pad_0008[12]; // 0x0008
		int iMaxClip1; // 0x0014
		int iMaxClip2; // 0x0018
		int iDefaultClip1; // 0x001C
		int iDefaultClip2; // 0x0020
		char pad_0024[8]; // 0x0024
		char* szWorldModel; // 0x002C
		char* szViewModel; // 0x0030
		char* szDroppedModel; // 0x0034
		char pad_0038[4]; // 0x0038
		char* N0000023E; // 0x003C
		char pad_0040[56]; // 0x0040
		char* szEmptySound; // 0x0078
		char pad_007C[4]; // 0x007C
		char* szBulletType; // 0x0080
		char pad_0084[4]; // 0x0084
		char* szHudName; // 0x0088
		char* szWeaponName; // 0x008C
		char pad_0090[56]; // 0x0090
		int WeaponType; // 0x00C8
		int iWeaponPrice; // 0x00CC
		int iKillAward; // 0x00D0
		char* szAnimationPrefix; // 0x00D4
		float flCycleTime; // 0x00D8
		float flCycleTimeAlt; // 0x00DC
		float flTimeToIdle; // 0x00E0
		float flIdleInterval; // 0x00E4
		bool bFullAuto; // 0x00E8
		char pad_0x00E5[3]; // 0x00E9
		int iDamage; // 0x00EC
		float flArmorRatio; // 0x00F0
		int iBullets; // 0x00F4
		float flPenetration; // 0x00F8
		float flFlinchVelocityModifierLarge; // 0x00FC
		float flFlinchVelocityModifierSmall; // 0x0100
		float flRange; // 0x0104
		float flRangeModifier; // 0x0108
		float flThrowVelocity; // 0x010C
		char pad_0x010C[12]; // 0x0110
		bool bHasSilencer; // 0x011C
		char pad_0x0119[3]; // 0x011D
		char* pSilencerModel; // 0x0120
		int iCrosshairMinDistance; // 0x0124
		int iCrosshairDeltaDistance;// 0x0128 - iTeam?
		float flMaxPlayerSpeed; // 0x012C
		float flMaxPlayerSpeedAlt; // 0x0130
		float flSpread; // 0x0134
		float flSpreadAlt; // 0x0138
		float flInaccuracyCrouch; // 0x013C
		float flInaccuracyCrouchAlt; // 0x0140
		float flInaccuracyStand; // 0x0144
		float flInaccuracyStandAlt; // 0x0148
		float flInaccuracyJumpInitial;// 0x014C
		float flInaccuracyJump; // 0x0150
		float flInaccuracyJumpAlt; // 0x0154
		float flInaccuracyLand; // 0x0158
		float flInaccuracyLandAlt; // 0x015C
		float flInaccuracyLadder; // 0x0160
		float flInaccuracyLadderAlt; // 0x0164
		float flInaccuracyFire; // 0x0168
		float flInaccuracyFireAlt; // 0x016C
		float flInaccuracyMove; // 0x0170
		float flInaccuracyMoveAlt; // 0x0174
		float flInaccuracyReload; // 0x0178
		int iRecoilSeed; // 0x017C
		float flRecoilAngle; // 0x0180
		float flRecoilAngleAlt; // 0x0184
		float flRecoilAngleVariance; // 0x0188
		float flRecoilAngleVarianceAlt; // 0x018C
		float flRecoilMagnitude; // 0x0190
		float flRecoilMagnitudeAlt; // 0x0194
		float flRecoilMagnitudeVariance; // 0x0198
		float flRecoilMagnitudeVarianceAlt; // 0x019C
		float flRecoveryTimeCrouch; // 0x01A0
		float flRecoveryTimeStand; // 0x01A4
		float flRecoveryTimeCrouchFinal; // 0x01A8
		float flRecoveryTimeStandFinal; // 0x01AC
		int iRecoveryTransitionStartBullet;// 0x01B0
		int iRecoveryTransitionEndBullet; // 0x01B4
		bool bUnzoomAfterShot; // 0x01B8
		bool bHideViewModelZoomed; // 0x01B9
		char pad_0x01B5[2]; // 0x01BA
		char iZoomLevels[3]; // 0x01BC
		int iZoomFOV[2]; // 0x01C0
		float fZoomTime[3]; // 0x01C4
		char* szWeaponClass; // 0x01D4
		float flAddonScale; // 0x01D8
		char pad_0x01DC[4]; // 0x01DC
		char* szEjectBrassEffect; // 0x01E0
		char* szTracerEffect; // 0x01E4
		int iTracerFrequency; // 0x01E8
		int iTracerFrequencyAlt; // 0x01EC
		char* szMuzzleFlashEffect_1stPerson; // 0x01F0
		char pad_0x01F4[4]; // 0x01F4
		char* szMuzzleFlashEffect_3rdPerson; // 0x01F8
		char pad_0x01FC[4]; // 0x01FC
		char* szMuzzleSmokeEffect; // 0x0200
		float flHeatPerShot; // 0x0204
		char* szZoomInSound; // 0x0208
		char* szZoomOutSound; // 0x020C
		float flInaccuracyPitchShift; // 0x0210
		float flInaccuracySoundThreshold; // 0x0214
		float flBotAudibleRange; // 0x0218
		BYTE pad_0x0218[8]; // 0x0220
		char* pWrongTeamMsg; // 0x0224
		bool bHasBurstMode; // 0x0228
		BYTE pad_0x0225[3]; // 0x0229
		bool bIsRevolver; // 0x022C
		bool bCannotShootUnderwater; // 0x0230 };,
		CHudTexture* iconWeapon;
		CHudTexture* iconAmmo;
		CHudTexture* iconWeaponS;
	};

	struct CCSWeaponInfo
	{
		char pad00[0x4];
		char* m_WeaponName;			// 0x04 / weapon_%s which works with the revolver and coop items too
		char pad08[0x80];
		char* m_LocalizedWpnName;	// 0x88 / #SFUI_WPNHUD_%s
		char pad8C[0x3C];
		int m_WeaponType;			// 0xC8
		char padCC[0x20];
		int m_Damage;				// 0xEC
		float m_ArmorRatio;			// 0xF0
		int m_BulletsPerShot;		// 0xF4
		float m_Penetration;		// 0xF8
		char padFC[0x8];
		float m_Range;				// 0x104
		float m_RangeModifier;		// 0x108
		char pad10C[0x10];
		bool m_HasSilencer;			// 0x11C
		char pad120[0x108];
		bool m_HasBurstmode;		// 0x228
		bool m_IsRevolver;			// 0x229
	};

class CBaseCombatWeapon
{
public:
	char			__pad[0x64];
	int				index;//0x68
	int&			GetWeaponID();//0x6C
	float&			GetNextPrimaryAttack();
	float&			GetAccuracyPenalty();
	int*			GetXUIDLow();
	int*			GetXUIDHigh();
	int*			GetEntityQuality();
	int*			GetAccountID();
	int*			GetItemIDHigh();
	int&			GetItemDefinitionIndex();
	float&          GetflPostponeFireReadyTime();
	int*			GetFallbackPaintKit();
	int*			GetFallbackStatTrak();
	int*			GetFallbackSeed();
	float*			GetFallbackWear();
	bool			IsEmpty();
	bool			IsReloading();
	void			UpdateAccuracyPenalty();
	float			GetWeaponSpread();
	float			GetInaccuracy();
	float GetSpreadReal();
	float			GetWeaponCone();
	WeaponInfo_t*	GetCSWpnData();
	bool			IsGun();
	std::string		GetWeaponName();

	bool IsRevolver();

	/*int GetWeaponType();*/

};
//enum WEAPONCLASS
//{
//	WEPCLASS_INVALID,
//	WEPCLASS_RIFLE,
//	WEPCLASS_PISTOL,
//	WEPCLASS_SHOTGUN,
//	WEPCLASS_SNIPER,
//	WEPCLASS_SMG,
//	WEPCLASS_MACHINEGUN,
//	WEPCLASS_KNIFE,
//};
//
//int CBaseCombatWeapon::GetWeaponType()
//{
//	if (!this) return WEPCLASS_INVALID;
//	auto id = this->GetWeaponID();
//	switch (id)
//	{
//	case WEAPON_DEAGLE:
//	case WEAPON_ELITE:
//	case WEAPON_FIVESEVEN:
//	case WEAPON_HKP2000:
//	case WEAPON_USP_SILENCER:
//	case WEAPON_CZ75A:
//	case WEAPON_TEC9:
//	case WEAPON_REVOLVER:
//	case WEAPON_GLOCK:
//	case WEAPON_P250:
//		return WEPCLASS_PISTOL;
//		break;
//	case WEAPON_AK47:
//	case WEAPON_M4A1:
//	case WEAPON_M4A1_SILENCER:
//	case WEAPON_GALILAR:
//	case WEAPON_AUG:
//	case WEAPON_FAMAS:
//	case WEAPON_SG556:
//		return WEPCLASS_RIFLE;
//		break;
//	case WEAPON_P90:
//	case WEAPON_BIZON:
//	case WEAPON_MP7:
//	case WEAPON_MP9:
//	case WEAPON_MAC10:
//	case WEAPON_UMP45:
//		return WEPCLASS_SMG;
//		break;
//	case WEAPON_AWP:
//	case WEAPON_G3SG1:
//	case WEAPON_SCAR20:
//	case WEAPON_SSG08:
//		return WEPCLASS_SNIPER;
//		break;
//	case WEAPON_NEGEV:
//	case WEAPON_M249:
//		return WEPCLASS_MACHINEGUN;
//		break;
//	case WEAPON_MAG7:
//	case WEAPON_SAWEDOFF:
//	case WEAPON_NOVA:
//	case WEAPON_XM1014:
//		return WEPCLASS_SHOTGUN;
//		break;
//	case WEAPON_KNIFE:
//	case WEAPON_KNIFE_BAYONET:
//	case WEAPON_KNIFE_BUTTERFLY:
//	case WEAPON_KNIFE_FALCHION:
//	case WEAPON_KNIFE_FLIP:
//	case WEAPON_KNIFE_GUT:
//	case WEAPON_KNIFE_KARAMBIT:
//	case WEAPON_KNIFE_TACTICAL:
//	case WEAPON_KNIFE_M9_BAYONET:
//	case WEAPON_KNIFE_PUSH:
//	case WEAPON_KNIFE_SURVIVAL_BOWIE:
//	case WEAPON_KNIFE_T:
//		return WEPCLASS_KNIFE;
//		break;
//
//	default:
//		return WEPCLASS_INVALID;
//	}
//}


class CMoveData {
public:
	bool			m_bFirstRunOfFunctions : 1;
	bool			m_bGameCodeMovedPlayer : 1;
	bool			m_bNoAirControl : 1;

	unsigned long	m_nPlayerHandle;
	int				m_nImpulseCommand;
	QAngle			m_vecViewAngles;
	QAngle			m_vecAbsViewAngles;
	int				m_nButtons;
	int				m_nOldButtons;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;

	float			m_flMaxSpeed;
	float			m_flClientMaxSpeed;

	Vector			m_vecVelocity;
	Vector			m_vecOldVelocity;
	float			somefloat;
	QAngle			m_vecAngles;
	QAngle			m_vecOldAngles;

	float			m_outStepHeight;
	Vector			m_outWishVel;
	Vector			m_outJumpVel;

	Vector			m_vecConstraintCenter;
	float			m_flConstraintRadius;
	float			m_flConstraintWidth;
	float			m_flConstraintSpeedFactor;
	bool			m_bConstraintPastRadius;

	void			SetAbsOrigin(const Vector &vec);
	const Vector	&GetAbsOrigin() const;

private:
	Vector			m_vecAbsOrigin;		// edict::origin
};


enum class CSGOClassID
{
	CAK47 = 1,
	CBaseAnimating = 2,
	CBaseAnimatingOverlay = 3,
	CBaseAttributableItem = 4,
	CBaseButton = 5,
	CBaseCombatCharacter = 6,
	CBaseCombatWeapon = 7,
	CBaseCSGrenade = 8,
	CBaseCSGrenadeProjectile = 9,
	CBaseDoor = 10,
	CBaseEntity = 11,
	CBaseFlex = 12,
	CBaseGrenade = 13,
	CBaseParticleEntity = 14,
	CBasePlayer = 15,
	CBasePropDoor = 16,
	CBaseTeamObjectiveResource = 17,
	CBaseTempEntity = 18,
	CBaseToggle = 19,
	CBaseTrigger = 20,
	CBaseViewModel = 21,
	CBaseVPhysicsTrigger = 22,
	CBaseWeaponWorldModel = 23,
	CBeam = 24,
	CBeamSpotlight = 25,
	CBoneFollower = 26,
	CBreakableProp = 27,
	CBreakableSurface = 28,
	CC4 = 29,
	CCascadeLight = 30,
	CChicken = 31,
	CColorCorrection = 32,
	CColorCorrectionVolume = 33,
	CCSGameRulesProxy = 34,
	CCSPlayer = 35,
	CCSPlayerResource = 36,
	CCSRagdoll = 37,
	CCSTeam = 38,
	CDEagle = 39,
	CDecoyGrenade = 40,
	CDecoyProjectile = 41,
	CDynamicLight = 42,
	CDynamicProp = 43,
	CEconEntity = 44,
	CEconWearable = 45,
	CEmbers = 46,
	CEntityDissolve = 47,
	CEntityFlame = 48,
	CEntityFreezing = 49,
	CEntityParticleTrail = 50,
	CEnvAmbientLight = 51,
	CEnvDetailController = 52,
	CEnvDOFController = 53,
	CEnvParticleScript = 54,
	CEnvProjectedTexture = 55,
	CEnvQuadraticBeam = 56,
	CEnvScreenEffect = 57,
	CEnvScreenOverlay = 58,
	CEnvTonemapController = 59,
	CEnvWind = 60,
	CFEPlayerDecal = 61,
	CFireCrackerBlast = 62,
	CFireSmoke = 63,
	CFireTrail = 64,
	CFish = 65,
	CFlashbang = 66,
	CFogController = 67,
	CFootstepControl = 68,
	CFunc_Dust = 69,
	CFunc_LOD = 70,
	CFuncAreaPortalWindow = 71,
	CFuncBrush = 72,
	CFuncConveyor = 73,
	CFuncLadder = 74,
	CFuncMonitor = 75,
	CFuncMoveLinear = 76,
	CFuncOccluder = 77,
	CFuncReflectiveGlass = 78,
	CFuncRotating = 79,
	CFuncSmokeVolume = 80,
	CFuncTrackTrain = 81,
	CGameRulesProxy = 82,
	CHandleTest = 83,
	CHEGrenade = 84,
	CHostage = 85,
	CHostageCarriableProp = 86,
	CIncendiaryGrenade = 87,
	CInferno = 88,
	CInfoLadderDismount = 89,
	CInfoOverlayAccessor = 90,
	CItem_Healthshot = 91,
	CItemDogtags = 92,
	CKnife = 93,
	CKnifeGG = 94,
	CLightGlow = 95,
	CMaterialModifyControl = 96,
	CMolotovGrenade = 97,
	CMolotovProjectile = 98,
	CMovieDisplay = 99,
	CParticleFire = 100,
	CParticlePerformanceMonitor = 101,
	CParticleSystem = 102,
	CPhysBox = 103,
	CPhysBoxMultiplayer = 104,
	CPhysicsProp = 105,
	CPhysicsPropMultiplayer = 106,
	CPhysMagnet = 107,
	CPlantedC4 = 108,
	CPlasma = 109,
	CPlayerResource = 110,
	CPointCamera = 111,
	CPointCommentaryNode = 112,
	CPointWorldText = 113,
	CPoseController = 114,
	CPostProcessController = 115,
	CPrecipitation = 116,
	CPrecipitationBlocker = 117,
	CPredictedViewModel = 118,
	CProp_Hallucination = 119,
	CPropDoorRotating = 120,
	CPropJeep = 121,
	CPropVehicleDriveable = 122,
	CRagdollManager = 123,
	CRagdollProp = 124,
	CRagdollPropAttached = 125,
	CRopeKeyframe = 126,
	CSCAR17 = 127,
	CSceneEntity = 128,
	CSensorGrenade = 129,
	CSensorGrenadeProjectile = 130,
	CShadowControl = 131,
	CSlideshowDisplay = 132,
	CSmokeGrenade = 133,
	CSmokeGrenadeProjectile = 134,
	CSmokeStack = 135,
	CSpatialEntity = 136,
	CSpotlightEnd = 137,
	CSprite = 138,
	CSpriteOriented = 139,
	CSpriteTrail = 140,
	CStatueProp = 141,
	CSteamJet = 142,
	CSun = 143,
	CSunlightShadowControl = 144,
	CTeam = 145,
	CTeamplayRoundBasedRulesProxy = 146,
	CTEArmorRicochet = 147,
	CTEBaseBeam = 148,
	CTEBeamEntPoint = 149,
	CTEBeamEnts = 150,
	CTEBeamFollow = 151,
	CTEBeamLaser = 152,
	CTEBeamPoints = 153,
	CTEBeamRing = 154,
	CTEBeamRingPoint = 155,
	CTEBeamSpline = 156,
	CTEBloodSprite = 157,
	CTEBloodStream = 158,
	CTEBreakModel = 159,
	CTEBSPDecal = 160,
	CTEBubbles = 161,
	CTEBubbleTrail = 162,
	CTEClientProjectile = 163,
	CTEDecal = 164,
	CTEDust = 165,
	CTEDynamicLight = 166,
	CTEEffectDispatch = 167,
	CTEEnergySplash = 168,
	CTEExplosion = 169,
	CTEFireBullets = 170,
	CTEFizz = 171,
	CTEFootprintDecal = 172,
	CTEFoundryHelpers = 173,
	CTEGaussExplosion = 174,
	CTEGlowSprite = 175,
	CTEImpact = 176,
	CTEKillPlayerAttachments = 177,
	CTELargeFunnel = 178,
	CTEMetalSparks = 179,
	CTEMuzzleFlash = 180,
	CTEParticleSystem = 181,
	CTEPhysicsProp = 182,
	CTEPlantBomb = 183,
	CTEPlayerAnimEvent = 184,
	CTEPlayerDecal = 185,
	CTEProjectedDecal = 186,
	CTERadioIcon = 187,
	CTEShatterSurface = 188,
	CTEShowLine = 189,
	CTesla = 190,
	CTESmoke = 191,
	CTESparks = 192,
	CTESprite = 193,
	CTESpriteSpray = 194,
	CTest_ProxyToggle_Networkable = 194,
	CTestTraceline = 196,
	CTEWorldDecal = 197,
	CTriggerPlayerMovement = 198,
	CTriggerSoundOperator = 199,
	CVGuiScreen = 200,
	CVoteController = 201,
	CWaterBullet = 202,
	CWaterLODControl = 203,
	CWeaponAug = 204,
	CWeaponAWP = 205,
	CWeaponBaseItem = 206,
	CWeaponBizon = 207,
	CWeaponCSBase = 208,
	CWeaponCSBaseGun = 209,
	CWeaponCycler = 210,
	CWeaponElite = 211,
	CWeaponFamas = 212,
	CWeaponFiveSeven = 213,
	CWeaponG3SG1 = 214,
	CWeaponGalil = 215,
	CWeaponGalilAR = 216,
	CWeaponGlock = 217,
	CWeaponHKP2000 = 218,
	CWeaponM249 = 219,
	CWeaponM3 = 220,
	CWeaponM4A1 = 221,
	CWeaponMAC10 = 222,
	CWeaponMag7 = 223,
	CWeaponMP5Navy = 224,
	CWeaponMP7 = 225,
	CWeaponMP9 = 226,
	CWeaponNegev = 227,
	CWeaponNOVA = 228,
	CWeaponP228 = 229,
	CWeaponP250 = 230,
	CWeaponP90 = 231,
	CWeaponSawedoff = 232,
	CWeaponSCAR20 = 233,
	CWeaponScout = 234,
	CWeaponSG550 = 235,
	CWeaponSG552 = 236,
	CWeaponSG556 = 237,
	CWeaponSSG08 = 238,
	CWeaponTaser = 239,
	CWeaponTec9 = 240,
	CWeaponTMP = 241,
	CWeaponUMP45 = 242,
	CWeaponUSP = 243,
	CWeaponXM1014 = 244,
	CWorld = 245,
	DustTrail = 246,
	MovieExplosion = 247,
	ParticleSmokeGrenade = 248,
	RocketTrail = 249,
	SmokeTrail = 250,
	SporeExplosion = 251,
	SporeTrail = 252
};