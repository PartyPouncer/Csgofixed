#include "Cheat.h"

bool __fastcall hkFireEventClientSide(void* ecx, void* edx, CGameEvent* pEvent)
{
	if (!pEvent)
		return oFireEventClientSide(ecx, pEvent);

	if (!strcmp(pEvent->GetName(), "player_death"))
	{
		// The game launched a player_death event.
		int nUserID = pEvent->GetInt("attacker");
		int nDead = pEvent->GetInt("userid");
		if (!nUserID || !nDead)
			return false;

		// Continue only if I'm the one who killed
		if (I::Engine->GetPlayerForUserID(nUserID) != I::Engine->GetLocalPlayerIndex())
			return false; //This will craft deathnotices only when I kill

						  // If I return false previously this if clause won't ever be executed. Just adjust the if clause properly
						  // If I'm the one who dies...
		if (I::Engine->GetPlayerForUserID(nDead) == I::Engine->GetLocalPlayerIndex())
		{
			I::Engine->ClientCmd("say Wait...you actually killed me? How dare...");
			return false;
		}

		player_info_t killed_info = GetInfo(I::Engine->GetPlayerForUserID(nDead));

		std::stringstream ss;
		ss << "say " << killed_info.szName << ", you got rekt by the ColumbineHook, an exclusive internal meme, using a weapon named " << pEvent->GetString("weapon") << ".";

		I::Engine->ClientCmd(ss.str().c_str());
	}

	if (!strcmp(pEvent->GetName(), "bomb_planted"))
	{
		// The game launched the bomb_beginplant event
		int nPlanter = pEvent->GetInt("userid");
		if (!nPlanter)
			return false;

		player_info_t planter_info = GetInfo(I::Engine->GetPlayerForUserID(nPlanter));

		std::stringstream ss;
		ss << "say Wow, " << planter_info.szName << ", you planted the bomb like a real muslim!";

		I::Engine->ClientCmd(ss.str().c_str());

	}

	if (!strcmp(pEvent->GetName(), "bomb_exploded"))
	{
		// The game launched the bomb_exploded event
		I::Engine->ClientCmd("say ALLAHU AKBAR!!!");
	}

	if (!strcmp(pEvent->GetName(), "bomb_dropped"))
	{
		int nDropper = pEvent->GetInt("userid");
		if (!nDropper)
			return false;

		player_info_t info = GetInfo(I::Engine->GetPlayerForUserID(nDropper));

		std::stringstream ss;
		ss << "say Oh no! " << info.szName << " dropped the fuckin bomb!";

		I::Engine->ClientCmd(ss.str().c_str());
	}

	if (!strcmp(pEvent->GetName(), "bomb_defused"))
	{
		int nDefuser = pEvent->GetInt("userid");
		if (!nDefuser)
			return false;

		player_info_t info = GetInfo(I::Engine->GetPlayerForUserID(nDefuser));

		std::stringstream ss;

		ss << "say " << info.szName << " defused the bomb with SWAT style! Bin Laden really sad atm...";

		I::Engine->ClientCmd(ss.str().c_str());
	}

	if (!strcmp(pEvent->GetName(), "bomb_begindefuse"))
	{
		//[WARNING: This event isn't called anymore, idk why]
		int nDefuser = pEvent->GetInt("userid");
		if (!nDefuser)
			return false;

		player_info_t info = GetInfo(I::Engine->GetPlayerForUserID(nDefuser));

		std::stringstream ss;

		ss << "say " << info.szName << " started defusing the mothafucking bomb!";
		if (pEvent->GetInt("haskit"))
			ss << " And he has got a l33t defuser!!!";

		I::Engine->ClientCmd(ss.str().c_str());
	}

	if (!strcmp(pEvent->GetName(), "bomb_abortdefuse"))
	{
		//[WARNING: This event isn't called anymore, idk why]
		int nAborter = pEvent->GetInt("userid");
		if (!nAborter)
			return false;

		player_info_t info = GetInfo(I::Engine->GetPlayerForUserID(nAborter));

		// Continue only if I'm not the aborter
		if (I::Engine->GetPlayerForUserID(nAborter) == I::Engine->GetLocalPlayerIndex())
			return false;

		std::stringstream ss;

		ss << "say " << info.szName << " aborted the bomb defusal like a fucking pussy!!! MAYBE HE NEEDS SOME COLUMBINEHOOK ;)";

		I::Engine->ClientCmd(ss.str().c_str());
	}

	if (!strcmp(pEvent->GetName(), "round_freeze_end"))
	{
		I::Engine->ClientCmd("say Wow another round full of pure skills starts!");
	}

	return oFireEventClientSide(ecx, pEvent);
}