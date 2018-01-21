#include "SDK.h"

QAngle              G::FakeAngle;
QAngle              G::RealAngle;
float               G::Lby;
bool				G::isAutowalling;
bool				G::Aimbotting;
bool				G::InAntiAim;
QAngle				G::LastAngle;
QAngle              G::VisualAngle;
CBaseEntity*		G::LocalPlayer;
bool				G::Return;
CUserCmd*			G::UserCmd;
bool				G::LastLBYUpdate = false;
bool				G::LastLBYUpdateEnemy = false;
HMODULE				G::Dll;
HWND				G::Window;
bool				G::PressedKeys[ 256 ] = {};
bool				G::d3dinit = false;
float				G::FOV;
float               G::MyLowerBody;
bool                G::LowerBodyWasUpdate;
int					G::ChamMode = -1;
int                 G::missedshots;
int                 G::Shots;
bool				G::SendPacket = true;
int					G::BestTarget = -1;
float               G::flHurtTime;


VTHook*				H::VPanel;
VTHook*				H::ClientMode;
VTHook*				H::Client;
VTHook*				H::Prediction;
VTHook*				H::ModelRender;
VTHook*				H::Surface;
VTHook*				H::D3D9;
VTHook*				H::pGEM;
VTHook*             H::TraceVMT;
VTHook*				H::Input;


CLegitBot*			E::LegitBot = new CLegitBot();
CRageBot*			E::RageBot = new CRageBot();
CVisuals*			E::Visuals = new CVisuals();
CMiscellaneous*		E::Misc = new CMiscellaneous();
