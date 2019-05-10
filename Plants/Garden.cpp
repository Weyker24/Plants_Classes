#pragma once
#include "pch.h"
#include "garden.h"
Tree::Tree()
{
	;
}
void Tree::In(ifstream &file)
{
	file >> age;
}

void Tree::Out(ofstream &file)
{
	file << "������ ����: ������. ��������: ";
	this->OutCommon(file);
	file << ". �������: " << age << ". ���������� ��������� ���� = " << OutConsonant() << "." << endl;
}


Shrub::Shrub()
{
	;
}

void Shrub::In(ifstream &file)
{
	int tmp;
	file >> tmp;
	month = (G_month)(tmp - 1);
}

void Shrub::Out(ofstream &file)
{
	file << "������ ����: ����. ��������: ";
	OutCommon(file);
	file << ". ����� ��������: ";
	string months[] = { "������","�������","����","������","���","����","����","������","��������","�������","������","�������" };
	file << months[month] << ". ���������� ��������� ���� = " << OutConsonant() << "." << endl;
}

int Plant::ConsonantCount(string &name)
{
	int consonant = 0;
	string alphabet_consonant("����������������������������������������");
	for (unsigned int i = 0; i < name.length(); i++)
	{
		if (alphabet_consonant.find(name[i]) != string::npos)
		{
			consonant++;
		}
	}
	cout << endl;
	return consonant;
}

void Plant::InCommon(ifstream& file)
{
	file >> name;
	consonant = ConsonantCount(name);
}

void Plant::OutCommon(ofstream& file)
{
	file << name;
}

int Plant::OutConsonant()
{
	return consonant;
}

Plant *Plant::InPlant(ifstream &file)
{
	int key;
	string name;
	Plant *x;
	file >> key;
	if (key == 1)
	{
		x = new Tree();
		x->InCommon(file);
	}
	else if (key == 2)
	{
		x = new Shrub();
		x->InCommon(file);
	}
	else
	{
		//todo
		exit(0);
	}
	x->In(file);
	return x;
}

Node::Node()
{
	;
}

void Node::In(ifstream &file)
{
	Plant *plant = Plant::InPlant(file);

	cur = plant;
}

void Node::Out(ofstream &file)
{
	cur->Out(file);
}

Container::Container()
{
	;
}

void Container::In(ifstream &file)
{
	Node *node;
	for (; !file.eof(); )
	{
		amount++;

		node = new Node();
		node->In(file);

		if (first == NULL)
		{
			first = node;
			last = node;
		}

		node->next = first;
		node->prev = last;
		last->next = node;
		first->prev = node;
		last = node;

		if (amount == max_amount)
		{
			cout << "������: ��������� ������������ ���������� ���������." << endl;
			cout << "��������� ��������� ���������� � ������� ����������." << endl;
			return;
		}
	}
}

void Container::Out(ofstream &file)
{
	Node *node;
	file << "���������� ���������� ���������: " << amount << endl;
	node = first;
	for (int i = 0; i < amount; i++)
	{
		node->Out(file);
		node = node->next;
	}
}