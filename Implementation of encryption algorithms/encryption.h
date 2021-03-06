#pragma once
#include <iostream>
#include <string> 
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ceasar
{
private:
	int key; //ключ шифрования.
public:
	ceasar(const int m_key = 3);     //конструктор

	string encrypt(const string& message); //шифрует

	string decrypt(const string& message); //дешифрует

	~ceasar() {}     //деструктор
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class affine
{
private:
	int key_a, key_b; //ключ шифрования. ключ а - взаимно простое с 26 число (26-количество букв в алфавите).
public:
	affine(const int key_one = 3, const int key_two = 5);     //конструктор

	string encrypt(const string& message); //шифрует

	string decrypt(const string& message); //дешифрует

	~affine() {}     //деструктор
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class vigener
{
private:
	string key_word;
public:
	vigener(const string& key = "Holmes!");     //конструктор

	string encrypt(const string& message); //шифрует

	string decrypt(const string& message); //дешифрует

	~vigener() {}     //деструктор

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class playfair
{
private:
	//ключ должен быть только из английских строчных букв.
	string key_max_word;
	bool without_meaning = false;//служит индикатором наличия пустышки на конце слова.
public:
	playfair(const string& key = "D !o?:?ct!or!");     //конструктор

	string encrypt(const string& message); //шифрует

	string decrypt(const string& message); //дешифрует

	~playfair() {}     //деструктор
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class polybius
{
private:
	//матрица для английского языка 5x5.
	char english_matrix[5][5];

public:
	polybius();     //конструктор

	string encrypt(const string& message); //шифрует

	string decrypt(const string& message); //дешифрует

	~polybius() {}     //деструктор
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class hilla
{
private:
	int key_matrix[2][2]; //матрица ключ - размера 2x2.
	bool without_meaning = false;//служит индикатором наличия пустышки на конце слова.

public:
	hilla();     //конструктор

	string encrypt(const string& message); //шифрует

	string decrypt(const string& message); //дешифрует

	~hilla() {}     //деструктор
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////