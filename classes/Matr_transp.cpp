// Matr_transp.cpp : Defines the entry point for the console application.
//Задана квадратна матриця дійсних чисел m × m. Написати програму   транспонування цiєї матрицi 
//(помiняти рядки iз стовпцями). Матрицю задати  в класі Matr. Розмірність задати в головній програмі константою. 
#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
const int N=4;
class Matr{			
	float **m;
	unsigned int size;
public:
	Matr();								// конструктор без параметрів
	Matr(unsigned int n);				//конструктор з параметрами, n-кількість елементів в матриці; виділяємо ДП
	~Matr();							// в деструкторі звільняємо ДП
	void Create(unsigned int nn);
	void Clear();
	Matr(const Matr&);						// конструктор копіювання
	//float Getelem(unsigned int i,unsigned int j) const;				//зчитування елементів матриці з позиції [i][j]
	unsigned int Getsize();
	void Setel(unsigned int i,unsigned int j, float ch);	    	//запис елемента матриці в позицію [i][j]
	void Transp();						 //транспонування матриці
	void ShowMatr() const;				// роздрук матриці
};
/////////////////////////////////////////////////////////////
void Matr::Create(unsigned int nn)
{
	size=nn;
	m=new float*[size];
	if (m==NULL) {
		cout<<" Error! Can't allocate! not enough memory. ";
		exit(1);
	}
	for(unsigned int i=0; i<size; i++)
	{
		m[i]=new float[size];
		if (m[i]==NULL) 
		{
		cout<<" Error! Can't allocate! not enough memory. ";
		exit(1);
	    }
	}
}
/////////////////////////////////////////////////////////////
Matr::Matr()
{
	Create(N);
}
////////////////////////////////////////////////////////////
Matr::Matr(const Matr& a)
{
	Create(a.size);
	for( unsigned int i=0; i<size; i++ )      
		 for(unsigned int j=0; j<size; j++ ) 
			m[i][j]=a.m[i][j];		 // копіює значення елементів
}
//////////////////////////////////////////////////////////////
Matr::Matr(unsigned int n)
{
	Create(n);
}
//////////////////////////////////////////////////////////////
void Matr::Clear()
{
	for(unsigned int i=0; i<size; i++)
		delete[] m[i];
	delete[] m;
	m=NULL;
}
////////////////////////////////////////////////////////////////
Matr::~Matr()
{
	Clear();
}
/////////////////////////////////////////////////////////////
/*float Matr::Getelem(unsigned int i,unsigned int j) const
{
	if(i>size||i<0||j>size||j<0)
		return 0;
	else
		return m[i][j];
}*/
/////////////////////////////////////////////////////////////
void Matr::Setel(unsigned int i,unsigned int j, float ch){
	if(i<size||i>=0||j<size||j>=0)
		m[i][j]=ch;
	else 
		cout<<"Error!";
}
//////////////////////////////////////////////////////////////
void Matr::Transp()
{
	float aa;
	for(unsigned int i=0; i<size; i++)
		for(unsigned int j=0; j<size; j++)
			if(i<j)
			{
				aa=m[i][j];
				m[i][j]=m[j][i];
				m[j][i]=aa;
			}
}
//////////////////////////////////////////////////////////////
void Matr::ShowMatr() const
{
	for(unsigned int i=0; i<size; i++)
	{
		for(unsigned int j=0; j<size; j++)
			cout<<setw(5)<<m[i][j];
		cout<<endl;
	}
	cout<<endl;
}
////////////////////////////////////////////////////////////////
unsigned int Matr::Getsize()
{
	return size;
}
/////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n;
	cout<<" Enter matrix size: ";
	cin>>n;
	Matr M1(n);
	for(unsigned int i=0; i<M1.Getsize(); i++)		// заповнюємо матрицю
		for(unsigned int j=0; j<M1.Getsize(); j++)
			M1.Setel(i,j,i+j*2);
	cout<<"\n\t Matrix:"<<endl;
	M1.ShowMatr();
	cout<<endl;
	cout<<"\tTransposed matrix: \n";
	M1.Transp();
	M1.ShowMatr();
	system("pause");
	return 0;
}

