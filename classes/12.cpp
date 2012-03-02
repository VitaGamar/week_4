// 12.cpp : Defines the entry point for the console application.
//
///Задана квадратна матриця розмірності m*m. Матрицю задати в класі Matr	.
//Знайти скалярний добуток першого рядка матриці на m-мірний вектор,кожна координата якого є залишок по mod m 
//від різних елементів останнього стовпця матриці. 
//Розмірність задати в головній програмі константою. Елементами матриці є цілі числа.
#include "stdafx.h"
#include<iostream>
using namespace std;
typedef unsigned short int ui;
const ui K=4;		//розмірність матриці
////////////////////////////////////////////////////////
class Matr{
	int **m;
	ui N;				//розмір матриці
public:
	Matr ( );			//конструктор без параметрів
	Matr ( ui n );			//конструктор з параметрами
	Matr ( const Matr& mas );		//конструктор копіювання
	~Matr ( );
	void Create( ui n );			//створення обєкту
	void Clear();					//звільнення памяті
	ui GetSize( ) const;			//отримує розмір матриці
	void PrintM( ) const;				//виводить матрицю
	void SetEl ( ui i, ui j, int value );		//заповнює матрицю значеннями
	int ScalarMult ( ) const;		//функція знаходить скалярний добуток першого рядка матриці на m-мірний вектор,
										//кожна координата якого є залишок по mod m 
										//від різних елементів останнього стовпця матриці. 
};
////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	ui size;
	cout<<"Enter matrix size: ";
	cin>>size;
	Matr mas(size);
	ui ln=mas.GetSize();
	for ( ui i=0; i<ln; i++ )
		for ( ui j=0; j<ln; j++ )
			mas.SetEl ( i, j, (2*i+3*j) );			//заповнення матриці значеннями 2i+3j
	cout<<"\nYour matrix: \n";
	mas.PrintM();
	cout<<"\nScalar multiplication : "<<mas.ScalarMult( )<<endl;		//вивід скалярного добутку
	system("pause");
	return 0;
}

////////////////////////////////////////////////////////
Matr::Matr( ) {					//конструктор без параметрів					
	Create( K );				//встановлюється константний розмір по замовчуванні
}

////////////////////////////////////////////////////////
Matr::Matr ( ui size ) {			//конструктор з параметрами
	Create( size );
}

////////////////////////////////////////////////////////
Matr::Matr ( const Matr& mas ) {		//коструктор копіювання
	Create(mas.N);
	for( ui i=0; i<N; i++ )	     
		for( ui j=0; j<N; j++ )	
			m[i][j]=mas.m[i][j];				// копіює значення елементів
}
/////////////////////////////////////////////////////
void Matr::Create( ui size ){
	N=size;
	m=new int*[N];					//виділяє місце 
	if(m==NULL) { 
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
	for( ui i=0; i<N; i++ )	{		//в ДП під 
		m[i]=new int[N];			//матрицю N*N
		if(m[i]==NULL) { 
			cout<<"Error!Cant allocate memory";  exit(1); }
	}
}

////////////////////////////////////////////////////////
Matr::~Matr ( ) {				//деструктор
	Clear();				
}
//////////////////////////////////////////////////////
void Matr::Clear(){
	for( ui i=0; i<N; i++ )			//звільняє виділену
		delete[] m[i];				//під матрицю N*N
	delete []m;						//память
	N=0;
	m=NULL;
}

////////////////////////////////////////////////////////
int Matr::ScalarMult( ) const {			//знаходить скалярний добуток першого рядка матриці 
										//на m-мірний вектор,кожна координата якого є залишок по mod m 
										//від різних елементів останнього стовпця матриці
	int res=0, d;
	cout<<"\nResidue of division: \n";
	for ( ui i=0; i<N; i++ ){			//остача від ділення елементів останнього стовпця на розмірність матриці
		d=m[i][N-1] % N;
		res+= m[0][i]*d;
		cout<<d<<" ";
	}
	return res;
}

////////////////////////////////////////////////////////

void Matr::SetEl ( ui i, ui j, int value ) {			//встановлює значення value
	if ( i>=0 || i<N || j>=0 || j<N )
		*(*(m+i)+j) = value;								//на позицію (i,j)
	else cout<<"Error!";
}
////////////////////////////////////////////////////////
void Matr::PrintM( ) const{
	for( ui i=0; i<N; i++ ){
		for( ui j=0; j<N; j++ )
			cout<<m[i][j]<<" ";
		cout<<endl;
	}
}
///////////////////////////////////////////////////////////
ui Matr::GetSize( ) const{
	return N;
}