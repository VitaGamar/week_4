// 19.cpp : Defines the entry point for the console application.
//
//19.	Заданий вектор ГР розмірності п, компонентами якого є записи, що містять анкети
//службовців деякого закладу. В кожній анкеті вказується прізвище службовця, 
//його стать, дата народження у вигляді: число, місяць, рік. Визначити процедуру пошуку
//а)	найстаршого з чоловіків групи ГР;
//б)	людей з групи ГР, прізвища яких починаються з заданої літери.

#include "stdafx.h"
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
typedef unsigned short int ui;
const ui K=4;
const enum sex {w, m};  //для позначення статы
struct date{
	ui day, month, year;		//містить інформацію про дату народження
};
struct info{				//містить інформацію про службовця
	char name[20];
	sex s;
	date birth; 
};
class Form{
	info *inf;
	ui size;
public:
	Form();
	Form( ui n );					//конструктор з параметром
	Form( const Form& v );			//конструктор копіювання
	~Form();
	void Create( ui n );			//виділення памяті 
	void Clear();					//звільнення памяті
	ui GetSize( ) const;			//отримує кількість службовців
	void PrintForm( ) const;				//виводить інформацію з анкети
	void SetInfo ( ui i, info& value );				//запис структури з інф. про службовця в анкету
	bool InsertInfo( info& value);				//введення інф про службовця
	void Sort( );							//сортування
	void Swap(info *p, ui j );				//обмін елементів
	info* GetElem( ui i );				//повертає структуру з інф про і-го службовця
	void FirstLetter( char ch );		//знаходить службовця з першою літерою ch у прізвищі
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
		while(f.InsertInfo(information)==0)			//ввід інформації про службовця
			cout<<"Wrong input!Try again.";			//поки не помилка вводу
		f.SetInfo(i, information);					//запис отриманої інформації в анкету
	}
	f.Sort();
	f.PrintForm();
	for(ui i=0; i<f.GetSize();i++)
		if(((f.GetElem(i))->s)==m) {
			cout<<"The oldest man: "<<f.GetElem(i)->name;		//вивід найстаршого чоловіка-службовця
			is=true;
			break;
		}
	if(is==false) cout<<"There isnt any man";			//якщо немає чоловіків
	char ch;
	cout<<"\nEnter a symbol: ";
	cin>>ch;
	f.FirstLetter(ch);			//пошук службовця з першою літерою в прізвищі ch
	system("pause");
	return 0;
}
//////////////////////////////////////////////////////
void Form::Create( ui n ){			//виділення необх кількості памяті
	size=n;
	inf=new info[size];					
	if(inf==NULL) {					//якщо помилка виділення
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
}
////////////////////////////////////////////////////
Form::Form(){			//якщо не вказана кількість службовців створюється К службовців за замовчуванням
	Create( K );
}
////////////////////////////////////////////////////
Form::Form( ui n ){    //конструктор з параметрами
	Create( n );
}
////////////////////////////////////////////////////
Form::Form( const Form& v ) {		//конструктор копіювання
	Create(v.size);					//виділення необх кількості памяті
	for(ui i=0; i<size; i++){
		inf[i]=v.inf[i];			//копіювання вмісту
	}
}

////////////////////////////////////////////////////////
Form::~Form ( ) {				//деструктор
	Clear();				
}
//////////////////////////////////////////////////////
void Form::Clear(){		//звільнення виділеної памяті
	delete [] inf;						
	inf=NULL;
}

////////////////////////////////////////////////////////
void Form::PrintForm( ) const{			//вивід інформації з анкети
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
ui Form::GetSize( ) const{			//повертає кількість службовців
	return size;
}
////////////////////////////////////////////////////////////
void Form::SetInfo ( ui i, info& value ){	//занесення інформації про службовця в анкету на і-ту позицію
	if ( i>=0 || i<size )			
		inf[i]=value;
	else {									//якщо невірна позиція
		cout<<"Error!"; 
		return ;
	}
}
///////////////////////////////////////////////////////////
bool Form::InsertInfo( info& value){		//ввід інфрмації про службовця
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
	if(d<0 || d>31 || mon<0 || mon>12 || y<0)			//якщо невірний формат дати
		return 0;
	else{
		value.birth.day=d;
		value.birth.month=mon;
		value.birth.year=y;
	}
	
	return 1;
}
////////////////////////////////////////////////////////////////
void Form::Sort( ){				//сортування
info y;
char ds1[10], ds2[10], ms1[20], ms2[20] ;
for(ui i=size-1; i>0; i--)
	for(ui j=0; j<i; j++){
		
		itoa((inf+j)->birth.month, ms1, 10);			//перетворює місяць в символьний тип
		itoa((inf+j+1)->birth.month, ms2, 10);

		itoa((inf+j)->birth.day, ds1, 10);				//перетворює день в символьний тип
		itoa((inf+j+1)->birth.day, ds2, 10);

		if((inf[j].birth.year) > (inf[j+1].birth.year))       
				Swap( inf, j);

		if((inf[j].birth.year) == (inf[j+1].birth.year))			//якщо роки однакові
			if(strcmp(strcat(ds1, ms1),strcat(ds2, ms2))>0)			//обєднання дня і місяця і порівняння їх на рівність
				Swap(inf, j);		
	}
}
//////////////////////////////////////////////////////////////////
void Form::Swap( info *p, ui j){			//міняє місцями 2елементи
	info y;	
	y=*(p+j);
	*(p+j)=*(p+j+1);
	*(p+j+1)=y;
}

//////////////////////////////////////////////////////////////////
void Form::FirstLetter( char ch ){			//знаходження службовця з першою літерою ch в прізвищі
	bool is=false;
	cout<<"\n Last names with first letter "<<ch<<": ";
	for(ui i=0; i<size; i++)
		if( (inf+i)->name[0]==ch) {
			cout<<(inf+i)->name<<" ";
			is=true;				//знайшли
		}
	if(is==false) cout<<"There isnt person with such last name.\n";			//якщо немає такого службовця
}
///////////////////////////////////////////////////////////////////
info* Form::GetElem( ui i ) {		//повертає інформацію про конкретного користувача
	if ( i>=0 || i<size ) return inf+i;  
	else return 0;
}
