#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include "BigNumber.h"
#include "QInt.h"
#include "QFloat.h"

//hàm đọc file và xử lý kết quả in ra của số nguyên theo dạng yêu cầu
void processFileInt(ifstream &finp, ofstream &fout);

//hàm đọc file và xử lý kết quả in ra của số chấm động theo dạng yêu cầu
void processFileFloat(ifstream &finp, ofstream &fout);

//hàm in kết quả của số nguyên ra màn hình console theo dạng yêu cầu
void processConsoleInt(string a);

//hàm in kết quả của số chấm động ra màn hình console theo dạng yêu cầu
void processConsoleFloat(string a);