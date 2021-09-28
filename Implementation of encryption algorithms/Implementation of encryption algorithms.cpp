//Святченко Артём Андреевич КТСО-03-20

#include <iostream>
#include <fstream> //библиотека для работы с файлами.
#include <string> 
#include "encryption.h"
using namespace std;

/*Таблица кодировки ASCII
32-пробел;
65-90-заглавные английские буквы;
97-122-строчные английские буквы.
*/


int main()
{
	string str; //переменная, которая будет хранить сообщение из файла.
	////////////////////////////////////////////////////////  Работа с файлом. Открытие и чтение данных. 
	cout << "***************************************************************" << endl;

	string namefile = "TEXT.txt";  //Переменная, хранящая путь до файла.
	ifstream fin;
	fin.open(namefile); //открываем файл.

	if (!fin.is_open()) //проверка на то, смогли ли мы открыть наш файл.
	{
		cout << "File open error." << endl;
		cout << "The program is shutting down. Please create a file ''TEXT.txt''." << endl << endl;
		cout << "***************************************************************" << endl;
		return 0;//Завершаем работу программы.
	}
	else
	{
		cout << "The file is open." << endl << endl;
		while (!fin.eof()) //Цикл работает до тех пор, пока не дойдет до конца файла.
		{
			getline(fin, str); //считывает данные из файла построчно.
		};
		if (str.empty())//Проверка на пустую строку.
		{
			cout << "File is empty." << endl;
			cout << "The program is shutting down. Please enter a message for encryption in the file ''TEXT.txt''." << endl;
			cout << "The file is closed." << endl << endl;
			cout << "***************************************************************" << endl;
			fin.close(); //закрываем файл.
			return 0;//Завершаем работу программы.
		}
		else
		{
			cout << "The text to be encrypted:" << endl;
			cout << str << endl << endl;; // Выводим исходное сообщение, которое будем шифровать.
		}
	};
	cout << "The file is closed." << endl << endl;
	fin.close(); //закрываем файл.
	cout << "***************************************************************" << endl;
	////////////////////////////////////////////////////////////// ШИФР ЦЕЗАРЯ  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ceasar cipher_ceasar; //Объект класса шифрования методом Цезаря ( https://ru.wikipedia.org/wiki/%D0%A8%D0%B8%D1%84%D1%80_%D0%A6%D0%B5%D0%B7%D0%B0%D1%80%D1%8F )

	string DecryptTextCesar = cipher_ceasar.encrypt(str);               //зашифровали строку шифром Цезаря
	string EncryptTextCesar = cipher_ceasar.decrypt(DecryptTextCesar);  //дешифровали зашифрованную строку
												  /*Вывод в консоль*/
	cout << "encrypt text method's Ceasar: " << DecryptTextCesar << endl;
	cout << "decrypt text method's Ceasar: " << EncryptTextCesar << endl << endl;


	////////////////////////////////////////////////////////////// АФИННЫЙ ШИФР //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	affine cipher_affine; //Объект класса шифрования аффинным методом ( https://ru.wikipedia.org/wiki/%D0%90%D1%84%D1%84%D0%B8%D0%BD%D0%BD%D1%8B%D0%B9_%D1%88%D0%B8%D1%84%D1%80 )

	string DecryptTextAffine = cipher_affine.encrypt(str);                //зашифровали строку аффинным шифром
	string EncryptTextAffine = cipher_affine.decrypt(DecryptTextAffine);  //дешифровали зашифрованную строку
												  /*Вывод в консоль*/
	cout << "encrypt text method's Affine: " << DecryptTextAffine << endl;
	cout << "decrypt text method's Affine: " << EncryptTextAffine << endl << endl;


	/////////////////////////////////////////////////////////////////// ШИФР ВИЖЕНЕРА  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vigener cipher_vigener; //Объект класса шифрования методом Виженера ( https://ru.wikipedia.org/wiki/%D0%A8%D0%B8%D1%84%D1%80_%D0%92%D0%B8%D0%B6%D0%B5%D0%BD%D0%B5%D1%80%D0%B0 )

	string DecryptTextVigener = cipher_vigener.encrypt(str);				//зашифровали строку шифром Виженера
	string EncryptTextVigener = cipher_vigener.decrypt(DecryptTextVigener); //дешифровали зашифрованную строку
						/* вывод в консоль */
	cout << "encrypt text method's Vigener: " << DecryptTextVigener << endl;
	cout << "decrypt text method's Vigener: " << EncryptTextVigener << endl << endl;


	/////////////////////////////////////////////////////////////////////////// ШИФР ПЛЕЙФЕРА //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	playfair cipher_playfair; //Объект класса шифрования методом Плейфера ( https://ru.wikipedia.org/wiki/%D0%A8%D0%B8%D1%84%D1%80_%D0%9F%D0%BB%D0%B5%D0%B9%D1%84%D0%B5%D1%80%D0%B0 )

	string DecryptTextPlayfire = cipher_playfair.encrypt(str);				     //зашифровали строку шифром Плейфера
	string EncryptTextPlayfire = cipher_playfair.decrypt(DecryptTextPlayfire);   //дешифровали зашифрованную строку
						 /* вывод в консоль */
	cout << "encrypt text method's Playfair: " << DecryptTextPlayfire << endl;
	cout << "decrypt text method's Playfiar: " << EncryptTextPlayfire << endl << endl;


	/////////////////////////////////////////////////////////////////////////////// ШИФР ПОЛИБИЯ /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	polybius cipher_polybiy; //Объект класса шифрования методом Полибия ( https://ru.wikipedia.org/wiki/%D0%9A%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82_%D0%9F%D0%BE%D0%BB%D0%B8%D0%B1%D0%B8%D1%8F )

	string DecryptTextPolybiy = cipher_polybiy.encrypt(str);				//зашифровали строку методом Полибия
	string EncryptTextPolibiy = cipher_polybiy.decrypt(DecryptTextPolybiy); //дешифровали зашифрованную строку
							/* вывод в консоль */
	cout << "encrypt text method's Polybiy: " << DecryptTextPolybiy << endl;
	cout << "decrypt text method's Polybiy: " << EncryptTextPolibiy << endl << endl;


	/////////////////////////////////////////////////////////////////////////////// ШИФР Хилла /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hilla cipher_hilla; //Объект класса шифрования методом Хилла ( https://ru.wikipedia.org/wiki/%D0%A8%D0%B8%D1%84%D1%80_%D0%A5%D0%B8%D0%BB%D0%BB%D0%B0 )

	string DecryptTextHilla = cipher_hilla.encrypt(str);			    //зашифровали строку шифром Хилла
	string EncryptTextHilla = cipher_hilla.decrypt(DecryptTextHilla);   //дешифровали зашифрованную строку
							/* вывод в консоль */
	cout << "encrypt text method's Hilla: " << DecryptTextHilla << endl;
	cout << "decrypt text method's Hilla: " << EncryptTextHilla << endl << endl;


	cout << "***************************************************************\n";
	/* вывод результатов шифрования и дешифрования в файл*/

	string namefileout = "encryption and decryption.txt";  //Переменная, хранящая путь до файла.
	ofstream fout;
	fout.open(namefileout);

	if (!fout.is_open()) //проверка на то, смогли ли мы открыть наш файл.
	{
		cout << "File open error." << endl;
	}
	else
	{
		cout << "The file is open." << endl;
		fout << "***************************************************************\n";
		fout << "encrypt text method's Ceasar: " << DecryptTextCesar << endl;
		fout << "decrypt text method's Ceasar: " << EncryptTextCesar << endl << endl;
		fout << "encrypt text method's Affine: " << DecryptTextAffine << endl;
		fout << "decrypt text method's Affine: " << EncryptTextAffine << endl << endl;
		fout << "encrypt text method's Vigener: " << DecryptTextVigener << endl;
		fout << "decrypt text method's Vigener: " << EncryptTextVigener << endl << endl;
		fout << "encrypt text method's Playfair: " << DecryptTextPlayfire << endl;
		fout << "decrypt text method's Playfiar: " << EncryptTextPlayfire << endl << endl;
		fout << "encrypt text method's Polybiy: " << DecryptTextPolybiy << endl;
		fout << "decrypt text method's Polybiy: " << EncryptTextPolibiy << endl << endl;
		fout << "encrypt text method's Hilla: " << DecryptTextHilla << endl;
		fout << "decrypt text method's Hilla: " << EncryptTextHilla << endl << endl;
		fout << "***************************************************************\n";
		cout << "Data has been successfully written to file." << endl;
	};
	fout.close(); //закрываем файл.
	cout << "The file is closed." << endl << endl;
	cout << "***************************************************************\n";


	return 0;
}