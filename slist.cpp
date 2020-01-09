#include "slistheader.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h> 
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace slistheader;

/*
Class Library File
*/
/*class slist
{
  public:
      int length;
      Node* head;
      Node* tail;

      slist();
	  slist(slist s, int index1, int index2); //added in to help with sublist method
      ~slist();
      void add(char cod[], double lat, double lon);
      //void remove(char cod[], double lat, double lon);
      void clear();
      bool equals(slist s);
      Node* get(int index);
      void insert(int index, char cod[], double lat, double lon);
      void exchg(int index1, int index2);
      void swap(int index1, int index2);
      bool isEmpty();
      Node* remove(int index);
      void set(int index, char cod[], double lat, double lon);
      int size();
      slist subList(int start, int end);
      string toString();
};*/

    // Constructor
    slist::slist()
    {
      this->head = NULL;
      this->tail = NULL;
      this->length = 0;
    }

	slist::slist(slist* s, int index1, int index2)
	{
		this->head = s->get(index1);
		//this->tail = s.get(index2);
		//this->length = index2-index1+1;
		//cout << "works until here" << endl;
		for(int i = index1+1; i<index2; i++)
		{
			this->add(s->get(index1)->code, s->get(index1)->latitude, s->get(index1)->longitude, s->get(index1)->distAUS);
		}
		tail = get(index2-index1-1);

	}

    // Destructor
    slist::~slist(){
		cout << "destructor called" << endl;
        Node* current = this->head;
		Node* next;
        while (current != NULL)  
		{ 
    		next = current->next;  
    		free(current);  
    		current = next;  
		}  
    }

    // add(value)				//Adds a new value to the end of this list.
    void slist::add(char cod[], double lat, double lon, double dist)
    {
	  //this = (*slist)reallloc((length+1)*sizeof(Node));
      Node* toAdd = (Node*)malloc(sizeof(Node));//attempt to try to 
	  //Node* toAdd = new Node();
	  //cout << "node created" << endl;
      strcpy(toAdd->code, cod);
	  //cout << "code copied" << endl;
      toAdd->longitude = lon;
      toAdd->latitude = lat;
	  toAdd->distAUS = dist;
	  //cout << "coordinates copied" << endl;
      toAdd->next = NULL;
	  //cout << "next set" << endl;
      if(length != 0) get(length-1)->next = toAdd; //Problem, causes segfault;
	  else
	  {
		  head = toAdd;
	  }
	  //cout << "added to end" << endl; 
	  toAdd->next = tail;
	  //cout << "tail set" << endl;
	  //cout << "added " << cod << endl;
	  length+=1;
    }

    // clear()					//Removes all elements from this list.
    void slist::clear()
    {
      Node* current = this->head;
      while(current->next != NULL)
      {
        delete current;
      }
      this->head = NULL;
      this->tail = NULL;
      this->length = 0;
    } //CHECK THIS ONE -- MAY BE DONE WRONG

    // equals(list)				//Returns true if the two lists contain the same elements in the same order.
    bool slist::equals(slist s)
    {
	  if(s.length != length) return false;
      Node* currentself = this->head;
      Node* currentother = s.head;
      while(currentself->next != NULL)
      {
        if(!(currentself->code == currentother->code || currentself->longitude == currentother->longitude||currentself->latitude == currentother->latitude || currentself->distAUS == currentother->distAUS))
        {
          return false;
        }
		currentself = currentself->next;
		currentother = currentother->next;
      }
      if(currentself->next != currentother->next)
        return false;
      else return true;
    }

    //get(index)				//Returns the element at the specified index in this list.
    Node* slist::get(int index)
    {
      Node* current = this->head;
      for(int i = 0; i < index; i++)
      {
		//cout << "run " << i << endl;
        current = current->next;
      }
      return current;
    }

    //insert(index, value)		//Inserts the element into this list before the specified index.
    void slist::insert(int index, char cod[], double lat, double lon, double dist)
    {
      Node* toInsert = new Node;
      strcpy(toInsert->code, string(cod).c_str()); 
      toInsert->latitude = lat;
      toInsert->longitude = lon;
	  toInsert->distAUS = dist;
	  
	  toInsert->next = get(index);

	  get(index-1)->next = toInsert; 

	  length+=1;
    }

    //exchg(index1, index2)		//Switches the payload data of specified indexes.
    void slist::exchg(int index1, int index2)
    {
		char     tmpcod[5];
		strcpy(tmpcod, (get(index1)->code));
    	double   tmplat = get(index1)->latitude;
    	double   tmplon = get(index1)->longitude;
		double   tmpdst = get(index1)->distAUS;

		strcpy(get(index1)->code, get(index2)->code);
		get(index1)->latitude = get(index2)->latitude;
		get(index1)->longitude = get(index2)->longitude;
		get(index1)->distAUS = get(index2)->distAUS;

		strcpy(get(index2)->code, tmpcod);
		get(index2)->latitude = tmplat;
		get(index2)->longitude = tmplon;
		get(index2)->distAUS = tmpdst;

		//cout << "transfer works";
    }	

    //swap(index1,index2)		//Swaps node located at index1 with node at index2
    void slist::swap(int index1, int index2)
    {
		//cout << index1 << " " << index2 << endl;
		if (index1 == 0 && index2 == length-1)
        {
            Node* temp = get(index1);
            get(index2)->next = get(1);
            head = get(index2);
            temp->next = NULL;
            tail = temp;
            get(index2-1)->next = temp;
        } else if (index1 == 0 && index2 != length-1)
		{
			//cout << "second if: idx1=0 idx2 not end" << endl;
			Node* temp = get(index1);
			/*strcpy(temp->code, get(index1)->code);	
			temp->latitude = get(index1)->latitude;
			temp->longitude = get(index1)->longitude;
			temp->distAUS = get(index1)->distAUS;*/

			Node* temp2 = get(index2+1);
			/*strcpy(temp2->code, get(index2)->code);	
			temp2->latitude = get(index2)->latitude;
			temp2->longitude = get(index2)->longitude;
			temp2->distAUS = get(index2)->distAUS;*/

            get(index2)->next = get(1);
            head = get(index2);
			//cout << get(index2)->code << endl;
            temp->next = temp2;
			get(index2-1)->next = temp;
		} else if(index2 == length-1 && index1 != 0)
		{
			Node* temp = get(index1);
			get(index2)->next = get(index1+1);
			get(index1-1)->next = get(index2);
			temp->next = get(index2);
			get(index2-1)->next = temp;
			tail = get(index2);
		} else
		{
			Node* temp = get(index1);
			Node* temp2 = get(index2+1);
			get(index2)->next = get(index1)->next;
			get(index1-1)->next = get(index2);
			temp->next = temp2;
			get(index2-1)->next = temp;
		}
	}

    // isEmpty()				//Returns true if this list contains no elements.
    bool slist::isEmpty()
    {
      return this->length == 0 && this->head == NULL && this->tail == NULL;
    } //CHECK THIS ONE ONCE OTHER METHODS ARE DONE

    // remove(index)			//Removes the element at the specified index from this list.
    Node* slist::remove(int index)
    {
		if(index != 0)
		{
			Node* temp = get(index);
			get(index-1)->next = get(index+1);
			length -= 1;
			return temp;
		}
		else
		{
			//cout << "z";
			Node* temp = head;
			//cout << "a";
			head = get(1);
			//cout << "b";
			length -= 1;
			return temp;
		}
    }

    // set(index, value)		//Replaces the element at the specified index in this list with a new value.
    void slist::set(int index, char cod[], double lat, double lon, double dist)
    {
      strcpy(get(index)->code, cod);
	  get(index)->latitude = lat;
	  get(index)->longitude = lon;
	  get(index)->distAUS = dist;
    }

    // size()					//Returns the number of elements in this list.
    int slist::size()
    {
		return length;
    }

    // subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
    slist slist::subList(int start, int end)
    {
		return slist(this, start, end);
    }

    // toString()				//Converts the list to a printable string representation.
    string slist::toString()
    {
		if(length == 0) return "\n";
	  stringstream str;
      Node* current = this->head;
      int c = 1;
      for(int i = 0; i < length; i++)
      {
		  //cout << str.str() << endl;
		str << c << ": " << current->code << ": (" << current->latitude << 
		", " << current->longitude << ") " << current->distAUS << "\n";
        //s = string(s) + sprintf(//(string("" + c) + string(": ") + string(current->code, 5) + string(": (") + to_string(current->latitude) + string(", ") + to_string(current->longitude) + string(")\n"));
        c++;
		current = current->next;
		//cout << str.str() << endl;
      }
	  //cout<<str.str()<<endl;
      return str.str();
    } //CHECK FORMATTING