#include <iostream>
using namespace std;

//Tests are defined inside namespace to avoid clashes between tests for different classes
namespace Poly_test{
void PassTest() 
{ 
    cout << ":::PASS TESTS:::" << endl << endl; // :::PASS TESTS:::

    vector<int> arr_a= {1,2,3,4,5,6};
    Poly a(5,arr_a); 
    cout << "vector<int> arr_a= {1,2,3,4,5,6};\nPoly a(5,arr_a) = " << a << endl<<endl; 

    vector<int> arr_b= {1,2,0,0,0,6};
    Poly b(5,arr_b); 
    cout << "vector<int> arr_b= {1,2,0,0,0,6};\nPoly b(5,arr_b) = " << b << endl<<endl;

    Poly c;
    cout<<"Testing I/O:"<<endl;
    cin>>c;
    cout<<"The entered polynomial was: "<<c<<endl;
}

void FailTest() 
{ 
    cout << "\n:::FAIL TESTS:::" << endl << endl; // :::FAIL TESTS:::
    
    try
    {
        vector<int> arr_a= {1,2,6};
        cout << "vector<int> arr_a= {1,2,6};\nPoly a(5,arr_a) = " ;
        Poly a(5,arr_a); 
        cout<< a << endl<<endl;
    }
    catch (const char* s) 
    { 
        cout << s << endl; 
    }
     
}

void MixedTest() 
{ 
    cout << "\n:::MIXED TESTS:::" << endl << endl; // :::MIXED TESTS:::

    vector<int> arr_a= {1,2,3,4,5,6};
    Poly a(5,arr_a); 

    vector<int> arr_b= {1,2,3,4,5};
    Poly b(4,arr_b); 

    vector<int> arr_c= {1,2,3,4};
    Poly c(3,arr_c); 

    vector<int> arr_d= {1,2,3};
    Poly d(2,arr_d); 

    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    cout<<"c = "<<c<<endl;
    cout<<"d = "<<d<<endl;
    
    d = (a+b)*(c);
    cout << "\nd = ( a + b ) * ( c ) = " << d << endl;
    
}
}
