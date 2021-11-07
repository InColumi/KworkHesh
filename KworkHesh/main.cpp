#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const unsigned long int _p = 1000000007;
const unsigned long long int _x = 263;

unsigned long int getHashCode(string line, int m)
{
	unsigned long long int sum = 0;
	unsigned long long int xK = 1;
	for (size_t i = 0; i < line.size(); i++)
	{
		sum += (int)line[i] * xK;
		xK = (xK * _x) % _p;
	}

	return (sum %_p) % m;
}

void pushFront(vector<string>& items, string item)
{
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i] == item)
		{
			return;
		}
	}
	vector<string> newItems;
	newItems.push_back(item);
	for (size_t i = 0; i < items.size(); i++)
	{
		newItems.push_back(items[i]);
	}
	items = newItems;
}

void remove(vector<string>& items, string item)
{
	size_t index = -1;
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i] == item)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return;
	}
	std::vector<string>::iterator it = items.begin();
	std::advance(it, index);
	items.erase(it);
}

int main()
{
	setlocale(LC_ALL, "rus");

	std::ofstream out;
	out.open("output.txt");

	int sizeTable;
	int countRequest;
	string command;
	string line;
	
	cin >> sizeTable;
	cin >> countRequest;
	
	vector<vector<string>> hashTable(sizeTable);

	unsigned int hashCode;
	while (countRequest > 0)
	{
		cin >> command;
		cin >> line;
		if (command == "add")
		{
			hashCode = getHashCode(line, sizeTable);
			pushFront(hashTable[hashCode], line);
		}
		else if (command == "del")
		{
			hashCode = getHashCode(line, sizeTable);
			remove(hashTable[hashCode], line);
		}
		else if (command == "find")
		{
			hashCode = getHashCode(line, sizeTable);
			bool isExist = false;
			for (size_t i = 0; i < hashTable[hashCode].size(); i++)
			{
				if (hashTable[hashCode][i] == line)
				{
					out << "yes\n";
					isExist = true;
					break;
				}
			}
			if (isExist == false)
			{
				out << "no\n";
			}
		}
		else if (command == "check")
		{
			int index = stoi(line);
			size_t size = hashTable[index].size();
			if (size == 0)
			{
				out << " ";
			}
			for (size_t i = 0; i < hashTable[index].size(); i++)
			{
				out << hashTable[index][i] << ' ';
			}
			out << "\n";
		}
		--countRequest;
	}
	system("pause");
	return 0;
}

/* Tests
(этот текст косячит...)
Входные данные.
5
12
add world
add HellO
check 4
find World
find world
del world
check 4
del HellO
add luck
add GooD
check 2
del good

Выходные данные
HellO world
no
yes
HellO
GooD luck

Входные данные.
4
8
add test
add test
find test
del test
find test
find Test
add Test
find Test

Выходные данные
yes
no
no
yes

Пример 3.
Входные данные.
3
12
check 0
find help
add help
add del
add add
find add
find del
del del
find del
check 0
check 1
check 2

Выходные данные

no
yes
yes
no

add help

Sample Input 2:
4
8
add test
add test
find test
del test
find test
find Test
add Test
find Test

Sample Output 2:
yes
no
no
yes

*/
