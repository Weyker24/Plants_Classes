#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum Type
{
	TREE,
	SHRUB
};

enum G_month
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

enum G_type
{
	FAIL_T,
	HOME,
	GARDEN,
	WILD
};

enum G_habitat
{
	FAIL_H,
	TUNDRA,
	DESERT,
	STEPPE,
	SIBERIA
};

class Plant
{
public:
	string name;
	G_habitat habitate;
	int consonant;
	void InCommon( ifstream & );
	void OutCommon( ofstream & );
	int OutConsonant();

	static Plant *InPlant( ifstream & );
	static int ConsonantCount( string & );

	virtual void OutTree( ofstream & );

	virtual void In( ifstream& in ) = 0;
	virtual void Out( ofstream& out ) = 0;
};

class Tree : public Plant
{
public:
	int age;
	void In( ifstream & );
	void Out( ofstream & );

	void OutTree( ofstream & );

	Tree();
	~Tree()
	{
		void Clear();
	}
};

class Shrub : public Plant
{
public:
	G_month month;
	void In( ifstream & );
	void Out( ofstream & );

	Shrub();
	~Shrub()
	{
		void Clear();
	}
};

class Flower : public Plant
{
public:
	G_type type;
	void In( ifstream & );
	void Out( ofstream & );
	Flower();
	~Flower()
	{
		void Clear();
	}
};

class Node : public Plant
{
public:
	Plant *cur = NULL;
	Node *prev = NULL;
	Node *next = NULL;
	void In( ifstream & );
	void Out( ofstream & );
	void OutTree( ofstream & );
	Node();
	~Node()
	{
		void Clear();
	}
};

class Container : public Plant
{
	enum { max_amount = 100 }; // максимальная длина
	int amount = 0;
	Node *first = NULL; //Первый элемент
	Node *last = NULL; //Последний элемент
public:
	void In( ifstream & );
	void Out( ofstream & );
	void OutTree( ofstream & );

	void Sort();
	void Pop( Node * );
	void Push( Node *, Node *, Node * );
	void Swap( Node *, Node * );
	Container();
	~Container()
	{
		void Clear();
	}

};