g++ RDFDriver.cpp RDFObject.cpp -o rdftest
valgrind --leak-check=yes ./rdftest
./rdftest
