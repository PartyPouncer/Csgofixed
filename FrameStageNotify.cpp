#include "Cheat.h"
#include "FrameStageNotify.h"

struct PlayerAA
{
	CBaseEntity* player;
	QAngle angle;

	PlayerAA(CBaseEntity* player, QAngle angle)
	{
		this->player = player;
		this->angle = angle;
	}
};

namespace LBYthings
{
	float OldYawDeltasX[64];
	float OldLowerBodyYawsX[64];
	float flTemp[64];
	float resolved_yaw[64];

	float LastLBYUpdateTime;
	float LastLBYUpdateTimeEnemy;

	float GetLatency()
	{
		INetChannelInfo *nci = I::Engine->GetNetChannelInfo();
		if (nci)
		{
			float Latency = nci->GetAvgLatency(2) + nci->GetAvgLatency(1);
			return Latency;
		}
		else
		{
			return 0.0f;
		}
	}

	bool NextLBYUpdate()
	{
		static float OldLBY = 0.f;
		float flServerTime = I::Globals->curtime;
		static int LBYBreakerTimer = 0;

		if (OldLBY != G::LocalPlayer->GetLowerBodyTarget())
		{
			LBYBreakerTimer++;
			OldLBY = G::LocalPlayer->GetLowerBodyTarget();
			LastLBYUpdateTime = flServerTime;
		}

		if (G::LocalPlayer->GetVelocity().Length2D() > /*10.5f*/0.1f && G::LocalPlayer->GetFlags() & FL_ONGROUND)
		{
			LastLBYUpdateTime = flServerTime;
			return true;
		}


		if ((LastLBYUpdateTime + 1 - (GetLatency() * 2) < flServerTime) && (G::LocalPlayer->GetFlags() & FL_ONGROUND))
		{
			if (LastLBYUpdateTime + 1.1 - (GetLatency() * 2) < flServerTime)
			{
				LastLBYUpdateTime += 1.1;
			}
			return true;
		}

		return false;
	}
	bool NextLBYUpdateEnemy()
	{
		float OldLBY = 0.f;
		float flServerTime = I::Globals->curtime;
		static int LBYBreakerTimer = 0;
		for (int i = 0; i <= I::Globals->maxClients; i++)
		{
			CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);

			if (Entity == NULL)
				continue;

			if (Entity == G::LocalPlayer)
				continue;

			if ((Entity->GetTeam() == G::LocalPlayer->GetTeam()) || Entity->GetDormant() || !Entity->GetAlive() || Entity->GetHealth() <= 0)
				continue;

			if (OldLBY != Entity->GetLowerBodyTarget())
			{
				LBYBreakerTimer++;
				OldLBY = Entity->GetLowerBodyTarget();
				LastLBYUpdateTimeEnemy = flServerTime;
			}

			if (Entity->GetVelocity().Length2D() > 0.1f && Entity->GetFlags() & FL_ONGROUND)
			{
				LastLBYUpdateTimeEnemy = flServerTime;
				return true;
			}


			if ((LastLBYUpdateTimeEnemy + 1.f - (GetLatency() * 2.f) < flServerTime) && (Entity->GetFlags() & FL_ONGROUND))
			{
				if (LastLBYUpdateTimeEnemy + 1.1f - (GetLatency() * 2.f) < flServerTime)
				{
					LastLBYUpdateTimeEnemy += 1.1f;
				}
				return true;
			}

			return false;
		}
	}
	void lbydelta(CBaseEntity* ent)
	{
		float flYaw;

		float LowerYaw = ent->GetLowerBodyTarget();
		int index = ent->GetIndex();

		if (OldLowerBodyYawsX[index] != LowerYaw)
		{
			OldYawDeltasX[index] = LowerYaw - OldLowerBodyYawsX[index];
			OldLowerBodyYawsX[index] = LowerYaw;

			if (ent->GetVelocity().Length2D() > 0.1f && ent->GetFlags() & FL_ONGROUND)
			{
				flTemp[index] = LowerYaw;
				OldLowerBodyYawsX[index] = LowerYaw;
			}
			else
			{
				flTemp[index] = OldLowerBodyYawsX[index];
			}
		}
		else
		{
			flTemp[index] = LowerYaw - OldYawDeltasX[index];
		}

		float FixedResolve = flTemp[index];

		if (G::LastLBYUpdateEnemy)
		{
			flYaw = FixedResolve;
		}
		else
		{
			if (LastLBYUpdateTimeEnemy <= 0.57f && LastLBYUpdateTimeEnemy >= 0.27f) // if it wasnt long ago that lby updated, just check nearby
			{
				resolved_yaw[index] = FixedResolve + U::RandomFloat(-35, 35);
			}
			else // if its getting old info, check in a wider area
			{
				resolved_yaw[index] = FixedResolve + U::RandomFloat(-90, 90);
			}
			flYaw = resolved_yaw[index];
		}

		ent->GetHeadRotation()->y = flYaw;
	}
	void lbydelta2(CBaseEntity* ent)
	{
		float flYaw;

		float LowerYaw = ent->GetLowerBodyTarget();
		int index = ent->GetIndex();

		if (OldLowerBodyYawsX[index] != LowerYaw)
		{
			OldYawDeltasX[index] = LowerYaw - OldLowerBodyYawsX[index];
			OldLowerBodyYawsX[index] = LowerYaw;

			if (ent->GetVelocity().Length2D() > 0.1f && ent->GetFlags() & FL_ONGROUND)
			{
				flTemp[index] = LowerYaw;
				OldLowerBodyYawsX[index] = LowerYaw;
			}
			else
			{
				flTemp[index] = OldLowerBodyYawsX[index];
			}
		}
		else
		{
			flTemp[index] = LowerYaw - OldYawDeltasX[index];
		}

		float FixedResolve = flTemp[index];

		if (G::LastLBYUpdate)
		{
			flYaw = FixedResolve;
		}
		else
		{
			if (LastLBYUpdateTime <= 0.57f && LastLBYUpdateTime >= 0.27f) // if it wasnt long ago that lby updated, just check nearby
			{
				resolved_yaw[index] = FixedResolve + U::RandomFloat(-35, 35); // -35.0 - 35.0
			}
			else // if its getting old info, check in a wider area
			{
				resolved_yaw[index] = FixedResolve + U::RandomFloat(-90, 90);
			}
			flYaw = resolved_yaw[index];
		}
		ent->GetHeadRotation()->y = flYaw;
	}
}
//
//struct Resolvenz
//{
//	float lby;
//	float angy;
//	bool moving;
//};
//
//void automaticpewpew(CBaseEntity* ent)
//{
//	int indexEnt = ent->GetIndex();
//
//	bool is_walking = false;
//	bool update_lby = false;
//	bool is_intime = false;
//	bool is_meming = false;
//
//	static float lbys[64];
//	static float lbytimes[64];
//
//	std::vector<Resolvenz> struzt[64];
//
//	if (struzt[indexEnt].size() > 32)//20
//		struzt[indexEnt].pop_back();
//
//	if (ent->GetVelocity().Length2D() > 0.1f && ent->GetFlags() & FL_ONGROUND)
//		is_walking = true;
//
//	if (I::Globals->curtime - lbytimes[indexEnt] > 1.1f)
//		is_intime = true;
//
//	if (is_walking && !is_meming)
//	{
//		update_lby = true;
//	}
//	else
//	{
//		if (lbys[indexEnt] != ent->GetLowerBodyTarget())
//		{
//			update_lby = true;
//		}
//		else
//		{
//			if (is_intime)
//			{
//				update_lby = true;
//			}
//		}
//	}
//	float reslv = 0.0f;
//	if (update_lby)
//	{
//		lbys[indexEnt] = ent->GetLowerBodyTarget();
//		lbytimes[indexEnt] = I::Globals->curtime;
//
//		Resolvenz mem;
//		mem.angy = ent->GetEyeAngles().y;
//		mem.lby = ent->GetLowerBodyTarget();
//		mem.moving = is_walking;
//		struzt[indexEnt].insert(struzt[indexEnt].begin(), mem);
//
//		reslv = ent->GetLowerBodyTarget();
//	}
//	else
//	{
//
//		int samelbys = 0;
//		if (struzt[indexEnt].size() > 4)
//		{
//			for (auto x = 0; x < struzt[indexEnt].size() - 2; x++)
//			{
//				if (struzt[indexEnt][x].lby == struzt[indexEnt][x + 1].lby && !struzt[indexEnt][x].moving && !struzt[indexEnt][x + 1].moving)
//					samelbys++;
//			}
//		}
//
//
//		if (samelbys > 5)
//		{
//			reslv = struzt[indexEnt].front().lby + 180.0f;
//		}
//		else
//		{
//			if (!struzt[indexEnt].empty())
//			{
//				int __;
//				float yaw_deltas;
//
//				for (auto x : struzt[indexEnt])
//				{
//					__++;
//					yaw_deltas += x.angy - x.lby;
//				}
//
//				yaw_deltas /= (float)__;
//
//				reslv = ent->GetLowerBodyTarget() + yaw_deltas;//lby vorher
//			}
//			else
//			{
//				LBYthings::lbydelta(ent);
//			}
//		}
//	}
//	while (reslv < -180.0f)
//		reslv += 360.0f;
//
//	while (reslv >  180.0f)
//		reslv -= 360.0f;
//
//	*(float*)((DWORD)ent + offsets.m_angEyeAnglesY) = reslv;
//}

//float DoYawAAA(CBaseEntity* pEnt) 
//{
//	float yaw = pEnt->GetHeadRotation()->y;
//
//	yaw -= 180.f;
//
//	return yaw;
//}
//
//
//float LBYResolver(CBaseEntity* Player, bool lby2)
//{
//	QAngle angle;
//
//	angle.y = Player->GetHeadRotation()->y;
//
//	if (G::LastLBYUpdate)
//		angle.y -= lby2 ? 180.f : 90.f;
//
//	return *(float*)((DWORD)Player + offsets.m_angEyeAnglesY) = angle.y;
//}


void PitchCorrection()
{
	CUserCmd* pCmd;
	for (int i = 0; i < I::Engine->GetMaxClients(); ++i)
	{
		CBaseEntity* pLocal = G::LocalPlayer;
		CBaseEntity *player = (CBaseEntity*)I::ClientEntList->GetClientEntity(i);

		if (!player || player->GetDormant() || player->GetHealth() < 1 || (DWORD)player == (DWORD)pLocal)
			continue;

		if (!player)
			continue;

		if (pLocal)
			continue;

		if (pLocal && player && pLocal->GetAlive())
		{
			if (Vars.Ragebot.Pitchfix)
			{
				QAngle* eyeAngles = player->GetHeadRotation();
				if (eyeAngles->x < -179.f) eyeAngles->x += 360.f;
				else if (eyeAngles->x > 90.0 || eyeAngles->x < -90.0) eyeAngles->x = 89.f;
				else if (eyeAngles->x > 89.0 && eyeAngles->x < 91.0) eyeAngles->x -= 90.f;
				else if (eyeAngles->x > 179.0 && eyeAngles->x < 181.0) eyeAngles->x -= 180;
				else if (eyeAngles->x > -179.0 && eyeAngles->x < -181.0) eyeAngles->x += 180;
				else if (fabs(eyeAngles->x) == 0) eyeAngles->x = std::copysign(89.0f, eyeAngles->x);
			}
		}
	}
}


#define TIME_T222O_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / I::Globals->interval_per_tick ) )

int meme_resolvenz::get_best_tick(int playerindex)
{
	return tickenz[playerindex];
}

float meme_resolvenz::ret_last_time(int indexpla)
{
	return last_time[indexpla];
}

void meme_resolvenz::record_and_set(CBaseEntity* pEntity)
{
	auto index = pEntity->GetIndex(); 
	
	bool on_lbys = (pEntity->GetFlags() & FL_ONGROUND && (pEntity->GetVelocity().Length2D() > 0.1));

	if (backtrack_me_angle[index] != pEntity->GetLowerBodyTarget() || on_lbys)
	{	
		backtrack_me_angle[index] = pEntity->GetLowerBodyTarget();
		tickenz[index] = TIME_T222O_TICKS(pEntity->GetSimulationTime());
		last_time[index] = I::Engine->GetLastTimeStamp();
	}


	if ((G::UserCmd->tick_count - tickenz[index]) > 32)
	{
		lby_last[index] = pEntity->GetLowerBodyTarget();
	}

	float last_angle = 0.0f;

	if (G::UserCmd->tick_count -  tickenz[index] > 12)
	{
		tickenz[index] = 0;
		last_time[index] = I::Engine->GetLastTimeStamp();

		if (Vars.Playerlist.Player[index] == 1)
		{
			if ((lby_last[index] == pEntity->GetLowerBodyTarget() || GetAsyncKeyState(0x12)) && !on_lbys)
				last_angle = lby_last[index] + 90.0f;
			else
			{
				float delta = pEntity->GetHeadRotation()->y - backtrack_me_angle[index];
				last_angle = pEntity->GetLowerBodyTarget() + delta;
			}
				
		}
		else
		{
			if (GetAsyncKeyState(0x12) && !on_lbys)
				last_angle = lby_last[index] + 90.0f;
			else
			{
				float delta = pEntity->GetHeadRotation()->y - backtrack_me_angle[index];
				last_angle = pEntity->GetLowerBodyTarget() + delta;
			}
		}
	}
	else
	{
		last_angle = backtrack_me_angle[index];
	}

	pEntity->GetHeadRotation()->y = last_angle;
}

	







std::unordered_map<MaterialHandle_t, Color> skyboxMaterials;
FrameStageNotifyFn oFrameStageNotify;
void __stdcall Hooks::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!G::LocalPlayer || G::LocalPlayer->GetHealth() <= 0)
		return oFrameStageNotify(stage);

	QAngle aim_punch_old;
	QAngle view_punch_old;

	QAngle* aim_punch = nullptr;
	QAngle* view_punch = nullptr;

	/*G::LastLBYUpdate = LBYthings::NextLBYUpdate();*/

	if (I::Engine->IsInGame() && stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && Vars.Ragebot.Enabled)
	{
		G::LastLBYUpdate = LBYthings::NextLBYUpdate();
		CBaseEntity* pEntity = nullptr;
		CBaseEntity *pLocal = I::ClientEntList->GetClientEntity(I::Engine->GetLocalPlayer());
		G::LastLBYUpdateEnemy = LBYthings::NextLBYUpdateEnemy();
	}

	if (I::Engine->IsInGame() && stage == FRAME_RENDER_START && Vars.Visuals.Removals.VisualRecoil)
	{
		
		if (G::LocalPlayer && G::LocalPlayer->GetAlive())
		{
			aim_punch = (QAngle*)((DWORD)G::LocalPlayer + offsets.m_aimPunchAngle);
			view_punch = (QAngle*)((DWORD)G::LocalPlayer + offsets.m_viewPunchAngle);

			aim_punch_old = *aim_punch;
			view_punch_old = *view_punch;

			*aim_punch = QAngle(0, 0, 0);
			*view_punch = QAngle(0, 0, 0);
		}
	}
	if (I::Engine->IsInGame() && stage == FRAME_RENDER_START && Vars.Misc.thirdperson && G::LocalPlayer->GetAlive())
	{
		/*if (*(bool*)((DWORD)I::Input + 0xA5))*/
		if(Vars.Misc.thirdperson && G::LocalPlayer->GetAlive())
		*(QAngle*)((DWORD)G::LocalPlayer + 0x31C8) = G::VisualAngle;
	}
	if (I::Engine->IsInGame() && stage == FRAME_NET_UPDATE_POSTDATAUPDATE_END && Vars.Visuals.Removals.RaveSky)
	{

		for (MaterialHandle_t i = I::MaterialSystem->FirstMaterial(); i != I::MaterialSystem->InvalidMaterial(); i = I::MaterialSystem->NextMaterial(i))
		{
			IMaterial *mat = I::MaterialSystem->GetMaterial(i);

			if (!mat)
				continue;

			if (strcmp(mat->GetTextureGroupName(), TEXTURE_GROUP_SKYBOX) != 0)
				continue;

			if (skyboxMaterials.find(i) == skyboxMaterials.end())
				skyboxMaterials.emplace(i, Color());

			static float rainbow;
			rainbow += 0.007f;
			if (rainbow > 1.f) rainbow = 0.f;

			Color color = Color::FromHSB(rainbow, 1.f, 1.f);


			//if (skyboxMaterials.at(i) != color)
			{
				mat->ColorModulate(color.r(), color.g(), color.b());

				skyboxMaterials.at(i) = color;
			}
		}
	}
	


	if (I::Engine->IsInGame() && stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START && Vars.Playerlist.use)
	{
		{
			static float oldshit[64];
			static float difoldshit[64];
			for (int i = 0; i <= I::Globals->maxClients; i++)
			{
				CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);

				if (Entity == NULL)
					continue;

				if (Entity == G::LocalPlayer)
					continue;

				if ((Entity->GetTeam() == G::LocalPlayer->GetTeam()) || Entity->GetDormant() || !Entity->GetAlive() || Entity->GetHealth() <= 0)
					continue;

				if (Vars.Playerlist.Player[i] == 0 || Vars.Playerlist.Player[i] == 1)//Auto
				{
					//	automaticpewpew(Entity);

					meme_resolvenz::get_instance()->record_and_set(Entity);

				}
				//else if (Vars.Playerlist.Player[i] == 2)//delta
				//{
				//	LBYthings::lbydelta(Entity);
				//	if (Entity->GetHeadRotation()->y > 180.0f)
				//		Entity->GetHeadRotation()->y -= 360.0f;
				//	if (Entity->GetHeadRotation()->y < -180.0f)
				//		Entity->GetHeadRotation()->y += 360.0f;
				//}
				//else if (Vars.Playerlist.Player[i] == 3)//delta2
				//{
				//	/*LBYthings::lbydelta2(Entity);
				//	if (Entity->GetHeadRotation()->y > 180.0f)
				//		Entity->GetHeadRotation()->y -= 360.0f;
				//	if (Entity->GetHeadRotation()->y < -180.0f)
				//		Entity->GetHeadRotation()->y += 360.0f;*/
				//}
				//else if (Vars.Playerlist.Player[i] == 4)//delta3
				//{
				//	/*static float OldLowerBodyYaws[64];
				//	static float OldYawDeltas[64];
				//	float CurYaw = Entity->GetLowerBodyTarget();
				//	if (OldLowerBodyYaws[i] != CurYaw)
				//	{
				//		OldYawDeltas[i] = Entity->GetEyeAngles().y - CurYaw;
				//		OldLowerBodyYaws[i] = CurYaw;
				//		Entity->GetHeadRotation()->y = CurYaw;
				//		continue;
				//	}
				//	else
				//	{
				//		Entity->GetHeadRotation()->y = Entity->GetEyeAngles().y - OldYawDeltas[i];
				//	}
				//	Entity->GetHeadRotation()->y = CurYaw;*/
				//}
				//else if (Vars.Playerlist.Player[i] == 5)//BruteForce
				//{
				//	/*if ((Entity->GetLowerBodyTarget() != Entity->GetHeadRotation()->y) && (Entity->GetVelocity().Length2D() > 0.1f && Entity->GetFlags() & FL_ONGROUND))
				//	{
				//		Entity->GetHeadRotation()->y = Entity->GetLowerBodyTarget() + U::RandomFloat(-35, +35);
				//	}*/
				//}
				//else if (Vars.Playerlist.Player[i] == 6)//lby
				//{
				//	/**(float*)((DWORD)Entity + offsets.m_angEyeAnglesY) = *(float*)((DWORD)Entity + offsets.m_flLowerBodyYawTarget);*/
				//}
				else if (Vars.Playerlist.Player[i] == 3)
				{
					return;
				}
			}
		}
	}

	oFrameStageNotify(stage);

	if (aim_punch && view_punch && Vars.Visuals.Removals.VisualRecoil)
	{
		*aim_punch = aim_punch_old;
		*view_punch = view_punch_old;
	}
}