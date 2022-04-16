//include directives
#include <iostream>

using namespace std;

//utility function that uses binary search to find element in a given array
//arr - pointer to array to search in
//left - left index of arr to start search from
//right - right index of arr to search till
//key - the element being searched for
//returns -1 if element not found or index in arr
int binary_search(int *arr, int left, int right, int key)
{
    if (right >= left) 
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] > key)
            return binary_search(arr, left, mid - 1, key);
        return binary_search(arr, mid + 1, right, key);
    }
    return -1;
}

//class definition
class PrimalityTest 
{
    static PrimalityTest* _myTest;
    int nStored;// number of Stored Primes
    int *primes;// pointer to Buffer
    int bufsize;// size of the buffer
    PrimalityTest(int bufsize);
    ~PrimalityTest();

    public:

    static PrimalityTest& newTest(int bufsize = 100); 
    void test(int n);
};

//constructor function to initialise object
//buffersize - size of the buffer
PrimalityTest::PrimalityTest(int buffersize)
{
    bufsize = buffersize;
    primes = new int[bufsize];
    for(int i=1;i<bufsize;i++)
    {
        primes[i] = 0;
    }
    primes[0]=2;
    nStored = 1;
}

//destructor 
PrimalityTest::~PrimalityTest()
{
    delete(primes);
    free(_myTest);
}

//method to create object if not created yet and to resize buffer array if buffer size is changed
//bufsize - size of the buffer
//returns reference to only object of PrimalityTest class
PrimalityTest& PrimalityTest::newTest(int bufsize)
{
    if(_myTest == NULL)
    {
        _myTest= new PrimalityTest(bufsize);
    }
    else if(_myTest->bufsize!=bufsize)
    {
        if(bufsize<_myTest->nStored)
        {
            cout<<"Buffer Overflow!"<<endl;
            exit(0);
        }
        //new buffer array created
        int *new_primes = new int[bufsize];
        //copying elements to new buffer
        for(int i=0;i<bufsize;i++)
        {
            if(i<_myTest->nStored)
            {
                new_primes[i] = _myTest->primes[i];
            }
            else
            {
                new_primes[i] = 0;
            }
        }
        _myTest->primes = new_primes;
    }
    return *_myTest;
}

//method to test for primality
//n - integer being tested
//return - none, output is printed
void PrimalityTest::test(int n)
{   
    //flag variable which turns 0 when element is surely non-prime
    int prime=1;

    //largest prime stored in buffer till now
    int last_prime_now=0;
    if(nStored!=0)
    {
        last_prime_now = primes[nStored-1];
    }

    //quick check to determine non-primality
    if(n%2==0 || n%3==0 || ((n%6)*(n%6))%6!=1)
    {
        prime=0;
    }
    //buffer is filled with atleast all primes <= sqrt(n)   
    else if(last_prime_now*last_prime_now<=n)
    {
        for(int i =last_prime_now+1;i*i<=n;i++)
        {
            int flag=1;
            for(int j=0;j<nStored;j++)
            {
                if(i%primes[j]==0)
                {
                    flag=0;
                    break;
                }
            }
            if(flag==0)
            {
                continue;
            }
            else
            {
                if(nStored>=bufsize)
                    {
                        cout<<"Buffer Overflow!"<<endl;
                        exit(0);
                    }
                    else
                    {
                        primes[nStored] = i;
                        nStored++;
                    }
            }
        }
    }
    //if largest prime stored in buffer is greater than n then binary search for n 
    else if(last_prime_now>=n)
    {
        if(binary_search(primes,0,nStored-1,n)==-1)
        {
            prime=0;
        }
        else
        {
            prime=2;
        }
    }

    //buffer contains all primes <=sqrt(n) and n must be divisible by atleast one of these if non-prime
    if(prime==1)
    {
        for(int j=0;j<nStored;j++)
        {
            if(n%primes[j]==0)
            {
                prime=0;
                break;
            }
        }
    }
    
    //printing required output using flag variable
    if(prime==0)
    {
        cout<<n<<" is not a prime number."<<endl;
        return;
    }
    else
    {
        cout<<n<<" is a prime number."<<endl;
        return;
    }
}

//initialising the static variable of class
PrimalityTest* PrimalityTest::_myTest = NULL;

int main() 
{
    //test cases
    PrimalityTest::newTest().test(2958);
    PrimalityTest::newTest().test(823);
    PrimalityTest::newTest().test(83479);
    return 0;
}