#include "stdafx.h"
#include "QFloat.h"

QFloat::QFloat()
{
	for (int i = 0; i < maxLenData; i++)
	{
		data[i] = 0;
	}
}

QFloat::QFloat(const string & value, const string & type)
{
	for (int i = 0; i < maxLenData; i++)
	{
		data[i] = 0;
	}
	uploadData(value, type);
}

QFloat::QFloat(const QFloat & a)
{
	for (int i = 0; i < maxLenData; i++)
	{
		data[i] = a.data[i];
	}
}

void QFloat::uploadData(string inString, string type)
{
	string outString = inString;
	if (type == "10")
	{
		outString = convertDecToBin_Float(inString);
	}

	for (int i = 0; i < outString.length(); i++)
	{
		data[i / 32] <<= 1;
		data[i / 32] += (int)(outString[i] - '0');
	}
}

string QFloat::getBin()
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

string QFloat::getDec()
{
	if (isNaN())
	{
		return "NaN";
	}
	return convertBinToDec_Float(getBin());
}

int QFloat::getBit(int pos)
{
	return (data[pos / 32] >> (31 - pos % 32)) & 1;
}

void QFloat::setBit(int value, int pos)
{
	if (value == 1)
		data[pos / 32] |= (1 << (31 - pos % 32));
	else
		data[pos / 32] &= ~(1 << (31 - pos % 32));
}

bool QFloat::is0()
{
	if (data[0] != 0 && data[0] != (1 << 31))
	{
		return false;
	}
	for (int i = 1; i < 4; i++)
	{
		if (data[i] != 0)
		{
			return false;
		}
	}
	return true;
}

QFloat& QFloat::operator=(const QFloat& b)
{
	for (int i = 0; i < maxLenData; i++)
	{
		this->data[i] = b.data[i];
	}
	return *this;
}

//***************************
string QFloat::getBits(int begin, int end)
{
	string res = "";
	for (int i = begin; i <= end; i++)
	{
		res.push_back(this->getBit(i) + '0');
	}
	return res;
}

int QFloat::getValue(string bits)
{
	int res = 0, temp = 1;
	int len = bits.length();
	for (int i = len - 1; i >= 0; i--)
	{
		res += temp*(bits[i] - '0');
		temp *= 2;
	}
	return res;
}

string QFloat::shiftRight(string bits)//dịch luận lý
{
	int len = bits.length();
	for (int i = len - 1; i > 0; i--)
		bits[i] = bits[i - 1];
	bits[0] = '0';
	return bits;
}

string QFloat::shiftLeft(string bits)
{
	int n = bits.length();
	for (int i = 0; i < n - 1; ++i)
		bits[i] = bits[i + 1];
	bits[n - 1] = 0;
	return bits;
}
//
string QFloat::fillBits(string a, int n)
{
	while (a.length() < n)
		a.insert(a.begin(), '0');
	return a;
}

string QFloat::addSignificand(string a, bool sign1, string b, bool sign2, bool &sign)
{
	sign = 0;

	QInt x(a, "2");
	QInt y(b, "2");
	QInt one("1", "10");
	if (sign1 != 0)
	{
		~x;
		x = x + one;
	}
	if (sign2 != 0)
	{
		~y;
		y = y + one;
	}

	QInt res = x + y;
	if (res.getBit(0) == 1)
	{
		sign = 1;
		res = res - one;
		~res;
	}

	return res.getBin();
}

int QFloat::normalizeSignificand_Add(string &a)
{
	while (a.length() > 114)
		a.erase(a.begin());
	int res = 0;
	if (a[0] == '1')
	{
		a = shiftRight(a);
		res++;
		a.erase(a.begin());
	}
	else
	{
		a.erase(a.begin());
		while (a[0] == '0')
		{
			a = shiftLeft(a);
			res--;
		}
	}
	a.erase(a.begin());

	return res;
}

bool QFloat::is0(const string& a)
{
	int len = a.length();
	for (int i = 0; i < len; i++)
	{
		if (a[i] == '1')
			return false;
	}
	return true;
}

QFloat QFloat::operator+(QFloat y)
{
	if (this->is0())
	{
		return y;
	}
	else if (y.is0())
	{
		return *this;
	}

	string exp1 = getBits(1, 15), exp2 = y.getBits(1, 15);

	int gap = getValue(exp1) - getValue(exp2);

	string exp = (gap >= 0) ? exp1 : exp2;

	string significand1 = this->getBits(16, 127);
	string significand2 = y.getBits(16, 127);

	significand1.insert(significand1.begin(), '1');
	significand2.insert(significand2.begin(), '1');

	if (gap > 0)
	{
		for (int i = 1; i <= gap; i++)
			significand2 = shiftRight(significand2);
	}
	else if (gap < 0)
	{
		for (int i = 1; i <= -gap; i++)
			significand1 = shiftRight(significand1);
	}

	gap = 0;

	bool sign1 = this->getBit(0);
	bool sign2 = y.getBit(0);
	bool sign = 0;

	string significand = addSignificand(significand1, sign1, significand2, sign2, sign);

	if (is0(significand))
		return QFloat("0", "10");

	gap = normalizeSignificand_Add(significand);

	int e = getValue(exp) - maxExpVal + gap;

	if (e < minExpVal)
	{
		return QFloat("0", "10");
	}

	if (e > maxExpVal)
	{
		return returnINF(sign);
	}

	exp = value_to_bias(e);

	string temp;
	temp = (char)((int)sign + '0') + exp + significand;
	return QFloat(temp, "2");
}

QFloat QFloat::operator-(QFloat y)
{
	if (y.getBit(0) == 0)y.setBit(1, 0);
	else y.setBit(0, 0);

	return *this + y;
}

string QFloat::multiplySignificand(string a, string b)
{
	a.insert(a.begin(), '1');
	b.insert(b.begin(), '1');
	a = fillBits(a, 128);
	b = fillBits(b, 128);
	QInt Q(a, "2"), M(b, "2");
	QInt A = Q.nhan(M);
	QInt QQ = Q*M;
	string res = A.getBin() + QQ.getBin();
	return res;
}

int QFloat::normalizeSignificand_Multiply(string&a)
{
	while (a.length() > 226) 
		a.erase(a.begin());
	int res = 0;
	//
	while (a[0] == '0')
	{
		a = shiftLeft(a);
		res--;
	}
	a.erase(a.begin());

	while (a.length() > 112)
		a.erase(a.end() - 1);
	return res + 1;
}


QFloat QFloat::operator*(QFloat y)
{
	if (this->is0() || y.is0())
		return QFloat("0", "10");

	bool sign = getBit(0) ^ y.getBit(0);

	if (this->isINF() || y.isINF())
	{
		return returnINF(sign);
	}

	string exp1 = getBits(1, 15);
	string exp2 = y.getBits(1, 15);
	long long gap = getValue(exp1) + getValue(exp2) - 2 * maxExpVal;
	if (gap < minExpVal)
	{
		return QFloat("0", "10");
	}
	if (gap > maxExpVal)
	{
		return returnINF(sign);
	}

	string significand1 = getBits(16, 127);
	string significand2 = y.getBits(16, 127);
	string significand = multiplySignificand(significand1, significand2);

	//
	gap += normalizeSignificand_Multiply(significand);
	//
	if (gap < minExpVal)
	{
		return QFloat("0", "10");
	}
	if (gap > maxExpVal)
	{
		return returnINF(sign);
	}

	string e = value_to_bias(gap);
	string temp = significand;
	temp = e + temp;
	temp = ((sign == 0) ? "0" : "1") + temp;

	return QFloat(temp, "2");
}

/////Devide    ...........................................
//Devide
int QFloat::compare(string a, string b)
{
	while (a.length() < b.length())
		a.insert(a.begin(), '0');
	while (b.length() < a.length())
		b.insert(b.begin(), '0');

	for (int i = 0; i < a.length(); i++)
	{
		if ((a[i] - '0') >(b[i] - '0'))
			return 1;
		else if ((b[i] - '0') > (a[i] - '0'))
			return -1;
	}
	return 0;
}

string QFloat::divideSignificand(string a, string b)
{
	a = '1' + a;
	b = '1' + b;

	a = fillBits(a, 128);
	b = fillBits(b, 128);

	string res = (QInt(a, "2") / QInt(b, "2")).getBin();  //Lay a div b (chuoi 128 bit)

	int _compare = 0;
	string surplus = (QInt(a, "2") % QInt(b, "2")).getBin();   //Lay a mod b (chuoi 128 bit)

		//Gan them 128 bit khi chia du vao res (Bang cach nhan 2) -> chuoi 256 bit
	for (int i = 0; i < 128; ++i)
	{
		surplus = shiftLeft(surplus); //So du nhan 2
		_compare = compare(surplus, b); //So sanh phan du sau khi nhan hai co lon hon b khong
		if (_compare < 0)
		{
			res += '0';
		}
		else
		{
			res += '1';
			surplus = (QInt(surplus, "2") - QInt(b, "2")).getBin();
		}
	}

	return res;
}

QFloat QFloat::operator/(QFloat b)
{
	QFloat result;

	if (b.is0())
	{
		if (this->is0())
		{
			return returnNaN();
		}
		else
		{
			return returnINF(this->getBit(0));
		}
	}
	if (this->is0() && !b.is0())
	{
		return QFloat("0", "10");
	}

	if (this->isINF())
	{
		if (b.isINF())
		{
			return returnNaN();
		}
		else returnINF(this->getBit(0));
	}

	int sign = (this->getBit(0) != b.getBit(0)) ? 1 : 0;

	//Tinh phan mu
	string exp1 = getBits(1, 15), exp2 = b.getBits(1, 15);
	int gap = getValue(exp1) - getValue(exp2);

	//

	//Lay va chia hai phan tri
	string significand1 = this->getBits(16, 127), significand2 = b.getBits(16, 127);
	string significand = divideSignificand(significand1, significand2);

	//Dua phan dinh tri ve dung 112 bit
	while (significand.length() > 129)
	{
		if (significand[0] == '1')
		{
			significand = shiftRight(significand);
			gap++;
		}
		significand.erase(significand.begin());
	}
	while (significand[0] == '0')
	{
		significand = shiftLeft(significand);
		gap--;
	}

	significand.erase(significand.begin());
	while (significand.length() > 112)
		significand.erase(significand.end() - 1);

	//Xu ly cac truong hop dac biet
	if (gap < minExpVal)
	{
		return QFloat("0", "10");
	}
	if (gap > maxExpVal)
	{
		return returnINF(sign);
	}

	//Chuyen phan mu tu so nguyen ve dang bias
	string exp = value_to_bias(gap);

	string temp(significand);

	//Ghep cac phan dau + mu + dinhTri thanh chuoi 128 bit hoan chinh bieu dien so thuc 
	temp = exp + temp;
	temp = char(sign + '0') + temp;

	return QFloat(temp, "2");
}
//..................................

void QFloat::write(ostream &f, string type)
{
	if (type == "10")
	{
		f << this->getDec() << endl;
	}
	else if (type == "2")
	{
		f << this->getBin() << endl;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

QFloat QFloat::returnINF(int sign)
{
	QFloat res;

	for (int i = 1; i < 16; i++)
		res.setBit(1, i);

	if (sign == 1)res.setBit(1, 0);
	else res.setBit(0, 0);

	return res;
}

QFloat QFloat::returnNaN()
{
	QFloat res;

	for (int i = 1; i < 16; i++)
		res.setBit(1, i);
	res.setBit(1, 127);

	return res;
}

bool QFloat::isINF()
{
	for (int i = 1; i < 16; i++)
		if (getBit(i) == 0)
			return false;

	for (int i = 16; i < 128; i++)
		if (getBit(i) == 1)
			return false;

	return true;
}

bool QFloat::isNaN()
{
	for (int i = 1; i < 16; i++)
		if (getBit(i) == 0)
			return false;

	if (isINF())
		return false;

	return true;
}

bool QFloat::isDenormalizedNumber()
{
	for (int i = 0; i < 16; i++)
		if (getBit(i) == 1)
			return false;

	if (is0())
		return false;

	return true;
}


QFloat::~QFloat()
{
}
