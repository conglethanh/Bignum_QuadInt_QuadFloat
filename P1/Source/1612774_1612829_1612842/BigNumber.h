#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <string>
#include <vector>

const int maxLenData = 4; //chuỗi dài của mảng data
const int maxLenBit = 128; //chiều dài đầy đủ của dãy bit biểu diễn số chấm động
const int maxLenFra = 112; //chiều dài của phần trị của dãy bit biểu diễn số chấm động
const int maxLenExp = 15;//chiều dài của phần mũ số của dãy bit biểu diễn số chấm động
const int maxExpVal = (1 << 14) - 1; //giá trị lớn nhất của phần mũ
const int minExpVal = -(1 << 14) + 2;//giá trị nhỏ nhất của phần mũ
const int speExpVal = -(1 << 14) + 1;//giá trị đặc biệt của phần mũ


//hàm chia một chuỗi số thập phân cho 2
string divideBy2(string number);

//hàm cộng 2 chuỗi số thập phân
string add(string a, string b);

//hàm nhân 2 chuỗi số thập phân
string mul(string a, string b);

//hàm lấy lũy thừa bậc power của chuỗi số thập phân number
string powerBig(string number, int power);

//hàm trừ 2 chuỗi số thập phân
string sub(string a, string b);

//hàm cắt chuỗi theo khoảng trắng, trả về vector các chuỗi con sau khi cắt
vector<string> splitString(string a);

//hàm chuyển chuỗi đầu vào về dạng chuẩn dùng cho số nguyên
//nếu là dạng thập phân thì bỏ dấu - và bật isNegative=true để cho biết nó là số âm
//nếu là dạng nhị phân thì chèn thêm bit 0 cho đủ 128 bit
string convertString(string a, string type, bool& isNegative);

//hàm chuẩn hóa chuỗi số nguyên đầu ra
//bỏ bớt số 0 dư thừa trước chuỗi đầu ra cho gọn
string normalize(string in);

//FLOAT

//hàm đảo chuỗi
void reverse(std::string &num);

//hàm kiểm tra chuỗi thập phân có phải là 0 hay không
bool isZero(const string &num);

//hàm trả về chuỗi nhị phân biểu diễn số 0
string ZERO_float();

//hàm trả về chuỗi nhị phân biểu diễn số vô cực dương
string INF_float();

//chuỗi số thập phân chia lấy dư cho 2 
char modBy2(const string &num);

//hàm chuyển đổi phần nguyên của chuỗi số thực dạng thập phân sang dạng nhị phân
string decToBin_int(string num);

//hàm nhân chuỗi số dạng thập phân cho một số val nào đó
string mul(const string &num, int val);

//hàm chuyển đổi phần thập phân của chuỗi số thực dạng thập phân sang dạng nhị phân
string decToBin_fra(string num);

//hàm phụ, chuẩn hóa chuỗi nhị phân biểu diễn số thực
//về dạng 1. 
//trả về số mũ của chuỗi số sau khi chuẩn hóa
int normalize_float(string &num);

//hàm phụ dùng cho chuỗi số nhị phân dạng không chuẩn
//đem về dạng 0.
void bin_shr(string &num, int pow);

//hàm chuyển giá trị thập phân sang dạng nhị phân bias
string value_to_bias(int num);

//hàm chuyển đổi chuỗi số thực dạng thập phân sang dạng nhị phân
string convertDecToBin_Float(string dec);

//FLOAT BIN->DEC

//chuyển chuỗi số nhị phân bias sang giá trị thập phân
int bias_to_value(string num);

//hàm chuẩn hóa số mũ của chuỗi số dạng nhị phân
//sao cho trả về chuỗi số nhị phân hoàn chỉnh (x2^0)
void denormalize_float(string &num, int pow_2);

//hàm phụ, chuyển đổi chuỗi số dạng nhị phân sang dạng chuẩn
//vd: 0.0,INF...
//nếu là số không chuẩn => đem về dạng 0.
//nếu là số chuẩn => đem về dạng 1.
string return_float(const string &num);

//hàm chuyển chuỗi số nhị phân biểu diễn phần nguyên của số thực sang dạng thập phân
string binToDec_int(std::string num);

//hàm chuyển chuỗi số nhị phân biểu diễn phần thập phân của số thực sang dạng thập phân
string binToDec_fra(std::string num);

//hàm chuyển đổi chuỗi số nhị phân biểu diễn số thực sang dạng thập phân
string convertBinToDec_Float(string bin);