// include required headers
#include <iostream>
#include <vector>
using namespace std;

//default T = int
template<typename T = int> 
class Poly_ 
{
    vector<T> coeff_;  //coeff_ vector stores coeffs correspoding to it's index as degree
    int deg_; // degree of the polynomial

public:

    //default polynomial is just the constant 0
    Poly_(int deg=0, vector<T> arr = {0}): deg_{deg}
    {
        if(arr.size()!=deg_+1)
        {
            throw("Coefficients array size mismatch!");
        }
        for(int i=0;i<=deg;i++)
        {
            coeff_.push_back(arr[i]);
        }
    }

    //default destructor is sufficient
    ~Poly_()
    {

    }

    //copy constructor copies data members
    Poly_( Poly_ &other)
    {
        deg_ = other.deg_;
        coeff_.clear();

        for(int i=0;i<=deg_;i++)
        {
            coeff_.push_back(other.coeff_[i]);
        }
    }

    //inplace negate operator
    Poly_& operator!()
    {
        for(int i=0;i<coeff_.size();i++)
        {
            coeff_[i]*=-1;
        }
        return *this;
    }

    // arithmetic operators are overloaded using usual semantics
    Poly_ operator+( Poly_ &other)
    {
        int max_deg = max(deg_,other.deg_);
        vector<int> vect(max_deg+1, 0);
        Poly_ temp(max_deg,vect);
        for(int i=0;i<=min(deg_,other.deg_);i++)
        {
            temp.coeff_[i] = coeff_[i]+other.coeff_[i];
        }
        if(deg_>other.deg_)
        {
            for(int i=other.deg_+1;i<=deg_;i++)
            {
                temp.coeff_[i] = coeff_[i];
            }
        }
        else
        {
            for(int i=deg_+1;i<=other.deg_;i++)
            {
                temp.coeff_[i] = other.coeff_[i];
            }
        }
        return temp;
    }

    Poly_ operator-( Poly_ &other)
    {
        Poly_ temp = other;
        !temp;
        return *this + temp;
    }

    Poly_ operator*( Poly_ &other)
    {
        int max_deg = deg_+other.deg_;
        vector<int> vect(max_deg+1, 0);
        Poly_ temp(max_deg,vect);
        for(int i =0;i<=deg_;i++)
        {
            for(int j=0;j<=other.deg_;j++)
            {
                temp.coeff_[i+j]+=coeff_[i]*other.coeff_[j];
            }
        }
        return temp;
    }

    void operator+=( Poly_ &f1)
    {
        *this = *this + f1;
    }

    void operator-=( Poly_ &f1)
    {
        *this = *this - f1;
    }

    void operator*=(Poly_ &f1)
    {
        *this = *this * f1;
    }

    //input and output operator overloads for all template variations are made friends of the class
    template <typename U>
    friend ostream &operator<<(ostream &out, const Poly_<U> &c);

    template <typename U>
    friend istream &operator>>(istream &in, Poly_<U> &c);
};

typedef Poly_<int> Poly;

template <typename T = int>
ostream &operator<<(ostream &out, const Poly_<T> &c)
{
    int flag=0;
    for(int i=c.deg_;i>0;i-=1)
    {
        if(flag==1)
        {
            out<<" + ";
        }
        out<<c.coeff_[i]<<"x^"<<i;
        flag=1;
    }
    if(flag==1)
    {
        out<<" + ";
    }
    out<<c.coeff_[0];
    return out;
}

template <typename T = int>
istream &operator>>(istream &in, Poly_<T> &c)
{
    cout << "Enter degree:";
    int d;
    in >> d;
    vector<T> coeff;
    for(int i=0;i<=d;i++)
    {
        T temp;
        cout<< "Enter coeff at degree "<<i<<":"<<endl;
        in>>temp;
        coeff.push_back(temp);
    }
    Poly temp(d,coeff);
    c = temp;
    return in;
}