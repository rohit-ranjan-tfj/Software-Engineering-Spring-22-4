//include statements
#include <iostream>
#include <list>
#include <vector>

using namespace std;

//class definition for Customer
class Customer 
{
    //name of the customer
    string name; 
    
    //unique id of customer
    int id;  

    //NumCustomer stores the current number of instances of the class 
    //it is static because counting is to be done by class
    static int NumCustomer; 

    public:

    //constructor to initialise data members and assign id
    Customer(string name = "NA");

    //default destructor is used
    // ~Customer(); 

    //operator overloading for output operator
    friend ostream& operator << (ostream &os, const Customer & cust);

    //operator overloading for input operator
    friend istream& operator >> (istream &is, Customer & cust);
};

//class definition for ProductItem
class ProductItem 
{
    //title of product
    string title;

    //unique id of the product
    int id;

    //NumProductItem stores the current number of instances of the class 
    //it is static because counting is to be done by class
    static int NumProductItem;

    //price of product
    float price;

    //number of copies of product
    int copies;

    public:

    //constructor to initialise data members and assign id
    ProductItem(string title = "NA", float price = 0);

    //default destructor is used
    // ~ProductItem();

    //utility function that returns id of instance
    int getid();

    //utility function that increases copies of instance
    void incrementcopies(ProductItem& p);

    //operator overloading for output operator
    friend ostream& operator << (ostream &os, const ProductItem & pi);

    //operator overloading for input operator
    friend istream& operator >> (istream &is, ProductItem & pi);

    //operator overloading for * operator which changes the number of copies of the product
    //a - new number of copies of the product
    //returns a reference to edited product
    ProductItem& operator* (int a);

    //operator overloading for = operator which acts as copy constructor
    //pi - object to copy data members into
    //returns a reference to edited product
    ProductItem& operator= (ProductItem & pi);
};

//class definition for Order
class Order 
{
    //unique id of the order
    int id;

    //flag variable that holds 1 if order has been finalised and can no longer be edited
    int flag;

    //NumOrder stores the current number of instances of the class 
    //it is static because counting is to be done by class
    static int NumOrder;

    //customer associated with the order
    Customer c;

    //vector of all products in the order
    vector<ProductItem> prods;

    public:

    //constructor to initialise data members and assign id
    Order(Customer &in_c);

    //default destructor is used
    // ~Order();

    //utility function that returns id of instance
    int getid();

    //utility function that returns flag of instance
    int getflag();

    //utility function that sets the flag status of the instance
    void setflag();

    //operator overloading for output operator
    friend ostream& operator << (ostream &os, const Order & o);

    //operator overloading for input operator
    friend istream& operator >> (istream &is, Order & o);

    //operator overloading for + operator which adds products to order
    //p - product to be added
    //returns a reference to edited order
    Order & operator+ (ProductItem &p);

    //operator overloading for = operator which acts as copy constructor
    //o - object to copy data members into
    //returns a reference to edited order
    Order & operator= (Order &o);
};

//class definition for ShoppingBasket
class ShoppingBasket 
{
    //unique id of the basket
    int id;

    //NumBasket stores the current number of instances of the class 
    //it is static because counting is to be done by class
    static int NumBasket;

    //customer associated with the basket
    Customer c;

    //list of all orders in the basket
    list<Order> orders;

    public:

    //constructor to initialise data members and assign id
    ShoppingBasket(Customer &in_c);

    //default destructor is used
    // ~ShoppingBasket();

    //operator overloading for output operator
    friend ostream& operator << (ostream &os, const ShoppingBasket & sb);

    //operator overloading for input operator
    friend istream& operator >> (istream &is, ShoppingBasket & sb);

    //operator overloading for + operator which adds order to basket
    //p - order to be added
    //returns a reference to edited basket
    ShoppingBasket & operator+ (Order &p);

    //operator overloading for - operator which removes order from basket
    //orderid - id of order to be removed
    //returns a reference to edited basket
    ShoppingBasket & operator- (int orderid);

    //operator overloading for = operator which acts as copy constructor
    //sb - object to copy data members into
    //returns a reference to edited basket
    ShoppingBasket & operator= (ShoppingBasket &sb);
};

Customer::Customer(string name)
{
    this->name = name;
    this->id = ++NumCustomer;
}

ostream& operator << (ostream &os, const Customer & cust)
{
    os << "Customer name: "<<cust.name<<"\nCustomer id: "<<cust.id;
    return os;
}

istream& operator >> (istream &is, Customer & cust)
{
    cout<<"Enter Customer Name: ";
    is>>cust.name;
    return is;
}

ProductItem::ProductItem(string title, float price)
{
    this->title = title;
    this->id = ++NumProductItem;
    this->price = price;
    this->copies = -1;
}

int ProductItem::getid()
{
    return this->id;
}

void ProductItem::incrementcopies(ProductItem& p)
{
    this->copies+=p.copies;
}

ostream& operator << (ostream &os, const ProductItem & pi)
{
    os<<"Product Title: "<<pi.title<<"\nProduct id: "<<pi.id<<"\nProduct price: "<<pi.price<<"\nProduct copies: "<<pi.copies;
    return os;
}

istream& operator >> (istream &is, ProductItem & pi)
{
    cout<<"Enter Product Title: ";
    is>>pi.title;
    cout<<"Enter Product Price: ";
    is>>pi.price;
    cout<<"Enter Product Copies: ";
    is>>pi.copies;
    return is;
}

ProductItem& ProductItem::operator*(int a)
{
    //temporary object created in free store 
    ProductItem *temp = new ProductItem();
    //the count is decreased because only a copy is being created not a new instance
    NumProductItem--;
    this->operator=(*temp);

    if(this->copies == -1)
    {
        temp->copies = a;
    }
    else
    {
        temp->copies *= a;
    }
    temp->id = this->id;
    return *temp;
}

ProductItem& ProductItem::operator=(ProductItem & pi)
{
    pi.title = this->title;
    pi.price = this->price;
    pi.copies = this->copies;
    return pi;
}

Order::Order(Customer &in_c)
{
    this->id = ++NumOrder;
    this->c = in_c;
    this->flag = 0;
}

ostream& operator << (ostream &os, const Order & o)
{
    os<<"Order id: "<<o.id<<"\nCustomer Details:\n"<<o.c<<"\nProduct List:";
    for(auto itr = o.prods.begin(); itr != o.prods.end(); itr++)
    {
        os<<"\n"<<*itr;
    }
    return os;
}

istream& operator >> (istream &is, Order & o)
{
    if(o.getflag()!=1)
    {
        cout<<"Enter Customer Details:"<<endl;
        is>>o.c;
        cout<<"Enter number of Products: ";
        int size;
        is>>size;
        for(int i=0;i<size;i++)
        {
            cout<<"Enter Product "<<i+1<<" details:\n";
            ProductItem temp;
            is>>temp;
            o.prods.push_back(temp);
        }
    }
    else
    {
        cout<<"Order is finalised and cannot be edited now!";
    }
    return is;
}

Order& Order::operator+ (ProductItem &p)
{
    int size = this->prods.size();
    int i = 0;
    for(;i<size;i++)
    {
        if((this->prods[i]).getid()==p.getid())
        {
            break;
        }
    }
    
    if(this->flag!=1)
    {
        if(i==size)
        {
            this->prods.push_back(p);
        }
        else
        {
            (this->prods[i]).incrementcopies(p);
        }
    }
    else
    {
        cout<<"Order is finalised and cannot be edited now!"<<endl;
    }
    return *this;
}

Order& Order::operator= (Order &o)
{
    if(this!=&o)
    {
        o.c = this->c;
        o.prods.clear();
        for(auto prod:this->prods)
        {
            o.prods.push_back(prod);
        }
    }
    return o;
}

int Order::getid()
{
    return this->id;
}

int Order::getflag()
{
    return this->flag;
}

void Order::setflag()
{
    this->flag=1;
}

ShoppingBasket::ShoppingBasket(Customer &in_c)
{
    this->id = ++NumBasket;
    this->c = in_c;
}

ostream& operator << (ostream &os, const ShoppingBasket & sb)
{
    os<<"Shopping Basket id: "<<sb.id<<"\nCustomer details:\n"<<sb.c<<"\nOrders List:";
    for(auto itr = sb.orders.begin(); itr != sb.orders.end(); itr++)
    {
        os<<"\n"<<*itr;
    }
    return os;
}

istream& operator >> (istream &is, ShoppingBasket & sb)
{
    cout<<"Enter Customer Details:"<<endl;
    is>>sb.c;
    cout<<"Enter number of Orders: ";
    int size;
    is>>size;
    for(int i=0;i<size;i++)
    {
        cout<<"Enter Object "<<i+1<<" details:\n";
        Order temp(sb.c);
        is>>temp;
        sb.orders.push_back(temp);
    }
    return is;
}

ShoppingBasket& ShoppingBasket::operator+ (Order &p)
{
    this->orders.push_back(p);
    return *this;
}

ShoppingBasket& ShoppingBasket::operator- (int orderid)
{
    for (auto itr = this->orders.begin(); itr != this->orders.end(); itr++)
    {
        if((*itr).getid() == orderid)
        {
            this->orders.erase(itr);
            break;
        }
    }
    return *this;
}

ShoppingBasket& ShoppingBasket::operator= (ShoppingBasket &sb)
{
    if(&sb!=this)
    {
        sb.NumBasket = this->NumBasket;
        sb.c = this->c;
        sb.orders.clear();
        for(auto order:this->orders)
        {
            sb.orders.push_back(order);
        }
    }
    return sb;
}

//initialising the static data members
int Customer::NumCustomer = 0 ;
int ProductItem::NumProductItem = 0;
int Order::NumOrder = 0;
int ShoppingBasket::NumBasket = 0;

int main() 
{
    //create a customer
    Customer *c = new Customer("Nikhil");

    // create a product
    ProductItem *p = new ProductItem("Something");

    // create am Order
    Order *o = new Order(*c);

    // add 10 copies of p to order o
    Order &oref = *o;
    oref = oref + *p * 10;

    // create a shopping basket
    ShoppingBasket *s = new ShoppingBasket(*c);
    ShoppingBasket &shop = *s;
    shop = shop + oref;
    shop = shop - oref.getid();
    
    return 0;
}
