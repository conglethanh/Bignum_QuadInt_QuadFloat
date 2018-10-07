#include "stdafx.h"
#include "ProcessFile.h"

void processFileInt(ifstream &finp, ofstream &fout)
{
	string a;
	
	while (!finp.eof())
	{
		getline(finp, a);
		
		vector<string> num = splitString(a);
		
		if (num.size() == 3)
		{
			QInt x(num[2], num[0]);
			if (num[1] == "~")
			{
				~x;
				x.write(fout, num[0]);
			}
			else x.write(fout, num[1]);
		}
		else
		{
			string sign = num[2];
			string type = num[0];
			
			QInt x(num[1], type);
			QInt y(num[3], type);

			if (sign == "+")
			{
				(x + y).write(fout, type);
			}
			else if (sign == "-")
			{
				(x - y).write(fout, type);
			}
			else if (sign == "*")
			{
				(x * y).write(fout, type);
			}
			else if (sign == "/")
			{
				(x / y).write(fout, type);
			}
			else if (sign == "%")
			{
				(x % y).write(fout, type);
			}
			else if (sign == "&")
			{
				(x & y).write(fout, type);
			}
			else if (sign == "|")
			{
				(x | y).write(fout, type);
			}
			else if (sign == "^")
			{
				(x ^ y).write(fout, type);
			}
			else if (sign == ">>")
			{
				int n = atoi(num[3].c_str());
				(x >> n).write(fout, type);
			}
			else if (sign == "<<")
			{
				int n = atoi(num[3].c_str());
				(x << n).write(fout, type);
			}
			else if (sign == "ror")
			{
				int n = atoi(num[3].c_str());
				(x.ror(n)).write(fout, type);
			}
			else if (sign == "rol")
			{
				int n = atoi(num[3].c_str());
				(x.rol(n)).write(fout, type);
			}
		}
	}
}

void processFileFloat(ifstream &finp, ofstream &fout)
{
	string a;

	while (!finp.eof())
	{
		getline(finp, a);

		vector<string> num = splitString(a);

		if (num.size() == 3)
		{
			//chuyển đổi
			QFloat x(num[2],num[0]);

			x.write(fout, num[1]);
		}
		else
		{
			string sign = num[2];
			string type = num[0];
			QFloat x(num[1], num[0]);
			QFloat y(num[3], num[0]);

			if (sign == "+")
			{
				(x + y).write(fout, type);
			}
			else if (sign == "-")
			{
				(x - y).write(fout, type);
			}
			else if (sign == "*")
			{
				(x * y).write(fout, type);
			}
			else if (sign == "/")
			{
				(x / y).write(fout, type);
			}
		}
	}
}

void processConsoleInt(string a)
{
	vector<string> num = splitString(a);

	if (num.size() == 3)
	{
		QInt x(num[2], num[0]);
		if (num[1] == "~")
		{
			~x;
			x.write(cout, num[0]);
		}
		else x.write(cout, num[1]);
	}
	else
	{
		string sign = num[2];
		string type = num[0];

		QInt x(num[1], type);
		QInt y(num[3], type);

		if (sign == "+")
		{
			(x + y).write(cout, type);
		}
		else if (sign == "-")
		{
			(x - y).write(cout, type);
		}
		else if (sign == "*")
		{
			(x * y).write(cout, type);
		}
		else if (sign == "/")
		{
			(x / y).write(cout, type);
		}
		else if (sign == "%")
		{
			(x % y).write(cout, type);
		}
		else if (sign == "&")
		{
			(x & y).write(cout, type);
		}
		else if (sign == "|")
		{
			(x | y).write(cout, type);
		}
		else if (sign == "^")
		{
			(x ^ y).write(cout, type);
		}
		else if (sign == ">>")
		{
			int n = atoi(num[3].c_str());
			(x >> n).write(cout, type);
		}
		else if (sign == "<<")
		{
			int n = atoi(num[3].c_str());
			(x << n).write(cout, type);
		}
		else if (sign == "ror")
		{
			int n = atoi(num[3].c_str());
			(x.ror(n)).write(cout, type);
		}
		else if (sign == "rol")
		{
			int n = atoi(num[3].c_str());
			(x.rol(n)).write(cout, type);
		}
	}
}

void processConsoleFloat(string a)
{
	vector<string> num = splitString(a);

	if (num.size() == 3)
	{
		//chuyển đổi
		QFloat x(num[2], num[0]);

		x.write(cout, num[1]);
	}
	else
	{
		string sign = num[2];
		string type = num[0];
		QFloat x(num[1], num[0]);
		QFloat y(num[3], num[0]);

		if (sign == "+")
		{
			(x + y).write(cout, type);
		}
		else if (sign == "-")
		{
			(x - y).write(cout, type);
		}
		else if (sign == "*")
		{
			(x * y).write(cout, type);
		}
		else if (sign == "/")
		{
			(x / y).write(cout, type);
		}
	}
}
