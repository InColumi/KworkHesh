#include <iostream>
#include <string>
#include <vector>

using namespace std;

const unsigned long int _p = 1000000007;
const unsigned long int _x = 263;

int getMod(unsigned long int a, unsigned long int p)
{
	return (a >= 0) ? a % p : p + (a % p);
}

unsigned long int getHashCode(string line, int m)
{
	unsigned long int sum = 0;
	unsigned long int xK = 1;
	for (size_t i = 0; i < line.size(); i++)
	{
		sum += getMod(((int)line[i] * xK), _p);
		xK *= _x;
	}

	return getMod(sum, m);
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
	int sizeTable;
	int countRequest;
	string command;
	string line;
	
	cin >> sizeTable;

	cin >> countRequest;
	
	vector<vector<string>> hashTable(sizeTable);

	unsigned int hashCode;
	while (countRequest >= 0)
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
					cout << "yes\n";
					isExist = true;
					break;
				}
			}
			if (isExist == false)
			{
				cout << "no\n";
			}
		}
		else if (command == "check")
		{
			int index = stoi(line);
			size_t size = hashTable[index].size();
			if (size == 0)
			{
				cout << " ";
			}
			for (size_t i = 0; i < hashTable[index].size(); i++)
			{
				cout << hashTable[index][i] << ' ';
			}
			cout << "\n";
		}
		countRequest--;
	}
	system("pause");
	return 0;
}

