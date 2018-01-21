#include "Cheat.h"

OverrideViewFn oOverrideView;
void __stdcall Hooks::OverrideView( CViewSetup* vsView )
{
	vsView->fov += (float)Vars.Visuals.FOVAdd;

	G::FOV = vsView->fov;
	
	oOverrideView( vsView );
}