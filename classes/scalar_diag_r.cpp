// scalar_diag_r.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
const int N=4;
class Matr{			
	int **m;
	unsigned int size;
public:
	Matr();								// ����������� ��� ���������
	Matr(unsigned int n);				//����������� � �����������, n-������� �������� � �������; �������� ��
	~Matr();							// � ���������� ��������� ��
	void Create(unsigned int nn);
	void Clear();
	Matr(const Matr&);						// ����������� ���������
	unsigned int Getsize();					//�������� ����� �������
	void Setel(unsigned int i,unsigned int j, int ch);	    	//����� �������� ������� � ������� [i][j]
	void ShowMatr() const;				// ������� �������
	int Scalar();						//���������� ���������� ������� ������� ����� ������� � ������� �������
};

void Matr::Create(unsigned int nn)
{
	size=nn;				
	m=new int*[size];
	if (m==NULL) {							// ���� ����� ���;��
		cout<<" Error! Can't allocate! not enough memory. ";	// ����������� ����������
		exit(1);							// �������� ����� � ��������
	}
	for(unsigned int i=0; i<size; i++)
	{
		m[i]=new int[size];
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
	Create(a.size);			// ��������� ����������� � ����� ����������
	for( unsigned int i=0; i<size; i++ )      
		 for(unsigned int j=0; j<size; j++ ) 
			m[i][j]=a.m[i][j];					 // ������� �������� ��������
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
void Matr::Setel(unsigned int i,unsigned int j, int ch){
	if(i<size||i>=0||j<size||j>=0)
		m[i][j]=ch;
	else 
		cout<<"Error!";
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
int Matr::Scalar()
{
	unsigned int sum=0;
	for(unsigned int j=0; j<N; j++)
		sum+=m[0][j]*m[j][j];
	return sum;
}
int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n;
	cout<<" Enter matrix size: ";
	cin>>n;
	Matr M(n);
	for(unsigned int i=0; i<M.Getsize(); i++)		// ���������� �������
		for(unsigned int j=0; j<M.Getsize(); j++)
			M.Setel(i,j,i+j*2);
	cout<<"\n\t Matrix:"<<endl;
	M.ShowMatr();
	cout<<endl;
	cout<<"Scalar multiplication: "<<M.Scalar();
	system("pause");
	return 0;
}


