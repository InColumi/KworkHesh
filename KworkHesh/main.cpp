#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const long int _p = 1000000007; // число p 100 000 000 007
const long long int _x = 263;

/// <summary>
/// Метод деления по модулю
/// </summary>
/// <param name="a">число</param>
/// <param name="p">модуль, по которому нужно делить</param>
/// <returns>число по модулю p</returns>
long long int getMod(long long int a, long long int p)
{
	return (a >= 0) ? a % p : p + (a % p); // если отрицательное число, тогда добавляет еще модуль, чтобы избавиться от отрицательности
}

/// <summary>
/// Метод формирования хеш кода
/// </summary>
/// <param name="line">срока с текстом</param>
/// <param name="m">размер хеш-таблицы</param>
/// <returns>хеш-код</returns>
long int getHashCode(string line, int m)
{
	long long int sum = 0; // сумма для числа
	long long int xK = 1; // первое значение Х, 
	for (size_t i = 0; i < line.size(); i++)
	{
		sum += (int)line[i] * xK; // формула, как в задании
		xK = getMod(xK * _x, _p); // умножаем xK на наш X, чтобы получить следующую степень XK. И берем модуль в случае, если число больше P
	}

	return getMod(getMod(sum, _p), m); // берем модуль от суммы оп Р и берем модуль по M(Размер таблицы)
}

/// <summary>
/// Метод добавления в начало ячейки
/// </summary>
/// <param name="items">ячейка со строкамя</param>
/// <param name="item">строка, которую нужно добавить</param>
void pushFront(vector<string>& items, string item)
{
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i] == item) // Проверяем есть ли такая же строка в ячейке. ЕСли есть, то ничего не делаем.
		{
			return;
		}
	}

	vector<string> newItems; // новая ячейка
	newItems.push_back(item); // добавляем новую строку на первое место
	for (size_t i = 0; i < items.size(); i++)
	{
		newItems.push_back(items[i]); // добавляем все остальные строки, если были 
	}
	items = newItems; // присваиваем старой ячейке новую
}


/// <summary>
/// Метод удаления строки из ячейки
/// </summary>
/// <param name="items">ячейка со строками</param>
/// <param name="item">строка для удаления</param>
void remove(vector<string>& items, string item)
{
	size_t index = -1; // значение индекса для поиска строки по умолчанию
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i] == item) // если нашли строку в ячейке
		{
			index = i; // сохраняем индекс, чтобы потом удалить
			break;
		}
	}
	if (index == -1) // если индекс не изменился, то просо выходим. Так как такой строки нет в ячейке и удалять ничего не нужно
	{
		return;
	}

	std::vector<string>::iterator it = items.begin(); // объявляем итератор и присваиваем ему начало вектора
	std::advance(it, index); // удаляем строку из ячейки
	items.erase(it); // Обновяем ячейку
}

int main()
{
	setlocale(LC_ALL, "rus");

	std::ofstream out; // создаем объект для записи в файл
	out.open("output.txt"); // открываем файл

	int sizeTable; // размер таблицы
	int countRequest; // кол-во запросов
	string command; // команда
	string line; // строка текста

	cin >> sizeTable; // вводим размер таблицы
	cin >> countRequest; // вводим кол-во запросов

	vector<vector<string>> hashTable(sizeTable); // выделяем таблицу размером sizeTable

	int hashCode; // переменная для хранения хеш-кода
	while (countRequest > 0) // если кол-во запросов больше нуля, то продолжаем считывать команды
	{
		cin >> command; // считываем команду
		cin >> line;// считываем строку
		if (command == "add") // если команда равна add
		{
			hashCode = getHashCode(line, sizeTable); // вычисляем хеш-код
			pushFront(hashTable[hashCode], line); // добавялем его в начало
		}
		else if (command == "del") // если команда равна del
		{
			hashCode = getHashCode(line, sizeTable);// вычисляем хеш-код
			remove(hashTable[hashCode], line); // удаляем, если есть такая строка
		}
		else if (command == "find") // если команда равна find
		{
			hashCode = getHashCode(line, sizeTable);// вычисляем хеш-код
			bool isExist = false; // если существует
			for (size_t i = 0; i < hashTable[hashCode].size(); i++)
			{
				if (hashTable[hashCode][i] == line) // если в ячейке под хеш-кодом есть строка, что мы ввели
				{
					out << "yes\n"; // говорим, что есть
					isExist = true; // меняем флаг, что такая строка есть
					break;
				}
			}
			if (isExist == false) // если флаг не изменился, то выводим, что нет.
			{
				out << "no\n";
			}
		}
		else if (command == "check")// если команда равна check
		{
			int index = stoi(line); // конвертируем ввод строки в число
			size_t size = hashTable[index].size(); // узнаем размер ячейки таблицы под индком, который ввели
			if (size == 0) // если размер ячейки 0, то очевидно, что там ничего нет и мы просто выводим пустую строку
			{
				out << "";
			}
			else
			{
				for (size_t i = 0; i < hashTable[index].size() - 1; i++) // -1 чтобы не выводить последнюю строку, так как в месте с ней выведется лишний пробел
				{
					out << hashTable[index][i] << ' '; // выводим все строки в введенной ячейке
				}
				out << hashTable[index][hashTable[index].size() - 1]; // выводим последююи строку в ячейке
			}
			
			out << "\n"; // перевод на новую строку
		}
		--countRequest;  // уменьшаем кол-во запросов на 1
	}
	out.close(); // закрываем файл с ответом
	system("pause");
	return 0;
}