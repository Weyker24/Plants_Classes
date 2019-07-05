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
	file << ". �������: " << age << endl;
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
	file << months[month] << "." << endl;
}

// ����� ���� ���������������
void Tree::MMTree( ofstream &file )
{
	file << "������ � ������" << endl;
}
//-----------------------------------------------------
// ����� ������������ � ��������������
void Tree::MMShrub( ofstream &file )
{
	file << "���� � ������" << endl;
}
//-----------------------------------------------------
// ����� �������������� � ������������
void Shrub::MMTree( ofstream &file )
{
	file << "������ � ����" << endl;
}
//-----------------------------------------------------
// ����� ���� �������������
void Shrub::MMShrub( ofstream &file )
{
	file << "���� � ����" << endl;
}
// �����������
void Tree::MultiMethod( Plant *other,
							 ofstream &file )
{
	other->MMTree( file );
}
//-----------------------------------------------------
// �����������
void Shrub::MultiMethod( Plant *other,
						ofstream &file )
{
	other->MMShrub( file );
}
void Plant::InCommon(ifstream& file)
{
	file >> name;
}

void Plant::OutCommon(ofstream& file)
{
	file << name;
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

// ����� ������������ ��� ��������� ����������
void Container::MultiMethod( ofstream &file )
{
	Node *first_tmp;
	Node *second_tmp;
	first_tmp = first;
	file << "Multimethod." << endl;
	for ( int i = 0; i < amount - 1; i++ )
	{
		second_tmp = first_tmp->next;
		for ( int j = i + 1; j < amount; j++ )
		{
			first_tmp->cur->MultiMethod( second_tmp->cur, file );
			first_tmp->cur->Out( file );
			second_tmp->cur->Out( file );
			second_tmp = second_tmp->next;
		}
		first_tmp = first_tmp->next;
	}
}
