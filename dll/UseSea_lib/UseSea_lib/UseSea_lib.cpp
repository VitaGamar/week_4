// UseSea_lib.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include <iostream>
#include <Windows.h>
#include "UseSea_lib.h"
using namespace std;

HMODULE hLib;

// Dll function pointers //////////////////////////////////////////////////////////////////////////
PrintFields					PrintF;
setShips					SetSh;
RunGamePlayer				RunGameP;
RunGameComp					RunGameC;

HMODULE InitPointers()
{
	hLib = LoadLibrary(TEXT("Sea_lib.dll"));
	if(!hLib)
		return NULL;
	PrintF = (PrintFields)GetProcAddress(hLib, "PrintFields");
	SetSh = (setShips)GetProcAddress(hLib, "setShips");
	RunGameP = (RunGamePlayer)GetProcAddress(hLib, "RunGamePlayer");
	RunGameC = (RunGameComp)GetProcAddress(hLib, "RunGameComp");
return hLib;
}


void Create (Field& player, Field& comp){      
   for(int i=0; i<N; i++)
       for(int j=0; j<N; j++)
	   {
		   player.FirstField[i][j]=' ';				//заповнення матриці пробілами
  		   player.SecondField[i][j]=' ';
		   comp.FirstField[i][j]=' ';      
  		   comp.SecondField[i][j]=' ';
		   player.FlotLife=20;
		   comp.FlotLife=20;
		   player.win=false;
		   comp.win=false;
	   }
}


int _tmain()
{
	InitPointers();
	Field player;
	Field comp;
	Create(player, comp);
	SetSh(player, comp);
	while (player.win!=true || comp.win!=true)
	{
		 RunGameP(player, comp);
		 RunGameC(player, comp);
	}
	PrintF(player);
	if(player.win==true)	 
         cout<<"Congratulations! Уou won!"<<endl;
	else
         cout<<"Sorry! You lost"<<endl;
    _getch();
	system("pause");
	FreeLibrary(hLib);
	return 0;
}

