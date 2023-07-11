// 20장 섯다 게임으로 1월~10월의 패 중 피를 제외한 20장으로 게임을 함
// 룰은 오리지널 2장 섯다
// 9 4 구사는 원래의 룰과 달리 무조건 재경기
// 컴퓨터의 패와 플레이어의 패가 정확히 무엇인지 아는 것은 불가능
// 점수로만 승패를 결정함
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#pragma warning(disable:4996)
#define SIZE 4

int score_cmp(int Cscore, int Pscore);

// 플레이어 패와 점수가 포함된 구조체
typedef struct {
	int player_1;	int player_2;	int score_pl;
}PP;

// 컴퓨터의 패와 점수가 포함된 구조체
typedef struct {
	int com_1;	int com_2;	int score_com;
}CC;

int main(void)
{
	int i, j, ch, select;	// select가 int형이므로 선택시 문자를 입력하면 오류가 발생함
	int ran[SIZE];			// 난수 배열
	int *winner;			// 승자에게 동적 메모리를 할당하여 승자를 출력하도록
	char re;				// 재경기 변수(y/n)

	PP pl = { 0,0,100 };	// 구조체 변수 선언 및 초기화
	CC co = { 0,0,100 };

	while (1)
	{
		printf("\n");
		printf("섯다~~~~날 이길 수 있겠어?\n");
		printf("\n1. 게임 시작\n");
		printf("2. 게임 설명\n");
		printf("3. 게임 종료\n");
		printf("\n당신의 선택 : ");	scanf("%d", &select);
		printf("\n");

		if (select == 1)
			break;
		else if (select == 2)
		{
			printf("\t\t\t<RULE>\n\n");
			printf("섯다는 화투패 2장으로 높은 족보를 만들어서 상대를 제압하는 배팅게임입니다.\n\n");
			printf("삼팔광땡, 장땡 등의 일반적인 족보와 구사, 땡잡이, 암행어사 등의 특수 족보로\n");
			printf("서열을 넘나드는 눈치 게임이 진행 됩니다.\n\n");
			printf("게임은 20장 섯다로 게임으로 1월~10월의 피를 제외한 20장으로 게임을 합니다.\n\n");
			printf("룰은 전통적인 섯다 방식으로 화투패 2장을 모두 받은 다음 베팅하여 승부를 가립니다.\n\n");

			printf("\t############### 기본점수는 100점 ###############\n\n");
			printf("2 8혹은3 7망통이면 +0, 1끗이면 +1, 2끗이면 +2, 3끗이면 +3, 4끗이면 +4\n");
			printf("5끗이면 +5, 6끗이면 +6, 7끗이면 +7, 8끗이면 +8, 9끗이면 +10\n\n");
			printf("4 6세륙이면 +15, 4 10장사이면 +20, 1 10장삥이면 +25, 1 9구삥이면 +30\n");
			printf("1 4독사이면 +35, 1 2알리이면 +40\n\n");
			printf("1땡이면 +50, 2땡이면 +60, 3땡이면 +70, 4땡이면 +80, 5때이면 +90, 6땡이면 +100\n");
			printf("7땡이면 +110, 8땡이면 +120, 9땡이면 +130, 3 7땡잡이면 +140, 10장땡이면 +150\n\n");
			printf("1 3혹은1 8광땡이면 +170, 암행어사이면 +185, 3 8광땡이면 +200\n\n");
			printf("점수에 따른 자신의 패가 무엇인지 아시는 것이 좋겠죠??\n");

			printf("\nc를 입력하면 이전 화면으로 돌아갑니다 : ");

			while (1)
			{
				while ((ch = getche()) == 'c')
				{
					printf("\n\n잠시만 기다려주세요..");
					Sleep(2000);
					system("cls");
					main();
				}
			}
		}
		else if (select == 3)
		{
			printf("\n3초 후에 게임을 종료합니다.\n\n");
			printf("3..\n\n");  Sleep(1000);
			printf("2..\n\n");  Sleep(1000);
			printf("1..\n");  Sleep(1000);
			exit(1);
		}
		else
		{
			printf("\n잘못된 입력입니다. 잠시후 다시 입력해주세요\n\n");
			printf("2...\n\n");  Sleep(1000);
			printf("1...\n"); Sleep(1000);
			system("cls");
			main();
		}
	}
	
	printf("\n패 부여중....\n\n");

	for (i = 0; i < SIZE; i++)
	{
		srand(time(NULL));		// seed 값 변경
		ran[i] = (rand() % 100) + 1;		// 1~100난수 생성

		if (1 <= ran && ran <= 20)		// 20장 섯다의 패는 20개 이므로 난수가 1~20까지만 생성 되도록 설정
			ran[i] = ran[i];
		else if (21 <= ran[i] && ran[i] <= 40)
			ran[i] = ran[i] - 20;
		else if (41 <= ran[i] && ran[i] <= 60)
			ran[i] = ran[i] - 40;
		else if (61 <= ran[i] && ran[i] <= 80)
			ran[i] = ran[i] - 60;
		else if (81 <= ran[i] && ran[i] <= 100)
			ran[i] = ran[i] - 80;
		for (j = 0; j < i; j++)		// 패가 20장에 한정되어 있으므로 생성되는 난수 4개가 서로 달라야함
		{
			if (ran[i] == ran[j])
				i--;
		}
	}
	co.com_1 = ran[0];		// 각 난수 부여
	co.com_2 = ran[1];
	pl.player_1 = ran[2];
	pl.player_2 = ran[3];
	
	// 둘 중 하나가 9 4 구사인 경우는 재경기
	if ((co.com_1 == 4 && co.com_2 == 9)
		|| (co.com_1 == 4 && co.com_2 == 19)
		|| (co.com_1 == 14 && co.com_2 == 9)
		|| (co.com_1 == 14 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 4)
		|| (co.com_1 == 9 && co.com_2 == 14)
		|| (co.com_1 == 19 && co.com_2 == 4)
		|| (co.com_1 == 19 && co.com_2 == 14))
	{
		printf("컴퓨터에게 9 4 재경기 패가 떠 재경기를 해야 합니다.\n\n");
		printf("잠시만 기다려주세요..\n");
		Sleep(2000);
		system("cls");
		main();
	}
	else if ((pl.player_1 == 4 && pl.player_2 == 9)
		|| (pl.player_1 == 4 && pl.player_2 == 19)
		|| (pl.player_1 == 14 && pl.player_2 == 9)
		|| (pl.player_1 == 14 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 4)
		|| (pl.player_1 == 9 && pl.player_2 == 14)
		|| (pl.player_1 == 19 && pl.player_2 == 4)
		|| (pl.player_1 == 19 && pl.player_2 == 14))
	{
		printf("당신에게 9 4 재경기 패가 떠 재경기를 해야 합니다.\n\n");
		printf("잠시만 기다려주세요..\n");
		Sleep(2000);
		system("cls");
		main();
	}
	
	// 컴퓨터 패에 따른 점수 부여
	if ((co.com_1 == 2 && co.com_2 == 8)			// 2 8 망통
		|| (co.com_1 == 2 && co.com_2 == 18)
		|| (co.com_1 == 12 && co.com_2 == 8)
		|| (co.com_1 == 12 && co.com_2 == 18)
		|| (co.com_1 == 8 && co.com_2 == 2)
		|| (co.com_1 == 8 && co.com_2 == 12)
		|| (co.com_1 == 18 && co.com_2 == 2)
		|| (co.com_1 == 18 && co.com_2 == 12))
		co.score_com = 100;

	if ((co.com_1 == 3 && co.com_2 == 7)			// 3 7 망통 (상대가 땡이 아니면 망통임)
		|| (co.com_1 == 3 && co.com_2 == 17)
		|| (co.com_1 == 13 && co.com_2 == 7)
		|| (co.com_1 == 13 && co.com_2 == 17)
		|| (co.com_1 == 7 && co.com_2 == 3)
		|| (co.com_1 == 7 && co.com_2 == 13)
		|| (co.com_1 == 17 && co.com_2 == 3)
		|| (co.com_1 == 17 && co.com_2 == 13))
		co.score_com = 100;

	if ((co.com_1 == 2 && co.com_2 == 9)			// 1끗 (암행어사는 상대가 광땡이 아니면 1끗)
		|| (co.com_1 == 2 && co.com_2 == 19)
		|| (co.com_1 == 12 && co.com_2 == 9)
		|| (co.com_1 == 12 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 2)
		|| (co.com_1 == 9 && co.com_2 == 12)
		|| (co.com_1 == 19 && co.com_2 == 2)
		|| (co.com_1 == 19 && co.com_2 == 12)
		|| (co.com_1 == 3 && co.com_2 == 8)
		|| (co.com_1 == 3 && co.com_2 == 18)
		|| (co.com_1 == 13 && co.com_2 == 8)
		|| (co.com_1 == 13 && co.com_2 == 18)
		|| (co.com_1 == 8 && co.com_2 == 3)
		|| (co.com_1 == 8 && co.com_2 == 13)
		|| (co.com_1 == 18 && co.com_2 == 3)
		|| (co.com_1 == 18 && co.com_2 == 13)
		|| (co.com_1 == 4 && co.com_2 == 7)
		|| (co.com_1 == 4 && co.com_2 == 17)
		|| (co.com_1 == 14 && co.com_2 == 7)
		|| (co.com_1 == 14 && co.com_2 == 17)
		|| (co.com_1 == 7 && co.com_2 == 4)
		|| (co.com_1 == 7 && co.com_2 == 14)
		|| (co.com_1 == 17 && co.com_2 == 4)
		|| (co.com_1 == 17 && co.com_2 == 14)
		|| (co.com_1 == 5 && co.com_2 == 6)
		|| (co.com_1 == 5 && co.com_2 == 16)
		|| (co.com_1 == 15 && co.com_2 == 6)
		|| (co.com_1 == 15 && co.com_2 == 16)
		|| (co.com_1 == 6 && co.com_2 == 5)
		|| (co.com_1 == 6 && co.com_2 == 15)
		|| (co.com_1 == 16 && co.com_2 == 5)
		|| (co.com_1 == 16 && co.com_2 == 15))
		co.score_com = 101;

	if ((co.com_1 == 2 && co.com_2 == 10)			// 2끗
		|| (co.com_1 == 2 && co.com_2 == 20)
		|| (co.com_1 == 12 && co.com_2 == 10)
		|| (co.com_1 == 12 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 2)
		|| (co.com_1 == 10 && co.com_2 == 12)
		|| (co.com_1 == 20 && co.com_2 == 2)
		|| (co.com_1 == 20 && co.com_2 == 12)
		|| (co.com_1 == 3 && co.com_2 == 9)
		|| (co.com_1 == 3 && co.com_2 == 19)
		|| (co.com_1 == 13 && co.com_2 == 9)
		|| (co.com_1 == 13 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 3)
		|| (co.com_1 == 9 && co.com_2 == 13)
		|| (co.com_1 == 19 && co.com_2 == 3)
		|| (co.com_1 == 19 && co.com_2 == 13)
		|| (co.com_1 == 4 && co.com_2 == 8)
		|| (co.com_1 == 4 && co.com_2 == 18)
		|| (co.com_1 == 14 && co.com_2 == 8)
		|| (co.com_1 == 14 && co.com_2 == 18)
		|| (co.com_1 == 8 && co.com_2 == 4)
		|| (co.com_1 == 8 && co.com_2 == 14)
		|| (co.com_1 == 18 && co.com_2 == 4)
		|| (co.com_1 == 18 && co.com_2 == 14)
		|| (co.com_1 == 5 && co.com_2 == 7)
		|| (co.com_1 == 5 && co.com_2 == 17)
		|| (co.com_1 == 15 && co.com_2 == 7)
		|| (co.com_1 == 15 && co.com_2 == 17)
		|| (co.com_1 == 7 && co.com_2 == 5)
		|| (co.com_1 == 7 && co.com_2 == 15)
		|| (co.com_1 == 17 && co.com_2 == 5)
		|| (co.com_1 == 17 && co.com_2 == 15))
		co.score_com = 102;

	if ((co.com_1 == 3 && co.com_2 == 10)			// 3끗 (9 4 구사는 재경기 패이므로 제외)
		|| (co.com_1 == 3 && co.com_2 == 20)
		|| (co.com_1 == 13 && co.com_2 == 10)
		|| (co.com_1 == 13 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 3)
		|| (co.com_1 == 10 && co.com_2 == 13)
		|| (co.com_1 == 20 && co.com_2 == 3)
		|| (co.com_1 == 20 && co.com_2 == 13)
		|| (co.com_1 == 5 && co.com_2 == 8)
		|| (co.com_1 == 5 && co.com_2 == 18)
		|| (co.com_1 == 15 && co.com_2 == 8)
		|| (co.com_1 == 15 && co.com_2 == 18)
		|| (co.com_1 == 8 && co.com_2 == 5)
		|| (co.com_1 == 8 && co.com_2 == 15)
		|| (co.com_1 == 18 && co.com_2 == 5)
		|| (co.com_1 == 18 && co.com_2 == 15)
		|| (co.com_1 == 6 && co.com_2 == 7)
		|| (co.com_1 == 6 && co.com_2 == 17)
		|| (co.com_1 == 16 && co.com_2 == 7)
		|| (co.com_1 == 16 && co.com_2 == 17)
		|| (co.com_1 == 7 && co.com_2 == 6)
		|| (co.com_1 == 7 && co.com_2 == 16)
		|| (co.com_1 == 17 && co.com_2 == 6)
		|| (co.com_1 == 17 && co.com_2 == 16))
		co.score_com = 103;

	if ((co.com_1 == 1 && co.com_2 == 3)			// 4끗
		|| (co.com_1 == 1 && co.com_2 == 13)
		|| (co.com_1 == 11 && co.com_2 == 3)
		|| (co.com_1 == 11 && co.com_2 == 13)
		|| (co.com_1 == 3 && co.com_2 == 1)
		|| (co.com_1 == 3 && co.com_2 == 11)
		|| (co.com_1 == 13 && co.com_2 == 1)
		|| (co.com_1 == 13 && co.com_2 == 11)
		|| (co.com_1 == 5 && co.com_2 == 9)
		|| (co.com_1 == 5 && co.com_2 == 19)
		|| (co.com_1 == 15 && co.com_2 == 9)
		|| (co.com_1 == 15 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 5)
		|| (co.com_1 == 9 && co.com_2 == 15)
		|| (co.com_1 == 19 && co.com_2 == 5)
		|| (co.com_1 == 19 && co.com_2 == 15)
		|| (co.com_1 == 6 && co.com_2 == 8)
		|| (co.com_1 == 6 && co.com_2 == 18)
		|| (co.com_1 == 16 && co.com_2 == 8)
		|| (co.com_1 == 16 && co.com_2 == 18)
		|| (co.com_1 == 8 && co.com_2 == 6)
		|| (co.com_1 == 8 && co.com_2 == 16)
		|| (co.com_1 == 18 && co.com_2 == 6)
		|| (co.com_1 == 18 && co.com_2 == 16))
		co.score_com = 104;

	if ((co.com_1 == 2 && co.com_2 == 3)			// 5끗
		|| (co.com_1 == 2 && co.com_2 == 13)
		|| (co.com_1 == 12 && co.com_2 == 3)
		|| (co.com_1 == 12 && co.com_2 == 13)
		|| (co.com_1 == 3 && co.com_2 == 2)
		|| (co.com_1 == 3 && co.com_2 == 12)
		|| (co.com_1 == 13 && co.com_2 == 2)
		|| (co.com_1 == 13 && co.com_2 == 12)
		|| (co.com_1 == 5 && co.com_2 == 10)
		|| (co.com_1 == 5 && co.com_2 == 20)
		|| (co.com_1 == 15 && co.com_2 == 10)
		|| (co.com_1 == 15 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 5)
		|| (co.com_1 == 10 && co.com_2 == 15)
		|| (co.com_1 == 20 && co.com_2 == 5)
		|| (co.com_1 == 20 && co.com_2 == 15)
		|| (co.com_1 == 6 && co.com_2 == 9)
		|| (co.com_1 == 6 && co.com_2 == 19)
		|| (co.com_1 == 16 && co.com_2 == 9)
		|| (co.com_1 == 16 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 6)
		|| (co.com_1 == 9 && co.com_2 == 16)
		|| (co.com_1 == 19 && co.com_2 == 6)
		|| (co.com_1 == 19 && co.com_2 == 16)
		|| (co.com_1 == 7 && co.com_2 == 8)
		|| (co.com_1 == 7 && co.com_2 == 18)
		|| (co.com_1 == 17 && co.com_2 == 8)
		|| (co.com_1 == 17 && co.com_2 == 18)
		|| (co.com_1 == 8 && co.com_2 == 7)
		|| (co.com_1 == 8 && co.com_2 == 17)
		|| (co.com_1 == 18 && co.com_2 == 7)
		|| (co.com_1 == 18 && co.com_2 == 17))
		co.score_com = 105;

	if ((co.com_1 == 1 && co.com_2 == 5)			// 6끗
		|| (co.com_1 == 1 && co.com_2 == 15)
		|| (co.com_1 == 11 && co.com_2 == 5)
		|| (co.com_1 == 11 && co.com_2 == 15)
		|| (co.com_1 == 5 && co.com_2 == 1)
		|| (co.com_1 == 5 && co.com_2 == 11)
		|| (co.com_1 == 15 && co.com_2 == 1)
		|| (co.com_1 == 15 && co.com_2 == 11)
		|| (co.com_1 == 2 && co.com_2 == 4)
		|| (co.com_1 == 2 && co.com_2 == 14)
		|| (co.com_1 == 12 && co.com_2 == 4)
		|| (co.com_1 == 12 && co.com_2 == 14)
		|| (co.com_1 == 4 && co.com_2 == 2)
		|| (co.com_1 == 4 && co.com_2 == 12)
		|| (co.com_1 == 14 && co.com_2 == 2)
		|| (co.com_1 == 14 && co.com_2 == 12)
		|| (co.com_1 == 6 && co.com_2 == 10)
		|| (co.com_1 == 6 && co.com_2 == 20)
		|| (co.com_1 == 16 && co.com_2 == 10)
		|| (co.com_1 == 16 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 6)
		|| (co.com_1 == 20 && co.com_2 == 16)
		|| (co.com_1 == 10 && co.com_2 == 6)
		|| (co.com_1 == 20 && co.com_2 == 16)
		|| (co.com_1 == 7 && co.com_2 == 9)
		|| (co.com_1 == 7 && co.com_2 == 19)
		|| (co.com_1 == 17 && co.com_2 == 9)
		|| (co.com_1 == 17 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 7)
		|| (co.com_1 == 9 && co.com_2 == 17)
		|| (co.com_1 == 19 && co.com_2 == 7)
		|| (co.com_1 == 19 && co.com_2 == 17))
		co.score_com = 106;

	if ((co.com_1 == 1 && co.com_2 == 6)			// 7끗
		|| (co.com_1 == 1 && co.com_2 == 16)
		|| (co.com_1 == 11 && co.com_2 == 6)
		|| (co.com_1 == 11 && co.com_2 == 16)
		|| (co.com_1 == 6 && co.com_2 == 1)
		|| (co.com_1 == 6 && co.com_2 == 11)
		|| (co.com_1 == 16 && co.com_2 == 1)
		|| (co.com_1 == 16 && co.com_2 == 11)
		|| (co.com_1 == 2 && co.com_2 == 5)
		|| (co.com_1 == 2 && co.com_2 == 15)
		|| (co.com_1 == 12 && co.com_2 == 5)
		|| (co.com_1 == 12 && co.com_2 == 15)
		|| (co.com_1 == 5 && co.com_2 == 2)
		|| (co.com_1 == 5 && co.com_2 == 12)
		|| (co.com_1 == 15 && co.com_2 == 2)
		|| (co.com_1 == 15 && co.com_2 == 12)
		|| (co.com_1 == 3 && co.com_2 == 4)
		|| (co.com_1 == 3 && co.com_2 == 14)
		|| (co.com_1 == 13 && co.com_2 == 4)
		|| (co.com_1 == 13 && co.com_2 == 14)
		|| (co.com_1 == 4 && co.com_2 == 3)
		|| (co.com_1 == 4 && co.com_2 == 13)
		|| (co.com_1 == 14 && co.com_2 == 3)
		|| (co.com_1 == 14 && co.com_2 == 13)
		|| (co.com_1 == 7 && co.com_2 == 10)
		|| (co.com_1 == 7 && co.com_2 == 20)
		|| (co.com_1 == 17 && co.com_2 == 10)
		|| (co.com_1 == 17 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 7)
		|| (co.com_1 == 10 && co.com_2 == 17)
		|| (co.com_1 == 20 && co.com_2 == 7)
		|| (co.com_1 == 20 && co.com_2 == 17)
		|| (co.com_1 == 8 && co.com_2 == 9)
		|| (co.com_1 == 8 && co.com_2 == 19)
		|| (co.com_1 == 18 && co.com_2 == 9)
		|| (co.com_1 == 18 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 8)
		|| (co.com_1 == 9 && co.com_2 == 18)
		|| (co.com_1 == 19 && co.com_2 == 8)
		|| (co.com_1 == 19 && co.com_2 == 18))
		co.score_com = 107;

	if ((co.com_1 == 1 && co.com_2 == 7)			// 8끗
		|| (co.com_1 == 1 && co.com_2 == 17)
		|| (co.com_1 == 11 && co.com_2 == 7)
		|| (co.com_1 == 11 && co.com_2 == 17)
		|| (co.com_1 == 7&& co.com_2 == 1)
		|| (co.com_1 == 7 && co.com_2 == 11)
		|| (co.com_1 == 17 && co.com_2 == 1)
		|| (co.com_1 == 17 && co.com_2 == 11)
		|| (co.com_1 == 2 && co.com_2 == 6)
		|| (co.com_1 == 2 && co.com_2 == 16)
		|| (co.com_1 == 12 && co.com_2 == 6)
		|| (co.com_1 == 12 && co.com_2 == 16)
		|| (co.com_1 == 6 && co.com_2 == 2)
		|| (co.com_1 == 6 && co.com_2 == 12)
		|| (co.com_1 == 16 && co.com_2 == 2)
		|| (co.com_1 == 16 && co.com_2 == 12)
		|| (co.com_1 == 3 && co.com_2 == 5)
		|| (co.com_1 == 3 && co.com_2 == 15)
		|| (co.com_1 == 13 && co.com_2 == 5)
		|| (co.com_1 == 13 && co.com_2 == 15)
		|| (co.com_1 == 5 && co.com_2 == 3)
		|| (co.com_1 == 5 && co.com_2 == 13)
		|| (co.com_1 == 15 && co.com_2 == 3)
		|| (co.com_1 == 15 && co.com_2 == 13)
		|| (co.com_1 == 8 && co.com_2 == 10)
		|| (co.com_1 == 8 && co.com_2 == 20)
		|| (co.com_1 == 18 && co.com_2 == 10)
		|| (co.com_1 == 18 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 8)
		|| (co.com_1 == 10 && co.com_2 == 18)
		|| (co.com_1 == 20 && co.com_2 == 8)
		|| (co.com_1 == 20 && co.com_2 == 18))
		co.score_com = 108;

	if ((co.com_1 == 1 && co.com_2 == 8)			// 9끗
		|| (co.com_1 == 1 && co.com_2 == 18)
		|| (co.com_1 == 11 && co.com_2 == 8)
		|| (co.com_1 == 11 && co.com_2 == 18)
		|| (co.com_1 == 8 && co.com_2 == 1)
		|| (co.com_1 == 8 && co.com_2 == 11)
		|| (co.com_1 == 18 && co.com_2 == 1)
		|| (co.com_1 == 18 && co.com_2 == 11)
		|| (co.com_1 == 2 && co.com_2 == 7)
		|| (co.com_1 == 2 && co.com_2 == 17)
		|| (co.com_1 == 12 && co.com_2 == 7)
		|| (co.com_1 == 12 && co.com_2 == 17)
		|| (co.com_1 == 7 && co.com_2 == 2)
		|| (co.com_1 == 7 && co.com_2 == 12)
		|| (co.com_1 == 17 && co.com_2 == 2)
		|| (co.com_1 == 17 && co.com_2 == 12)
		|| (co.com_1 == 3 && co.com_2 == 6)
		|| (co.com_1 == 3 && co.com_2 == 16)
		|| (co.com_1 == 13 && co.com_2 == 6)
		|| (co.com_1 == 13 && co.com_2 == 16)
		|| (co.com_1 == 6 && co.com_2 == 3)
		|| (co.com_1 == 6 && co.com_2 == 13)
		|| (co.com_1 == 16 && co.com_2 == 3)
		|| (co.com_1 == 16 && co.com_2 == 13)
		|| (co.com_1 == 4 && co.com_2 == 5)
		|| (co.com_1 == 4 && co.com_2 == 15)
		|| (co.com_1 == 14 && co.com_2 == 5)
		|| (co.com_1 == 14 && co.com_2 == 15)
		|| (co.com_1 == 5 && co.com_2 == 4)
		|| (co.com_1 == 5 && co.com_2 == 14)
		|| (co.com_1 == 15 && co.com_2 == 4)
		|| (co.com_1 == 15 && co.com_2 == 14)
		|| (co.com_1 == 9 && co.com_2 == 10)
		|| (co.com_1 == 9 && co.com_2 == 20)
		|| (co.com_1 == 19 && co.com_2 == 10)
		|| (co.com_1 == 19 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 9)
		|| (co.com_1 == 10 && co.com_2 == 19)
		|| (co.com_1 == 20 && co.com_2 == 9)
		|| (co.com_1 == 20 && co.com_2 == 19))
		co.score_com = 109;

	if ((co.com_1 == 4 && co.com_2 == 6)			// 4 6 세륙
		|| (co.com_1 == 4 && co.com_2 == 16)
		|| (co.com_1 == 14 && co.com_2 == 6)
		|| (co.com_1 == 14 && co.com_2 == 16)
		|| (co.com_1 == 6 && co.com_2 == 4)
		|| (co.com_1 == 6 && co.com_2 == 14)
		|| (co.com_1 == 16 && co.com_2 == 4)
		|| (co.com_1 == 16 && co.com_2 == 14))
		co.score_com = 115;

	if ((co.com_1 == 4 && co.com_2 == 10)			// 4 10 장사
		|| (co.com_1 == 4 && co.com_2 == 20)
		|| (co.com_1 == 14 && co.com_2 == 10)
		|| (co.com_1 == 14 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 4)
		|| (co.com_1 == 10 && co.com_2 == 14)
		|| (co.com_1 == 20 && co.com_2 == 4)
		|| (co.com_1 == 20 && co.com_2 == 14))
		co.score_com = 120;

	if ((co.com_1 == 1 && co.com_2 == 10)			// 1 10 장삥
		|| (co.com_1 == 1 && co.com_2 == 20)
		|| (co.com_1 == 11 && co.com_2 == 10)
		|| (co.com_1 == 11 && co.com_2 == 20)
		|| (co.com_1 == 10 && co.com_2 == 1)
		|| (co.com_1 == 10 && co.com_2 == 11)
		|| (co.com_1 == 20 && co.com_2 == 1)
		|| (co.com_1 == 20 && co.com_2 == 11))
		co.score_com = 125;

	if ((co.com_1 == 1 && co.com_2 == 9)			// 1 10 구삥
		|| (co.com_1 == 1 && co.com_2 == 19)
		|| (co.com_1 == 11 && co.com_2 == 9)
		|| (co.com_1 == 11 && co.com_2 == 19)
		|| (co.com_1 == 9 && co.com_2 == 1)
		|| (co.com_1 == 9 && co.com_2 == 11)
		|| (co.com_1 == 19 && co.com_2 == 1)
		|| (co.com_1 == 19 && co.com_2 == 11))
		co.score_com = 130;

	if ((co.com_1 == 1 && co.com_2 == 4)			// 1 4 독사
		|| (co.com_1 == 1 && co.com_2 == 14)
		|| (co.com_1 == 11 && co.com_2 == 4)
		|| (co.com_1 == 11 && co.com_2 == 14)
		|| (co.com_1 == 4 && co.com_2 == 1)
		|| (co.com_1 == 4 && co.com_2 == 11)
		|| (co.com_1 == 14 && co.com_2 == 1)
		|| (co.com_1 == 14 && co.com_2 == 11))
		co.score_com = 135;

	if ((co.com_1 == 1 && co.com_2 == 2)			// 1 2 알리
		|| (co.com_1 == 1 && co.com_2 == 12)
		|| (co.com_1 == 11 && co.com_2 == 2)
		|| (co.com_1 == 11 && co.com_2 == 12)
		|| (co.com_1 == 2 && co.com_2 == 1)
		|| (co.com_1 == 2 && co.com_2 == 11)
		|| (co.com_1 == 12 && co.com_2 == 1)
		|| (co.com_1 == 12 && co.com_2 == 11))
		co.score_com = 140;

	if ((co.com_1 == 1 && co.com_2 == 11)			// 1 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 11 && co.com_2 == 1))
	{
		co.score_com = 150;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 2 && co.com_2 == 12)			// 2 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 12 && co.com_2 == 2))
	{
		co.score_com = 160;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 3 && co.com_2 == 13)			// 3 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 13 && co.com_2 == 3))
	{
		co.score_com = 170;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 4 && co.com_2 == 14)			// 4 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 14 && co.com_2 == 4))
	{
		co.score_com = 180;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 5 && co.com_2 == 15)			// 5 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 15 && co.com_2 == 5))
	{
		co.score_com = 190;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 6 && co.com_2 == 16)			// 6 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 16 && co.com_2 == 6))
	{
		co.score_com = 200;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 7 && co.com_2 == 17)			// 7 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 17 && co.com_2 == 7))
	{
		co.score_com = 210;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 8 && co.com_2 == 18)			// 8 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 18 && co.com_2 == 8))
	{
		co.score_com = 220;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 9 && co.com_2 == 19)			// 9 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (co.com_1 == 19 && co.com_2 == 9))
	{
		co.score_com = 230;
		if ((pl.player_1 == 3 && pl.player_2 == 7)
			|| (pl.player_1 == 3 && pl.player_2 == 17)
			|| (pl.player_1 == 13 && pl.player_2 == 7)
			|| (pl.player_1 == 13 && pl.player_2 == 17)
			|| (pl.player_1 == 7 && pl.player_2 == 3)
			|| (pl.player_1 == 7 && pl.player_2 == 13)
			|| (pl.player_1 == 17 && pl.player_2 == 3)
			|| (pl.player_1 == 17 && pl.player_2 == 13))
			pl.score_pl = 240;
	}

	if ((co.com_1 == 10 && co.com_2 == 20)			// 10 장땡(땡잡이로 못잡음)
		|| (co.com_1 == 20 && co.com_2 == 10))
		co.score_com = 250;

	if ((co.com_1 == 1 && co.com_2 == 3)			// 1 3 or 1 8 광땡 --> 상대가 암행어사이면 상대 승
		|| (co.com_1 == 3 && co.com_2 == 1)
		|| (co.com_1 == 1 && co.com_2 == 8)
		|| (co.com_1 == 8 && co.com_2 == 1))
	{
		co.score_com = 270;
		if ((pl.player_1 == 14 && pl.player_2 == 17)
			|| (pl.player_1 == 17 && pl.player_2 == 14))
			pl.score_pl = 285;
	}

	if ((co.com_1 == 3 && co.com_2 == 8)			// 3 8 광땡
		|| (co.com_1 == 8 && co.com_2 == 3))
		co.score_com = 300;
	
	// 플레이어 패에 따른 점수 부여
	if ((pl.player_1 == 2 && pl.player_2 == 8)			// 2 8 망통
		|| (pl.player_1 == 2 && pl.player_2 == 18)
		|| (pl.player_1 == 12 && pl.player_2 == 8)
		|| (pl.player_1 == 12 && pl.player_2 == 18)
		|| (pl.player_1 == 8 && pl.player_2 == 2)
		|| (pl.player_1 == 8 && pl.player_2 == 12)
		|| (pl.player_1 == 18 && pl.player_2 == 2)
		|| (pl.player_1 == 18 && pl.player_2 == 12))
		pl.score_pl = 100;

	if ((pl.player_1 == 3 && pl.player_2 == 7)			// 3 7 망통 (상대가 땡이 아니면 망통임)
		|| (pl.player_1 == 3 && pl.player_2 == 17)
		|| (pl.player_1 == 13 && pl.player_2 == 7)
		|| (pl.player_1 == 13 && pl.player_2 == 17)
		|| (pl.player_1 == 7 && pl.player_2 == 3)
		|| (pl.player_1 == 7 && pl.player_2 == 13)
		|| (pl.player_1 == 17 && pl.player_2 == 3)
		|| (pl.player_1 == 17 && pl.player_2 == 13))
		pl.score_pl = 100;

	if ((pl.player_1 == 2 && pl.player_2 == 9)			// 1끗 (암행어사는 상대가 광땡이 아니면 1끗)
		|| (pl.player_1 == 2 && pl.player_2 == 19)
		|| (pl.player_1 == 12 && pl.player_2 == 9)
		|| (pl.player_1 == 12 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 2)
		|| (pl.player_1 == 9 && pl.player_2 == 12)
		|| (pl.player_1 == 19 && pl.player_2 == 2)
		|| (pl.player_1 == 19 && pl.player_2 == 12)
		|| (pl.player_1 == 3 && pl.player_2 == 8)
		|| (pl.player_1 == 3 && pl.player_2 == 18)
		|| (pl.player_1 == 13 && pl.player_2 == 8)
		|| (pl.player_1 == 13 && pl.player_2 == 18)
		|| (pl.player_1 == 8 && pl.player_2 == 3)
		|| (pl.player_1 == 8 && pl.player_2 == 13)
		|| (pl.player_1 == 18 && pl.player_2 == 3)
		|| (pl.player_1 == 18 && pl.player_2 == 13)
		|| (pl.player_1 == 4 && pl.player_2 == 7)
		|| (pl.player_1 == 4 && pl.player_2 == 17)
		|| (pl.player_1 == 14 && pl.player_2 == 7)
		|| (pl.player_1 == 14 && pl.player_2 == 17)
		|| (pl.player_1 == 7 && pl.player_2 == 4)
		|| (pl.player_1 == 7 && pl.player_2 == 14)
		|| (pl.player_1 == 17 && pl.player_2 == 4)
		|| (pl.player_1 == 17 && pl.player_2 == 14)
		|| (pl.player_1 == 5 && pl.player_2 == 6)
		|| (pl.player_1 == 5 && pl.player_2 == 16)
		|| (pl.player_1 == 15 && pl.player_2 == 6)
		|| (pl.player_1 == 15 && pl.player_2 == 16)
		|| (pl.player_1 == 6 && pl.player_2 == 5)
		|| (pl.player_1 == 6 && pl.player_2 == 15)
		|| (pl.player_1 == 16 && pl.player_2 == 5)
		|| (pl.player_1 == 16 && pl.player_2 == 15))
		pl.score_pl = 101;

	if ((pl.player_1 == 2 && pl.player_2 == 10)			// 2끗
		|| (pl.player_1 == 2 && pl.player_2 == 20)
		|| (pl.player_1 == 12 && pl.player_2 == 10)
		|| (pl.player_1 == 12 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 2)
		|| (pl.player_1 == 10 && pl.player_2 == 12)
		|| (pl.player_1 == 20 && pl.player_2 == 2)
		|| (pl.player_1 == 20 && pl.player_2 == 12)
		|| (pl.player_1 == 3 && pl.player_2 == 9)
		|| (pl.player_1 == 3 && pl.player_2 == 19)
		|| (pl.player_1 == 13 && pl.player_2 == 9)
		|| (pl.player_1 == 13 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 3)
		|| (pl.player_1 == 9 && pl.player_2 == 13)
		|| (pl.player_1 == 19 && pl.player_2 == 3)
		|| (pl.player_1 == 19 && pl.player_2 == 13)
		|| (pl.player_1 == 4 && pl.player_2 == 8)
		|| (pl.player_1 == 4 && pl.player_2 == 18)
		|| (pl.player_1 == 14 && pl.player_2 == 8)
		|| (pl.player_1 == 14 && pl.player_2 == 18)
		|| (pl.player_1 == 8 && pl.player_2 == 4)
		|| (pl.player_1 == 8 && pl.player_2 == 14)
		|| (pl.player_1 == 18 && pl.player_2 == 4)
		|| (pl.player_1 == 18 && pl.player_2 == 14)
		|| (pl.player_1 == 5 && pl.player_2 == 7)
		|| (pl.player_1 == 5 && pl.player_2 == 17)
		|| (pl.player_1 == 15 && pl.player_2 == 7)
		|| (pl.player_1 == 15 && pl.player_2 == 17)
		|| (pl.player_1 == 7 && pl.player_2 == 5)
		|| (pl.player_1 == 7 && pl.player_2 == 15)
		|| (pl.player_1 == 17 && pl.player_2 == 5)
		|| (pl.player_1 == 17 && pl.player_2 == 15))
		pl.score_pl = 102;

	if ((pl.player_1 == 3 && pl.player_2 == 10)			// 3끗 (9 4 구사는 재경기 패이므로 제외)
		|| (pl.player_1 == 3 && pl.player_2 == 20)
		|| (pl.player_1 == 13 && pl.player_2 == 10)
		|| (pl.player_1 == 13 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 3)
		|| (pl.player_1 == 10 && pl.player_2 == 13)
		|| (pl.player_1 == 20 && pl.player_2 == 3)
		|| (pl.player_1 == 20 && pl.player_2 == 13)
		|| (pl.player_1 == 5 && pl.player_2 == 8)
		|| (pl.player_1 == 5 && pl.player_2 == 18)
		|| (pl.player_1 == 15 && pl.player_2 == 8)
		|| (pl.player_1 == 15 && pl.player_2 == 18)
		|| (pl.player_1 == 8 && pl.player_2 == 5)
		|| (pl.player_1 == 8 && pl.player_2 == 15)
		|| (pl.player_1 == 18 && pl.player_2 == 5)
		|| (pl.player_1 == 18 && pl.player_2 == 15)
		|| (pl.player_1 == 6 && pl.player_2 == 7)
		|| (pl.player_1 == 6 && pl.player_2 == 17)
		|| (pl.player_1 == 16 && pl.player_2 == 7)
		|| (pl.player_1 == 16 && pl.player_2 == 17)
		|| (pl.player_1 == 7 && pl.player_2 == 6)
		|| (pl.player_1 == 7 && pl.player_2 == 16)
		|| (pl.player_1 == 17 && pl.player_2 == 6)
		|| (pl.player_1 == 17 && pl.player_2 == 16))
		pl.score_pl = 103;

	if ((pl.player_1 == 1 && pl.player_2 == 3)			// 4끗
		|| (pl.player_1 == 1 && pl.player_2 == 13)
		|| (pl.player_1 == 11 && pl.player_2 == 3)
		|| (pl.player_1 == 11 && pl.player_2 == 13)
		|| (pl.player_1 == 3 && pl.player_2 == 1)
		|| (pl.player_1 == 3 && pl.player_2 == 11)
		|| (pl.player_1 == 13 && pl.player_2 == 1)
		|| (pl.player_1 == 13 && pl.player_2 == 11)
		|| (pl.player_1 == 5 && pl.player_2 == 9)
		|| (pl.player_1 == 5 && pl.player_2 == 19)
		|| (pl.player_1 == 15 && pl.player_2 == 9)
		|| (pl.player_1 == 15 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 5)
		|| (pl.player_1 == 9 && pl.player_2 == 15)
		|| (pl.player_1 == 19 && pl.player_2 == 5)
		|| (pl.player_1 == 19 && pl.player_2 == 15)
		|| (pl.player_1 == 6 && pl.player_2 == 8)
		|| (pl.player_1 == 6 && pl.player_2 == 18)
		|| (pl.player_1 == 16 && pl.player_2 == 8)
		|| (pl.player_1 == 16 && pl.player_2 == 18)
		|| (pl.player_1 == 8 && pl.player_2 == 6)
		|| (pl.player_1 == 8 && pl.player_2 == 16)
		|| (pl.player_1 == 18 && pl.player_2 == 6)
		|| (pl.player_1 == 18 && pl.player_2 == 16))
		pl.score_pl = 104;

	if ((pl.player_1 == 2 && pl.player_2 == 3)			// 5끗
		|| (pl.player_1 == 2 && pl.player_2 == 13)
		|| (pl.player_1 == 12 && pl.player_2 == 3)
		|| (pl.player_1 == 12 && pl.player_2 == 13)
		|| (pl.player_1 == 3 && pl.player_2 == 2)
		|| (pl.player_1 == 3 && pl.player_2 == 12)
		|| (pl.player_1 == 13 && pl.player_2 == 2)
		|| (pl.player_1 == 13 && pl.player_2 == 12)
		|| (pl.player_1 == 5 && pl.player_2 == 10)
		|| (pl.player_1 == 5 && pl.player_2 == 20)
		|| (pl.player_1 == 15 && pl.player_2 == 10)
		|| (pl.player_1 == 15 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 5)
		|| (pl.player_1 == 10 && pl.player_2 == 15)
		|| (pl.player_1 == 20 && pl.player_2 == 5)
		|| (pl.player_1 == 20 && pl.player_2 == 15)
		|| (pl.player_1 == 6 && pl.player_2 == 9)
		|| (pl.player_1 == 6 && pl.player_2 == 19)
		|| (pl.player_1 == 16 && pl.player_2 == 9)
		|| (pl.player_1 == 16 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 6)
		|| (pl.player_1 == 9 && pl.player_2 == 16)
		|| (pl.player_1 == 19 && pl.player_2 == 6)
		|| (pl.player_1 == 19 && pl.player_2 == 16)
		|| (pl.player_1 == 7 && pl.player_2 == 8)
		|| (pl.player_1 == 7 && pl.player_2 == 18)
		|| (pl.player_1 == 17 && pl.player_2 == 8)
		|| (pl.player_1 == 17 && pl.player_2 == 18)
		|| (pl.player_1 == 8 && pl.player_2 == 7)
		|| (pl.player_1 == 8 && pl.player_2 == 17)
		|| (pl.player_1 == 18 && pl.player_2 == 7)
		|| (pl.player_1 == 18 && pl.player_2 == 17))
		pl.score_pl = 105;

	if ((pl.player_1 == 1 && pl.player_2 == 5)			// 6끗
		|| (pl.player_1 == 1 && pl.player_2 == 15)
		|| (pl.player_1 == 11 && pl.player_2 == 5)
		|| (pl.player_1 == 11 && pl.player_2 == 15)
		|| (pl.player_1 == 5 && pl.player_2 == 1)
		|| (pl.player_1 == 5 && pl.player_2 == 11)
		|| (pl.player_1 == 15 && pl.player_2 == 1)
		|| (pl.player_1 == 15 && pl.player_2 == 11)
		|| (pl.player_1 == 2 && pl.player_2 == 4)
		|| (pl.player_1 == 2 && pl.player_2 == 14)
		|| (pl.player_1 == 12 && pl.player_2 == 4)
		|| (pl.player_1 == 12 && pl.player_2 == 14)
		|| (pl.player_1 == 4 && pl.player_2 == 2)
		|| (pl.player_1 == 4 && pl.player_2 == 12)
		|| (pl.player_1 == 14 && pl.player_2 == 2)
		|| (pl.player_1 == 14 && pl.player_2 == 12)
		|| (pl.player_1 == 6 && pl.player_2 == 10)
		|| (pl.player_1 == 6 && pl.player_2 == 20)
		|| (pl.player_1 == 16 && pl.player_2 == 10)
		|| (pl.player_1 == 16 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 6)
		|| (pl.player_1 == 20 && pl.player_2 == 16)
		|| (pl.player_1 == 10 && pl.player_2 == 6)
		|| (pl.player_1 == 20 && pl.player_2 == 16)
		|| (pl.player_1 == 7 && pl.player_2 == 9)
		|| (pl.player_1 == 7 && pl.player_2 == 19)
		|| (pl.player_1 == 17 && pl.player_2 == 9)
		|| (pl.player_1 == 17 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 7)
		|| (pl.player_1 == 9 && pl.player_2 == 17)
		|| (pl.player_1 == 19 && pl.player_2 == 7)
		|| (pl.player_1 == 19 && pl.player_2 == 17))
		pl.score_pl = 106;

	if ((pl.player_1 == 1 && pl.player_2 == 6)			// 7끗
		|| (pl.player_1 == 1 && pl.player_2 == 16)
		|| (pl.player_1 == 11 && pl.player_2 == 6)
		|| (pl.player_1 == 11 && pl.player_2 == 16)
		|| (pl.player_1 == 6 && pl.player_2 == 1)
		|| (pl.player_1 == 6 && pl.player_2 == 11)
		|| (pl.player_1 == 16 && pl.player_2 == 1)
		|| (pl.player_1 == 16 && pl.player_2 == 11)
		|| (pl.player_1 == 2 && pl.player_2 == 5)
		|| (pl.player_1 == 2 && pl.player_2 == 15)
		|| (pl.player_1 == 12 && pl.player_2 == 5)
		|| (pl.player_1 == 12 && pl.player_2 == 15)
		|| (pl.player_1 == 5 && pl.player_2 == 2)
		|| (pl.player_1 == 5 && pl.player_2 == 12)
		|| (pl.player_1 == 15 && pl.player_2 == 2)
		|| (pl.player_1 == 15 && pl.player_2 == 12)
		|| (pl.player_1 == 3 && pl.player_2 == 4)
		|| (pl.player_1 == 3 && pl.player_2 == 14)
		|| (pl.player_1 == 13 && pl.player_2 == 4)
		|| (pl.player_1 == 13 && pl.player_2 == 14)
		|| (pl.player_1 == 4 && pl.player_2 == 3)
		|| (pl.player_1 == 4 && pl.player_2 == 13)
		|| (pl.player_1 == 14 && pl.player_2 == 3)
		|| (pl.player_1 == 14 && pl.player_2 == 13)
		|| (pl.player_1 == 7 && pl.player_2 == 10)
		|| (pl.player_1 == 7 && pl.player_2 == 20)
		|| (pl.player_1 == 17 && pl.player_2 == 10)
		|| (pl.player_1 == 17 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 7)
		|| (pl.player_1 == 10 && pl.player_2 == 17)
		|| (pl.player_1 == 20 && pl.player_2 == 7)
		|| (pl.player_1 == 20 && pl.player_2 == 17)
		|| (pl.player_1 == 8 && pl.player_2 == 9)
		|| (pl.player_1 == 8 && pl.player_2 == 19)
		|| (pl.player_1 == 18 && pl.player_2 == 9)
		|| (pl.player_1 == 18 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 8)
		|| (pl.player_1 == 9 && pl.player_2 == 18)
		|| (pl.player_1 == 19 && pl.player_2 == 8)
		|| (pl.player_1 == 19 && pl.player_2 == 18))
		pl.score_pl = 107;

	if ((pl.player_1 == 1 && pl.player_2 == 7)			// 8끗
		|| (pl.player_1 == 1 && pl.player_2 == 17)
		|| (pl.player_1 == 11 && pl.player_2 == 7)
		|| (pl.player_1 == 11 && pl.player_2 == 17)
		|| (pl.player_1 == 7&& pl.player_2 == 1)
		|| (pl.player_1 == 7 && pl.player_2 == 11)
		|| (pl.player_1 == 17 && pl.player_2 == 1)
		|| (pl.player_1 == 17 && pl.player_2 == 11)
		|| (pl.player_1 == 2 && pl.player_2 == 6)
		|| (pl.player_1 == 2 && pl.player_2 == 16)
		|| (pl.player_1 == 12 && pl.player_2 == 6)
		|| (pl.player_1 == 12 && pl.player_2 == 16)
		|| (pl.player_1 == 6 && pl.player_2 == 2)
		|| (pl.player_1 == 6 && pl.player_2 == 12)
		|| (pl.player_1 == 16 && pl.player_2 == 2)
		|| (pl.player_1 == 16 && pl.player_2 == 12)
		|| (pl.player_1 == 3 && pl.player_2 == 5)
		|| (pl.player_1 == 3 && pl.player_2 == 15)
		|| (pl.player_1 == 13 && pl.player_2 == 5)
		|| (pl.player_1 == 13 && pl.player_2 == 15)
		|| (pl.player_1 == 5 && pl.player_2 == 3)
		|| (pl.player_1 == 5 && pl.player_2 == 13)
		|| (pl.player_1 == 15 && pl.player_2 == 3)
		|| (pl.player_1 == 15 && pl.player_2 == 13)
		|| (pl.player_1 == 8 && pl.player_2 == 10)
		|| (pl.player_1 == 8 && pl.player_2 == 20)
		|| (pl.player_1 == 18 && pl.player_2 == 10)
		|| (pl.player_1 == 18 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 8)
		|| (pl.player_1 == 10 && pl.player_2 == 18)
		|| (pl.player_1 == 20 && pl.player_2 == 8)
		|| (pl.player_1 == 20 && pl.player_2 == 18))
		pl.score_pl = 108;

	if ((pl.player_1 == 1 && pl.player_2 == 8)			// 9끗
		|| (pl.player_1 == 1 && pl.player_2 == 18)
		|| (pl.player_1 == 11 && pl.player_2 == 8)
		|| (pl.player_1 == 11 && pl.player_2 == 18)
		|| (pl.player_1 == 8 && pl.player_2 == 1)
		|| (pl.player_1 == 8 && pl.player_2 == 11)
		|| (pl.player_1 == 18 && pl.player_2 == 1)
		|| (pl.player_1 == 18 && pl.player_2 == 11)
		|| (pl.player_1 == 2 && pl.player_2 == 7)
		|| (pl.player_1 == 2 && pl.player_2 == 17)
		|| (pl.player_1 == 12 && pl.player_2 == 7)
		|| (pl.player_1 == 12 && pl.player_2 == 17)
		|| (pl.player_1 == 7 && pl.player_2 == 2)
		|| (pl.player_1 == 7 && pl.player_2 == 12)
		|| (pl.player_1 == 17 && pl.player_2 == 2)
		|| (pl.player_1 == 17 && pl.player_2 == 12)
		|| (pl.player_1 == 3 && pl.player_2 == 6)
		|| (pl.player_1 == 3 && pl.player_2 == 16)
		|| (pl.player_1 == 13 && pl.player_2 == 6)
		|| (pl.player_1 == 13 && pl.player_2 == 16)
		|| (pl.player_1 == 6 && pl.player_2 == 3)
		|| (pl.player_1 == 6 && pl.player_2 == 13)
		|| (pl.player_1 == 16 && pl.player_2 == 3)
		|| (pl.player_1 == 16 && pl.player_2 == 13)
		|| (pl.player_1 == 4 && pl.player_2 == 5)
		|| (pl.player_1 == 4 && pl.player_2 == 15)
		|| (pl.player_1 == 14 && pl.player_2 == 5)
		|| (pl.player_1 == 14 && pl.player_2 == 15)
		|| (pl.player_1 == 5 && pl.player_2 == 4)
		|| (pl.player_1 == 5 && pl.player_2 == 14)
		|| (pl.player_1 == 15 && pl.player_2 == 4)
		|| (pl.player_1 == 15 && pl.player_2 == 14)
		|| (pl.player_1 == 9 && pl.player_2 == 10)
		|| (pl.player_1 == 9 && pl.player_2 == 20)
		|| (pl.player_1 == 19 && pl.player_2 == 10)
		|| (pl.player_1 == 19 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 9)
		|| (pl.player_1 == 10 && pl.player_2 == 19)
		|| (pl.player_1 == 20 && pl.player_2 == 9)
		|| (pl.player_1 == 20 && pl.player_2 == 19))
		pl.score_pl = 109;

	if ((pl.player_1 == 4 && pl.player_2 == 6)			// 4 6 세륙
		|| (pl.player_1 == 4 && pl.player_2 == 16)
		|| (pl.player_1 == 14 && pl.player_2 == 6)
		|| (pl.player_1 == 14 && pl.player_2 == 16)
		|| (pl.player_1 == 6 && pl.player_2 == 4)
		|| (pl.player_1 == 6 && pl.player_2 == 14)
		|| (pl.player_1 == 16 && pl.player_2 == 4)
		|| (pl.player_1 == 16 && pl.player_2 == 14))
		pl.score_pl = 115;

	if ((pl.player_1 == 4 && pl.player_2 == 10)			// 4 10 장사
		|| (pl.player_1 == 4 && pl.player_2 == 20)
		|| (pl.player_1 == 14 && pl.player_2 == 10)
		|| (pl.player_1 == 14 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 4)
		|| (pl.player_1 == 10 && pl.player_2 == 14)
		|| (pl.player_1 == 20 && pl.player_2 == 4)
		|| (pl.player_1 == 20 && pl.player_2 == 14))
		pl.score_pl = 120;

	if ((pl.player_1 == 1 && pl.player_2 == 10)			// 1 10 장삥
		|| (pl.player_1 == 1 && pl.player_2 == 20)
		|| (pl.player_1 == 11 && pl.player_2 == 10)
		|| (pl.player_1 == 11 && pl.player_2 == 20)
		|| (pl.player_1 == 10 && pl.player_2 == 1)
		|| (pl.player_1 == 10 && pl.player_2 == 11)
		|| (pl.player_1 == 20 && pl.player_2 == 1)
		|| (pl.player_1 == 20 && pl.player_2 == 11))
		pl.score_pl = 125;

	if ((pl.player_1 == 1 && pl.player_2 == 9)			// 1 10 구삥
		|| (pl.player_1 == 1 && pl.player_2 == 19)
		|| (pl.player_1 == 11 && pl.player_2 == 9)
		|| (pl.player_1 == 11 && pl.player_2 == 19)
		|| (pl.player_1 == 9 && pl.player_2 == 1)
		|| (pl.player_1 == 9 && pl.player_2 == 11)
		|| (pl.player_1 == 19 && pl.player_2 == 1)
		|| (pl.player_1 == 19 && pl.player_2 == 11))
		pl.score_pl = 130;

	if ((pl.player_1 == 1 && pl.player_2 == 4)			// 1 4 독사
		|| (pl.player_1 == 1 && pl.player_2 == 14)
		|| (pl.player_1 == 11 && pl.player_2 == 4)
		|| (pl.player_1 == 11 && pl.player_2 == 14)
		|| (pl.player_1 == 4 && pl.player_2 == 1)
		|| (pl.player_1 == 4 && pl.player_2 == 11)
		|| (pl.player_1 == 14 && pl.player_2 == 1)
		|| (pl.player_1 == 14 && pl.player_2 == 11))
		pl.score_pl = 135;

	if ((pl.player_1 == 1 && pl.player_2 == 2)			// 1 2 알리
		|| (pl.player_1 == 1 && pl.player_2 == 12)
		|| (pl.player_1 == 11 && pl.player_2 == 2)
		|| (pl.player_1 == 11 && pl.player_2 == 12)
		|| (pl.player_1 == 2 && pl.player_2 == 1)
		|| (pl.player_1 == 2 && pl.player_2 == 11)
		|| (pl.player_1 == 12 && pl.player_2 == 1)
		|| (pl.player_1 == 12 && pl.player_2 == 11))
		pl.score_pl = 140;

	if ((pl.player_1 == 1 && pl.player_2 == 11)			// 1 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 11 && pl.player_2 == 1))
	{
		pl.score_pl = 150;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 2 && pl.player_2 == 12)			// 2 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 12 && pl.player_2 == 2))
	{
		pl.score_pl = 160;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 3 && pl.player_2 == 13)			// 3 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 13 && pl.player_2 == 3))
	{
		pl.score_pl = 170;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 4 && pl.player_2 == 14)			// 4 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 14 && pl.player_2 == 4))
	{
		pl.score_pl = 180;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 5 && pl.player_2 == 15)			// 5 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 15 && pl.player_2 == 5))
	{
		pl.score_pl = 190;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 6 && pl.player_2 == 16)			// 6 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 16 && pl.player_2 == 6))
	{
		pl.score_pl = 200;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 7 && pl.player_2 == 17)			// 7 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 17 && pl.player_2 == 7))
	{
		pl.score_pl = 210;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 8 && pl.player_2 == 18)			// 8 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 18 && pl.player_2 == 8))
	{
		pl.score_pl = 220;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 9 && pl.player_2 == 19)			// 9 땡 --> 상대가 3 7 땡잡이면 상대 승
		|| (pl.player_1 == 19 && pl.player_2 == 9))
	{
		pl.score_pl = 230;
		if ((co.com_1 == 3 && co.com_2 == 7)
			|| (co.com_1 == 3 && co.com_2 == 17)
			|| (co.com_1 == 13 && co.com_2 == 7)
			|| (co.com_1 == 13 && co.com_2 == 17)
			|| (co.com_1 == 7 && co.com_2 == 3)
			|| (co.com_1 == 7 && co.com_2 == 13)
			|| (co.com_1 == 17 && co.com_2 == 3)
			|| (co.com_1 == 17 && co.com_2 == 13))
			co.score_com = 240;
	}

	if ((pl.player_1 == 10 && pl.player_2 == 20)			// 10 장땡(땡잡이로 못잡음)
		|| (pl.player_1 == 20 && pl.player_2 == 10))
		pl.score_pl = 250;

	if ((pl.player_1 == 1 && pl.player_2 == 3)			// 1 3 or 1 8 광땡 --> 상대가 암행어사이면 상대 승
		|| (pl.player_1 == 3 && pl.player_2 == 1)
		|| (pl.player_1 == 1 && pl.player_2 == 8)
		|| (pl.player_1 == 8 && pl.player_2 == 1))
	{
		pl.score_pl = 270;
		if ((co.com_1 == 14 && co.com_2 == 17) || (co.com_1 == 17 && co.com_2 == 14))
			co.score_com = 285;
	}

	if ((pl.player_1 == 3 && pl.player_2 == 8) || (pl.player_1 == 8 && pl.player_2 == 3))		// 38광땡
		pl.score_pl = 300;
	
	winner = (int*)malloc(sizeof(int));			// 승자가 되는 자를 동적 메모리를 빌려서 출력

	*winner=score_cmp(co.score_com, pl.score_pl);			// 점수를 비교하여 승자가 컴퓨터면 1, 플레이어면 2, 비기면 3
	
	// 승자 출력
	if (*winner == 1)
		printf("\n당신은 패배했습니다..다음 기회를 노려봐요..\n");
	else if (*winner == 2)
		printf("\n당신이 이겼습니다! 축하드려요~!\n");
	else if (*winner == 3)
		printf("\n컴퓨터와 당신의 점수가 같으므로 재경기를 해야 합니다.\n");

	free(winner);			// 동적 메모리 반납

	// 재경기 권유
	printf("\n재경기를 하시겠습니까 ? (y/n) : ");
	while (1)
	{

		re = getchar();

		if ((re == 'y'))
		{
			printf("\n\n잠시 후, 화면을 지우고 다시 시작합니다.\n\n");
			printf("2..\n\n"); Sleep(1000);
			printf("1..\n"); Sleep(1000);
			system("cls");
			main();
		}
		if ((re == 'n'))
		{
			printf("\n\n잠시 후에 프로그램이 종료됩니다.\n\n");
			printf("2..\n\n"); Sleep(1000);
			printf("1..\n"); Sleep(1000);
			exit(1);
		}
	}

	return 0;
}
int score_cmp(int Cscore, int Pscore)			// 점수 비교 함수
{
	printf("컴퓨터의 점수는 %d 이고\n",Cscore);
	printf("당신의 점수는 %d 이므로\n",Pscore);
	if (Cscore > Pscore)
		return 1;
	else if (Cscore < Pscore)
		return 2;
	else if (Cscore == Pscore)
		return 3;
}
