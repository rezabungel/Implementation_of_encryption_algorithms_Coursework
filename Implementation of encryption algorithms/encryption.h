#pragma once
#include <iostream>
#include <string> 
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ceasar
{
private:
	int key; //���� ����������.
public:
	ceasar(const int m_key = 3);     //�����������

	string encrypt(const string& message); //�������

	string decrypt(const string& message); //���������

	~ceasar() {}     //����������
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class affine
{
private:
	int key_a, key_b; //���� ����������. ���� � - ������� ������� � 26 ����� (26-���������� ���� � ��������).
public:
	affine(const int key_one = 3, const int key_two = 5);     //�����������

	string encrypt(const string& message); //�������

	string decrypt(const string& message); //���������

	~affine() {}     //����������
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class vigener
{
private:
	string key_word;
public:
	vigener(const string& key = "Holmes!");     //�����������

	string encrypt(const string& message); //�������

	string decrypt(const string& message); //���������

	~vigener() {}     //����������

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class playfair
{
private:
	//���� ������ ���� ������ �� ���������� �������� ����.
	string key_max_word;
	bool without_meaning = false;//������ ����������� ������� �������� �� ����� �����.
public:
	playfair(const string& key = "D !o?:?ct!or!");     //�����������

	string encrypt(const string& message); //�������

	string decrypt(const string& message); //���������

	~playfair() {}     //����������
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class polybius
{
private:
	//������� ��� ����������� ����� 5x5.
	char english_matrix[5][5];

public:
	polybius();     //�����������

	string encrypt(const string& message); //�������

	string decrypt(const string& message); //���������

	~polybius() {}     //����������
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class hilla
{
private:
	int key_matrix[2][2]; //������� ���� - ������� 2x2.
	bool without_meaning = false;//������ ����������� ������� �������� �� ����� �����.

public:
	hilla();     //�����������

	string encrypt(const string& message); //�������

	string decrypt(const string& message); //���������

	~hilla() {}     //����������
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////