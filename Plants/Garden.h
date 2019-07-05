#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum Type {
	TREE,
	SHRUB
};

enum G_month
{
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

class Plant {
	string name;
public:
	void InCommon(ifstream &);
	void OutCommon(ofstream &);
	static Plant *InPlant(ifstream &);

	virtual void In(ifstream& in) = 0;
	virtual void Out(ofstream& out) = 0;

	virtual void MultiMethod( Plant *other, ofstream &file ) = 0;
	virtual void MMTree( ofstream &file ) = 0;
	virtual void MMShrub( ofstream &file ) = 0;
};

class Tree : public Plant {
	int age;
public:
	void In(ifstream &);
	void Out(ofstream &);
	Tree();

	void MultiMethod( Plant *other, ofstream &file );
	void MMTree( ofstream &file );
	void MMShrub( ofstream &file );

	~Tree()
	{
		void Clear();
	}
};

class Shrub : public Plant {
	G_month month;
public:
	void In(ifstream &);
	void Out(ofstream &);
	Shrub();

	void MultiMethod( Plant *other, ofstream &file );
	void MMTree( ofstream &file );
	void MMShrub( ofstream &file );

	~Shrub()
	{
		void Clear();
	}
};

class Node : public Plant {
public:
	Plant *cur = NULL;
	Node *prev = NULL;
	Node *next = NULL;
	void In(ifstream &);
	void Out(ofstream &);

	void MultiMethod( Plant *other, ofstream &file ) { ; }
	void MMTree( ofstream &file ) { ; }
	void MMShrub( ofstream &file ) { ; }

	Node();
	~Node()
	{
		void Clear();
	}
};

class Container : public Plant {
	enum { max_amount = 100 }; // максимальная длина
	int amount = 0;
	Node *first = NULL; //Первый элемент
	Node *last = NULL; //Последний элемент
public:
	
	void In(ifstream &);
	void Out(ofstream &);

	void MultiMethod( ofstream &file );
	void MultiMethod( Plant *other, ofstream &file ) { ; }
	void MMTree( ofstream &file ) { ; }
	void MMShrub( ofstream &file ) { ; }
	Container();
	~Container()
	{
		void Clear();
	}

};