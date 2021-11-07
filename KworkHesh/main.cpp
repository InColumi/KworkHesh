#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const long int _p = 1000000007; // ����� p 100 000 000 007
const long long int _x = 263;

/// <summary>
/// ����� ������� �� ������
/// </summary>
/// <param name="a">�����</param>
/// <param name="p">������, �� �������� ����� ������</param>
/// <returns>����� �� ������ p</returns>
long long int getMod(long long int a, long long int p)
{
	return (a >= 0) ? a % p : p + (a % p); // ���� ������������� �����, ����� ��������� ��� ������, ����� ���������� �� ���������������
}

/// <summary>
/// ����� ������������ ��� ����
/// </summary>
/// <param name="line">����� � �������</param>
/// <param name="m">������ ���-�������</param>
/// <returns>���-���</returns>
long int getHashCode(string line, int m)
{
	long long int sum = 0; // ����� ��� �����
	long long int xK = 1; // ������ �������� �, 
	for (size_t i = 0; i < line.size(); i++)
	{
		sum += (int)line[i] * xK; // �������, ��� � �������
		xK = getMod(xK * _x, _p); // �������� xK �� ��� X, ����� �������� ��������� ������� XK. � ����� ������ � ������, ���� ����� ������ P
	}

	return getMod(getMod(sum, _p), m); // ����� ������ �� ����� �� � � ����� ������ �� M(������ �������)
}

/// <summary>
/// ����� ���������� � ������ ������
/// </summary>
/// <param name="items">������ �� ��������</param>
/// <param name="item">������, ������� ����� ��������</param>
void pushFront(vector<string>& items, string item)
{
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i] == item) // ��������� ���� �� ����� �� ������ � ������. ���� ����, �� ������ �� ������.
		{
			return;
		}
	}

	vector<string> newItems; // ����� ������
	newItems.push_back(item); // ��������� ����� ������ �� ������ �����
	for (size_t i = 0; i < items.size(); i++)
	{
		newItems.push_back(items[i]); // ��������� ��� ��������� ������, ���� ���� 
	}
	items = newItems; // ����������� ������ ������ �����
}


/// <summary>
/// ����� �������� ������ �� ������
/// </summary>
/// <param name="items">������ �� ��������</param>
/// <param name="item">������ ��� ��������</param>
void remove(vector<string>& items, string item)
{
	size_t index = -1; // �������� ������� ��� ������ ������ �� ���������
	for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i] == item) // ���� ����� ������ � ������
		{
			index = i; // ��������� ������, ����� ����� �������
			break;
		}
	}
	if (index == -1) // ���� ������ �� ���������, �� ����� �������. ��� ��� ����� ������ ��� � ������ � ������� ������ �� �����
	{
		return;
	}

	std::vector<string>::iterator it = items.begin(); // ��������� �������� � ����������� ��� ������ �������
	std::advance(it, index); // ������� ������ �� ������
	items.erase(it); // �������� ������
}

int main()
{
	setlocale(LC_ALL, "rus");

	std::ofstream out; // ������� ������ ��� ������ � ����
	out.open("output.txt"); // ��������� ����

	int sizeTable; // ������ �������
	int countRequest; // ���-�� ��������
	string command; // �������
	string line; // ������ ������

	cin >> sizeTable; // ������ ������ �������
	cin >> countRequest; // ������ ���-�� ��������

	vector<vector<string>> hashTable(sizeTable); // �������� ������� �������� sizeTable

	int hashCode; // ���������� ��� �������� ���-����
	while (countRequest > 0) // ���� ���-�� �������� ������ ����, �� ���������� ��������� �������
	{
		cin >> command; // ��������� �������
		cin >> line;// ��������� ������
		if (command == "add") // ���� ������� ����� add
		{
			hashCode = getHashCode(line, sizeTable); // ��������� ���-���
			pushFront(hashTable[hashCode], line); // ��������� ��� � ������
		}
		else if (command == "del") // ���� ������� ����� del
		{
			hashCode = getHashCode(line, sizeTable);// ��������� ���-���
			remove(hashTable[hashCode], line); // �������, ���� ���� ����� ������
		}
		else if (command == "find") // ���� ������� ����� find
		{
			hashCode = getHashCode(line, sizeTable);// ��������� ���-���
			bool isExist = false; // ���� ����������
			for (size_t i = 0; i < hashTable[hashCode].size(); i++)
			{
				if (hashTable[hashCode][i] == line) // ���� � ������ ��� ���-����� ���� ������, ��� �� �����
				{
					out << "yes\n"; // �������, ��� ����
					isExist = true; // ������ ����, ��� ����� ������ ����
					break;
				}
			}
			if (isExist == false) // ���� ���� �� ���������, �� �������, ��� ���.
			{
				out << "no\n";
			}
		}
		else if (command == "check")// ���� ������� ����� check
		{
			int index = stoi(line); // ������������ ���� ������ � �����
			size_t size = hashTable[index].size(); // ������ ������ ������ ������� ��� ������, ������� �����
			if (size == 0) // ���� ������ ������ 0, �� ��������, ��� ��� ������ ��� � �� ������ ������� ������ ������
			{
				out << "";
			}
			else
			{
				for (size_t i = 0; i < hashTable[index].size() - 1; i++) // -1 ����� �� �������� ��������� ������, ��� ��� � ����� � ��� ��������� ������ ������
				{
					out << hashTable[index][i] << ' '; // ������� ��� ������ � ��������� ������
				}
				out << hashTable[index][hashTable[index].size() - 1]; // ������� ��������� ������ � ������
			}
			
			out << "\n"; // ������� �� ����� ������
		}
		--countRequest;  // ��������� ���-�� �������� �� 1
	}
	out.close(); // ��������� ���� � �������
	system("pause");
	return 0;
}