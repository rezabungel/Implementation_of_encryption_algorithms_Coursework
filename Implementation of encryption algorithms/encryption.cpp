#include "encryption.h"
//��� �����::�����(���������) {����������}


ceasar::ceasar(const int m_key) :key(m_key)
{
	if (m_key != 3)
	{
		key = 3;
	}
}

string ceasar::encrypt(const string& message)
{
	string secret;
	string help;
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			switch (message[i])
			{
			case 88:
				help = 65;
				secret = secret + help;
				break;
			case 89:
				help = 66;
				secret = secret + help;
				break;
			case 90:
				help = 67;
				secret = secret + help;
				break;
			case 120:
				help = 97;
				secret = secret + help;
				break;
			case 121:
				help = 98;
				secret = secret + help;
				break;
			case 122:
				help = 99;
				secret = secret + help;
				break;
			default:
				help = message[i] + key; //�������� �� 3
				secret = secret + help;
				break;
			}
		}
		else
		{
			secret = secret + message[i];
		}
	};
	return secret;
}

string ceasar::decrypt(const string& message)
{
	string unsecret;
	string help;
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			switch (message[i])
			{
			case 65:
				help = 88;
				unsecret = unsecret + help;
				break;
			case 66:
				help = 89;
				unsecret = unsecret + help;
				break;
			case 67:
				help = 90;
				unsecret = unsecret + help;
				break;
			case 97:
				help = 120;
				unsecret = unsecret + help;
				break;
			case 98:
				help = 121;
				unsecret = unsecret + help;
				break;
			case 99:
				help = 122;
				unsecret = unsecret + help;
				break;
			default:
				help = message[i] - key; //�������� �� 3
				unsecret = unsecret + help;
				break;
			}
		}
		else
		{
			unsecret = unsecret + message[i];
		}
	};
	return unsecret;
}

affine::affine(const int key_one, const int key_two) :
	key_a(key_one), key_b(key_two)
{

}

//��� ������ ������� ����������, ����������, ����� ������� � ����� ���� ������: a..z = 0..25. ���������� � ��� ��������� ����. ����� ������� �� �������, �������� ��������.
string affine::encrypt(const string& message)
{
	string secret;
	char help;
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{//��������� �����-��������� �� 65.
				help = message[i] - 65;
				help = (help * key_a + key_b) % 26; //������� ����������.
				help = help + 65;
				secret = secret + help;
			}
			else
			{//�������� �����-��������� �� 97.
				help = message[i] - 97;
				help = (help * key_a + key_b) % 26; //������� ����������.
				help = help + 97;
				secret = secret + help;
			};
		}
		else
		{
			secret = secret + message[i];
		};
	};
	return secret;
}

//��� ������ ������� ������������, ����������, ����� ������� � ����� ���� ������: a..z = 0..25. ���������� � ��� ��������� ����. ����� ������� �� �������, �������� ��������.
string affine::decrypt(const string& message)
{
	//���������� ����������������� ��������.
	int k = 0;
	for (k; k < 26; k++)
	{
		if ((key_a * k) % 26 == 1)
		{
			break;
		}
	}
	//k-����������������� ��������
	string unsecret;
	char help;
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{//��������� �����-��������� �� 65.
				help = message[i] - 65;
				help = k * (help - key_b + 26) % 26;  //������� ������������.
				help = help + 65;
				unsecret = unsecret + help;
			}
			else
			{//�������� �����-��������� �� 97.
				help = message[i] - 97;
				help = k * (help - key_b + 26) % 26; //������� ������������.
				help = help + 97;
				unsecret = unsecret + help;
			};
		}
		else
		{
			unsecret = unsecret + message[i];
		};
	};
	return unsecret;
}

vigener::vigener(const string& key)
{
	//���� ������ ���� ������ �� ���������� �������� ����.
	//���������� ����. (��������� �����, �������, ����� ����������). !��������� ����� ��������� �� ��������!
	string help_key = key;
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] >= 65 && key[i] <= 90)
		{
			help_key[i] = help_key[i] + 32; //�������� ��������� ����� �� ��������.
		}
	};
	for (int i = 0; i < help_key.length(); i++)
	{//������� ������� � ����� ����������.
		if (help_key[i] >= 97 && help_key[i] <= 122)
		{
			index = index + 1;
			key_word.resize(index, help_key[i]);
		}
	}
}

//��� ������ ������� ����������, ����������, ����� ������� � ����� ���� ������: a..z = 0..25. ���������� � ��� ��������� ����. ����� ������� �� �������, �������� ��������.
string vigener::encrypt(const string& message)
{//string=a"hello" /*length=5       a[0]=h,a[4]=o*/
	int key_position = 0;
	string secret;
	char help;//����������� ����� ������� ����.
	char help_key;//����� �����.
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{
				help = message[i] - 65; //��������� �����-��������� �� 65.

				help_key = key_word[key_position] - 97;//�������� �������� ����� ����� � ������� ���������.

				help = (help + help_key) % 26; //������� ����������.
				help = help + 65;
				secret = secret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//���� ����� �� ����� �����, �� ����� ��������� ��� ��������, ����� �������� �������.
				{
					key_position = 0;
				}
			}
			else
			{
				help = message[i] - 97;//�������� �����-��������� �� 97.

				help_key = key_word[key_position] - 97;//�������� �������� ����� ����� � ������� ���������.

				help = (help + help_key) % 26; //������� ����������.
				help = help + 97;
				secret = secret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//���� ����� �� ����� �����, �� ����� ��������� ��� ��������, ����� �������� �������.
				{
					key_position = 0;
				}
			};
		}
		else
		{
			secret = secret + message[i];
		};
	};
	return secret;
}

string vigener::decrypt(const string& message)
{
	int key_position = 0;
	string unsecret;
	char help;//�������������� ����� ������� ����.
	char help_key; //����� �����.
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{
				help = message[i] - 65;//��������� �����-��������� �� 65.

				help_key = key_word[key_position] - 97;//�������� �������� ����� ����� � ������� ���������.

				help = (help + 26 - help_key) % 26; //������� ������������.
				help = help + 65;
				unsecret = unsecret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//���� ����� �� ����� �����, �� ����� ��������� ��� ��������, ����� �������� �������.
				{
					key_position = 0;
				}
			}
			else
			{
				help = message[i] - 97;//�������� �����-��������� �� 97.

				help_key = key_word[key_position] - 97; //�������� �������� ����� ����� � ������� ���������.

				help = (help + 26 - help_key) % 26; //������� ������������.
				help = help + 97;
				unsecret = unsecret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//���� ����� �� ����� �����, �� ����� ��������� ��� ��������, ����� �������� �������.
				{
					key_position = 0;
				}
			};
		}
		else
		{
			unsecret = unsecret + message[i];
		};
	};
	return unsecret;
}

playfair::playfair(const string& key)
{
	//���� ������ ���� ������ �� ���������� �������� ����.
	//���������� ����. (������� ��������� � ��������� �����, �������, ����� ����������). !��������� ����� ��������� �� ��������!
	string help_key = key;
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] >= 65 && key[i] <= 90)
		{
			help_key[i] = help_key[i] + 32; //�������� ��������� ����� �� ��������
		}
	};
	for (int i = 0; i < help_key.length(); i++)
	{//������� �������, ����� ���������� � ��������� �����.
		if (help_key[i] >= 97 && help_key[i] <= 122)
		{
			bool povtor = false;
			for (int j = 0; j < key_max_word.length(); j++)
			{
				if (help_key[i] == key_max_word[j])
				{
					povtor = true;
				}
			}
			if (povtor != true)
			{
				index = index + 1;
				key_max_word.resize(index, help_key[i]);
			}
		}
	}
}

string playfair::encrypt(const string& message)
{//��� ��������� ����������� ��������� i=j. 
	string help_secret = message;
	string secret;
	bool test_j = false;
	for (int i = 0; i < key_max_word.length(); i++)
	{
		if (key_max_word[i] == 'j')
		{
			test_j = true;
		};
	};
	const int ROW = 5;
	const int COL = 5;
	int index_key = 0;
	char letter = 'a';
	char matrix[ROW][COL];
	//�������� �������� �������.
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (index_key < key_max_word.length())
			{
				matrix[i][j] = key_max_word[index_key];
				index_key = index_key + 1;
			}
			else
			{//���� ������� � �������.
				bool test;
				do {//����-��: �������� �� ��� ���, ���� �� ������ �����, ������� �� ����������� � �����.
					test = true;
					int new_index_key = 0;

					while (new_index_key < key_max_word.length())
					{//����-����: �������� �� ��� ���, ���� �� ���������� ���� ����.
						if (letter == key_max_word[new_index_key])
						{
							test = false;//������ ����� ��� ����, ����� ��������� ���������.
						};
						new_index_key = new_index_key + 1;
					};

					if (test == false)
					{
						if (letter == 'i')
						{//���� � ����� ����� ���� ����� i.
							letter = letter + 2;//���������� ����� 'j'.
						}
						else
						{
							letter = letter + 1; //��������� �����.
						}
					};
					if (letter == 'i' && test_j == true)
					{//���� � ����� ��� ����� i, �� ���� ����� j.
						test = false;
						letter = letter + 2;//���������� ����� 'j', �.�. �� ����� �����, ��� ��� ���� � �����.
					};
				} while (test == false);
				matrix[i][j] = letter;
				if (letter == 'i')
				{
					letter = letter + 2;//���������� ����� 'j'.
				}
				else
				{
					letter = letter + 1; //��������� �����.
				}
			};
		};
	};
	//�������� ������� �������.

//������� �� �������� � ����������.
	for (int i = 0; i < message.length(); i++)
	{

		int index[4] = {};//���������� ��� �������� �������� ����������������� ����� �������� � �������� �������.//������ 0,2-������ 1 � 2 ��������; ������ 1,3-������� 1 � 2 ��������.
		int index_first = 0;//����� �� �������� ������ ������� ��������.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//����� �������.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
			{
				bigram[0] = message[i] + 32;//������� �� ��������� ����� � ��������.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i];
				index_first = i;
			};
			while (bigram[1] == ' ')//���� �������� �� ��� ���, ���� �� �� ������ ����� ��� �� ������ �� ����� ������.
			{
				if (i < message.length() - 1)
				{//���� � ������ ��� ���� �������.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
						{
							bigram[1] = message[i] + 32;//������� �� ��������� ����� � ��������.
							big_letter[1] = true;
						}
						else
						{
							bigram[1] = message[i];
						};
					};
				}
				else
				{
					i = i + 1;
					bigram[1] = 'x';//��������-���������� �����, ����� � ������ ����������� �����.
					help_secret = help_secret + 'x';
					without_meaning = true;
				};
			};
			//�������� �������.

			//��� ��������� ����������� ��������� i=j, ������ ���� � �������� ������� ���������� 'i', �� � ��� ��� 'j' � ��������.
			if (test_j == true)
			{
				if (bigram[0] == 'i')
				{
					bigram[0] = 'j';
				};
				if (bigram[1] == 'i')
				{
					bigram[1] = 'j';
				};
			}
			else
			{
				if (bigram[0] == 'j')
				{
					bigram[0] = 'i';
				};
				if (bigram[1] == 'j')
				{
					bigram[1] = 'i';
				};
			};

			//����� ��������������� ����� �������� � �������� �������.
			for (int j = 0; j < ROW; j++)
			{
				for (int k = 0; k < COL; k++)
				{
					if (matrix[j][k] == bigram[0])
					{
						index[0] = j; //������ ������ ����� �� ��������.
						index[1] = k; //������� ������ ����� �� ��������.
					};
					if (matrix[j][k] == bigram[1])
					{
						index[2] = j; //������ ������ ����� �� ��������.
						index[3] = k; //������� ������ ����� �� ��������.
					};
				};
			};

			//��������, ����� � ��� ���� ��� ������ ���������� ����� � ����� ���� �� ��������� �������� - �� �� �������������.
			//����� ������ �� ��������� ��������, ��� ����� ��� � ������ ��������, �� � ���������� ��������. 
			//����������.
			if ((index[0] == index[2]) && (index[1] != index[3]))//����� ��������� � ���������� �������, �� � ������ ��������.
			{
				int back = 0;

				//���������� ������ ����� ��������.
				if (big_letter[0] == true)
				{
					back = 32;//���������� ��������� � ��������� ������.
				};
				if (index[1] == 4)
				{//��������� ������-������.
					help_secret[index_first] = matrix[index[0]][0] - back;
				}
				else
				{
					help_secret[index_first] = matrix[index[0]][index[1] + 1] - back;
				};

				//���������� ������ ����� ��������.
				back = 0;
				if (big_letter[1] == true)
				{
					back = 32;//���������� ��������� � ��������� ������.
				};
				if (index[3] == 4)
				{//��������� ������-������.
					help_secret[i] = matrix[index[2]][0] - back;
				}
				else
				{
					help_secret[i] = matrix[index[2]][index[3] + 1] - back;
				};
			}
			else
			{
				if ((index[0] != index[2]) && (index[1] == index[3]))//����� ��������� � ������ ��������, �� � ���������� ��������.		
				{
					int back = 0;
					//���������� ������ ����� ��������.
					if (big_letter[0] == true)
					{
						back = 32;//���������� ��������� � ��������� ������.
					};
					if (index[0] == 4)
					{//��������� ����-������.
						help_secret[index_first] = matrix[0][index[1]] - back;
					}
					else
					{
						help_secret[index_first] = matrix[index[0] + 1][index[1]] - back;
					};

					//���������� ������ ����� ��������.
					back = 0;
					if (big_letter[1] == true)
					{
						back = 32;//���������� ��������� � ��������� ������.
					};

					if (index[2] == 4)
					{//��������� ����-������.
						help_secret[i] = matrix[0][index[3]] - back;
					}
					else
					{
						help_secret[i] = matrix[index[2] + 1][index[3]] - back;
					};
				}
				else
				{
					if ((index[0] != index[2]) && (index[1] != index[3]))//����� ��������� � ������ �������� � � ������ ��������.
					{
						int back = 0;
						//���������� ������ ����� ��������.
						if (big_letter[0] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};
						help_secret[index_first] = matrix[index[0]][index[3]] - back;

						back = 0;
						//���������� ������ ����� ��������.
						if (big_letter[1] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};
						help_secret[i] = matrix[index[2]][index[1]] - back;

					}
					else
					{//����������������� ���� ���������. � ���� ������ ������ �����, ������� ��������� ��� ������ �������. 
						int back = 0;
						//���������� ������ ����� ��������.
						if (big_letter[0] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};
						if (index[0] == 4)
						{//��������� ����-������.
							help_secret[index_first] = matrix[0][index[1]] - back;
						}
						else
						{
							help_secret[index_first] = matrix[index[0] + 1][index[1]] - back;
						};

						//���������� ������ ����� ��������.
						back = 0;
						if (big_letter[1] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};

						if (index[2] == 4)
						{//��������� ����-������.
							help_secret[i] = matrix[0][index[3]] - back;
						}
						else
						{
							help_secret[i] = matrix[index[2] + 1][index[3]] - back;
						};
					};
				};
			};
		};
	};
	secret = help_secret;
	return secret;
}

string playfair::decrypt(const string& message)
{//��� ��������� ����������� ��������� i=j. //� ������������� ��������� �� ������� �������� ������ i �� j (� ��������).
	string help_unsecret = message;
	string unsecret;
	bool test_j = false;
	for (int i = 0; i < key_max_word.length(); i++)
	{
		if (key_max_word[i] == 'j')
		{
			test_j = true;
		};
	};
	const int ROW = 5;
	const int COL = 5;
	int index_key = 0;
	char letter = 'a';
	char matrix[ROW][COL];
	//�������� �������� �������.
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (index_key < key_max_word.length())
			{
				matrix[i][j] = key_max_word[index_key];
				index_key = index_key + 1;
			}
			else
			{//���� ������� � �������.
				bool test;
				do {//����-��: �������� �� ��� ���, ���� �� ������ �����, ������� �� ����������� � �����.
					test = true;
					int new_index_key = 0;

					while (new_index_key < key_max_word.length())
					{//����-����: �������� �� ��� ���, ���� �� ���������� ���� ����.
						if (letter == key_max_word[new_index_key])
						{
							test = false;//������ ����� ��� ����, ����� ��������� ���������.
						};
						new_index_key = new_index_key + 1;
					};

					if (test == false)
					{
						if (letter == 'i')
						{//���� � ����� ����� ���� ����� i.
							letter = letter + 2;//���������� ����� 'j'.
						}
						else
						{
							letter = letter + 1; //��������� �����.
						}
					};
					if (letter == 'i' && test_j == true)
					{//���� � ����� ��� ����� i, �� ���� ����� j.
						test = false;
						letter = letter + 2;//���������� ����� 'j', �.�. �� ����� �����, ��� ��� ���� � �����.
					};
				} while (test == false);
				matrix[i][j] = letter;
				if (letter == 'i')
				{
					letter = letter + 2;//���������� ����� 'j'.
				}
				else
				{
					letter = letter + 1; //��������� �����.
				}
			};
		};
	};
	//�������� ������� �������.

	//������� �� �������� � ������������.
	for (int i = 0; i < message.length(); i++)
	{

		int index[4] = {};//���������� ��� �������� �������� ����������������� ����� �������� � �������� �������.//������ 0,2-������ 1 � 2 ��������; ������ 1,3-������� 1 � 2 ��������.
		int index_first = 0;//����� �� �������� ������ ������� ��������.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//����� �������.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
			{
				bigram[0] = message[i] + 32;//������� �� ��������� ����� � ��������.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i];
				index_first = i;
			};
			while (bigram[1] == ' ')//���� �������� �� ��� ���, ���� �� �� ������ ����� ��� �� ������ �� ����� ������.
			{
				if (i < message.length() - 1)
				{//���� � ������ ��� ���� �������.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
						{
							bigram[1] = message[i] + 32;//������� �� ��������� ����� � ��������.
							big_letter[1] = true;
						}
						else
						{
							bigram[1] = message[i];
						};
					};
				}
			};
			//�������� �������.

			//����� ��������������� ����� �������� � �������� �������.
			for (int j = 0; j < ROW; j++)
			{
				for (int k = 0; k < COL; k++)
				{
					if (matrix[j][k] == bigram[0])
					{
						index[0] = j; //������ ������ ����� �� ��������.
						index[1] = k; //������� ������ ����� �� ��������.
					};
					if (matrix[j][k] == bigram[1])
					{
						index[2] = j; //������ ������ ����� �� ��������.
						index[3] = k; //������� ������ ����� �� ��������.
					};
				};
			};

			//������������.
			if ((index[0] == index[2]) && (index[1] != index[3]))//����� ��������� � ���������� �������, �� � ������ ��������.
			{
				int back = 0;
				//������������ ������ ����� ��������.
				if (big_letter[0] == true)
				{
					back = 32;//���������� ��������� � ��������� ������.
				};
				if (index[1] == 0)
				{//��������� �����-������.
					help_unsecret[index_first] = matrix[index[0]][4] - back;
				}
				else
				{
					help_unsecret[index_first] = matrix[index[0]][index[1] - 1] - back;
				};

				//������������ ������ ����� ��������.
				back = 0;
				if (big_letter[1] == true)
				{
					back = 32;//���������� ��������� � ��������� ������.
				};
				if (index[3] == 0)
				{//��������� �����-������.
					help_unsecret[i] = matrix[index[2]][4] - back;
				}
				else
				{
					help_unsecret[i] = matrix[index[2]][index[3] - 1] - back;
				};
			}
			else
			{
				if ((index[0] != index[2]) && (index[1] == index[3]))//����� ��������� � ������ ��������, �� � ���������� ��������.		
				{
					int back = 0;
					//������������ ������ ����� ��������.
					if (big_letter[0] == true)
					{
						back = 32;//���������� ��������� � ��������� ������.
					};
					if (index[0] == 0)
					{//��������� ����-������.
						help_unsecret[index_first] = matrix[4][index[1]] - back;
					}
					else
					{
						help_unsecret[index_first] = matrix[index[0] - 1][index[1]] - back;
					};

					//������������ ������ ����� ��������.
					back = 0;
					if (big_letter[1] == true)
					{
						back = 32;//���������� ��������� � ��������� ������.
					};

					if (index[2] == 0)
					{//��������� ����-������.
						help_unsecret[i] = matrix[4][index[3]] - back;
					}
					else
					{
						help_unsecret[i] = matrix[index[2] - 1][index[3]] - back;
					};
				}
				else
				{
					if ((index[0] != index[2]) && (index[1] != index[3]))//����� ��������� � ������ �������� � � ������ ��������.
					{
						int back = 0;
						//������������ ������ ����� ��������.
						if (big_letter[0] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};
						help_unsecret[index_first] = matrix[index[0]][index[3]] - back;

						back = 0;
						//������������ ������ ����� ��������.
						if (big_letter[1] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};
						help_unsecret[i] = matrix[index[2]][index[1]] - back;

					}
					else
					{//����������������� ���� ���������. � ���� ������ ������ �����, ������� ��������� ��� ������ �������. 
						int back = 0;
						//������������ ������ ����� ��������.
						if (big_letter[0] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};
						if (index[0] == 0)
						{//��������� ����-������.
							help_unsecret[index_first] = matrix[4][index[1]] - back;
						}
						else
						{
							help_unsecret[index_first] = matrix[index[0] - 1][index[1]] - back;
						};

						//������������ ������ ����� ��������.
						back = 0;
						if (big_letter[1] == true)
						{
							back = 32;//���������� ��������� � ��������� ������.
						};

						if (index[2] == 0)
						{//��������� ����-������.
							help_unsecret[i] = matrix[4][index[3]] - back;
						}
						else
						{
							help_unsecret[i] = matrix[index[2] - 1][index[3]] - back;
						};
					};
				};
			};
		};
	};
	unsecret = help_unsecret;
	if (without_meaning == true)
	{//� ����� ���� ����� ��������. �� ��� �� �����������.
		unsecret.resize(help_unsecret.length() - 1, help_unsecret[help_unsecret.length() - 1]);
	};
	return unsecret;
}

polybius::polybius()
{
	char letter = 'a';
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			english_matrix[i][j] = letter;
			if (letter != 'i')
			{
				letter = letter + 1;
			}
			else
			{
				letter = letter + 2;//���������� j.
			};
		};
	};
}

string polybius::encrypt(const string& message)
{//����� j-�� ���������. ��� ��� i=j - � ������� �� ����� ����� i.
	string secret = message;
	for (int i = 0; i < message.length(); i++)
	{
		bool big_letter = false;
		if (secret[i] >= 65 && secret[i] <= 90)
		{
			secret[i] = secret[i] + 32;//������� �� ��������� ����� � ��������.
			big_letter = true;
		};
		for (int j = 0; j < 5; j++)//������.
		{
			for (int k = 0; k < 5; k++)//�������.
			{

				if (english_matrix[j][k] == secret[i])
				{
					if (j == 4)
					{//���� ���� ������ ������ ���.
						secret[i] = english_matrix[0][k];
						j = 100;
						k = 100;
					}
					else
					{
						secret[i] = english_matrix[j + 1][k];
						j = 100;
						k = 100;
					};//j=k=100-������������ ����� �� ����� ������� �� ������� � ������� � ��������� ����� ���������. 
				};
			};
		};
		if (big_letter == true)
		{
			secret[i] = secret[i] - 32;//����������� � ��������� �����.
		};
	};
	return secret;
}

string polybius::decrypt(const string& message)
{
	string unsecret = message;
	for (int i = 0; i < message.length(); i++)
	{
		bool big_letter = false;
		if (unsecret[i] >= 65 && unsecret[i] <= 90)
		{
			unsecret[i] = unsecret[i] + 32;//������� �� ��������� ����� � ��������.
			big_letter = true;
		};
		for (int j = 0; j < 5; j++)//������.
		{
			for (int k = 0; k < 5; k++)//�������.
			{
				if (english_matrix[j][k] == unsecret[i])
				{
					if (j == 0)
					{//���� ���� ������ ������ ���.
						unsecret[i] = english_matrix[4][k];
						j = 100;
						k = 100;
					}
					else
					{
						unsecret[i] = english_matrix[j - 1][k];
						j = 100;
						k = 100;
					};//j=k=100-������������ ����� �� ����� ������� �� ������� � ������� � ��������� ����� ���������. 
				};
			};
		};
		if (big_letter == true)
		{
			unsecret[i] = unsecret[i] - 32;//����������� � ��������� �����.
		};
	};
	return unsecret;
}

hilla::hilla()
{
	key_matrix[0][0] = 4;
	key_matrix[0][1] = 5;
	key_matrix[1][0] = 3;
	key_matrix[1][1] = 4;
}

string hilla::encrypt(const string& message)
{
	string help_secret = message;
	string secret;
	//������� �� �������� � ����������.
	for (int i = 0; i < message.length(); i++)
	{
		int to_the_range = 97;//��� ������ ������� ����������, ����������, ����� ������� � ����� ���� ������: a..z = 0..25. ���������� � ��� ��������� ����. ����� ������� �� �������, �������� ��������.
		int index_first = 0;//����� �� �������� ������ ������� ��������.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//����� �������.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
			{
				bigram[0] = message[i] + 32 - to_the_range;//������� �� ��������� ����� � �������� � � ��������� 0..25.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i] - to_the_range;//������� � ��������� 0..25.
				index_first = i;
			};
			while (bigram[1] == ' ')//���� �������� �� ��� ���, ���� �� �� ������ ����� ��� �� ������ �� ����� ������.
			{
				if (i < message.length() - 1)
				{//���� � ������ ��� ���� �������.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
						{
							bigram[1] = message[i] + 32 - to_the_range;//������� �� ��������� ����� � �������� � � ��������� 0..25.
							big_letter[1] = true;
						}
						else
						{
							bigram[1] = message[i] - to_the_range;//������� � ��������� 0..25.
						};
					};
				}
				else
				{
					i = i + 1;
					bigram[1] = 'x' - to_the_range;//��������-���������� �����, ����� � ������ ����������� �����.//������� � ��������� 0..25.
					help_secret = help_secret + 'x';
					without_meaning = true;
				};
			};
			//�������� ������� � ��������� � ��������� 0..25.
			//����������.
			int bigram_int[2];
			//������� � �������������� ���� ��� �������� ���������� ����������.
			bigram_int[0] = (int)bigram[0];
			bigram_int[1] = (int)bigram[1];
			//�������� ������� �� ���� (��������� �� ��������� ��������), ����� ������� ������.
			int shifr_bigram_int[2];
			shifr_bigram_int[0] = (bigram_int[0] * key_matrix[0][0] + bigram_int[1] * key_matrix[1][0]) % 26;
			shifr_bigram_int[1] = (bigram_int[0] * key_matrix[0][1] + bigram_int[1] * key_matrix[1][1]) % 26;

			//������������ � ���������� ����.
			bigram[0] = (char)shifr_bigram_int[0];
			bigram[1] = (char)shifr_bigram_int[1];
			//������������ � ��������� ��������
			if (big_letter[0] == true)
			{
				bigram[0] = bigram[0] - 32 + to_the_range;
			}
			else
			{
				bigram[0] = bigram[0] + to_the_range;
			};
			if (big_letter[1] == true)
			{
				bigram[1] = bigram[1] - 32 + to_the_range;
			}
			else
			{
				bigram[1] = bigram[1] + to_the_range;
			};
			help_secret[index_first] = bigram[0];
			help_secret[i] = bigram[1];
		};
	};
	secret = help_secret;
	return secret;
}

string hilla::decrypt(const string& message)
{
	string help_unsecret = message;
	string unsecret;
	//������� �� �������� � ����������.
	for (int i = 0; i < message.length(); i++)
	{
		int to_the_range = 97;//��� ������ ������� ����������, ����������, ����� ������� � ����� ���� ������: a..z = 0..25. ���������� � ��� ��������� ����. ����� ������� �� �������, �������� ��������.
		int index_first = 0;//����� �� �������� ������ ������� ��������.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//����� �������.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
			{
				bigram[0] = message[i] + 32 - to_the_range;//������� �� ��������� ����� � �������� � � ��������� 0..25.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i] - to_the_range;//������� � ��������� 0..25.
				index_first = i;
			};
			while (bigram[1] == ' ')//���� �������� �� ��� ���, ���� �� �� ������ ����� ��� �� ������ �� ����� ������.
			{
				if (i < message.length() - 1)
				{//���� � ������ ��� ���� �������.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//���������� �������.
						{
							bigram[1] = message[i] + 32 - to_the_range;//������� �� ��������� ����� � �������� � � ��������� 0..25.
							big_letter[1] = true;
						}
						else
						{
							bigram[1] = message[i] - to_the_range;//������� � ��������� 0..25.
						};
					};
				}
				else
				{
					i = i + 1;
					bigram[1] = 'x' - to_the_range;//��������-���������� �����, ����� � ������ ����������� �����.//������� � ��������� 0..25.
					help_unsecret = help_unsecret + 'x';
					without_meaning = true;
				};
			};
			//�������� ������� � ��������� � ��������� 0..25.
			//������������.
			int obratnay_key_matrix[2][2];
			//������-������������ ������� ����� 1. ������ �������� ������� �������� ��������� �������.
			obratnay_key_matrix[0][0] = key_matrix[1][1];
			obratnay_key_matrix[0][1] = -1 * key_matrix[0][1];
			obratnay_key_matrix[1][0] = -1 * key_matrix[1][0];
			obratnay_key_matrix[1][1] = key_matrix[0][0];
			int shifr_bigram_int[2];
			//������� � �������������� ���� ��� �������� ���������� ����������.
			shifr_bigram_int[0] = (int)bigram[0];
			shifr_bigram_int[1] = (int)bigram[1];
			//�������� ������� �� ���� (��������� �� ��������� ��������), ����� ������� ������.
			int bigram_int[2];
			bigram_int[0] = (shifr_bigram_int[0] * obratnay_key_matrix[0][0] + shifr_bigram_int[1] * obratnay_key_matrix[1][0]) % 26;
			bigram_int[1] = (shifr_bigram_int[0] * obratnay_key_matrix[0][1] + shifr_bigram_int[1] * obratnay_key_matrix[1][1]) % 26;

			if (bigram_int[0] < 0)//���� �������� ������������� �����.
			{
				bigram_int[0] = bigram_int[0] + 26;
			};
			if (bigram_int[1] < 0)//���� �������� ������������� �����.
			{
				bigram_int[1] = bigram_int[1] + 26;
			};

			//������������ � ���������� ����.
			bigram[0] = (char)bigram_int[0];
			bigram[1] = (char)bigram_int[1];
			//������������ � ��������� ��������
			if (big_letter[0] == true)
			{
				bigram[0] = bigram[0] - 32 + to_the_range;
			}
			else
			{
				bigram[0] = bigram[0] + to_the_range;
			};
			if (big_letter[1] == true)
			{
				bigram[1] = bigram[1] - 32 + to_the_range;
			}
			else
			{
				bigram[1] = bigram[1] + to_the_range;
			};
			help_unsecret[index_first] = bigram[0];
			help_unsecret[i] = bigram[1];
		};
	};
	unsecret = help_unsecret;
	if (without_meaning == true)
	{//� ����� ���� ����� ��������. �� ��� �� �����������.
		unsecret.resize(help_unsecret.length() - 1, help_unsecret[help_unsecret.length() - 1]);
	};
	return unsecret;
}