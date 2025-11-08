#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

class RDFObject
{
// private node class for objects located in the graph/RDFObject
private:
	class Node 
	{
	public:
		// unique id for node
		string id;
		// connections from this node to others
		vector <pair<string, Node*>> connections;
		bool visited = false; // used for graph traversal
		Node() {
			id = "emptyNode";
		}
		Node(string newid) {
			id = newid;
		}
		Node(string newid, string connectionType, Node* connectTo) {
			id = newid;
			connections.emplace_back(connectionType, connectTo);
		}
		~Node() {

		}
	};

	// all nodes in the RDFObject
	vector <Node*> listOfNodes;

	// resets node visited boolean for traversal
	void resetVisitMarkers();
	// creates a connection between two nodes with a predicate connectionType
	bool createConnection(Node* start, string connectionType, Node* end);
	// checks if a node with the given id is already in the RDFObject
	Node* isInGraph(string id);
	// checks if a connections between two nodes with a certain connection type already
	// exists in the graph or not
	bool isConnected(Node* start, string connection, Node* end);
	// prints edges of the RDFObject recursively, depth first traversal
	ostream& printEdges(ostream& out, Node* ptr);

public:
	// default constructor
	RDFObject();
	// constructor when given a file name
	RDFObject(string fileName);
	// destructor
	~RDFObject();

	// prints out RDFObject to a file
	void GraphPrint(string fileName);
	// overload for <<
	friend ostream& operator<<(ostream& out, RDFObject& object);
	// overload for >>
	friend istream& operator>>(istream& in, RDFObject& object);
};

