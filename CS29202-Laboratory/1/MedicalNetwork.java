//Software Engineering Lab Spring 2022
//Assignment 1
//Rohit Ranjan, 20CS30066

//import statements 
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class MedicalNetwork {

    //Static lists created to keep track of all entities of a particular type. 
    static List<Manufacturer> manufacturers = new ArrayList<>();
    static List<Product> products = new ArrayList<>();
    static List<Customer> customers = new ArrayList<>();
    static List<Shop> shops = new ArrayList<>();
    static List<DeliveryAgent> deliveryagents = new ArrayList<>();

    public static void main(String []args) throws ParseException{

        System.out.println("\nWelcome to the Online Medicine Network!");

        //Scanner object created for facilitating inputs
        Scanner myobj = new Scanner(System.in);
        
        //the infinite loop repeats the menu unless exited by user
        while(true){
            System.out.println("\nHere is the Menu:");
            System.out.println("1. Create an entity.");
            System.out.println("2. Print entities of a type.");
            System.out.println("3. Delete an entity.");
            System.out.println("4. Add Product to Manufacturer.");
            System.out.println("5. Add copies of Product to Shop.");
            System.out.println("6. Add order of Product to Customer.");
            System.out.println("7. Process order from Customer.");
            System.out.println("8. List Purchases of Customer.");
            System.out.println("9. List Inventory of Shop.");
            System.out.println("10. List Products of Manufacturer.");
            System.out.println("11. Repeat Menu.");
            System.out.println("12. Exit.");
            System.out.println("\nPlease enter the number corresponding to your choice.");
            
            int input = myobj.nextInt();
            
            switch(input){
                case 1:
                    CreateEntity(myobj);
                    break;
                case 2:
                    PrintEntity(myobj);
                    break;
                case 3:
                    DeleteEntity(myobj);                    
                    break;
                case 4:
                    AddProducttoManf(myobj);
                    break;
                case 5:
                    AddProducttoShop(myobj);
                    break;
                case 6:
                    AddProducttoCust(myobj);
                    break;
                case 7:
                    ProcessOrder(myobj);
                    break;
                case 8:
                    ListPurchases(myobj);
                    break;
                case 9:
                    ListInventory(myobj);
                    break;
                case 10:
                    ListProductsofManf(myobj);
                    break;
                case 11: 
                    continue;
                case 12:
                    System.out.println("\nExiting!");
                    return ;
                default:
                    System.out.println("Wrong input. Repeating the menu for you.");
                    continue;
            }
        }
    }

    //function to create any new entity
    static void CreateEntity(Scanner myobj) throws ParseException{
        System.out.println("Enter the type :");
        String type = myobj.next();
        if(type.equals("Manufacturer")){
            manufacturers.add(new Manufacturer(myobj));
        } 
        else if(type.equals("Product")){
            products.add(new Product(myobj));
        }
        else if(type.equals("Customer")){
            customers.add(new Customer(myobj));
        }
        else if(type.equals("Shop")){
            shops.add(new Shop(myobj));
        }
        else if(type.equals("DeliveryAgent")){
            deliveryagents.add(new DeliveryAgent(myobj));
        }
        else{
            System.out.println("\nNo such type exists. Repeating the menu for you.");
            return;
        }
        System.out.println("\nCreated the requested entity. Repeating the menu for you.");
    }

    //function to print all data of any entity
    static void PrintEntity(Scanner myobj) throws ParseException{
        System.out.println("Enter the type :");
        String type = myobj.next();

        if(type.equals("Manufacturer")){
            System.out.println("\nHere are all the entities of type "+type+":\n");
            for(Manufacturer x:manufacturers){
                x.printobj();
                System.out.print("\n");
            }
        } 
        else if(type.equals("Product")){
            System.out.println("\nHere are all the entities of type "+type+":\n");
            for(Product x:products){
                x.printobj();
                System.out.print("\n");
            }
        }
        else if(type.equals("Customer")){
            System.out.println("\nHere are all the entities of type "+type+":\n");
            for(Customer x:customers){
                x.printobj();
                System.out.print("\n");
            }
        }
        else if(type.equals("Shop")){
            System.out.println("\nHere are all the entities of type "+type+":\n");
            for(Shop x:shops){
                x.printobj();
                System.out.print("\n");
            }
        }
        else if(type.equals("DeliveryAgent")){
            System.out.println("\nHere are all the entities of type "+type+":\n");
            for(DeliveryAgent x:deliveryagents){
                x.printobj();
                System.out.print("\n");
            }
        }
        else{
            System.out.println("\nNo such type exists. Repeating the menu for you.");
            return;
        }
        System.out.println("Printed all requested entities. Repeating the menu for you.");
    }

    //function to delete any entity
    static void DeleteEntity(Scanner myobj) throws ParseException{
        System.out.println("Enter the type :");
        String type = myobj.next();
        System.out.print("\n");

        //flag variable keeps track if entity is successfully deleted
        int flag=42;

        if(type.equals("Manufacturer")){
            int number = manufacturers.size();
            if(number==0){
                flag=0;
            }
            else{
                flag=1;
                for(int i=1;i<=number;i++){
                    if (manufacturers.get(i-1)==null){
                        continue;
                    }
                    System.out.println(""+i+". Delete Manufacturer with Unique ID :"+manufacturers.get(i-1).uid);
                }
                System.out.println("Enter your choice :");
                int choice=myobj.nextInt();
                manufacturers.remove(choice-1);
            }
        } 
        else if(type.equals("Product")){
            int number = products.size();
            if(number==0){
                flag=0;
            }
            else{
                flag=1;
                for(int i=1;i<=number;i++){
                    if (products.get(i-1)==null){
                        continue;
                    }
                    System.out.println(""+i+". Delete Product with Unique ID :"+products.get(i-1).uid);
                }
                System.out.println("Enter your choice :");
                int choice=myobj.nextInt();

                //Deletion of Product entity also removes the product from its manufacturer's set of products produced
                for(Manufacturer x:manufacturers){
                    if((x.name).equals(products.get(choice-1).manf)){
                        x.products.remove(products.get(choice-1));
                        break;
                    }
                }

                products.remove(choice-1);
            }
        }
        else if(type.equals("Customer")){
            int number = customers.size();
            if(number==0){
                flag=0;
            }
            else{
                flag=1;
                for(int i=1;i<=number;i++){
                    if (customers.get(i-1)==null){
                        continue;
                    }
                    System.out.println(""+i+". Delete Customer with Unique ID :"+customers.get(i-1).uid);
                }
                System.out.println("Enter your choice :");
                int choice=myobj.nextInt();
                customers.remove(choice-1);
            }
        }
        else if(type.equals("Shop")){
            int number = shops.size();
            if(number==0){
                flag=0;
            }
            else{
                flag=1;
                for(int i=1;i<=number;i++){
                    if (shops.get(i-1)==null){
                        continue;
                    }
                    System.out.println(""+i+". Delete Shop with Unique ID :"+shops.get(i-1).uid);
                }
                System.out.println("Enter your choice :");
                int choice=myobj.nextInt();
                shops.remove(choice-1);
            }
        }
        else if(type.equals("DeliveryAgent")){
            int number = deliveryagents.size();
            if(number==0){
                flag=0;
            }
            else{
                flag=1;
                for(int i=1;i<=number;i++){
                    if (deliveryagents.get(i-1)==null){
                        continue;
                    }
                    System.out.println(""+i+". Delete Delivery Agent with Unique ID :"+deliveryagents.get(i-1).uid);
                }
                System.out.println("Enter your choice :");
                int choice=myobj.nextInt();
                deliveryagents.remove(choice-1);
            }
        }
        else{
            System.out.println("\nNo such type exists. Repeating the menu for you.");
        }

        if(flag==0){
            System.out.println("No entities of this type available to delete. Repeating the menu for you.");
        }
        else{
            System.out.println("\nDeleted the selected entity. Repeating the menu for you.");
        }
    }

    //function to add products to Manufacturer
    static void AddProducttoManf(Scanner myobj) throws ParseException{
        System.out.println("\nHere is the list of products :");
        int counter=1;
        for(Product x:products){
            System.out.println(""+counter+". Product "+x.name+" from Manufacturer "+x.manf);
            counter++;
        }
        if (counter==1){
            System.out.println("No products have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of product to be added to manufacturer.");
        int choice = myobj.nextInt();
        String manf = products.get(choice-1).manf;
        int flag=0;
        for(Manufacturer y:manufacturers){
            if(manf.equals(y.name)){
                y.products.add(products.get(choice-1));
                flag=1;
                break;
            }
        }
        if(flag==0){
            System.out.println("Manufacturer named "+manf+" not found. Product not added.");
        }
        else{
            System.out.println("Product added. Repeating the menu for you.");
        }
    }

    //function to add product and its quantity to a Shop
    static void AddProducttoShop(Scanner myobj) throws ParseException{
        System.out.println("\nHere is the list of shops :");
        int counter1=1;
        for(Shop x:shops){
            System.out.println(""+counter1+". Shop "+x.name);
            counter1++;
        }
        if (counter1==1){
            System.out.println("No shops have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of shop to add product.");
        int choice1 = myobj.nextInt();

        System.out.println("\nHere is the list of products :");
        int counter2=1;
        for(Product x:products){
            System.out.println(""+counter2+". Product "+x.name);
            counter2++;
        }
        if (counter2==1){
            System.out.println("No products have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of product to be added to shop.");
        int choice2 = myobj.nextInt();
        System.out.println("Enter copies of product to be added to shop.");
        int copies = myobj.nextInt();

        Pair<Product,Integer> entry = new Pair(products.get(choice2-1),copies);
        shops.get(choice1-1).inventory.add(entry);

        System.out.println("Product added. Repeating the menu for you.");
    }

    //function to add product order from Customer
    static void AddProducttoCust(Scanner myobj) throws ParseException{
        System.out.println("\nHere is the list of Customers :");
        int counter1=1;
        for(Customer x:customers){
            System.out.println(""+counter1+". Customer "+x.name);
            counter1++;
        }
        if (counter1==1){
            System.out.println("No customers have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of customer to add product.");
        int choice1 = myobj.nextInt();

        System.out.println("\nHere is the list of products:");
        int counter2=1;
        for(Product x:products){
            System.out.println(""+counter2+". Product "+x.name);
            counter2++;
        }
        if (counter2==1){
            System.out.println("No products have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of product to be added to Customer.");
        int choice2 = myobj.nextInt();

        customers.get(choice1-1).products.add(products.get(choice2-1));

        System.out.println("Product added. Repeating the menu for you.");
    }

    //function to process a product in the product list of Customer
    static void ProcessOrder(Scanner myobj) throws ParseException{
        System.out.println("\nHere is the list of Customers :");
        int counter1=1;
        for(Customer x:customers){
            System.out.println(""+counter1+". Customer "+x.name);
            counter1++;
        }
        if (counter1==1){
            System.out.println("No customers have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of customer to preocess order from.");
        int choice1 = myobj.nextInt();

        System.out.println("\nHere is the list of Customer "+customers.get(choice1-1).name+"'s orders");
        int counter2=1;
        for(Product x:customers.get(choice1-1).products){
            System.out.println(""+counter2+". Order of Product "+x.name);
            counter2++;
        }
        if (counter2==1){
            System.out.println("No orders have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of order to process.");
        int choice2 = myobj.nextInt();

        int flag=0;

        //Checking if a valid shop is present for selected product in customer's zipcode
        for(Shop x:shops){
            if(x.zipcode == customers.get(choice1-1).zipcode){
                for(Pair<Product,Integer> p:x.inventory){
                    if(p.getLeft().name.equals(customers.get(choice1-1).products.get(choice2-1).name)){
                        if(p.getRight()>0){
                            flag=1;
                            int min=1000000000;
                            if(deliveryagents.size()==0){
                                System.out.println("No Delivery Agent has been added. Repeating the menu for you.");
                                return;
                            }
                            DeliveryAgent min_d = null;

                            //Delivery is allotted to Agent with minimum number of deliveries yet
                            for(DeliveryAgent xx:deliveryagents){
                                if(xx.zipcode == customers.get(choice1-1).zipcode){
                                    if(min>xx.num_delivered){
                                        min = xx.num_delivered;
                                        min_d = xx;
                                    }
                                }
                            }
                            if(min_d == null){
                                System.out.println("No Delivery Agent found at Customer's zipcode. Repeating the menu for you.");
                                return;
                            }
                            min_d.num_delivered++;
                            customers.get(choice1-1).purchases.add(customers.get(choice1-1).products.get(choice2-1));
                            customers.get(choice1-1).products.remove(choice2-1);
                            System.out.println("Order processed and allotted to Delivery Agent "+min_d.name+". Repeating the menu for you.");
                            p.setRight(p.getRight()-1);
                            break;
                        }
                    }
                }
                if(flag==1){
                    break;
                }
            }
        }
        if(flag==0){
            System.out.println("Order not processed. Valid shop at the zipcode not found.");
        }
    }

    //function to list all purchases made by Customer
    static void ListPurchases(Scanner myobj) throws ParseException{
        System.out.println("\nHere is the list of Customers :");
        int counter1=1;
        for(Customer x:customers){
            System.out.println(""+counter1+". Customer "+x.name);
            counter1++;
        }
        if (counter1==1){
            System.out.println("No customers have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of customer to list purchases.");
        int choice1 = myobj.nextInt();
        int counter2=1;
        for(Product x:customers.get(choice1-1).purchases){
            System.out.println(""+counter2+". Purchased product "+ x.name);
            counter2++;
        }
        if(counter2==1){
            System.out.println("No products have been purchased yet. Repeating the menu for you.");
        }
    }

    //function to list inventory of the Shop
    static void ListInventory(Scanner myobj) throws ParseException{
        System.out.println("\nHere is the list of Shops :");
        int counter1=1;
        for(Shop x:shops){
            System.out.println(""+counter1+". Shop "+x.name);
            counter1++;
        }
        if (counter1==1){
            System.out.println("No shops have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of shop to list inventory.");
        int choice1 = myobj.nextInt();
        int counter2=1;  
        for(Pair<Product,Integer> prod:shops.get(choice1-1).inventory){
            System.out.println("Product "+counter2+" :"+prod.getLeft().name+" , Number of Copies :"+prod.getRight());
            counter2++;
        }
        if(counter2==1){
            System.out.println("No inventory for selected shop. Repeating the menu for you.");
        }
    }

    //function to list all products of the Manufacturer
    static void ListProductsofManf(Scanner myobj) throws ParseException{
        System.out.println("\nHere is the list of Manufacturers :");
        int counter1=1;
        for(Manufacturer x:manufacturers){
            System.out.println(""+counter1+". Manufacturer "+x.name);
            counter1++;
        }
        if (counter1==1){
            System.out.println("No manufacturers have been added yet. Repeating the menu for you.");
            return;
        }
        System.out.print("\n");
        System.out.println("Enter choice of manufacturer to list products.");
        int choice1 = myobj.nextInt();
        int counter2=1;  
        for(Product prod:manufacturers.get(choice1-1).products){
            System.out.println("Product "+counter2+" :"+prod.name);
            counter2++;
        }
        if(counter2==1){
            System.out.println("No products for selected Manufacturer. Repeating the menu for you.");
        }
    }
}

//class defining basic propertities of any entity
class Entity{

    //static variable NEXT_ID helps in allotting unique ids to all created entities
    static int NEXT_ID=1;
    
    int uid;
    String name;
    Date join_date;

    public Entity(Scanner myobj) throws ParseException{
        this.uid = NEXT_ID;
        NEXT_ID+=1;
        System.out.println("Enter the Name :");
        this.name = myobj.next();
        System.out.println("Enter the Joining Date in DD/MM/YYYY format :");
        SimpleDateFormat format = new SimpleDateFormat("dd/MM/yyyy");
        String input_date = myobj.next();
        if(null != input_date && input_date.trim().length() > 0){
            this.join_date = format.parse(input_date);
        }
    }
    void printobj(){
        System.out.println("Unique ID :"+this.uid);
        System.out.println("Name :"+this.name);
        System.out.println("Joining Date :"+this.join_date);
    }
}

//entity Manufacturer inherits from Entity
class Manufacturer extends Entity{
    Set<Product> products = new HashSet<Product>();

    public Manufacturer(Scanner myobj) throws ParseException{
        super(myobj);
    }
    void printobj(){
        System.out.println("Entity Type :Manufacturer");
        super.printobj();
        int counter =1;
        for(Product prod:products){
            System.out.println("Product "+counter+" :"+prod.name);
            counter++;
        }

    }

}

//entity Product inherits from Entity
class Product extends Entity{
    String manf;

    public Product(Scanner myobj) throws ParseException{
        super(myobj);
        System.out.println("Enter name of Manufacturer :");
        this.manf = myobj.next();
    }

    void printobj(){
        System.out.println("Entity Type :Product");
        super.printobj();
        System.out.println("Manufacturer :"+this.manf);
    }
}

//entity PositionalEntity inherits from Entity and all entities having a zipcode inherit from it
class PositionalEntity extends Entity{
    int zipcode;

    public PositionalEntity(Scanner myobj) throws ParseException{
        super(myobj);
        System.out.println("Enter Zip-Code :");
        this.zipcode = myobj.nextInt();
    }

    void printobj(){
        super.printobj();
        System.out.println("Zip-Code :"+this.zipcode);
    }
}

//entity Customer inherits from PositionalEntity
class Customer extends PositionalEntity{
    List<Product> products = new ArrayList<Product>();
    List<Product> purchases = new ArrayList<Product>();

    public Customer(Scanner myobj) throws ParseException{
        super(myobj);
    }

    void printobj(){
        System.out.println("Entity Type :Customer");
        super.printobj(); 
        int counter=1;  
        for(Product prod:products){
            System.out.println("Product "+counter+" :"+prod.name);
            counter++;
        }
        counter=1;  
        for(Product prod:purchases){
            System.out.println("Purchased Product "+counter+" :"+prod.name);
            counter++;
        }
    }
}

//entity Shop inherits from PositionalEntity
class Shop extends PositionalEntity{
    List<Pair<Product,Integer>> inventory= new java.util.ArrayList<>();

    public Shop(Scanner myobj) throws ParseException{
        super(myobj);
    }

    void printobj(){
        System.out.println("Entity Type :Shop");
        super.printobj(); 
        int counter=1;  
        for(Pair<Product,Integer> prod:inventory){
            System.out.println("Product "+counter+" :"+prod.getLeft().name+" , Number of Copies :"+prod.getRight());
            counter++;
        }
    }
}

//entity DeliveryAgent inherits from PositionalEntity
class DeliveryAgent extends PositionalEntity{
    int num_delivered;

    public DeliveryAgent(Scanner myobj) throws ParseException{
        super(myobj);
    }
    void printobj(){
        System.out.println("Entity Type :Delivery Agent");
        super.printobj();
        System.out.println("Number of Deliveries :"+num_delivered);
    }
}

//class defining a simple java tuple with get and set functions
class Pair<L,R> {

    private L left;
    private R right;
  
    public Pair(L left, R right){
      assert left != null;
      assert right != null;
  
      this.left = left;
      this.right = right;
    }
  
    public L getLeft(){
         return left; 
    }
    public R getRight(){ 
        return right; 
    }
    public void setLeft(L left){ 
        this.left = left; 
    }
    public void setRight(R right){ 
        this.right = right; 
    }
 
}