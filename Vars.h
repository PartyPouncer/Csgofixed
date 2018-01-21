#pragma once
#include <unordered_map>

struct AimbotWeaponConfig_
{

	bool Enabled;
	bool    Silent;
	int 	Key;
	bool	OnKey;
	int 	Filter;
	bool 	RCS2;
	float 	RCSAmount;
	float   RCSAMT;
	float	Speed;
	bool 	VisCheck;
	int 	Hitbox;
	float 	FOV;
	bool 	AlwaysOn;
	bool	FriendlyFire;
	bool    Faceitmode;
};

struct Variables
{
	Variables()
	{

	}

	struct Ragebot_s
	{
		bool 	Enabled;
		bool    Norecoil;
		bool 	AutoFire;
		bool 	Hold;
		int 	HoldKey;
		int     Resolvermode;
		bool    Pitchfix;
		int 	Filter; // will hold flags for team/enemy/etc.
		int     bomber;
		bool 	Silent;
		bool    WeaponCFGRage;
		bool    usemaus;
		bool	RCS;
		bool 	VisCheck;
		bool 	AutoWall;
		float	AutoWallDmg;
		int 	TargetMethod;
		int		Hitbox;
		float 	FOV;
		bool 	HitChance;
		float	HitChanceAmt;
		bool    AutoScope;
		bool 	AutoStop;
		bool 	AutoCrouch;
		bool    FakeDuck;
		bool 	FriendlyFire;
		bool	Aimstep;
		bool    BackTrack;
		float	AimstepAmount;
		bool	HitScanAll;
		bool	HitScanPerformance;
		bool    PreferHitbox;
		bool    AAA;
		bool    velprediction;
		bool    Pseudonospread;
		bool    PVSFix;
		bool    Multipoint;
		float   Multipointintense;
		float   Multipointscale;
		bool    Fakeanglefix;
		bool    Fakeanglefixadv;
		bool    Fakeanglefixbeta;
		bool    FakeLagfix;
		bool	HitScanHitbox;
		bool	SmartHitbox;
		int		SmartHitboxHealth;
		bool	UntrustedCheck;
		struct
		{
			bool	Enabled;
			int		Pitch;
			int		FakeYaw;
			int     RealYaw;
			bool	AimAtPlayer;
			bool	DetectEdge;
			bool    FakeEdge;
			bool    HasNoEnemy;
			bool    Shuffle;
			bool    AntiResolver;
			bool    flipAAonhit;
			bool	PSilent;
		} Antiaim;
	} Ragebot;

	struct
	{
		struct
		{
			bool 	Enabled;
			bool    Silent;
			bool    MaxSpeed;
			int 	Key;
			bool	OnKey;
			int 	Filter; // will hold flags for team/enemy/etc.
			bool 	RCS;
			bool    legitaa;
			bool    LegitBacktrack;
			float 	RCSAmount;
			float   RCSAMT;
			float	Speed;
			float   Ticks;
			bool 	VisCheck;
			bool    Smokecheck;
			bool 	Weaponcfg;
			bool 	SaveWeaponcfg;
			int 	Hitbox;
			float 	FOV;
			bool 	AlwaysOn;
			bool	FriendlyFire;
			bool    Faceitmode;
			bool    Fastzoom;
			bool    FastzoomSwitch;
		} Aimbot;

		struct
		{
			bool	Enabled;
			bool    SmokeCheck;
			bool	AutoFire;
			int		Key;
			bool 	HitChance;
			float	HitChanceAmt;

			struct
			{
				bool Head;
				bool Chest;
				bool Stomach;
				bool Arms;
				bool Legs;
				bool Friendly;
			} Filter;

		} Triggerbot;

	} Legitbot;

	struct
	{
		bool 	Enabled;
		bool 	Box;
		bool    Cornerbox;
		bool    None;
		int 	BoxType;
		int     bomber;
		bool    Hitmarker;
		bool    Hitmarkersound;
		bool    FakeAAChams;
		bool    DLight;
		bool    RainbowDlight;
		bool	Skeleton;
		bool    LastPos;
		bool    DrawHitbox;
		bool    DrawMultipints;
		bool	Glow;
		bool	BulletTrace;
		bool    Scoutjumpshot;
		bool    pSpecList;
		bool    BackTrack;
		bool    HitBoxDot;
		float   BulletTraceLength;
		float   FOVAdd;
		
		float   DLightRadius;
		bool	CrosshairOn;
		int		CrosshairType;
		int		CrosshairStyle;
		bool    CrosshairSpread;
		bool    CrosshairFOV;
		float 	TeamColor[ 3 ];			
		float 	TeamColorWall[ 3 ];
		float 	EnemyColor[ 3 ];
		float 	EnemyColorWall[ 3 ];
		struct
		{
			bool Enemies;
			bool Friendlies;
			bool Weapons;
			bool DrawWeapon;
			bool Hostage;
			bool Nades;
			bool Chickens;
			bool C4;
		} Filter;

		struct
		{
			bool	Enabled;
			bool    Rainbow;
			int 	Mode;
			bool	XQZ;
			bool    Fake;
			float 	TeamColor[ 3 ];
			float 	TeamColorWall[ 3 ];
			float  	EnemyColor[ 3 ];
			float 	EnemyColorWall[ 3 ];
		} Chams;

		struct
		{
			bool 	Name;
			bool    LBY;
			bool 	Health;
			bool 	Weapon;
			bool    DrawWeapon;
			bool    RankESP;
			bool    Hostage;
			bool	Flashed;
			float    AlphaFade;
		} Info;

		struct
		{
			bool	WireframeHands;
			bool	Hands;
			bool	Weapon;
			bool	VisualRecoil;
			bool	Flash;
			bool    RaveSky;
			bool    NightMode;
			bool    Hitmarker;
			bool    Scope;
			bool    Postprocess;
			bool	Sky;
		} Removals;
	} Visuals;

	struct
	{
		bool 	Bhop;
		bool    AutoRevovler;
		bool 	AutoStrafe;
		bool    RageAutoStrafe;
		bool    CircleStrafer;
		bool    svcheats;
		bool    hakenkreuz;
		bool    undosvcheats;
		bool    RemoveScope;
		bool	ChatSpam;
		int		ChatSpamMode;
		bool	Watermark;
		bool    Timestamp;
		bool	Ranks;
		int m_iRand = rand() % 4 + 1;
		bool	AirStuck;
		bool    AutoPistol;
		bool    moonwalk;
		bool    NameHide;
		bool    NameSpammer;
		bool    NameSpammer2;
		bool    NameStealer;
		bool    Teleport;
		bool    MTeleport;
		bool    LocationSpam;
		bool    SetClanTag;
		bool    AutoBlocker;
		bool    fakelag;
		int     fakelagchoke;
		int     fakelagsend;
		bool    Walkbot;
		bool    thirdperson;
		int thirdpersonkey;
		int		AirStuckKey;
		int     TeleportKey;
		int     AutoblockerKey;
		int     FakewalkKey;
		bool    FakeWalk;
		bool	AutoAccept;
		bool    aniclantag;
		char	clantagbuffer[128] = "FH4x";
		char	tag_chars[10] = "/-\\|";
		int		interval;
		int		interval_end;
		bool   placeholder;
	} Misc;

	struct
	{
		bool bKnife;
		int	iKnife;
	} Skins;

	struct
	{
		bool use;
		int Player[64];
		bool Playeralone;
	} Playerlist;

	struct
	{
		bool	Opened = false;
		int 	Key;
		bool	Ragebot = false;
		bool	Legitbot = false;
		bool	Visual = false;
		bool	Misc = false;
		bool    Playerlist = false;
		bool	Skins = false;
	} Menu;

};

extern AimbotWeaponConfig_ AimbotWeaponConfig;
extern Variables Vars;