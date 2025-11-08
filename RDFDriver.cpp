#include<iostream>
#include<fstream>
#include "RDFObject.h"

using namespace std;

int main () {

	RDFObject rdf1;
	RDFObject rdf2("test1.ttl");
	cout << "---Constructors Tested---" << endl;

	ifstream inFile("test1.ttl");
	inFile >> rdf1;
	inFile.close();

	cout << "--- input operator tested---" << endl;

	ofstream outFile("output.ttl");
	outFile << rdf2;
	outFile.close();

	cout << "--- output operator tested ---" << endl;

	rdf1.GraphPrint("test.gml");

	cout << "--- GraphPrint tested ---" << endl;


	

	return 0;
}
