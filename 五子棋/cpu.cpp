#include "cpu.h"
#include <stdlib.h>
#include <time.h>
cpu::cpu(void)
{
	a=0;
	b=0;
}


cpu::~cpu(void)
{

}
bool cpu::FindXString(int X,int Color,char CM[][15])
{
	int i,j;	//循环控制变量
	int m=0,n=0;//记录串开始的坐标
	int sign;
	int num=0;	//计数串长
	int color=0;//上一个棋子颜色是否与当前串一致
	int Rand[4]={0,0,0,0};
	srand(time(NULL));
	for(int num=1;num<5;)
	{
		int x=rand()%4;
		if(Rand[x]==0)
		{
			Rand[x]=num;
			num++;
		}
	}
	for(int x=0;x<4;x++)
	switch(Rand[x])
	{
	case 1:
	//横向检测
	for(i=0;i<15;i++)
	{
		color=0;
		for(j=0;j<15;j++)
		{
			if(CM[i][j]==Color)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i;
					n=j-1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==X)
			{
				if(m>=0&&m<15&&n>=0&&n<15&&CM[m][n]==0)
				{
					a=m;
					b=n;
					return true;
				}else if(m>=0 && m<15 && (n+X+1)>=0 && (n+X+1)<15 && CM[m][n+X+1]==0)
				{
					a=m;
					b=n+X+1;
					return true;
				}
			}
		}
		num=0;
	}
	break;
	case 2:
	//左斜向检测
	for(sign=10;sign>=-10;sign--)
	{
		color=0;
		for(i=sign>0? 0:-sign,j=sign>=0? sign:0;sign>=0? j<15:i<15;i++,j++)
		{
			if(CM[i][j]==Color)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i-1;
					n=j-1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==X)
			{
				if(m>=0&&m<15&&n>=0&&n<15&&CM[m][n]==0)
				{
					a=m;
					b=n;
					return true;
				}else if(m+X+1>=0 && m+X+1<15 && (n+X+1)>=0 && (n+X+1)<15 && CM[m+X+1][n+X+1]==0)
				{
					a=m+X+1;
					b=n+X+1;
					return true;
				}
			}
		}
		num=0;
	}
	break;
	case 3:
	//纵向检测
	for(i=0;i<15;i++)
	{
		color=0;
		for(j=0;j<15;j++)
		{
			if(CM[j][i]==Color)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=j-1;
					n=i;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==X)
			{
				if(m>=0&&m<15&&n>=0&&n<15&&CM[m][n]==0)
				{
					a=m;
					b=n;
					return true;
				}else if((m+X+1)>=0 && (m+X+1)<15 && n>=0 && n<15 && CM[m+X+1][n]==0)
				{
					a=m+X+1;
					b=n;
					return true;
				}
			}
		}
		num=0;
	}
	break;
	case 4:
	//右斜向检测
	for(sign=4;sign<26;sign++)
	{
		color=0;
		for(i=sign>14? sign%14:0,j=sign>14? 14:sign;sign>14? i<15:j>=0;i++,j--)
		{
			if(CM[i][j]==Color)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i-1;
					n=j+1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==X)
			{
				if(m>=0&&m<15&&n>=0&&n<15&&CM[m][n]==0)
				{
					a=m;
					b=n;
					return true;
				}else if((m+X+1)>=0 && (m+X+1)<15 && (n-X-1)>=0 && (n-X-1)<15 && CM[m+X+1][n-X-1]==0)
				{
					a=m+X+1;
					b=n-X-1;
					return true;
				}
			}
		}
		num=0;
	}
	break;
	}
return false;
}

bool cpu::FourChess(char CM[][15])
{
	if(FindXString(4,1,CM))
	{
		CM[a][b]=2;
		return true;
	}
	return false;
}


bool cpu::ThreeChess(char CM[][15])
{
	int i,j;	//循环控制变量
	int m=0,n=0;//记录串开始的坐标
	int sign;
	int num=0;	//计数串长
	int color=0;//上一个棋子颜色是否与当前串一致
	
	//横向检测
	for(i=0;i<15;i++)
	{
		color=0;
		for(j=0;j<15;j++)
		{
			if(CM[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i;
					n=j-1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==3)
			{
				if(CM[m][n+4]==0&&CM[m][n+5]==1)
				{
					if(m<0||n+4<0||n+4>14)
					{
						return false;
					}
					CM[m][n+4]=2;
					return true;
				}else if(CM[m][n]==0&&CM[m][n-1]==1)
				{
					if(m<0||n-1<0)
					{
						return false;
					}
					CM[m][n-1]=2;
					return true;
				}else if(CM[m][n]==0&&CM[m][n+4]==0)
				{
					if(m<0||n<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}
			}
		}
		num=0;
	}
	//左斜向检测
	for(sign=10;sign>=-10;sign--)
	{
		color=0;
		for(i=sign>0? 0:-sign,j=sign>=0? sign:0;sign>=0? j<15:i<15;i++,j++)
		{
			if(CM[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i-1;
					n=j-1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==3)
			{
				if(CM[m+5][n+5]==1&&CM[m+4][n+4]==0)
				{
					if(m+4>14||n+4>14)
					{
						return false;
					}
					CM[m+4][n+4]=2;
					return true;
				}else if(CM[m][n]==0&&CM[m-1][n-1]==1)
				{
					if(m<0||n<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}else if(CM[m][n]==0&&CM[m+4][n+4]==0)
				{
					if(m<0||n<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}
			}
		}
		num=0;
	}
	
	//纵向检测
	for(i=0;i<15;i++)
	{
		color=0;
		for(j=0;j<15;j++)
		{
			if(CM[j][i]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=j-1;
					n=i;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==3)
			{
				if(CM[m+5][n]==1&&CM[m+4][n]==0)
				{
					if(m+5>14||n<0)
					{
						return false;
					}
					CM[m+4][n]=2;
					return true;
				}else if(CM[m-1][n]==1&&CM[m][n]==0)
				{
					if(m-1<0||n<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}else if(CM[m][n]==0&&CM[m+4][n]==0)
				{
					if(m+4>14||n<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}
			}
		}
		num=0;
	}
	//右斜向检测
	for(sign=4;sign<26;sign++)
	{
		color=0;
		for(i=sign>14? sign%14:0,j=sign>14? 14:sign;sign>14? i<15:j>=0;i++,j--)
		{
			if(CM[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i-1;
					n=j+1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==3)
			{
				if(CM[m+5][n-5]==1&&CM[m+4][n-4]==0)
				{
					if(m+5>14||n-5<0)
					{
						return false;
					}
					CM[m+4][n-4]=2;
					return true;
				}else if(CM[m-1][n+1]==1&&CM[m][n]==0)
				{
					if(m-1<0||n+1>14)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}else if(CM[m+4][n-4]==0&&CM[m][n]==0)
				{
					if(m+4>14||n-4<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}

			}
		}
		num=0;
	}
	return false;
}

void cpu::Attach(char CM[][15])
{
	
	if(FindXString(4,2,CM))
	{
		CM[a][b]=2;
	}else if(FindXString(3,2,CM))
	{
		CM[a][b]=2;
	}else if(FindXString(2,2,CM))
	{
		CM[a][b]=2;
	}else if(FindXString(1,2,CM))
	{
		CM[a][b]=2;
	}else if(FindXString(1,1,CM))
	{
		CM[a][b]=2;
	}
}

bool cpu::MyFourChess(char CM[][15])
{
	if(FindXString(4,2,CM))
	{
		CM[a][b]=2;
		return true;
	}
	return false;
}

bool cpu::TwoChess(char CM[][15])
{
	int i,j;	//循环控制变量
	int m=0,n=0;//记录串开始的坐标
	int sign;
	int num=0;	//计数串长
	int color=0;//上一个棋子颜色是否与当前串一致
	
	//横向检测
	for(i=0;i<15;i++)
	{
		color=0;
		for(j=0;j<15;j++)
		{
			if(CM[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i;
					n=j-1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==2)
			{
				if(CM[m][n]==0&&CM[m][n+3]==0&&CM[m][n+4]==1)
				{
					if(m<0||n+3<0||n+3>14)
					{
						return false;
					}
					CM[m][n+3]=2;
					return true;
				}else if(CM[m][n]==0&&CM[m][n+3]==0&&CM[m][n-1]==1)
				{
					if(m<0||n-1<0)
					{
						return false;
					}
					CM[m][n-1]=2;
					return true;
				}
			}
		}
		num=0;
	}
	//左斜向检测
	for(sign=10;sign>=-10;sign--)
	{
		color=0;
		for(i=sign>0? 0:-sign,j=sign>=0? sign:0;sign>=0? j<15:i<15;i++,j++)
		{
			if(CM[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i-1;
					n=j-1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==2)
			{
				if(CM[m][n]==0&&CM[m+4][n+4]==1&&CM[m+3][n+3]==0)
				{
					if(m+3>14||n+3>14)
					{
						return false;
					}
					CM[m+3][n+3]=2;
					return true;
				}else if(CM[m][n]==0&&CM[m+3][n+3]==0&&CM[m-1][n-1]==1)
				{
					if(m<0||n<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}
			}
		}
		num=0;
	}
	
	//纵向检测
	for(i=0;i<15;i++)
	{
		color=0;
		for(j=0;j<15;j++)
		{
			if(CM[j][i]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=j-1;
					n=i;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==2)
			{
				if(CM[m+4][n]==1&&CM[m][n]==0&&CM[m+3][n]==0)
				{
					if(m+3>14||n<0)
					{
						return false;
					}
					CM[m+3][n]=2;
					return true;
				}else if(CM[m-1][n]==1&&CM[m][n]==0&&CM[m+3][n]==0)
				{
					if(m-1<0||n<0)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}
			}
		}
		num=0;
	}
	//右斜向检测
	for(sign=4;sign<26;sign++)
	{
		color=0;
		for(i=sign>14? sign%14:0,j=sign>14? 14:sign;sign>14? i<15:j>=0;i++,j--)
		{
			if(CM[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else 
				{
					m=i-1;
					n=j+1;
					num=1;
					color=1;
				}
			}else 
			{
				color=0;
				num=0;
			}
			if(num==2)
			{
				if(CM[m+4][n-4]==1&&CM[m][n]==0&&CM[m+3][n-3]==0)
				{
					if(m+3>14||n-3<0)
					{
						return false;
					}
					CM[m+3][n-3]=2;
					return true;
				}else if(CM[m-1][n+1]==1&&CM[m][n]==0&&CM[m+3][n-3]==0)
				{
					if(m-1<0||n+1>14)
					{
						return false;
					}
					CM[m][n]=2;
					return true;
				}
			}
		}
		num=0;
	}
	return false;
}