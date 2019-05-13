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
	int consonant;
public:
	void InCommon(ifstream &);
	void OutCommon(ofstream &);
	int OutConsonant();

	static Plant *InPlant(ifstream &);
	static int ConsonantCount(string &);

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
	enum { max_amount = 100 }; // ������������ �����
	int amount = 0;
	Node *first = NULL; //������ �������
	Node *last = NULL; //��������� �������
public:
	void In(ifstream &);
	void Out(ofstream &);

	void Sort();
	void Pop(Node *);
	void Push(Node *, Node *, Node *);
	void Swap(Node *, Node *);
	Container();
	~Container()
	{
		void Clear();
	}

};