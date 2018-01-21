#include "Cheat.h"
DrawModelExecuteFn oDrawModelExecute;

void ForceMaterial(IMaterial* material, Color color)
{
	if (material != NULL)
	{
		I::RenderView->SetColorModulation(color.Base());
		I::ModelRender->ForcedMaterialOverride(material);
	}
}


void __stdcall Hooks::DrawModelExecute(void* context, void* state, const ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld)
{
	H::ModelRender->UnHook();



	if (I::Engine->IsInGame() && G::LocalPlayer)
	{
		if (info.pModel)
		{

			std::string modelName = I::ModelInfo->GetModelName(info.pModel);

			if (modelName.find(strenc("models/player")) != std::string::npos && Vars.Visuals.Chams.Enabled)
			{
				CBaseEntity* pModelEntity = (CBaseEntity*)I::ClientEntList->GetClientEntity(info.entity_index);

				if (pModelEntity && pModelEntity->GetAlive() && !pModelEntity->GetDormant())
				{
					if (Vars.Visuals.Filter.Enemies && !Vars.Visuals.Filter.Friendlies && pModelEntity->GetTeam() != G::LocalPlayer->GetTeam())
					{
						static float rainbow;
						rainbow += 0.001f;
						if (rainbow > 1.f) rainbow = 0.f;
						Color render_color_hidden = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(72, 219, 75) : Color(232, 209, 32);
						Color render_color_visible = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(84, 167, 255) : Color(200, 60, 60);
						Color render_rainbow_color_hidden = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(72, 219, 75) : Color::FromHSB(rainbow, 1.f, 1.f);
						Color render_rainbow_color_visible = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(84, 167, 255) : Color::FromHSB(rainbow, 1.f, 1.f);

						if (Vars.Visuals.Chams.XQZ)
						{
							ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, Vars.Visuals.Chams.Rainbow ? render_rainbow_color_hidden : render_color_hidden);
							I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

							if (Vars.Visuals.Chams.Mode == 0)
								hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							else
								hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}

						if (Vars.Visuals.Chams.Mode == 0)
							visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						else
							visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

						ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, Vars.Visuals.Chams.Rainbow ? render_rainbow_color_visible : render_color_visible);
						I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}
					else if (!Vars.Visuals.Filter.Enemies && Vars.Visuals.Filter.Friendlies && pModelEntity->GetTeam() == G::LocalPlayer->GetTeam())
					{
						Color render_color_hidden = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(1, 1, 1) : Color(1, 1, 1);
						Color render_color_visible = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(60, 200, 60) : Color(60, 200, 60);
						if (Vars.Visuals.Chams.XQZ)
						{
							ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, render_color_hidden);
							I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

							if (Vars.Visuals.Chams.Mode == 0)
							{
								hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							}
							else
							{
								hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							}
						}

						if (Vars.Visuals.Chams.Mode == 0)
						{
							visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else
						{
							visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}

						ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, render_color_visible);
						I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}
					else if (Vars.Visuals.Filter.Enemies && Vars.Visuals.Filter.Friendlies)
					{
						Color render_color_hidden = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(1, 1, 1) : Color(1, 1, 1);
						Color render_color_visible = pModelEntity->GetTeam() == G::LocalPlayer->GetTeam() ? Color(60, 200, 60) : Color(60, 200, 60);
						if (Vars.Visuals.Chams.XQZ)
						{
							ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? hidden_flat : hidden_tex, render_color_hidden);
							I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);

							if (Vars.Visuals.Chams.Mode == 0)
							{
								hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							}
							else
							{
								hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
							}
						}

						if (Vars.Visuals.Chams.Mode == 0)
						{
							visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else
						{
							visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}

						ForceMaterial(Vars.Visuals.Chams.Mode == 0 ? visible_flat : visible_tex, render_color_visible);
						I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
					}
				}
			}
			else if (modelName.find(strenc("flash")) != std::string::npos && Vars.Visuals.Removals.Flash)
			{
				IMaterial* flash = I::MaterialSystem->FindMaterial(charenc("effects\\flashbang"), charenc(TEXTURE_GROUP_CLIENT_EFFECTS));
				IMaterial* flashWhite = I::MaterialSystem->FindMaterial(charenc("effects\\flashbang_white"), charenc(TEXTURE_GROUP_CLIENT_EFFECTS));
				flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				I::ModelRender->ForcedMaterialOverride(flash);
				I::ModelRender->ForcedMaterialOverride(flashWhite);
			}

			/*else if (modelName.find(strenc("smoke")) != std::string::npos && Vars.Visuals.Removals.Smoke)
			{
				IMaterial* smoke0 = I::MaterialSystem->FindMaterial(("particle/smoke_dust.vmt"), (TEXTURE_GROUP_CLIENT_EFFECTS));
				IMaterial* smoke1 = I::MaterialSystem->FindMaterial(("particle/smokegrenade.vtf"), (TEXTURE_GROUP_CLIENT_EFFECTS));
				IMaterial* smoke2 = I::MaterialSystem->FindMaterial(("particle/smokegrenade_thick.vtf"), (TEXTURE_GROUP_CLIENT_EFFECTS));
				IMaterial* smoke3 = I::MaterialSystem->FindMaterial(("particle/particle_smokegrenade.vmt"), (TEXTURE_GROUP_CLIENT_EFFECTS));

				smoke0->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				smoke1->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				smoke2->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				smoke3->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				I::ModelRender->ForcedMaterialOverride(smoke3);
				I::ModelRender->ForcedMaterialOverride(smoke0);
				I::ModelRender->ForcedMaterialOverride(smoke1);
				I::ModelRender->ForcedMaterialOverride(smoke2);
			}*/

			else if (modelName.find(charenc("arms")) != std::string::npos && Vars.Visuals.Removals.Hands)
			{
				IMaterial* Hands = I::MaterialSystem->FindMaterial(modelName.c_str(), charenc(TEXTURE_GROUP_MODEL));
				Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				I::ModelRender->ForcedMaterialOverride(Hands);
			}

			else if (modelName.find(charenc("weapon")) != std::string::npos && Vars.Visuals.Removals.Weapon)
			{
				if (!(modelName.find(charenc("arms")) != std::string::npos))
				{
					IMaterial* Weapon = I::MaterialSystem->FindMaterial(modelName.c_str(), charenc(TEXTURE_GROUP_MODEL));
					Weapon->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					I::ModelRender->ForcedMaterialOverride(Weapon);
				}
			}

		   if (modelName.find(charenc("arms")) != std::string::npos && Vars.Visuals.Removals.WireframeHands)
			{

					IMaterial* Weapon = I::MaterialSystem->FindMaterial(modelName.c_str(), charenc(TEXTURE_GROUP_MODEL));
					Weapon->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
					I::ModelRender->ForcedMaterialOverride(Weapon);

			}
		}
	}
	std::string modelName2 = I::ModelInfo->GetModelName(info.pModel);
	const char* ModelName2 = I::ModelInfo->GetModelName((model_t*)info.pModel);
	if (Vars.Visuals.Chams.Fake)
	{
		if (G::LocalPlayer)
		{
			IMaterial* mat = I::MaterialSystem->CreateMaterial(false, false, false);
			//IMaterial *covered = ChamsStyle1337 ? CoveredLit : CoveredFlat;
			if (mat)
			{
				Vector memen;
				memen.y = (G::UserCmd->viewangles.y);
				Vector OrigAng;
				OrigAng = memen;
				G::LocalPlayer->SetAngle2(Vector(0, G::LocalPlayer->GetLowerBodyTarget(), 0)); // paste here ur AA.y value or pLocal->GetLby() (for example)
				bool LbyColor = false; // u can make LBY INDICATOR. When LbyColor is true. Color will be Green , if false it will be White
				float NormalColor[3] = { 1, 1, 1 };
				float lbyUpdateColor[3] = { 0, 1, 0 };
				I::RenderView->SetColorModulation(LbyColor ? lbyUpdateColor : NormalColor);
				I::RenderView->SetBlend(1.0f);
				I::ModelRender->ForcedMaterialOverride(mat);

				I::ModelRender->ForcedMaterialOverride(nullptr);
				G::LocalPlayer->SetAngle2(OrigAng);
				I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
			}
		}
	}
	I::ModelRender->DrawModelExecute(context, state, info, pCustomBoneToWorld);
	I::ModelRender->ForcedMaterialOverride(NULL);
	H::ModelRender->ReHook();
}
