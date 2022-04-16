#include <iostream>
using namespace std;

#include "Fraction.h" 
#include "Poly.h"
#include "Int.h"
#include "Fraction_test.h" 
#include "Poly_test.h"
#include "Int_test.h"

//All the three UDTs can be tested from here using appropriate namespaces
int main()
{
    int choice;
    cout<<"Enter choice for testing:\n\n1.Fraction\n2.Int\n3.Poly\n"<<endl;
    cin>>choice;
    if(choice==1)
    {
        Fraction_test::PassTest();
        Fraction_test::FailTest();
        Fraction_test::MixedTest();
    }
    else if(choice==2)
    {
        Int_test::PassTest();
        Int_test::FailTest();
        Int_test::MixedTest();
    }
    else if(choice==3)
    {
        Poly_test::PassTest();
        Poly_test::FailTest();
        Poly_test::MixedTest();
    }
    else
    {
        cout<<"Wrong Choice!"<<endl;
    }
}