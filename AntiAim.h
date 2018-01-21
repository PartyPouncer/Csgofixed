#pragma once

enum AA_Pitch
{
	AA_PITCH_RANDOM,
	AA_PITCH_DANCE,
	AA_PITCH_EMOTION,
	AA_PITCH_HIDE,
	AA_PITCH_DOWN,
	AA_PITCH_FAKE_DOWN,
	AA_PITCH_UP,
	AA_PITCH_STATIC,
	AA_PITCH_OFF
};

enum AA_Yaw
{
	AA_YAW_RANDOM,
	AA_YAW_FAKERANDOM,
	AA_YAW_NORMAL,
	AA_YAW_FAKEBACKWARD,
	AA_YAW_JITTER,
	AA_YAW_FAKEJITTER,
	AA_YAW_FAKEJITTER2,
	AA_YAW_JITTER_SYNCED,
	AA_YAW_SPINHACK,
	AA_YAW_SIDEWAYS,
	AA_YAW_STATIC,
	AA_YAW_FAKE_SIDEWAYS,
	AA_YAW_FAKE_STATIC,
	AA_YAW_FAKE_SPIN,
	AA_YAW_KIDUA,
	AA_YAW_SIDE,
	AA_YAW_FH4X,
	AA_YAW_LBYBREAK,
	AA_YAW_FAKE2,
	AA_YAW_LAGSPIN,
	AA_YAW_ADD90FAKE,
	AA_YAW_OFF


};

class CAntiAim
{
public:
	
	/*void Run();*/
	void Run(CUserCmd * pCmd, bool & bSendPacket);
	
	
private:
	void aimAtPlayer(CUserCmd * pCmd);
	/*void antiAimYaw();*/
	void aimAtPlayer();
	//bool DetectEdge(CBaseEntity * pLocalBaseEntity, CUserCmd * cmd, float flWall, float flCornor);
	void DoAntiAim(CUserCmd * pCmd, bool & bSendPacket);
};

extern CAntiAim* AntiAim;
