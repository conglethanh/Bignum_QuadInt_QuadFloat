// 1612774_1612829_1612842.cpp : Defines the entry point for the console application.
#include "stdafx.h"

#include "QInt.h"
#include "BigNumber.h"
#include "ProcessFile.h"
#include "QFloat.h"

int main(int argc, char** argv)
{
	try
	{
		if (argc < 3)
		{
			cout << "NOT ENOUGH PARAMETERS\n";
			return 0;
		}
		ifstream finp(argv[1]);
		if (finp.fail())
		{
			cout << "NOT OPEN FILE INPUT\n";
			return 0;
		}
		ofstream fout(argv[2]);
		if (fout.fail())
		{
			cout << "NOT OPEN FILE OUTPUT\n";
			return 0;
		}

		string temp;
		int tmp = 0;
		cout << "Chon 1 de thuc hien voi so nguyen:" << endl;
		cout << "Chon 2 de thuc hien voi so thuc:" << endl;
		cin >> tmp;
		cin.ignore();
		switch (tmp)
		{
		case 1:
			cout << "Xu li so nguyen:" << endl;
			processFileInt(finp, fout);
			finp.close();
			fout.close();
			break;
		case 2:
			cout << "Xu li so thuc:" << endl;
			processFileFloat(finp, fout);
			finp.close();
			fout.close();
			break;
		default:
			cout << "CHOOSE FAIL\n";
			break;
		}
	}
	catch (int err)
	{
		if (err == 0)
			cout << "Loi chia so 0!" << endl;
	}
	return 0;
}

