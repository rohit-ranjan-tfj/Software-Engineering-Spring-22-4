// Software Engineering Assignment 2
// Rohit Ranjan
// 20CS30066

#include "assgn2.hpp"

xml_document<> doc;
xml_node<> * root_node = NULL;

//utility function to calculate crow fly dist using Haversine Formula
double distance(double lat1,double lon1,double lat2,double lon2) 
{
  double dLat = degtoradians(lat2-lat1);  
  double dLon = degtoradians(lon2-lon1); 
  double a = sin(dLat/2) * sin(dLat/2) + cos(degtoradians(lat1)) * cos(degtoradians(lat2)) * sin(dLon/2) * sin(dLon/2); 
  double c = 2 * atan2(sqrt(a), sqrt(1-a)); 
  double RADIUS = 6378.1;
  return c*RADIUS;
}

//utility function to convert degrees to radians
double degtoradians(double degree) 
{
  return degree * (PI/180);
}

//utility function that parses the osm and populates the hashtable
void parseOSM(unordered_map<long long, node*> &nodes, unordered_map<long long, way*> &ways)
{
    cout << "\nParsing map data (map.osm)..." << endl;
   
    // Read the map.osm file
    ifstream theFile ("map.osm");
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
   
    // Parse the buffer
    doc.parse<0>(&buffer[0]);
   
    // Find out the root node
    root_node = doc.first_node("osm");

    // Iterate over the nodes
    for (xml_node<> * curr_node = root_node->first_node("node"); curr_node; curr_node = curr_node->next_sibling())
    {
        if(curr_node->name() == string("node"))
        {
            node *temp = new node;
            temp->id = (atol) (curr_node->first_attribute("id")->value());
            temp->visible = (curr_node->first_attribute("visible")->value()=="true"? 1:0);
            temp->version = (atoi) (curr_node->first_attribute("version")->value());
            temp->changeset = (atoi)  (curr_node->first_attribute("changeset")->value());
            temp->timestamp = curr_node->first_attribute("timestamp")->value();
            temp->user = curr_node->first_attribute("user")->value();
            temp->uid = (atoi) (curr_node->first_attribute("uid")->value());
            temp->lat = (atof) (curr_node->first_attribute("lat")->value());
            temp->lon = (atof) (curr_node->first_attribute("lon")->value());
            ll_node* temp_ll = new ll_node;
            temp_ll->id = temp->id;
            temp->edges = temp_ll;
            for(xml_node<> * internal_node = curr_node->first_node("tag"); internal_node; internal_node = internal_node->next_sibling())
            {
                if(internal_node->name() == string("tag"))
                {
                    string k,v;
                    k = internal_node->first_attribute("k")->value();
                    v = internal_node->first_attribute("v")->value();
                    temp->tag.push_back(make_pair(k,v));
                }
            }
            nodes.insert(make_pair(temp->id,temp));
        }    
        
    }
    
    // Iterate over the ways
    for (xml_node<> * curr_node = root_node->first_node("way"); curr_node; curr_node = curr_node->next_sibling())
    {
        if(curr_node->name() == string("way"))
        {
            way *temp = new way;
            temp->id = (atol) (curr_node->first_attribute("id")->value());
            temp->visible = (curr_node->first_attribute("visible")->value()=="true"? 1:0);
            temp->version = (atoi) (curr_node->first_attribute("version")->value());
            temp->changeset = (atoi)  (curr_node->first_attribute("changeset")->value());
            temp->timestamp = curr_node->first_attribute("timestamp")->value();
            temp->user = curr_node->first_attribute("user")->value();
            temp->uid = (atoi) (curr_node->first_attribute("uid")->value());
 
            for(xml_node<> * internal_node = curr_node->first_node("tag"); internal_node; internal_node = internal_node->next_sibling())
            {
                if(internal_node->name() == string("tag"))
                {
                    string k,v;
                    k = internal_node->first_attribute("k")->value();
                    v = internal_node->first_attribute("v")->value();
                    temp->tag.push_back(make_pair(k,v));
                }
            }
            for(xml_node<> * internal_node = curr_node->first_node("nd"); internal_node; internal_node = internal_node->next_sibling())
            {
                if(internal_node->name() == string("nd"))
                {
                    long long ref = (atol) (internal_node->first_attribute("ref")->value());
                    temp->nd.push_back(ref);
                }
            }
            ways.insert(make_pair(temp->id,temp));
        }    
        
    }

    cout<<"Parsing map successful.\n"<<endl;
}

//utility function that implements search feature
void search(unordered_map<long long, node*> &nodes, unordered_map<long long, way*> &ways)
{
    cout<<"\nPlease enter the search string:"<<endl;
    string s;
    int flag=0;
    cin>>s;
    cout<<"\nHere are the search results:\n"<<endl;
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        for(int j=0;j<(itr->second->tag).size();j++)
        {
            if(itr->second->tag[j].first == "name")
            {
                if(boost::algorithm::contains(itr->second->tag[j].second,s))
                {
                    flag=1;
                    cout<<"Node ID = "<<itr->second->id<<" and Name is "<<itr->second->tag[j].second<<endl;
                }
            }
        }
    }
    for (auto itr = ways.begin(); itr != ways.end(); itr++)
    {
        for(int j=0;j<(itr->second->tag).size();j++)
        {
            if(itr->second->tag[j].first == "name")
            {
                if(boost::algorithm::contains(itr->second->tag[j].second,s))
                {
                    flag=1;
                    cout<<"Way ID = "<<itr->second->id<<" and Name is "<<itr->second->tag[j].second<<endl;
                }
            }
        }
    }
    if(flag==0)
    {
        cout<<"No matching node or way found."<<endl;
    }
}

//utility function that searches and prints k-closest nodes
void firstknodes(unordered_map<long long, node*> &nodes)
{
    priority_queue<pair<double, long long>,vector<pair<double,long long>>,ComparisonClass> distances;
    cout<<"\nEnter ID of the node:"<<endl;
    long long id;
    cin>>id;

    double lat,lon;

    if (nodes.find(id) == nodes.end())
    {
        cout<<"No node with ID = "<<id<<" found."<<endl;
    }
    else
    {
        lat = nodes.find(id)->second->lat;
        lon = nodes.find(id)->second->lon;

        for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
        {
            distances.emplace(distance(itr->second->lat,itr->second->lon,lat,lon), itr->second->id);
        }
        cout<<"Enter the value of k:"<<endl;
        int k;
        cin>>k;
        distances.pop();
        cout<<"\nHere are the "<<k<<"-closest nodes:\n"<<endl;
        while(k--)
        {
            cout<<"Node ID "<<distances.top().second<<" at a distance of "<<distances.top().first<<" km."<<endl;
            distances.pop();
        }
    }
        
}

//utility function that converts parsed data into graph using adjacency list representation
void adjacency_list(unordered_map<long long, node*> &nodes, unordered_map<long long, way*> &ways)
{
    cout<<"Generating graph for OSM..."<<endl;
    for (auto itr = ways.begin(); itr != ways.end(); itr++)
    {
        way* curr = itr->second;
        ll_node* temp;
        if(curr->nd.size()>=2)
        {
            ll_node* temp1 = new ll_node;
            temp1->id  = curr->nd[1];
            temp = nodes.find(curr->nd[0])->second->edges;
            temp1->next = temp->next;
            temp->next=temp1;

            ll_node* centre1 = new ll_node;
            centre1->id = curr->nd[0];
            temp = nodes.find(temp1->id)->second->edges;
            centre1->next = temp->next;
            temp->next=centre1;

            ll_node* temp2 = new ll_node;
            temp2->id  = curr->nd[curr->nd.size()-2];
            temp = nodes.find(curr->nd[curr->nd.size()-1])->second->edges;
            temp2->next = temp->next;
            temp->next=temp2;

            ll_node* centre2 = new ll_node;
            centre2->id = curr->nd[curr->nd.size()-1];
            temp = nodes.find(temp2->id)->second->edges;
            centre2->next = temp->next;
            temp->next=centre2;

            for(int i =1;i<curr->nd.size()-1;i++)
            {
                ll_node* temp1 = new ll_node;
                temp1->id  = curr->nd[i-1];
                ll_node* temp2 = new ll_node;
                temp2->id  = curr->nd[i+1];
                temp = nodes.find(curr->nd[i])->second->edges;
                temp2->next = temp->next;
                temp1->next = temp2;
                temp->next = temp1;
            }
        }
    }
    cout<<"Graph generation successful.\n"<<endl;
}

//utility function to print shortest path calculated via Djikstra's Algorithm
void printPath(long long dest_id,unordered_map<long long, long long> parent)
{
    if(parent.find(dest_id)->second ==-1)
    {
        cout<<dest_id<<endl;
        return;
    }
    printPath(parent.find(dest_id)->second,parent);
    cout<<dest_id<<endl;
}

//utility function that uses Dijkstra's Algorithm for finding shortest path
void dijkstra(unordered_map<long long, node*> nodes)
{
    long long src,dest;
    cout<<"\nEnter source node ID:"<<endl;
    cin>>src;
    if(nodes.find(src)==nodes.end())
    {
        cout<<"Given source node was not found!"<<endl;
        return;
    }
    cout<<"Enter destination node ID:"<<endl;
    cin>>dest;
    if(nodes.find(dest)==nodes.end())
    {
        cout<<"Given destination node was not found!"<<endl;
        return;
    }

    unordered_map<long long, bool> isinheap;
    unordered_map<long long, double> dist;
    unordered_map<long long, long long> parent;

    priority_queue<pair<double, long long>,vector<pair<double,long long>>,ComparisonClass> heap;

    for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        if(itr->second->id != src)
        {
            heap.emplace(DBL_MAX, itr->second->id);
            dist.insert(make_pair(itr->second->id,DBL_MAX));
        }
        else
        {
            heap.emplace(0.0, itr->second->id);
            dist.insert(make_pair(itr->second->id,0.0));
        }
        isinheap.insert(make_pair(itr->second->id,1));
        parent.insert(make_pair(itr->second->id,-1));
    }
    
    while (!heap.empty())
    {
        pair<double, long long> min_node = heap.top();

        if(isinheap.find(dest)->second == 0)
        {
            break;
        }

        if(isinheap.find(min_node.second)->second == 0)
        {
            heap.pop();
            continue;
        }

        ll_node* curr = nodes.find(min_node.second)->second->edges->next;

        while (curr != nullptr)
        {
            long long curr_id = curr->id;

            if(nodes.find(min_node.second)==nodes.end() || nodes.find(curr_id)==nodes.end() || dist.find(min_node.second)==dist.end() || dist.find(curr_id)==dist.end() || isinheap.find(min_node.second)==isinheap.end() || isinheap.find(curr_id)==isinheap.end())
            {
                curr = nullptr;
                continue;
            }
            else if (isinheap.find(curr_id)->second==1 && min_node.first != DBL_MAX && 
              distance(nodes.find(min_node.second)->second->lat,nodes.find(min_node.second)->second->lon,nodes.find(curr_id)->second->lat,nodes.find(curr_id)->second->lon) + dist.find(min_node.second)->second < dist.find(curr_id)->second)
            {
                dist.find(curr_id)->second = dist.find(min_node.second)->second + distance(nodes.find(min_node.second)->second->lat,nodes.find(min_node.second)->second->lon,nodes.find(curr_id)->second->lat,nodes.find(curr_id)->second->lon);
                parent.find(curr_id)->second = min_node.second;
                heap.emplace(dist.find(curr_id)->second, curr_id);


            }

            curr = curr->next;
        }

        heap.pop();
        isinheap.find(min_node.second)->second = 0;
    }  
    if(dist.find(dest)->second == DBL_MAX)
    {
        cout<<"\nNo path between these two nodes."<<endl;
        return;
    }
    cout<<"\nThe shortest path distance is "<<dist.find(dest)->second<<" km."<<endl;  
    cout<<"\nHere is the path along the nodes.\n"<<endl;
    printPath(dest,parent);         
}