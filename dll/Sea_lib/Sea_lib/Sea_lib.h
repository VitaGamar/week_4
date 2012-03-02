#ifndef DllHeader
#define DllHeader
#define DLLexport __declspec(dllexport)

#include <iostream>
using namespace std;
const int N=12;
 struct Field
	{
		char FirstField[N][N];							// ���� � ����� ���������
		char SecondField[N][N];							// ���������� ���� ����� ���������
		int FlotLife;								   //������� ����� �� ������
		bool win;									// ������ ��������
	};

extern "C"
{
DLLexport void PrintFields(Field& );														//����������� ����
DLLexport void setShips(Field& , Field&);															// ��������� ��������
DLLexport void RunGamePlayer(Field& , Field&);												//������ ���
DLLexport void RunGameComp(Field& , Field&);
}

 bool ShipFieldTest(const int&, const int&, const int&, const int&, char [N][N] );  //��������� �� ������� ������� ��������
 void setFlotShip(int, char [N][N]);												//��������� �������� (int-������� �����), ��� ������
 void setFlotShipComp(int, char [N][N]);											//��������� �������� (int-������� �����),, ��� ���;�����
 void getAtackCoordinates(int& x, int& y);										//�������� ���������� ��� �����, ��� ������(��� � ���������)
 void getAtackCompCoordinates(int& x, int& y, char [N][N]);							//�������� ���������� ��� �����, ��� ���������
 bool ShipTest(const int&, const int&, char [N][N]);								//��������� �� ���� ��������
 void getDeletedShipCoordinates(const int&, const int&, int&, int&, int&, int&, char [N][N]);//�������� ���������� ��������� �������
 void DeleteShip(const int&, const int&, const int&, const int&, char [N][N]);			//�� ��������� ���� �� ���
#endif