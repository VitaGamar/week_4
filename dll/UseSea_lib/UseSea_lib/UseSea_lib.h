#ifndef Header
#define Header
#include <iostream>
#include<conio.h>
using namespace std;
const int N=12;
struct Field
	{
		char FirstField[N][N];							// поле зі своїми кораблями
		char SecondField[N][N];							// результати ходів проти суперника
		int FlotLife;								   //кількість палуб на кораблі
		bool win;									// ознака перемоги
	};
typedef void (*PrintFields)(Field& );														//надрукувати поля
typedef void (*setShips)(Field& , Field&);															// поставити корабель
typedef void (*RunGamePlayer)(Field& , Field&);												//процес гри
typedef void (*RunGameComp)(Field& , Field&);
#endif