#pragma comment(lib,"msimg32.lib")
#include <Windows.h>
#include "resource.h"
#include "player.h"
#include "cpu.h"
//函数声明
LRESULT CALLBACK MainWinPorc(HWND hWnd,UINT message,WPARAM  wParam,LPARAM lParam);
void LoadChessBoard(HDC hdc);
int CheckWin();
void Reset();

//全局变量
char ChessMatrix[15][15]={0};
HINSTANCE hIn;
int MouseX=0,MouseY=0;//储存鼠标按下时的坐标
player players;
cpu Cpu;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevhInstance,LPSTR lpCmdline,int CmdShow)
{
	WNDCLASS MainWindow;
	HWND MainHwnd;
	MSG msg;
	hIn = hInstance;

	MainWindow.cbClsExtra=0;
	MainWindow.cbWndExtra=0;
	MainWindow.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	MainWindow.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	MainWindow.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	MainWindow.hInstance=hInstance;
	MainWindow.lpfnWndProc=MainWinPorc;
	MainWindow.lpszClassName="MainWin";
	MainWindow.lpszMenuName=NULL;
	MainWindow.style=CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&MainWindow);

	MainHwnd=CreateWindow("MainWin","五子棋",WS_MINIMIZEBOX|WS_SYSMENU,200,200,540,580,NULL,LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1)),hInstance,NULL);

	ShowWindow(MainHwnd,SW_SHOW);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


LRESULT CALLBACK MainWinPorc(HWND hWnd,UINT message,WPARAM  wParam,LPARAM lParam)
{
	HDC hdc;
	int WIN;
	PAINTSTRUCT ps;
	switch(message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		LoadChessBoard(hdc);
		EndPaint(hWnd,&ps);
		break;
	case WM_LBUTTONDOWN:
		MouseX=LOWORD (lParam);
		MouseY=HIWORD (lParam);
		break;
	case WM_LBUTTONUP:
		if(MouseX==LOWORD (lParam)&&MouseY==HIWORD (lParam))
		{
			if(players.CheckClick(MouseX,MouseY))
			{
				if(ChessMatrix[players.m][players.n]==0)
				{
					ChessMatrix[players.m][players.n]=1;
					hdc=GetDC(hWnd);
					LoadChessBoard(hdc);
					WIN=CheckWin();
					if(WIN==1)
					{
						MessageBox(hWnd,"You Win!!!\n (*^_^*)","你赢了",MB_OK|MB_ICONEXCLAMATION);
						Reset();
						LoadChessBoard(hdc);
						return 0;
					}
					if(!Cpu.MyFourChess(ChessMatrix))
					{
						if(!Cpu.FourChess(ChessMatrix))
						{
							if(!Cpu.ThreeChess(ChessMatrix))
							{
								if(!Cpu.TwoChess(ChessMatrix))
								{
									Cpu.Attach(ChessMatrix);
								}
							}
						}
					}
					LoadChessBoard(hdc);
					WIN=CheckWin();
					if(WIN==2)
					{
						MessageBox(hWnd,"You lose!\n/(ㄒoㄒ)/~~","你输啦",MB_OK|MB_ICONHAND);
						Reset();
						LoadChessBoard(hdc);
						return 0;
					}
				}
			}
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_MENU_NEWGAME:
			Reset();
			hdc=GetDC(hWnd);
			LoadChessBoard(hdc);
			break;
		case ID_MENU_EXIT:
			SendMessage(hWnd,WM_DESTROY,0,0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}

void LoadChessBoard(HDC hdc)
{
	//加载黑棋
	HBITMAP BlackBMP=LoadBitmap(hIn,MAKEINTRESOURCE(IDB_Black));
	HDC BlackBMPDC=CreateCompatibleDC(hdc);
	SelectObject(BlackBMPDC,BlackBMP);
	//加载白棋
	HBITMAP WhiteBMP=LoadBitmap(hIn,MAKEINTRESOURCE(IDB_White));
	HDC WhiteBMPDC=CreateCompatibleDC(hdc);
	SelectObject(WhiteBMPDC,WhiteBMP);
	//加载棋盘
	HBITMAP hBitmap=LoadBitmap(hIn,MAKEINTRESOURCE(IDB_Chessboard));
	HDC bitmapdc=CreateCompatibleDC(hdc);
	SelectObject(bitmapdc,hBitmap);
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			switch(ChessMatrix[i][j])
			{
			case 1:TransparentBlt(bitmapdc,11+j*35,11+i*35,28,28,WhiteBMPDC,0,0,97,97,RGB(0,0,0));
				break;
			case 2:
				TransparentBlt(bitmapdc,11+j*35,11+i*35,28,28,BlackBMPDC,0,0,200,200,RGB(255,255,255));
				break;
			}
		}
	}
	BitBlt(hdc,0,0,535,535,bitmapdc,0,0,SRCCOPY);
	DeleteObject(hBitmap);		//释放兼容性位图
	DeleteDC(bitmapdc);		//释放DC	
}

//判断胜负
int CheckWin()
{
	int i,j;
	int sign;
	int num=0;
	int color=0;//上一个棋子颜色
	//右斜向检测
	for(sign=4;sign<26;sign++)
	{
		for(i=sign>14? sign%14:0,j=sign>14? 14:sign;sign>14? i<15:j>=0;i++,j--)
		{
			if(ChessMatrix[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else if(color==0||color==2)
				{
					num=1;
					color=1;
				}
			}else if(ChessMatrix[i][j]==2)
			{
				
				if(color==2)
				{
					num++;
				}else if(color==0||color==1)
				{
					num=1;
					color=2;
				}
			}else color=0;
			if(num==5)
			{
				return color;
			}
		}
		num=0;
	}
	//左斜向检测
	for(sign=10;sign>=-10;sign--)
	{
		for(i=sign>0? 0:-sign,j=sign>=0? sign:0;sign>=0? j<15:i<15;i++,j++)
		{
			if(ChessMatrix[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else if(color==0||color==2)
				{
					num=1;
					color=1;
				}
			}else if(ChessMatrix[i][j]==2)
			{
				
				if(color==2)
				{
					num++;
				}else if(color==0||color==1)
				{
					num=1;
					color=2;
				}
			}else color=0;
			if(num==5)
			{
				return color;
			}
		}
		num=0;
	}
	//横向检测
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(ChessMatrix[i][j]==1)
			{
				if(color==1)
				{
					num++;
				}else if(color==0||color==2)
				{
					num=1;
					color=1;
				}
			}else if(ChessMatrix[i][j]==2)
			{
				
				if(color==2)
				{
					num++;
				}else if(color==0||color==1)
				{
					num=1;
					color=2;
				}
			}else color=0;
			if(num==5)
			{
				return color;
			}
		}
		num=0;
	}
	//纵向检测
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			if(ChessMatrix[j][i]==1)
			{
				if(color==1)
				{
					num++;
				}else if(color==0||color==2)
				{
					num=1;
					color=1;
				}
			}else if(ChessMatrix[j][i]==2)
			{
				
				if(color==2)
				{
					num++;
				}else if(color==0||color==1)
				{
					num=1;
					color=2;
				}
			}else color=0;
			if(num==5)
			{
				return color;
			}
		}
		num=0;
	}

	return 0;
}

//重置棋盘
void Reset()
{
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			ChessMatrix[i][j]=0;
		}
	}
}