#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class matrix_t {

	int **data;
	unsigned int rows;
	unsigned int columns;

public:
	matrix_t add(matrix_t & other) {
		if (!(rows == other.rows && columns == other.columns))
		{
			cout << "An error has occured while reading input data.\n";
			exit(0);
		}
		matrix_t res;
		res.rows = rows;
		res.columns = columns;

		res.data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			res.data[i] = new int[columns];
			for (unsigned int j = 0; j < columns; ++j) {
				res.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return res;
	}
	matrix_t sub(matrix_t & other) {
		if (!(rows == other.rows && columns == other.columns))
		{
			cout << "An error has occured while reading input data.\n";
			exit(0);
		}
		matrix_t res;
		res.rows = rows;
		res.columns = columns;

		res.data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			res.data[i] = new int[columns];
			for (unsigned int j = 0; j < columns; ++j) {
				res.data[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return res;
	}
	matrix_t mul(matrix_t & other) {
		if (columns != other.rows)
		{
			cout << "An error has occured while reading input data.\n";
			exit(0);
		}
		matrix_t res;
		res.rows = rows;
		res.columns = other.columns;

		res.data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			res.data[i] = new int[columns];
			for (unsigned int j = 0; j < other.columns; ++j) {
				res.data[i][j] = 0;
				for (int k = 0; k < columns; k++)
					res.data[i][j] += (data[i][k] * other.data[k][j]);
			}
		}
			return res;
	}
	matrix_t trans(matrix_t & other) {
		matrix_t res;
		res.rows = columns;
		res.columns = rows;
		res.data = new int *[columns];
		for (unsigned int i = 0; i < columns; ++i) {
			res.data[i] = new int[rows];
			for (unsigned int j = 0; j < rows; ++j) {
				res.data[i][j] = data[j][i];
			}
		}
		return res;
	}
	
	ifstream & read(ifstream & stream) {
		string line, str;
		getline(stream, line);
		int rows, columns;
		char symbol;

		if (stream >> rows && stream >> symbol && symbol == ',' && stream >> columns);
		else {
			stream.setstate(ios::failbit);
			return stream;
			}
		this->rows = rows;
		this->columns = columns;

		int ** elements = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			elements[i] = new int[columns];
			getline(stream, str);
			for (unsigned int j = 0; j < columns; ++j) {
				if (!(stream >> elements[i][j])) {
					stream.setstate(ios::failbit);
					return stream;
				}
			}
		}
		
		data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			data[i] = new int[columns];
			for (unsigned int j = 0; j < columns; ++j) {
				data[i][j] = elements[i][j];
			}
		}

		for (unsigned int i = 0; i < rows; ++i) {
			delete[] elements[i];
		}
		delete[] elements;
		return stream;
	}
	ostream & write(ostream & stream) {
		stream << endl;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				stream << data[i][j] << ' ';
			}
			stream << endl;
		}
		return stream;
	}
};

void finput()
{
	ofstream fout;
	fout.open("A.txt");
	fout << "A.txt\n3, 3\n2 2 2\n2 2 2\n2 2 2";
	fout.close();

	fout.open("B.txt");
	fout << "B.txt\n3, 3\n1 1 1\n1 1 1\n1 1 1";
	fout.close();

	fout.open("C.txt");
	fout << "C.txt\n3, 3\n1 2 3\n4 5 6\n7 8 9";
	fout.close();

	fout.open("D.txt");
	fout << "D.txt\n3, 2\n1 2\n4 5\n7 8";
	fout.close();
}

int main() {

	finput();
	unsigned int num;
	char op;
	string str, name1;
	matrix_t A, B, res;

	getline(cin, str);

	for (num = 0; (str[num] != ' ') && (str[num] != '+') && (str[num] != '-') && (str[num] != '*'); num++)
	{
		name1 = name1 + str[num];
	}
	for (; (str[num] != '+') && (str[num] != '-') && (str[num] != '*') && (str[num] != 'T'); num++);
	op = str[num];
	if (op != 'T')
	{
		string name2;
		num++;
		while (str[num] == ' ') num++;
		for (; num < str.length(); num++)
		{
			name2 += str[num];
		}

		ifstream fin2;
		fin2.open(name2);
		if (!fin2.is_open())
		{
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
		if (!B.read(fin2))
		{
			cout << "An error has occured while reading input data.\n";
			return 0;
		}
		fin2.close();
	}

	ifstream fin1;
	fin1.open(name1);
	if (!fin1.is_open())
	{
		cout << "An error has occured while reading input data.\n";
		return 0;
	}
	if (!A.read(fin1))
	{
		cout << "An error has occured while reading input data.\n";
		return 0;
	}

	switch (op) {
	case '+': 
		res = A.add(B);
		break;
	case '-': 
		res = A.sub(B);
		break;
	case '*': 
		res = A.mul(B);
		break;
	case 'T': 
		res = A.trans(B);
		break; 
	default: 
		cout << "An error has occured while reading input data.\n";
	}
	res.write(cout);
	return 0;
}
