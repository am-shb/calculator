#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include<QString>

class BigInteger
{
private:
    QString number;
    BigInteger dropZeros();

public:
    BigInteger();
    BigInteger(long long num);
    BigInteger(QString str);

    QString toString();
    long long toLong();
    void setString(QString str);
    bool isNegative();
    BigInteger negate();
    BigInteger abs();
    int length();
    bool isEven();
    // !important: base should be less than 10
    BigInteger toBase(unsigned int base);
    BigInteger fromBase(unsigned int base);

    BigInteger add(BigInteger other);
    BigInteger subtract(BigInteger other);
    BigInteger multiply(BigInteger other);
    BigInteger divide(BigInteger other);
    BigInteger mod(BigInteger other);
    BigInteger pow(unsigned int exponent); //fast binary power
    BigInteger fact();
    BigInteger sqrt();
    BigInteger root(unsigned int r);

    int compareTo(BigInteger other);

    /*************************
    **  operator overloads  **
    *************************/
    //unary operators
    BigInteger operator-();

    //binary arithmetic operators
    friend BigInteger operator+(BigInteger n1, const BigInteger &n2);
    friend BigInteger operator-(BigInteger n1, const BigInteger &n2);
    friend BigInteger operator*(BigInteger n1, const BigInteger &n2);
    friend BigInteger operator/(BigInteger n1, const BigInteger &n2);
    friend BigInteger operator%(BigInteger n1, const BigInteger &n2);
    friend BigInteger operator^(BigInteger n1, const int &exponent);

    //assignment operators
    BigInteger& operator=(const BigInteger &other);
    BigInteger& operator=(const long long &other);
    BigInteger& operator=(const QString &other);
    BigInteger& operator+=(const BigInteger &other);
    BigInteger& operator-=(const BigInteger &other);
    BigInteger& operator*=(const BigInteger &other);
    BigInteger& operator/=(const BigInteger &other);
    BigInteger& operator%=(const BigInteger &other);
    BigInteger& operator^=(const int &exponent);

    //relational operators
    friend bool operator==(BigInteger n1, const BigInteger &n2);
    friend bool operator!=(BigInteger n1, const BigInteger &n2);
    friend bool operator>(BigInteger n1, const BigInteger &n2);
    friend bool operator>=(BigInteger n1, const BigInteger &n2);
    friend bool operator<(BigInteger n1, const BigInteger &n2);
    friend bool operator<=(BigInteger n1, const BigInteger &n2);
};

#endif // BIGINTEGER_H
