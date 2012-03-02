// Similar_address.cpp : Defines the entry point for the console application.
//Задано вектор С розміру п, компонентами якого є відомості про мешканців деяких міст. 
//Інформація про кожного мешканця містить його прізвище, назву міста мешкання; 
//адреси мешкання у вигляді: вулиця, будинок, квартира. Визначити процедуру пошуку двох будь-яких жителів із списку С, 
//що мешкають в різних містах за однаковою адресою.

#include "stdafx.h"
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
const int N=4;						//кількість жителів при виклику конструктора без параметрів
struct address{						// повна адреса мешканця
	string street, building, flat; // можливий варіант будинку 22а, та блочного типу квартира(н-д, 1а і 1б)
};
struct inform{					//інформація про мешканців міста
	string surname, town;		
	address addr;
};
class Citizens{			
	inform *C;					// масив структур з інвормацією про мешканців
	unsigned int size;			// розмір масиву
public:
	Citizens();								// конструктор без параметрів
	Citizens(unsigned int n);				//конструктор з параметрами, n-кількість елементів в матриці; 
	~Citizens();							// в деструкторі звільняємо ДП
	void Create(unsigned int n);		//виділення ДП
	void Clear();
	Citizens(const Citizens&);						//конструктор копіювання
	unsigned int Getsize() const;					// доступ до прихованого поля size
	void Setel(unsigned int i, inform& ch);	    	//розміщення структури в позицію і
	inform* Citizens::Getelem(unsigned int i) const;	//отримуємо вказівник на і-тий елемент в масиві С
	void InsertInf(inform& a);		//введення інформації з клавіатури, заносимо в структуру  інформацією про про мешканців міста
	void Print() const;				// роздрук матриці
	void FindCitiz(unsigned int &k,unsigned int& p);	//пошук жителів, мешкають в різних містах за однаковою адресою

};
/////////////////////////////////////////////////////////////
void Citizens::Create(unsigned int n)
{
	size=n;
	C=new inform[size];
	if (C==NULL)		//якщо немає вільної пам;яті
	{
		cout<<" Error! Can't allocate! not enough memory. ";	//повдомляємо про це користувача
		exit(1);												// та аварійно завершуємо програму
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
	Create(a.size);								//спочатку розміщуємо в пам;ті
	for( unsigned int i=0; i<size; i++ )      
			C[i]=a.C[i];						 // потім поелементно копіюємо
}
//////////////////////////////////////////////////////////////
Citizens::Citizens(unsigned int n)
{
	Create(n);
}
//////////////////////////////////////////////////////////////
void Citizens::Clear()
{
	delete[] C;		//звільнення ДП
	C = NULL;		//занулення вказівника
}
////////////////////////////////////////////////////////////////
Citizens::~Citizens()
{
	Clear();
}
/////////////////////////////////////////////////////////////
void Citizens::Setel(unsigned int i, inform& ch){
	if(i<size||i>=0)		//якщо індекс не виходить за межі масиву
		C[i]=ch;			//записуємо в масив
	else 
		cout<<"Error!";		
}
/////////////////////////////////////////////////////////////
inform* Citizens::Getelem(unsigned int i) const //повертає вказівник на і-тий елемент в масиві
{
	if(i<size||i>=0)		
		return C+i;
	else return NULL;
}
/////////////////////////////////////////////////////////////
void Citizens::InsertInf(inform& a)		//ввід інформації з клавіатури
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
void Citizens::FindCitiz(unsigned int &k,unsigned int& p) // р і к - номер елементу в масиві С
{

string s=" ";
string s1=" ";
for(unsigned int i=0,j=i+1; i<size-1; i++,j++)
	{
		s.insert(0,C[i].addr.building);			//в s- повна адреса і-того жителя
		s.insert(s.size(),C[i].addr.street);
		s.insert(s.size(),C[i].addr.flat);
		s1.insert(0,C[j].addr.building);		//в s1- повна адреса j-того жителя
		s1.insert(s1.size(),C[j].addr.street);
		s1.insert(s1.size(),C[j].addr.flat);
		if(s==s1)								//якщо адреси жителів збігаються
			if(C[i].town!=C[j].town)			//але живуть вони в різних містах
			{
				k=i;							// ми знайшли те що шукали
				p=j;							
				return;
			}
		s=" ";
		s1=" ";
	}
 k=0; p=0;									//якщо ж таких жителів немає - то індеси одинакові і нульові
}

/////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n;							//розмір масиву
	unsigned int i, j;						//номер елемента в масиві
	cout<<" Enter number of citizens: ";
	cin>>n;
	Citizens Cit(n);
	inform inf;
	for(unsigned int i=0; i<Cit.Getsize(); i++)		// заповнюємо матрицю
	{
			Cit.InsertInf(inf);					//заносимо інформацію в структуру
			Cit.Setel(i,inf);					//та добавляємо її в масив
	}
	Cit.Print();
	Cit.FindCitiz(i,j);
	cout<<" \n\tResidents who live in different cities at the same address:\n ";
	if ((i==0)&&(j==0))						// таких жителів немає
		cout<<"\t Such citizens doesn't exist.";
	else									//якщо ж вони існують
		{
			if(Cit.Getelem(i)==NULL || Cit.Getelem(j)==NULL)		//отримуємо інформацію про них
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
