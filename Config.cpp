#include "Cheat.h"

void CConfig::Setup()
{
	SetupValue( Vars.Ragebot.Enabled, false, strenc( "Ragebot" ), strenc( "Enabled" ) );
	SetupValue(Vars.Ragebot.WeaponCFGRage, false, strenc("Ragebot"), strenc("WeaponCFGRage"));
	SetupValue( Vars.Ragebot.AutoFire, false, strenc( "Ragebot" ), strenc( "AutoFire" ) );
	SetupValue( Vars.Ragebot.Hold, false, strenc( "Ragebot" ), strenc( "Hold" ) );
	SetupValue( Vars.Ragebot.HoldKey, 0, strenc( "Ragebot" ), strenc( "HoldKey" ) );
	SetupValue( Vars.Ragebot.Silent, true, strenc( "Ragebot" ), strenc( "Silent" ) );
	SetupValue( Vars.Ragebot.Hitbox, 6, strenc( "Ragebot" ), strenc( "Hitbox" ) );
	SetupValue(Vars.Ragebot.PreferHitbox, false, strenc("Ragebot"), strenc("PreferHitbox"));
	SetupValue(Vars.Ragebot.AAA, false, strenc("Ragebot"), strenc("AAA"));
	SetupValue(Vars.Ragebot.Fakeanglefix, false, strenc("Ragebot"), strenc("fakeanglefix"));
	SetupValue( Vars.Ragebot.FriendlyFire, false, strenc( "Ragebot" ), strenc( "FriendlyFire" ) );
	SetupValue( Vars.Ragebot.AutoStop, false, strenc( "Ragebot" ), strenc( "AutoStop" ) );
	SetupValue( Vars.Ragebot.AutoScope, false, strenc("Ragebot"), strenc("AutoScope"));
	SetupValue(Vars.Misc.AutoRevovler, false, strenc("Misc"), strenc("AutoRevolver"));
	SetupValue( Vars.Ragebot.AutoCrouch, false, strenc( "Ragebot" ), strenc( "AutoCrouch" ) );
	SetupValue( Vars.Ragebot.AutoWall, true, strenc( "Ragebot" ), strenc( "AutoWall" ) );
	SetupValue( Vars.Ragebot.AutoWallDmg, 10.f, strenc( "Ragebot" ), strenc( "AutoWallDamage" ) );
	SetupValue(Vars.Ragebot.SmartHitbox, false, strenc("Ragebot"), strenc("SmartHitbox"));
	SetupValue(Vars.Ragebot.SmartHitboxHealth, 25.f, strenc("Ragebot"), strenc("Smarthitboxminhealth"));
	SetupValue( Vars.Ragebot.HitChance, false, strenc( "Ragebot" ), strenc( "HitChance" ) );
	SetupValue(Vars.Ragebot.FakeLagfix, false, strenc("Ragebot"), strenc("FakeLagFix"));
	SetupValue( Vars.Ragebot.HitChanceAmt, 26.f, strenc( "Ragebot" ), strenc( "HitChanceAmount" ) );
	SetupValue( Vars.Ragebot.Aimstep, false, strenc( "Ragebot" ), strenc( "Aimstep" ) );
	SetupValue(Vars.Ragebot.BackTrack, false, strenc("Ragebot"), strenc("BackTrack"));
	SetupValue( Vars.Ragebot.AimstepAmount, 15.f, strenc( "Ragebot" ), strenc( "AimstepAmount" ) );
	SetupValue(Vars.Ragebot.HitScanPerformance, false, strenc("Ragebot"), strenc("HitScanNormal"));
	SetupValue(Vars.Ragebot.Multipoint, false, strenc("Ragebot"), strenc("MultiPoint"));
	/*SetupValue(Vars.Ragebot.Multipointintense, 5.f, strenc("Ragebot"), strenc("multipointsintense"));*/
	SetupValue(Vars.Ragebot.Multipointscale, 0.8f, strenc("Ragebot"), strenc("multipointscale"));
	SetupValue(Vars.Ragebot.Pseudonospread, false, strenc("Ragebot"), strenc("pseudospread"));
	SetupValue(Vars.Ragebot.PVSFix, false, strenc("Ragebot"), strenc("PVS"));
	SetupValue( Vars.Ragebot.UntrustedCheck, true, strenc( "Ragebot" ), strenc( "Anti-Untrust" ) );
	SetupValue( Vars.Ragebot.Antiaim.Enabled, false, strenc( "Ragebot" ), strenc( "AntiaimEnabled" ) );
	SetupValue( Vars.Ragebot.Antiaim.Pitch, 0, strenc( "Ragebot" ), strenc( "AntiaimPitch" ) );
	SetupValue( Vars.Ragebot.Antiaim.FakeYaw, 0, strenc( "Ragebot" ), strenc( "AntiaimYaw" ) );
	SetupValue(Vars.Ragebot.Antiaim.AimAtPlayer, true, strenc("Ragebot"), strenc("At Players"));
	SetupValue(Vars.Ragebot.Antiaim.Shuffle, true, strenc("Ragebot"), strenc("Shuffle"));
	//SetupValue(Vars.Ragebot.Antiaim.DetectEdge, false, strenc("Ragebot"), strenc("Detect Edge"));
	//SetupValue(Vars.Ragebot.Fakeanglefix, false, strenc("Ragebot"), strenc("FakeAnglefix"));
	//SetupValue(Vars.Ragebot.Fakeanglefixadv, false, strenc("Ragebot"), strenc("FakeAnglefixadv"));
	//SetupValue(Vars.Ragebot.Fakeanglefixbeta, false, strenc("Ragebot"), strenc("FakeAnglefixbeta"));



	SetupValue( Vars.Legitbot.Aimbot.Enabled, true, strenc( "Legitbot" ), strenc( "Enabled" ) );
	SetupValue( Vars.Legitbot.Aimbot.AlwaysOn, false, strenc( "Legitbot" ), strenc( "AlwaysOn" ) );
	SetupValue(Vars.Legitbot.Aimbot.Weaponcfg, false, strenc("Legitbot"), strenc("weaponconfig"));
	SetupValue( Vars.Legitbot.Aimbot.Key, 0, strenc( "Legitbot" ), strenc( "Key" ) );
	SetupValue( Vars.Legitbot.Aimbot.OnKey, false, strenc( "Legitbot" ), strenc( "OnKey" ) );
	SetupValue( Vars.Legitbot.Aimbot.FriendlyFire, false, strenc( "Legitbot" ), strenc( "FriendlyFire" ) );
	SetupValue(Vars.Legitbot.Aimbot.Silent, false, strenc("Legitbot"), strenc("pSilent"));
	SetupValue(Vars.Legitbot.Aimbot.MaxSpeed, false, strenc("Legitbot"), strenc("MaxSpeed"));
	SetupValue( Vars.Legitbot.Aimbot.Hitbox, 6, strenc( "Legitbot" ), strenc( "Hitbox" ) );
	SetupValue( Vars.Legitbot.Aimbot.FOV, 10.f, strenc( "Legitbot" ), strenc( "FOV" ) );
	SetupValue( Vars.Legitbot.Aimbot.Speed, 5.f, strenc( "Legitbot" ), strenc( "Speed" ) );
	SetupValue( Vars.Legitbot.Aimbot.RCS, false, strenc( "Legitbot" ), strenc( "RCS" ) );
	SetupValue( Vars.Legitbot.Aimbot.RCSAmount, 100.f, strenc( "Legitbot" ), strenc( "RCSAmount" ) );
	SetupValue(Vars.Legitbot.Aimbot.LegitBacktrack, true, strenc("Legitbot"), strenc("LegitBackTrack"));
	SetupValue(Vars.Legitbot.Aimbot.Ticks, 12.f, strenc("Legitbot"), strenc("Ticks"));
	SetupValue(Vars.Legitbot.Aimbot.Faceitmode, true, strenc("Legitbot"), strenc("UseMouseEvent"));
	SetupValue(Vars.Legitbot.Aimbot.Smokecheck, true, strenc("Legitbot"), strenc("Smokecheck"));
	SetupValue(Vars.Legitbot.Aimbot.Fastzoom, false, strenc("Legitbot"), strenc("fastzoom"));
	SetupValue(Vars.Legitbot.Aimbot.FastzoomSwitch, false, strenc("Legitbot"), strenc("fastzoomswitch"));

	SetupValue( Vars.Legitbot.Triggerbot.Enabled, false, strenc( "Triggerbot" ), strenc( "Enabled" ) );
	SetupValue( Vars.Legitbot.Triggerbot.AutoFire, false, strenc( "Triggerbot" ), strenc( "AutoFire" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Key, 0, strenc( "Triggerbot" ), strenc( "Key" ) );
	SetupValue( Vars.Legitbot.Triggerbot.HitChance, false, strenc( "Triggerbot" ), strenc( "HitChance" ) );
	SetupValue( Vars.Legitbot.Triggerbot.HitChanceAmt, 60.f, strenc( "Triggerbot" ), strenc( "HitChanceAmt" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Head, false, strenc( "Triggerbot" ), strenc( "Head" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Chest, false, strenc( "Triggerbot" ), strenc( "Chest" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Stomach, false, strenc( "Triggerbot" ), strenc( "Stomach" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Arms, false, strenc( "Triggerbot" ), strenc( "Arms" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Legs, false, strenc( "Triggerbot" ), strenc( "Legs" ) );
	SetupValue( Vars.Legitbot.Triggerbot.Filter.Friendly, false, strenc( "Triggerbot" ), strenc( "Friendly" ) );

	SetupValue( Vars.Visuals.Enabled, true, strenc( "Visuals" ), strenc( "Enabled" ) );
	SetupValue( Vars.Visuals.Skeleton, false, strenc( "Visuals" ), strenc( "Skeleton" ) );
	SetupValue(Vars.Visuals.DrawHitbox, false, strenc("Visuals"), strenc("Hitbox"));
	SetupValue( Vars.Visuals.BulletTrace, false, strenc( "Visuals" ), strenc( "BulletTrace" ) );
	SetupValue(Vars.Visuals.BoxType, 1, strenc("Visuals"), strenc("BoxType"));
	SetupValue( Vars.Visuals.BulletTraceLength, 100.f, strenc( "Visuals" ), strenc( "BulletTraceLength" ) );
	SetupValue(Vars.Visuals.FOVAdd, 0.f, strenc("Visuals"), strenc("Fov"));
	SetupValue( Vars.Visuals.Glow, false, strenc( "Visuals" ), strenc( "Glow" ) );
	SetupValue( Vars.Visuals.CrosshairOn, false, strenc( "Visuals" ), strenc( "CrosshairOn" ) );
	SetupValue(Vars.Visuals.CrosshairSpread, false, strenc("Visuals"), strenc("SpreadCrosshair"));
	SetupValue(Vars.Visuals.CrosshairFOV, false, strenc("Visuals"), strenc("FOVCrosshair"));
	SetupValue( Vars.Visuals.CrosshairType, 0, strenc( "Visuals" ), strenc( "CrosshairType" ) );
	SetupValue( Vars.Visuals.CrosshairStyle, 0, strenc( "Visuals" ), strenc( "CrosshairStyle" ) );
	SetupValue( Vars.Visuals.Info.Name, true, strenc( "Visuals" ), strenc( "Name" ) );
	SetupValue(Vars.Visuals.Info.LBY, true, strenc("Visuals"), strenc("LBY"));
	SetupValue( Vars.Visuals.Info.Health, true, strenc( "Visuals" ), strenc( "Health" ) );
	SetupValue( Vars.Visuals.Info.Weapon, true, strenc( "Visuals" ), strenc( "Weapon" ) );
	SetupValue(Vars.Visuals.Info.DrawWeapon, true, strenc("Visuals"), strenc("Weapon Icon"));
	SetupValue( Vars.Visuals.Info.Flashed, true, strenc( "Visuals" ), strenc( "Flashed" ) );
	SetupValue( Vars.Visuals.Filter.Enemies, true, strenc( "Visuals" ), strenc( "Enemies" ) );
	SetupValue( Vars.Visuals.Filter.Friendlies, false, strenc( "Visuals" ), strenc( "Friendlies" ) );
	SetupValue(Vars.Visuals.Info.Hostage, true, strenc("Visuals"), strenc("Hostages"));
	SetupValue( Vars.Visuals.Filter.Weapons, true, strenc( "Visuals" ), strenc( "Weapons" ) );
	SetupValue( Vars.Visuals.Filter.Nades, true, strenc( "Visuals" ), strenc( "Decoy" ) );
	SetupValue( Vars.Visuals.Filter.C4, true, strenc( "Visuals" ), strenc( "C4" ) );
	SetupValue(Vars.Visuals.Filter.Chickens, true, strenc("Visuals"), strenc("Chickens"));
	SetupValue( Vars.Visuals.Chams.Enabled, true, strenc( "Visuals" ), strenc( "ChamsEnabled" ) );
	SetupValue( Vars.Visuals.Chams.Mode, 0, strenc( "Visuals" ), strenc( "ChamsMode" ) );
	SetupValue( Vars.Visuals.Chams.XQZ, true, strenc( "Visuals" ), strenc( "ChamsXQZ" ) );
	SetupValue(Vars.Visuals.Chams.Rainbow, false, strenc("Visuals"), strenc("ChamsRainbow"));
	SetupValue( Vars.Visuals.Removals.Hands, false, strenc( "Visuals" ), strenc( "No Hands" ) );
	SetupValue(Vars.Visuals.Removals.Postprocess, false, strenc("Visuals"), strenc("PostProcess"));
	SetupValue(Vars.Visuals.Removals.NightMode, false, strenc("Visuals"), strenc("NightMode"));
	SetupValue(Vars.Visuals.Removals.WireframeHands, false, strenc("Visuals"), strenc("WireframeHands"));
	SetupValue( Vars.Visuals.Removals.Weapon, false, strenc( "Visuals" ), strenc( "No Weapon" ) );
	SetupValue( Vars.Visuals.Removals.VisualRecoil, false, strenc( "Visuals" ), strenc( "No Recoil" ) );
	SetupValue( Vars.Visuals.Removals.Flash, false, strenc( "Visuals" ), strenc( "No Flash" ) );
	SetupValue(Vars.Visuals.Removals.Scope, false, strenc("Visuals"), strenc("No Scope"));
	SetupValue(Vars.Visuals.Hitmarker, false, strenc("Visuals"), strenc("Hitmarker"));
	SetupValue(Vars.Visuals.Hitmarkersound, false, strenc("Visuals"), strenc("HitmarkerSound"));
	SetupValue(Vars.Visuals.DLight, false, strenc("Visuals"), strenc("DLight"));
	SetupValue(Vars.Visuals.DLightRadius, 100.f, strenc("Visuals"), strenc("DLightRadius"));
	SetupValue(Vars.Visuals.RainbowDlight, false, strenc("Visuals"), strenc("RainbowDLight"));
	SetupValue(Vars.Visuals.pSpecList, false, strenc("Visuals"), strenc("specatorlist"));
	SetupValue(Vars.Visuals.BackTrack, false, strenc("Visuals"), strenc("BackTrack"));
	SetupValue(Vars.Visuals.Removals.RaveSky, false, strenc("Visuals"), strenc("ravesky"));
	SetupValue(Vars.Visuals.Removals.NightMode, false, strenc("Visuals"), strenc("nightmode"));



	SetupValue( Vars.Misc.Bhop, true, strenc( "Misc" ), strenc( "Bhop" ) );
	SetupValue( Vars.Misc.AutoStrafe, false, strenc( "Misc" ), strenc( "AutoStrafe" ) );
	SetupValue(Vars.Misc.RageAutoStrafe, false, strenc("Misc"), strenc("RageStrafer"));
	SetupValue( Vars.Misc.Watermark, true, strenc( "Misc" ), strenc( "Watermark" ) );
	SetupValue(Vars.Misc.Timestamp, true, strenc("Misc"), strenc("Time"));
	SetupValue( Vars.Misc.Ranks, true, strenc( "Misc" ), strenc( "Ranks" ) );
	SetupValue(Vars.Misc.thirdperson, false, strenc("Misc"), strenc("thirdperson"));
	SetupValue( Vars.Misc.AutoAccept, true, strenc( "Misc" ), strenc( "AutoAccept" ) );
	SetupValue(Vars.Misc.AutoPistol, false, strenc("Misc"), strenc("AutoPistol"));
	SetupValue( Vars.Misc.AirStuck, false, strenc( "Misc" ), strenc( "AirStuck" ) );
	SetupValue( Vars.Misc.AirStuckKey, 0, strenc( "Misc" ), strenc( "AirStuckKey" ) );
	SetupValue(Vars.Misc.moonwalk, false, strenc("Misc"), strenc("Moonwalk"));
	SetupValue(Vars.Misc.NameHide, false, strenc("Misc"), strenc("Name Hide"));
	SetupValue(Vars.Misc.aniclantag, false, strenc("Misc"), strenc("Animated Clantg"));
	/*SetupValue(Vars.Misc.clantagbuffer, 128, strenc("Misc"), strenc("clantagbuffer"));
	SetupValue(Vars.Misc.tag_chars, 128, strenc("Misc"), strenc("tag-chars"));*/
	SetupValue(Vars.Misc.interval, 15, strenc("Misc"), strenc("Start Interval"));
	SetupValue(Vars.Misc.interval_end, 50, strenc("Misc"), strenc("End Interval"));
	SetupValue(Vars.Misc.LocationSpam, false, strenc("Misc"), strenc("Location Spam"));
	SetupValue(Vars.Misc.Teleport, false, strenc("Misc"), strenc("Teleport"));
	SetupValue(Vars.Misc.TeleportKey, 0, strenc("Misc"), strenc("TeleportKey"));
	SetupValue(Vars.Misc.FakeWalk, false, strenc("Misc"), strenc("fakewalk"));
	SetupValue(Vars.Misc.FakewalkKey, 0, strenc("Misc"), strenc("fakewalkKey"));
	SetupValue(Vars.Misc.AutoBlocker, false, strenc("Misc"), strenc("AutoBlocker"));
	SetupValue(Vars.Misc.AutoblockerKey, 0, strenc("Misc"), strenc("AutoBlockerKey"));
	SetupValue(Vars.Misc.fakelag, false, strenc("Misc"), strenc("FakeLag"));
	SetupValue(Vars.Misc.fakelagchoke, 9.f, strenc("Misc"), strenc("FakeLagChoke"));
	SetupValue(Vars.Misc.fakelagsend, 5.f, strenc("Misc"), strenc("FakeLagSend"));

}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue<bool>(category, name, &value));
}

void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + strenc("\\FH4x\\");
		file = std::string(path) + strenc("\\FH4x\\FH4x.ini");
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + strenc("\\FH4x\\");
		file = std::string(path) + strenc("\\FH4x\\FH4x.ini");
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}


AimbotWeaponConfig_ AimbotWeaponConfig;

CConfig* Config = new CConfig();
Variables Vars;