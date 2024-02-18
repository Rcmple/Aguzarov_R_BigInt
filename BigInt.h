#ifndef AGUZAROV_R_BIGINT_BIGINT_H
#define AGUZAROV_R_BIGINT_BIGINT_H
#include <iostream>
#include <vector>
using namespace std;
class BigInt{
public:
    vector<int> Integer;
    vector <int> Decimal;
    bool sign = false;

    BigInt() = default;
    explicit BigInt(const string& s){
        int cur_position = 0;
        if(s[0] < '0' || s[0] > '9') {
            if (s[0] == '-') {
                sign = true;
            }
            cur_position++;
        }
        int s_size = (int)s.size();
        while(cur_position < s_size && s[cur_position] != '.'){
            Integer.push_back(s[cur_position] - '0');
            cur_position++;
        }
        cur_position++;
        while(cur_position < s_size){
            Decimal.push_back(s[cur_position] - '0');
            cur_position++;
        }
        this->remove_zeros();
    }
    BigInt& remove_zeros() {
        int cnt_Integer_zeros = 0;
        for (int i = 0; i < Integer.size(); i++) {
            if(Integer[i] != 0) break;
            cnt_Integer_zeros = i + 1;
        }
        int cnt_Decimal_zeros = 0;
        for (int i = (int) Decimal.size() - 1; i >= 0; i--) {
            if(Decimal[i] != 0) break;
            cnt_Decimal_zeros = (int) (Decimal.size() - i);
        }
        for (int i = 0; i < cnt_Integer_zeros; i++) {
            Integer.erase(Integer.begin());
        }
        for(int i = 0; i < cnt_Decimal_zeros; i++) {
            Decimal.pop_back();
        }
        if(Integer.empty()) {
            Integer.push_back(0);
        }
        if(Decimal.empty()) {
            Decimal.push_back(0);
        }
        return *this;
    }
    BigInt& operator = (const BigInt& other) = default;
    //Унарные операции
    BigInt operator += (const BigInt& second);
    BigInt operator -= (const BigInt& second);
    BigInt operator *= (const BigInt& second);
    BigInt operator - () const;
    BigInt operator + () const;
};
BigInt operator + (const BigInt& first, const BigInt& second);
BigInt operator - (const BigInt& first, const BigInt& second);
BigInt operator * (const BigInt& first, const BigInt& second);
istream& operator >> (istream& is, BigInt& cur);
ostream& operator << (ostream& os, const BigInt& cur);
bool operator < (const BigInt& first, const BigInt& second);
bool operator == (const BigInt& first, const BigInt& second);
bool operator <= (const BigInt& first, const BigInt& second);
bool operator > (const BigInt& first, const BigInt& second);
bool operator >= (const BigInt& first, const BigInt& second);
#endif //AGUZAROV_R_BIGINT_BIGINT_H
