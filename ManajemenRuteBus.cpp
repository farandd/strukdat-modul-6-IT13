#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class BusNode
{
public:
    BusNode(const string &cityName) : name(cityName) {}
    virtual ~BusNode() {}

    string getName() const
    {
        return name;
    }

protected:
    string name;
};

// Abstract Class Graph
class BusGraph
{
public:
    virtual ~BusGraph() {}

    virtual void addNode(BusNode *node) = 0;
    virtual void addEdge(int node1Index, int node2Index) = 0;
    virtual void display() const = 0;
};

class BusGraphAdjacencyMatrix : public BusGraph
{
public:
    BusGraphAdjacencyMatrix(int size) : nodeCount(0), adjacencyMatrix(size, vector<int>(size, 0)) {}

    ~BusGraphAdjacencyMatrix() override
    {
        for (int i = 0; i < nodeCount; i++)
        {
            delete nodes[i];
        }
    }

    void addNode(BusNode *node) override
    {
        nodes.push_back(node);
        nodeCount++;
    }

    void addEdge(int node1Index, int node2Index) override
    {
        adjacencyMatrix[node1Index][node2Index] = 1;
        adjacencyMatrix[node2Index][node1Index] = 1;
    }

    void display() const override
    {
        cout << "-------------------------------------------------------" << endl;
        cout << "Bus Route Graph (Adjacency Matrix):" << endl;

        for (int i = 0; i < nodeCount; i++)
        {
            cout << nodes[i]->getName() << " connected to: ";

            for (int j = 0; j < nodeCount; j++)
            {
                if (adjacencyMatrix[i][j] == 1)
                {
                    cout << nodes[j]->getName() << " - ";
                }
            }
            cout << endl;
        }
        cout << "-------------------------------------------------------" << endl;
    }

protected:
    int nodeCount;
    vector<BusNode *> nodes;
    vector<vector<int>> adjacencyMatrix;
};

class BusTransRoute
{
public:
    BusTransRoute(const string &start, const string &end) : startLocation(start), endLocation(end) {}

private:
    string startLocation;
    string endLocation;
};

class BusRoute : public BusGraphAdjacencyMatrix
{
public:
    BusRoute(int size) : BusGraphAdjacencyMatrix(size) {}

    int findNodeIndex(const string &nodeName);
    void displayShortestRoute(const string &startLocation, const string &endLocation);
    void displayAllRoutes(const string &startLocation, const string &endLocation);
    void deleteRoute(int node1Index, int node2Index);
    void addRoute(int node1Index, int node2Index);
    void displayAdjacencyMatrix() const;

private:
    void dfs(int currentNode, int targetNode, vector<int> &visited, vector<int> &path, bool &found);
    int minDistance(const vector<int> &distance, const vector<bool> &visited);
    void printShortestRoute(int start, int end, const vector<int> &parent);
    void dfsAllRoutes(int currentNode, int targetNode, vector<int> &visited, vector<int> &path);
    void printRouteHeader() const;
    void printDeletedRoute(int node1Index, int node2Index);
    void printAddedRoute(int node1Index, int node2Index);
};

void BusRoute::displayAdjacencyMatrix() const
{
    cout << "-------------------------------------------------------" << endl;
    cout << "Bus Route Graph (Adjacency Matrix):" << endl;

    for (int i = 0; i < nodeCount; i++)
    {
        cout << nodes[i]->getName() << " connected to: ";

        for (int j = 0; j < nodeCount; j++)
        {
            if (adjacencyMatrix[i][j] == 1)
            {
                cout << nodes[j]->getName() << " - ";
            }
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------" << endl;
}

void BusRoute::addRoute(int node1Index, int node2Index)
{
    if (node1Index >= 0 && node1Index < nodeCount && node2Index >= 0 && node2Index < nodeCount &&
        adjacencyMatrix[node1Index][node2Index] == 0 && adjacencyMatrix[node2Index][node1Index] == 0)
    {
        adjacencyMatrix[node1Index][node2Index] = 1;
        adjacencyMatrix[node2Index][node1Index] = 1;
        printAddedRoute(node1Index, node2Index);
    }
    else
    {
        cout << "Invalid route. Route already exists.\n";
    }
}

void BusRoute::printAddedRoute(int node1Index, int node2Index)
{
    printRouteHeader();
    cout << "Route added: " << nodes[node1Index]->getName() << " - " << nodes[node2Index]->getName() << endl;
    printRouteHeader();
}

void BusRoute::deleteRoute(int node1Index, int node2Index)
{
    if (node1Index >= 0 && node1Index < nodeCount && node2Index >= 0 && node2Index < nodeCount &&
        adjacencyMatrix[node1Index][node2Index] == 1 && adjacencyMatrix[node2Index][node1Index] == 1)
    {
        adjacencyMatrix[node1Index][node2Index] = 0;
        adjacencyMatrix[node2Index][node1Index] = 0;
        printDeletedRoute(node1Index, node2Index);
    }
    else
    {
        cout << "Invalid route. Route does not exist.\n";
    }
}

void BusRoute::printDeletedRoute(int node1Index, int node2Index)
{
    printRouteHeader();
    cout << "Route deleted: " << nodes[node1Index]->getName() << " - " << nodes[node2Index]->getName() << endl;
    printRouteHeader();
}

int BusRoute::findNodeIndex(const string &nodeName)
{
    string lowerNodeName = nodeName;
    transform(lowerNodeName.begin(), lowerNodeName.end(), lowerNodeName.begin(), ::tolower);

    for (int i = 0; i < nodeCount; ++i)
    {
        string currentNodeName = nodes[i]->getName();
        transform(currentNodeName.begin(), currentNodeName.end(), currentNodeName.begin(), ::tolower);

        if (currentNodeName == lowerNodeName)
        {
            return i;
        }
    }
    return -1;
}

void BusRoute::printRouteHeader() const
{
    cout << "-------------------------------------------------------" << endl;
}

void BusRoute::displayShortestRoute(const string &startLocation, const string &endLocation)
{
    int startIndex = findNodeIndex(startLocation);
    int endIndex = findNodeIndex(endLocation);

    if (startIndex != -1 && endIndex != -1)
    {
        vector<int> distance(nodeCount, INT_MAX);
        vector<int> parent(nodeCount, -1);
        vector<bool> visited(nodeCount, false);

        distance[startIndex] = 0;

        for (int count = 0; count < nodeCount - 1; ++count)
        {
            int u = minDistance(distance, visited);
            visited[u] = true;

            for (int v = 0; v < nodeCount; ++v)
            {
                if (!visited[v] && adjacencyMatrix[u][v] && distance[u] != INT_MAX &&
                    distance[u] + adjacencyMatrix[u][v] < distance[v])
                {
                    distance[v] = distance[u] + adjacencyMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        printShortestRoute(startIndex, endIndex, parent);

        BusTransRoute route(startLocation, endLocation);
    }
    else
    {
        cout << "Invalid start or end location." << endl;
    }
}

int BusRoute::minDistance(const vector<int> &distance, const vector<bool> &visited)
{
    int minDist = INT_MAX, minIndex = -1;

    for (int v = 0; v < nodeCount; ++v)
    {
        if (!visited[v] && distance[v] <= minDist)
        {
            minDist = distance[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void BusRoute::printShortestRoute(int start, int end, const vector<int> &parent)
{
    printRouteHeader();
    if (parent[end] == -1)
    {
        cout << "No route from " << nodes[start]->getName() << " to " << nodes[end]->getName() << endl;
        return;
    }

    vector<int> path;
    for (int at = end; at != -1; at = parent[at])
    {
        path.push_back(at);
    }

    cout << "Shortest Route from " << nodes[start]->getName() << " to " << nodes[end]->getName() << ": ";
    for (int i = path.size() - 1; i >= 0; --i)
    {
        cout << nodes[path[i]]->getName();
        if (i > 0)
        {
            cout << " - ";
        }
    }
    cout << endl;
    printRouteHeader();
}

void BusRoute::displayAllRoutes(const string &startLocation, const string &endLocation)
{
    printRouteHeader();
    int startIndex = findNodeIndex(startLocation);
    int endIndex = findNodeIndex(endLocation);

    if (startIndex != -1 && endIndex != -1)
    {
        vector<int> visited(nodeCount, false);
        vector<int> path;

        cout << "All possible routes from " << startLocation << " to " << endLocation << ":\n";
        dfsAllRoutes(startIndex, endIndex, visited, path);
    }
    else
    {
        cout << "Invalid start or end location." << endl;
    }
    printRouteHeader();
}

void BusRoute::dfsAllRoutes(int currentNode, int targetNode, vector<int> &visited, vector<int> &path)
{
    visited[currentNode] = true;
    path.push_back(currentNode);

    if (currentNode == targetNode)
    {
        cout << "Route: ";
        for (int i = 0; i < path.size(); ++i)
        {
            cout << nodes[path[i]]->getName();
            if (i < path.size() - 1)
            {
                cout << " - ";
            }
        }
        cout << endl;
    }
    else
    {
        for (int neighbor = 0; neighbor < nodeCount; ++neighbor)
        {
            if (!visited[neighbor] && adjacencyMatrix[currentNode][neighbor] == 1)
            {
                dfsAllRoutes(neighbor, targetNode, visited, path);
            }
        }
    }

    visited[currentNode] = false;
    path.pop_back();
}

int main()
{
    BusRoute BusRoute(20);

    BusRoute.addNode(new BusNode("Jakarta"));      // 0
    BusRoute.addNode(new BusNode("Bandung"));      // 1
    BusRoute.addNode(new BusNode("Cirebon"));      // 2
    BusRoute.addNode(new BusNode("Pekalongan"));   // 3
    BusRoute.addNode(new BusNode("Semarang"));     // 4
    BusRoute.addNode(new BusNode("Magelang"));     // 5
    BusRoute.addNode(new BusNode("Jogja"));        // 6
    BusRoute.addNode(new BusNode("Madiun"));       // 7
    BusRoute.addNode(new BusNode("Tulungagung"));  // 8
    BusRoute.addNode(new BusNode("Kediri"));       // 9
    BusRoute.addNode(new BusNode("Surabaya"));     // 10
    BusRoute.addNode(new BusNode("Malang"));       // 11
    BusRoute.addNode(new BusNode("Jember"));       // 12

    BusRoute.addEdge(0, 1);   // Jakarta - Bandung
    BusRoute.addEdge(1, 2);   // Bandung - Cirebon
    BusRoute.addEdge(2, 3);   // Cirebon - Pekalongan
    BusRoute.addEdge(3, 4);   // Pekalongan - Semarang
    BusRoute.addEdge(4, 5);   // Semarang - Magelang
    BusRoute.addEdge(5, 6);   // Magelang - Jogja
    BusRoute.addEdge(6, 7);   // Jogja - Madiun
    BusRoute.addEdge(7, 8);   // Madiun - Tulungagung
    BusRoute.addEdge(8, 9);   // Tulungagung - Kediri
    BusRoute.addEdge(9, 10);  // Kediri - Surabaya
    BusRoute.addEdge(10, 11); // Surabaya - Malang
    BusRoute.addEdge(11, 12); // Malang - Jember

    BusRoute.display();

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Show Shortest Route\n";
        cout << "2. Show All Routes\n";
        cout << "3. Add City\n";
        cout << "4. Add Route\n";
        cout << "5. Delete Route\n";
        cout << "6. Show Adjacency Matrix\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string startLocation, endLocation;
            cout << "Enter start location: ";
            getline(cin, startLocation);

            cout << "Enter end location: ";
            getline(cin, endLocation);

            BusRoute.displayShortestRoute(startLocation, endLocation);
            break;
        }
        case 2:
        {
            string startLocation, endLocation;
            cout << "Enter start location: ";
            getline(cin, startLocation);

            cout << "Enter end location: ";
            getline(cin, endLocation);

            BusRoute.displayAllRoutes(startLocation, endLocation);
            break;
        }
        case 3:
        {
            string cityName;
            cout << "Enter the name of the city to add: ";
            getline(cin, cityName);

            BusRoute.addNode(new BusNode(cityName));
            cout << "City added successfully.\n";
            break;
        }
        case 4:
        {
            string city1, city2;
            cout << "Enter the names of the cities to add the route (space-separated): ";
            cin >> city1 >> city2;

            int node1 = BusRoute.findNodeIndex(city1);
            int node2 = BusRoute.findNodeIndex(city2);

            if (node1 != -1 && node2 != -1)
            {
                BusRoute.addRoute(node1, node2);
            }
            else
            {
                cout << "Invalid city names. Please enter valid city names.\n";
            }
            break;
        }
        case 5:
        {
            string city1, city2;
            cout << "Enter the names of the cities to delete the route (space-separated): ";
            cin >> city1 >> city2;

            int node1 = BusRoute.findNodeIndex(city1);
            int node2 = BusRoute.findNodeIndex(city2);

            if (node1 != -1 && node2 != -1)
            {
                BusRoute.deleteRoute(node1, node2);
            }
            else
            {
                cout << "Invalid city names. Please enter valid city names.\n";
            }
            break;
        }
        case 6:
        {
            BusRoute.displayAdjacencyMatrix();
            break;
        }
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
