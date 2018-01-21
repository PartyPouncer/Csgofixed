#pragma once

class CLegitBot
{
public:
	void Run();
	bool EntityIsValid( int i );
	void ChangeSet();
private:
	void GoToTarget();
	void FindTarget();
	void GoToTargetMouseEvent();
	void DropTarget();

	 Vector GetHitboxPosition(int Hitbox, CBaseEntity* ent);

	void Triggerbot();
	void RCS();
	void legitaa();
	QAngle m_oldPunch;
	QAngle m_oldView;
	bool bReset = false;
	class CFixMove
	{
	public:
		void Start();
		void End();
	private:
		float m_oldforward, m_oldsidemove;
		QAngle m_oldangle;
	};
private:
	int m_fbestfov;
	int m_ibesttarget;
};



struct BacktrackingRecord
{
	int Tick;
	Vector Position;
	matrix3x4a_t Matrix[128];
	BacktrackingRecord(int iTick, Vector vPos, matrix3x4a_t* mat)
	{
		Tick = iTick;
		Position = vPos;
		for (int x = 0; x < 128; x++)
		{
			Matrix[x] = mat[x];
		}
	}
};

namespace LegitBacktracking
{
	extern std::vector<BacktrackingRecord> PlayerRecords[64];

	void CM(void);
	void PT(void);
	void FN(void);
}




