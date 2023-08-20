/*
* Victor Gomez
* Assignment: Project 2 CS 300
* 08/12/2023
* Instructor Charles Griffith
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <climits>
#include <vector>
#include <time.h>
#include <list>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 8;

// define a structure to hold information
struct Course {
	string courseId; // unique identifier
	string courseTitle;
	string coursePre1;
	string coursePre2;
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */


void printMenu() {
	cout << "MENU:" << endl;
	cout << "Option 1 Load Data Structure" << endl;
	cout << "Option 2 Print Course List" << endl;
	cout << "Option 3 Print Course" << endl;
	cout << "Option 9 Exit" << endl;
}

class HashTable {

private:
	// Define structures to hold courses
	struct Node {
		Course courses;
		unsigned int key;
		Node* next;

		// default constructor
		Node() {
			key = UINT_MAX;
			next = nullptr;
		}

		// initialize with a course
		Node(Course aCourse) : Node() {
			courses = aCourse;
		}

		// initialize with a course and a key
		Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
			key = aKey;
		}
	};

	vector<Node> nodes;

	unsigned int tableSize = DEFAULT_SIZE;

	unsigned int hash(int key);

public:
	HashTable();
	HashTable(unsigned int size);
	virtual ~HashTable();
	void printCourseInformation();
	void Insert(Course courses);
	Course Search(string courseId);
	void printCourse(Course courses);

};

/**
 * Default constructor
 */
HashTable::HashTable() {
	// FIXME (1): Initialize the structures used to hold bids
	nodes.resize(tableSize);
	// Initalize node structure by resizing tableSize
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
	// invoke local tableSize to size with this->
	// resize nodes size
	this->tableSize = size;
	nodes.resize(tableSize);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
	// FIXME (2): Implement logic to free storage when class is destroyed

	// erase nodes beginning

	nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
	// FIXME (3): Implement logic to calculate a hash value
	// return key tableSize

	return key % tableSize;


}

void HashTable::printCourse(Course courses) {


	string iD = courses.courseId;
	string title = courses.courseTitle;
	string pre1 = courses.coursePre1;
	string pre2 = courses.coursePre2;

	cout << " Course ID : " << iD << endl;
	cout << " Course Title : " << title << endl;
	cout << " Course Pre : " << pre1 << endl;
	cout << " Course Pre : " << pre2 << endl;

	cout << endl;


};

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Course courses) {

	 // create the key for the given course
	unsigned key = hash(atoi(courses.courseId.c_str()));

	// try and retrieve node using the key
	Node* oldNode = &(nodes.at(key));

	// if no entry found for this key
	if (oldNode == nullptr) {
		Node* newNode = new Node(courses, key);
		nodes.insert(nodes.begin() + key, (*newNode));
	}
	else
	{
		// node found
		if (oldNode->key == UINT_MAX) {
			oldNode->key = key;
			oldNode->courses= courses;
			oldNode->next = nullptr;
		}
		else {
			// find the next open node (last one)
			while (oldNode->next != nullptr) {
				oldNode = oldNode->next;
			}
			oldNode->next = new Node(courses, key);

		}

	}


}

//Searching for Course


Course HashTable::Search(string courseId) {
	Course courses;

	unsigned key = hash(atoi(courseId.c_str()));
	// search for node with the key value
	Node* node = &(nodes.at(key));
	// search for node using key
	// if node is found by given key
	if (node != nullptr && node->key != UINT_MAX
		&& node->courses.courseId.compare(courseId) == 0) {
		return node->courses;
	}
	// if there is no node with the key value
	if (node == nullptr || node->key == UINT_MAX) {
		return courses;
	}
	// traverse list to look for a match
	while (node != nullptr) {
		if (node->key != UINT_MAX && node->courses.courseId.compare(courseId) == 0) {
			return node->courses;
		}
		node = node->next;
	}
	return courses;

}


/**
 * Print all courses and prereq
 */
void HashTable::printCourseInformation() {
	// for node begin to end iterate
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		// if key not equal to UINT_MAx
		if (it->key != UINT_MAX) {

			cout << "Course ID: " << it->courses.courseId << " ";
			cout << "Course Title: " << it->courses.courseTitle << " ";
			cout << "Course Pre: " << it->courses.coursePre1 << " ";
			cout << "Course Pre: " << it->courses.coursePre2 << endl;

			// node is equal to next iter
			Node* node = it->next;

			// while node not equal to nullptr
			while (node != nullptr) {
				// output course, title, pre1, and pre2
				cout << "Course ID: " << node->courses.courseId << " ";
				cout << "Course Title: " << node->courses.courseTitle << " ";
				cout << "Course Pre: " << node->courses.coursePre1 << " ";
				cout << "Course Pre: " << node->courses.coursePre2 << endl;

				// node is equal to next node
				node = node->next;
			}
		}
	}

}


int main() {

	// Variables
	ifstream inFS;
	string input;
	int n = 0;
	char q = 'c';
	int menuOpt = 0;
	string courseKey = "";
	

	HashTable* courseTable;

	Course courses;

	courseTable = new HashTable();


	// While menu loop
	while (q != 'q') {

		printMenu();

		cout << endl;
		cout << "Please enter the number of the Option you wish to use. (Example 1, 2, 3, or 9)" << endl;
		cin >> menuOpt;
		cout << endl;
		// Option 1
		if (menuOpt == 1) {

			// Opening file Computer.txt
			cout << "Opening file ComputerScience.txt" << endl;
			cout << "Loading Info into Data Structure" << endl << endl;

			inFS.open("ComputerScience.txt", ios::in);


			while (inFS) {

				string line1, line2, line3, line4, line5;
				stringstream linestream;

				while (getline(inFS, line1)) {
					Course courses;

					line4 = "";
					line5 = "";

					stringstream linestream(line1);
					getline(linestream, line2, ',');
					courses.courseId = line2;
					getline(linestream, line3, ',');
					courses.courseTitle = line3;
					getline(linestream, line4, ',');
					courses.coursePre1 = line4;
					getline(linestream, line5, ',');
					courses.coursePre2 = line5;


					courseTable->Insert(courses);

					linestream.clear();
					linestream.str("");
				}
			}
			// If could not open file error message
			if (!inFS.is_open()) {
				cout << "Could not open file ComputerScience.txt" << endl;
				return 1;
			}

			cout << endl;
			// Close file Computer.txt
			inFS.close();



		}
		//Option 2
		else if (menuOpt == 2) {

			// Print Course List
			cout << "Printing Course List" << endl;

			courseTable -> printCourseInformation();

			cout << endl;

		}
		//Option 3
		else if (menuOpt == 3) {

			cout << "Please enter Course ID to find the prereqs:" << endl;
			cin >> courseKey;
			transform(courseKey.begin(), courseKey.end(), courseKey.begin(), ::toupper);

			courses = courseTable->Search(courseKey);

			//Print Course
			cout << "Pringting Course" << endl;
			courseTable -> printCourse(courses);

		}
		//Option 4
		else if (menuOpt == 9) {

			//Quits program and says Bye!!!
			cout << "Thank you for using the course planner!" << endl;
			q = 'q';
		}
		//Error, if wrong int put in
		else if (menuOpt <= 0 || (menuOpt >= 4 && menuOpt != 9)) {
			cout << "Please Enter a valid option." << endl;
		}


	}

	return 0;
}