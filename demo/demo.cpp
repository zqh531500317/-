#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<queue>
#include<stdlib.h>
using namespace std;
#define windowlength 450
#define windowwidth 450
#define bodylength 15
int speed ;
int direction;
int inf[windowlength / bodylength][windowwidth / bodylength];
bool havefood;
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
void creat() {
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
	outtextxy(windowlength / 2-80, windowwidth/2-30, "你输了，使用回车退出");
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
		if(tail.y == windowwidth - bodylength|| inf[tail.x / bodylength][tail.y / bodylength + 1] == 1)
		return false;
		else if (inf[tail.x / bodylength][tail.y / bodylength + 1] == 2) {
			temp.setbody(tail.x, tail.y + bodylength);
			snake.push(temp);
			inf[tail.x / bodylength][tail.y / bodylength + 1] = 1;
			havefood = false;
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
		if(tail.x == windowlength - bodylength|| inf[tail.x / bodylength + 1][tail.y / bodylength] == 1)
	    return false;
		else if (inf[tail.x / bodylength + 1][tail.y / bodylength] == 2) {
			temp.setbody(tail.x + bodylength, tail.y);
			snake.push(temp);
			inf[tail.x / bodylength + 1][tail.y / bodylength] = 1;
			havefood = false;
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
	srand((unsigned int)time(NULL));
	x = rand() % (windowlength / bodylength);
	y = rand() % (windowlength / bodylength);
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
int list() {
	printf("请输入难度等级(1-5之间，数字越大，越难),按回车退出。\n");
	char x = _getch();
	switch (x) {
	case '1':speed = 800; break;
	case '2':speed = 500; break;
	case '3':speed = 300; break;
	case '4':speed = 100; break;
	case '5':speed = 50; break;
	case 13:return 0;
	default:list();
	}
	return 1;
}
int main() {
	if (list() == 0)
		return 0;
	direction = 2;//默认方向向下
	initgraph(windowlength, windowwidth);
	char x;
	creat();
	while (1) {
		if (_kbhit()) {
			x = _getch();
			if (x == 'w'&&direction!=2) {
				direction = 1;
			}
			else if (x == 's'&&direction!=1) {
				direction = 2;
			}
			else if (x == 'a'&&direction!=4) {
				direction = 3;
			}
			else if (x == 'd'&&direction!=3) {
				direction = 4;
			}
			else if (x == 27)
				break;
		}
		if (judgeandmove(snake.front(), direction,snake.back())) {
			;
		}
		else {
			lose();
			break;
		}
		if (!havefood)
			food();
		Sleep(speed);
		fflush(stdin);//清空输入流缓存，减小转向延迟
	}
	while (x = _getch())
		if (x == 13)
			break;
	closegraph();

	return 0;
}