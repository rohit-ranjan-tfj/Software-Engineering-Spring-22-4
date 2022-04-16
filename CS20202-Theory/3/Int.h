// include required headers
#include <iostream>
using namespace std;

// an N-bits integer class with underlying type T
template<typename T = int, unsigned int N = 4>
class Int_ 
{ 
    T v_; // actual value in underlying type T

    //arr stores values of the n bits in the integer
    //the representation conforms to the signed binary representation in common usage in digital computers
    bool arr[N]; 

public:

    Int_(T v=0): v_{v} // default value of integer is 0
    {
        for(int i =0;i<N;i++)
        {
            arr[i] = 0;
        }
        
        int counter = 0;
        //the value is converted to base 2 for storing in the array of bits
        while(v!=0)
        {
            if(counter>=N)
            {
                break;
                //break is implemented because we have exhausted all allocated bits
            }   
            else
                arr[counter] = v%2;
            v=v/2;
            counter++;
        }

        //for negative values, 2's complement is then calculated
        if(v_<0)
        {
            for(int i = 0;i<N;i++)
            {
                if(arr[i]==1)
                {
                    arr[i]=0;
                }
                else
                {
                    arr[i]=1;
                }
            }
            *this = *this + Int_(1);
        }

    }

    //copy contructor to copy data members
    Int_(const Int_ &f1)
    {
        v_ = f1.v_;
        for(int i =0;i<N;i++)
        {
            arr[i] = f1.arr[i];
        }
    }

    //default destructor is sufficient
    ~Int_()
    {
    }

    //addition is implemented using the full adder method
    //the carry for the MSB is ignored due to overflow
    Int_ operator+(const Int_ &other)
    {
        Int_ sum(0);
        bool carry =0;
        for(int i=0;i<N;i++)
        {
            bool a = arr[i];
            bool b = other.arr[i];
            sum.arr[i] = carry ^ (a ^ b);
            carry = (a & b) || (b & carry) || (a & carry);
        }
        return sum;
    }

    //substraction is implemented using binary addition again
    //the second operand is flipped to negate it and then added
    Int_ operator-(const Int_ &other)
    {
        Int_ temp = other;
        for(int i = 0;i<N;i++)
        {
            if(temp.arr[i]==1)
            {
                arr[i]=0;
            }
            else
            {
                temp.arr[i]=1;
            }
        }
        temp = temp + Int_(1);
        return *this + temp;
    }

    //the - operator is also overlaoded as a unary operator following usual semantics
    Int_ operator-()
    {
        Int_ temp = *this;
        for(int i = 0;i<N;i++)
        {
            if(temp.arr[i]==1)
            {
                arr[i]=0;
            }
            else
            {
                temp.arr[i]=1;
            }
        }
        temp = temp + Int_(1);
        return temp;
    }

    //Multiplication and advanced operators are implemented using the actual value representation
    //However the results are converted to Int_ to allow for overflow characteristics
    Int_ operator*(const Int_ &other)
    {
        T new_v = v_*other.v_;
        return Int_(new_v);
    }

    Int_ operator/(const Int_ &other)
    {
        T new_v = v_/other.v_;
        return Int_(new_v);
    }

    Int_ operator%(const Int_ &other)
    {
        T new_v = v_%other.v_;
        return Int_(new_v);
    }

    void operator+=(const Int_ &f1)
    {
        *this = *this + f1;
    }

    void operator-=(const Int_ &f1)
    {
        *this = *this - f1;
    }

    void operator*=(const Int_ &f1)
    {
        *this = *this * f1;
    }

    void operator/=(const Int_ &f1)
    {
        *this = *this / f1;
    }

    void operator%=(const Int_ &f1)
    {
        *this = *this % f1;
    }

    // comparision operators are overloaded to provide complete functionality to fractions
    //further overloads allow for comparing across different types as well

    bool operator<(const Int_ &f1)
    {
        return v_ < f1.v_;
    }

    template<typename U = int>
    bool operator<(U f1)
    {
        return v_ < f1;
    }

    bool operator<=(const Int_ &f1)
    {
        return v_ <= f1.v_;
    }

    template<typename U = int>
    bool operator<=(U f1)
    {
        return v_ <= f1;
    }

    bool operator>(const Int_ &f1)
    {
        return v_ > f1.v_;
    }

    template<typename U = int>
    bool operator>(U f1)
    {
        return v_ > f1;
    }

    bool operator>=(const Int_ &f1)
    {
        return v_ >= f1.v_;
    }

    template<typename U = int>
    bool operator>=(U f1)
    {
        return v_ >= f1;
    }

    bool operator==(const Int_ &f1)
    {
        return v_ == f1.v_;
    }

    template<typename U = int>
    bool operator==(U f1)
    {
        return v_ == f1;
    }

    bool operator!=(const Int_ &f1)
    {
        return v_ != f1.v_;
    }

    template<typename U = int>
    bool operator!=(U f1)
    {
        return v_ != f1;
    }

    //input and output operator overloads for all template variations are made friends of the class
    template<typename U, unsigned int M>
    friend ostream &operator<<(ostream &out, const Int_<U,M> &c);

    template<typename U, unsigned int M>
    friend istream &operator>>(istream &in, Int_<U,M> &c);
};

typedef Int_<int, 4> Int;

//output operator converts the signed binary representation to usual decimal form
template<typename U, unsigned int M>
ostream &operator<<(ostream &out, const Int_<U,M> &c)
{
    Int_<U,M> temp = c;
    if(temp.arr[M-1]==1)
    {
        temp = temp + Int_<U,M>(-1);
        for(int i = 0;i<M;i++)
        {
            if(temp.arr[i]==1)
            {
                temp.arr[i]=0;
            }
            else
            {
                temp.arr[i]=1;
            }
        }
    }
    U sum=0;
    for(int i=M-2;i>=0;i--)
    {
        sum+=temp.arr[i]*1<<i;
    }
    if(c.arr[M-1]==1)
        sum*=-1;
    if(c.arr[M-1]==1 && sum==0)
        sum=-1 * 1<<(M-1);
    out<<sum;
    return out;
}

template<typename U, unsigned int M>
istream &operator>>(istream &in, Int_<U,M> &c)
{
    cout << "Enter Value:";
    U v;
    in >> v;
    Int_<U,M> temp(v);
    c = temp;
    return in;
}
