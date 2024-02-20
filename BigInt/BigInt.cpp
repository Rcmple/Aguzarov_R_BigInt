#include "BigInt.h"
//реализация унарных операций
BigInt BigInt::operator - () const{
    BigInt cur = *this;
    cur.sign = !cur.sign;
    return cur;
}
BigInt BigInt::operator + () const{
    return *this;
}
BigInt& BigInt::operator++() {
    *this += BigInt(1);
    return *this;
}
BigInt BigInt::operator++(int) {
    BigInt old = *this;
    operator++();
    return old;
}
BigInt& BigInt::operator--() {
    *this -= BigInt(1);
    return *this;
}
BigInt BigInt::operator--(int) {
    BigInt old = *this;
    operator--();
    return old;
}
//реализация логических операций
bool operator==(const BigInt& first, const BigInt& second) {
    if (first.sign != second.sign) return false;
    if (second.Integer.empty()) {
        if (first.Integer.empty() || first.Integer.size() == 1 && first.Integer[0] == 0) return true;
        return false;
    }
    if (first.Integer.size() != second.Integer.size() || second.Decimal.size() != first.Decimal.size()) {
        return false;
    }
    for (int i = 0; i < first.Integer.size(); i++) {
        if (first.Integer[i] != second.Integer[i]) return false;
    }
    for (int i = 0; i < first.Decimal.size(); i++) {
        if (first.Decimal[i] != second.Decimal[i]) return false;
    }
    return true;
}

bool operator < (const BigInt& first, const BigInt& second) {
    if (first == second) return false;
    if (first.sign){
        if (second.sign) return (-second < -first);
        else return true;
    } else if(second.sign) return false;
    else {
        if (first.Integer.size() != second.Integer.size()) {
            return first.Integer.size() < second.Integer.size();
        } else{
            for(int i = 0; i < first.Integer.size(); i++) {
                if(first.Integer[i] != second.Integer[i]) {
                    return first.Integer[i] < second.Integer[i];
                }
            }
            for(int i = 0; i < min(first.Decimal.size(), second.Decimal.size()); i++) {
                if(first.Decimal[i] != second.Decimal[i]) {
                    return first.Decimal[i] < second.Decimal[i];
                }
            }
        }
        if(first.Decimal.size() < second.Decimal.size()) {
            return true;
        }
        else {
            return false;
        }
    }
}

bool operator <= (const BigInt& first, const BigInt& second) {
    return (first < second || first == second);
}

bool operator > (const BigInt& first, const BigInt& second) {
    return !(first <= second);
}

bool operator >= (const BigInt& first, const BigInt& second) {
    return !(first < second);
}

bool operator != (const BigInt& first, const BigInt& second) {
    return !(first == second);
}

//Реализация бинарных операций
BigInt operator + (const BigInt& first, const BigInt& second) {
    if(first.sign) {
        if(!second.sign) {
            return -((-first) + (-second));
        } else{
            return (second - (-first));
        }
    } else if(second.sign) return (first - (-second));

    BigInt sum_ans;
    int Decimal_sum_left = 0;
    int Decimal_sz_max = (int)max(first.Decimal.size(), second.Decimal.size());
    sum_ans.Decimal.resize(Decimal_sz_max);
    for(int i = Decimal_sz_max - 1; i >= 0; i--) {
        if(i >= first.Decimal.size()) {
            int sum_Decimal = (second.Decimal[i] + Decimal_sum_left);
            sum_ans.Decimal[i] = sum_Decimal % 10;
            Decimal_sum_left = sum_Decimal / 10;
        }
        else if (i >= second.Decimal.size()) {
            int sum_Decimal = (first.Decimal[i] + Decimal_sum_left);
            sum_ans.Decimal[i] = sum_Decimal % 10;
            Decimal_sum_left = sum_Decimal / 10;
        } else {
            int sum_Decimal = (first.Decimal[i] + second.Decimal[i] + Decimal_sum_left);
            sum_ans.Decimal[i] = sum_Decimal % 10;
            Decimal_sum_left = sum_Decimal / 10;
        }
    }
    int Integer_sz_max = (int)max(first.Integer.size(), second.Integer.size());
    int prev_Integer_size = (int)first.Integer.size();
    int prev_second_Integer_size = (int)second.Integer.size();
    sum_ans.Integer.resize(Integer_sz_max);
    int Integer_sum_left = Decimal_sum_left;
    for(int i = 0; i < Integer_sz_max; i++) {
        if(prev_Integer_size - i - 1 < 0) {
            int Integer_sum = second.Integer[prev_second_Integer_size - i - 1] + Integer_sum_left;
            sum_ans.Integer[Integer_sz_max - i - 1] = Integer_sum % 10;
            Integer_sum_left = Integer_sum / 10;
        } else if(prev_second_Integer_size - i - 1 < 0) {
            int Integer_sum = first.Integer[prev_Integer_size - i - 1] + Integer_sum_left;
            sum_ans.Integer[Integer_sz_max - i - 1] = Integer_sum % 10;
            Integer_sum_left = Integer_sum / 10;

        } else{
            int Integer_sum = first.Integer[prev_Integer_size - i - 1] +
                              second.Integer[prev_second_Integer_size - i - 1] + Integer_sum_left;
            sum_ans.Integer[Integer_sz_max - i - 1] = Integer_sum % 10;
            Integer_sum_left = Integer_sum / 10;
        }
    }
    if(Integer_sum_left > 0){
        sum_ans.Integer.insert(sum_ans.Integer.begin(), Integer_sum_left);
    }
    sum_ans.remove_zeros();
    return sum_ans;
}
BigInt operator - (const BigInt& first, const BigInt& second) {
    if(second.sign) return first + (-second);
    else if(first.sign) return -((-first) + second);
    else if(first < second) return -(second - first);
    BigInt sub_ans;
    //Decimal
    int Decimal_sz_max = (int)max(first.Decimal.size(), second.Decimal.size());
    sub_ans.Decimal.resize(Decimal_sz_max);
    int Decimal_sub_left = 0;
    for (int i = Decimal_sz_max - 1; i >= 0; i--) {
        int fir_d_sz = (int) (first.Decimal.size() - i - 1);
        int sec_d_sz = (int) (second.Decimal.size() - i - 1);
        if(fir_d_sz < 0) {
            int sub_Decimal = -second.Decimal[i] - Decimal_sub_left;
            if(sub_Decimal < 0) {
                sub_Decimal += 10;
                Decimal_sub_left = 1;
            } else{
                Decimal_sub_left = 0;
            }
            sub_ans.Decimal[i] = sub_Decimal;
        }
        else if ((sec_d_sz - i - 1) < 0) {
            int sub_Decimal = first.Decimal[i] - Decimal_sub_left;
            if(sub_Decimal < 0) {
                sub_Decimal += 10;
                Decimal_sub_left = 1;
            } else{
                Decimal_sub_left = 0;
            }
            sub_ans.Decimal[i] = sub_Decimal;
        } else {
            int sub_Decimal = first.Decimal[i] - second.Decimal[i] - Decimal_sub_left;
            if(sub_Decimal < 0) {
                sub_Decimal += 10;
                Decimal_sub_left = 1;
            } else{
                Decimal_sub_left = 0;
            }
            sub_ans.Decimal[i] = sub_Decimal;
        }
    }
    //Integer
    int Integer_sz_max = (int)max(first.Integer.size(), second.Integer.size());
    int prev_Integer_size = (int)first.Integer.size();
    int prev_second_Integer_size = (int)second.Integer.size();
    sub_ans.Integer.resize(Integer_sz_max);
    int Integer_sub_left = Decimal_sub_left;
    for(int i = 0; i < Integer_sz_max; i++) {
        if(prev_Integer_size - i - 1 < 0) {
            int sub_Integer = -second.Integer[prev_second_Integer_size - i - 1] - Integer_sub_left;
            if(sub_Integer < 0) {
                sub_Integer += 10;
                Integer_sub_left = 1;
            } else{
                Integer_sub_left = 0;
            }
            sub_ans.Integer[Integer_sz_max - i - 1] = sub_Integer;
        } else if(prev_second_Integer_size - i - 1 < 0) {
            int sub_Integer = first.Integer[prev_Integer_size - i - 1] - Integer_sub_left;
            if(sub_Integer < 0) {
                sub_Integer += 10;
                Integer_sub_left = 1;
            } else {
                Integer_sub_left = 0;
            }
            sub_ans.Integer[Integer_sz_max - i - 1] = sub_Integer;
        } else{
            int sub_Integer = first.Integer[prev_Integer_size - i - 1] - second.Integer[prev_second_Integer_size - i - 1] - Integer_sub_left;
            if(sub_Integer < 0) {
                sub_Integer += 10;
                Integer_sub_left = 1;
            } else {
                Integer_sub_left = 0;
            }
            sub_ans.Integer[Integer_sz_max - i - 1] = sub_Integer;
        }
    }
    sub_ans.remove_zeros();
    return sub_ans;
}
BigInt operator * (const BigInt& first, const BigInt& second) {
    vector <int> all_first;
    all_first.reserve(first.Integer.size() + first.Decimal.size());
    for(auto &x : first.Integer) {
        all_first.push_back(x);
    }
    if(first.Decimal.size() > 1 || first.Decimal[0] != 0) {
        for(auto &x : first.Decimal) {
            all_first.push_back(x);
        }
    }
    vector <int> all_second;
    all_second.reserve(second.Integer.size() + second.Decimal.size());
    for(auto &x : second.Integer) {
        all_second.push_back(x);
    }
    if(second.Decimal.size() > 2 || second.Decimal[0] != 0) {
        for(auto &x : second.Decimal) {
            all_second.push_back(x);
        }
    }
    int first_d_sz = 0;
    if(first.Decimal.size() > 1 || first.Decimal[0] != 0) {
        first_d_sz = (int) first.Decimal.size();
    }
    int second_d_sz = 0;
    if(second.Decimal.size() > 1 || second.Decimal[0] != 0) {
        second_d_sz = (int) second.Decimal.size();
    }
    int get_sub = first_d_sz - second_d_sz;
    for(int i = 0; i < get_sub; i++) {
        all_second.push_back(0);
    }
    get_sub = second_d_sz - first_d_sz;
    for(int i = 0; i < get_sub; i++) {
        all_first.push_back(0);
    }
    int all_sz = (int)(all_first.size() + all_second.size() + 2);
    vector <int> result(all_sz, 0);
    int df_pos = 0;
    for(int i = (int) all_second.size() - 1; i >= 0; i--) {
        if(all_second[i] == 0) {
            df_pos++;
            continue;
        }
        int mult_left = 0;
        for(int j = (int) all_first.size() - 1; j >= 0; j--) {
            int all_mult = all_second[i] * all_first[j] + mult_left;
            int cur_index = (int)(all_sz - (all_first.size() - j) - df_pos);
            result[cur_index] += all_mult % 10;
            if(result[cur_index] > 9) {
                result[cur_index - 1] += result[cur_index] / 10;
                result[cur_index] %= 10;
            }
            mult_left = all_mult / 10;
        }
        if(mult_left > 0) {
            result[all_sz - all_first.size() - 1 - df_pos] += mult_left;
        }
        df_pos++;
    }
    int sz_without_Decimal = (int) (result.size() - first_d_sz - second_d_sz - abs(first_d_sz - second_d_sz)) - 1;
    BigInt all_res;
    for(int i = 0; i <= sz_without_Decimal; i++) {
        all_res.Integer.push_back(result[i]);
    }
    for(int i = sz_without_Decimal + 1; i < result.size(); i++) {
        all_res.Decimal.push_back(result[i]);
    }
    all_res.remove_zeros();
    if((first.sign && !second.sign) || (second.sign && !first.sign)) {
        all_res.sign = true;
    }
    return all_res;
}
BigInt prev_divide(BigInt mid) {
    vector <int> all_first;
    all_first.reserve(mid.Integer.size() + mid.Decimal.size());
    for(auto &x : mid.Integer) {
        all_first.push_back(x);
    }
    if(mid.Decimal.size() > 1 || mid.Decimal[0] != 0) {
        for(auto &x : mid.Decimal) {
            all_first.push_back(x);
        }
    }
    for(int i = 0; i < 100; i++) {
        all_first.push_back(0);
    }
    BigInt ans;
    long long cur_left_divide = 0;
    for (int i = 0; i < all_first.size(); i++) {
        long long cur_res = all_first[i] + cur_left_divide * 10;
        if(i < mid.Integer.size()) ans.Integer.push_back((int)(cur_res / 2));
        else ans.Decimal.push_back((int)(cur_res / 2));
        cur_left_divide = cur_res % 2;
    }
    ans.remove_zeros();
    return ans;
}
BigInt operator / (const BigInt &first, const BigInt &second) {
    if(first.Integer.size() == 1 && first.Integer[0] == 0 && first.Decimal.size() == 1 && first.Decimal[0] == 0) {
        BigInt ans(0);
        return ans;
    }
    if(second.Integer.size() == 1 && second.Integer[0] == 0 && second.Decimal.size() == 1 && second.Decimal[0] == 0) {
        BigInt ans(0);
        return ans;
    }
    vector <int> all_first;
    all_first.reserve(first.Integer.size() + first.Decimal.size());
    for(auto &x : first.Integer) {
        all_first.push_back(x);
    }
    if(first.Decimal.size() > 1 || first.Decimal[0] != 0) {
        for(auto &x : first.Decimal) {
            all_first.push_back(x);
        }
    }
    BigInt l;
    l.get_max();
    l.remove_zeros();
    l = -l;
    BigInt r;
    r.get_max();
    r.remove_zeros();
    BigInt esp;
    esp.esp();
    while((r - l) > esp) {
        BigInt mid;
        mid.remove_zeros();
        mid = prev_divide((r + l));
        if((mid * second) < first) {
            l = mid;
        } else{
            r = mid;
        }
    }
    return r;
}
BigInt operator ""_f(const char* s) {
    return BigInt(s);
}
BigInt& BigInt:: operator += (const BigInt& second) {
    return (*this = *this + second);
}
BigInt& BigInt::operator -= (const BigInt& second) {
    return (*this = *this - second);
}
BigInt& BigInt::operator *= (const BigInt& second) {
    return (*this = *this * second);
}
BigInt& BigInt::operator/=(const BigInt &second) {
    return (*this = *this / second);
}
// INPUT

istream &operator>>(istream &is, BigInt &cur) {
    string tmp;
    is >> tmp;
    cur = BigInt(tmp);
    return is;
}

// OUTPUT

ostream &operator<<(ostream &os, const BigInt &cur) {
    if (cur.sign) {
        os << '-';
    }
    for (auto &cur_digit_Integer: cur.Integer) {
        os << cur_digit_Integer;
    }
    if (!cur.Decimal.empty()) {
        if(cur.Decimal.size() > 2 || cur.Decimal[0] != 0) {
            cout << ".";
            for(int i = 0; i < cur.Decimal.size() && i < BigInt::accuracy; i++) {
                os << cur.Decimal[i];
            }
        }
    }
    return os;
}