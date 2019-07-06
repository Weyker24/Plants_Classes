#pragma once
#include "pch.h"
#include "garden.h"

bool is_number( string s )
{
	std::string::const_iterator it = s.begin();
	isdigit( *it );
	while ( it != s.end() && isdigit( (unsigned char) *it ) ) ++it;
	return !s.empty() && it == s.end();
}

bool is_good_string( string s )
{
	std::string::const_iterator it = s.begin();
	while ( it != s.end() && isdigit( *it ) ) ++it;
	return !s.empty() && it == s.end() && !( *it == ' ' );
}

bool is_empty_file( std::ifstream& pFile )
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

Tree::Tree()
{
	;
}
void Tree::In( ifstream &file )
{
	age = 0;
	string tmp;
	getline( file, tmp );
	if ( tmp.empty() ) { age = -1; name = "fail"; return; }
	if ( !is_number( tmp ) ) { age = -2; name = "fail"; return; }
	else { age = stoi( tmp ); }
	if ( age < 0 || age > MAX_TREE_LIFE ) { age = -3; name = "fail"; return; }
}

void Tree::Out( ofstream &file )
{
	file << "Объект типа: дерево. Название: ";
	this->OutCommon( file );
	file << "Возраст: " << age << ". Количество согласных букв = " << OutConsonant() << "." << endl;
}

void Tree::OutTree( ofstream &file )
{
	Out( file );
}

Shrub::Shrub()
{
	;
}

void Shrub::In( ifstream &file )
{
	month = ( GenMonth ) ( 0 );
	string tmp;
	getline( file, tmp );
	if ( tmp.empty() ) { month = ( GenMonth ) ( 0 ); name = "fail"; return; }
	if ( !is_number( tmp ) ) { month = ( GenMonth ) ( 0 ); name = "fail"; return; }
	else { month = ( GenMonth ) stoi( tmp ); month = ( GenMonth ) ( stoi( tmp ) ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > MAX_MONTHS ) { month = ( GenMonth ) ( 0 ); name = "fail"; return; }
}

void Shrub::Out( ofstream &file )
{
	file << "Объект типа: куст. Название: ";
	OutCommon( file );
	file << "Месяц цветения: ";
	string months[] = { "Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь" };
	file << months [month-1] << "Количество согласных букв = " << OutConsonant() << "." << endl;
}


Flower::Flower()
{
	;
}
void Flower::In( ifstream &file )
{
	type = ( GenType ) ( 0 );
	string tmp;
	getline( file, tmp );
	if ( tmp.empty() ) { type = ( GenType ) ( 0 ); name = "fail"; return; }
	if ( !is_number( tmp ) ) { type = ( GenType ) ( 0 ); name = "fail"; return; }
	else { type = ( GenType ) stoi( tmp ); type = ( GenType ) ( stoi( tmp ) ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > MAX_TYPES ) { type = ( GenType ) ( 0 ); name = "fail"; return; }
}

void Flower::Out( ofstream &file )
{
	file << "Объект типа: цветы. Название: ";
	this->OutCommon( file );
	string types[] = { "Домашние", "Садовые", "Дикие" };
	file << "Тип растения: " << types [type - 1] << "Количество согласных букв = " << OutConsonant() << "." << endl;
}

// Вывод двух деревьев
void Tree::MMTree( ofstream &file )
{
	file << "Дерево и дерево" << endl;
}
//-----------------------------------------------------
// Вывод сначала куста, а затем дерева
void Tree::MMShrub( ofstream &file )
{
	file << "Куст и дерево" << endl;
}
//-----------------------------------------------------
// Вывод сначала цветка, а затем дерева
void Tree::MMFlower( ofstream &file )
{
	file << "Цветок и дерево" << endl;
}
//-----------------------------------------------------
// Вывод сначала дерева, а затем куста
void Shrub::MMTree( ofstream &file )
{
	file << "Дерево и куст" << endl;
}
//-----------------------------------------------------
// Вывод двух кустов
void Shrub::MMShrub( ofstream &file )
{
	file << "Куст и куст" << endl;
}
//-----------------------------------------------------
// Вывод цветка и куста
void Shrub::MMFlower( ofstream &file )
{
	file << "Цветок и куст" << endl;
}
//-----------------------------------------------------

// Вывод сначала дерева, а затем цветка
void Flower::MMTree( ofstream &file )
{
	file << "Дерево и цветок" << endl;
}
//-----------------------------------------------------
// Вывод сначала куста, а затем цветка
void Flower::MMShrub( ofstream &file )
{
	file << "Куст и куст" << endl;
}
//-----------------------------------------------------
// Вывод двух цветков
void Flower::MMFlower( ofstream &file )
{
	file << "Два Цветка" << endl;
}
//-----------------------------------------------------
// мультиметод дерева
void Tree::MultiMethod( Plant *other,
							 ofstream &file )
{
	other->MMTree( file );
}
//-----------------------------------------------------
// мультиметод куста
void Shrub::MultiMethod( Plant *other,
						ofstream &file )
{
	other->MMShrub( file );
}
// мультиметод цветка
void Flower::MultiMethod( Plant *other,
						ofstream &file )
{
	other->MMFlower( file );
}
//-----------------------------------------------------

int Plant::ConsonantCount( string &name )
{
	int consonant = 0;
	string alphabet_consonant( "QWRTPSDFGHJKLZXCVBNMqwrtpsdfghjklzxcvbnm" );
	for ( unsigned int i = 0; i < name.length(); i++ )
	{
		if ( alphabet_consonant.find( name [i] ) != string::npos )
		{
			consonant++;
		}
	}
	cout << endl;
	return consonant;
}

void Plant::InCommon( ifstream& file )
{
	string tmp;
	//Ввод имени
	getline( file, tmp );
	if ( tmp.empty() ) { name = "fail"; return; }
	if ( is_number( tmp ) && is_good_string( tmp ) ) { name = "fail"; return; }
	else { name = tmp; }
	if ( tmp.length() > 20 ) { name = "fail"; return; }
	//Ввод места обитания
	getline( file, tmp );
	if ( tmp.empty() ) { habitate = ( GenHabitat ) ( 0 ); return; }
	if ( !is_number( tmp ) ) { habitate = ( GenHabitat ) ( 0 ); return; }
	else { habitate = ( GenHabitat ) stoi( tmp ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > MAX_HABITATES ) { habitate = ( GenHabitat ) ( 0 ); return; }
	consonant = ConsonantCount( name );
}

void Plant::OutCommon( ofstream& file )
{
	file << name;
	string habitat_a[] = { "Тундра", "Пустыня", "Степь", "Сибирь" };
	file << " Место обитания: " << habitat_a [habitate - 1] << ". ";
}

int Plant::OutConsonant()
{
	return consonant;
}

void Plant::OutTree( ofstream& file )
{
	;
}

Plant *Plant::InPlant( ifstream &file )
{
	int key;
	string name;
	Plant *x;
	string tmp;
	//Ввод типа
	getline( file, tmp );
	if ( tmp.empty() || tmp [0] == ' ' || tmp [0] == '\t' ) { return NULL; }
	if ( !is_number( tmp ) ) { return NULL; }
	else { key = stoi( tmp ); }
	if ( stoi( tmp ) < 1 || stoi( tmp ) > MAX_TYPES ) { return NULL; }
	if ( key == 1 )
	{
		x = new Tree();
	}
	else if ( key == 2 )
	{
		x = new Shrub();
	}
	else if ( key == 3 )
	{
		x = new Flower();
	}
	else
	{
		//todo
		exit( 0 );
	}
	x->InCommon( file );
	if ( x->name == "fail" || x->habitate == 0 )
		return NULL;
	x->In( file );
	if ( x->name == "fail" )
	{
		if ( key == 1 )
		{
			cout << ( "Ошибка в вводе возраста дерева" ) << endl;
		}
		else if ( key == 2 )
		{
			cout << ( "Ошибка в вводе месяца" ) << endl;
		}
		else if ( key == 3 )
		{
			cout << ( "Ошибка в вводе типа цветка" ) << endl;
		}
		return NULL;
	}
	return x;
}

Node::Node()
{
	;
}

void Node::In( ifstream &file )
{
	Plant *plant = Plant::InPlant( file );

	cur = plant;
}

void Node::Out( ofstream &file )
{
	cur->Out( file );
}

void Node::OutTree( ofstream &file )
{
	cur->OutTree( file );
}

Container::Container()
{
	;
}

void Container::In( ifstream &file )
{
	Node *node;
	for ( ; !file.eof(); )
	{
		amount++;

		node = new Node();
		node->In( file );
		if ( node->cur == NULL )
		{
			cout << "Файл некорректно написан" << endl;
			exit( 0 );
		}
		if ( first == NULL )
		{
			first = node;
			last = node;
		}

		node->next = first;
		node->prev = last;
		last->next = node;
		first->prev = node;
		last = node;

		if ( amount == max_amount )
		{
			cout << "Ошибка: достигнут максимальное количество элементов." << endl;
			cout << "Программа продолжит выполнение с текущим содержимым." << endl;
			return;
		}
	}

}

void Container::Out( ofstream &file )
{
	Node *node;
	file << "Количество хранящихся элементов: " << amount << endl;
	node = first;
	for ( int i = 0; i < amount; i++ )
	{
		node->Out( file );
		node = node->next;
	}
}

void Container::OutTree( ofstream &file )
{
	Node *node;
	file << "Количество хранящихся элементов: " << amount << endl;
	node = first;
	for ( int i = 0; i < amount; i++ )
	{
		node->OutTree( file );
		node = node->next;
	}
}

void Container::Sort()
{
	Node *node_cur = first->next;
	Node *tmp;
	Node *tmp2;

	for ( node_cur = first->next; node_cur != first;)
	{
		if ( node_cur->cur->OutConsonant() < node_cur->prev->cur->OutConsonant() )
		{
			tmp2 = node_cur;
			node_cur = node_cur->next;
			if ( first->cur->OutConsonant() > tmp2->cur->OutConsonant() )
			{
				Pop( tmp2 );
				Push( first->prev, first, tmp2 );
				first = tmp2;
				last = tmp2->prev;
			}
			else
			{
				for ( tmp = tmp2->prev; tmp != first->prev; tmp = tmp->prev )
				{
					if ( ( tmp->cur->OutConsonant() > tmp2->cur->OutConsonant() ) && ( tmp->prev->cur->OutConsonant() <= tmp2->cur->OutConsonant() ) )
					{
						Pop( tmp2 );
						Push( tmp->prev, tmp, tmp2 );
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

void Container::Pop( Node *node )
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
}
//Вставляет node3 между node1 и node2.
void Container::Push( Node *node1, Node *node2, Node *node3 )
{
	node1->next = node3;
	node2->prev = node3;
	node3->prev = node1;
	node3->next = node2;
}

void Container::Swap( Node *node1, Node *node2 )
{
	Node *new_node = new Node;

	new_node->cur = node2->cur;
	node1->cur = node2->cur;
	node2->cur = new_node->cur;
}


// Вызов мультиметода для элементов контейнера
void Container::MultiMethod( ofstream &file )
{
	Node *first_tmp;
	Node *second_tmp;
	first_tmp = first;
	file << "Мультиметод." << endl;
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
