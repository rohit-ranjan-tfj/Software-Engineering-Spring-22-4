// include required headers
#include <iostream>
#include <algorithm>
using namespace std;

//default T = int
template <typename T = int>
class Fraction_ 
{

    T n_; // numerator
    T d_; // denominator

public:
    
    //default value of fraction is 1
    //this allows for initialising fractions and filling their value later
    Fraction_(T a=1, T b=1) : n_{a}, d_{b} 
    {
        if (d_ == 0)
        {
            //Error thrown to avoid a 0 denominator situation
            throw("Denominator cannot be zero!");
        }
        else if (d_ < 0)
        {
            n_ *= -1;
            d_ *= -1;
        }

        //std::abs avoided to prevent overload issues with different T
        T gcd = __gcd((n_>T(0))?n_:(T(-1)*n_), d_);

        //fraction is always stored in reduced form
        n_ /= gcd;
        d_ /= gcd;
    }

    //default destructor is sufficient
    ~Fraction_()
    {
    }

    //copy constructor copies the data members
    Fraction_(const Fraction_ &f1)
    {
        n_ = f1.n_;
        d_ = f1.d_;
    }

    //input and output operator overloads for all template variations are made friends of the class
    template <typename U>
    friend ostream &operator<<(ostream &out, const Fraction_<U> &c);

    template <typename U>
    friend istream &operator>>(istream &in, Fraction_<U> &c);

    //utility function that returns sign of fraction
    int sign()
    {
        return int(n_ / abs(n_));
    }

    //utility function that returns the double value of fraction
    double to_double()
    {
        return (n_*1.0)/(d_*1.0);
    }

    //reduce function is redundant because fractions are always stored in reduced form
    Fraction_& reduce()
    {
        return *this;
    }

    //unary operations are defined to be inplace following normal semantics

    //inplace negation of the fraction
    Fraction_& negate()
    {
        Fraction_ result(-1*n_, d_);
        *this = result;
        return *this;
    }

    //inplace invert operation
    Fraction_& operator!()
    {
        Fraction_ result(d_, n_);
        *this = result;
        return *this;
    }

    //increment operator for componendo
    Fraction_& operator++()
    {
        Fraction_ result(n_ + d_, d_);
        *this = result;
        return *this;
    }

    //decrement operator for divinendo
    Fraction_& operator--()
    {
        Fraction_ result(n_ - d_, d_);
        *this = result;
        return *this;
    }

    //binary operators are not inplace following usual semantics

    Fraction_ operator+(const Fraction_ &f1)
    {
        int lcm_d = (d_ * f1.d_) / __gcd(d_, f1.d_);
        int num = n_ * (lcm_d / d_) + f1.n_ * (lcm_d / f1.d_);
        return Fraction_(num, lcm_d);
    }

    Fraction_ operator-(const Fraction_ &f1)
    {
        int lcm_d = (d_ * f1.d_) / __gcd(d_, f1.d_);
        int num = n_ * (lcm_d / d_) - f1.n_ * (lcm_d / f1.d_);
        return Fraction_(num, lcm_d);
    }

    Fraction_ operator*(const Fraction_ &f1)
    {
        return Fraction_(n_ * f1.n_, d_ * f1.d_);
    }

    Fraction_ operator/(const Fraction_ &f1)
    {
        //Error thrown to prevent division by zero.
        if (f1.n_==0)
            throw("Division by Zero!");
        else
            return Fraction_(n_ * f1.d_, d_ * f1.n_);
    }

    Fraction_ operator%(const Fraction_ &f1)
    {
        Fraction_ div = *this / f1;
        int floor = (div.n_ * 1.0) / (div.d_ * 1.0);
        return *this - Fraction_(floor * f1.n_, f1.d_);
    }

    //advanced operators are also inplace following usual semantics

    void operator+=(const Fraction_ &f1)
    {
        *this = *this + f1;
    }

    void operator-=(const Fraction_ &f1)
    {
        *this = *this - f1;
    }

    void operator*=(const Fraction_ &f1)
    {
        *this = *this * f1;
    }

    void operator/=(const Fraction_ &f1)
    {
        *this = *this / f1;
    }

    void operator%=(const Fraction_ &f1)
    {
        *this = *this % f1;
    }

    // comparision operators are overloaded to provide complete functionality to fractions

    bool operator<(const Fraction_ &f1)
    {
        return n_*f1.d_ < f1.n_*d_;
    }

    bool operator<=(const Fraction_ &f1)
    {
        return n_*f1.d_ <= f1.n_*d_;
    }

    bool operator>(const Fraction_ &f1)
    {
        return n_*f1.d_ > f1.n_*d_;
    }

    bool operator>=(const Fraction_ &f1)
    {
        return n_*f1.d_ >= f1.n_*d_;
    }

    bool operator==(const Fraction_ &f1)
    {
        return n_*f1.d_ == f1.n_*d_;
    }

    bool operator!=(const Fraction_ &f1)
    {
        return n_*f1.d_ != f1.n_*d_;
    }

    //utility functions defined for gcd and lcm of fractions

    Fraction_ gcd(const Fraction_ &f1)
    {
        int num = __gcd(n_,f1.n_);
        int denom = (d_*f1.d_)/__gcd(d_,f1.d_);
        return Fraction_(num, denom);
    }

    Fraction_ lcm(const Fraction_ &f1)
    {
        int denom = __gcd(d_,f1.d_);
        int num = (n_*f1.n_)/__gcd(n_,f1.n_);
        return Fraction_(num, denom);
    }

};

typedef Fraction_<int> Fraction;

template <typename T = int>
ostream &operator<<(ostream &out, const Fraction_<T> &c)
{
    out << c.n_;
    out << "/" << c.d_ ;
    return out;
}

template <typename T = int>
istream &operator>>(istream &in, Fraction_<T> &c)
{
    cout << "Enter Numerator:";
    T n,d;
    in >> n;
    cout << "Enter Denominator:";
    in >> d;
    Fraction_<int> temp(n,d);
    c = temp;
    return in;
}