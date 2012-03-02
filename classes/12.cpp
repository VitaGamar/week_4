// 12.cpp : Defines the entry point for the console application.
//
///«адана квадратна матриц€ розм≥рност≥ m*m. ћатрицю задати в клас≥ Matr	.
//«найти скал€рний добуток першого р€дка матриц≥ на m-м≥рний вектор,кожна координата €кого Ї залишок по mod m 
//в≥д р≥зних елемент≥в останнього стовпц€ матриц≥. 
//–озм≥рн≥сть задати в головн≥й програм≥ константою. ≈лементами матриц≥ Ї ц≥л≥ числа.
#include "stdafx.h"
#include<iostream>
using namespace std;
typedef unsigned short int ui;
const ui K=4;		//розм≥рн≥сть матриц≥
////////////////////////////////////////////////////////
class Matr{
	int **m;
	ui N;				//розм≥р матриц≥
public:
	Matr ( );			//конструктор без параметр≥в
	Matr ( ui n );			//конструктор з параметрами
	Matr ( const Matr& mas );		//конструктор коп≥юванн€
	~Matr ( );
	void Create( ui n );			//створенн€ обЇкту
	void Clear();					//зв≥льненн€ пам€т≥
	ui GetSize( ) const;			//отримуЇ розм≥р матриц≥
	void PrintM( ) const;				//виводить матрицю
	void SetEl ( ui i, ui j, int value );		//заповнюЇ матрицю значенн€ми
	int ScalarMult ( ) const;		//функц≥€ знаходить скал€рний добуток першого р€дка матриц≥ на m-м≥рний вектор,
										//кожна координата €кого Ї залишок по mod m 
										//в≥д р≥зних елемент≥в останнього стовпц€ матриц≥. 
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
			mas.SetEl ( i, j, (2*i+3*j) );			//заповненн€ матриц≥ значенн€ми 2i+3j
	cout<<"\nYour matrix: \n";
	mas.PrintM();
	cout<<"\nScalar multiplication : "<<mas.ScalarMult( )<<endl;		//вив≥д скал€рного добутку
	system("pause");
	return 0;
}

////////////////////////////////////////////////////////
Matr::Matr( ) {					//конструктор без параметр≥в					
	Create( K );				//встановлюЇтьс€ константний розм≥р по замовчуванн≥
}

////////////////////////////////////////////////////////
Matr::Matr ( ui size ) {			//конструктор з параметрами
	Create( size );
}

////////////////////////////////////////////////////////
Matr::Matr ( const Matr& mas ) {		//коструктор коп≥юванн€
	Create(mas.N);
	for( ui i=0; i<N; i++ )	     
		for( ui j=0; j<N; j++ )	
			m[i][j]=mas.m[i][j];				// коп≥юЇ значенн€ елемент≥в
}
/////////////////////////////////////////////////////
void Matr::Create( ui size ){
	N=size;
	m=new int*[N];					//вид≥л€Ї м≥сце 
	if(m==NULL) { 
		cout<<"Error!Cant allocate memory"; 
		exit(1);
	}
	for( ui i=0; i<N; i++ )	{		//в ƒѕ п≥д 
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
	for( ui i=0; i<N; i++ )			//зв≥льн€Ї вид≥лену
		delete[] m[i];				//п≥д матрицю N*N
	delete []m;						//пам€ть
	N=0;
	m=NULL;
}

////////////////////////////////////////////////////////
int Matr::ScalarMult( ) const {			//знаходить скал€рний добуток першого р€дка матриц≥ 
										//на m-м≥рний вектор,кожна координата €кого Ї залишок по mod m 
										//в≥д р≥зних елемент≥в останнього стовпц€ матриц≥
	int res=0, d;
	cout<<"\nResidue of division: \n";
	for ( ui i=0; i<N; i++ ){			//остача в≥д д≥ленн€ елемент≥в останнього стовпц€ на розм≥рн≥сть матриц≥
		d=m[i][N-1] % N;
		res+= m[0][i]*d;
		cout<<d<<" ";
	}
	return res;
}

////////////////////////////////////////////////////////

void Matr::SetEl ( ui i, ui j, int value ) {			//встановлюЇ значенн€ value
	if ( i>=0 || i<N || j>=0 || j<N )
		*(*(m+i)+j) = value;								//на позиц≥ю (i,j)
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