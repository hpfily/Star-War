#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RED_ID  0
#define BLUE_ID 1
#define WAIT_ID	2
#define WINSHIP_ID 3

#define CANNON_ENABLE_NUMBER 3

#define TRUE 1
#define FALSE 0;

#define RANDOM(x) (rand()%x)

typedef __int32 DWORD;


class  Map;

typedef struct Card
{
	DWORD m_Id;
	DWORD m_Number;
	DWORD m_Score;
	char  m_strName[20];
	void(Map::*m_pfnCardSkill)(DWORD camp, Card* pCard);
}Card,*ptrCard;

class Stack
{
	ptrCard	*m_pBase;
	ptrCard	*m_pTop;
	DWORD	m_Size;
	DWORD	m_Max;
public:
	Stack(DWORD size)
	{
		m_pBase = (ptrCard*)malloc(sizeof(ptrCard)*size+1);
		m_pTop = m_pBase;
		m_Size = 0;
		m_Max = size;
	}
	~Stack()
	{
		free(m_pBase);
		m_pBase = m_pTop = NULL;
	}
	bool isFull()
	{
		if (m_Size == m_Max)
			return TRUE;
		return FALSE;
	}
	bool isEmpty()
	{
		if (m_Size==0)
			return TRUE;
		return FALSE;

	}
	DWORD push(Card *pCard)
	{
		if (isFull())
			return FALSE;
		m_pTop++;
		*m_pTop = pCard;
		m_Size++;
		return TRUE;
	}
	DWORD pop(Card **ppCard)
	{
		if (isEmpty())
		{
			return FALSE;
		}
		ppCard = m_pTop;
		m_pTop = NULL;
		m_pTop--;
		m_Size--;
		return TRUE;
	}

	DWORD getSize()
	{
		return m_Size;
	}
	ptrCard* getTop()
	{
		return m_pTop;
	}
	ptrCard* getBase()
	{
		return m_pBase;
	}

};
enum MapRoleIndex
{
	AncientCore = 0,
	Doctor,
	Crystal,
	FlyMan,
	Battleship,
	Monster,
	Soldier,
	SearchMachine,
	Cannon,
	Wating,

	ScoreRed,
	ScoreBlue,
	WinShip,
};
class Map
{

	Stack	*m_pAncientCore;
	Stack	*m_pDoctor;
	Stack	*m_pCrystal;
	Stack	*m_pFlyMan;
	Stack	*m_pBattleship;
	Stack	*m_pMonster;
	Stack	*m_pSoldier;
	Stack	*m_pSearchMachine;
	Stack	*m_pCannon;
	Stack	*m_pWating;

	Stack	*m_pScoreRed;
	Stack	*m_pScoreBlue;
	Stack	*m_pWinShip;
	Stack*  m_GetRoleStack(MapRoleIndex Role)
	{
		switch (Role)
		{
		case AncientCore:
			//printf("AncientCore\n");
			return m_pAncientCore;
			break;
		case Doctor:
			//printf("Doctor\n");
			return m_pDoctor;
			break;
		case Crystal:
			return m_pCrystal;
			break;
		case FlyMan:
			return m_pFlyMan;
			break;
		case Battleship:
			return m_pBattleship;
			break;
		case Monster:
			return m_pMonster;
			break;
		case Soldier:
			return m_pSoldier;
			break;
		case SearchMachine:
			return m_pSearchMachine;
			break;
		case Cannon:
			return m_pCannon;
			break;
		case Wating:
			return m_pWating;
			break;
		case ScoreRed:
			return m_pScoreRed;
			break;
		case ScoreBlue:
			return m_pScoreBlue;
			break;
		case WinShip:
			return m_pWinShip;
			break;
		default:
			return NULL;
			break;
		}
	}
public:
	Map()
	{
		//需要修改
		m_pAncientCore	= new Stack(12);
		m_pDoctor		= new Stack(8);
		m_pCrystal		= new Stack(18);
		m_pFlyMan	= new Stack(10);
		m_pBattleship	= new Stack(3);
		m_pMonster		= new Stack(8);
		m_pSoldier		= new Stack(2);
		m_pSearchMachine	= new Stack(4);
		m_pCannon		= new Stack(3);
		
		m_pWating		= new Stack(20);
		m_pScoreRed		= new Stack(104);
		m_pScoreBlue	= new Stack(104);

		m_pWinShip		= new Stack(9);

	}
	~Map()
	{
		delete	m_pAncientCore;
		delete	m_pDoctor;
		delete	m_pCrystal;
		delete	m_pFlyMan;
		delete	m_pBattleship;
		delete	m_pMonster;
		delete	m_pSoldier;
		delete	m_pSearchMachine;
		delete	m_pCannon;
		delete	m_pWating;
		delete	m_pScoreRed;
		delete	m_pScoreBlue;
		delete	m_pWinShip;
		m_pAncientCore=NULL;
		m_pDoctor=NULL;
		m_pCrystal=NULL;
		m_pFlyMan=NULL;
		m_pBattleship=NULL;
		m_pMonster=NULL;
		m_pSoldier=NULL;
		m_pSearchMachine=NULL;
		m_pCannon=NULL;
		m_pWating=NULL;
		m_pScoreRed = NULL;
		m_pScoreBlue = NULL;
		m_pWinShip = NULL;
	}

	DWORD  m_GetCardNum(MapRoleIndex Role)
	{
		return m_GetRoleStack(Role)->getSize();
	}
	DWORD m_GetScore(MapRoleIndex Role)
	{
		DWORD score=0;
		Stack *pCardStack= m_GetRoleStack(Role);
		ptrCard  *ppCard = pCardStack->getTop();
		ptrCard  *pBase = pCardStack->getBase();
		while (ppCard!= pBase)
		{
			score += (*ppCard)->m_Score;
			ppCard--;
		}
		
		return score;
	}

	void m_fWinScore(DWORD camp, Stack *pCardStack)
	{
		if (pCardStack->isEmpty())
		{
			return;
		}
		Stack* pScoreStack;
		switch (camp)
		{
			case RED_ID:
				pScoreStack = m_pScoreRed;
				break;
			case BLUE_ID:
				pScoreStack = m_pScoreBlue;
				break;
			case WAIT_ID:
				pScoreStack = m_pWating;
				break;
			case WINSHIP_ID:
				pScoreStack = m_pWinShip;
			default:
				return;
				break;
		}
		while (!pCardStack->isEmpty())
		{
			Card *pTemp;
			pCardStack->pop(&pTemp);
			pScoreStack->push(pTemp);
		}
	}
	void Cardfunc_Core(DWORD camp, Card* pCard)
	{
		printf("hellp Cardfunc_Core\n");
		m_pAncientCore->push(pCard);
	}
	void Cardfunc_Crystal(DWORD camp, Card* pCard)
	{
		m_pCrystal->push(pCard);
	}
	void Cardfunc_Doctor(DWORD camp, Card* pCard)
	{
		m_pDoctor->push(pCard);
		if (!m_pAncientCore->isEmpty()&&!m_pCrystal->isEmpty())
		{
			m_fWinScore(camp, m_pCrystal);
			return;
		}
		if (!m_pAncientCore->isEmpty())
		{
			m_fWinScore(camp, m_pAncientCore);
			return;
		}
		if (!m_pCrystal->isEmpty())
		{
			m_fWinScore(camp, m_pCrystal);
			return;
		}

	}
	void Cardfunc_FlyMan(DWORD camp, Card* pCard)
	{
		m_pFlyMan->push(pCard);

		m_fWinScore(camp, m_pCrystal);

	}
	void Cardfunc_Canno(DWORD camp, Card* pCard)
	{
		m_pCannon->push(pCard);

		if (m_pCannon->isFull())
		{
			m_fWinScore(camp, m_pFlyMan);
			m_fWinScore(WAIT_ID, m_pWating);
		}
	}
	void Cardfunc_Battleship(DWORD camp, Card* pCard)
	{
		m_pBattleship->push(pCard);
		if (m_pBattleship->isFull())
		{
			m_fWinScore(camp, m_pWating);
			m_fWinScore(WINSHIP_ID, m_pBattleship);
		}
	}
	void Cardfunc_Monster(DWORD camp, Card* pCard)
	{
		m_pMonster->push(pCard);
		m_fWinScore(camp, m_pDoctor);
	}
	void Cardfunc_Soldier(DWORD camp, Card* pCard)
	{
		m_pSoldier->push(pCard);
		if (m_pSoldier->isFull())
		{
			m_fWinScore(camp, m_pMonster);
			m_fWinScore(WAIT_ID,m_pSoldier);
		}
	}
	void Cardfunc_SeachMachine(DWORD camp, Card* pCard)
	{
		m_pSearchMachine->push(pCard);
		if (m_pSearchMachine->isFull())
		{
			m_fWinScore(camp, m_pSearchMachine);
		}
	}
	
};
Map g_Map;

Card  g_CardTable[52] =
{
//	 id     num     score     name
	{ 1		,3		,1		,"风暴巨炮"		,&Map::Cardfunc_Canno },
	{ 2		,3		,1		,"风暴巨炮"		,&Map::Cardfunc_Canno },
	{ 3		,3		,1		,"风暴巨炮"		,&Map::Cardfunc_Canno },
	{ 4		,3		,2		,"风暴巨炮"		,&Map::Cardfunc_Canno },
	{ 5		,3		,2		,"风暴巨炮"		,&Map::Cardfunc_Canno },
	{ 6		,3		,2		,"风暴巨炮"		,&Map::Cardfunc_Canno },

	{ 7		,2		,1		,"外星翼人" ,	&Map::Cardfunc_FlyMan },
	{ 8		,2		,1		,"外星翼人" ,	&Map::Cardfunc_FlyMan },
	{ 9		,2		,2		,"外星翼人" ,	&Map::Cardfunc_FlyMan },
	{ 10	,2		,2		,"外星翼人" ,	&Map::Cardfunc_FlyMan },
	{ 11	,1		,3		,"外星翼人" ,	&Map::Cardfunc_FlyMan },

	{ 12	,3		,1		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 13	,3		,1		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 14	,3		,1		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 15	,3		,2		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 16	,3		,2		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 17	,3		,2		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 18	,2		,3		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 19	,2		,3		,"能量水晶" ,	&Map::Cardfunc_Crystal },
	{ 20	,1		,4		,"能量水晶" ,	&Map::Cardfunc_Crystal },

	{ 21	,2		,1		,"星际战士" ,    &Map::Cardfunc_Soldier },
	{ 22	,2		,1		,"星际战士" ,    &Map::Cardfunc_Soldier },
	{ 23	,2		,2		,"星际战士" ,    &Map::Cardfunc_Soldier },
	{ 24	,2		,2		,"星际战士" ,    &Map::Cardfunc_Soldier },

	{ 25	,2		,1		,"女博士" ,		&Map::Cardfunc_Doctor },
	{ 26	,2		,1		,"女博士" ,		&Map::Cardfunc_Doctor },
	{ 27	,2		,2		,"女博士" ,		&Map::Cardfunc_Doctor },
	{ 28	,2		,2		,"女博士" ,		&Map::Cardfunc_Doctor },

	{ 29	,2		,1		,"异形怪兽" ,    &Map::Cardfunc_Monster },
	{ 30	,2		,1		,"异形怪兽" ,    &Map::Cardfunc_Monster },
	{ 31	,1		,2		,"异形怪兽" ,    &Map::Cardfunc_Monster },
	{ 32	,1		,3		,"异形怪兽" ,    &Map::Cardfunc_Monster },

	{ 33	,6		,2		,"远古核心" ,    &Map::Cardfunc_Core },
	{ 34	,6		,2		,"远古核心" ,    &Map::Cardfunc_Core },
	{ 35	,6		,2		,"远古核心" ,    &Map::Cardfunc_Core },
	{ 36	,6		,2		,"远古核心" ,    &Map::Cardfunc_Core },
	{ 37	,6		,2		,"远古核心" ,    &Map::Cardfunc_Core },
	{ 38	,6		,2		,"远古核心" ,    &Map::Cardfunc_Core },

	{ 39	,2		,1		,"探索机器" ,    &Map::Cardfunc_SeachMachine },
	{ 40	,2		,1		,"探索机器" ,    &Map::Cardfunc_SeachMachine },
	{ 41	,2		,2		,"探索机器" ,    &Map::Cardfunc_SeachMachine },
	{ 42	,2		,2		,"探索机器" ,    &Map::Cardfunc_SeachMachine },
	{ 43	,2		,3		,"探索机器" ,    &Map::Cardfunc_SeachMachine },
	{ 44	,2		,3		,"探索机器" ,    &Map::Cardfunc_SeachMachine },
	{ 45	,2		,4		,"探索机器" ,    &Map::Cardfunc_SeachMachine },
	{ 46	,2		,4		,"探索机器" ,    &Map::Cardfunc_SeachMachine },

	{ 47	,6		,0		,"征服战舰" ,    &Map::Cardfunc_Battleship },
	{ 48	,6		,0		,"征服战舰" ,    &Map::Cardfunc_Battleship },
	{ 49	,6		,0		,"征服战舰" ,    &Map::Cardfunc_Battleship },
	{ 50	,6		,0		,"征服战舰" ,    &Map::Cardfunc_Battleship },
	{ 51	,6		,0		,"征服战舰" ,    &Map::Cardfunc_Battleship },
	{ 52	,6		,0		,"征服战舰" ,    &Map::Cardfunc_Battleship },

};
Card RedCard[52];
Card BlueCard[52];

void shuffle_bak()
{
	int a[10];
	for (size_t i = 0; i < 10; ++i)
	{
		a[i] = i;
	}
	printf("\n");
	srand((int)time(0));

	for (size_t i = 9; i >0; --i)
	{
		int range = i + 1;
		int rd = RANDOM(range);
		int swap_index_left = 9 - i;
		int swap_index_right = rd + swap_index_left;
		int temp = a[swap_index_right];
		a[swap_index_right] = a[swap_index_left];
		a[swap_index_left] = temp;

	}
	for (size_t i = 0; i < 10; ++i)
	{
		printf("%d ", a[i]);
	}
}

void shuffle_Card(Card *pCard,DWORD number)
{
	int n = number - 1;
	srand((int)time(0));
	for (size_t i = n; i >0; --i)
	{
		int range = i + 1;
		int rd = RANDOM(range);
		int swap_index_left = n - i;
		int swap_index_right = rd + swap_index_left;
		Card temp = pCard[swap_index_right];
		pCard[swap_index_right] = pCard[swap_index_left];
		pCard[swap_index_left] = temp;
	}
}

void MapInit()
{

}
void CardInit()
{
	memcpy(RedCard, g_CardTable, sizeof(g_CardTable));
	shuffle_Card(RedCard, sizeof(RedCard)/sizeof(Card));
	memcpy(BlueCard, g_CardTable, sizeof(g_CardTable));
	shuffle_Card(BlueCard, sizeof(BlueCard) / sizeof(Card));
}
void ScoreInit()
{

}
void SysInit()
{
	MapInit();
	CardInit();
	ScoreInit();
}

int main__()
{
	SysInit();
	system("cls");
	system("mode con cols=150 lines=100");//改变宽高
	system("color fc");//改变颜色
	(g_Map.*(g_CardTable[0].m_pfnCardSkill))(1, &g_CardTable[0]);
	(g_Map.*(g_CardTable[0].m_pfnCardSkill))(1, &g_CardTable[2]);
	(g_Map.*(g_CardTable[0].m_pfnCardSkill))(1, &g_CardTable[5]);

	Stack *pRedCardStack = new Stack(52);
	for (size_t i = 0; i < sizeof(RedCard); ++i)
	{
		pRedCardStack->push(&RedCard[i]);
	}
	char RTbuf[8000];

	sprintf_s(RTbuf,
		"\n"
		"\n"
		"\n"
		"    *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *  AncientCor  *              *    Doctor    *              *   Crystal    *              *    FlyMan    *              *  Battleship  *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *  CardNum%3d  *     <----    *  CardNum%3d  *    ---->     *  CardNum%3d  *     <----    *  CardNum%3d  *              *  CardNum%3d  *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *  Score  %3d  *              *  Score  %3d  *              *  Score  %3d  *              *  Score  %3d  *              *  Score  %3d  *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *    \n"
		"\n"
		"                                        / \\                                                         / \\ \n"
		"                                         |                                                           |   \n"
		"                                         |                                                           |   \n"
		"                                         |                                                           |   \n"
		"\n"

		"    *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *   \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *              *              *              *              *              *              *              *              *              *     \n"
		"    *    Soldier   *              *   Monster    *              * SeachMachine *              *     Canno    *              *    Wating    *    \n"
		"    *              *              *              *              *              *              *              *              *              *     \n"
		"    *  CardNum%3d  *     ---->    *  CardNum%3d  *              *  CardNum%3d  *              *  CardNum%3d  *              *  CardNum%3d  *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *  Score  %3d  *              *  Score  %3d  *              *  Score  %3d  *              *  Score  %3d  *              *  Score  %3d  *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *              *              *              *              *              *              *              *              *              *    \n"
		"    *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *              *  *  *  *  *  *    \n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"    *  *  *  *  *  *        *  *  *  *  *  *        *  *  *  *  *  *        *  *  *  *  *  *        *  *  *  *  *  *   \n"
		"    *              *        *              *        *              *        *              *        *              *    \n"
		"    *              *        *              *        *              *        *              *        *              *     \n"
		"    *    Soldier   *        *   Monster    *        * SeachMachine *        *     Canno    *        *    Wating    *    \n"
		"    *              *        *              *        *              *        *              *        *              *     \n"
		"    *  CardNum%3d  *        *  CardNum%3d  *        *  CardNum%3d  *        *  CardNum%3d  *        *  CardNum%3d  *    \n"
		"    *              *        *              *        *              *        *              *        *              *    \n"
		"    *  Score  %3d  *        *  Score  %3d  *        *  Score  %3d  *        *  Score  %3d  *        *  Score  %3d  *    \n"
		"    *              *        *              *        *              *        *              *        *              *    \n"
		"    *              *        *              *        *              *        *              *        *              *    \n"
		"    *  *  *  *  *  *        *  *  *  *  *  *        *  *  *  *  *  *        *  *  *  *  *  *        *  *  *  *  *  *    \n"
		"\n"
		"\n"
		"\n"
		"\n"
		"    Score:%3d   CardNum:%3d\n"
		, g_Map.m_GetCardNum(AncientCore), g_Map.m_GetCardNum(Doctor), g_Map.m_GetCardNum(Crystal), g_Map.m_GetCardNum(FlyMan), g_Map.m_GetCardNum(Battleship)
		, g_Map.m_GetScore(AncientCore), g_Map.m_GetScore(Doctor), g_Map.m_GetScore(Crystal), g_Map.m_GetScore(FlyMan), g_Map.m_GetScore(Battleship)

		, g_Map.m_GetCardNum(Soldier), g_Map.m_GetCardNum(Monster), g_Map.m_GetCardNum(SearchMachine), g_Map.m_GetCardNum(Cannon), g_Map.m_GetCardNum(Wating)
		, g_Map.m_GetScore(Soldier), g_Map.m_GetScore(Monster), g_Map.m_GetScore(SearchMachine), g_Map.m_GetScore(Cannon), g_Map.m_GetScore(Wating)
		,1,2,3, 1, 2, 3,1, 2, 3, 1, 2, 3, 1, 2, 3
		);
	printf(RTbuf);
	

	
	getchar();
	getchar();
	return 0;
}