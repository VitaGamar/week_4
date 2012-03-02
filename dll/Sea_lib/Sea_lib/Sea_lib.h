#ifndef DllHeader
#define DllHeader
#define DLLexport __declspec(dllexport)

#include <iostream>
using namespace std;
const int N=12;
 struct Field
	{
		char FirstField[N][N];							// поле зі своїми кораблями
		char SecondField[N][N];							// результати ходів проти суперника
		int FlotLife;								   //кількість палуб на кораблі
		bool win;									// ознака перемоги
	};

extern "C"
{
DLLexport void PrintFields(Field& );														//надрукувати поля
DLLexport void setShips(Field& , Field&);															// поставити корабель
DLLexport void RunGamePlayer(Field& , Field&);												//процес гри
DLLexport void RunGameComp(Field& , Field&);
}

 bool ShipFieldTest(const int&, const int&, const int&, const int&, char [N][N] );  //перевірити чи можливо ставити корабель
 void setFlotShip(int, char [N][N]);												//поставити корабель (int-кількість палуб), хід гравця
 void setFlotShipComp(int, char [N][N]);											//поставити корабель (int-кількість палуб),, хід ком;ютера
 void getAtackCoordinates(int& x, int& y);										//отримати координаты для атаки, хід гравця(ввід з клавіатури)
 void getAtackCompCoordinates(int& x, int& y, char [N][N]);							//отримати координаты для атаки, хід компЮтера
 bool ShipTest(const int&, const int&, char [N][N]);								//перевірити чи існує корабель
 void getDeletedShipCoordinates(const int&, const int&, int&, int&, int&, int&, char [N][N]);//отримати координаты знищеного корабля
 void DeleteShip(const int&, const int&, const int&, const int&, char [N][N]);			//та позначити його на полі
#endif