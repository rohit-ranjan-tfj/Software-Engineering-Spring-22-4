// Software Engineering Assignment 2
// Rohit Ranjan
// 20CS30066

#include "assgn2.hpp"

int main(void)
{
    //unordered_map used from stl because it stores nodes and ways in hahtable
    //this allows nodes and ways to be retrieved in constant time using their id as key
    unordered_map<long long, node*> nodes;
    unordered_map<long long, way*> ways;
    int choice;

    //utility function that parses the osm and populates the hashtable
    parseOSM(nodes,ways);

    //utility function that converts parsed data into graph using adjacency list representation
    adjacency_list(nodes,ways);

    cout<<"Welcome to the OSM Map of Kharagpur!"<<endl;
    cout<<"Software Engineering Assignment 2"<<endl;
    cout<<"Rohit Ranjan __ 20CS30066"<<endl;

    while(true)
    {
        cout<<"\nHere is the menu:\n"<<endl;
        cout<<"1. Print the number of nodes in Kharagpur area."<<endl;
        cout<<"2. Print the number of ways in Kharagpur area."<<endl;
        cout<<"3. Search all nodes and ways using substring of name attribute."<<endl;
        cout<<"4. Print the first k-closest nodes to a node in Kharagpur area."<<endl;
        cout<<"5. Find the shortest path between two nodes using ways in Kharagpur area."<<endl;
        cout<<"6. Repeat the menu."<<endl;
        cout<<"7. Exit."<<endl;

        cout<<"\nEnter the number corresponding to your choice."<<endl;

        cin>>choice;

        switch(choice)
        {
            case 1:
                cout<<"\nThe number of nodes is "<<nodes.size()<<"."<<endl;
                break;
            case 2:
                cout<<"\nThe number of ways is "<<ways.size()<<"."<<endl;
                break;
            case 3:
                //utility function that implements search feature
                search(nodes,ways);
                break;
            case 4:
                //utility function that searches and prints k-closest nodes
                firstknodes(nodes);
                break;
            case 5:
                //utility function that uses Dijkstra's Algorithm for finding shortest path
                dijkstra(nodes);
                break;
            case 6:
                break;
            case 7:
                cout<<"Exiting!"<<endl;
                return 0;
            default:
                cout<<"Invalid Input!!"<<endl;
        }
        cout<<"Repeating the menu for you."<<endl;
    }

    return 0;
}