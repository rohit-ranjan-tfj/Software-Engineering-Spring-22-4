#include <iostream>
using namespace std;

//Tests are defined inside namespace to avoid clashes between tests for different classes
namespace Int_test
{
    void PassTest() 
    { 
        cout << ":::PASS TESTS:::" << endl << endl; // :::PASS TESTS:::

        Int a(5); 
        cout << "Int a(5) = " << a << endl; // Int a(5) = 5
        
        Int b(2); 
        cout << "Int b(2) = " << b << endl; // Int b(2) = 2
        
        cout << "a + b = " << (a + b) << endl; // a + b = 7

        cout<<"\nTesting overflow characteristics:"<<endl<<endl;
        for(int i =-16;i<=16;i++)
        {
            Int a(i);
            cout<<"Int("<<i<<"): "<<a<<endl;
        }
    }

    void FailTest() 
    { 
        cout << "\n:::FAIL TESTS:::" << endl << endl; // :::FAIL TESTS:::

        Int a(5); 
        cout << "Int a(5) = " << a << endl; // Int a(5) = 5
        
        Int b(22); 
        cout << "Int b(22) = " << b ; // Int b(22) = 6
        cout<<" Overflow causes wrapping around!"<<endl;
        
        cout << "a + b = " << (a + b); // a + b = -5
        cout<<" Overflow causes wrong sum!"<<endl;
    }

    void MixedTest() 
    { 
        cout << "\n:::MIXED TESTS:::" << endl << endl; // :::MIXED TESTS:::

        Int f1(1), f2(4), f3(6), f4(-7);
        cout << "f1 = " << f1 << " f2 = " << f2 << " f3 = " << f3 << " f4 = " << f4 << endl;
        //f1 = 1 f2 = 4 f3 = 6 f4 = -7
        f4 = f1 + f4 + f2 - f3 +(f3%f2);
        cout << "f4 = f1 + f4 + f2 - f3 +(f3\%f2) = " << f4 << endl;
        // f4 = f1 + f4 + f2 - f3 +(f3%f2) = -6
    }
}
