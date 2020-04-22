#pragma once
class cpu
{
private:
	int a;
	int b;
public:
	cpu(void);
	~cpu(void);

//玩家四子的情况，必堵
bool FourChess(char CM[][15]);
//玩家三子的情况，需看情况堵
bool ThreeChess(char CM[][15]);
//玩家二子的特殊情况，需看情况堵
bool TwoChess(char CM[][15]);
//除去玩家三、四子的情况后，可攻
void Attach(char CM[][15]);
//己方四子的情况，必下
bool MyFourChess(char CM[][15]);

private:
	//找某种颜色的特定长度的串，1为白色，2为黑色
	bool FindXString(int X,int Color,char CM[][15]);

};

