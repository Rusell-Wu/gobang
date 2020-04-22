#pragma once
class player
{
private:
	char state;
public:
	int n;
	int m;
public:
	player(void);//构造函数

	~player(void);//析构函数

	bool CheckClick(int x,int y);//检查鼠标点击位置是否有效
	
};

