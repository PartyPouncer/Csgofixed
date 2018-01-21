#pragma once

class IVPanel
{
public:
	unsigned int GetPanel(int type)
	{
		typedef unsigned int(__thiscall *tGetPanel)(void*, int type);
		return U::GetVFunc< tGetPanel >(this, 1)(this, type);
	}

	const char* GetName(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, unsigned int);
		return U::GetVFunc< OriginalFn >(this, 36)(this, vguiPanel);
	}
};