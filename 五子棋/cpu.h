#pragma once
class cpu
{
private:
	int a;
	int b;
public:
	cpu(void);
	~cpu(void);

//������ӵ�������ض�
bool FourChess(char CM[][15]);
//������ӵ�������迴�����
bool ThreeChess(char CM[][15]);
//��Ҷ��ӵ�����������迴�����
bool TwoChess(char CM[][15]);
//��ȥ����������ӵ�����󣬿ɹ�
void Attach(char CM[][15]);
//�������ӵ����������
bool MyFourChess(char CM[][15]);

private:
	//��ĳ����ɫ���ض����ȵĴ���1Ϊ��ɫ��2Ϊ��ɫ
	bool FindXString(int X,int Color,char CM[][15]);

};

