#ifndef AGUZAROV_R_BIGINT_BIGINT_H
#define AGUZAROV_R_BIGINT_BIGINT_H
#include <iostream>
#include <vector>
using namespace std;
class BigInt{
public:
    static unsigned accuracy;
    BigInt() = default;
    explicit BigInt(int cur) : BigInt(to_string(cur)) {};
    explicit BigInt(unsigned cur) : BigInt(to_string(cur)) {};
    explicit BigInt(long long cur) : BigInt(to_string(cur)) {};
    explicit BigInt(unsigned long long cur) : BigInt(to_string(cur)) {};
    explicit BigInt(double cur) : BigInt(to_string(cur)) {};
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
    BigInt& pow(long long k) {
        BigInt ans(*this);
        *this = BigInt(1);
        while(k != 0) {
            if(k % 2 == 1) *this *= ans;
            ans *= ans;
            k /= 2;
        }
        return *this;
    }
    string to_str() {
        string res;
        if(sign) {
            res.push_back('-');
        }
        for(auto &x : Integer) {
            res.push_back(x + '0');
        }
        if(Decimal.size() > 1 || Decimal[0] != 0) {
            res.push_back('.');
            for(int i = 0; i < Decimal.size() && i < 10; i++) {
                res.push_back(Decimal[i] + '0');
            }
        }
        return res;
    }
    BigInt& operator = (const BigInt& other) = default;
    BigInt& operator += (const BigInt& second);
    BigInt& operator -= (const BigInt& second);
    BigInt& operator *= (const BigInt& second);
    BigInt& operator /= (const BigInt& second);
    BigInt operator - () const;
    BigInt operator + () const;
    BigInt& operator ++ ();
    BigInt operator ++ (int);
    BigInt& operator -- ();
    BigInt operator -- (int);
    friend BigInt operator + (const BigInt& first, const BigInt& second);
    friend BigInt operator - (const BigInt& first, const BigInt& second);
    friend BigInt operator * (const BigInt& first, const BigInt& second);
    friend BigInt operator / (const BigInt& first, const BigInt& second);
    friend istream& operator >> (istream& is, BigInt& cur);
    friend ostream& operator << (ostream& os, const BigInt& cur);
    friend bool operator < (const BigInt& first, const BigInt& second);
    friend bool operator == (const BigInt& first, const BigInt& second);
    friend bool operator <= (const BigInt& first, const BigInt& second);
    friend bool operator > (const BigInt& first, const BigInt& second);
    friend bool operator >= (const BigInt& first, const BigInt& second);
    friend BigInt prev_divide(BigInt mid);
private:
    vector<int> Integer;
    vector <int> Decimal;
    bool sign = false;
    BigInt& esp() {
        Integer.push_back(0);
        for(int i = 0; i < BigInt::accuracy + 10; i++) {
            Decimal.push_back(0);
        }
        Decimal.push_back(1);
        return *this;
    }
    BigInt& get_max() {
        Integer.push_back(1);
        for(int i = 0; i < 30; i++) {
            Integer.push_back(0);
        }
        return *this;
    }
};
BigInt operator ""_f(const char* );
#endif //AGUZAROV_R_BIGINT_BIGINT_H
