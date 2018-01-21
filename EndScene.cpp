#include "Cheat.h"
#include "Menu.h"

void GUI_Init( IDirect3DDevice9* pDevice );

EndSceneFn oEndScene;
long __stdcall Hooks::EndScene(IDirect3DDevice9* pDevice)
{
	if (!G::d3dinit)
		GUI_Init(pDevice);

	H::D3D9->ReHook();

	ImGui::GetIO().MouseDrawCursor = Vars.Menu.Opened;

	ImGui_ImplDX9_NewFrame();

	if (Vars.Menu.Opened)
	{
		int pX, pY;
		I::InputSystem->GetCursorPosition(&pX, &pY);
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos.x = (float)(pX);
		io.MousePos.y = (float)(pY);

		ImGui::Begin(charenc("FH4x by Nertigel"), &Vars.Menu.Opened, ImVec2(230, 180), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		{
			ImGui::Checkbox(charenc("Ragebot"), &Vars.Menu.Ragebot);
			ImGui::Checkbox(charenc("Legitbot"), &Vars.Menu.Legitbot);
			ImGui::Checkbox(charenc("Visuals"), &Vars.Menu.Visual);
			ImGui::Checkbox(charenc("Misc"), &Vars.Menu.Misc);
			ImGui::Checkbox(charenc("Skins"), &Vars.Menu.Skins);
			ImGui::Checkbox(charenc("PlayerList"), &Vars.Menu.Playerlist);

			//playerlsit machen doer

			ImGui::Separator();
			ImGui::Columns(2, charenc("##config-settings"), false);
			if (ImGui::Button(charenc("Save Config"), ImVec2(93.f, 20.f))) Config->Save();
			ImGui::NextColumn();
			if (ImGui::Button(charenc("Load Config"), ImVec2(93.f, 20.f))) Config->Load();
			ImGui::Columns(1);
		}
		ImGui::End(); //End main window

		if (Vars.Menu.Ragebot)
		{
			ImGui::Begin(charenc("Ragebot Settings"), &Vars.Menu.Ragebot, ImVec2(300, 500), 0.9f, ImGuiWindowFlags_NoCollapse);
			{
				ImGui::Separator();
				ImGui::Text(charenc("Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enabled"), &Vars.Ragebot.Enabled);
				ImGui::Separator();
				ImGui::Checkbox(charenc("Use Weapon Cfg"), &Vars.Ragebot.WeaponCFGRage);
				if (ImGui::Button(charenc(" Save Current Weapon "))) E::RageBot->ChangeSetRage();
				ImGui::Separator();
				ImGui::Combo(charenc("Aimbot Key"), &Vars.Ragebot.HoldKey, keyNames, ARRAYSIZE(keyNames));
				ImGui::Checkbox(charenc("Use Key"), &Vars.Ragebot.Hold);
				ImGui::Checkbox(charenc("Auto Fire"), &Vars.Ragebot.AutoFire);
				//ImGui::SliderFloat( charenc( "FOV" ), &Vars.Ragebot.FOV, 1.f, 180.f, "%.0f" );
				ImGui::Checkbox(charenc("PSilent"), &Vars.Ragebot.Silent);
				ImGui::Checkbox(charenc("Aim Step"), &Vars.Ragebot.Aimstep);
				ImGui::SliderFloat(charenc("Angle Per Tick"), &Vars.Ragebot.AimstepAmount, 1.f, 180.f, "%.0f");
				ImGui::Separator();

				ImGui::Text(charenc("Target"));
				ImGui::Separator();
				//ImGui::Combo( charenc( "Mode" ), &Vars.Ragebot.TargetMethod, targetMode, ARRAYSIZE( targetMode ) );
				ImGui::Combo(charenc("Hitbox"), &Vars.Ragebot.Hitbox, aimBoxes, ARRAYSIZE(aimBoxes));
				ImGui::Checkbox(charenc("Prefer Hitbox"), &Vars.Ragebot.PreferHitbox);
				ImGui::Checkbox(charenc("Smart BodyAim [Only Works Without Multipoint]"), &Vars.Ragebot.SmartHitbox);
				ImGui::SliderInt(charenc("BodyAim Min Health"), &Vars.Ragebot.SmartHitboxHealth, 1.f, 100.f, "%.0f");
				ImGui::Separator();
				/*ImGui::Text(charenc("Auto Resolver[Beta]"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Pitch Fix"), &Vars.Ragebot.Pitchfix);
				ImGui::Combo(charenc("Resolver Mode"), &Vars.Ragebot.Resolvermode, Resolvermode, ARRAYSIZE(Resolvermode));
				ImGui::Separator();*/
				ImGui::Checkbox(charenc("Friendly Fire"), &Vars.Ragebot.FriendlyFire);
				ImGui::Checkbox(charenc("Auto Wall"), &Vars.Ragebot.AutoWall);
				ImGui::Separator();
				ImGui::Text(charenc("Extras"));
				ImGui::Separator();
				/*ImGui::Checkbox(charenc("BackTrack"), &Vars.Ragebot.BackTrack);*/
				ImGui::Checkbox(charenc("FakeLag Fix"), &Vars.Ragebot.FakeLagfix);
				ImGui::Checkbox(charenc("Hitscan"), &Vars.Ragebot.HitScanPerformance);
				ImGui::Checkbox(charenc("MultiPoint"), &Vars.Ragebot.Multipoint);
				/*ImGui::SliderFloat(charenc("MultiPointIntense"), &Vars.Ragebot.Multipointintense, 0.f, 9.f, "%.0f");*/
				/*ImGui::Checkbox(charenc("Resolver [Experimental]"), &Vars.Ragebot.Fakeanglefixbeta);*/
				ImGui::SliderFloat(charenc("Multipoint Scale"), &Vars.Ragebot.Multipointscale, 0.1f, 1.f, "%.1f");
				ImGui::Checkbox(charenc("Draw Multipints [Debug]"), &Vars.Visuals.DrawMultipints);
				ImGui::Separator();
				ImGui::Text(charenc("Accuracy"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Auto Stop"), &Vars.Ragebot.AutoStop);
				ImGui::Checkbox(charenc("Auto Crouch"), &Vars.Ragebot.AutoCrouch);
				ImGui::Checkbox(charenc("Auto Scope"), &Vars.Ragebot.AutoScope);
				ImGui::Checkbox(charenc("Auto Revolver"), &Vars.Misc.AutoRevovler);
				ImGui::Checkbox(charenc("Pseudo No Spread"), &Vars.Ragebot.Pseudonospread);
				ImGui::Checkbox(charenc("Inaccuracy"), &Vars.Ragebot.HitChance);
				ImGui::SliderFloat(charenc("%"), &Vars.Ragebot.HitChanceAmt, 1.f, 100.f, "%.0f");
				ImGui::SliderFloat(charenc("Min Damage"), &Vars.Ragebot.AutoWallDmg, 0.1f, 120.f, "%.1f");
				ImGui::Separator();
				ImGui::Text(charenc("Anti-Aim"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Anti-Aim Enabled"), &Vars.Ragebot.Antiaim.Enabled);
				ImGui::Combo(charenc("Pitch"), &Vars.Ragebot.Antiaim.Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));//
				ImGui::Combo(charenc("RealYaw"), &Vars.Ragebot.Antiaim.RealYaw, antiaimrealyaw, ARRAYSIZE(antiaimrealyaw));
				ImGui::Combo(charenc("FakeYaw"), &Vars.Ragebot.Antiaim.FakeYaw, antiaimfakeyaw, ARRAYSIZE(antiaimfakeyaw));
				ImGui::Checkbox(charenc("At Players"), &Vars.Ragebot.Antiaim.AimAtPlayer);
				ImGui::Checkbox(charenc("Flip on Hit"), &Vars.Ragebot.Antiaim.flipAAonhit);
				ImGui::Checkbox(charenc("Shuffle"), &Vars.Ragebot.Antiaim.Shuffle);
				ImGui::Checkbox(charenc("lby"), &Vars.Ragebot.Antiaim.FakeEdge);
				ImGui::Separator();
				ImGui::Text(charenc("Anti-Untrusted"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Turn ON! For Official Valve Servers"), &Vars.Ragebot.UntrustedCheck);
			}
			ImGui::End(); //End Ragebot window
		}
		if (Vars.Menu.Legitbot)
		{
			ImGui::Begin(charenc("Legitbot Settings"), &Vars.Menu.Legitbot, ImVec2(300, 500), 0.9f, ImGuiWindowFlags_NoCollapse);
			{
				ImGui::Separator();
				ImGui::Text(charenc("Aimbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable Aimbot"), &Vars.Legitbot.Aimbot.Enabled);
				ImGui::Separator();
				ImGui::Checkbox(charenc("Use Weapon Cfg"), &Vars.Legitbot.Aimbot.Weaponcfg);
				if (ImGui::Button(charenc(" Save Current Weapon "))) E::LegitBot->ChangeSet();
				ImGui::Checkbox(charenc("Autoaim"), &Vars.Legitbot.Aimbot.AlwaysOn);
				ImGui::Combo(charenc("Aimbot Key"), &Vars.Legitbot.Aimbot.Key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Checkbox(charenc("Aim on Key"), &Vars.Legitbot.Aimbot.OnKey);
				ImGui::Checkbox(charenc("pSilent"), &Vars.Legitbot.Aimbot.Silent);
				/*ImGui::Checkbox(charenc("Max Aim Speed"), &Vars.Legitbot.Aimbot.MaxSpeed);*/
				ImGui::Checkbox(charenc("Friendly Fire"), &Vars.Legitbot.Aimbot.FriendlyFire);
				ImGui::Separator();
				ImGui::Combo(charenc("Hitbox"), &Vars.Legitbot.Aimbot.Hitbox, aimBoxesLegit, ARRAYSIZE(aimBoxesLegit));
				ImGui::SliderFloat(charenc("FOV"), &Vars.Legitbot.Aimbot.FOV, 0.1f, 45.f, "%.1f");
				ImGui::SliderFloat(charenc("Aim Speed"), &Vars.Legitbot.Aimbot.Speed, 0.f, 100.f, "%.0f");
				ImGui::SliderFloat(charenc("RCS %"), &Vars.Legitbot.Aimbot.RCSAmount, 1.f, 100.f, "%.0f");
				ImGui::Checkbox(charenc("Standalone RCS"), &Vars.Legitbot.Aimbot.RCS);
				ImGui::SliderFloat(charenc("Standalone RCS %"), &Vars.Legitbot.Aimbot.RCSAMT, 1.f, 100.f, "%.0f");
				ImGui::Checkbox(charenc("BackTrack"), &Vars.Legitbot.Aimbot.LegitBacktrack);
				ImGui::SliderFloat(charenc("Ticks"), &Vars.Legitbot.Aimbot.Ticks, 1.f, 25.f, "%.0f");
				ImGui::Separator();
				ImGui::Text(charenc("Extras"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("AutoFastScope"), &Vars.Legitbot.Aimbot.Fastzoom);
				ImGui::Checkbox(charenc("Sniper-Pistol Autoswitch"), &Vars.Legitbot.Aimbot.FastzoomSwitch);
				ImGui::Checkbox(charenc("Smokecheck"), &Vars.Legitbot.Aimbot.Smokecheck);
				ImGui::Checkbox(charenc("Use Mouse Event"), &Vars.Legitbot.Aimbot.Faceitmode);
				ImGui::Checkbox(charenc("Legit AA [Only Works With pSilent]"), &Vars.Legitbot.Aimbot.legitaa);
				ImGui::Separator();

				ImGui::Text(charenc("Triggerbot"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable Triggerbot"), &Vars.Legitbot.Triggerbot.Enabled);
				ImGui::Checkbox(charenc("Auto Fire"), &Vars.Legitbot.Triggerbot.AutoFire);
				ImGui::Combo(charenc("Triggerbot Key"), &Vars.Legitbot.Triggerbot.Key, keyNames, ARRAYSIZE(keyNames));
				ImGui::Checkbox(charenc("Inaccuracy"), &Vars.Legitbot.Triggerbot.HitChance);
				ImGui::SliderFloat(charenc("%"), &Vars.Legitbot.Triggerbot.HitChanceAmt, 1.f, 100.f, "%.0f");
				ImGui::Separator();

				ImGui::Text(charenc("Filter"));
				ImGui::Separator();
				ImGui::BeginChild(charenc("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 6));
				{
					ImGui::Selectable(charenc("Head"), &Vars.Legitbot.Triggerbot.Filter.Head);
					ImGui::Selectable(charenc("Chest"), &Vars.Legitbot.Triggerbot.Filter.Chest);
					ImGui::Selectable(charenc("Stomach"), &Vars.Legitbot.Triggerbot.Filter.Stomach);
					ImGui::Selectable(charenc("Arms"), &Vars.Legitbot.Triggerbot.Filter.Arms);
					ImGui::Selectable(charenc("Legs"), &Vars.Legitbot.Triggerbot.Filter.Legs);
					ImGui::Selectable(charenc("Friendlies"), &Vars.Legitbot.Triggerbot.Filter.Friendly);
				}
				ImGui::EndChild();
			}
			ImGui::End(); //End Legitbot window
		}
		if (Vars.Menu.Visual)
		{
			ImGui::Begin(charenc("Visual Settings"), &Vars.Menu.Visual, ImVec2(300, 500), 0.9f, ImGuiWindowFlags_NoCollapse);
			{
				ImGui::Separator();
				ImGui::Text(charenc("Visuals"));
				ImGui::Separator();
				ImGui::Columns(2, charenc("##c1"), false);
				ImGui::Checkbox(charenc("Enable Visuals"), &Vars.Visuals.Enabled);
				ImGui::Separator();
				ImGui::Checkbox(charenc("Glow"), &Vars.Visuals.Glow);
				ImGui::Checkbox(charenc("Hitmarker"), &Vars.Visuals.Hitmarker);
				ImGui::Checkbox(charenc("Hitmarker Sounds"), &Vars.Visuals.Hitmarkersound);
				ImGui::Checkbox(charenc("Show Spectators"), &Vars.Visuals.pSpecList);
				/*ImGui::Checkbox(charenc("Show Last Pos"), &Vars.Visuals.LastPos);*/
				ImGui::NextColumn();
				ImGui::Checkbox(charenc("Aim Trace Line"), &Vars.Visuals.BulletTrace);
				ImGui::Checkbox(charenc("Head Dot"), &Vars.Visuals.HitBoxDot);
				ImGui::Checkbox(charenc("DLights"), &Vars.Visuals.DLight);
				ImGui::Checkbox(charenc("Rainbow DLights"), &Vars.Visuals.RainbowDlight);
				ImGui::Columns(1);
				ImGui::Combo(charenc("Box Type"), &Vars.Visuals.BoxType, BoxType, ARRAYSIZE(BoxType));
				ImGui::SliderFloat(charenc("DLight Radius"), &Vars.Visuals.DLightRadius, 1.f, 100.f, "%.0f");
				ImGui::SliderFloat(charenc("Trace Length"), &Vars.Visuals.BulletTraceLength, 1.f, 3000.f, "%.0f");
				ImGui::SliderFloat(charenc("Fov Changer"), &Vars.Visuals.FOVAdd, -100.f, 100.f, "%.0f");
				/*ImGui::SliderFloat(charenc("Fade Esp"), &Vars.Visuals.Info.AlphaFade, -255.f, 255.f, "%.0f");*/

				ImGui::Separator();
				ImGui::Text(charenc("Info"));
				ImGui::Separator();
				ImGui::BeginChild(charenc("info"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 8));
				{
					ImGui::Selectable(charenc(" Name "), &Vars.Visuals.Info.Name);
					ImGui::Selectable(charenc(" Health "), &Vars.Visuals.Info.Health);
					ImGui::Selectable(charenc(" Weapon "), &Vars.Visuals.Info.Weapon);
					ImGui::Selectable(charenc(" BackTrack "), &Vars.Visuals.BackTrack);
					ImGui::Selectable(charenc(" LBY Indicator "), &Vars.Visuals.Info.LBY);
					ImGui::Selectable(charenc(" Flashed "), &Vars.Visuals.Info.Flashed);
					ImGui::Selectable(charenc(" Skeleton "), &Vars.Visuals.Skeleton);
					ImGui::Selectable(charenc(" Hitbox "), &Vars.Visuals.DrawHitbox);
				}
				ImGui::EndChild();
				ImGui::Separator();

				ImGui::Text(charenc("Filter"));
				ImGui::Separator();
				ImGui::BeginChild(charenc("filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 8));
				{
					ImGui::Selectable(charenc(" Enemies "), &Vars.Visuals.Filter.Enemies);
					ImGui::Selectable(charenc(" Friendlies "), &Vars.Visuals.Filter.Friendlies);
					ImGui::Selectable(charenc(" Hostages "), &Vars.Visuals.Info.Hostage);
					ImGui::Selectable(charenc(" Weapons "), &Vars.Visuals.Filter.Weapons);
					ImGui::Selectable(charenc(" Weapon Icons "), &Vars.Visuals.Filter.DrawWeapon);
					ImGui::Selectable(charenc(" Nades "), &Vars.Visuals.Filter.Nades);
					ImGui::Selectable(charenc(" C4 "), &Vars.Visuals.Filter.C4);
					ImGui::Selectable(charenc(" Chickens "), &Vars.Visuals.Filter.Chickens);
				}
				ImGui::EndChild();
				ImGui::Separator();
				ImGui::Text(charenc("Chams"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Enable Chams"), &Vars.Visuals.Chams.Enabled);
				ImGui::Combo(charenc("Mode"), &Vars.Visuals.Chams.Mode, chamsMode, ARRAYSIZE(chamsMode));
				ImGui::Checkbox(charenc("XQZ"), &Vars.Visuals.Chams.XQZ);
				ImGui::Checkbox(charenc("Rainbow"), &Vars.Visuals.Chams.Rainbow);
				/*	ImGui::Checkbox(charenc("Ghost"), &Vars.Visuals.Chams.Fake);*/
				ImGui::Separator();
				ImGui::Text(charenc("Extras"));
				ImGui::Separator();
				ImGui::Columns(2, charenc("##c2"), false);
				ImGui::Checkbox(charenc("No Hands"), &Vars.Visuals.Removals.Hands);
				ImGui::Checkbox(charenc("Wireframe Hands"), &Vars.Visuals.Removals.WireframeHands);
				ImGui::Checkbox(charenc("No Weapon"), &Vars.Visuals.Removals.Weapon);
				ImGui::Checkbox(charenc("No PostProcess"), &Vars.Visuals.Removals.Postprocess);
				ImGui::NextColumn();
				ImGui::Checkbox(charenc("No Visual Recoil"), &Vars.Visuals.Removals.VisualRecoil);
				ImGui::Checkbox(charenc("No Flash"), &Vars.Visuals.Removals.Flash);
				ImGui::Checkbox(charenc("No Scope"), &Vars.Visuals.Removals.Scope);
				ImGui::Checkbox(charenc("Rave Sky"), &Vars.Visuals.Removals.RaveSky);
				ImGui::Checkbox(charenc("Night Mode"), &Vars.Visuals.Removals.NightMode);
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text(charenc("Crosshair"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Crosshair Enabled"), &Vars.Visuals.CrosshairOn);
				ImGui::Checkbox(charenc("Show Spread"), &Vars.Visuals.CrosshairSpread);
				ImGui::Checkbox(charenc("Show Fov"), &Vars.Visuals.CrosshairFOV);
				ImGui::Combo(charenc("Type"), &Vars.Visuals.CrosshairType, crosshairType, ARRAYSIZE(crosshairType));
				ImGui::Combo(charenc("Style"), &Vars.Visuals.CrosshairStyle, crosshairStyle, ARRAYSIZE(crosshairStyle));
			}
			ImGui::End(); //End Visuals window
		}
		if (Vars.Menu.Misc)
		{
			ImGui::Begin(charenc("Misc Settings"), &Vars.Menu.Misc, ImVec2(300, 500), 0.9f, ImGuiWindowFlags_NoCollapse);
			{
				ImGui::Separator();
				ImGui::Text(charenc("Movement"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Bunny Hop"), &Vars.Misc.Bhop);
				ImGui::Checkbox(charenc("Autostrafe"), &Vars.Misc.AutoStrafe);
				ImGui::Checkbox(charenc("RageStrafer"), &Vars.Misc.RageAutoStrafe);
				ImGui::Separator();
				ImGui::Text(charenc("Custom Name"));
				ImGui::Separator();
				ImGui::PushItemWidth(180);
				static char buf1[128] = ""; ImGui::InputText(charenc("##Name"), buf1, 128);
				ImGui::SameLine();
				ImGui::PushItemWidth(50);
				if (ImGui::Button(charenc(" Change Name "))) E::Misc->ChangeName(buf1);
				ImGui::Separator();
				ImGui::Text(charenc("Custom ClanTag"));
				ImGui::Separator();
				ImGui::PushItemWidth(180);
				ImGui::Text(charenc("ClanTag"));
				static char buf3[128] = ""; ImGui::InputText(charenc("##Tag"), buf3, 128);
				ImGui::Text(charenc("ClanTag Name"));
				static char buf4[128] = ""; ImGui::InputText(charenc("##Tname"), buf4, 128);
				ImGui::SameLine();
				ImGui::PushItemWidth(50);
				if (ImGui::Button(charenc(" Change ClanTag "))) E::Misc->SetClanTag(buf3, buf4);
				ImGui::Separator();
				ImGui::PushItemWidth(180);
				ImGui::Checkbox(charenc("Animated ClanTag"), &Vars.Misc.aniclantag);
				ImGui::InputText(charenc("##ClanTag"), Vars.Misc.clantagbuffer, 128);
				ImGui::InputText(charenc("##Animation Chars"), Vars.Misc.tag_chars, 10);
				ImGui::SliderInt(charenc("Start Interval"), &Vars.Misc.interval, 1, 100, "%.0f");
				ImGui::SliderInt(charenc("End Interval"), &Vars.Misc.interval_end, 1, 150, "%.0f");
				ImGui::Separator();
				ImGui::Text(charenc("1337 Tagz"));
				ImGui::PushItemWidth(50);
				if (ImGui::Button(charenc(" Valve "))) E::Misc->SetClanTag("[VALV\xE1\xB4\xB1]", "Valve");
				ImGui::SameLine();
				if (ImGui::Button(charenc(" NiP "))) E::Misc->SetClanTag("NiP", "Ninjas");
				ImGui::SameLine();
				if (ImGui::Button(charenc(" ENVYUS "))) E::Misc->SetClanTag("ENVYUS", "EnVyUs");
				ImGui::SameLine();
				if (ImGui::Button(charenc(" Nazi "))) E::Misc->SetClanTag("卐 Heil 卐", "卐 88 卐");
				ImGui::SameLine();
				if (ImGui::Button(charenc(" Virtus.Pro "))) E::Misc->SetClanTag("Virtus.Pro", "Virtus");
				ImGui::SameLine();
				if (ImGui::Button(charenc(" Na'Vi "))) E::Misc->SetClanTag("Na'Vi", "NAVI");
				ImGui::SameLine();
				if (ImGui::Button(charenc(" FH4x ")))E::Misc->SetClanTag("->FH4x<-", "FerrityH4x");
				ImGui::SameLine();
				if (ImGui::Button(charenc(" Hide "))) E::Misc->SetClanTag("\n 卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐卐", "no name");
				ImGui::Separator();
				ImGui::Text(charenc("Chat Spam"));
				ImGui::Separator();
				ImGui::PushItemWidth(180);
				static char buf2[128] = ""; ImGui::InputText(charenc("##File"), buf2, 128);
				ImGui::SameLine();
				ImGui::PushItemWidth(50);
				if (ImGui::Button(charenc("Load File"))) E::Misc->ReadChatspam(buf2);
				ImGui::PushItemWidth(180);
				ImGui::Combo(charenc("Mode"), &Vars.Misc.ChatSpamMode, chatspamMode, ARRAYSIZE(chatspamMode));
				ImGui::Checkbox(charenc("ChatSpam"), &Vars.Misc.ChatSpam);
				ImGui::Separator();
				ImGui::Checkbox(charenc("Teleport"), &Vars.Misc.Teleport);
				ImGui::Combo(charenc("Teleport Key"), &Vars.Misc.TeleportKey, keyNames, ARRAYSIZE(keyNames));
				ImGui::Separator();
				ImGui::Checkbox(charenc("AirStuck"), &Vars.Misc.AirStuck);
				ImGui::Combo(charenc("AirStuck Key"), &Vars.Misc.AirStuckKey, keyNames, ARRAYSIZE(keyNames));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Block Teammates"), &Vars.Misc.AutoBlocker);
				ImGui::Combo(charenc("Block Key"), &Vars.Misc.AutoblockerKey, keyNames, ARRAYSIZE(keyNames));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Fake Walk"), &Vars.Misc.FakeWalk);
				ImGui::Combo(charenc("Walk Key"), &Vars.Misc.FakewalkKey, keyNames, ARRAYSIZE(keyNames));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Fakelag"), &Vars.Misc.fakelag);
				ImGui::SliderInt(charenc("Fakelag Choke"), &Vars.Misc.fakelagchoke, 0, 20, "%.0f");
				ImGui::SliderInt(charenc("Fakelag Send"), &Vars.Misc.fakelagsend, 0, 20, "%.0f");
				ImGui::Separator();
				if (ImGui::Button(charenc(" Bypass sv_cheats "))) E::Misc->svcheats();
				ImGui::Separator();
				ImGui::Text(charenc("Extras"));
				ImGui::Separator();
				ImGui::Checkbox(charenc("Ranks"), &Vars.Misc.Ranks);
				ImGui::Checkbox(charenc("Auto Accept"), &Vars.Misc.AutoAccept);
				ImGui::Checkbox(charenc("AutoPistol"), &Vars.Misc.AutoPistol);
				ImGui::Checkbox(charenc("Watermark"), &Vars.Misc.Watermark);
				ImGui::Checkbox(charenc("Clock"), &Vars.Misc.Timestamp);
				ImGui::Checkbox(charenc("ThirdPerson [ Need Sv_Cheats ]"), &Vars.Misc.thirdperson);
				ImGui::Checkbox(charenc("AirStuck Allways"), &Vars.Misc.MTeleport);
				ImGui::Checkbox(charenc("Moonwalk"), &Vars.Misc.moonwalk);
				ImGui::Checkbox(charenc("No Name"), &Vars.Misc.NameHide);
				ImGui::Checkbox(charenc("Name Spam"), &Vars.Misc.NameSpammer);
				ImGui::Checkbox(charenc("Paste Crasher"), &Vars.Misc.NameSpammer2);
				ImGui::Checkbox(charenc("Name Steal [Need No Name]"), &Vars.Misc.NameStealer);
				ImGui::Checkbox(charenc("Location Spam"), &Vars.Misc.LocationSpam);
				ImGui::Checkbox(charenc("WalkBot"), &Vars.Misc.Walkbot);

			}
			ImGui::End(); //End Misc window
		}

		//meisnte skins? nvm
		if (Vars.Menu.Skins)
		{
			ImGui::Begin(charenc("Skins[Coming Soon]"), &Vars.Menu.Skins, ImVec2(300, 500), 0.9f, ImGuiWindowFlags_NoCollapse);
			{
				ImGui::Checkbox(charenc("Knife Changer"), &Vars.Skins.bKnife);
				ImGui::Combo(charenc("Knife"), &Vars.Skins.iKnife, MenuKnives, ARRAYSIZE(MenuKnives));
			}
			ImGui::End();
		}
		if (Vars.Menu.Playerlist)
		{
			ImGui::Begin(charenc("Playerlist"), &Vars.Menu.Playerlist, ImVec2(300, 400), 0.9f, ImGuiWindowFlags_NoCollapse);
			{
				ImGui::Checkbox(charenc("Resolver"), &Vars.Playerlist.use);

				static const char* modes[] =
				{
					"Auto",
					"Auto + LBY Break Fix",
					/*"Delta",*/
					"Off"
				};
				for (int i = 0; i < I::Globals->maxClients; i++)
				{
					CBaseEntity* Entity = I::ClientEntList->GetClientEntity(i);

					if (Entity == NULL)
					{
						Vars.Playerlist.Player[i] = 0;
						continue;
					}
					if (Entity->GetTeam() == 1)
						continue;


					if (Entity == G::LocalPlayer)
						continue;

					if (Entity->GetTeam() == G::LocalPlayer->GetTeam())
						continue;

					if (!Entity->IsPlayer())
						continue;

					ImGui::Combo(Entity->GetName().c_str(), &Vars.Playerlist.Player[i], modes, ARRAYSIZE(modes));
				}
			}
			ImGui::End();
		}
	}
	ImGui::Render();
	return oEndScene(pDevice);
}

ResetFn oReset;
long __stdcall Hooks::Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	if( !G::d3dinit )
		return oReset( pDevice, pPresentationParameters );

	ImGui_ImplDX9_InvalidateDeviceObjects();

	auto hr = oReset( pDevice, pPresentationParameters );
	ImGui_ImplDX9_CreateDeviceObjects();


	return hr;
}

void GUI_Init( IDirect3DDevice9* pDevice ) 
{
	ImGui_ImplDX9_Init(G::Window, pDevice);

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.40f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 1.00f, 1.00f, 0.65f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.80f, 0.80f, 0.18f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44f, 0.80f, 0.80f, 0.27f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.44f, 0.81f, 0.86f, 0.66f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.18f, 0.21f, 0.73f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.16f, 0.24f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.65f, 0.65f, 0.46f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.01f, 1.00f, 1.00f, 0.43f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.62f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 0.50f, 0.50f, 0.33f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.00f, 0.50f, 0.50f, 0.47f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.78f, 0.78f, 0.35f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.78f, 0.78f, 0.47f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.78f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.04f, 0.10f, 0.09f, 0.51f);

	style.Alpha = 1.f;
	style.ChildWindowRounding = 3.f;
	style.FramePadding = ImVec2(4, 1);
	style.WindowRounding = 3.f;
	style.GrabRounding = 1.f;
	style.GrabMinSize = 20.f;
	style.FrameRounding = 3.f;
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;

	G::d3dinit = true;
};