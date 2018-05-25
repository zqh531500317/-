#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<queue>
#include<stdlib.h>
using namespace std;
#define windowlength 1600
#define windowwidth 900
#define gamelength 450
#define gamewidth 450
#define bodylength 15
int speed ;
int direction;
int inf[gamelength / bodylength][gamewidth / bodylength];
bool havefood;
double score,k;
char a[10];
class body {
public:
	int x;
	int y;
	void setbody(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
queue <body> snake;
int list() {
	printf("�������Ѷȵȼ�(1-5֮�䣬����Խ��Խ��),���س��˳���\n");
	char x = _getch();
	switch (x) {
	case '1':speed = 500; k = 0.5; break;
	case '2':speed = 300;k=1; break;
	case '3':speed = 180;k=1.5; break;
	case '4':speed = 80;k=2; break;
	case '5':speed = 30;k=3; break;
	case 13:return 0;
	default:printf("��������Ч����\n"); list(); break;
	}
	return 1;
}
void creat() {
	score = 0;
	memset(inf, 0, sizeof(inf));
	initgraph(windowlength, windowwidth);
	direction = 2;//Ĭ�Ϸ�������
	havefood = false;
	setorigin(100, 100);
	setlinecolor(RED);
	setlinestyle(PS_DASHDOT|PS_JOIN_ROUND,5);
	line(-3, -3, -3, 3 + gamewidth);
	line(gamelength+3, -3, gamelength + 3, 3 + gamewidth);
	line(-3, -3, gamelength+3 , -3);
	line(-3, 3 + gamewidth, gamelength+3 , 3 + gamewidth);
	setlinestyle(PS_SOLID , 1);
	setlinecolor(BLUE);
	setfillcolor(BLUE);
	body a, b, c;
	a.setbody(0, 0);
	b.setbody(0, bodylength);
	c.setbody(0, 2 * bodylength);
	inf[0][0] = 1;
	inf[0][1] = 1;
	inf[0][2] = 1;
	snake.push(a);
	snake.push(b);
	snake.push(c);
	fillrectangle(a.x, a.y, a.x + bodylength, a.y + bodylength);
	fillrectangle(b.x, b.y, b.x + bodylength, b.y + bodylength);
	fillrectangle(c.x, c.y, c.x + bodylength, c.y + bodylength);
}
void lose() {
	_itoa_s((int)score, a, 10);
	outtextxy(gamelength / 2 - 100, gamewidth / 2 - 30, "��ĵ÷�Ϊ:");
	outtextxy(gamelength / 2 - 10, gamewidth / 2 - 30, a);
	char x;
	while (x = _getch())
		if (x == 13) {
			closegraph();
			return;
		}
}
bool judgeandmove(body a,int x,body tail) {
	body temp;
	if (x == 1) {
		if(tail.y == 0||inf[tail.x/bodylength][tail.y / bodylength - 1]==1)
		return false;
		else if (inf[tail.x / bodylength][tail.y / bodylength - 1] == 2) {
			temp.setbody(tail.x, tail.y - bodylength);
			snake.push(temp);
			inf[tail.x / bodylength][tail.y / bodylength - 1] = 1;
			havefood = false;
			score += k;
		}
		else {
			temp.setbody(tail.x, tail.y - bodylength);
			snake.push(temp);
			fillrectangle(tail.x, tail.y - bodylength, tail.x + bodylength, tail.y);
			inf[tail.x / bodylength][tail.y / bodylength - 1] = 1;
			clearrectangle(a.x, a.y, a.x + bodylength, a.y + bodylength);
			inf[a.x / bodylength][a.y / bodylength] = 0;
			snake.pop();
		}
	}
	else if (x == 2 ) {
		if(tail.y == gamewidth - bodylength|| inf[tail.x / bodylength][tail.y / bodylength + 1] == 1)
		return false;
		else if (inf[tail.x / bodylength][tail.y / bodylength + 1] == 2) {
			temp.setbody(tail.x, tail.y + bodylength);
			snake.push(temp);
			inf[tail.x / bodylength][tail.y / bodylength + 1] = 1;
			havefood = false;
			score += k;
		}
		else {
			temp.setbody(tail.x, tail.y + bodylength);
			snake.push(temp);
			fillrectangle(tail.x, tail.y+bodylength , tail.x + bodylength, tail.y+2*bodylength);
			inf[tail.x / bodylength][tail.y / bodylength + 1] = 1;
			clearrectangle(a.x, a.y, a.x + bodylength, a.y + bodylength);
			inf[a.x / bodylength][a.y / bodylength] = 0;
			snake.pop();
		}
	}
	else if (x == 3 ) {
		if(tail.x == 0|| inf[tail.x / bodylength - 1][tail.y / bodylength] == 1)
		return false;
		else if (inf[tail.x / bodylength - 1][tail.y / bodylength] == 2) {
			temp.setbody(tail.x - bodylength, tail.y);
			snake.push(temp);
			inf[tail.x / bodylength - 1][tail.y / bodylength] = 1;
			havefood = false;
			score += k;
		}
		else {
			temp.setbody(tail.x - bodylength, tail.y);
			snake.push(temp);
			fillrectangle(tail.x - bodylength, tail.y, tail.x, tail.y+bodylength);
			inf[tail.x / bodylength - 1][tail.y / bodylength] = 1;
			clearrectangle(a.x, a.y, a.x + bodylength, a.y + bodylength);
			inf[a.x / bodylength][a.y / bodylength] = 0;
			snake.pop();
		}
	}
	else if (x == 4 ) {
		if(tail.x == gamelength - bodylength|| inf[tail.x / bodylength + 1][tail.y / bodylength] == 1)
	    return false;
		else if (inf[tail.x / bodylength + 1][tail.y / bodylength] == 2) {
			temp.setbody(tail.x + bodylength, tail.y);
			snake.push(temp);
			inf[tail.x / bodylength + 1][tail.y / bodylength] = 1;
			havefood = false;
			score += k;
		}
		else {
			temp.setbody(tail.x + bodylength, tail.y);
			snake.push(temp);
			fillrectangle(tail.x + bodylength, tail.y, tail.x + 2 * bodylength, tail.y+bodylength);
			inf[tail.x / bodylength + 1][tail.y / bodylength] = 1;
			clearrectangle(a.x, a.y, a.x + bodylength, a.y + bodylength);
			inf[a.x / bodylength][a.y / bodylength] = 0;
			snake.pop();
		}
	}
	return true;
}
void food() {
	int x, y;
	x = rand() % (gamelength / bodylength);
	y = rand() % (gamelength / bodylength);
	if (inf[x][y] == 1) {
		food();
		return;
	}
	else {
		inf[x][y] = 2;
		havefood = true;
		fillrectangle(x*bodylength, y*bodylength, x*bodylength + bodylength, y*bodylength + bodylength);
	}
}
int game() {	
	while (!snake.empty())
		snake.pop();
	if (list() == 0)
		return 0;
	system("cls");
	creat();
	char x;
	while (1) {
		if (_kbhit()) {
			x = _getch();
			if ((x == 'w'||x=='W')&&direction != 2) {
				direction = 1;
			}
			else if ((x == 's'||x=='S')&&direction != 1) {
				direction = 2;
			}
			else if ((x == 'a'||x=='A')&&direction != 4) {
				direction = 3;
			}
			else if ((x == 'd'||x=='D')&&direction != 3) {
				direction = 4;
			}
			else if (x == 27)
				break;
		}
		if (judgeandmove(snake.front(), direction, snake.back())) {
			;
		}
		else {
			lose();
			break;
		}
		if (!havefood)
			food();
		Sleep(speed);
		fflush(stdin);//������������棬��Сת���ӳ�
	}
	game();
}
int main() {
	srand((unsigned int)time(NULL));
	game();
	return 0;
}