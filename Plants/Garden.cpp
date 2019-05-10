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
	file << "Объект типа: дерево. Название: ";
	this->OutCommon(file);
	file << "Возраст: " << age << ". " << "Количество согласных букв = " << OutConsonant() << "." << endl;
}

Flower::Flower()
{
	;
}
void Flower::In(ifstream &file)
{
	int tmp;
	file >> tmp;
	type = (G_type)(tmp - 1);
}

void Flower::Out(ofstream &file)
{
	file << "Объект типа: цветы. Название: ";
	this->OutCommon(file);
	string types[] = { "Домашние", "Садовые", "Дикие" };
	file << "Тип растения: " << types[type] << ". " << "Количество согласных букв = " << OutConsonant() << "." << endl;
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
	file << "Объект типа: куст. Название: ";
	OutCommon(file);
	file << "Месяц цветения: ";
	string months[] = { "Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь" };
	file << months[month] << ". " << "Количество согласных букв = " << OutConsonant() << "." << endl;
}

void Plant::InCommon(ifstream& file)
{
	string tmp_s;
	int tmp_i;
	file >> name;
	consonant = ConsonantCount(name);
	file >> tmp_i;
	/*file >> tmp_s;
	while ((int)tmp_s[0] > 9)
	{
		cout << "{" << tmp_s[0] << "}";
		name.append(" ");
		name.append(tmp_s);
		file >> tmp_s;
	}
	tmp_i = (int)tmp_s[0];*/
	habitat = (G_habitat)(tmp_i - 1);
}

void Plant::OutCommon(ofstream& file)
{
	file << name;
	string habitat_a[] = { "Тундра", "Пустыня", "Степь", "Сибирь"};
	file << " Место обитания: " << habitat_a[habitat] << ". ";
}

int Plant::OutConsonant()
{
	return consonant;
}

int Plant::ConsonantCount(string &name)
{
	int consonant = 0;
	string alphabet_consonant ("БВГДЖЗКЛМНПРСТФХЦЧШЩбвгджзклмнпрстфхцчшщ");
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

Plant *Plant::InPlant(ifstream &file)
{
	int key;
	string name;
	Plant *x;
	file >> key;

	//Определение типа объекта
	//Обновить при добавлении/удалении нового объекта

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
	else if (key == 3)
	{
		x = new Flower();
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
			cout << "Ошибка: достигнут максимальное количество элементов." << endl;
			cout << "Программа продолжит выполнение с текущим содержимым." << endl;
			return;
		}
	}
}

void Container::Out(ofstream &file)
{
	Node *node;
	file << "Количество хранящихся элементов: " << amount << endl;
	node = first;
	for (int i = 0; i < amount; i++)
	{
		node->Out(file);
		node = node->next;
	}
}

void Container::Sort()
{
	Node *node_cur = first->next;
	Node *tmp;
	Node *tmp2;

	for (node_cur = first->next; node_cur != first;)
	{
		if (node_cur->cur->OutConsonant() < node_cur->prev->cur->OutConsonant())
		{
			tmp2 = node_cur;
			node_cur = node_cur->next;
			if (first->cur->OutConsonant() > tmp2->cur->OutConsonant())
			{
				Pop(tmp2);
				Push(first->prev, first, tmp2);
				first = tmp2;
				last = tmp2->prev;
			}
			else
			{
				for (tmp = tmp2->prev; tmp != first->prev; tmp = tmp->prev)
				{
					if ((tmp->cur->OutConsonant() > tmp2->cur->OutConsonant()) && (tmp->prev->cur->OutConsonant() <= tmp2->cur->OutConsonant()))
					{
						Pop(tmp2);
						Push(tmp->prev, tmp, tmp2);
						break;
					}
				}
			}
		}
		else
		{
			node_cur = node_cur->next;
		}
	}
}

void Container::Swap(Node *node1, Node *node2)
{
	Node *new_node = new Node;

	new_node->cur = node2->cur;
	node1->cur = node2->cur;
	node2->cur = new_node->cur;
}

void Container::Pop(Node *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
}
//Вставляет node3 между node1 и node2.
void Container::Push(Node *node1, Node *node2, Node *node3)
{
	node1->next = node3;
	node2->prev = node3;
	node3->prev = node1;
	node3->next = node2;
}