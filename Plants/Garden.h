#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define MAX_TYPES 4 // максимальное число раздичных типов растений 
#define MAX_MONTHS 13 // максимальное число месяцев 
#define MAX_HABITATES 4 // максимальное количество мест обитания
#define MAX_TREE_LIFE 3000 // максимальный возраст дерева

using namespace std;
//Список объектов в программе (в файле для ввода: порядковый номер)
//Обновить при добавлении нового объекта
//Первый тип изпользуется для выявлении ошибок
enum Type
{
	FAIL_T,
	TREE,
	SHRUB,
	FLOWER
};

//Список месяцов года (в файле для ввода: порядковый номер)
//Первый тип изпользуется для выявлении ошибок
enum GenMonth
{
	FAIL_M,
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

//Список мест обитания (в файле для ввода: порядковый номер)
//Первый тип изпользуется для выявлении ошибок
enum GenHabitat
{
	FAIL_H,
	TUNDRA,
	DESERT,
	STEPPE,
	SIBERIA
};

//Список типов растений в программе (в файле для ввода: порядковый номер в списке)
//Обновить при добавлении нового типа
//Первый тип изпользуется для выявлении ошибок
enum GenType
{
	FAIL_T,
	HOME,
	GARDEN,
	WILD
};

// Класс Plant представляет из себя чисто виртуальный класс, 
// который ипользуется в качестве родителя для всех основных классов
// растений в этой программе.
class Plant
{
public:
	string name; // название растения
	GenHabitat habitate; // место обитания
	int consonant; // количество согласных букв в названии
	void InCommon( ifstream & ); // метод для ввода общих параметров
	void OutCommon( ofstream & ); // метод для вывода общих параметров
	int OutConsonant(); // метод вывода количества согласных букв в слове

	virtual void In(ifstream& in) = 0;
	virtual void Out(ofstream& out) = 0;

	virtual void MultiMethod( Plant *other, ofstream &file ) = 0;
	virtual void MMTree( ofstream &file ) = 0;
	virtual void MMShrub( ofstream &file ) = 0;
	static Plant *InPlant( ifstream & ); // основной метод для создания нового объекта
	static int ConsonantCount( string & ); // метод для подсчета количеста согласных букв в названии

	virtual void OutTree( ofstream & ); // метод для фильтрованного вывода

	virtual void In( ifstream& in ) = 0; // чисто виртуальный метод ввода для наследуемых классов
	virtual void Out( ofstream& out ) = 0; // чисто виртуальный метод вывода для наследуемых классов
};

// Класс Three используется для хранении информации о введенном дереве
class Tree : public Plant
{
public:
	int age; //возраст дерева
	void In( ifstream & );
	void Out( ofstream & );

	void OutTree( ofstream & );

	Tree();

	void MultiMethod( Plant *other, ofstream &file );
	void MMTree( ofstream &file );
	void MMShrub( ofstream &file );

	~Tree()
	{
		void Clear();
	}
};

// Класс Three используется для хранении информации о введенном кусте
class Shrub : public Plant
{
public:
	GenMonth month; //месяц цветения
	void In( ifstream & ); // Метод ввода из файла
	void Out( ofstream & ); // Метод вывода в файл

	Shrub();

	void MultiMethod( Plant *other, ofstream &file );
	void MMTree( ofstream &file );
	void MMShrub( ofstream &file );

	~Shrub()
	{
		void Clear();
	}
};

// Класс Three используется для хранении информации о введенном цветке
class Flower : public Plant
{
public:
	GenType type; //тип цветка
	void In( ifstream & );
	void Out( ofstream & );
	Flower();
	~Flower()
	{
		void Clear();
	}
};

// Класс Node представляет из себя элемент программы, который содержит 
// в себе информацию о храниом объекте, а также указатели на связные с ним
// другие элементы
class Node : public Plant
{
public:
	Plant *cur = NULL;
	Node *prev = NULL;
	Node *next = NULL;
	void In(ifstream &);
	void Out(ofstream &);

	void MultiMethod( Plant *other, ofstream &file ) { ; }
	void MMTree( ofstream &file ) { ; }
	void MMShrub( ofstream &file ) { ; }

	Plant *cur = NULL; // Указатель на текущий элемент
	Node *prev = NULL; // Указатель на предыдущий элемент
	Node *next = NULL; // Указатель на следующий элемент
	void In( ifstream & );
	void Out( ofstream & );
	void OutTree( ofstream & );
	Node();
	~Node()
	{
		void Clear();
	}
};

// Класс Container представляет из себя основное хранилище всех элементов
// В нем содержаться функции сортировки, добавления нового элемента и
// вывода содержимого.
class Container : public Plant
{
	enum { max_amount = 100 }; // Максимальная длина
	int amount = 0; // Текущее число элементов
	Node *first = NULL; //Первый элемент
	Node *last = NULL; //Последний элемент
public:
	void In( ifstream & ); 
	void Out( ofstream & ); 
	void OutTree( ofstream & ); // Метод фильтрованного ввода в файл

	void Sort(); // Метод сортировки
	void Pop( Node * ); // Метод изъятия элемента из контейнера
	void Push( Node *, Node *, Node * ); // Метод занесения элемента контейнера
	void Swap( Node *, Node * ); // Метод, которая меняет местами 2 элемента
	
	void In(ifstream &);
	void Out(ofstream &);

	void MultiMethod( ofstream &file );
	void MultiMethod( Plant *other, ofstream &file ) { ; }
	void MMTree( ofstream &file ) { ; }
	void MMShrub( ofstream &file ) { ; }
	Container();
	~Container()
	{
		void Clear(); // Деструктор для контейнера
	}

};