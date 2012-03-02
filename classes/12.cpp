// 12.cpp : Defines the entry point for the console application.
//
///������ ��������� ������� ��������� m*m. ������� ������ � ���� Matr	.
//������ ��������� ������� ������� ����� ������� �� m-����� ������,����� ���������� ����� � ������� �� mod m 
//�� ����� �������� ���������� ������� �������. 
//��������� ������ � ������� ������� ����������. ���������� ������� � ��� �����.
#include "stdafx.h"
#include<iostream>
using namespace std;
typedef unsigned short int ui;
const ui K=4;		//��������� �������
////////////////////////////////////////////////////////
class Matr{
	int **m;
	ui N;				//����� �������
public:
	Matr ( );			//����������� ��� ���������
	Matr ( ui n );			//����������� � �����������
	Matr ( const Matr& mas );		//����������� ���������
	~Matr ( );
	void Create( ui n );			//��������� �����
	void Clear();					//��������� �����
	ui GetSize( ) const;			//������ ����� �������
	void PrintM( ) const;				//�������� �������
	void SetEl ( ui i, ui j, int value );		//�������� ������� ����������
	int ScalarMult ( ) const;		//������� ��������� ��������� ������� ������� ����� ������� �� m-����� ������,
										//����� ���������� ����� � ������� �� mod m 
										//�� ����� �������� ���������� ������� �������. 
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
			mas.SetEl ( i, j, (2*i+3*j) );			//���������� ������� ���������� 2i+3j
	cout<<"\nYour matrix: \n";
	mas.PrintM();
	cout<<"\nScalar multiplication : "<<mas.ScalarMult( )<<endl;		//���� ���������� �������
	system("pause");
	return 0;
}

////////////////////////////////////////////////////////
Matr::Matr( ) {					//����������� ��� ���������					
	Create( K );				//�������������� ����������� ����� �� �����������
}

////////////////////////////////////////////////////////
Matr::Matr ( ui size ) {			//����������� � �����������
	Create( size );
}

////////////////////////////////////////////////////////
Matr::Matr ( const Matr& mas ) {		//���������� ���������
	Create(mas.N);
	for( ui i=0; i<N; i++ )	     
		for( ui j=0; j<N; j++ )	
			m[i][j]=mas.m[i][j];				// ����� �������� ��������
}
/////////////////////////////////////////////////////
void Matr::Create( ui size ){
	N=size;
	m=new int*[N];					//������ ���� 
	if(m==NULL) { 
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
	for( ui i=0; i<N; i++ )	{		//� �� �� 
		m[i]=new int[N];			//������� N*N
		if(m[i]==NULL) { 
			cout<<"Error!Cant allocate memory";  exit(1); }
	}
}

////////////////////////////////////////////////////////
Matr::~Matr ( ) {				//����������
	Clear();				
}
//////////////////////////////////////////////////////
void Matr::Clear(){
	for( ui i=0; i<N; i++ )			//������� �������
		delete[] m[i];				//�� ������� N*N
	delete []m;						//������
	N=0;
	m=NULL;
}

////////////////////////////////////////////////////////
int Matr::ScalarMult( ) const {			//��������� ��������� ������� ������� ����� ������� 
										//�� m-����� ������,����� ���������� ����� � ������� �� mod m 
										//�� ����� �������� ���������� ������� �������
	int res=0, d;
	cout<<"\nResidue of division: \n";
	for ( ui i=0; i<N; i++ ){			//������ �� ������ �������� ���������� ������� �� ��������� �������
		d=m[i][N-1] % N;
		res+= m[0][i]*d;
		cout<<d<<" ";
	}
	return res;
}

////////////////////////////////////////////////////////

void Matr::SetEl ( ui i, ui j, int value ) {			//���������� �������� value
	if ( i>=0 || i<N || j>=0 || j<N )
		*(*(m+i)+j) = value;								//�� ������� (i,j)
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