// Sea_lib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Sea_lib.h"
#include<iomanip>
#include <cstdlib>
#include <conio.h>
extern "C"
{

// ���� ���� ������
void PrintFields(Field& player)				
{
        system("cls");					//�������� �����
        cout<<"  ";      
        for (int i=1; i<=10; i++)		//����������� ������� ����� ��������� ��� FirstField
                cout<<i<<" ";
        cout<<"  ";
        for(int i=1; i<=10; i++)		//����������� ������� ����� ��������� ��� SecondField
                cout<<i<<" ";                        
        cout<<endl;       
        for(int i=1; i<=10; i++)		//����������� ����� ����� ��������� � ��� ����
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
 //��� ������
void RunGamePlayer(Field& player, Field& comp)
{
			 int x,y,x1,y1,x2,y2;				//��� ��� �����(x,y) � ������������/�������� �������(�1,�1,�2,�2)
                while(1)						//��� ������
                {
                        PrintFields(player);										//����������� ����
                        getAtackCoordinates(x,y);									//�������� ���������� ��� �����
                         if ( player.SecondField[y][x] == 'x' || player.SecondField[y][x]=='o')	// �� ���� ������� ���������
                        {												
                                cout<<"Stupid move! retry";
                                _getch();
                                continue;
                        }
                        else
                        {
                                if ( comp.FirstField[y][x] == ' ')
                                {											//���� ����
                                        player.SecondField[y][x] = 'o';
                                        PrintFields(player);
                                        _getch();
                                        return;
                                }
                                else										//���� �����
                                {
                                        player.SecondField [y][x] = 'x';			//��������� ����������� � ���� �� ������� ���
                                        comp.FirstField [y][x] = 'x';		//��������� ����������� � ���� �� ������� ���, � ���������
                                        if ( ShipTest(x, y, comp.FirstField) )//���� �������� ���� �������
                                        {
                                                getDeletedShipCoordinates(x,y,x1,y1,x2,y2, comp.FirstField);//�������� ����������
                                                DeleteShip(x1,y1,x2,y2, player.SecondField);			//��������� �������� �������� �� ������� ����
                                        }
 										comp.FlotLife--;							//�������� �� ���� ������
								}
                                if(comp.FlotLife>0 ? false : true)		//����� ���� �������
                                {
                                        player.win=true;				// ���! �� �������!
                                        PrintFields(player);
                                        _getch(); 
										return;
                                }                                                       
                        }
                }
}

//��� ����;�����, 䳿 ��������
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


//�������� �������� ���������(�� ���� ������ �� �� �������)
bool ShipFieldTest(const int& x1, const int& y1, const int& x2, const int& y2, char field[N][N])	
{
		for(int i=y1-1; i<=y2+1; i++)				//�������� �� �� ��������� ������������ ����� ������� ��������
               for(int j=x1-1; j<=x2+1; j++)
                     if(field[i][j]!=' ')		
                            return true;			//���, �������
        return false;
}

//��������� ������� ������ ������� size 
void setFlotShip(int size, char First[N][N])
{
        int x1, y1, x2, y2;      
        while(1)
        {
             cout<<"Enter coordinates(2points) of you ship: ";
             cin>>x1>>y1>>x2>>y2;	 //	�������� �����(���� ���������� �������� �� ��� ���� �  ���� ������� �������)
             if((x1!=x2 && y1!=y2) || (x1<1)  || (x2>10)  || (y1<1)  || (y2>10) || (ShipFieldTest(x1,y1,x2,y2,First)))
               {
					  cout<<"Error! You can't put you ship here. Please, retry."<<endl;
					  continue;		// ������� ��������
			   }
              else
                      if(x2-x1!=size-1 && y2-y1!=size-1)				//���� �������� �� ���� ������
                            {cout<<"Wrong number of deck!"<<endl; continue;}	//���������� ���	
                      else
                           for(int i=y1; i<=y2; i++)		
                                for(int j=x1; j<=x2; j++)		
                                     First[i][j]='*';			//���� �� ����� ���������� - ����� ������� ��������
               return;
        }
}
//��������� ������� ��������� ������� size 
void setFlotShipComp(int size, char FirstComp[N][N])
{
        int x1,y1,x2,y2;
        srand(time(0));
        int POSITION;  
        while(1)
        {
                POSITION=1+rand() % 2;					//��������� ������� �������               
                if(POSITION==1)							//���� �������� ��������� �����������
                {
                        x1=x2=1+rand() % 10;			//�� ��� �1=�2
                        y1=1+rand() % 10;				
                        if ( y1+size-1 > 10 )			//���� ����� ���������� ���� �������� �� ��� ������
                                continue;				//��������� ���� ��������
                        else							//������ ����� ��������� �������� �������� ����� + ������� ����� 
                                y2 = y1+size-1;
                } 
                else									//���� �������� ��������� �������������
                        {
                                y1 = y2=1+rand() % 10;
                                x1 = 1+rand() % 10;
                                if ( x1+size-1>10 )
                                        continue;
                                else
                                        x2 = x1+size-1;
                        }                 
                if ( ShipFieldTest(x1,y1,x2,y2,FirstComp) )			//���� ����� � ��������
                        continue;						//��������� ���� �������� 
                else									//������ ��������� �������� �� ���
                {
                        for ( int i=y1; i<=y2; i++ )
                                for ( int j=x1; j<=x2; j++ )
                                        FirstComp[i][j]='*';
                        return;
                }
        }
}
// ���� �� ������ ������� ��������� - �� �������� �������. �������� ������� ����� 'o'
void DeleteShip(const int& x1, const int& y1, const int& x2, const int& y2, char field[N][N])
{
        if(x1==x2)									//���� �������� ��������� �����������
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

//�������� �� ������ � ������������ �, � - ������� �� ������
bool ShipTest(const int& x, const int& y, char field[N][N])
{
        for(int i=y; field[i][x]!=' ' && field[i][x]!='o'; i++)		//�������� ������� � ���� ������� ���� ����!=���������
                if(field[i][x]=='*')								//������ ������� � ��������� false ���� ���������� ����� ������
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
        return true;		// ���� ���� �������� ��� ������� - ��������� true
}

//� �1, �1, �2, �2 - ������ �������; �,� �������� �1, �1, �2, �2
void getDeletedShipCoordinates(const int& x, const int& y, int& x1, int& y1, int& x2, int& y2, char first[N][N])
{
        if(first[y+1][x]=='*' || first[y+1][x]=='x' || first[y-1][x]=='*' || first[y-1][x]=='x')//���� �������� ��������� �����������
        {
                x1=x2=x;															//�������� �1 � �2 �������� ���������� '�'
                for(int i=y; first[i][x]!=' ' && first[i][x]!='o'; y1=i, i--);		//�������� ���������� �1 � �2
                for(int i=y; first[i][x]!=' ' && first[i][x]!='o'; y2=i, i++);
        }      
        else																		//���� �������� ��������� �� �����������
        {
                y1=y2=y;															//�������� �1 � �2 �������� ���������� '�'
                for(int j=x; first[y][j]!=' ' && first[y][j]!='o'; x1=j, j--);		//�������� ���������� �1 � �2
                for(int j=x; first[y][j]!=' ' && first[y][j]!='o'; x2=j, j++);
        }
}
// �������� ���������� ����� �� ����������� 
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
// �������� ���������� ����� �� ��������� 
void getAtackCompCoordinates(int& x, int& y, char CompSecond[N][N])
{
	do{

		x=1+rand() % 10; 
		y=1+rand() % 10;
	}
	while (CompSecond[x][y]!=' ');
}