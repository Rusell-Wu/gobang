#pragma once
class player
{
private:
	char state;
public:
	int n;
	int m;
public:
	player(void);//���캯��

	~player(void);//��������

	bool CheckClick(int x,int y);//��������λ���Ƿ���Ч
	
};

