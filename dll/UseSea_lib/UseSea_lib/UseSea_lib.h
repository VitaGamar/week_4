#ifndef Header
#define Header
#include <iostream>
#include<conio.h>
using namespace std;
const int N=12;
struct Field
	{
		char FirstField[N][N];							// ���� � ����� ���������
		char SecondField[N][N];							// ���������� ���� ����� ���������
		int FlotLife;								   //������� ����� �� ������
		bool win;									// ������ ��������
	};
typedef void (*PrintFields)(Field& );														//����������� ����
typedef void (*setShips)(Field& , Field&);															// ��������� ��������
typedef void (*RunGamePlayer)(Field& , Field&);												//������ ���
typedef void (*RunGameComp)(Field& , Field&);
#endif