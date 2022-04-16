#include <iostream> 
using namespace std; 

//Tests are defined inside namespace to avoid clashes between tests for different classes
namespace Fraction_test{
void PassTest() 
{ 
    cout << ":::PASS TESTS:::" << endl << endl; // :::PASS TESTS:::

    Fraction fa(5, 3); 
    cout << "Fraction fa(5, 3) = " << fa << endl; // Fraction fa(5, 3) = 5/3
    
    Fraction fb(7, 9); 
    cout << "Fraction fb(7, 9) = " << fb << endl; // Fraction fb(7, 9) = 7/9
    
    cout << "fa + fb = " << (fa + fb) << endl; // fa + fb = 22/9
}

void FailTest() 
{ 
    cout << ":::FAIL TESTS:::" << endl << endl; // :::FAIL TESTS:::

    try 
    { 
        cout << "Fraction(1, 0): "; 
        Fraction f1(1, 0); 
    }
    catch (const char* s) 
    { 
        cout << s << endl; 
    } // Fraction(1, 0): Denominator cannot be zero!

    Fraction f1(5, 12), f2(0, 1), f3;
    try 
    { 
        cout << "Binary Divide: f3 = " << f1 << " / " << f2 << ": ";
        f3 = f1 / f2; 
        cout << f3 << endl;
    }
    catch (const char* s) 
    { 
        cout << s << endl; 
    } // Binary Divide: f3 = 5/12 / 0: Division by Zero!
}

void MixedTest() 
{ 
    cout << ":::MIXED TESTS:::" << endl << endl; // :::MIXED TESTS:::

    Fraction f1(2, 3), f2(8), f3(5, 6), f4;
    cout << "f1 = " << f1 << " f2 = " << f2 << " f3 = " << f3 << " f4 = " << f4 << endl;
    // f1 = 2/3 f2 = 8 f3 = 5/6 f4 = 1
    f4 = (f1 + f2) / (f1 - f2) + !f3 - f2 * f3;
    cout << "f4 = (f1 + f2) / (f1 - f2) + !f3 - f2 * f3 = " << f4 << endl;
    // f4 = (f1 + f2) / (f1 - f2) + !f3 - f2 * f3 = -1097/165
}
}
