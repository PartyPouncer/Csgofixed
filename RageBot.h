#pragma once

struct Hitbox
{
	Hitbox( void )
	{
		hitbox = -1;
	}

	Hitbox( int newHitBox )
	{
		hitbox = newHitBox;
	}

	int  hitbox;
	Vector points[ 9 ];
};

enum
{
	FL_HIGH = ( 1 << 0 ),
	FL_LOW = ( 1 << 1 ),
	FL_SPECIAL = ( 1 << 2 )
};

struct BestPoint
{
	BestPoint( void )
	{
		hitbox = -1;
		point = Vector( 0, 0, 0 );
		index = -1;
		dmg = -1;
		flags = 0;
	}

	BestPoint( int newHitBox )
	{
		hitbox = newHitBox;
		point = Vector( 0, 0, 0 );
		index = -1;
		dmg = -1;
		flags = 0;
	}

	Vector point;
	int  index;
	float  dmg;
	int  flags;
	int  hitbox;
};

class CRageBot
{
public:
	/*void Run();*/
	void ChangeSetRage();
	bool Aimstep( QAngle src, QAngle dst, QAngle& out, int steps );
	void Run(CUserCmd * pCmd, bool & bSendPacket);
	bool GetHitBoxCenter(CBaseEntity* ClientEntity, int iHitBox, Vector* vOut);
	CBaseEntity* FindTarget();
private:
	CBaseEntity* WasFuerAwallFindTarget();
	CBaseEntity* FindTargetNoAwall();
	void GoToTarget(CBaseEntity* target);
	bool GetMultiPointHitboxPosition(CBaseEntity * ClientEntity, int iHitBox, Vector * vOut);
	Vector GetHitboxPosition(int Hitbox, CBaseEntity* ent);

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
	float m_fbestfov;
	float m_fbestdist;
	int	m_ibesttarget;
	int hitboxID;
	int curpoint;
};

#define MAX_PLAYERS 64;