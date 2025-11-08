[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/s8DZkGMB)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=21130840&assignment_repo_type=AssignmentRepo)
Note that this is not official.  Follow the canvas assignment for the official requirements.

# Background

Many documents are structured such as HTML, XML, RDF, OWL, etc. Besides the WWW, other systems such as knowledge management and semantic web systems use these formats to represent knowledge and make it easy for algorithms to parse and utilize the data. This assignment focuses on a simplified version of the Resource Description Framework (RDF).  RDF is a very extensible and flexible way of describing the relationships between unique objects.  RDF uses triples to describe these relationships.  An RDF triple consists of a Subject, a Predicate, and an Object.  For example, "Brent is friends with John." could be converted to an RDF triple where Brent is the subject, Friend is the predicate, and John is the object.  In real RDF, you can import rules about a particular domain that describes relationships and properties, also known as an ontology, but in our case, we are just going to assume a simple ontology described later in this document so that the assignment can focus more on recursion.

 

In this assignment, you will create an RDFObject Class that contains a Unique Identifier for each RDFObject, and a std::map of predicate->Object std::pair.   Within the RDFObject class you will also include a method that reads in a structured file and a method to write out the data in the class as a structured file.

Note:  I have provided a limited RDF format.  Your program does not need to be able to parse any arbitrary RDF file.  You can assume the following things about the format:

    You will not need to process any ontologies.  You do not need to support any RDF classes or properties not mentioned in this assignment.
    Descriptors do not contain any whitespace
    The file format will be in Turtle format (or similar -- see the description below as I don't want you writing a complete turtle processor)
    The graph described my the RDFTriples will be connected (there exists a path to all nodes from any node).  Links between objects and subjects are considered to be bi-directional for ease of implementation, even if they logically would not normally be.  If (Brent, teaches, CSS342) is your RDF triple, then you need to create a Brent node, create a CSS342 node, and link the Brent node to the CSS342 node and then link the CSS342 node to the Brent node by creating a <teaching, CSS342> pair in Brent's predicate vector and a <teaching, Brent> pair in CSS342's predicate vector.

 

# Methods you must implement, but you may find others helpful such as a Constructor that takes in a unique id or Getter/Setter methods.

 

Public

    Constructor -- This builds just a single node.
    Constructor (filename) -- initializes an RDF graph from a file.  The constructor should open the file and use the >> operator to read it in.
    Destructor -- make sure to delete all dynamically allocated memory.  You can use valgrind to make sure you are doing this correctly.
    >> -- Correctly read in an RDF document to the class from an istream.  Note that this will dynamically allocate RDFObjects for each item in the turtle file and link them together in the vector of pairs.
    operator << – Must use recursion -- Correctly writes out the RDFObject graph as a turtle file to an ostream.  You must visit all nodes in the graph and print out in turtle format.  Note that because of some simplifications that we made, this may result in your turtle output not being the same as the input since you are storing bi-directional predicates for ease of access whereas the turtle file you read is unidirectional.  This is ok.
    GraphPrint (filename) – Must use recursion -- hint:  This will use a some of the same functionality as <<, so share as much code as possible between the two with generic functions.  This will output the RDF Graph into gml format.

Note that for all recursion, you may use either depth first search or breadth first search.

# Turtle format --  Turtle format that we will use in this assignment is as follows

<UNIQUE IDENTIFIER>

     namespace:predicate VALUE;

where a Unique Identifier can have any number of predicates describing it.  For example:

<https://faculty.washington.edu/lagesse/>
    school:name "Brent Lagesse";
    school:title "Associate Professor";
    school:teaching <https://canvas.uw.edu/courses/1588618/>;
    school:teaching <https://canvas.uw.edu/courses/1588620/>;
  

Note that Unique Identifiers will always be encased in < > and literal values will be encased in "".  In both cases, you will need to create an RDFObject.

 

 

 

# GML format -- This is a simple text-based graph format.   The following example shows you how to create two nodes and connect them with the edge.  In your program, you will replace A and B with the unique IDs of their RDFObject.  You will also replace the node label with the unique ID.   The edge will represent a predicate that describes the relationship between A and B.  You will replace edge label with that predicate.

graph

[

     node

     [

     id A

    label "node label"
     ]

     node

     [

     id A

    label "node label"
     ]

     edge

     [

     source A

     target B

     label "edge label"

     ]

]

 

# Protected/Private

You will be expected to create helper functions as needed for internal use by your class.

 

 

 

# Deliverables

Submit all of these in a zip file on canvas

    RDFObject.cpp – Implementation of all functionality
    RDFObject.h – Class Signature
    RDFDriver.cpp – Test program (provided by me)
    test1.ttl -- Test input (provided by me)
    test.sh -- testing script (provided by me)

 Include a readme if you have made any changes to the files you are not supposed to change or need to explain anything about your work.

# Grading

 

The program must compile, and I must be able to test the correctness of your code for you to receive credit.

Correct design of the class and constructors is worth 10

Correct parsing of the file is worth 20

Correct Writing of the file is worth 15

Correct Graph Print is worth 15

Correct Finder functions are worth 10 each

 

Coding practices (indentation, naming, comments, etc) are worth 10 points

Proper use of version control (meaningful commit message, frequent commits whenever you finish any functionality) are worth 10 points

