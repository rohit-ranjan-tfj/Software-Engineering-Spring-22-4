// Software Engineering Assignment 2
// Rohit Ranjan
// 20CS30066

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include "rapidxml.hpp"
#include <limits>
#include <cfloat>

using namespace std;
using namespace rapidxml;

const double PI = 3.14159265359;

//data structure for nodes of linked list
typedef struct _ll_node
{
    long long id;
    _ll_node* next;
} ll_node;

//data structure for nodes
typedef struct _node
{
    long long id;
    bool visible;
    int version;
    int changeset;
    string timestamp;
    string user;
    int uid;
    double lat;
    double lon;
    vector<pair<string,string>> tag;

    //edges stores the head pointer for adjacency list of particular node
    ll_node* edges;
} node;

//data structure for ways
typedef struct _way
{
    long long id;
    bool visible;
    int version;
    int changeset;
    string timestamp;
    string user;
    int uid;
    vector<long long> nd;
    vector<pair<string,string>> tag;
} way;

//comparator function for min heap
class ComparisonClass {
public:
    bool operator() (pair<double, long long> &a, pair<double, long long> &b) 
    {
        return a.first>b.first;
    }
};

double distance(double lat1,double lon1,double lat2,double lon2);
double degtoradians(double degree);
void parseOSM(unordered_map<long long, node*> &nodes, unordered_map<long long, way*> &ways);
void search(unordered_map<long long, node*> &nodes, unordered_map<long long, way*> &ways);
void firstknodes(unordered_map<long long, node*> &nodes);
void adjacency_list(unordered_map<long long, node*> &nodes, unordered_map<long long, way*> &ways);
void printPath(long long dest_id,unordered_map<long long, long long> parent);
void dijkstra(unordered_map<long long, node*> nodes);

