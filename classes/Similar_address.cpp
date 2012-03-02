// Similar_address.cpp : Defines the entry point for the console application.
//������ ������ � ������ �, ������������ ����� � ������� ��� ��������� ������ ���. 
//���������� ��� ������� �������� ������ ���� �������, ����� ���� ��������; 
//������ �������� � ������: ������, �������, ��������. ��������� ��������� ������ ���� ����-���� ������ �� ������ �, 
//�� �������� � ����� ����� �� ��������� �������.

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
const int N=4;						//������� ������ ��� ������� ������������ ��� ���������
struct address{						// ����� ������ ��������
	string street, building, flat; // �������� ������ ������� 22�, �� �������� ���� ��������(�-�, 1� � 1�)
};
struct inform{					//���������� ��� ��������� ����
	string surname, town;		
	address addr;
};
class Citizens{			
	inform *C;					// ����� �������� � ����������� ��� ���������
	unsigned int size;			// ����� ������
public:
	Citizens();								// ����������� ��� ���������
	Citizens(unsigned int n);				//����������� � �����������, n-������� �������� � �������; 
	~Citizens();							// � ���������� ��������� ��
	void Create(unsigned int n);		//�������� ��
	void Clear();
	Citizens(const Citizens&);						//����������� ���������
	unsigned int Getsize() const;					// ������ �� ����������� ���� size
	void Setel(unsigned int i, inform& ch);	    	//��������� ��������� � ������� �
	inform* Citizens::Getelem(unsigned int i) const;	//�������� �������� �� �-��� ������� � ����� �
	void InsertInf(inform& a);		//�������� ���������� � ���������, �������� � ���������  ����������� ��� ��� ��������� ����
	void Print() const;				// ������� �������
	void FindCitiz(unsigned int &k,unsigned int& p);	//����� ������, �������� � ����� ����� �� ��������� �������

};
/////////////////////////////////////////////////////////////
void Citizens::Create(unsigned int n)
{
	size=n;
	C=new inform[size];
	if (C==NULL)		//���� ���� ����� ���;��
	{
		cout<<" Error! Can't allocate! not enough memory. ";	//����������� ��� �� �����������
		exit(1);												// �� ������� ��������� ��������
	}
}
/////////////////////////////////////////////////////////////
Citizens::Citizens()
{
	Create(N);
}
////////////////////////////////////////////////////////////
Citizens::Citizens(const Citizens& a)
{
	Create(a.size);								//�������� �������� � ���;�
	for( unsigned int i=0; i<size; i++ )      
			C[i]=a.C[i];						 // ���� ����������� �������
}
//////////////////////////////////////////////////////////////
Citizens::Citizens(unsigned int n)
{
	Create(n);
}
//////////////////////////////////////////////////////////////
void Citizens::Clear()
{
	delete[] C;		//��������� ��
	C = NULL;		//��������� ���������
}
////////////////////////////////////////////////////////////////
Citizens::~Citizens()
{
	Clear();
}
/////////////////////////////////////////////////////////////
void Citizens::Setel(unsigned int i, inform& ch){
	if(i<size||i>=0)		//���� ������ �� �������� �� ��� ������
		C[i]=ch;			//�������� � �����
	else 
		cout<<"Error!";		
}
/////////////////////////////////////////////////////////////
inform* Citizens::Getelem(unsigned int i) const //������� �������� �� �-��� ������� � �����
{
	if(i<size||i>=0)		
		return C+i;
	else return NULL;
}
/////////////////////////////////////////////////////////////
void Citizens::InsertInf(inform& a)		//��� ���������� � ���������
{
	cout<<"\t Enter infrmation about residents of the city:\n";
	cout<<" Surname: "; 
	cin>>a.surname;
	cout<<" town: "; 
	cin>>a.town;
	cout<<" street: "; 
	cin>>a.addr.street;
	cout<<" building: "; 
	cin>>a.addr.building;
	cout<<" flat: "; 
	cin>>a.addr.flat;
}
//////////////////////////////////////////////////////////////
void Citizens::Print() const
{
	cout<<"\n\n\t Infrmation about residents of the city:\n";
	cout<<"    Surname     town     street     building    flat:\n";
	for(unsigned int i=0; i<size; i++)
		cout<<setw(10)<<C[i].surname<<setw(10)<<C[i].town<<setw(10)<<C[i].addr.street<<setw(10)<<C[i].addr.building<<setw(10)<<C[i].addr.flat<<endl;
}
////////////////////////////////////////////////////////////////
unsigned int Citizens::Getsize() const
{
	return size;
}
/////////////////////////////////////////////////////////////////
void Citizens::FindCitiz(unsigned int &k,unsigned int& p) // � � � - ����� �������� � ����� �
{

string s=" ";
string s1=" ";
for(unsigned int i=0,j=i+1; i<size-1; i++,j++)
	{
		s.insert(0,C[i].addr.building);			//� s- ����� ������ �-���� ������
		s.insert(s.size(),C[i].addr.street);
		s.insert(s.size(),C[i].addr.flat);
		s1.insert(0,C[j].addr.building);		//� s1- ����� ������ j-���� ������
		s1.insert(s1.size(),C[j].addr.street);
		s1.insert(s1.size(),C[j].addr.flat);
		if(s==s1)								//���� ������ ������ ���������
			if(C[i].town!=C[j].town)			//��� ������ ���� � ����� �����
			{
				k=i;							// �� ������� �� �� ������
				p=j;							
				return;
			}
		s=" ";
		s1=" ";
	}
 k=0; p=0;									//���� � ����� ������ ���� - �� ������ �������� � ������
}

/////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n;							//����� ������
	unsigned int i, j;						//����� �������� � �����
	cout<<" Enter number of citizens: ";
	cin>>n;
	Citizens Cit(n);
	inform inf;
	for(unsigned int i=0; i<Cit.Getsize(); i++)		// ���������� �������
	{
			Cit.InsertInf(inf);					//�������� ���������� � ���������
			Cit.Setel(i,inf);					//�� ���������� �� � �����
	}
	Cit.Print();
	Cit.FindCitiz(i,j);
	cout<<" \n\tResidents who live in different cities at the same address:\n ";
	if ((i==0)&&(j==0))						// ����� ������ ����
		cout<<"\t Such citizens doesn't exist.";
	else									//���� � ���� �������
		{
			if(Cit.Getelem(i)==NULL || Cit.Getelem(j)==NULL)		//�������� ���������� ��� ���
				cout<<"Wrong index!";
			else
			{
				inf=*Cit.Getelem(i);
				cout<<inf.surname<<"  ";
				inf=*Cit.Getelem(j);
				cout<<inf.surname<<endl;
			}
		}
	system("pause");
	return 0;
}
