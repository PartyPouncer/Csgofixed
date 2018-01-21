#include "Cheat.h"
#include "PaintTraverse.h"
bool prePaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce)
{
	if (!I::Engine->IsConnected())
		return true;

	if (Vars.Visuals.Removals.Scope && I::Engine->IsConnected() && I::Engine->IsInGame() && G::LocalPlayer && G::LocalPlayer->GetAlive() && strcmp("HudZoom", I::VPanel->GetName(panel)) == 0)
		return false;

	/*if (Vars.Visuals.Removals.Scope && G::LocalPlayer->GetAlive() && strcmp("FocusOverlayPanel", I::VPanel->GetName(panel)) == 0)
		return false;*/

	return true;
}


PaintTraverseFn oPaintTraverse;
void __fastcall Hooks::PaintTraverse(void *ecx, void* edx, unsigned int panel, bool forceRepaint, bool allowForce)
{
	if (prePaintTraverse(panel, forceRepaint, allowForce))
		oPaintTraverse(ecx, panel, forceRepaint, allowForce);
	
	static unsigned int drawPanel;
	if (!drawPanel)
	{
		const char* panelname = I::VPanel->GetName(panel);

		if (panelname[0] == 'M' && panelname[2] == 't')
			drawPanel = panel;
	}
	if (panel != drawPanel)
		return;
	// dumb fix so we can have no visuals but still see the menu
	D::DrawPixel(1, 1, Color(0, 0, 0));

	E::Visuals->Run();
}