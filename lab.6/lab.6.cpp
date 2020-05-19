#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cctype>
#include <wchar.h>
using namespace std;
#pragma warning(disable : 4996)
char company[20][100] = { "Samsung","Sony","LG","Vizio","TCL","Hisence","Panasonic" };
char firstnames[20][100] = { "Amelia","Alister","Myrtle","Fergus","Agatha","Piers","William","Olivia","James"};
char lastnames[20][100] = { "Smith","Johnson","Williams","Jones","Brown","Miller","Wilson","Taylor","Thomas"};
FILE* f_in, * f_out;
struct TV
{
	char name[100]="";
	int diagonal;
	int price;
	void SetFullInfo() 
	{
		strcat(name, company[rand() % 8]);
		diagonal = rand() % 80 + 20;
		price = rand() % (240 + 50) * 10;
		if (diagonal > 70)price += 500;
	}
	void OutFullInfo(FILE* f_out) {
		fwrite(&company, sizeof(char), 1, f_out);
		fwrite(&diagonal, sizeof(short), 1, f_out);
		fwrite(&price, sizeof(int), 1, f_out);
	}
	void PrintInfo()
	{
		string out = "";
		out += "Company: ";
		out += name;
		out += "\n";
		out += "Diagonal: " + to_string(diagonal) + "\n";
		out += "Price: " + to_string(price) + "\n";
		cout<< out;
	}
};
void InitOfArray(TV* array, int* size)
{
	for (size_t i = 0; i < *size; i++)
	{
		(array + i)->SetFullInfo();
	}
}


void PrintSamsung(TV* array, int* size,int k)
{
	for (size_t i = 0; i < *size; i++)
	{
		if (strcmp((array + i)->name, "Samsung")==0 && (array + i)->diagonal >= 32) {
			k++;
		}
	}
	cout << "Quantity of Samsung TVs :" << k << endl;
	k = 0;
	for (size_t i = 0; i < *size; i++)
	{
		if (strcmp((array + i)->name, "Samsung") == 0 && (array + i)->diagonal >= 32) {
			k++;
			cout << k <<" ";
			(array + i)->PrintInfo();
		}
	}
}

void firstlvl() 
{
	int k = 0;
	int size = 0;
	const char* name = "D:\\TVs.txt";
	f_out = fopen(name, "wb");
	cout << "Enter quantity of TVs: ";
	while (!(cin >> size))
	{
		cout << "Wrong input" << endl;
		cin.clear();
		cin.ignore(65535, '\n');
	}
	int* ptrsize = &size;
	TV* array = new TV[size];
	InitOfArray(array, ptrsize);
	fwrite(array, sizeof(TV), size, f_out);
	fclose(f_out);

	delete[] array;

	TV* save = new TV[size];
	f_in = fopen(name, "rb");
	fread(save, sizeof(TV), size, f_in);
	fclose(f_in);

	PrintSamsung(save, ptrsize, k);
}

void secondlvl() 
{
	wchar_t before[10];
	wcscpy(before, L"привет");
	wcout << "Before: " << before << endl;
	const char* name = "D:\\Text.txt";
	f_out = fopen(name , "wb");
	fwrite(before,sizeof(wchar_t),10,f_out);
	fclose(f_out);

	wchar_t after[10];
	f_in = fopen(name, "rb");
	fread(after, sizeof(wchar_t), 10, f_in);
	fclose(f_in);
	for (int i = 0; i < 10; i++)
	{
		after[i] = towupper(after[i]);
	}
	wcout << "After: " << after << endl;
}

struct Name {
	char F[56] = "";
	char I[32] = "";
	void setFullname() {
		strcat(F, firstnames[rand() % 10]);
		strcat(F, lastnames[rand() % 10]);
	}
};
struct Date {
	short day;
	short month;
	short year;
	bool isCorrect();
	void setFulldate() {
		do
		{
			day = rand() % 32;
			month = rand() % 13;
			year = rand() % 21 + 2000;
		} while (!isCorrect());
	}
};
bool Date::isCorrect()
{
	bool result = false;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		if ((day <= 31) && (day > 0))
			result = true;
		break;
	}

	case 4:
	case 6:
	case 9:
	case 11:
	{
		if ((day <= 30) && (day > 0))
			result = true;
		break;
	}

	case 2:
	{
		if (year % 4 != 0)
		{
			if ((day <= 28) && (day > 0))
				result = true;
		}
		else
			if (year % 400 == 0)
			{
				if ((day <= 29) && (day > 0))
					result = true;
			}
			else
				if ((year % 100 == 0) && (year % 400 != 0))
				{
					if ((day == 28) && (day > 0))
						result = true;
				}
				else
					if ((year % 4 == 0) && (year % 100 != 0))
						if ((day <= 29) && (day > 0))
							result = true;
		break;
	}

	default:
		result = false;
	}

	return result;
}
struct buyer
{
	Name person;
	Date buyday;
	int FirstPrice;
	int SecondPrice;
	short discount;
	void SetFullInfo()
	{
		person.setFullname();
		buyday.setFulldate();
		FirstPrice = rand() % 20000;
		SecondPrice = rand() % 20000;
		discount = rand() % 21;
	}
	void PrintInfo() 
	{
		string out = "";
		out += person.F;
		out += "  ";
		out += person.I;
		out += "\n";
		out += "First total cost: " + to_string(FirstPrice) + "\n";
		out += "Second total cost: " + to_string(SecondPrice) + "\n";
		out += "Discount: " + to_string(discount) + "\n";
		cout << out;
	}
};
void InitOfArray(buyer* array, int* size)
{
	for (size_t i = 0; i < *size; i++)
	{
		(array + i)->SetFullInfo();
	}
}
void changeArray(buyer* array, int* size) 
{
	for (size_t i = 0; i < *size; i++)
	{
		if ((array + i)->FirstPrice >= 10000 && (array + i)->SecondPrice >= 10000)
		{
			(array + i)->discount += 7;
		}
	}
}

void thirdlvl() 
{
	int size = 0;
	const char* name = "D:\\Buyers.txt";
	f_out = fopen(name, "wb");
	cout << "Enter quantity of Buyers: ";
	while (!(cin >> size))
	{
		cout << "Wrong input" << endl;
		cin.clear();
		cin.ignore(65535, '\n');
	}
	int* ptrsize = &size;
	buyer* array = new buyer[size];
	InitOfArray(array, ptrsize);
	fwrite(array, sizeof(buyer), size, f_out);
	fclose(f_out);
	cout << endl << "Before:" << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << i + 1 << " ";
		(array + i)->PrintInfo();
	}
	delete[] array;

	buyer* save = new buyer[size];
	f_in = fopen(name, "rb");
	fread(save, sizeof(buyer), size, f_in);
	fclose(f_in);

	changeArray(save, ptrsize);

	f_out = fopen(name, "wb");
	fwrite(save, sizeof(buyer), size, f_out);
	fclose(f_out);

	delete[] save;

	buyer* import = new buyer[size];
	f_in = fopen(name, "rb");
	fread(import, sizeof(buyer), size, f_in);
	fclose(f_in);
	cout << endl << "After:" << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << i + 1 << " ";
		(import + i)->PrintInfo();
	}
}
int main()
{
	setlocale(0, "");
	srand(time(0));

	int a;
	while (true)
	{
		cout << "Numbers of levels are 1 2 3 (0 to exit)\n";
		cin >> a;
		cout << endl;
		switch (a)
		{
		case 1:
			firstlvl();
			break;
		case 2:
			secondlvl();
			break;
		case 3:
			thirdlvl();
			break;
		case 0:
			return(0);
			break;
		default:
			cout << "Incorrect number, try again" << endl;
			break;
		}
	}
}

