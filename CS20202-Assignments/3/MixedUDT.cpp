#include <iostream>
using namespace std;

#include "Fraction.h" 
#include "Poly.h"
#include "Int.h"

//The template classes are integrated and tested here
int main()
{
    cout<<"::Testing Fraction_<Int_<int,4u>>::"<<endl<<endl;
    cout<<"Int_<int,4u> a(5),b(3);"<<endl;
    Int_<int,4u> a(5),b(3);
    Fraction_<Int_<int,4u>> f(a,b);
    cout<<"Fraction_<Int_<int,4u>> f(a,b) = "<<f<<endl<<endl;

    cout<<"::Testing Poly_<Int_<int,4u>>::"<<endl<<endl;
    cout<<"vector<Int_<int,4u>> arr_a= {1,2,6};"<<endl;
    vector<Int_<int,4u>> arr_a= {1,2,6};
    Poly_<Int_<int,4u>> q(2,arr_a);
    cout<<"Poly_<Int_<int,4u>> q(2,arr_a) = "<<q<<endl<<endl;

    cout<<"::Testing Poly_<Fraction_<Int_<int,4u>>>::"<<endl<<endl;

    Fraction_<Int_<int,4u>> f1(1,2);
    Fraction_<Int_<int,4u>> f2(2,3);
    Fraction_<Int_<int,4u>> f3(3,4);

    vector<Fraction_<Int_<int,4u>>> arr_b;
    arr_b.push_back(f1);
    arr_b.push_back(f2);
    arr_b.push_back(f3);

    cout<<"vector<Fraction_<Int_<int,4u>>> arr_b = { ";
    for( int i =0;i<arr_b.size();i++)
    {
        cout<<arr_b[i]<<" ";
    }
    cout<<"}"<<endl;
    Poly_<Fraction_<Int_<int,4u>>> p(2,arr_b);
    cout<<"Poly_<Fraction_<Int_<int,4u>>> p(2,arr_b) = "<<p<<endl;
}