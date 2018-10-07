#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include "BigNumber.h"


class QInt
{
private:
	//data mảng 4 int, xem như dãy 128 bit
	unsigned int data[4];
public:
	//hàm khởi tạo mặc định số nguyên bằng 0
	QInt();

	//hàm khởi tạo có 2 tham số, tham số 1: chuỗi đầu vào, tham số 2: kiểu số (dec,bin,hex)
	QInt(string value, string type);

	//hàm kiểm tra một số có bằng 0 hay không?
	bool is0();

	//hàm chuyển đổi chuỗi thập phân sang chuỗi nhị phân
	string convertStringDecToBin(string decimal);

	//hàm chuyển đổi chuỗi thập lục phân sang chuỗi nhị phân
	string convertStringHexToBin(string hex);

	//hàm chuyển dữ liệu lên data, với inString là chuỗi đầu vào, type là kiểu số, isNegative (true: số âm, false: số dương)
	void uploadData(string inString, string type, bool isNegative);

	//hàm lấy ra bit tại vị trí pos là 0 hay 1
	int getBit(int pos);

	//hàm chuyển đổi bit tại vị trí nào đó, với: value là giá trị bit (0, 1), pos là vị trí
	void setBit(int value, int pos);

	//hàm lấy ra chuỗi số dạng nhị phân 
	string getBin();

	//hàm lấy ra chuỗi số dạng thập phân
	string getDec();

	//hàm lấy ra chuỗi số dạng thập lục phân
	string getHex();

	//toán tử gán bằng của QInt
	QInt& operator=(const QInt& x);

	//toán tử NOT
	void operator~();

	//toán tử cộng 2 số nguyên
	QInt operator+(QInt b);

	//toán tử trừ 2 số nguyên
	QInt operator-(QInt b);

	//hàm dịch phải 1 bit (dịch số học)
	QInt right();

	//toán tử dịch sang phải value (bit)
	QInt operator>>(int value);

	//hàm dịch trái 1 bit (dịch số học)
	QInt left();

	//toán tử dịch sang trái value (bit)
	QInt operator<<(int value);

	//toán tử nhân 2 số nguyên (trả về 128bit QInt sau => giá trị sau khi nhân)
	QInt operator*(QInt b);

	//hàm nhân 2 số nguyên (trả về 128bit QInt đầu)
	QInt nhan(QInt b);

	//=====
	//toán tử AND 2 số nguyên
	QInt operator&(QInt b);

	//toán tử OR 2 số nguyên
	QInt operator|(QInt b);

	//toán tử XOR 2 số nguyên
	QInt operator^(QInt b);

	//toán tử CHIA NGUYÊN 2 số nguyên
	QInt operator/(QInt b);

	//toán tử CHIA LẤY PHẦN DƯ 2 số nguyên
	QInt operator%(QInt b);

	//toán tử quay phải n bit
	QInt ror(unsigned int n);

	//toán tử quay trái n bit
	QInt rol(unsigned int n);

	//hàm in ra giá trị, với: f là loại in ra (file, console), type: kiểu số (bin,dec,hex)
	void write(ostream &f, string type);

	~QInt();
};