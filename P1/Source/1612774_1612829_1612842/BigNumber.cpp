#include "stdafx.h"
#include "BigNumber.h"

string divideBy2(string number)
{
	string ans;

	int idx = 0;
	int temp = number[idx] - '0';
	while (temp < 2)
		temp = temp * 10 + (number[++idx] - '0');

	while (number.size() > idx)
	{
		ans += (temp / 2) + '0';
		temp = (temp % 2) * 10 + number[++idx] - '0';
	}

	if (ans.length() == 0)
		return "0";

	return ans;
}

string add(string a, string b){	string res = "";	while (a.length() < b.length()) a = "0" + a;	while (b.length() < a.length()) b = "0" + b;	int carry = 0;	for (int i = a.length() - 1; i >= 0; i--)	{		int tmp = a[i] - 48 + b[i] - 48 + carry;		carry = tmp / 10;		tmp = tmp % 10;		res = (char)(tmp + 48) + res;	}	if (carry>0) res = "1" + res;	return res;}


string mul(string a, string b){	string res = "";	int n = a.length();	int m = b.length();	int len = n + m - 1;	int carry = 0;	for (int i = len; i >= 0; i--)	{		int tmp = 0;		for (int j = n - 1; j >= 0; j--)			if (i - j <= m && i - j >= 1)			{				int a1 = a[j] - 48;				int b1 = b[i - j - 1] - 48;				tmp += a1*b1;			}		tmp += carry;		carry = tmp / 10;		res = (char)(tmp % 10 + 48) + res;	}	while (res.length() > 1 && res[0] == '0') res.erase(0, 1);	return res;}

string powerBig(string number, int power){	string res = "1";	for (int i = 0; i < power; i++) {		res = mul(res, number);	}	return res;}

string sub(string a, string b){	string res = "";	while (a.length() < b.length()) a = "0" + a;	while (b.length() < a.length()) b = "0" + b;	bool neg = false;	if (a < b)	{		swap(a, b);		neg = true;	}	int borrow = 0;	for (int i = a.length() - 1; i >= 0; i--)	{		int tmp = a[i] - b[i] - borrow;		if (tmp<0)		{			tmp += 10;			borrow = 1;		}		else borrow = 0;		res = (char)(tmp % 10 + 48) + res;	}	while (res.length()>1 && res[0] == '0') res.erase(0, 1);	if (neg) res = "-" + res;	return res;}

vector<string> splitString(string a)
{
	const char* s_const = a.c_str();

	char* s = _strdup(s_const);

	char* nextToken = NULL;
	char* word = strtok_s(s, " ", &nextToken);
	vector<string> num;
	
	while (word != NULL)
	{
		num.push_back((string)word);
		word = strtok_s(NULL, " ", &nextToken);
	}
	return num;
}string convertString(string a, string type, bool& isNegative){
	if (type == "10")
	{
		if (a[0] == '-')
		{
			isNegative = true;
			a = a.erase(0, 1);
		}
	}
	else if (type == "2")
	{
		while (a.length() < 128)
		{
			a = a.insert(0, "0");
		}
		if (a[0] == '1')
		{
			isNegative = true;
		}
	}	return a;}string normalize(string in){
	string out = in;	while (out[0] == '0')	{		out = out.erase(0, 1);	}	return out;}//FLOAT DEC TO BIN

void reverse(string &num) {
	int len = num.length();
	for (int i = 0; i < len / 2; i++)
		swap(num[i], num[len - i - 1]);
}

bool isZero(const string &num) {
	int len = num.length();
	for (int i = 0; i < len; i++)
		if (num[i] >= '1' && num[i] <= '9')
			return false;
	return true;
}
													
string ZERO_float() { 
	string result = "";
	for (int i = 0; i < maxLenExp; i++)
		result += '0';
	return result;
}

string INF_float() { 
	string result = "";
	for (int i = 0; i < maxLenExp; i++)
		result += i >= 1 && i <= 15 ? '1' : '0';
	return result;
}

char modBy2(const string &num) {
	return ((num[num.length() - 1] - '0') % 2) + '0';
}

string decToBin_int(string num) {
	string res = "";
	do {
		res += modBy2(num);
		num = divideBy2(num);
	} while (!isZero(num));
	reverse(res);
	return res;
}

string mul(const string &num, int val) {
	string res = "";
	int t = 0;
	for (int i = num.length() - 1; i >= 0; --i) {
		t += (num[i] - '0')*val;
		res += (t % 10) + '0';
		t /= 10;
	}
	while (t > 0) {
		res += (t % 10) + '0';
		t /= 10;
	}
	reverse(res);
	return res;
}

string decToBin_fra(string num) {
	string res = "";
	int reslen = 0;
	do {
		int len = num.length();
		num = mul(num, 2);
		if (len == num.length())
		{
			res += '0'; 
			reslen++;
		}
		else {
			res += '1';
			reslen++;
			num = num.erase(0, 1);
			//num = num.substr(1);
		}
		if (reslen > 2 * maxExpVal) break;
	} while (!isZero(num));
	return res;
}

int normalize_float(string &num) { 
	int p = num.find('.');
	int pow = 0;
	while (p > 1) {
		pow++;
		swap(num[p], num[p - 1]);
		p--;
	}
	p = num.length();
	if (num != "0.0")
	{
		while (num[0] == '0') {
			pow--;
			swap(num[1], num[2]);
			if (num[p - 1] == '.')
			{
				num += '0';
				p++;
			}
			num = num.erase(0, 1), p--;
			if (num[0] == '.')
			{
				num = '0' + num;
				p++;
			}
		}
	}
	return pow;
}

void bin_shr(string &num, int pow) { 
	int p = num.find('.');
	if (p == -1)
	{
		p = num.length();
		num += ".0";
	}
	int len = num.length();
	for (int i = 0; i < pow; ++i) {
		swap(num[p], num[p + 1]);
		p++;
		if (num[len - 1] == '.')
		{
			num += '0';
			len++;
		}
	}
	p = 0;
	while (num[p] == '0' && num[p + 1] != '.')
		p++;

	//num = num.substr(p, num.length());
	num = num.substr(p);
}

string value_to_bias(int num) { 
	num += maxExpVal;
	string res = "";
	for (int i = 0; i < 15; i++) {
		res += (num % 2) + '0';
		num /= 2;
	}
	reverse(res);
	return res;
}

string convertDecToBin_Float(string dec)
{
	if (isZero(dec)) return ZERO_float();
	string res;
	if (dec[0] == '-')
	{
		res += '1';
		dec = dec.erase(0, 1);
	}
	else res += '0';

	int p = dec.find('.');
	if (p == -1) {
		p = dec.length();
		dec += ".0";
	}
	string firstPart = decToBin_int(dec.substr(0, p));
	string secondPart = decToBin_fra(dec.substr(p + 1));
	string b_dec = firstPart + '.' + secondPart;
	string b_dec_special = b_dec;
	int pow = normalize_float(b_dec);
	if (pow > maxExpVal)
		return res[0] == '0' ? INF_float() : ('1' + INF_float().erase(0, 1));
	if (pow < minExpVal) {
		for (int i = 1; i <= 15; ++i)
			res += '0';

		bin_shr(b_dec_special, maxExpVal);

		int len = b_dec.length();
		for (int i = 16; i < maxLenBit; ++i)
			if (i - 16 + 2 < len) res += b_dec_special[i - 16 + 2];
			else res += '0';

			return res;
	}
	res += value_to_bias(pow);

	int len = b_dec.length();
	for (int i = 16; i < maxLenBit; ++i) {
		if (i - 16 + 2 < len) res += b_dec[i - 16 + 2];
		else res += '0';
	}
	return res;
}

//FLOAT BIN->DEC

int bias_to_value(string num)
{ 
	int res = 0;
	int len = num.length();
	for (int i = 0; i < len; i++) {
		res *= 2;
		res += (num[i] - '0');
	}
	return res - maxExpVal;
}

void denormalize_float(string &num, int pow) 
{
	int p = num.find('.'), len = num.length();
	while (pow > 0) {
		swap(num[p], num[p + 1]);
		p++;
		if (p == len - 1) {
			num += '0';
			len++;
		}
		pow--;
	}
	while (pow < 0) {
		swap(num[p], num[p - 1]);
		p--;
		if (p == 0) {
			num = '0' + num;
			len++;
			p = 1;
		}
		pow++;
	}
}

string return_float(const string &num) {
	int pow = bias_to_value(num.substr(1, 15));
	if (pow < minExpVal) {
		if (isZero(num.substr(1))) return "0.0";
		string res = "0.";
		for (int i = 0; i < maxExpVal; ++i) res += '0';
		res += num.substr(16);
		return res;
	}
	if (pow > maxExpVal)
	{
		return num[0] == '0' ? "INF" : "-INF";
	}
	string res = "1." + num.substr(16);
	denormalize_float(res, pow);
	return res;
}

string binToDec_int(string num) {
	string temp = "0";
	for (int i = 0, len = num.length(); i < len; ++i) {
		temp = mul(temp, 2);
		if (num[i] == '1')
			temp = add(temp, "1");
	}
	return temp;
}

string binToDec_fra(std::string num) {
	string temp = "0";
	for (int i = num.length() - 1; i >= 0; --i) {
		temp = num[i] + temp;
		temp = mul(temp, 5);
	}
	return temp;
}

string convertBinToDec_Float(string bin)
{
	//char sig = bin[0] == '1' ? '-' : '\0';
	char sig = bin[0];

	bin = return_float(bin);
	if (bin == "-INF" || bin == "INF" || bin == "0.0") return bin;
	int p = bin.find('.');
	if (p == -1) {
		p = bin.length();
		bin += ".0";
	}
	string r1 = binToDec_int(bin.substr(0, p));
	string r2 = binToDec_fra(bin.substr(p + 1));

	if (sig == '1')
	{
		return '-' + r1 + '.' + r2;
	}
	else return r1 + '.' + r2;

	//return sig + r1 + '.' + r2;
}