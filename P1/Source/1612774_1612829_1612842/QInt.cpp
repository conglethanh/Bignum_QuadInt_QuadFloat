#include "stdafx.h"
#include "QInt.h"


QInt::QInt()
{
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
}

QInt::QInt(string value, string type)
{
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0;
	}
	bool isNegative = false;
	value = convertString(value, type, isNegative);
	this->uploadData(value, type, isNegative);
}

bool QInt::is0()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->data[i] != 0)
			return false;
	}
	return true;
}

string QInt::convertStringDecToBin(string decimal)
{
	string result = "";

	if (decimal == "0")
		return result;

	string temp = decimal;
	while (temp != "1")
	{
		if ((temp[temp.length() - 1] - '0') % 2 == 1)
		{
			result = "1" + result;
		}
		else
			result = "0" + result;
		temp = divideBy2(temp);
	}
	result = "1" + result;
	return result;
}

string QInt::convertStringHexToBin(string hex)
{
	string result = "";

	int len = hex.length();
	string tempBin[]{ "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	char tempHex[]{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (tempHex[j] == hex[i])
			{
				result += tempBin[j];
			}
		}
	}
	return result;
}

void QInt::uploadData(string inString, string type, bool isNegative)
{
	string outString;
	if (type == "10")
	{
		string bin = convertStringDecToBin(inString);
		outString = bin;
	}
	else if (type == "2")
	{
		outString = inString;
	}
	else if (type == "16")
	{
		string bin = convertStringHexToBin(inString);
		outString = bin;
	}

	string temp = outString;

	int k = 3;

	while (outString.length() > 32)
	{
		temp = outString.substr(outString.length() - 32, 32);
		
		outString = outString.erase(outString.length() - 32, 32);

		for (int i = 31; i >= 0; i--)
		{
			int x = 1;
			if (temp[i] == '1') {
				x = x << 31 - i;
				this->data[k] = this->data[k] | x;
			}
		}
		k--;
	}

	temp = outString;
	int lenBin = outString.length();
	for (int i = lenBin - 1; i >= 0; i--)
	{
		int x = 1;
		if (temp[i] == '1')
		{
			x = x << lenBin - i - 1;
			this->data[k] = this->data[k] | x;
		}
	}

	if (isNegative == true && type == "10")
	{
		~(*this);
		QInt one;
		one.uploadData("1", "10", false);
		*this = *this + one;
	}
}

int QInt::getBit(int pos)
{
	return (data[pos / 32] >> (31 - pos % 32)) & 1;
}

void QInt::setBit(int value, int pos)
{
	if (value == 1)
		data[pos / 32] |= (1 << (31 - pos % 32));
	else
		data[pos / 32] &= ~(1 << (31 - pos % 32));
}

string QInt::getBin()
{
	string result;
	for (int i = 0; i < 128; i++)
	{
		if (this->getBit(i) == 1)
		{
			result += "1";
		}
		else result += "0";
	}
	return result;
}

string QInt::getDec()
{
	string result = "0";

	for (int i = 1; i < 128; i++)
	{
		if (this->getBit(i) == 1)
		{
			result = add(result, powerBig("2", 127 - i));
		}
	}

	if (this->getBit(0) == 1)
	{
		result = sub(result, powerBig("2", 127));
	}

	return result;
}

string QInt::getHex()
{
	string result = "";

	for (int i = 0; i < 128; i += 4)
	{
		int x = 0;
		int j = 0;
		while (j < 4)
		{
			int temp = getBit(i + j);

			if (temp == 1)
			{
				x += pow(2, 3 - j);
			}
			j++;
		}

		if (x < 10 && x >= 0)
		{
			char t = x + '0';
			result += t;
		}
		else
		{
			switch (x)
			{
			case 10:
				result += 'A'; break;
			case 11:
				result += 'B'; break;
			case 12:
				result += 'C'; break;
			case 13:
				result += 'D'; break;
			case 14:
				result += 'E'; break;
			case 15:
				result += 'F'; break;
			}
		}
	}

	return result;
}

QInt& QInt::operator=(const QInt& x)
{
	for (int i = 0; i < 4; i++)
	{
		this->data[i] = x.data[i];
	}

	return *this;
}

void QInt::operator~()
{
	for (int i = 0; i < 128; i++)
	{
		data[i / 32] ^= (1 << (31 - i % 32));
	}
}

QInt QInt::operator+(QInt b)
{
	bool in = false, out = false;
	QInt result;
	int getA, getB;
	for (int i = 127; i >= 0; i--)
	{
		in = out;

		getA = this->getBit(i);
		getB = b.getBit(i);

		if (getA == 1 && getB == 1)
		{
			out = true;
			if (in == true)
			{
				result.setBit(1, i);
			}
		}
		else
		{
			if (in == true)
			{
				if (getA == getB)
				{
					result.setBit(1, i);
					out = false;
				}
			}
			else
			{
				out = false;
				if (getA != getB)
				{
					result.setBit(1, i);
				}
			}
		}
	}
	return result;
}

QInt QInt::operator-(QInt b)
{
	QInt result;
	QInt one;
	one.uploadData("1", "10", false);
	QInt one_2;
	one_2.uploadData("1", "10", false);
	~one_2;
	one_2 = one_2 + one;

	if (b.getBit(0) == 1)
	{
		b = b + one_2;
		~b;
	}
	else
	{
		~b;
		b = b + one;
	}
	result = (*this) + b;
	return result;
}

QInt QInt::right()
{
	QInt result = *this;
	int temp;

	for (int i = 2; i >= 0; i--)
	{
		result.data[i + 1] >>= 1;

		temp = result.getBit(31 + i * 32);
		if (temp == 1)
		{
			result.setBit(1, 32 + i * 32);
		}
		else
		{
			result.setBit(0, 32 + i * 32);
		}
	}
	temp = result.getBit(0);
	result.data[0] >>= 1;
	result.setBit(temp, 0);

	return result;
}

QInt QInt::operator>>(int value)
{
	QInt result = *this;
	for (int i = 0; i < value; i++)
	{
		result = result.right();
	}
	return result;
}

QInt QInt::left()
{
	QInt result = *this;
	int temp;
	for (int i = 0; i < 3; i++)
	{
		result.data[i] <<= 1;

		temp = result.getBit((i + 1) * 32);
		if (temp == 1)
		{
			result.setBit(1, 31 + i * 32);
		}
		else
		{
			result.setBit(0, 31 + i * 32);
		}
	}
	temp = (*this).getBit(0);
	result.data[3] <<= 1;
	result.setBit(temp, 0);

	return result;
}

QInt QInt::operator<<(int value)
{
	QInt result = *this;
	for (int i = 0; i < value; i++)
	{
		result = result.left();
	}
	return result;
}

QInt QInt::operator*(QInt b)
{
	//M->b
	QInt A;
	QInt Q = *this; //a
	int q = 0;

	for (int i = 0; i < 128; i++)
	{
		if ((Q.data[3] & 1) != q) //10 or 01
		{
			if (q == 1) //01
				A = A + b;
			else A = A - b; //10
		}
		q = Q.data[3] & 1; //lấy bit cuối của Q
		int x = A.data[3] & 1; //lấy bit cuối của A
		Q = Q.right();
		A = A.right();

		if (x == 0)
			Q.setBit(0, 0);
		else Q.setBit(1, 0);
	}

	return Q;
}

QInt QInt::nhan(QInt b)
{
	//M->b
	QInt A;
	QInt Q = *this; //a
	int q = 0;

	for (int i = 0; i < 128; i++)
	{
		if ((Q.data[3] & 1) != q) //10 or 01
		{
			if (q == 1) //01
				A = A + b;
			else A = A - b; //10
		}
		q = Q.data[3] & 1; //lấy bit cuối của Q
		int x = A.data[3] & 1; //lấy bit cuối của A
		Q = Q.right();
		A = A.right();

		if (x == 0)
			Q.setBit(0, 0);
		else Q.setBit(1, 0);
	}

	return A;
}

//=====
QInt QInt::operator&(QInt b)
{
	QInt result;

	int tempa, tempb;
	for (int i = 127; i >= 0; i--) {
		tempa = this->getBit(i); tempb = b.getBit(i);
		if (tempa == tempb) {
			if (tempa == 1) result.setBit(1, i); //Set bit tai vi tri i cua result bang 1
		}
	}

	return result;
}

QInt QInt::operator|(QInt b) {
	QInt result;

	int tempa, tempb;
	for (int i = 127; i >= 0; i--) {
		tempa = this->getBit(i); tempb = b.getBit(i);
		if (tempa == 1 || tempb == 1) {
			result.setBit(1, i); //Set bit tai vi tri i cua result bang 1
		}
	}

	return result;
}

QInt QInt::operator^(QInt b) {
	QInt result;

	int tempa, tempb;
	for (int i = 127; i >= 0; i--) {
		tempa = this->getBit(i); tempb = b.getBit(i);
		if (tempa != tempb) {
			result.setBit(1, i); //Set bit tai vi tri i cua result bang 1
		}
	}

	return result;
}

QInt QInt::operator/(QInt b)
{
	QInt A;

	if (b.is0())
		throw 0;
	if (this->is0())
		return A;

	QInt Q = *this;
	QInt M = b;

	int signa = this->getBit(0), signb = M.getBit(0);

	if (signa == 1)
		Q = A - Q;
	if (signb == 1)
		M = A - M;

	for (int i = 0; i < 127; i++)
	{
		int temp = Q.getBit(1);
		A = A.left(); A.setBit(temp, 127);

		Q = Q.left();
		A = A - M;

		if (A.getBit(0) == 1)
		{
			Q.setBit(0, 127);
			A = A + M;
		}
		else
		{
			Q.setBit(1, 127);
		}
	}

	if (signa != signb)
	{
		QInt temp;
		Q = temp - Q;
	}

	return Q;
}

QInt QInt::operator%(QInt b)
{
	QInt A;

	if (b.is0())
		throw 0;
	if (this->is0())
		return A;

	QInt Q = *this;
	QInt M = b;

	int signa = this->getBit(0), signb = M.getBit(0);

	if (signa == 1)
		Q = A - Q;
	if (signb == 1)
		M = A - M;

	for (int i = 0; i < 127; i++)
	{
		int temp = Q.getBit(1);
		A = A.left(); A.setBit(temp, 127);

		Q = Q.left();
		A = A - M;

		if (A.getBit(0) == 1)
		{
			Q.setBit(0, 127);
			A = A + M;
		}
		else
		{
			Q.setBit(1, 127);
		}
	}

	if (signa != signb)
	{
		QInt temp;
		Q = temp - Q;
	}

	return A;
}

QInt QInt::ror(unsigned int n)
{
	QInt res = *this;
	for (int i = 0; i < n % 128; i++)
	{
		if (res.getBit(0) == 1 && res.getBit(127) == 0)
		{
			res = res >> 1;
			res.setBit(0, 0);
		}
		else if (res.getBit(0) == 0 && res.getBit(127) == 1)
		{
			res = res >> 1;
			res.setBit(1, 0);
		}
		else res = res >> 1;
	}
	return res;
}

QInt QInt::rol(unsigned int n)
{
	return this->ror(128 - n % 128);
}

void QInt::write(ostream &f, string type)
{
	if (this->getDec() == "0")
	{
		f << "0" << endl;
		return;
	}
	if (type == "16")
	{
		f << normalize(this->getHex()) << endl;
	}
	else if (type == "10")
	{

		f << normalize(this->getDec()) << endl;
	}
	else if (type == "2")
	{
		f << normalize(this->getBin()) << endl;
	}
}

QInt::~QInt()
{
}
