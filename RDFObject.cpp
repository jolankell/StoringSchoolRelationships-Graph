#include "RDFObject.h"

// default constructor
RDFObject::RDFObject() {

}

// constructor when given a file
RDFObject::RDFObject(string fileName) {
	ifstream fin(fileName);
	fin >> *this;
}

// destructor
RDFObject::~RDFObject() {
	for (int i = 0; i < listOfNodes.size(); i++) {
		delete listOfNodes[i];
	}
}

// resets visited data member of nodes for traversal
void RDFObject::resetVisitMarkers() {
	for (int i = 0; i < listOfNodes.size(); i++) {
		listOfNodes[i]->visited = false;
	}
}

// prints graph to a file, calls operator<< overload
void RDFObject::GraphPrint(string fileName) {
	ofstream fout(fileName);
	fout << *this;
}

// recursivley prints edges, called in operator<< overload
ostream& RDFObject::printEdges(ostream& out, Node* ptr) {
	ptr->visited = true;

	for (int i = 0; i < ptr->connections.size(); i++) {
		out << "edge\n" << "[\n";
		out << "source " << ptr->id << endl << endl;
		out << "target " << ptr->connections[i].second->id << endl << endl;
		out << "label " << ptr->connections[i].first << endl;
		out << "]\n\n";

		if (ptr->connections[i].second->visited == false) {
			printEdges(out, ptr->connections[i].second);
		}
	}
	return out;
}

// prints graph to out, calls printEdges
ostream& operator << (ostream& out, RDFObject& object) {
	out << "graph\n" << "[\n\n";
	for (int i = 0; i < object.listOfNodes.size(); i++) {
		out << "node\n" << "[\n";
		out << object.listOfNodes[i]->id << endl << endl;
		out << object.listOfNodes[i]->id << endl;
		out << "]\n\n";
	}

	object.printEdges(out, object.listOfNodes[0]);
	object.resetVisitMarkers();

	out << "]\n";
	return out;
}

// reads from file in, using RDF triple format into a RDFObject object
istream& operator >> (istream& in, RDFObject& object) {
	string fileInput;
	string id;
	string predicate;
	string nodeConnect;
	int index = 0; bool connected;
	RDFObject::Node* start = nullptr;
	RDFObject::Node* end = nullptr;

	// reads in unique id
	while (getline(in, fileInput)) {

		if (fileInput.empty() == true) {
			continue;
		}

		id = fileInput;
		start = object.isInGraph(id);
		if (start == nullptr) {
			start = new RDFObject::Node(id);
			object.listOfNodes.push_back(start);
		}

		// reads in a predicate and destination id
		while (getline(in, fileInput) && fileInput != "" && fileInput != "\t") {

			fileInput.erase(0, 1);
			fileInput.erase(fileInput.size() - 1, 1);
			index = fileInput.find(' ');
			predicate = fileInput.substr(0, index);
			nodeConnect = fileInput.substr(index + 1);
			
			//cout << predicate << nodeConnect;

			end = object.isInGraph(nodeConnect);
			if (end == nullptr) {
				end = new RDFObject::Node(nodeConnect);
				object.listOfNodes.push_back(end);
			}

			connected = object.createConnection(start, predicate, end);
			if (connected == false) {
				cout << "Repeat connection in file, " << start->id << " already connected by " << predicate << " to "
					 << end->id << ", only one of the entries was inserted\n\n";
			}
		}
	}
	return in;
}

// creates a connection between start node and end node with predicate connectionType if
// it isnt already in the RDFObject
bool RDFObject::createConnection(Node* start, string connectionType, Node* end) {
	if (isConnected(start, connectionType, end) == false) {
		start->connections.emplace_back(connectionType, end);
		end->connections.emplace_back(connectionType, start);
		return true;
	}
	return false;
}

// checks if a node with the given id is already in the RDFObject
RDFObject::Node* RDFObject::isInGraph(string id) {
	for (int i = 0; i < listOfNodes.size(); i++) {
		if (listOfNodes[i]->id == id) {
			return listOfNodes[i];
		}
	}
	return nullptr;
}

// checks if a connection between start node and end node with a predicate connection
// already exists in the RDFObject or not
bool RDFObject::isConnected(Node* start, string connection, Node* end) {
	Node* node = nullptr;
	node = isInGraph(start->id);
	if (node != nullptr) {
		for (int i = 0; i < node->connections.size(); i++) {
			if (node->connections[i].first == connection && node->connections[i].second->id == end->id) {
				return true;
			}
		}
	}
	return false;
}