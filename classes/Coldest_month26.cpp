// Coldest_month26.cpp : Defines the entry point for the console application.
//26.	������ ����� ������� �, �������� ��� ��������� �������������� ����������� �� ������ x � ����� �.
//������� ���������, �� ������� ���� ����� � �� ����� ������ ����� ���������� ������� � ������������.

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#define ui unsigned int
using namespace std;
const ui nmon=12;		
const ui nisl=6;
const ui MAX=20;
char month[nmon][MAX]={"January", "February" , "March" , "April" , "May", "June", "July", "August", "September", "October", "November", "December"};// ������ ��� ������
char island[nisl][MAX]={"Mozambique ", "Kangaroo   ", "BoraBora   ", "Cuba       ", "Kalimantan ", "Madagascar "};			// ������� �������
class Taverage{		
	double **T;						// ������� ��������������� ����������
public:
	Taverage() ;					// ����������� ��� ���������
	~Taverage();					// � ���������� ��������� ��
	void Create();					//��������� � ��
	void Clear();					
	Taverage(const Taverage&);				// ����������� ���������
	void Setel(ui i, ui j, double ch);	//����� �������� � �������
	void minim(ui&, ui&);				// ����������� ����������
	void showel() const;			// ���� ������
};

////////////////////////////////////////////////////////////////////////////

int _tmain(int argc, _TCHAR* argv[])
{
	Taverage tav;
	ui mon, isl;
	for(unsigned int i=0; i<nisl; i++)
		for(unsigned int j=0; j<nmon; j++)
			tav.Setel(i,j,2.5+j*1.5+i);
	tav.showel();
	tav.minim(mon,isl);
	cout<<" Minimum was in  ";
	cout<<month[mon]<<"  in island  "<<island[isl]<<endl;
	system("pause");
	return 0;
}

////////////////////////////////////////////////////////////

void Taverage::Create()
{
	T=new double*[nisl];
	if (T==NULL) {
		cout<<" Error! Can't allocate! not enough memory. ";
		exit(1);
	}
	for(unsigned int i=0; i<nisl; i++)
	{
		T[i]=new double[nmon];
		if (T[i]==NULL) 
		{
		cout<<" Error! Can't allocate! not enough memory. ";
		exit(1);
	    }
	}
}
///////////////////////////////////////////////////////////////
Taverage::Taverage() {
	Create();
}
//////////////////////////////////////////////////////////////
Taverage::Taverage(const Taverage& a)
{
	Create();
	for( ui i=0; i<nisl; i++ )      
		 for( ui j=0; j<nmon; j++ ) 
			 T[i][j]=a.T[i][j];  // ����� �������� ��������
}
////////////////////////////////////////////////////////////////////
void Taverage::Clear()
{
	for(ui i=0; i<nisl; i++)
		delete[] T[i];
	delete[] T;
	T=NULL;
}
///////////////////////////////////////////////////////////////////
Taverage::~Taverage()
{
	Clear();
}
////////////////////////////////////////////////////////////////////
void Taverage::Setel(ui i,ui j, double ch){
	if(i<nisl||i>=0||j<nmon||j>=0)
		T[i][j]=ch;
	else 
		cout<<"Error!";
}
////////////////////////////////////////////////////////////////////
void Taverage::showel() const{
cout<<"\n\t       Jan   Feb  Mar  Apr  May  June July Aug Sept  Oct Nov   Dec\n"<<endl;
 for(ui i=0; i<nisl; i++){
  	 cout<<island[i]<<"   ";
	 for(ui j=0; j<nmon; j++) 
	 {
		setw(ios::left);	
		 cout<<setw(5)<<T[i][j];
	 }
     cout<<endl;
 }
}
///////////////////////////////////////////////////////////////////////////
void Taverage::minim(ui& mon, ui& is)
{
	double min=T[0][0];
	ui nm=0, ni=0;
	for(ui i=0; i<nisl; i++)
		for(ui j=0; j<nmon; j++)
			if(T[i][j]<min)
			{
				min=T[i][j];
				nm=j;			//�����;������� ����� ������� 
				ni=i;			//�� ����� �����
			}
	mon=nm;			
	is=ni;
}
