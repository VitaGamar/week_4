// 19.cpp : Defines the entry point for the console application.
//
//19.	������� ������ �� ��������� �, ������������ ����� � ������, �� ������ ������
//���������� ������� �������. � ����� ����� ��������� ������� ���������, 
//���� �����, ���� ���������� � ������: �����, �����, ��. ��������� ��������� ������
//�)	����������� � ������� ����� ��;
//�)	����� � ����� ��, ������� ���� ����������� � ������ �����.

#include "stdafx.h"
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
typedef unsigned short int ui;
const ui K=4;
const enum sex {w, m};  //��� ���������� �����
struct date{
	ui day, month, year;		//������ ���������� ��� ���� ����������
};
struct info{				//������ ���������� ��� ���������
	char name[20];
	sex s;
	date birth; 
};
class Form{
	info *inf;
	ui size;
public:
	Form();
	Form( ui n );					//����������� � ����������
	Form( const Form& v );			//����������� ���������
	~Form();
	void Create( ui n );			//�������� ����� 
	void Clear();					//��������� �����
	ui GetSize( ) const;			//������ ������� ����������
	void PrintForm( ) const;				//�������� ���������� � ������
	void SetInfo ( ui i, info& value );				//����� ��������� � ���. ��� ��������� � ������
	bool InsertInfo( info& value);				//�������� ��� ��� ���������
	void Sort( );							//����������
	void Swap(info *p, ui j );				//���� ��������
	info* GetElem( ui i );				//������� ��������� � ��� ��� �-�� ���������
	void FirstLetter( char ch );		//��������� ��������� � ������ ������ ch � �������
};
int _tmain(int argc, _TCHAR* argv[])
{
	ui num;
	bool is=false;
	cout<<"\nEnter a number of employees: ";
	cin>>num;
	Form f(num);
	info information;
	for(ui i=0; i<f.GetSize(); i++){
		while(f.InsertInfo(information)==0)			//��� ���������� ��� ���������
			cout<<"Wrong input!Try again.";			//���� �� ������� �����
		f.SetInfo(i, information);					//����� �������� ���������� � ������
	}
	f.Sort();
	f.PrintForm();
	for(ui i=0; i<f.GetSize();i++)
		if(((f.GetElem(i))->s)==m) {
			cout<<"The oldest man: "<<f.GetElem(i)->name;		//���� ����������� �������-���������
			is=true;
			break;
		}
	if(is==false) cout<<"There isnt any man";			//���� ���� �������
	char ch;
	cout<<"\nEnter a symbol: ";
	cin>>ch;
	f.FirstLetter(ch);			//����� ��������� � ������ ������ � ������� ch
	system("pause");
	return 0;
}
//////////////////////////////////////////////////////
void Form::Create( ui n ){			//�������� ����� ������� �����
	size=n;
	inf=new info[size];					
	if(inf==NULL) {					//���� ������� ��������
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
}
////////////////////////////////////////////////////
Form::Form(){			//���� �� ������� ������� ���������� ����������� � ���������� �� �������������
	Create( K );
}
////////////////////////////////////////////////////
Form::Form( ui n ){    //����������� � �����������
	Create( n );
}
////////////////////////////////////////////////////
Form::Form( const Form& v ) {		//����������� ���������
	Create(v.size);					//�������� ����� ������� �����
	for(ui i=0; i<size; i++){
		inf[i]=v.inf[i];			//��������� �����
	}
}

////////////////////////////////////////////////////////
Form::~Form ( ) {				//����������
	Clear();				
}
//////////////////////////////////////////////////////
void Form::Clear(){		//��������� ������� �����
	delete [] inf;						
	inf=NULL;
}

////////////////////////////////////////////////////////
void Form::PrintForm( ) const{			//���� ���������� � ������
	cout<<"\tInformation about employee:\n";
	cout<<"\n Last Name    Sex   Date of birth( day/month/year )\n";
	for( ui i=0; i<size; i++ ){
		cout<<setw(8)<<inf[i].name<<setw(8);
		switch(inf[i].s){
			case m: cout<<setw(9)<<"man"; break;
			case w: cout<<setw(9)<<"woman"; break;
		}
		cout<<setw(20)<<inf[i].birth.day<<"/"<<inf[i].birth.month<<"/"<<inf[i].birth.year<<endl;
		cout<<endl;
	}
}
///////////////////////////////////////////////////////////
ui Form::GetSize( ) const{			//������� ������� ����������
	return size;
}
////////////////////////////////////////////////////////////
void Form::SetInfo ( ui i, info& value ){	//��������� ���������� ��� ��������� � ������ �� �-�� �������
	if ( i>=0 || i<size )			
		inf[i]=value;
	else {									//���� ������ �������
		cout<<"Error!"; 
		return ;
	}
}
///////////////////////////////////////////////////////////
bool Form::InsertInfo( info& value){		//��� ��������� ��� ���������
	char ch;
	ui d, mon, y;
	cout<<"\nEnter information about employee";
	cout<<"\n Last name:  ";
	cin>>value.name;
	cout<<"Sex (w/m):  ";
	cin>>ch;
	switch(ch){
		case 'w': value.s=w; break;
		case 'm': value.s=m; break;
		default: return 0;
	}
	cout<<"Date of birth ( Day Month Year) :  ";
	cin>>d>>mon>>y;
	if(d<0 || d>31 || mon<0 || mon>12 || y<0)			//���� ������� ������ ����
		return 0;
	else{
		value.birth.day=d;
		value.birth.month=mon;
		value.birth.year=y;
	}
	
	return 1;
}
////////////////////////////////////////////////////////////////
void Form::Sort( ){				//����������
info y;
char ds1[10], ds2[10], ms1[20], ms2[20] ;
for(ui i=size-1; i>0; i--)
	for(ui j=0; j<i; j++){
		
		itoa((inf+j)->birth.month, ms1, 10);			//���������� ����� � ���������� ���
		itoa((inf+j+1)->birth.month, ms2, 10);

		itoa((inf+j)->birth.day, ds1, 10);				//���������� ���� � ���������� ���
		itoa((inf+j+1)->birth.day, ds2, 10);

		if((inf[j].birth.year) > (inf[j+1].birth.year))       
				Swap( inf, j);

		if((inf[j].birth.year) == (inf[j+1].birth.year))			//���� ���� �������
			if(strcmp(strcat(ds1, ms1),strcat(ds2, ms2))>0)			//�������� ��� � ����� � ��������� �� �� ������
				Swap(inf, j);		
	}
}
//////////////////////////////////////////////////////////////////
void Form::Swap( info *p, ui j){			//���� ������ 2��������
	info y;	
	y=*(p+j);
	*(p+j)=*(p+j+1);
	*(p+j+1)=y;
}

//////////////////////////////////////////////////////////////////
void Form::FirstLetter( char ch ){			//����������� ��������� � ������ ������ ch � �������
	bool is=false;
	cout<<"\n Last names with first letter "<<ch<<": ";
	for(ui i=0; i<size; i++)
		if( (inf+i)->name[0]==ch) {
			cout<<(inf+i)->name<<" ";
			is=true;				//�������
		}
	if(is==false) cout<<"There isnt person with such last name.\n";			//���� ���� ������ ���������
}
///////////////////////////////////////////////////////////////////
info* Form::GetElem( ui i ) {		//������� ���������� ��� ����������� �����������
	if ( i>=0 || i<size ) return inf+i;  
	else return 0;
}
