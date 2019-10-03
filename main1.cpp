#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;
using std::reverse;

//sign of number
enum sign{
    NEGATIVE = -1,
    POSITIVE = 1
};

//infinity Integer number
struct infinityInt {
    int base; //base of number
    sign mark;
    std::vector<int> number; //my number in memmory, but 123 -> 321
};

void printInfInt(infinityInt& a){
    if (a.mark == NEGATIVE)
        cout << '-';
    std::transform(a.number.rbegin(), a.number.rend(), std::ostream_iterator<int>(cout, ""), [](int t) {
        return t; //
    });
    cout<<std::endl; cout<<"Base: "<<a.base;
}

//for initialise my structure
void intialiseInfInt(infinityInt& a){
    int iBase;
    int t, iter = 0;
    char iSign;
    cin >> iSign;
    if (iSign != '-')
        a.mark = POSITIVE;
    else
        a.mark = NEGATIVE;
    cin >> t;
    while (t != -1) {
        a.number.push_back(t); //Take account of the sign
        cin >> t;
    }
    reverse(a.number.begin(), a.number.end());
    cin >> iBase;
    a.base = iBase;

}

//normalise number
void normaliseInfInt(infinityInt& a){
    int countNormalise = 0;
    if (a.number.size() != 0)
    {
        std::vector<int>::iterator it = a.number.end();
        while (*it == 0) {
            it--; //next rank
            countNormalise++; //count of first 0
        }
        a.number.resize(a.number.size() - countNormalise);
    }

}

bool bigger(infinityInt& a, infinityInt& b){
    if (a.base != b.base){
        cout << "Bad arguments. Not equal base!" << endl;
        return false;
    } else{
        normaliseInfInt(a);
        normaliseInfInt(b);
        if (a.mark > b.mark)
            return true;
        else{
            if (a.mark < b.mark)
                return false;
            if (a.number.size() > b.number.size())
                return true;
            if (a.number.size() < b.number.size())
                return false;
            if (a.number.size() == b.number.size()){
                auto firstBigger, firstLower;
                bool flagFB = true, flagFL = true, flagEQ = false; //TODO: need flagEQ?
                auto y = b.number.end();
                auto x = a.number.end();
                for (x; x >= a.number.begin(); x--){
                    if (flagFB || flagFL) {
                        if (*x > *y && flagFB) {
                            firstBigger = x;
                            flagFB = false;
                            if (firstBigger == a.number.end()) return true;
                        } else if (*x < *y && flagFL) {
                            firstLower = x;
                            flagFL = false;
                            if (firstLower == a.number.end()) return false;
                        } else flagEQ = true;
                        y--;
                    }
                    else
                        break;
                }
                if (firstBigger > firstLower) return true;
                else
                    return false;
            }
        }
    }
    return false;
}

bool smaller(infinityInt& a, infinityInt& b){
    return !bigger(a,b);
}

bool equal(infinityInt& a, infinityInt& b){
        if (a.base != b.base){
            cout << "Bad arguments. Not equal base!" << endl;
            return false;
        } else{
            normaliseInfInt(a);
            normaliseInfInt(b);
            if (a.mark > b.mark)
                return false;
            else{
                if (a.mark < b.mark)
                    return false;
                if (a.number.size() > b.number.size())
                    return false;
                if (a.number.size() < b.number.size())
                    return false;
                if (a.number.size() == b.number.size()){
                    bool flagEQ = true;
                    auto y = b.number.end();
                    auto x = a.number.end();
                    for (x; x >= a.number.begin(); x--){
                        if (flagEQ) {
                            if (*x > *y) {
                                flagEQ = false;
                            } else if (*x < *y) {
                                flagEQ = false;
                            }
                            y--;
                        }
                        else
                            break;
                    }
                    return flagEQ;
                }
            }
        }
    return false;
}
//deal absolute value of a and return old a.mark
sign absolute(infinityInt& a){
    sign retValue = a.mark;
    a.mark = POSITIVE;
    return retValue;
}

//sub 2 infinityInt
void subInfInt(infinityInt& a, infinityInt& b){
    int tempSize;
    if (a.base != b.base)
        cout << "Bad arguments. Not equal base!";
    else {
        //find biggest in a and b
        sign markA = absolute(a);
        sign markB = absolute(b);
        int flagBigger;
        if (bigger(a, b)) flagBigger = true;
        else flagBigger = false;

        //equal count elements in numbers
        if (a.number.size() != b.number.size()) {
            if (a.number.size() > b.number.size()) {
                tempSize = b.number.size();
                b.number.resize(a.number.size());
                for (tempSize; tempSize <= b.number.size(); tempSize++)
                    b.number[tempSize] = 0;
            } else {
                tempSize = a.number.size();
                a.number.resize(b.number.size());
                for (tempSize; tempSize <= a.number.size(); tempSize++)
                    a.number[tempSize] = 0;
            }
        }

        if (flagBigger) {
            auto x = a.number.begin();
            auto y = b.number.begin();
            for (x; x <= a.number.end(); x++) {
                if (*x > *y)
                    *x = *x - *y; // a.number[i] = a.number[i] - b.number[i]
                else{
                    *(x+1) =*(x+1) - 1;
                    *x = *x + a.base;
                    *x = *x - *y;
                }
                y++;
            }
            a.mark = markA;
            b.mark = markB;
        }
        else{
            auto x = a.number.begin();
            auto y = b.number.begin();
            for (y; y <= a.number.end(); y++) {
                if (*y > *x)
                    *x = *y - *x; // a.number[i] = a.number[i] - b.number[i]
                else{
                    *(y+1) =*(y+1) - 1;
                    *y = *y + a.base;
                    *x = *y - *x;
                }
                x++;
            }
            a.mark = markB;
            b.mark = markB;
        }
    }
    //normalise results
    normaliseInfInt(a);
    normaliseInfInt(b);
}

//addition 2 InftInt. answer in first argument of function
void additionInfInt(infinityInt& a, infinityInt& b){
    int tempSize;
    if (a.base != b.base)
        cout << "Bad arguments. Not equal base!";
    else{
        //equal count elements in numbers
        if (a.number.size() != b.number.size()) {
            if (a.number.size() > b.number.size()) {
                tempSize = b.number.size();
                b.number.resize(a.number.size());
                for (tempSize; tempSize <= b.number.size(); tempSize++)
                    b.number[tempSize] = 0;
            } else {
                tempSize = a.number.size();
                a.number.resize(b.number.size());
                for (tempSize; tempSize <= a.number.size(); tempSize++)
                    a.number[tempSize] = 0;
            }
        }
        auto x = a.number.begin();
        auto y = b.number.begin();
        int baseCarry = a.base;
        int carry = 0;
        if (a.mark == b.mark) {
            for (x; x <= a.number.end(); x++) {
                *x = *x + *y + carry; // a.number[i] = a.number[i] + b.number[i] + carry
                y++;
                carry = 0;
                if (*x >= baseCarry) carry = 1; //new carry
            }
        }
        else{
            subInfInt(a, b);
        }
        if (carry != 0){ //
            a.number.resize(a.number.size() + 1);
            a.number[a.number.size()] = carry; //overflow check
        }
        //normalise our elements
        normaliseInfInt(a);
        normaliseInfInt(b);
    }
}

void multipleInfInt(infinityInt& a, infinityInt& b){
    int tempSize;
    if (a.base != b.base)
        cout << "Bad arguments. Not equal base!";
    else {
        //equal count elements in numbers
        if (a.number.size() != b.number.size()) {
            if (a.number.size() > b.number.size()) {
                tempSize = b.number.size();
                b.number.resize(a.number.size());
                for (tempSize; tempSize <= b.number.size(); tempSize++)
                    b.number[tempSize] = 0;
            } else {
                tempSize = a.number.size();
                a.number.resize(b.number.size());
                for (tempSize; tempSize <= a.number.size(); tempSize++)
                    a.number[tempSize] = 0;
            }
        }
        auto x = a.number.begin();
        auto y = b.number.begin();
        int baseCarry = a.base;
        int carry = 0;
        for (x; x <= a.number.end(); x++){
            (long long) *x = *x * *y + carry;
            y++;
            carry = 0;
            if (*x >= baseCarry) carry++;
        }
    }

}


enum shifts{
    LEFT,
    RIGHT
};

infinityInt operator*(int v) const {
    infinityInt res = *this;
    res *= v;
    return res;
}

void trim() {
    while(!a.empty() && !a.back()) {
        a.pop_back();
    }
    if(a.empty()) {
        mark = 1;
    }
}

friend pair<infinityInt, infinityInt> divmod(const infinityInt &a1, const infinityInt &b1) {
    long long norm = a1.base / (b1.number.back() + 1);
    infinityInt a = a1.absolute() * norm;
    infinityInt b = b1.absolute() * norm;
    infinityInt q, r;
    q.number.resize(sizeof(a.number));
    for(long long i = sizeof(a.number) - 1; i >= 0; --i) {
        r *= base;
        r += a.number[i];
        long long s1 = sizeof(r.number) <= sizeof(b.number) ? 0 : r.number[sizeof(b.number)];
        long long s2 = sizeof(r.number) <= sizeof(b.number) - 1 ? 0 : r.number[sizeof(b.number) - 1];
        long long d = ((long long)a1.base * s1 + s2) / b.number.back();
        r -= b * d;
        while(r < 0) {
            r += b;
            --d;
        }
        q.number[i] = d;
    }
    q.mark = a1.mark * b1.mark;
    r.mark = a1.mark;
    q.trim();
    r.trim();
    return {q, r / norm};
}

infinityInt operator/(const infinityInt &v) const {
    return divmod(*this, v).first;
}

infinityInt operator%(const infinityInt &v) const {
    return divmod(*this, v).second;
}

bool isZero() const {
    return a.empty() || (a.size() == 1 && !a[0]);
}

friend infinityInt gcd(const infinityInt &a, const infinityInt &b) {
    return b.isZero() ? a : gcd(b, a % b);
}


int main() {

    infinityInt testInt;
    intialiseInfInt(testInt);

    printInfInt(testInt);

    additionInfInt(testInt, testInt);
    printInfInt(testInt);

    infinityInt secondTestInt;
    intialiseInfInt(secondTestInt);

    cout << bigger(secondTestInt, testInt);
    cout << smaller(secondTestInt, testInt);

    subInfInt(testInt, secondTestInt);
    printInfInt(testInt);

    multipleInfInt(testInt, testInt);
    printInfInt(testInt);


    printInfInt(divmod(testInt, secondTestInt).first);
    printInfInt(divmod(testInt, secondTestInt).second);

    printInfInt(gcd(testInt, secondTestInt));


    //std::cout << "Hello, World!" << std::endl;
    return 0;
}