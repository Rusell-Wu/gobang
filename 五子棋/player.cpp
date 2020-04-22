#include "player.h"


player::player(void)
{
	player::state=1;
	player::n=0;
	player::m=0;
}


player::~player(void)
{
}

bool player::CheckClick(int x,int y)
{
	int a=18,b=18,i=0;
	while(1)
	{
		if((a+8)<x)
		{
			a+=35;
		}else if(a>x)	return false;
		else break;
		i++;
	}
	player::n=i;
	i=0;
	while(1)
	{
		if((b+10)<y)
		{
			b+=35;
		}else if(b>y)	return false;
		else break;
		i++;
	}
	player::m=i;
	return true;
}

