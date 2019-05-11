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

	virtual void OutTree(ofstream &);

	virtual void In(ifstream& in) = 0;
	virtual void Out(ofstream& out) = 0;
};

class Tree : public Plant {
	int age;
public:
	void In(ifstream &);
	void Out(ofstream &);

	void OutTree(ofstream &);

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

	void OutShrub(ofstream &);

	Shrub();
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
	Node();
	~Node()
	{
		void Clear();
	}
};

class Container : public Plant {
	enum { max_amount = 100 }; // ������������ �����
	int amount = 0;
	Node *first = NULL; //������ �������
	Node *last = NULL; //��������� �������
public:
	void In(ifstream &);
	void Out(ofstream &);

	Container();
	~Container()
	{
		void Clear();
	}

};