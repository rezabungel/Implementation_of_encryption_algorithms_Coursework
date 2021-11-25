#include "encryption.h"
//тип класс::метод(параметры) {РЕАЛИЗАЦИЯ}


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
				help = message[i] + key; //сдвигаем на 3
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
				help = message[i] - key; //сдвигаем на 3
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

//Для работы формулы шифрования, необходимо, чтобы индексы у буквы были такими: a..z = 0..25. Аналогично и для заглавных букв. Такие индексы мы получим, выполняя смещение.
string affine::encrypt(const string& message)
{
	string secret;
	char help;
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{//заглавные буквы-смещаемся на 65.
				help = message[i] - 65;
				help = (help * key_a + key_b) % 26; //формула шифрования.
				help = help + 65;
				secret = secret + help;
			}
			else
			{//строчные буквы-смещаемся на 97.
				help = message[i] - 97;
				help = (help * key_a + key_b) % 26; //формула шифрования.
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

//Для работы формулы дешифрования, необходимо, чтобы индексы у буквы были такими: a..z = 0..25. Аналогично и для заглавных букв. Такие индексы мы получим, выполняя смещение.
string affine::decrypt(const string& message)
{
	//вычисяляем мультипликативную инверсию.
	int k = 0;
	for (k; k < 26; k++)
	{
		if ((key_a * k) % 26 == 1)
		{
			break;
		}
	}
	//k-мультипликативная инверсия
	string unsecret;
	char help;
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{//заглавные буквы-смещаемся на 65.
				help = message[i] - 65;
				help = k * (help - key_b + 26) % 26;  //формула дешифрования.
				help = help + 65;
				unsecret = unsecret + help;
			}
			else
			{//строчные буквы-смещаемся на 97.
				help = message[i] - 97;
				help = k * (help - key_b + 26) % 26; //формула дешифрования.
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
	//ключ должен быть только из английских строчных букв.
	//исправляем ключ. (заглавные буквы, пробелы, знаки препинания). !заглавные буквы изменятся на строчные!
	string help_key = key;
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] >= 65 && key[i] <= 90)
		{
			help_key[i] = help_key[i] + 32; //заменяем заглавные буквы на строчные.
		}
	};
	for (int i = 0; i < help_key.length(); i++)
	{//убирает пробелы и знаки препинания.
		if (help_key[i] >= 97 && help_key[i] <= 122)
		{
			index = index + 1;
			key_word.resize(index, help_key[i]);
		}
	}
}

//Для работы формулы шифрования, необходимо, чтобы индексы у буквы были такими: a..z = 0..25. Аналогично и для заглавных букв. Такие индексы мы получим, выполняя смещение.
string vigener::encrypt(const string& message)
{//string=a"hello" /*length=5       a[0]=h,a[4]=o*/
	int key_position = 0;
	string secret;
	char help;//шифрованная буква попадет сюда.
	char help_key;//буква ключа.
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{
				help = message[i] - 65; //заглавные буквы-смещаемся на 65.

				help_key = key_word[key_position] - 97;//смещение строчной буквы ключа к нужному диапазону.

				help = (help + help_key) % 26; //формула шифрования.
				help = help + 65;
				secret = secret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//если дошли до конца ключа, то чтобы применить его повторно, нужно обнулить позицию.
				{
					key_position = 0;
				}
			}
			else
			{
				help = message[i] - 97;//строчные буквы-смещаемся на 97.

				help_key = key_word[key_position] - 97;//смещение строчной буквы ключа к нужному диапазону.

				help = (help + help_key) % 26; //формула шифрования.
				help = help + 97;
				secret = secret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//если дошли до конца ключа, то чтобы применить его повторно, нужно обнулить позицию.
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
	char help;//расшифрованная буква попадет сюда.
	char help_key; //буква ключа.
	for (int i = 0; i < message.length(); i++)
	{
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if (message[i] >= 65 && message[i] <= 90)
			{
				help = message[i] - 65;//заглавные буквы-смещаемся на 65.

				help_key = key_word[key_position] - 97;//смещение строчной буквы ключа к нужному диапазону.

				help = (help + 26 - help_key) % 26; //формула дешифрования.
				help = help + 65;
				unsecret = unsecret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//если дошли до конца ключа, то чтобы применить его повторно, нужно обнулить позицию.
				{
					key_position = 0;
				}
			}
			else
			{
				help = message[i] - 97;//строчные буквы-смещаемся на 97.

				help_key = key_word[key_position] - 97; //смещение строчной буквы ключа к нужному диапазону.

				help = (help + 26 - help_key) % 26; //формула дешифрования.
				help = help + 97;
				unsecret = unsecret + help;
				key_position = key_position + 1;
				if (key_position == key_word.length())//если дошли до конца ключа, то чтобы применить его повторно, нужно обнулить позицию.
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
	//ключ должен быть только из английских строчных букв.
	//исправляем ключ. (убираем повторные и заглавные буквы, пробелы, знаки препинания). !заглавные буквы изменятся на строчные!
	string help_key = key;
	int index = 0;
	for (int i = 0; i < key.length(); i++)
	{
		if (key[i] >= 65 && key[i] <= 90)
		{
			help_key[i] = help_key[i] + 32; //заменяем заглавные буквы на строчные
		}
	};
	for (int i = 0; i < help_key.length(); i++)
	{//убирает пробелы, знаки препинания и повторные буквы.
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
{//для алгоритма применяется допущение i=j. 
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
	//создание ключевой матрицы.
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
			{//ключ занесен в матрицу.
				bool test;
				do {//цикл-до: работает до тех пор, пока не найдет букву, которая не встречается в ключе.
					test = true;
					int new_index_key = 0;

					while (new_index_key < key_max_word.length())
					{//цикл-пока: работает до тех пор, пока не просмотрим весь ключ.
						if (letter == key_max_word[new_index_key])
						{
							test = false;//значит буква уже есть, нужно проверить следующую.
						};
						new_index_key = new_index_key + 1;
					};

					if (test == false)
					{
						if (letter == 'i')
						{//если в нашем ключе была буква i.
							letter = letter + 2;//пропускаем букву 'j'.
						}
						else
						{
							letter = letter + 1; //следующая буква.
						}
					};
					if (letter == 'i' && test_j == true)
					{//если в ключе нет буквы i, но есть буква j.
						test = false;
						letter = letter + 2;//пропускаем букву 'j', т.к. мы точно знаем, что она есть в ключе.
					};
				} while (test == false);
				matrix[i][j] = letter;
				if (letter == 'i')
				{
					letter = letter + 2;//пропускаем букву 'j'.
				}
				else
				{
					letter = letter + 1; //следующая буква.
				}
			};
		};
	};
	//ключевая матрица создана.

//деление на биграммы и шифрование.
	for (int i = 0; i < message.length(); i++)
	{

		int index[4] = {};//используем для хранения индексов месторасположения буквы биграмма в ключевой матрице.//индекс 0,2-строки 1 и 2 биграмма; индекс 1,3-столбцы 1 и 2 биграмма.
		int index_first = 0;//чтобы не потерять индекс первого биграмма.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//поиск биграмм.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
			{
				bigram[0] = message[i] + 32;//переход от заглавной буквы к строчной.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i];
				index_first = i;
			};
			while (bigram[1] == ' ')//цикл работает до тех пор, пока мы не найдем букву или не дойдем до конца строки.
			{
				if (i < message.length() - 1)
				{//если в строке еще есть символы.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
						{
							bigram[1] = message[i] + 32;//переход от заглавной буквы к строчной.
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
					bigram[1] = 'x';//пустышка-присвоится тогда, когда в строке закончились буквы.
					help_secret = help_secret + 'x';
					without_meaning = true;
				};
			};
			//биграмма найдена.

			//для алгоритма применяется допущение i=j, значит если в ключевой матрице содержится 'i', то в ней нет 'j' и наоборот.
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

			//поиск местонахождения буквы биграмма в ключевой таблице.
			for (int j = 0; j < ROW; j++)
			{
				for (int k = 0; k < COL; k++)
				{
					if (matrix[j][k] == bigram[0])
					{
						index[0] = j; //строка первой буквы из биграмма.
						index[1] = k; //столбец первой буквы из биграмма.
					};
					if (matrix[j][k] == bigram[1])
					{
						index[2] = j; //строка второй буквы из биграмма.
						index[3] = k; //столбец второй буквы из биграмма.
					};
				};
			};

			//ситуацию, когда у нас идут две подряд одинаковые буквы и между ними мы вставляем пустышку - мы не рассматриваем.
			//такой случай мы зашифруем способом, как будто они в разных строчках, но в одинаковых столбцах. 
			//шифрование.
			if ((index[0] == index[2]) && (index[1] != index[3]))//буквы находятся в одинаковой строчке, но в разных столбцах.
			{
				int back = 0;

				//шифрование первой буквы биграмма.
				if (big_letter[0] == true)
				{
					back = 32;//необходимо вернуться к заглавным буквам.
				};
				if (index[1] == 4)
				{//смещаться вправо-некуда.
					help_secret[index_first] = matrix[index[0]][0] - back;
				}
				else
				{
					help_secret[index_first] = matrix[index[0]][index[1] + 1] - back;
				};

				//шифрование второй буквы биграмма.
				back = 0;
				if (big_letter[1] == true)
				{
					back = 32;//необходимо вернуться к заглавным буквам.
				};
				if (index[3] == 4)
				{//смещаться вправо-некуда.
					help_secret[i] = matrix[index[2]][0] - back;
				}
				else
				{
					help_secret[i] = matrix[index[2]][index[3] + 1] - back;
				};
			}
			else
			{
				if ((index[0] != index[2]) && (index[1] == index[3]))//буквы находятся в разных строчках, но в одинаковых столбцах.		
				{
					int back = 0;
					//шифрование первой буквы биграмма.
					if (big_letter[0] == true)
					{
						back = 32;//необходимо вернуться к заглавным буквам.
					};
					if (index[0] == 4)
					{//смещаться ниже-некуда.
						help_secret[index_first] = matrix[0][index[1]] - back;
					}
					else
					{
						help_secret[index_first] = matrix[index[0] + 1][index[1]] - back;
					};

					//шифрование второй буквы биграмма.
					back = 0;
					if (big_letter[1] == true)
					{
						back = 32;//необходимо вернуться к заглавным буквам.
					};

					if (index[2] == 4)
					{//смещаться ниже-некуда.
						help_secret[i] = matrix[0][index[3]] - back;
					}
					else
					{
						help_secret[i] = matrix[index[2] + 1][index[3]] - back;
					};
				}
				else
				{
					if ((index[0] != index[2]) && (index[1] != index[3]))//буквы находятся в разных строчках и в разных столбцах.
					{
						int back = 0;
						//шифрование первой буквы биграмма.
						if (big_letter[0] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};
						help_secret[index_first] = matrix[index[0]][index[3]] - back;

						back = 0;
						//шифрование второй буквы биграмма.
						if (big_letter[1] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};
						help_secret[i] = matrix[index[2]][index[1]] - back;

					}
					else
					{//месторасположение букв совпадает. в этом случае возьмём букву, которая находится под нашими буквами. 
						int back = 0;
						//шифрование первой буквы биграмма.
						if (big_letter[0] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};
						if (index[0] == 4)
						{//смещаться ниже-некуда.
							help_secret[index_first] = matrix[0][index[1]] - back;
						}
						else
						{
							help_secret[index_first] = matrix[index[0] + 1][index[1]] - back;
						};

						//шифрование второй буквы биграмма.
						back = 0;
						if (big_letter[1] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};

						if (index[2] == 4)
						{//смещаться ниже-некуда.
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
{//для алгоритма применяется допущение i=j. //в дешифрованном сообщении не удастся поменять нужные i на j (и наоборот).
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
	//создание ключевой матрицы.
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
			{//ключ занесен в матрицу.
				bool test;
				do {//цикл-до: работает до тех пор, пока не найдет букву, которая не встречается в ключе.
					test = true;
					int new_index_key = 0;

					while (new_index_key < key_max_word.length())
					{//цикл-пока: работает до тех пор, пока не просмотрим весь ключ.
						if (letter == key_max_word[new_index_key])
						{
							test = false;//значит буква уже есть, нужно проверить следующую.
						};
						new_index_key = new_index_key + 1;
					};

					if (test == false)
					{
						if (letter == 'i')
						{//если в нашем ключе была буква i.
							letter = letter + 2;//пропускаем букву 'j'.
						}
						else
						{
							letter = letter + 1; //следующая буква.
						}
					};
					if (letter == 'i' && test_j == true)
					{//если в ключе нет буквы i, но есть буква j.
						test = false;
						letter = letter + 2;//пропускаем букву 'j', т.к. мы точно знаем, что она есть в ключе.
					};
				} while (test == false);
				matrix[i][j] = letter;
				if (letter == 'i')
				{
					letter = letter + 2;//пропускаем букву 'j'.
				}
				else
				{
					letter = letter + 1; //следующая буква.
				}
			};
		};
	};
	//ключевая матрица создана.

	//деление на биграммы и дешифрование.
	for (int i = 0; i < message.length(); i++)
	{

		int index[4] = {};//используем для хранения индексов месторасположения буквы биграмма в ключевой матрице.//индекс 0,2-строки 1 и 2 биграмма; индекс 1,3-столбцы 1 и 2 биграмма.
		int index_first = 0;//чтобы не потерять индекс первого биграмма.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//поиск биграмм.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
			{
				bigram[0] = message[i] + 32;//переход от заглавной буквы к строчной.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i];
				index_first = i;
			};
			while (bigram[1] == ' ')//цикл работает до тех пор, пока мы не найдем букву или не дойдем до конца строки.
			{
				if (i < message.length() - 1)
				{//если в строке еще есть символы.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
						{
							bigram[1] = message[i] + 32;//переход от заглавной буквы к строчной.
							big_letter[1] = true;
						}
						else
						{
							bigram[1] = message[i];
						};
					};
				}
			};
			//биграмма найдена.

			//поиск местонахождения буквы биграмма в ключевой таблице.
			for (int j = 0; j < ROW; j++)
			{
				for (int k = 0; k < COL; k++)
				{
					if (matrix[j][k] == bigram[0])
					{
						index[0] = j; //строка первой буквы из биграмма.
						index[1] = k; //столбец первой буквы из биграмма.
					};
					if (matrix[j][k] == bigram[1])
					{
						index[2] = j; //строка второй буквы из биграмма.
						index[3] = k; //столбец второй буквы из биграмма.
					};
				};
			};

			//дешифрование.
			if ((index[0] == index[2]) && (index[1] != index[3]))//буквы находятся в одинаковой строчке, но в разных столбцах.
			{
				int back = 0;
				//дешифрование первой буквы биграмма.
				if (big_letter[0] == true)
				{
					back = 32;//необходимо вернуться к заглавным буквам.
				};
				if (index[1] == 0)
				{//смещаться влево-некуда.
					help_unsecret[index_first] = matrix[index[0]][4] - back;
				}
				else
				{
					help_unsecret[index_first] = matrix[index[0]][index[1] - 1] - back;
				};

				//дешифрование второй буквы биграмма.
				back = 0;
				if (big_letter[1] == true)
				{
					back = 32;//необходимо вернуться к заглавным буквам.
				};
				if (index[3] == 0)
				{//смещаться влево-некуда.
					help_unsecret[i] = matrix[index[2]][4] - back;
				}
				else
				{
					help_unsecret[i] = matrix[index[2]][index[3] - 1] - back;
				};
			}
			else
			{
				if ((index[0] != index[2]) && (index[1] == index[3]))//буквы находятся в разных строчках, но в одинаковых столбцах.		
				{
					int back = 0;
					//дешифрование первой буквы биграмма.
					if (big_letter[0] == true)
					{
						back = 32;//необходимо вернуться к заглавным буквам.
					};
					if (index[0] == 0)
					{//смещаться выше-некуда.
						help_unsecret[index_first] = matrix[4][index[1]] - back;
					}
					else
					{
						help_unsecret[index_first] = matrix[index[0] - 1][index[1]] - back;
					};

					//дешифрование второй буквы биграмма.
					back = 0;
					if (big_letter[1] == true)
					{
						back = 32;//необходимо вернуться к заглавным буквам.
					};

					if (index[2] == 0)
					{//смещаться выше-некуда.
						help_unsecret[i] = matrix[4][index[3]] - back;
					}
					else
					{
						help_unsecret[i] = matrix[index[2] - 1][index[3]] - back;
					};
				}
				else
				{
					if ((index[0] != index[2]) && (index[1] != index[3]))//буквы находятся в разных строчках и в разных столбцах.
					{
						int back = 0;
						//дешифрование первой буквы биграмма.
						if (big_letter[0] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};
						help_unsecret[index_first] = matrix[index[0]][index[3]] - back;

						back = 0;
						//дешифрование второй буквы биграмма.
						if (big_letter[1] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};
						help_unsecret[i] = matrix[index[2]][index[1]] - back;

					}
					else
					{//месторасположение букв совпадает. в этом случае возьмём букву, которая находится над нашими буквами. 
						int back = 0;
						//дешифрование первой буквы биграмма.
						if (big_letter[0] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};
						if (index[0] == 0)
						{//смещаться выше-некуда.
							help_unsecret[index_first] = matrix[4][index[1]] - back;
						}
						else
						{
							help_unsecret[index_first] = matrix[index[0] - 1][index[1]] - back;
						};

						//дешифрование второй буквы биграмма.
						back = 0;
						if (big_letter[1] == true)
						{
							back = 32;//необходимо вернуться к заглавным буквам.
						};

						if (index[2] == 0)
						{//смещаться выше-некуда.
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
	{//в конце есть буквы пустышка. от нее мы избавляемся.
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
				letter = letter + 2;//пропускаем j.
			};
		};
	};
}

string polybius::encrypt(const string& message)
{//Буква j-не шифруется. Так как i=j - в матрицу мы взяли букву i.
	string secret = message;
	for (int i = 0; i < message.length(); i++)
	{
		bool big_letter = false;
		if (secret[i] >= 65 && secret[i] <= 90)
		{
			secret[i] = secret[i] + 32;//переход от заглавной буквы к строчной.
			big_letter = true;
		};
		for (int j = 0; j < 5; j++)//строка.
		{
			for (int k = 0; k < 5; k++)//столбец.
			{

				if (english_matrix[j][k] == secret[i])
				{
					if (j == 4)
					{//ниже этой строки ничего нет.
						secret[i] = english_matrix[0][k];
						j = 100;
						k = 100;
					}
					else
					{
						secret[i] = english_matrix[j + 1][k];
						j = 100;
						k = 100;
					};//j=k=100-спровоцирует выход из цикла прохода по матрице и переход к следующей букве сообщения. 
				};
			};
		};
		if (big_letter == true)
		{
			secret[i] = secret[i] - 32;//возвращение к заглавной букве.
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
			unsecret[i] = unsecret[i] + 32;//переход от заглавной буквы к строчной.
			big_letter = true;
		};
		for (int j = 0; j < 5; j++)//строка.
		{
			for (int k = 0; k < 5; k++)//столбец.
			{
				if (english_matrix[j][k] == unsecret[i])
				{
					if (j == 0)
					{//выше этой строки ничего нет.
						unsecret[i] = english_matrix[4][k];
						j = 100;
						k = 100;
					}
					else
					{
						unsecret[i] = english_matrix[j - 1][k];
						j = 100;
						k = 100;
					};//j=k=100-спровоцирует выход из цикла прохода по матрице и переход к следующей букве сообщения. 
				};
			};
		};
		if (big_letter == true)
		{
			unsecret[i] = unsecret[i] - 32;//возвращение к заглавной букве.
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
	//деление на биграммы и шифрование.
	for (int i = 0; i < message.length(); i++)
	{
		int to_the_range = 97;//Для работы формулы шифрования, необходимо, чтобы индексы у буквы были такими: a..z = 0..25. Аналогично и для заглавных букв. Такие индексы мы получим, выполняя смещение.
		int index_first = 0;//чтобы не потерять индекс первого биграмма.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//поиск биграмм.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
			{
				bigram[0] = message[i] + 32 - to_the_range;//переход от заглавной буквы к строчной и к диапазону 0..25.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i] - to_the_range;//переход к диапазону 0..25.
				index_first = i;
			};
			while (bigram[1] == ' ')//цикл работает до тех пор, пока мы не найдем букву или не дойдем до конца строки.
			{
				if (i < message.length() - 1)
				{//если в строке еще есть символы.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
						{
							bigram[1] = message[i] + 32 - to_the_range;//переход от заглавной буквы к строчной и к диапазону 0..25.
							big_letter[1] = true;
						}
						else
						{
							bigram[1] = message[i] - to_the_range;//переход к диапазону 0..25.
						};
					};
				}
				else
				{
					i = i + 1;
					bigram[1] = 'x' - to_the_range;//пустышка-присвоется тогда, когда в строке закончились буквы.//переход к диапазону 0..25.
					help_secret = help_secret + 'x';
					without_meaning = true;
				};
			};
			//биграмма найдена и приведена к диапазону 0..25.
			//шифрование.
			int bigram_int[2];
			//переход к целочисленному типу для удобства дальнейших вычислений.
			bigram_int[0] = (int)bigram[0];
			bigram_int[1] = (int)bigram[1];
			//умножает биграмм на ключ (умножение по матричным правилам), затем находим модуль.
			int shifr_bigram_int[2];
			shifr_bigram_int[0] = (bigram_int[0] * key_matrix[0][0] + bigram_int[1] * key_matrix[1][0]) % 26;
			shifr_bigram_int[1] = (bigram_int[0] * key_matrix[0][1] + bigram_int[1] * key_matrix[1][1]) % 26;

			//возвращаемся к буквенному типу.
			bigram[0] = (char)shifr_bigram_int[0];
			bigram[1] = (char)shifr_bigram_int[1];
			//возвращаемся в буквенный диапазон
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
	//деление на биграммы и шифрование.
	for (int i = 0; i < message.length(); i++)
	{
		int to_the_range = 97;//Для работы формулы шифрования, необходимо, чтобы индексы у буквы были такими: a..z = 0..25. Аналогично и для заглавных букв. Такие индексы мы получим, выполняя смещение.
		int index_first = 0;//чтобы не потерять индекс первого биграмма.
		char bigram[2] = { ' ',' ' };
		bool big_letter[2] = { false,false };
		//поиск биграмм.
		if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
		{
			if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
			{
				bigram[0] = message[i] + 32 - to_the_range;//переход от заглавной буквы к строчной и к диапазону 0..25.
				big_letter[0] = true;
				index_first = i;
			}
			else
			{
				bigram[0] = message[i] - to_the_range;//переход к диапазону 0..25.
				index_first = i;
			};
			while (bigram[1] == ' ')//цикл работает до тех пор, пока мы не найдем букву или не дойдем до конца строки.
			{
				if (i < message.length() - 1)
				{//если в строке еще есть символы.
					i = i + 1;
					if ((message[i] >= 65 && message[i] <= 90) || (message[i] >= 97 && message[i] <= 122))
					{
						if ((message[i] >= 65 && message[i] <= 90))//уточняющие условие.
						{
							bigram[1] = message[i] + 32 - to_the_range;//переход от заглавной буквы к строчной и к диапазону 0..25.
							big_letter[1] = true;
						}
						else
						{
							bigram[1] = message[i] - to_the_range;//переход к диапазону 0..25.
						};
					};
				}
				else
				{
					i = i + 1;
					bigram[1] = 'x' - to_the_range;//пустышка-присвоется тогда, когда в строке закончились буквы.//переход к диапазону 0..25.
					help_unsecret = help_unsecret + 'x';
					without_meaning = true;
				};
			};
			//биграмма найдена и приведена к диапазону 0..25.
			//дешифрование.
			int obratnay_key_matrix[2][2];
			//допуск-определитель матрицы равен 1. значит обратная матрица найдется следующим образом.
			obratnay_key_matrix[0][0] = key_matrix[1][1];
			obratnay_key_matrix[0][1] = -1 * key_matrix[0][1];
			obratnay_key_matrix[1][0] = -1 * key_matrix[1][0];
			obratnay_key_matrix[1][1] = key_matrix[0][0];
			int shifr_bigram_int[2];
			//переход к целочисленному типу для удобства дальнейших вычислений.
			shifr_bigram_int[0] = (int)bigram[0];
			shifr_bigram_int[1] = (int)bigram[1];
			//умножает биграмм на ключ (умножение по матричным правилам), затем находим модуль.
			int bigram_int[2];
			bigram_int[0] = (shifr_bigram_int[0] * obratnay_key_matrix[0][0] + shifr_bigram_int[1] * obratnay_key_matrix[1][0]) % 26;
			bigram_int[1] = (shifr_bigram_int[0] * obratnay_key_matrix[0][1] + shifr_bigram_int[1] * obratnay_key_matrix[1][1]) % 26;

			if (bigram_int[0] < 0)//если получили отрицательное число.
			{
				bigram_int[0] = bigram_int[0] + 26;
			};
			if (bigram_int[1] < 0)//если получили отрицательное число.
			{
				bigram_int[1] = bigram_int[1] + 26;
			};

			//возвращаемся к буквенному типу.
			bigram[0] = (char)bigram_int[0];
			bigram[1] = (char)bigram_int[1];
			//возвращаемся в буквенный диапазон
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
	{//в конце есть буква пустышка. от нее мы избавляемся.
		unsecret.resize(help_unsecret.length() - 1, help_unsecret[help_unsecret.length() - 1]);
	};
	return unsecret;
}