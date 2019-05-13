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

enum G_type
{
	HOME,
	GARDEN,
	WILD
};

enum G_habitat
{
	TUNDRA,
	DESERT,
	STEPPE,
	SIBERIA
};

class Plant {
	string name;
	G_habitat habitat;
public:
	void InCommon(ifstream &);
	void OutCommon(ofstream &);
	static Plant *InPlant(ifstream &);

	virtual void In(ifstream& in) = 0;
	virtual void Out(ofstream& out) = 0;
};

class Tree : public Plant {
	int age;
public:
	void In(ifstream &);
	void Out(ofstream &);
	Tree();
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
	~Shrub()
	{
		void Clear();
	}
};

class Flower : public Plant {
	G_type type;
public:
	void In(ifstream &);
	void Out(ofstream &);
	Flower();
	~Flower()
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
	Container();
	~Container()
	{
		void Clear();
	}

};