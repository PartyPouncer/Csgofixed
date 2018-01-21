#include "Cheat.h"
#define JUNKS \
__asm _emit 0x45 \
__asm _emit 0x10 \
__asm _emit 0x85 \
__asm _emit 0x42 \
__asm _emit 0x94 \
__asm _emit 0x04 \
__asm _emit 0x84 \
__asm _emit 0x91 \
__asm _emit 0x87 \
__asm _emit 0x62 \
// Don't change this!
#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:

void CVisuals::Run()
{
	_JUNK_BLOCK(jmp_label1)
	if( Vars.Misc.Watermark )
		E::Visuals->Watermark();

	if (Vars.Misc.Timestamp)
		E::Visuals->Timestamp();

	if( !InGame() )
		return;

	if( !Vars.Visuals.Enabled )
		return;

	if (Vars.Visuals.pSpecList)
		pSpecList();

	if (Vars.Visuals.Removals.NightMode)
		Nightmode();

	if (Vars.Visuals.Removals.Scope)
		E::Misc->RemoveScope();

	if (Vars.Visuals.CrosshairFOV && G::LocalPlayer->GetAlive())
		DrawFOVCrosshair();


	static bool crosshair = false;

	if( Vars.Visuals.CrosshairOn )
	{
		DrawCrosshair( Color::Green() );
		if( !crosshair )
		{
			I::Engine->ClientCmd_Unrestricted( charenc( "crosshair 0" ),0 ); 
			crosshair = true;
		}
			
	}
	else
	{
		if( crosshair )
		{
			I::Engine->ClientCmd_Unrestricted( charenc( "crosshair 1" ),0 );
			crosshair = false;
		}
	}

	DrawGlow();
	

	for( int i = 0; i < I::ClientEntList->GetHighestEntityIndex(); i++ )
	{
		PlayerESP( i );
		WorldESP( i );
	}
}

void CVisuals::PlayerESP(int index)
{
	_JUNK_BLOCK(jmp_label2)
	CBaseEntity* Entity = I::ClientEntList->GetClientEntity(index);
	//test erst mal das far esp *
	if (EntityIsInvaild(Entity))
		return;

	if (!Vars.Visuals.Filter.Friendlies && !Entity->IsEnemy())
		return;

	if (!Vars.Visuals.Filter.Enemies && Entity->IsEnemy())
		return;

	Vector max = Entity->GetCollideable()->OBBMaxs();
	Vector pos, pos3D;
	Vector top, top3D;
	pos3D = Entity->GetOrigin();
	top3D = pos3D + Vector(0, 0, max.z);
	if (!D::WorldToScreen(pos3D, pos) || !D::WorldToScreen(top3D, top))
		return;

	float height = (pos.y - top.y);
	float width = height / 4.f;
	int x, y, w, h;
	int bottom = 0;
	int toppom = 0;

	if (Vars.Visuals.Skeleton)
		Skeleton(Entity, Color::White());

	if (Vars.Visuals.BackTrack)
		LegitBacktracking::PT();



	/*char buff[50];
	  sprintf(buff, "%-.5f", *(float*)((DWORD)Entity + offsets.m_flLowerBodyYawTarget));

	  D::DrawString(F::ESP, top.x, top.y - 6, Color::White(), FONT_CENTER, charenc("%s"), buff);

	  sprintf(buff, "%-.5f", *(float*)((DWORD)Entity + offsets.m_flDeathYaw));
	  D::DrawString(F::ESP, top.x, top.y + 2, Color::White(), FONT_CENTER, charenc("%s"), buff);

	  sprintf(buff, "%-.5f", *(float*)((DWORD)Entity + offsets.m_flAbsYaw));
	  D::DrawString(F::ESP, top.x, top.y + 9, Color::White(), FONT_CENTER, charenc("%s"), buff);*/



	for (int i = Hitboxes::HITBOX_LEFT_FOREARM; i >= Hitboxes::HITBOX_HEAD; i--)
	{
		Vector hitboxPos[9];

		if (!E::RageBot->GetHitBoxCenter(Entity, i, hitboxPos))
			continue;
	}

	Color boxColor;
	if (Entity->IsVisible(6))
	{
		boxColor = Entity->IsEnemy() ? Color(255, 0, 0) : Color(84, 167, 255);
	}
	else
	{

		boxColor = Entity->IsEnemy() ? Color(255, 255, 0) : Color(72, 219, 75);
	}

	if (Vars.Visuals.DLight)
		DrawDLight(Entity, boxColor);

	_JUNK_BLOCK(jmp_label3)

	static float rainbow;
	rainbow += 0.001f;
	if (rainbow > 1.f) rainbow = 0.f;
	else if (Vars.Visuals.RainbowDlight)
		DrawDLight(Entity, Color::FromHSB(rainbow, 1.f, 1.f));

	if (Vars.Visuals.BoxType == 1)
		PlayerBox(top.x, top.y, width, height, boxColor);

	if (Vars.Visuals.BoxType == 2)
		CornerBox(top.x - width, top.y, width * 2, height, boxColor, 6);

	if (Vars.Visuals.BoxType == 3)
		DBox(pos3D, Entity, boxColor);

	if (Vars.Visuals.Info.Name)
		D::DrawString(F::ESP, top.x, top.y - 6, Color::White(), FONT_CENTER, charenc("%s"), Entity->GetName().c_str());

	if (Vars.Visuals.Info.LBY)
	{
		if (InGame() && G::LocalPlayer->GetAlive() && Vars.Ragebot.Enabled)
		{
			D::DrawString(F::ESP, top.x, top.y + height + 10 - (5 * bottom++), G::LastLBYUpdateEnemy ? Color(200, 0, 0) : Color(0, 200, 0), FONT_CENTER, (" LBY "));
		}
	}
	_JUNK_BLOCK(jmp_label4)
	if (Vars.Visuals.Info.Health)
		HealthBar(pos, top, Entity->GetHealth());

	if (Vars.Visuals.BulletTrace)
		BulletTrace(Entity, Color(255, 255, 255, 255));

	if (Vars.Visuals.HitBoxDot)
		HitBoxDot(Entity, Color(255, 255, 255, 255));

	if (Vars.Visuals.Info.Weapon)
		D::DrawString(F::ESP, top.x, top.y + height + 8 + (10 * bottom++), Color::White(), FONT_CENTER, charenc("%s"), Entity->GetWeapon()->GetWeaponName().c_str());

	if (Entity->GetUserID() == Vars.Visuals.Filter.C4)
		D::DrawString(F::ESP, x + (w / 2), y + h + 12 + (10 * bottom++), Color::Red(), FONT_CENTER, charenc("BOMB"));

	if (Vars.Visuals.Info.DrawWeapon)
		DrawWeapon(top.x, top.y + height + 8 + (10 * bottom++), 0xA1, Entity);

	if (Vars.Visuals.Info.Flashed && Entity->IsFlashed())
		D::DrawString(F::ESP, top.x, top.y + height + 8 + (10 * bottom++), Color::Red(), FONT_CENTER, charenc("FLASHED"));

	if (Entity->IsVisible(6) && Vars.Visuals.DrawHitbox)
		E::Visuals->Hitboxes(Entity, Entity->IsEnemy() ? Color(255, 0, 0) : Color(84, 167, 255));
	else if (!Entity->IsVisible(6) && Vars.Visuals.DrawHitbox)
		E::Visuals->Hitboxes(Entity, Entity->IsEnemy() ? Color(255, 255, 0) : Color(72, 219, 75));

	if (Vars.Visuals.Hitmarker)
	{
		auto curtime = I::Globals->curtime;
		auto lineSize = 12;
		if (G::flHurtTime + 0.125f >= curtime)
		{
			int screenSizeX, screenCenterX;
			int screenSizeY, screenCenterY;
			I::Engine->GetScreenSize(screenSizeX, screenSizeY);

			screenCenterX = screenSizeX / 2;
			screenCenterY = screenSizeY / 2;

			I::Surface->DrawSetColor(255, 255, 255, 255);
			I::Surface->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
			I::Surface->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
			I::Surface->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
			I::Surface->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));
		}
	}
}

void CVisuals::WorldESP(int index)
{
	_JUNK_BLOCK(jmp_label5)
	CBaseEntity* Entity = I::ClientEntList->GetClientEntity(index);

	if (!Entity)
		return;

	bombtimer(Entity);

	Vector pos, pos3D;
	pos3D = Entity->GetOrigin();

	if (pos3D.IsZero())
		return;

	if (!D::WorldToScreen(pos3D, pos))
		return;
	if (Vars.Visuals.Filter.Chickens)
	{

		if (Entity->GetClientClass()->m_ClassID == 31)
			D::DrawString(F::ESP, pos.x, pos.y, Color(0, 255, 230), FONT_CENTER, charenc("Chicken"));
	}
	int x, y, w, h;
	if (GetBox(Entity, x, y, w, h))
	{

		if (Entity->GetClientClass()->m_ClassID == 85) // CHostage ClassID - Thx
		{
			if (Vars.Visuals.Info.Hostage)
				D::DrawString(F::ESP, x + (w / 2), y - 8, Color::Green(), FONT_CENTER, charenc("Hostage"));

			EspBox(Entity, Color(255, 255, 255));
		}
	}
	_JUNK_BLOCK(jmp_label6)
	int owner = Entity->GetOwner();

	if (owner == -1)
	{
		if (Vars.Visuals.Filter.Weapons)
		{
			if (strstr(Entity->GetClientClass()->m_pNetworkName, charenc("CWeapon")))
			{
				std::string wpnname = "unknown";

				wpnname = std::string(Entity->GetClientClass()->m_pNetworkName).substr(7);

				DrawEntity2(Entity, wpnname.c_str(), Color::White());

			}

			if (Entity->GetClientClass()->m_ClassID == 1) {
				DrawEntity2(Entity, charenc("AK-47"), Color(100, 100, 255, 250));
			}
			else if (Entity->GetClientClass()->m_ClassID == 39)
			{
				DrawEntity2(Entity, charenc("Deagle"), Color(100, 100, 255, 250));
			}
		}

		if (Entity->GetClientClass()->m_ClassID == 29 && Vars.Visuals.Filter.C4) {
			//BombCarrier = nullptr;
			D::DrawString(F::ESP, pos.x, pos.y, Color::Yellow(), FONT_CENTER, "%s", charenc("Dropped C4"));
			/*DrawEntity2(Entity, charenc("C4 Dropped"), Color::Yellow());*/
		}
	}
	if (Vars.Visuals.Filter.Nades && strstr(Entity->GetClientClass()->m_pNetworkName, charenc("Projectile")))
	{
		DrawThrowable(Entity, Entity->GetClientClass());
	}
	if (Vars.Visuals.Filter.Nades && strstr(Entity->GetClientClass()->m_pNetworkName, charenc("Grenade")) || strstr(Entity->GetClientClass()->m_pNetworkName, charenc("Flashbang")))
	{
		DrawOnFloor(Entity, Entity->GetClientClass());
	}
	

	if (strstr(Entity->GetClientClass()->m_pNetworkName, charenc("CPlantedC4")) && Vars.Visuals.Filter.C4) {
		char mew[519];
		sprintf(mew, "Planted C4 [%.1f]", Entity->GetBombTimer());
		/*D::DrawString(F::ESP, pos.x, pos.y, Color::Red(), FONT_CENTER, charenc("C4 [%.1f]"), Entity->GetBombTimer());*/
		DrawEntity(Entity, mew, Color::Red());
	}
}
//
//void CVisuals::DrawWarnings()
//{
//	if (Vars.Visuals.BackTrack)
//	{
//		if (I::Engine->IsInGame() && I::Engine->IsConnected())
//		{
//			std::stringstream text1 = std::stringstream("");
//			std::stringstream text2 = std::stringstream("");
//
//			CBaseEntity* pLocal = I::ClientEntList->GetClientEntity(I::Engine->GetLocalPlayer());
//			if (!pLocal)
//				return;
//			for (int i = 1; i <= I::Engine->GetMaxClients(); i++)
//			{
//				CBaseEntity* pPlayer = I::ClientEntList->GetClientEntity(i);
//				if (pPlayer)
//				{
//					if (!pPlayer->GetAlive())
//						continue;
//					if (pPlayer->GetTeam() == pLocal->GetTeam() && !Vars.Visuals.Filter.Friendlies)
//						continue;
//
//					player_info_t info;
//					if (!I::Engine->GetPlayerInfo(i, &info))
//						continue;
//
//
//					QAngle src, dst, forward;
//					trace_t tr;
//					Ray_t ray;
//					CTraceFilter filter;
//
//					M::AngleVectors(pPlayer->GetEyeAngles(), forward);
//					filter.pSkip = pPlayer;
//					src = pPlayer->GetBestEyePos(true);
//					dst = src + (forward * 8192);
//
//					ray.Init(src, dst);
//
//					Globals.g_pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
//
//					bool AimingToLocal = (tr.m_pEnt && tr.hitgroup > 0 && tr.hitgroup <= 7);
//					bool CanSeeLocal = Math.IsVisible(pPlayer->GetEyePosition(true), pLocal->GetEyePosition(true), pPlayer, pLocal);
//					if (AimingToLocal)
//						text2 << info.name << " ";
//					/*else */if (CanSeeLocal)
//						text1 << info.name << " ";
//
//				}
//			}
//			text2 << "Aiming to You";
//			text1 << "Can see You";
//			int screensizeX, screensizeY;
//			Globals.g_pEngine->GetScreenSize(screensizeX, screensizeY);
//			Drawings.DrawText(screensizeX / 2, 100, Color::Red(), B1gFont, true, text2.str().c_str());
//			Drawings.DrawText(screensizeX / 2, 140, Color::Green(), B1gFont, true, text1.str().c_str());
//		}
//	}
//}

void CVisuals::EspBox(CBaseEntity* pEntityPlayer, Color clr)
{
	_JUNK_BLOCK(jmp_label7)
	int x, y, w, h;
	GetBox(pEntityPlayer, x, y, w, h);
	{
		// Corner Box
		int VertLine = (((float)w) * (0.20f));
		int HorzLine = (((float)h) * (0.20f));

		D::DrawRect(x, y - 1, VertLine, 1, Color(10, 10, 10, 150));
		D::DrawRect(x + w - VertLine, y - 1, VertLine, 1, Color(10, 10, 10, 150));
		D::DrawRect(x, y + h - 1, VertLine, 1, Color(10, 10, 10, 150));
		D::DrawRect(x + w - VertLine, y + h - 1, VertLine, 1, Color(10, 10, 10, 150));

		D::DrawRect(x - 1, y, 1, HorzLine, Color(10, 10, 10, 150));
		D::DrawRect(x - 1, y + h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));
		D::DrawRect(x + w - 1, y, 1, HorzLine, Color(10, 10, 10, 150));
		D::DrawRect(x + w - 1, y + h - HorzLine, 1, HorzLine, Color(10, 10, 10, 150));

		D::DrawRect(x, y, VertLine, 1, clr);
		D::DrawRect(x + w - VertLine, y, VertLine, 1, clr);
		D::DrawRect(x, y + h, VertLine, 1, clr);
		D::DrawRect(x + w - VertLine, y + h, VertLine, 1, clr);

		D::DrawRect(x, y, 1, HorzLine, clr);
		D::DrawRect(x, y + h - HorzLine, 1, HorzLine, clr);
		D::DrawRect(x + w, y, 1, HorzLine, clr);
		D::DrawRect(x + w, y + h - HorzLine, 1, HorzLine, clr);
	}
}

bool CVisuals::GetBox(CBaseEntity *entity, int& x, int& y, int& w, int& h)
{
	_JUNK_BLOCK(jmp_label8)
	Vector vOrigin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	vOrigin = entity->GetOrigin();
	min = entity->GetCollideable()->OBBMins() + vOrigin;
	max = entity->GetCollideable()->OBBMaxs() + vOrigin;

	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	if (!D::WorldToScreen(points[3], flb) || !D::WorldToScreen(points[5], brt)
		|| !D::WorldToScreen(points[0], blb) || !D::WorldToScreen(points[4], frt)
		|| !D::WorldToScreen(points[2], frb) || !D::WorldToScreen(points[1], brb)
		|| !D::WorldToScreen(points[6], blt) || !D::WorldToScreen(points[7], flt))
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	x = (int)left;
	y = (int)top;
	w = (int)(right - left);
	h = (int)(bottom - top);

	return true;
}

void CVisuals::bombtimer(CBaseEntity* pEntity)
{
	_JUNK_BLOCK(jmp_label9)
	RECT TextxSizeS = D::GetTextSize(F::Watermark, "A | T");
	//14
	int screenW, screenH;
	I::Engine->GetScreenSize(screenW, screenH);

	int light = screenW - TextxSizeS.right - 20;

	if (Vars.Visuals.Filter.C4 && strstr(pEntity->GetClientClass()->m_pNetworkName, charenc(("CPlantedC4"))))
		D::DrawString(F::Watermark, light + 10, 12 + TextxSizeS.bottom + 3, Color::Red(), FONT_CENTER, "%.1f", pEntity->GetBombTimer());
}

void CVisuals::DrawEntity(CBaseEntity* entity, const char* string, Color color)
{
	_JUNK_BLOCK(jmp_label10)
	Vector max = entity->GetCollideable()->OBBMaxs();
	Vector pos, pos3D;
	Vector top, top3D;
	pos3D = entity->GetOrigin();
	top3D = pos3D + Vector(0, 0, max.z);

	if (!D::WorldToScreen(pos3D, pos) || !D::WorldToScreen(top3D, top))
		return;

	float height = (pos.y - top.y);
	float width = height / 4.f;
	PlayerBox(top.x, top.y, width + 10, height + 10, color);

	D::DrawString(F::ESP, top.x + width + 13, top.y + ((height + 10) / 2), Color(255, 255, 255, 255), FONT_CENTER, string);
}

void CVisuals::DrawEntity2(CBaseEntity* entity, const char* string, Color color)
{
	_JUNK_BLOCK(jmp_label11)
	Vector max = entity->GetCollideable()->OBBMaxs();
	Vector pos, pos3D;
	Vector top, top3D;
	pos3D = entity->GetOrigin();
	top3D = pos3D + Vector(0, 0, max.z);

	if (!D::WorldToScreen(pos3D, pos) || !D::WorldToScreen(top3D, top))
		return;

	float height = (pos.y - top.y);
	float width = height / 4.f;

	D::DrawString(F::ESP, top.x + width + 13, top.y + ((height + 10) / 2), Color(255, 255, 255, 255), FONT_CENTER, string);
}

void CVisuals::DrawThrowable(CBaseEntity* const throwable, ClientClass* client)
{
	_JUNK_BLOCK(jmp_label12)
	const model_t* nadeModel = throwable->GetModel();

	if (!nadeModel)
		return;

	studiohdr_t* hdr = I::ModelInfo->GetStudioModel(nadeModel);

	if (!hdr)
		return;

	if (!strstr(hdr->name, charenc("thrown")) && !strstr(hdr->name, charenc("dropped")))
		return;

	Color nadeColor = Color(255, 255, 255, 255);
	std::string nadeName = charenc("Flying Grenade");

	IMaterial* mats[32];
	I::ModelInfo->GetModelMaterials(nadeModel, hdr->numtextures, mats);

	for (int i = 0; i < hdr->numtextures; i++)
	{
		IMaterial* mat = mats[i];
		if (!mat)
			continue;

		if (strstr(mat->GetName(), charenc("flashbang")))
		{
			nadeName = charenc("Flashbang");
			nadeColor = Color(238, 233, 75);
			break;
		}
		else if (strstr(mat->GetName(), charenc("m67_grenade")) || strstr(mat->GetName(), charenc("hegrenade")))
		{
			nadeName = charenc("HE Grenade");
			nadeColor = Color(210, 0, 40);
			break;
		}
		else if (strstr(mat->GetName(), charenc("smoke")))
		{
			nadeName = charenc("Smoke");
			nadeColor = Color(93, 175, 97);
			break;
		}
		else if (strstr(mat->GetName(), charenc("decoy")))
		{
			nadeName = charenc("Decoy");
			nadeColor = Color(230, 78, 255);
			break;
		}
		else if (strstr(mat->GetName(), charenc("incendiary")) || strstr(mat->GetName(), charenc("molotov")))
		{
			nadeName = charenc("Molotov");
			nadeColor = Color(208, 131, 0);
			break;
		}
	}

	DrawEntity(throwable, nadeName.c_str(), nadeColor);
}

void CVisuals::DrawOnFloor(CBaseEntity* const throwable, ClientClass* client)
{
	_JUNK_BLOCK(jmp_label13)
	const model_t* nadeModel = throwable->GetModel();

	if (!nadeModel)
		return;

	studiohdr_t* hdr = I::ModelInfo->GetStudioModel(nadeModel);

	if (!hdr)
		return;

	if (!strstr(hdr->name, charenc("thrown")) && !strstr(hdr->name, charenc("dropped")))
		return;

	std::string nadeName = charenc("Flying Grenade");

	IMaterial* mats[32];
	I::ModelInfo->GetModelMaterials(nadeModel, hdr->numtextures, mats);

	for (int i = 0; i < hdr->numtextures; i++)
	{
		IMaterial* mat = mats[i];
		if (!mat)
			continue;

		if (strstr(mat->GetName(), charenc("flashbang")))
		{
			nadeName = charenc("Flashbang");
			break;
		}
		else if (strstr(mat->GetName(), charenc("m67_grenade")) || strstr(mat->GetName(), charenc("hegrenade")))
		{
			nadeName = charenc("HE Grenade");
			break;
		}
		else if (strstr(mat->GetName(), charenc("smoke")))
		{
			nadeName = charenc("Smoke");
			break;
		}
		else if (strstr(mat->GetName(), charenc("decoy")))
		{
			nadeName = charenc("Decoy");
			break;
		}
		else if (strstr(mat->GetName(), charenc("incendiary")) || strstr(mat->GetName(), charenc("molotov")))
		{
			nadeName = charenc("Molotov");
			break;
		}
	}

	DrawEntity2(throwable, nadeName.c_str(), Color::Purple());
}

void Line(Vector2D start_pos, Vector2D end_pos, Color col)
{
	D::DrawLine(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
}

void Circle(Vector2D position, float points, float radius, Color color)
{
	_JUNK_BLOCK(jmp_label14)
	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
	{
		Vector2D start(radius * cosf(a) + position.x, radius * sinf(a) + position.y);
		Vector2D end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y);
		Line(start, end, color);
	}
}

void CVisuals::FovCrosshair()
{
	_JUNK_BLOCK(jmp_label15)
	if (!G::LocalPlayer->GetAlive())
		return;

	if (!Vars.Visuals.CrosshairFOV)
		return;

	if (!G::LocalPlayer->GetWeapon()->IsGun())
		return;

	int width, height;
	I::Engine->GetScreenSize(width, height);

	float radAimbotFov = (float)(G::FOV * M_PI / 180);
	float radViewFov = (float)(G::FOV * M_PI / 180);

	float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * width;
#define LOC(x,y) Vector2D(x,y)
	Circle(LOC(width / 2, height / 2), 20, circleRadius, Color::White());
}

void CVisuals::DrawGlow()
{
	_JUNK_BLOCK(jmp_label16)
	CGlowObjectManager* GlowObjectManager = ( CGlowObjectManager* )offsets.GlowManager;

	for( int i = 0; i < GlowObjectManager->size; ++i )
	{
		CGlowObjectManager::GlowObjectDefinition_t* glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[ i ];
		CBaseEntity* Entity = glowEntity->getEntity();

		if( glowEntity->IsEmpty() || !Entity )
			continue;

		switch( Entity->GetClientClass()->m_ClassID )
		{

		/*case ( 133 || 40 || 97 || 84 || 87 || 66 || 9 ):
			if (Vars.Visuals.Filter.Nades)
				glowEntity->set(Color(255, 0, 255, 250));

			break;*/

		case 1:
			if (Vars.Visuals.Filter.Weapons)
				glowEntity->set(Color(100, 100, 255, 250));

			break;

		case 39:
			if (Vars.Visuals.Filter.Weapons)
				glowEntity->set(Color(255, 255, 255, 250));

			break;

		case 29:
			if( Vars.Visuals.Filter.C4 )
				glowEntity->set( Color( 255, 255, 0, 250 ) );
			
			break;



		case 35:
			if( Vars.Visuals.Glow )
			{
				if( !Vars.Visuals.Filter.Friendlies && !Entity->IsEnemy() )
					break;

				if( !Vars.Visuals.Filter.Enemies && Entity->IsEnemy() )
					break;

				if( Entity->m_visible )
					glowEntity->set( Entity->IsEnemy() ? Color( 232, 209, 32, 250 ) : Color( 72, 219, 75, 250 ) );

				else
					glowEntity->set( Entity->IsEnemy() ? Color( 200, 60, 60, 250 ) : Color( 84, 167, 255, 250 ) );

			}
			break;

		default:
			if( Vars.Visuals.Filter.Weapons )
			{
				if( strstr( Entity->GetClientClass()->m_pNetworkName, charenc( "CWeapon" ) ) )
					glowEntity->set( Color( 100, 100, 255, 250 ) );
			}
			break;
		}
	}
}

bool CVisuals::InGame()
{
	if( !I::Engine->IsInGame() )
		return false;

	if( !G::LocalPlayer )
		return false;

	return true;
}

bool CVisuals::EntityIsInvaild( CBaseEntity* Entity)
{
	if( !Entity )
		return true;
	if( Entity == G::LocalPlayer )
		return true;
	if( Entity->GetHealth() <= 0 )
		return true;
	/*if( Entity->GetDormant() )
		return true;*/

	if (Entity->GetDormant())
	{
		return true;
	}

	return false;
}

void CVisuals::BulletTraceOverlay( CBaseEntity* entity, Color color )
{
	_JUNK_BLOCK(jmp_label17)
	Vector src, dst, forward;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	M::AngleVectors( entity->GetEyeAngles(), &forward );
	filter.pSkip = entity;
	src = entity->GetBonePosition( 8 );
	dst = src + ( forward * Vars.Visuals.BulletTraceLength );

	ray.Init( src, dst );

	I::EngineTrace->TraceRay( ray, MASK_SHOT, &filter, &tr );

	I::DebugOverlay->AddLineOverlay( src, tr.endpos, color.r(), color.g(), color.b(), true, -1 );
}

void CVisuals::BulletTrace( CBaseEntity* entity, Color color )
{
	_JUNK_BLOCK(jmp_label18)
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	M::AngleVectors( entity->GetEyeAngles(), &forward );
	filter.pSkip = entity;
	src3D = entity->GetBonePosition( 8 ) - Vector( 0, 0, 0 );
	dst3D = src3D + ( forward * Vars.Visuals.BulletTraceLength );

	ray.Init( src3D, dst3D );

	I::EngineTrace->TraceRay( ray, MASK_SHOT, &filter, &tr );

	if( !D::WorldToScreen( src3D, src ) || !D::WorldToScreen( tr.endpos, dst ) )
		return;

	D::DrawLine( src.x, src.y, dst.x, dst.y, color );
	/*D::DrawRect( dst.x - 3, dst.y - 3, 6, 6, color );*/
}

void CVisuals::HitBoxDot(CBaseEntity* entity, Color color)
{
	_JUNK_BLOCK(jmp_label19)
	{
		Vector vecBonePos;
		Vector vecAimPos = entity->GetBonePosition( 8 );

		if (D::WorldToScreen(vecAimPos, vecBonePos))
		{
			/*{
				Vector vecBonePos;
				Vector vecAimPos = Entity->GetBonePosition(6);

				if (D::WorldToScreen(vecAimPos, vecBonePos))
				{

					D::DrawCircle(vecBonePos.x, vecBonePos.y - 3, 4, 6, color);
				}*/
			D::DrawOutlinedRect(vecBonePos.x -4, vecBonePos.y -4, 7, 7, color);
		}
	}
}

//void CVisuals::Watermark()
//{
//	static float rainbow;
//	rainbow += 0.005f;
//	if ( rainbow > 1.f ) rainbow = 0.f;
//	D::DrawString( F::Watermark, 5, 11, Color::FromHSB( rainbow, 1.f, 1.f ), FONT_LEFT, charenc("%s"), charenc( "FH4x CS:GO" ) );
//}


void CVisuals::Watermark()
{
	_JUNK_BLOCK(jmp_label20)
	static float rainbow;
	rainbow += 0.005f;
	static int ServerTime = 0;
	static const char* meme = ("FH4x");

	if (ServerTime >= 525)
		ServerTime = 0;

	int value = ServerTime / 30;

	switch (value) 
	{
	case 0:meme=(" "); break;
	case 1:meme = ("/"); break;
	case 2:meme = ("-"); break;
	case 3:meme = ("\\"); break;
	case 4:meme = ("|"); break;
	case 5:meme = ("F/"); break;
	case 6:meme = ("F-"); break;
	case 7:meme = ("F\\"); break;
	case 8:meme = ("F|"); break;
	case 9:meme = ("FH/"); break;
	case 10:meme = ("FH-"); break;
	case 11:meme = ("FH\\"); break;
	case 12:meme = ("FH|"); break;
	case 13:meme = ("FH4/"); break;
	case 14:meme = ("FH4-"); break;
	case 15:meme = ("FH4\\"); break;
	case 16:meme = ("FH4|"); break;
	case 17:meme = ("FH4x"); break;
	case 18:meme = ("    "); break;
	case 19:meme = ("FH4x"); break;
	case 20:meme = ("    "); break;
	case 21:meme = ("FH4x"); break;

	}
	ServerTime++;

	RECT TextxSize = D::GetTextSize(F::Watermark, "FH4x");

	if (rainbow > 1.f) rainbow = 0.f;
	D::DrawString(F::Watermark, 5, 11, Color::FromHSB(rainbow, 1.f, 1.f), FONT_LEFT, "%s", meme);

	if (InGame() && G::LocalPlayer->GetAlive() && Vars.Ragebot.Enabled)
	{
		D::DrawString(F::Watermark, 5, 1010, G::LastLBYUpdate ? Color(200, 0, 0) : Color(0, 200, 0), FONT_LEFT, (" L B Y "));
	}

	/*static float rainboff; D::DrawRectRainbow(5, 11 + 10 + 10, TextxSize.right, 2, 0.003f, rainboff);*/
}

void CVisuals::Timestamp()
{

	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);

	//%Y-%m-%d.%X"
	strftime(buf, sizeof(buf), "%X", &tstruct);

	D::DrawString(F::Watermark, 1850, 11, Color(255, 255, 255, 255), FONT_LEFT, buf);
}

void CVisuals::PlayerBox( float x, float y, float w, float h, Color clr )
{
	_JUNK_BLOCK(jmp_label21)
	I::Surface->DrawSetColor( clr );
	I::Surface->DrawOutlinedRect( x - w, y, x + w, y + h );

	I::Surface->DrawSetColor( Color::Black() );
	I::Surface->DrawOutlinedRect( x - w - 1, y - 1, x + w + 1, y + h + 1 );
	I::Surface->DrawOutlinedRect( x - w + 1, y + 1, x + w - 1, y + h - 1 );
}


void CVisuals::CornerBox(float x, float y, float iWidth, float iMiddle, Color colDraw, float scaling)
{

   /* --- : 1	--- :5
	* |			   |
	* |   : 2	   | : 6
	*
	*
	*
	* | :3		   | :7
	* |			   |
	* --- : 4	--- : 8
	*/

	//D::DrawCorner(x - iWidth, y, iWidth / 2, iWidth / 2, false, false, colDraw); // top left
	//D::DrawCorner(x - iWidth, y + iMiddle, iWidth / 2, iWidth / 2, false, true, colDraw); // bottom left
	//D::DrawCorner(x + iWidth, y, iWidth / 2, iWidth / 2, true, false, colDraw); // top right
	//D::DrawCorner(x + iWidth, y + iMiddle, iWidth / 2, iWidth / 2, true, true, colDraw); // bottom right

	

	D::DrawLine(x, y, x + iWidth / scaling, y, colDraw); //1
	D::DrawLine(x, y, x, y + iMiddle / scaling, colDraw); //2
	
	D::DrawLine(x, y + iMiddle - iMiddle / scaling, x, y + iMiddle, colDraw); //3
	D::DrawLine(x, y + iMiddle, x + iWidth / scaling, y + iMiddle, colDraw); //4

	D::DrawLine(x + iWidth - iWidth / scaling, y, x + iWidth, y, colDraw); //5
	D::DrawLine(x + iWidth, y, x + iWidth, y + iMiddle / scaling, colDraw); //6

	D::DrawLine(x + iWidth, y + iMiddle - iMiddle / scaling, x + iWidth, y + iMiddle, colDraw); //7
	D::DrawLine(x + iWidth - iWidth / scaling, y + iMiddle, x + iWidth, y + iMiddle, colDraw); //8
	

}

inline void Vector::Rotate2D(const float &f)
{
	float _x, _y;

	float s, c;

	M::SinCos(DEG2RAD(f), &s, &c);

	_x = x;
	_y = y;

	x = (_x * c) - (_y * s);
	y = (_x * s) + (_y * c);
}

void CVisuals::DBox(Vector pos, CBaseEntity* entity, Color clr)
{
	_JUNK_BLOCK(jmp_label22)
	ICollideable* coll = entity->GetCollideable();

	Vector min = coll->OBBMins();
	Vector max = coll->OBBMaxs();

	Vector corners[8] =
	{
		Vector(min.x,min.y,min.z),
		Vector(min.x,max.y,min.z),
		Vector(max.x,max.y,min.z),
		Vector(max.x,min.y,min.z),
		Vector(min.x,min.y,max.z),
		Vector(min.x,max.y,max.z),
		Vector(max.x,max.y,max.z),
		Vector(max.x,min.y,max.z)
	};

	float ang = (*(QAngle*)((DWORD)entity + offsets.m_angEyeAngles)).y;

	for (int i = 0; i <= 7; i++)
		corners[i].Rotate2D(ang);

	Vector _corners[8];

	for (int i = 0; i <= 7; i++)
		D::WorldToScreen(pos + corners[i], _corners[i]);

	
	
	int iScreenWidth = 0, iScreenHeight = 0;
	I::Engine->GetScreenSize(iScreenWidth, iScreenHeight);
	
	int x1 = iScreenWidth * 2, y1 = iScreenHeight * 2, x2 = -iScreenWidth, y2 = -iScreenHeight;

	for (int i = 0; i <= 7; i++)
	{
		x1 = (int)(min(x1, _corners[i].x));
		y1 = (int)(min(y1, _corners[i].y));
		x2 = (int)(max(x2, _corners[i].x));
		y2 = (int)(max(y2, _corners[i].y));
	}

	int diff = x2 - x1;
	int diff2 = y2 - y1;


	
	for (int i = 1; i <= 4; i++)
	{
		D::DrawLine((int)(_corners[i - 1].x), (int)(_corners[i - 1].y), (int)(_corners[i % 4].x), (int)(_corners[i % 4].y), clr);
		D::DrawLine((int)(_corners[i - 1].x), (int)(_corners[i - 1].y), (int)(_corners[i + 3].x), (int)(_corners[i + 3].y), clr);
		D::DrawLine((int)(_corners[i + 3].x), (int)(_corners[i + 3].y), (int)(_corners[i % 4 + 4].x), (int)(_corners[i % 4 + 4].y), clr);
	}
}

void CVisuals::HealthBar(Vector bot, Vector top, float health)
{
	_JUNK_BLOCK(jmp_label23)
	float h = (bot.y - top.y);
	float offset = (h / 4.f) + 6;

	UINT hp = h - (UINT)((h * health) / 100); // Percentage

	int Red = 255 - (health*2.55);
	int Green = health*2.55;

	D::DrawOutlinedRect((top.x - offset) - 1, top.y - 1, 3, h + 2, Color::Black());

	D::DrawLine((top.x - offset), top.y + hp, (top.x - offset), top.y + h, Color(Red, Green, 0, 255));
	D::DrawString(F::ESP, top.x - 20 - offset, top.y  + hp, Color(Red, Green, 0, 255), FONT_LEFT, "%.0f", health);
}


void CVisuals::Skeleton(CBaseEntity *Entity, Color color)
{
	_JUNK_BLOCK(jmp_label24)
	studiohdr_t* pStudioModel = I::ModelInfo->GetStudioModel(Entity->GetModel());
	if (pStudioModel)
	{
		static matrix3x4_t pBoneToWorldOut[128];
		if (Entity->SetupBones(pBoneToWorldOut, 128, 256, I::Globals->curtime))
		{
			for (int i = 0; i < pStudioModel->numbones; i++)
			{
				mstudiobone_t* pBone = pStudioModel->pBone(i);
				if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
					continue;

				Vector vBonePos1;
				if (!D::WorldToScreen(Vector(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
					continue;

				Vector vBonePos2;
				if (!D::WorldToScreen(Vector(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
					continue;

				D::DrawLine((int)vBonePos1.x, (int)vBonePos1.y, (int)vBonePos2.x, (int)vBonePos2.y, color);
			}
		}
	}
}

void CVisuals::DrawDLight(CBaseEntity* pEnt, Color	colore)
{
	_JUNK_BLOCK(jmp_label25)
	dlight_t* pElight = I::Effects->CL_AllocElight(pEnt->index);
	pElight->origin = pEnt->GetOrigin() + Vector(0.0f, 0.0f, 35.0f);
	pElight->radius = 100 * Vars.Visuals.DLightRadius;
	pElight->color = colore;
	pElight->die = I::Globals->curtime + 0.05f;
	pElight->decay = pElight->radius / 5.0f;
	pElight->key = pEnt->index;

	dlight_t* pDlight = I::Effects->CL_AllocDlight(pEnt->index);
	pDlight->origin = pEnt->GetOrigin();
	pDlight->radius = 100 * Vars.Visuals.DLightRadius;
	pDlight->color = colore;
	pDlight->die = I::Globals->curtime + 0.05f;
	pDlight->decay = pDlight->radius;
	pDlight->key = pEnt->index;
}

void CVisuals::DrawWeapon(int topx, int topy, HFont hFont, CBaseEntity* pEnt)
{
	_JUNK_BLOCK(jmp_label26)
	/*Sanity Checks*/
	auto pWeapon = pEnt->GetWeapon();
	if (!pWeapon) return;
	/*Declare*/
	auto WeaponIcon = pWeapon->GetCSWpnData()->iconWeapon->charinFont;
	/*Concat Strings*/

	D::DrawString(hFont, topx, topy, (Color(255, 255, 255, 255)), FONT_CENTER, "%c", WeaponIcon);
}

void CVisuals::DrawHitbox( matrix3x4a_t* matrix, Vector bbmin, Vector bbmax, int bone, Color color )
{
	_JUNK_BLOCK(jmp_label27)
	Vector points[] = { 
		Vector( bbmin.x, bbmin.y, bbmin.z ),
		Vector( bbmin.x, bbmax.y, bbmin.z ),
		Vector( bbmax.x, bbmax.y, bbmin.z ),
		Vector( bbmax.x, bbmin.y, bbmin.z ),
		Vector( bbmax.x, bbmax.y, bbmax.z ),
		Vector( bbmin.x, bbmax.y, bbmax.z ),
		Vector( bbmin.x, bbmin.y, bbmax.z ),
		Vector( bbmax.x, bbmin.y, bbmax.z )
	};

	Vector pointsTransformed[ 8 ];

	for( int index = 0; index <= 8; ++index )
	{
		if( index != 0 )
			points[ index ] = ( ( ( ( points[ index ] + points[ 0 ] ) * .5f ) + points[ index ] ) * .5f );

		M::VectorTransform( points[ index ], matrix[ bone ], pointsTransformed[ index ] );
	}

	D::Draw3DBox( pointsTransformed, color );
}

void CVisuals::Hitboxes(CBaseEntity *Entity, Color color)
{
	_JUNK_BLOCK(jmp_label28)
	matrix3x4a_t matrix[MAXSTUDIOBONES];

	if (!Entity->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, I::Engine->GetLastTimeStamp()))
	{

		return;
	}
	studiohdr_t* pStudioModel = I::ModelInfo->GetStudioModel(Entity->GetModel());
	if (!pStudioModel)
	{

		return;
	}
	mstudiohitboxset_t* set = pStudioModel->pHitboxSet(Entity->GetHitboxSet());
	if (!set)
	{

		return;
	}
	for (int i = 0; i < set->numhitboxes; i++)
	{
		mstudiobbox_t* hitbox = set->pHitbox(i);


		if (!hitbox)
		{

			return;
		}
		int bone = hitbox->bone;

		Vector vMaxUntransformed = hitbox->bbmax;
		Vector vMinUntransformed = hitbox->bbmin;
		/*Vector center = ((vMinUntransformed + vMaxUntransformed) * .5f);
		 D::DrawCircle(center.x, center.y, hitbox->radius*.2, 1, Color::LightBlue());*/
		if (hitbox->radius != -1.f)
		{
			vMinUntransformed -= Vector(hitbox->radius*.8, hitbox->radius*.8, hitbox->radius*.8);
			vMaxUntransformed += Vector(hitbox->radius*.8, hitbox->radius*.8, hitbox->radius*.8);
		}

		Vector points[] = {
			Vector(vMinUntransformed.x, vMinUntransformed.y, vMinUntransformed.z),
			Vector(vMinUntransformed.x, vMaxUntransformed.y, vMinUntransformed.z),
			Vector(vMinUntransformed.x, vMinUntransformed.y, vMaxUntransformed.z),
			Vector(vMinUntransformed.x, vMaxUntransformed.y, vMaxUntransformed.z),
			Vector(vMaxUntransformed.x, vMinUntransformed.y, vMaxUntransformed.z),
			Vector(vMaxUntransformed.x, vMaxUntransformed.y, vMinUntransformed.z),
			Vector(vMaxUntransformed.x, vMaxUntransformed.y, vMaxUntransformed.z),
			Vector(vMaxUntransformed.x, vMinUntransformed.y, vMaxUntransformed.z)
		};

		Vector pointsTransformed[8];

		for (int index = 0; index < 8; index++)
		{
			M::VectorTransform(points[index], matrix[hitbox->bone], pointsTransformed[index]);
		}

		D::Draw3DBox(pointsTransformed, color);

	}

}

void CVisuals::Nightmode()
{
	_JUNK_BLOCK(jmp_label29)
	{
		CBaseEntity* pLocal = I::ClientEntList->GetClientEntity(I::Engine->GetLocalPlayer());

		ConVar* r_drawspecificstaticprop = I::Cvar->FindVar("r_drawspecificstaticprop");
		SpoofedConvar* r_drawspecificstaticprop_s = new SpoofedConvar(r_drawspecificstaticprop);
		r_drawspecificstaticprop_s->SetInt(0);

		static auto sv_skyname = I::Cvar->FindVar("sv_skyname");
		sv_skyname->nFlags &= ~(1 << 14);

		for (MaterialHandle_t i = I::MaterialSystem->FirstMaterial(); i != I::MaterialSystem->InvalidMaterial(); i = I::MaterialSystem->NextMaterial(i))
		{
			IMaterial* pMaterial = I::MaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;
			if (Vars.Visuals.Removals.NightMode)
			{

				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(0.60, 0.60, 0.60);
				}

				if (strstr(pMaterial->GetTextureGroupName(), "World"))
				{
					sv_skyname->SetValue("sky_csgo_night02");
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
					pMaterial->ColorModulate(0.1, 0.1, 0.1);
				}

				if (strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
				{
					pMaterial->ColorModulate(0.3, 0.3, 0.3);
				}

			}
			/*if (!Vars.Visuals.Removals.NightMode)
			{
				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(1, 1, 1);
				}
				if ((strstr(pMaterial->GetTextureGroupName(), "World")) || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
				{
					sv_skyname->SetValue("sky_csgo_night02");
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
					pMaterial->ColorModulate(1, 1, 1);
				}
			}*/
		}
	}
}

void CVisuals::pSpecList()
{
	_JUNK_BLOCK(jmp_label30)
	int ix = 1;
	for (int i = 0; i <= I::Globals->maxClients; i++)
	{
		CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);

		if (Entity &&  Entity != G::LocalPlayer)
		{
			if (Entity->GetAlive())
				continue;

			player_info_t pinfo;
			if (I::Engine->GetPlayerInfo(i, &pinfo))
			{
				DWORD obs = Entity->GetOBS();

				if (obs)
				{
					CBaseEntity *pTarget = I::ClientEntList->GetClientEntityFromHandle(obs);
					player_info_t pinfo2;

					if (pTarget)
					{
						if (I::Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
						{

							if (pTarget->GetIndex() == G::LocalPlayer->GetIndex() && pTarget->GetAlive())
							{

								//		char buf[255]; sprintf_s(buf, "%s => %s", pinfo.name, pinfo2.name);
								char buf[255]; sprintf_s(buf, "%s is Watching You ", pinfo.name);
								//D::DrawString(F::ESP, 16, 55 + (15 * ix), Color::Red(), FONT_LEFT, charenc("%s"), buf);

								D::DrawString(F::ESP, 16, 450 + (15 * ix), Color::White(), FONT_LEFT, charenc("%s"), buf);

								ix++;
							}
						}
					}
				}
			}
		}
	}
}
void CVisuals::DrawFOVCrosshair()
{
	_JUNK_BLOCK(jmp_label31)
	int xs;
	int ys;
	float FoV;
	FoV = Vars.Legitbot.Aimbot.FOV;
	I::Engine->GetScreenSize(xs, ys);
	I::Engine->GetScreenSize(xs, ys);
	xs /= 2; ys /= 2;
	D::DrawCircle(xs, ys, FoV * 6.25, FoV * 6.25, Color(255, 255, 255, 255));
}
void CVisuals::DrawCrosshair( Color color )
{
	_JUNK_BLOCK(jmp_label32)
	int screenW, screenH;
	I::Engine->GetScreenSize( screenW, screenH );

	int crX = screenW / 2, crY = screenH / 2;
	int dy = screenH / G::FOV;
	int dx = screenW / G::FOV;
	int drX;
	int drY;

	if( Vars.Visuals.CrosshairType == 0 )
	{


		if (Vars.Visuals.Removals.VisualRecoil)
		{
			drX = crX - (int)(dx * (G::LocalPlayer->GetPunch().y * 2));
			drY = crY + (int)(dy * (G::LocalPlayer->GetPunch().x * 2));
		}
		else
		{
			drX = crX - dx * (G::LocalPlayer->GetPunch().y);
			drY = crY + dy * (G::LocalPlayer->GetPunch().x);
		}

			
	}
	else
	{
		drX = crX ;
		drY = crY ;
	}

	if( Vars.Visuals.CrosshairStyle == 0 )//cross
	{
		D::DrawLine( drX - 5, drY, drX + 5, drY, color );
		D::DrawLine( drX, drY - 5, drX, drY + 5, color );
	}

	if( Vars.Visuals.CrosshairStyle == 1 )//kreis
	{
		//D::DrawCircle( drX, drY, 5, 30, color );
		if (G::LocalPlayer->GetAlive() && I::Engine->IsInGame() && I::Engine->IsConnected())
		{
			CBaseCombatWeapon* pWeapon = G::LocalPlayer->GetWeapon();//m8 ich hab auf + auffnahme gelegt also das am numpad aso

			auto accuracy = (pWeapon->GetInaccuracy() + pWeapon->GetSpreadReal()) * 500.f;

			if (pWeapon->IsGun())
				D::DrawCircle(drX, drY, Vars.Visuals.CrosshairSpread ? accuracy + 3 : 6, 30, color);
			else
				D::DrawCircle(drX, drY, 5, 30, color);
		}
		else
		{
			D::DrawCircle(drX, drY, 6, 30, color);
		}
	}

	if (Vars.Visuals.CrosshairStyle == 2)
	{
		POINT Middle; Middle.x = drX; Middle.y = drY;
		int a = (int)(drY / 60);
		float gamma = atan(a / a);
		static float rainbow;
		rainbow += 0.005f;
		if (rainbow > 1.f) rainbow = 0.f;

		static int rotationdegree = 0;

		if (rotationdegree > 89) { rotationdegree = 0; }

		for (int i = 0; i < 4; i++)
		{
			std::vector <int> p;
			p.push_back(a * sin(DEG2RAD(rotationdegree + (i * 90))));									//p[0]		p0_A.x
			p.push_back(a * cos(DEG2RAD(rotationdegree + (i * 90))));									//p[1]		p0_A.y
			p.push_back((a / cos(gamma)) * sin(DEG2RAD(rotationdegree + (i * 90) + RAD2DEG(gamma))));	//p[2]		p0_B.x
			p.push_back((a / cos(gamma)) * cos(DEG2RAD(rotationdegree + (i * 90) + RAD2DEG(gamma))));	//p[3]		p0_B.y

			D::DrawLine(Middle.x, Middle.y, Middle.x + p[0], Middle.y - p[1], Color::FromHSB(rainbow, 1.f, 1.f));
			D::DrawLine(Middle.x + p[0], Middle.y - p[1], Middle.x + p[2], Middle.y - p[3], Color::FromHSB(rainbow, 1.f, 1.f));
		}
		rotationdegree++;
	}
	_JUNK_BLOCK(jmp_label33)
	if( Vars.Visuals.CrosshairStyle == 3 )
	{
		if (G::LocalPlayer->GetAlive() && I::Engine->IsInGame() && I::Engine->IsConnected())
		{
			CBaseCombatWeapon* pWeapon = G::LocalPlayer->GetWeapon();

			auto accuracy = (pWeapon->GetInaccuracy() + pWeapon->GetSpreadReal()) * 500.f;

			if (pWeapon->IsGun())
			{
				D::DrawCircle(drX, drY, Vars.Visuals.CrosshairSpread ? accuracy + 3 : 6, 30, color);
				D::DrawLine(drX - 5, drY, drX + 5, drY, color);
				D::DrawLine(drX, drY - 5, drX, drY + 5, color);
			}
			else
			{
				D::DrawLine(drX - 5, drY, drX + 5, drY, color);
				D::DrawLine(drX, drY - 5, drX, drY + 5, color);
			}
		}
		else
		{
			D::DrawCircle(drX, drY, 6, 30, color);
		}
	}
}