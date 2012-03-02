// Sea_lib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Sea_lib.h"
#include<iomanip>
#include <cstdlib>
#include <conio.h>
extern "C"
{

// вивід полів гравця
void PrintFields(Field& player)				
{
        system("cls");					//очистити экран
        cout<<"  ";      
        for (int i=1; i<=10; i++)		//надрукувати верхнюю лінійку координат для FirstField
                cout<<i<<" ";
        cout<<"  ";
        for(int i=1; i<=10; i++)		//надрукувати верхнюю лінійку координат для SecondField
                cout<<i<<" ";                        
        cout<<endl;       
        for(int i=1; i<=10; i++)		//надрукувати бокові лінійки координат і самі поля
        {
                cout<<setw(2)<<i;              
                for(int j=1; j<=10; j++)
                        cout<<player.FirstField[i][j]<<" ";               
                cout<<" "<<setw(2)<<i;               
                for(int k=1; k<=10; k++)
					cout<<player.SecondField[i][k]<<" ";                
                cout<<setw(2)<<i<<endl;
        }       
        cout<<endl;
}

void setShips(Field& player, Field& comp)
{
  
		PrintFields(player);
		setFlotShip(4,player.FirstField);
		setFlotShipComp(4, comp.FirstField);
 
        for(int i=0; i<2; i++)
        {
                PrintFields(player);
                setFlotShip(3,player.FirstField);
                setFlotShipComp(3,comp.FirstField);
        }
 
        for(int i=0; i<3; i++)
        {
                PrintFields(player);
                setFlotShip(2,player.FirstField);
                setFlotShipComp(2, comp.FirstField);
        }
 
        for(int i=0; i<4; i++)
        {
                PrintFields(player);
                setFlotShip(1,player.FirstField);
                setFlotShipComp(1, comp.FirstField);
        }
}
 //хід гравця
void RunGamePlayer(Field& player, Field& comp)
{
			 int x,y,x1,y1,x2,y2;				//дані для атаки(x,y) и встановлення/знищення кораблів(х1,у1,х2,у2)
                while(1)						//хід гравця
                {
                        PrintFields(player);										//надрукувати поля
                        getAtackCoordinates(x,y);									//отримати координати для атаки
                         if ( player.SecondField[y][x] == 'x' || player.SecondField[y][x]=='o')	// по полю влучати безглуздо
                        {												
                                cout<<"Stupid move! retry";
                                _getch();
                                continue;
                        }
                        else
                        {
                                if ( comp.FirstField[y][x] == ' ')
                                {											//якщо мимо
                                        player.SecondField[y][x] = 'o';
                                        PrintFields(player);
                                        _getch();
                                        return;
                                }
                                else										//якщо попав
                                {
                                        player.SecondField [y][x] = 'x';			//позначити потрапляння в ціль на другому полі
                                        comp.FirstField [y][x] = 'x';		//позначити потрапляння в ціль на першому полі, у компЮтера
                                        if ( ShipTest(x, y, comp.FirstField) )//якщо корабель було знищено
                                        {
                                                getDeletedShipCoordinates(x,y,x1,y1,x2,y2, comp.FirstField);//отримати координати
                                                DeleteShip(x1,y1,x2,y2, player.SecondField);			//позначити знищений корабель на другому поле
                                        }
 										comp.FlotLife--;							//зменшити на одну палубу
								}
                                if(comp.FlotLife>0 ? false : true)		//більше немає кораблів
                                {
                                        player.win=true;				// Ура! Ви виграли!
                                        PrintFields(player);
                                        _getch(); 
										return;
                                }                                                       
                        }
                }
}

//хід комп;ютера, дії аналогічні
 void RunGameComp(Field& player, Field& comp)
 {
     int x,y,x1,y1,x2,y2;       
				while(1)						
                {
                        getAtackCompCoordinates(x,y, comp.SecondField);
 
                        if ( comp.SecondField[y][x] =='x' ||  comp.SecondField[y][x]=='o')
                                continue;
                        else
                        {
                                if ( player.FirstField[y][x]==' ')
                                {
                                        comp.SecondField[y][x]='o';
										player.FirstField[y][x]='o'; 
                                        return;
                                }
                                else
                                {
                                       player.FirstField[y][x]='x';
										comp.SecondField[y][x]='x'; 
                                        PrintFields(player);
                                        _getch();
										 if ( ShipTest(x,y,player.FirstField) )
                                        {
                                                getDeletedShipCoordinates(x,y,x1,y1,x2,y2, player.FirstField);
                                                DeleteShip(x1,y1,x2,y2,player.FirstField);
                                                PrintFields(player);
                                                _getch();
                                                DeleteShip(x1,y1,x2,y2, comp.SecondField);
                                        }
										player.FlotLife--;
								}
                               if( player.FlotLife>0 ? false : true)
                               {
                                      comp.win=true;
                                      PrintFields(player);
                                      _getch();
                                      return;
                               }                              
                        }
                }
 }
}


//перевірка введених координат(чи дана ділянка ще не занаята)
bool ShipFieldTest(const int& x1, const int& y1, const int& x2, const int& y2, char field[N][N])	
{
		for(int i=y1-1; i<=y2+1; i++)				//перевірка чи за вказаними координатами можна ставити корабель
               for(int j=x1-1; j<=x2+1; j++)
                     if(field[i][j]!=' ')		
                            return true;			//так, можливо
        return false;
}

//розміщення корабля гравця розміром size 
void setFlotShip(int size, char First[N][N])
{
        int x1, y1, x2, y2;      
        while(1)
        {
             cout<<"Enter coordinates(2points) of you ship: ";
             cin>>x1>>y1>>x2>>y2;	 //	перевірка вводу(якщо координати виходять за межі поля і  дана клітинка зайнята)
             if((x1!=x2 && y1!=y2) || (x1<1)  || (x2>10)  || (y1<1)  || (y2>10) || (ShipFieldTest(x1,y1,x2,y2,First)))
               {
					  cout<<"Error! You can't put you ship here. Please, retry."<<endl;
					  continue;		// почнемо спочатку
			   }
              else
                      if(x2-x1!=size-1 && y2-y1!=size-1)				//якщо корабель не того розміру
                            {cout<<"Wrong number of deck!"<<endl; continue;}	//повторяємо ввід	
                      else
                           for(int i=y1; i<=y2; i++)		
                                for(int j=x1; j<=x2; j++)		
                                     First[i][j]='*';			//якщо всі умови виконались - можна ставити корабель
               return;
        }
}
//розміщення корабля компЮтера розміром size 
void setFlotShipComp(int size, char FirstComp[N][N])
{
        int x1,y1,x2,y2;
        srand(time(0));
        int POSITION;  
        while(1)
        {
                POSITION=1+rand() % 2;					//визначити позицію корабля               
                if(POSITION==1)							//якщо корабель розміщений вертикально
                {
                        x1=x2=1+rand() % 10;			//то тоді х1=х2
                        y1=1+rand() % 10;				
                        if ( y1+size-1 > 10 )			//якщо друга координата буде виходити за межі масива
                                continue;				//розпочати цикл спочатку
                        else							//інакше другій координаті присвоїти значение першої + кількість палуб 
                                y2 = y1+size-1;
                } 
                else									//якщо корабель розміщений горизонтально
                        {
                                y1 = y2=1+rand() % 10;
                                x1 = 1+rand() % 10;
                                if ( x1+size-1>10 )
                                        continue;
                                else
                                        x2 = x1+size-1;
                        }                 
                if ( ShipFieldTest(x1,y1,x2,y2,FirstComp) )			//якшо поруч є корабель
                        continue;						//розпочати цикл спочатку 
                else									//інакше позначити корабель на полі
                {
                        for ( int i=y1; i<=y2; i++ )
                                for ( int j=x1; j<=x2; j++ )
                                        FirstComp[i][j]='*';
                        return;
                }
        }
}
// якщо всі палуби корабля підстрелені - то корабель знищено. Розміщуємо навколо нього 'o'
void DeleteShip(const int& x1, const int& y1, const int& x2, const int& y2, char field[N][N])
{
        if(x1==x2)									//якщо корабель розміщений вертикально
        {
                for(int i=y1-1; i<=y2+1; i++)
                        for(int j=x1-1; j<=x2+1; j+=2)
                                field[i][j]='o';
                field[y1-1][x1]='o';
                field[y2+1][x1]='o';
        }
        
        else
        {
                for(int i=y1-1; i<=y2+1; i+=2)
                        for(int j=x1-1; j<=x2+1; j++)
                                field[i][j]='o';
                field[y1][x1-1]='o';
                field[y1][x2+1]='o';
        }
}

//перевірка чи палуба з координатами х, у - остання на кораблі
bool ShipTest(const int& x, const int& y, char field[N][N])
{
        for(int i=y; field[i][x]!=' ' && field[i][x]!='o'; i++)		//пройтися циклами в разні сторони доки поле!=координаті
                if(field[i][x]=='*')								//палуби корабля и повернути false якщо залишилась целая палуба
                        return false;
                        
        for(int i=y; field[i][x]!=' ' && field[i][x]!='o'; i--)
                if(field[i][x]=='*')
                        return false;
                        
        for(int j=x; field[y][j]!=' ' && field[y][j]!='o'; j++)
                if(field[y][j]=='*')
                        return false;
                        
        for(int j=x; field[y][j]!=' ' && field[y][j]!='o'; j--)
                if(field[y][j]=='*')
                        return false;
        return true;		// якщо весь корабель вже знищено - повертаємо true
}

//в х1, у1, х2, у2 - розміри корабля; х,у належать х1, у1, х2, у2
void getDeletedShipCoordinates(const int& x, const int& y, int& x1, int& y1, int& x2, int& y2, char first[N][N])
{
        if(first[y+1][x]=='*' || first[y+1][x]=='x' || first[y-1][x]=='*' || first[y-1][x]=='x')//якщо корабель розміщений вертикально
        {
                x1=x2=x;															//присвоїти х1 и х2 значення отриманого 'х'
                for(int i=y; first[i][x]!=' ' && first[i][x]!='o'; y1=i, i--);		//отримати координати у1 и у2
                for(int i=y; first[i][x]!=' ' && first[i][x]!='o'; y2=i, i++);
        }      
        else																		//якщо корабель розміщений по горизонтали
        {
                y1=y2=y;															//присвоїти у1 и у2 значення отриманого 'у'
                for(int j=x; first[y][j]!=' ' && first[y][j]!='o'; x1=j, j--);		//отримати координати х1 и х2
                for(int j=x; first[y][j]!=' ' && first[y][j]!='o'; x2=j, j++);
        }
}
// отримаємо координати атаки від користувача 
void getAtackCoordinates(int& x, int& y)
{
        while(1)
        {
                cout<<"Enter the coordinates for attack: ";
                cin>>x>>y;
                if(x<1 || x>10 || y<1 || y>10)
                {
                        cout<<"Error! Please retry..";
                        continue;
                }
                else
                        break;
        }
}
// отримаємо координати атаки від компЮтера 
void getAtackCompCoordinates(int& x, int& y, char CompSecond[N][N])
{
	do{

		x=1+rand() % 10; 
		y=1+rand() % 10;
	}
	while (CompSecond[x][y]!=' ');
}