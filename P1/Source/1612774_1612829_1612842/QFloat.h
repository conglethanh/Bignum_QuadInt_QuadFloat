#pragma once
#include "BigNumber.h"
#include "QInt.h"

class QFloat
{
private:
	//data mảng 4 int, xem như dãy 128 bit
	unsigned int data[4];
public:
	//hàm khởi tạo mặc định QFloat bằng 0
	QFloat();

	//hàm khởi tạo có 2 tham số, tham số 1: chuỗi đầu vào, tham số 2: kiểu số (dec,bin,hex)
	QFloat(const string& value, const string& type);

	//hàm khởi tạo sao chép QFloat
	QFloat(const QFloat& a);

	//hàm chuyển dữ liệu lên data, với inString là chuỗi đầu vào, type là kiểu số
	void uploadData(string inString, string type);

	//hàm lấy ra chuỗi số dạng nhị phân 
	string getBin();

	//hàm lấy ra chuỗi số dạng thập phân
	string getDec();

	//hàm lấy ra bit tại vị trí pos là 0 hay 1
	int getBit(int pos);

	//hàm chuyển đổi bit tại vị trí nào đó, với: value là giá trị bit (0, 1), pos là vị trí
	void setBit(int value, int pos);

	//hàm kiểm tra một số có bằng 0 hay không?
	bool is0();

	//toán tử gán bằng của QFloat
	QFloat& operator=(const QFloat& b);

	//***************************
	//hàm lấy ra dãy bit với vị trí đầu begin, vị trí cuối end
	string getBits(int begin, int end);

	//hàm lấy ra giá trị thập phân của chuỗi bit nhị phân
	int getValue(string bits);

	//hàm dịch phải 1 bit (dịch luận lý)
	string shiftRight(string bits);

	//hàm dịch phải 1 bit (dịch luận lý)
	string shiftLeft(string bits);
	
	//hàm điền đầy chuỗi bit sao cho chiều dài = n bit
	string fillBits(string a, int n);

	//********************KO****************************************
	//string convertToTwoComplement(string a);//bù 2;
	//string addBinNumber(string a, string b);
	//string normalize_TwoComplement(string a);
	//*************KO*******************************************************************

	//hàm cộng 2 phần trị của số chấm động
	string addSignificand(string a, bool sign1, string b, bool sign2, bool &sign);

	//hàm chuẩn hóa phần trị của số chấm động sau khi cộng về 112bit
	int normalizeSignificand_Add(string &a);

	//hàm kiểm tra chuỗi bit có phải có giá trị thập phân bằng 0 hay không
	bool is0(const string& a);

	//toán tử cộng 2 số chấm động
	QFloat operator+(QFloat y);

	//toán tử trừ 2 số chấm động
	QFloat operator-(QFloat y);

	//hàm nhân 2 phần trị của số chấm động
	string multiplySignificand(string a, string b);

	//hàm chuẩn hóa phần trị của số chấm động sau khi nhân về 112bit
	int normalizeSignificand_Multiply(string&a);

	//toán tử nhân 2 số chấm động
	QFloat operator*(QFloat y);

	/////Devide    ...........................................
	//Devide

	//hàm so sánh 2 chuỗi bit
	int compare(string a, string b);

	//hàm chia 2 phần trị của số chấm động
	string divideSignificand(string a, string b);

	//toán tử chia 2 số chấm động
	QFloat operator/(QFloat b);
	//..................................

	//hàm in ra giá trị, với: f là loại in ra (file, console), type: kiểu số (bin,dec,hex)
	void write(ostream &f, string type);

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//hàm trả về số chấm động vô cực, sign: dấu (+,-)
	QFloat returnINF(int sign);

	//hàm trả về số báo lỗi
	QFloat returnNaN();

	//hàm kiểm tra số vô cực
	bool isINF();

	//hàm kiểm tra số báo lỗi
	bool isNaN();

	//hàm kiểm tra số không chuẩn
	bool isDenormalizedNumber();

	~QFloat();
};
