#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RED_ID  0
#define BLUE_ID 1
#define WAIT_ID	2
#define TRUE 1
#define FALSE 0;
#define RANDOM(x) (rand()%x)
typedef unsigned int DWORD;


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
	Card	*m_pBase;
	Card	*m_pTop;
	DWORD	m_Size;
	DWORD	m_Max;
public:
	Stack(DWORD size)
	{
		m_pBase = (Card*)malloc(sizeof(Card)*size+1);
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
		m_pTop = pCard;
		m_Size++;
		return TRUE;
	}
	DWORD pop(Card **ppCard)
	{
		if (isEmpty())
		{
			return FALSE;
		}
		*ppCard = m_pTop;
		m_pTop--;
		m_Size--;
		return TRUE;
	}

	DWORD getSize()
	{
		return m_Size;
	}

};
class Map
{
	Stack	*m_pAncientCore;
	Stack	*m_pDoctor;
	Stack	*m_pCrystal;
	Stack	*m_pFlyPeople;
	Stack	*m_pBattleship;
	Stack	*m_pMonster;
	Stack	*m_pSoldier;
	Stack	*m_pSeachMachine;
	Stack	*m_pCannon;
	Stack	*m_pWating;

	Stack	*m_pScoreRed;
	Stack	*m_pScoreBlue;
public:
	Map()
	{
		//��Ҫ�޸�
		m_pAncientCore	= new Stack(12);
		m_pDoctor		= new Stack(8);
		m_pCrystal		= new Stack(18);
		m_pFlyPeople	= new Stack(10);
		m_pBattleship	= new Stack(3);
		m_pMonster		= new Stack(8);
		m_pSoldier		= new Stack(2);
		m_pSeachMachine	= new Stack(4);
		m_pCannon		= new Stack(3);
		m_pWating		= new Stack(20);

		m_pScoreRed		= new Stack(104);
		m_pScoreBlue	= new Stack(104);
	}
	~Map()
	{
		delete	m_pAncientCore;
		delete	m_pDoctor;
		delete	m_pCrystal;
		delete	m_pFlyPeople;
		delete	m_pBattleship;
		delete	m_pMonster;
		delete	m_pSoldier;
		delete	m_pSeachMachine;
		delete	m_pCannon;
		delete	m_pWating;
		delete	m_pScoreRed;
		delete	m_pScoreBlue;
		m_pAncientCore=NULL;
		m_pDoctor=NULL;
		m_pCrystal=NULL;
		m_pFlyPeople=NULL;
		m_pBattleship=NULL;
		m_pMonster=NULL;
		m_pSoldier=NULL;
		m_pSeachMachine=NULL;
		m_pCannon=NULL;
		m_pWating=NULL;
		m_pScoreRed = NULL;
		m_pScoreBlue = NULL;

	}

	void m_fWinScore(DWORD camp, Stack *pCardStack)
	{
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
			default:
				return;
				break;
		}
		while (pCardStack->isEmpty())
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
	void Cardfunc_FlyPeople(DWORD camp, Card* pCard)
	{
		m_pFlyPeople->push(pCard);
		if (m_pCrystal->isEmpty())
		{
			return;
		}
		m_fWinScore(camp, m_pCrystal);
	}
	void Cardfunc_Canno(DWORD camp, Card* pCard)
	{
		m_pCannon->push(pCard);
		if (m_pFlyPeople->isEmpty())
		{
			return;
		}
		if (m_pCannon->)
		{

		}

	}
};
Map g_Map;




Card  g_CardTable[52] =
{
//	 id     num     score     name
	{ 1		,3		,1		,"�籩����"		,&Map::Cardfunc_Core},
	{ 2		,3		,1		,"�籩����" },
	{ 3		,3		,1		,"�籩����" },
	{ 4		,3		,2		,"�籩����" },
	{ 5		,3		,2		,"�籩����" },
	{ 6		,3		,2		,"�籩����" },

	{ 7		,2		,1		,"��������" },
	{ 8		,2		,1		,"��������" },
	{ 9		,2		,2		,"��������" },
	{ 10	,2		,2		,"��������" },
	{ 11	,1		,3		,"��������" },

	{ 12	,3		,1		,"����ˮ��" },
	{ 13	,3		,1		,"����ˮ��" },
	{ 14	,3		,1		,"����ˮ��" },
	{ 15	,3		,2		,"����ˮ��" },
	{ 16	,3		,2		,"����ˮ��" },
	{ 17	,3		,2		,"����ˮ��" },
	{ 18	,2		,3		,"����ˮ��" },
	{ 19	,2		,3		,"����ˮ��" },
	{ 20	,1		,4		,"����ˮ��" },

	{ 21	,2		,1		,"�Ǽ�սʿ" },
	{ 22	,2		,1		,"�Ǽ�սʿ" },
	{ 23	,2		,2		,"�Ǽ�սʿ" },
	{ 24	,2		,2		,"�Ǽ�սʿ" },

	{ 25	,2		,1		,"Ů��ʿ" },
	{ 26	,2		,1		,"Ů��ʿ" },
	{ 27	,2		,2		,"Ů��ʿ" },
	{ 28	,2		,2		,"Ů��ʿ" },

	{ 29	,2		,1		,"���ι���" },
	{ 30	,2		,1		,"���ι���" },
	{ 31	,1		,2		,"���ι���" },
	{ 32	,1		,3		,"���ι���" },

	{ 33	,6		,2		,"Զ�ź���" },
	{ 34	,6		,2		,"Զ�ź���" },
	{ 35	,6		,2		,"Զ�ź���" },
	{ 36	,6		,2		,"Զ�ź���" },
	{ 37	,6		,2		,"Զ�ź���" },
	{ 38	,6		,2		,"Զ�ź���" },

	{ 39	,2		,1		,"̽������" },
	{ 40	,2		,1		,"̽������" },
	{ 41	,2		,2		,"̽������" },
	{ 42	,2		,2		,"̽������" },
	{ 43	,2		,3		,"̽������" },
	{ 44	,2		,3		,"̽������" },
	{ 45	,2		,4		,"̽������" },
	{ 46	,2		,4		,"̽������" },

	{ 47	,6		,0		,"����ս��" },
	{ 48	,6		,0		,"����ս��" },
	{ 49	,6		,0		,"����ս��" },
	{ 50	,6		,0		,"����ս��" },
	{ 51	,6		,0		,"����ս��" },
	{ 52	,6		,0		,"����ս��" },

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
int main()
{
	SysInit();

	(g_Map.*(g_CardTable[0].m_pfnCardSkill))(1, NULL);

	getchar();
	getchar();
}