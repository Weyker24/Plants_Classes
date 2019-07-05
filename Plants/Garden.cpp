#pragma once
#include "pch.h"
#include "garden.h"

#define max_types 4
#define max_habitates 4

bool is_number(string s)
{
	std::string::const_iterator it = s.begin();
	isdigit(*it);
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool is_good_string(string s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end() && !(*it == ' ');
}

bool is_empty_file(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

Tree::Tree()
{
	;
}
void Tree::In(ifstream &file)
{
	age = 0;
	string tmp;
	getline(file, tmp);
	if (tmp.empty()) { age = -1; name = "fail"; return; }
	if (!is_number(tmp)) { age = -2; name = "fail"; return;}
	else { age = stoi(tmp); }
	if (age < 0 || age > 3000) { age = -3; name = "fail"; return;}
}

void Tree::Out(ofstream &file)
{
	file << "Объект типа: дерево. Название: ";
	this->OutCommon(file);
	file << ". Возраст: " << age << ". Количество согласных букв = " << OutConsonant() << "." << endl;
}

void Tree::OutTree(ofstream &file)
{
	Out(file);
}

Shrub::Shrub()
{
	;
}

void Shrub::In(ifstream &file)
{
	month = (G_month)(0);
	string tmp;
	getline(file, tmp);
	if (tmp.empty()) { month = (G_month)(0); name = "fail"; return;}
	if (!is_number(tmp)) { month = (G_month)(0); name = "fail"; return;}
	else { month = (G_month)stoi(tmp); month = (G_month)(stoi(tmp));}
	if (stoi(tmp) < 1 || stoi(tmp) > 12) { month = (G_month)(0); name = "fail"; return;}
}

void Shrub::Out(ofstream &file)
{
	file << "Объект типа: куст. Название: ";
	OutCommon(file);
	file << "Месяц цветения: ";
	string months[] = { "Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь" };
	file << months[month] << ". Количество согласных букв = " << OutConsonant() << "." << endl;
}

int Plant::ConsonantCount(string &name)
{
	int consonant = 0;
	string alphabet_consonant("БВГДЖЗКЛМНПРСТФХЦЧШЩбвгджзклмнпрстфхцчшщ");
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

Flower::Flower()
{
	;
}
void Flower::In(ifstream &file)
{
	type = (G_type)(0);
	string tmp;
	getline(file, tmp);
	if (tmp.empty()) { type = (G_type)(0); name = "fail"; return;}
	if (!is_number(tmp)) { type = (G_type)(0); name = "fail";return;}
	else { type = (G_type)stoi(tmp); type = (G_type)(stoi(tmp)); }
	if (stoi(tmp) < 1 || stoi(tmp) > 12) { type = (G_type)(0); name = "fail"; return;}
}

void Flower::Out(ofstream &file)
{
	file << "Объект типа: цветы. Название: ";
	this->OutCommon(file);
	string types[] = { "Домашние", "Садовые", "Дикие" };
	file << "Тип растения: " << types[type] << ". Количество согласных букв = " << OutConsonant() << "." << endl;
}

void Plant::InCommon(ifstream& file)
{
	string tmp;
	//Ввод имени
	getline(file, tmp);
	if (tmp.empty()) { name = "fail"; return; }
	if (is_number(tmp) && is_good_string(tmp)) { name = "fail"; return; }
	else { name = tmp; }
	if (tmp.length() > 20) { name = "fail"; return; }
	//Ввод места обитания
	getline(file, tmp);
	if (tmp.empty()) { habitate = (G_habitat)(0); return; }
	if (!is_number(tmp)) { habitate = (G_habitat)(0); return; }
	else { habitate = (G_habitat)stoi(tmp); }
	if (stoi(tmp) < 1 || stoi(tmp) > max_habitates) { habitate = (G_habitat)(0); return; }
	consonant = ConsonantCount(name);
}

void Plant::OutCommon(ofstream& file)
{
	file << name;
	string habitat_a[] = { "Тундра", "Пустыня", "Степь", "Сибирь" };
	file << " Место обитания: " << habitat_a[habitate] << ". ";
}

int Plant::OutConsonant()
{
	return consonant;
}

void Plant::OutTree(ofstream& file)
{
	;
}

Plant *Plant::InPlant(ifstream &file)
{
	int key;
	string name;
	Plant *x;
	string tmp;
	//Ввод типа
	getline(file, tmp);
	if (tmp.empty() || tmp[0] == ' ' || tmp[0] == '\t') { return NULL; }
	if (!is_number(tmp)) { return NULL; }
	else { key = stoi(tmp); }
	if (stoi(tmp) < 1 || stoi(tmp) > max_types) { return NULL; }
	if (key == 1)
	{
		x = new Tree();
	}
	else if (key == 2)
	{
		x = new Shrub();
	}
	else if (key == 3)
	{
		x = new Flower();
	}
	else
	{
		//todo
		exit(0);
	}
	x->InCommon(file);
	if (x->name == "fail" || x->habitate == 0)
		return NULL;
	x->In(file);
	if (x->name == "fail")
	{
		if (key == 1)
		{
			cout << ("Ошибка в вводе возраста дерева") << endl;
		}
		else if (key == 2)
		{
			cout << ("Ошибка в вводе месяца") << endl;
		}
		else if (key == 3)
		{
			cout << ("Ошибка в вводе типа цветка") << endl;
		}
		return NULL;
	}
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

void Node::OutTree(ofstream &file)
{
	cur->OutTree(file);
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
		if (node->cur == NULL)
		{
			cout << "Файл некорректно написан" << endl;
			exit(0);
		}
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

void Container::OutTree(ofstream &file)
{
	Node *node;
	file << "Количество хранящихся элементов: " << amount << endl;
	node = first;
	for (int i = 0; i < amount; i++)
	{
		node->OutTree(file);
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

void Container::Swap(Node *node1, Node *node2)
{
	Node *new_node = new Node;

	new_node->cur = node2->cur;
	node1->cur = node2->cur;
	node2->cur = new_node->cur;
}