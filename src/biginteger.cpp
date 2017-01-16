#include "biginteger.h"
#include <QRegExp>

BigInteger::BigInteger() {

}
BigInteger::BigInteger(long long num)
{
    number = QString::number(num);
}
BigInteger::BigInteger(QString str)
{
    this->setString(str);
}

QString BigInteger::toString() {
    return number;
}
long long BigInteger::toLong() {
    return number.toLongLong();
}
void BigInteger::setString(QString str) {
    if(!QRegExp("-?[0-9]+").exactMatch(str))
        str = "0";
    number = str;
    this->dropZeros();
    if(number == "-0")
        number = "0";
}
BigInteger BigInteger::dropZeros() {
    bool isNeg = this->isNegative();
    int i = isNeg ? 1:0;

    while(number[i] == '0')
        i++;

    if(i==number.size()) i--;
    number = number.mid(i);

    if(isNeg) this->negate();

    return *this;
}
BigInteger BigInteger::negate() {
    if(number == "0")
        return *this;

    if(number[0] == '-')
        number = number.mid(1);
    else
        number.insert(0, '-');

    return *this;
}
bool BigInteger::isNegative() {
    return (number[0] == '-');
}
BigInteger BigInteger::abs() {
    QString a;
    if(this->isNegative())
        a = this->toString().mid(1);
    else
        a = this->toString();

    return BigInteger(a);
}
int BigInteger::length() {
    if(this->isNegative())
        return number.size() - 1;
    return number.size();
}
bool BigInteger::isEven() {
    return ((number[number.size() - 1].digitValue() % 2) == 0);
}
BigInteger BigInteger::toBase(unsigned int base) {
    if(base < 2 || base > 10)
        return -1;

    if(this->isNegative())
        return this->abs().toBase(base).negate();

    QString ans;
    while (*this >= 1) {
        ans.insert(0, (*this % base).toString());
        *this /= base;
    }
    return BigInteger(ans);
}
BigInteger BigInteger::fromBase(unsigned int base) {
    if(base < 2 || base > 10)
        return -1;

    if(this->isNegative())
        return this->abs().fromBase(base).negate();

    BigInteger ans = 0;
    for(int i=0; i<number.size(); i++) {
        ans *= base;
        ans += number[i].digitValue();
    }
    return ans;
}

BigInteger BigInteger::add(BigInteger other) {
    if(this->isNegative() || other.isNegative()) {
        if(this->isNegative() && !other.isNegative())
            return other.subtract(this->abs());
        if(!this->isNegative() && other.isNegative())
            return this->subtract(other.abs());
        else
            return this->abs().add(other.abs()).negate();
    }
    QString result;
    QString num1 = number,
            num2 = other.toString();

    int diff = qAbs(num1.size() - num2.size());
    for(int i=0; i<diff; i++)
        (num1.size() > num2.size() ? num2:num1).insert(0, "0");
    int c=0;
    for(int i=num1.size()-1; i>=0; i--) {
        int s = (num1[i].digitValue()) + (num2[i].digitValue()) + c;
        if(s < 10 || i == 0) {
            c = 0;
            result.insert(0, QString::number(s));
        }
        else {
            c = 1;
            result.insert(0, QString::number(s % 10));
        }
    }

    return BigInteger(result);
}
BigInteger BigInteger::subtract(BigInteger other) {
    if(this->isNegative() || other.isNegative()) {
        if(this->isNegative() && !other.isNegative())
            return other.add(this->abs()).negate();
        if(!this->isNegative() && other.isNegative())
            return this->add(other.abs());
        else
            return this->abs().subtract(other.abs()).negate();
    }
    if(other > *this)
        return other.subtract(*this).negate();

//    qDebug() << this->toString() << "-" << other.toString();

    QString num1 = this->toString(),
            num2 = other.toString();
    QString result;

    int diff = qAbs(num1.size() - num2.size());
    for(int i=0; i<diff; i++)
        (num1.size() > num2.size() ? num2:num1).insert(0, "0");

    for(int i=num1.size()-1; i>=0; i--) {
        int sub = num1[i].digitValue() - num2[i].digitValue();
        if(sub < 0) {
            sub += 10;
            for(int j=i; j>0; j--) {
                if(num1[j-1] != '0') {
                    num1[j-1] = QString::number(num1[j-1].digitValue() - 1)[0];
                    break;
                } else {
                    num1[j-1] = '9';
                }
            }
        }
        result.insert(0, QString::number(sub));
    }
    return BigInteger(result);
}
BigInteger BigInteger::multiply(BigInteger other) {
    if(this->isNegative() || other.isNegative()) {
        if(this->isNegative() && other.isNegative())
            return this->abs().multiply(other.abs());
        else
            return this->abs().multiply(other.abs()).negate();
    }

    BigInteger result("0");
    QString num1 = number,
            num2 = other.toString();
    int z = 0;
    QString r;
    for(int i=num1.size()-1; i>=0; i--) {
        r = "";
        for(int k=0; k<z; k++) r.insert(0, "0");
        int c = 0;
        for(int j=num2.size()-1; j>=0; j--) {
            int m = num1[i].digitValue() * num2[j].digitValue() + c;
            if(m > 9) {
                c = m / 10;
                m %= 10;
            }
            else
                c = 0;
            r.insert(0, QString::number(m));
            //qDebug() << "r: " << r << i << j;
        }
        r.insert(0, QString::number(c));
        result = result.add(BigInteger(r));
        z++;
    }
    return result;
}
BigInteger BigInteger::divide(BigInteger other) {
    if(other == 0) //zero division
        return -1;

    if(this->isNegative() || other.isNegative()) {
        if(this->isNegative() && other.isNegative())
            return this->abs().divide(other.abs());
        else
            return this->abs().divide(other.abs()).negate();
    }
    BigInteger q=0, d(this->toString());

    while(d - other >= 0) {
        d -= other;
        q += 1;
    }
    //qDebug() << q.toString() << d.toString();
    return BigInteger(q);
}
BigInteger BigInteger::mod(BigInteger other) {
    return *this - (this->divide(other) * other);
}
BigInteger BigInteger::pow(unsigned int exponent) {
    //if(exponent < 0) return BigInteger(0);
    if(exponent == 0) return BigInteger(1);
    if(exponent == 1) return *this;

    BigInteger base = *this;  // we dont want to change the value of *this
    BigInteger ans = 1;
    while(exponent > 0) {

        if(exponent % 2 == 1)
            ans *= base;

        exponent /= 2;
        base *= base;

    }
    return ans;
}
BigInteger BigInteger::fact() {
    if (*this > 500) // the calculation will take a very long time! (1135 digits)
        return -1;

    if(*this < 1) // negative fact
        return -1;

    BigInteger F(1);
    for(BigInteger i=2; i<= *this; i+=1) {
        F *= i;
    }
    return F;
}
BigInteger BigInteger::sqrt() {
    return this->root(2);
}
BigInteger BigInteger::root(unsigned int r) {
    if(r%2 == 0 && this->isNegative()) // even root with negative value!
        return -1;

    BigInteger i = BigInteger(10).pow(number.size() / 2);
    BigInteger step = i;
    QString sstep;
    while (step >= 1){
        while (i.pow(r) <= *this) {
            i += step;
        }
        i -= step;
        //instead of step /= 10, right shift step
        //step /= 10;
        sstep = step.toString();
        for(int i=sstep.size()-1; i>0; i--)
            sstep[i] = sstep[i-1];
        sstep[0] = '0';
        step.setString(sstep);
    }
    return i;
}

int BigInteger::compareTo(BigInteger other) {

    this->dropZeros();
    other.dropZeros();
    QString num1 = this->toString(),
            num2 = other.toString();


    if(this->isNegative() && !other.isNegative())
        return -1;
    else if(!this->isNegative() && other.isNegative())
        return 1;
    else if(this->isNegative() && other.isNegative()) {
        return -1 * this->abs().compareTo(other.abs());
    }



    if(num1.size() > num2.size())
        return 1;
    else if(num1.size() < num2.size())
        return -1;
    else {
        for(int i=0; i<num1.size(); i++) {
            if(num1[i] > num2[i])
                return 1;
            else if(num1[i] < num2[i])
                return -1;
        }
        return 0;
    }
}

BigInteger BigInteger::operator-() {
    return this->negate();
}

BigInteger operator+(BigInteger n1, const BigInteger &n2) {
    return n1.add(n2);
}
BigInteger operator-(BigInteger n1, const BigInteger &n2) {
    return n1.subtract(n2);
}
BigInteger operator*(BigInteger n1, const BigInteger &n2) {
    return n1.multiply(n2);
}
BigInteger operator/(BigInteger n1, const BigInteger &n2) {
    return n1.divide(n2);
}
BigInteger operator%(BigInteger n1, const BigInteger &n2) {
    return n1.mod(n2);
}
BigInteger operator^(BigInteger n1, const int &exponent) {
    return n1.pow(exponent);
}

BigInteger& BigInteger::operator=(const BigInteger &other) {
    this->number = other.number;
    return *this;
}
BigInteger& BigInteger::operator=(const long long &other) {
    this->number = QString::number(other);
    return *this;
}
BigInteger& BigInteger::operator=(const QString &other) {
    this->setString(other);
    return *this;
}
BigInteger& BigInteger::operator+=(const BigInteger &other) {
    *this = *this + other;
    return *this;
}
BigInteger& BigInteger::operator-=(const BigInteger &other) {
    *this = *this - other;
    return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger &other) {
    *this = *this * other;
    return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger &other) {
    *this = *this / other;
    return *this;
}
BigInteger& BigInteger::operator%=(const BigInteger &other) {
    *this = *this % other;
    return *this;
}
BigInteger& BigInteger::operator^=(const int &exponent) {
    *this = *this ^ exponent;
    return *this;
}

bool operator==(BigInteger n1, const BigInteger &n2) {
    return (n1.compareTo(n2) == 0);
}
bool operator!=(BigInteger n1, const BigInteger &n2) {
    return (n1.compareTo(n2) != 0);
}
bool operator>(BigInteger n1, const BigInteger &n2) {
    return (n1.compareTo(n2) == 1);
}
bool operator>=(BigInteger n1, const BigInteger &n2) {
    return (n1.compareTo(n2) > -1);
}
bool operator<(BigInteger n1, const BigInteger &n2) {
    return (n1.compareTo(n2) == -1);
}
bool operator<=(BigInteger n1, const BigInteger &n2) {
    return (n1.compareTo(n2) < 1);
}
