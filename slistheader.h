#include <string>

using namespace std;

namespace slistheader
{
class Node
{
  public:
    Node*    next;
    char     code[5];
    double   latitude;
    double   longitude;
	double distAUS;
};

class slist{
  public:
      int length;
      Node* head;
      Node* tail;

      slist();
	  slist(slist* s, int index1, int index2); //added in to help with sublist method
      ~slist();
      void add(char cod[], double lat, double lon, double dist);
      //void remove(char cod[], double lat, double lon);
      void clear();
      bool equals(slist s);
      Node* get(int index);
      void insert(int index, char cod[], double lat, double lon, double dist);
      void exchg(int index1, int index2);
      void swap(int index1, int index2);
      bool isEmpty();
      Node* remove(int index);
      void set(int index, char cod[], double lat, double lon, double dist);
      int size();
      slist subList(int start, int end);
      string toString();
};
};

/*
Header file for single linked list class library
*/


// add(value)				//Adds a new value to the end of this list.

// clear()					//Removes all elements from this list.

// equals(list)				//Returns true if the two lists contain the same elements in the same order.

//get(index)				//Returns the element at the specified index in this list.

//insert(index, value)		//Inserts the element into this list before the specified index.

//exchg(index1, index2)		//Switches the payload data of specified indexex.

//swap(index1,index2)		//Swaps node located at index1 with node at index2

// isEmpty()				//Returns true if this list contains no elements.

// mapAll(fn)				//Calls the specified function on each element of the linkedlist in ascending index order.

// remove(index)			//Removes the element at the specified index from this list.

// set(index, value)		//Replaces the element at the specified index in this list with a new value.

// size()					//Returns the number of elements in this list.

// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.

// toString()				//Converts the list to a printable string representation.