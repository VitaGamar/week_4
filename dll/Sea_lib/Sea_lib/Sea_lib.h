#ifndef DllHeader
#define DllHeader
#define DLLexport __declspec(dllexport)

#include <iostream>
using namespace std;
const int N=12;
 struct Field
	{
		char FirstField[N][N];							// поле з≥ своњми корабл€ми
		char SecondField[N][N];							// результати ход≥в проти суперника
		int FlotLife;								   //к≥льк≥сть палуб на корабл≥
		bool win;									// ознака перемоги
	};

extern "C"
{
DLLexport void PrintFields(Field& );														//надрукувати пол€
DLLexport void setShips(Field& , Field&);															// поставити корабель
DLLexport void RunGamePlayer(Field& , Field&);												//процес гри
DLLexport void RunGameComp(Field& , Field&);
}

 bool ShipFieldTest(const int&, const int&, const int&, const int&, char [N][N] );  //перев≥рити чи можливо ставити корабель
 void setFlotShip(int, char [N][N]);												//поставити корабель (int-к≥льк≥сть палуб), х≥д гравц€
 void setFlotShipComp(int, char [N][N]);											//поставити корабель (int-к≥льк≥сть палуб),, х≥д ком;ютера
 void getAtackCoordinates(int& x, int& y);										//отримати координаты дл€ атаки, х≥д гравц€(вв≥д з клав≥атури)
 void getAtackCompCoordinates(int& x, int& y, char [N][N]);							//отримати координаты дл€ атаки, х≥д компётера
 bool ShipTest(const int&, const int&, char [N][N]);								//перев≥рити чи ≥снуЇ корабель
 void getDeletedShipCoordinates(const int&, const int&, int&, int&, int&, int&, char [N][N]);//отримати координаты знищеного корабл€
 void DeleteShip(const int&, const int&, const int&, const int&, char [N][N]);			//та позначити його на пол≥
#endif