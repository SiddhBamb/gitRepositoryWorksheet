/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


#include <iostream>
#include <fstream>
#include <cmath> 
#include <string.h>
#include <stdio.h>
#include "slistheader.h"

using namespace std;
using namespace slistheader;

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
    
};



void simpleSortTotal(Node arr[], int low, int high);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main()//change to main later
{
    ifstream infile;
    int i=0;
    char cNum[10] ;
    //Airport* airportArr[13500];		// Replace array with Linked List
	slist* airportArr = new slist();
    int   airportCount;
    //Airport* a[13500];
	Airport* a;
    
    infile.open ("./USAirportCodes.csv", ifstream::in);
    if (infile.is_open())
    {
        int   c=0;
        while (infile.good())
        {
            a = new Airport();
            infile.getline(a->code, 256, ',');
            infile.getline(cNum, 256, ',');
            a->latitude = atof(cNum);
            infile.getline(cNum, 256, '\n');
            a->longitude = atof(cNum);
			(*airportArr).add(a->code, a->latitude, a->longitude, distanceEarth(a->latitude, a->longitude, 30.1944, 97.6700));


            if (!(c % 1000))
                //cout << airportArr->get(c)->code << " long: " <<airportArr->get(c)->longitude << " lat: " << airportArr->get(c)->latitude <<  endl;

            /*
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;                               
            }
            */

            
            i++ ;
            c++;
        }
        airportCount = c-1;
        infile.close();
        
         for (int c=0; c < airportCount; c++)
            if (!(c % 1000))
            {
                //cout << airportArr->get(c)->code << " long: " << airportArr->get(c)->longitude << " lat: " << airportArr->get(c)->latitude <<  endl;
                //cout << airportArr->get(c+1)->code << " long: " << airportArr->get(c+1)->longitude << " lat: " << airportArr->get(c+1)->latitude <<  endl;
                //cout <<"Distance between " << airportArr->get(c)->code << " and " << airportArr->get(c+1)->code << " is " << distanceEarth( airportArr->get(c)->longitude, airportArr->get(c)->latitude , airportArr->get(c+1)->longitude, airportArr->get(c+1)->latitude) << endl;
            }

			//cout << airportArr->size() << " " << //airportArr->get(0)->code << endl;
			airportArr->remove(0);



    }
    else
    {
        cout << "Error opening file";
    }
	
	//int x = (airportArr->size());
	Node arr [airportArr->size()];
	for(int a = 0; a < airportArr->size(); a++)
	{
		(arr)[a] = *airportArr->get(a);
	}

	simpleSortTotal(arr, 0, (sizeof(arr)/sizeof(Node))-1);//correct call: airport->size is right
	//cout << "a" << endl; //problem: sort doesn't complete (exited, illegal instruction) is the error, however, finishes all loops //FIXED: error was finish without returning anything
    //cout << airportArr->get(0)->code << " " << airportArr->get(1)->code << " " << airportArr->get(2)->code << " " << airportArr->get(3)->code << " " << airportArr->get(4)->code << endl;
	airportArr->clear();
	for(int a = 0; a < sizeof(arr)/sizeof(Node); a++)
	{
		airportArr->add(arr[a].code, arr[a].latitude, arr[a].longitude, arr[a].distAUS);
	}
	airportArr->remove(airportArr->size()-1);
	//cout << airportArr->toString() << endl;
	cout<<"The furthest Airport from AUS is " << airportArr->get(airportArr->size()-1)->code << "; It is " << airportArr->get(airportArr->size()-1)->distAUS << " kilometers away from AUS." << endl << endl;

	cout << "All airports within 100 miles of AUS (Note: the distanceEarth function returns distance in kilometers): " << endl;

	int n = 0;
	while((airportArr->get(n)->distAUS * 0.621371) < 100)
	{
		cout << n+1 << ": " << airportArr->get(n)->code << ": (" << airportArr->get(n)->latitude << ", " << airportArr->get(n)->longitude << ") Distance from AUS: " << (airportArr->get(n)->distAUS * 0.621371) << " miles" << endl;
		n++;
	}
}



#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}


/*
	Provide sort routine on linked list
*/

	void merge(Node arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    Node L[n1], R[n2]; //temps
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0; //
    j = 0; 
    k = l; // 
    while (i < n1 && j < n2) 
    { 
        if (L[i].distAUS <= R[j].distAUS) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 


void simpleSortTotal(Node arr [], int left, int right)
{
	//cout << "sorting now... " << endl;

    if (left < right) 
    { 
        int m = left+(right-left)/2; 

        simpleSortTotal(arr, left, m); 
        simpleSortTotal(arr, m+1, right); 
  
        merge(arr, left, m, right); 
    } 


	
	/*int i, j;
	Node* tmp = new Node;

      for (i = 1; i < n; i++) {

            j = i;
			cout << i << endl;
            while (j > 0 && arr->get(j-1)->distAUS > arr->get(j)->distAUS) {
				
                  /*strcpy(tmp->code,  arr->get(j)->code);
				  tmp->latitude =  arr->get(j)->latitude;
				  tmp->longitude =  arr->get(j)->longitude;
					tmp->distAUS =  arr->get(j)->distAUS;*/

					//cout << tmp->code << endl;
                  //arr->set(j, arr->get(j-1)->code, arr->get(j-1)->latitude, arr->get(j-1)->longitude, arr->get(j-1)->distAUS);

				//cout << tmp->code << endl;
                   //arr->set(j-1, tmp->code, tmp->latitude, tmp->longitude, tmp->distAUS);//arr[j - 1] = tmp;

				//cout<<"enters"<<endl;
				   /*arr->swap(j-1, j);//slow

                  j--;

            }
			//cout << arr->toString() << endl;

      } *///decent sort but doesnt work


    /*if (arr->size() <= 1) return arr; // base case
		// recursively sort two sub arrays ("divide")
		int mid     = arr->size() / 2;
		slist* arr2 = new slist(arr, 0, mid);
		slist* left  = simpleSortTotal(arr2);

		slist* arr3 = new slist(arr, mid, arr->size());
		slist* right = simpleSortTotal(arr3);
		//System.out.println("HELLO");
		// merge the left and right arrays ("conquer")
		int l = 0, r = 0;
		for (int i = 0; i < arr->size(); i++)
		{
			// if at the end of left or right array
			if (r >= right->size()){       
				arr->set(i, left->get(l)->code, left->get(l)->latitude, left->get(l)->longitude, left->get(l)->distAUS);  
				l++;
			}
			else if (l >= left->size()){   
				arr->set(i, right->get(r)->code, right->get(r)->latitude, right->get(r)->longitude, right->get(r)->distAUS);
				r++;
			}
			// find the minimum of the left and right array
			else if(left->get(l)->distAUS < right->get(r)->distAUS)
			{ 
				arr->set(i, left->get(l)->code, left->get(l)->latitude, left->get(l)->longitude, left->get(l)->distAUS); 
				l++;
			}
			else{                         
				arr->set(i, right->get(r)->code, right->get(r)->latitude, right->get(r)->longitude, right->get(r)->distAUS); 
				r++;
			}
		}
		// return the merged and sorted array
		return arr;
	*/ // failed attempt at mergesort
	/*int i, j; 
	Node* tmp;

      for (i = 0; i < n; i++) {

            j = i;
		cout << i << endl;
            while (j > 0 && (arr->get(j - 1)->distAUS > arr->get(j)->distAUS)) {
					
                  tmp = arr->get(j);

                  arr->exchg(j, j - 1);

                  //arr->set(j - 1, tmp->code, tmp->latitude, tmp->longitude, tmp->distAUS);

                  j--;

            }

      }*///SUPER SLOW, DON'T USE



	/*
	int i, j, min_idx;  
    for (i = 0; i < n-1; i++)  
    {  
		cout << i << endl;
        min_idx = i;  
        for (j = i+1; j < n; j++)  
        	if (arr->get(j)->distAUS < arr->get(min_idx)->distAUS) 
            	min_idx = j;  
  
        arr->exchg(min_idx, i);  
    } */ //INSANELY slow selection sort 
	/*int j = 0;  
	Node* key;
    for (int i = 1; i < n; i++) 
    {  
		cout << i << endl; 
		key = arr->get(i); 
		//cout << "a" << endl;
        j = i - 1; 
		//cout << "b" << endl; 
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position
    	while (j >= 0 && arr->get(j)->distAUS > key->distAUS) 
        {  
            arr->set(j+1, arr->get(j)->code, arr->get(j)->latitude, arr->get(j)->longitude, arr->get(j)->distAUS);//arr[j + 1] = arr[j];  
			//cout << "c" << endl;
            j = j - 1;  
        }  
        arr->set(j, key->code, key->latitude, key->longitude, key->distAUS);// arr[j + 1] = key;
		//cout << "d" << endl; 
    }*/  // superslow insertionsort implementation
	//return arr;
	//cout << "sort complete" << endl; 
}







//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


/*#include <iostream>
#include <fstream>
#include <cmath> 
#include "slistheader.h"
#include <string.h>

using namespace std;
using namespace slistheader;

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
    
};

int main()
{
	cout << "started main" << endl;
    slist * s = new slist();
	cout << "constructor test:\n initialized slist" << endl;
    //Airport* a[13500];
	(*s).add("zero", 0, 0,0);//problem with add method, results in seg fault //FIXED
	(*s).add("one", 1, 1,1);
	(*s).add("two", 2, 2,2);
	(*s).add("three", 3, 3,3);
	(*s).add("four", 4, 4,4);
	(*s).add("five", 5, 5,5);
	(*s).add("six", 6, 6,6);
	cout<<(s->toString())<<endl;

	slist * s2 = new slist();
	cout << "constructor test:\n initialized slist2" << endl;

    //Airport* a[13500];
	(*s2).add("zero", 0, 0,0);//problem with add method, results in seg fault //FIXED
	(*s2).add("one", 1, 1,1);
	(*s2).add("two", 2, 2,2);
	(*s2).add("three", 3, 3,3);
	(*s2).add("four", 4, 4,4);
	(*s2).add("five", 5, 5,5);
	(*s2).add("six", 6, 6,6);
	cout<<(s2->toString())<<endl;

	slist * s3 = new slist();
	cout << "contructor test:\n initialized slist3" << endl;
    //Airport* a[13500];
	(*s3).add("zero", 0, 0, 0);

	cout << "equals test\n" <<  (*s).equals((*s2)) << endl; //should be 1 for true : yes
	cout << "equals test:\n" <<  (*s).equals((*s3)) << endl << endl; //should be 0 for false : yes

	cout << "get test\n" << (*s).get(0)->code << (*s).get(2)->code << (*s).get(4)->code << (*s).get(6)->code << endl << endl;

	(*s).insert(3, "seven", 7, 7, 7); //problem: insert method just repeats the given thing for the all after that index//FIXED
	cout << "insert test\n" << (s->toString()) << endl;

	(*s).remove(3);
	cout << "remove test\n" << (s->toString()) << endl;

	(*s).exchg(0, 6);
	cout << "exchg test\n" << (s->toString()) << endl;
	//cout<<"exchg works";

	(*s).swap(0, 6);
	cout << "swap test \n" << (s->toString()) << endl;//WORKS

	(*s).swap(0, 5);
	cout << "swap test \n" << (s->toString()) << endl;
	(*s).swap(0,5);

	(*s).swap(2,6);
	cout << "swap test \n" << (s->toString()) << endl;
	(*s).swap(2,6);

	(*s).swap(3,4);
	cout << "swap test \n" << (s->toString()) << endl;
	(*s).swap(3,4);

	(*s3).clear();
	//cout << (*s3).toString() << endl;
	cout << "isEmpty test: s3 is now empty: " << (*s3).isEmpty() << endl << endl;

	(*s).add("zero", 0, 0, 0);
	(*s).set(7, "seven", 7, 7, 7);
	cout << "set test \n" << (s->toString()) << endl;

	cout << "size test \nslist1's size is: " << (*s).size() << endl << endl;

	//cout << "sublist test:\nslist1's sublist from 2 to 5 is: \n" << (*s).subList(2, 5).toString() << endl; // DOESN'T WORK: work on this later

	//cout<< (s->get(6)->code) << (s->get(0)->code)<<endl;
	

	/*(*s).clear();
	cout<<(s->toString())<<endl;*/
//}








//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


/*#include <iostream>
#include <fstream>
#include <cmath> 
#include "slistheader.h"
#include <string.h>

using namespace std;
using namespace slistheader;

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
    
};

int main()
{
	cout << "started main" << endl;
    slist * s = new slist();
	cout << "constructor test:\n initialized slist" << endl;
    //Airport* a[13500];
	(*s).add("zero", 0, 0,0);//problem with add method, results in seg fault //FIXED
	(*s).add("one", 1, 1,1);
	(*s).add("two", 2, 2,2);
	(*s).add("three", 3, 3,3);
	(*s).add("four", 4, 4,4);
	(*s).add("five", 5, 5,5);
	(*s).add("six", 6, 6,6);
	cout<<(s->toString())<<endl;

	slist * s2 = new slist();
	cout << "constructor test:\n initialized slist2" << endl;

    //Airport* a[13500];
	(*s2).add("zero", 0, 0,0);//problem with add method, results in seg fault //FIXED
	(*s2).add("one", 1, 1,1);
	(*s2).add("two", 2, 2,2);
	(*s2).add("three", 3, 3,3);
	(*s2).add("four", 4, 4,4);
	(*s2).add("five", 5, 5,5);
	(*s2).add("six", 6, 6,6);
	cout<<(s2->toString())<<endl;

	slist * s3 = new slist();
	cout << "contructor test:\n initialized slist3" << endl;
    //Airport* a[13500];
	(*s3).add("zero", 0, 0, 0);

	cout << "equals test\n" <<  (*s).equals((*s2)) << endl; //should be 1 for true : yes
	cout << "equals test:\n" <<  (*s).equals((*s3)) << endl << endl; //should be 0 for false : yes

	cout << "get test\n" << (*s).get(0)->code << (*s).get(2)->code << (*s).get(4)->code << (*s).get(6)->code << endl << endl;

	(*s).insert(3, "seven", 7, 7, 7); //problem: insert method just repeats the given thing for the all after that index//FIXED
	cout << "insert test\n" << (s->toString()) << endl;

	(*s).remove(3);
	cout << "remove test\n" << (s->toString()) << endl;

	(*s).exchg(0, 6);
	cout << "exchg test\n" << (s->toString()) << endl;
	//cout<<"exchg works";

	(*s).swap(0, 6);
	cout << "swap test \n" << (s->toString()) << endl;//WORKS

	(*s).swap(0, 5);
	cout << "swap test \n" << (s->toString()) << endl;
	(*s).swap(0,5);

	(*s).swap(2,6);
	cout << "swap test \n" << (s->toString()) << endl;
	(*s).swap(2,6);

	(*s).swap(3,4);
	cout << "swap test \n" << (s->toString()) << endl;
	(*s).swap(3,4);

	(*s3).clear();
	//cout << (*s3).toString() << endl;
	cout << "isEmpty test: s3 is now empty: " << (*s3).isEmpty() << endl << endl;

	(*s).add("zero", 0, 0, 0);
	(*s).set(7, "seven", 7, 7, 7);
	cout << "set test \n" << (s->toString()) << endl;

	cout << "size test \nslist1's size is: " << (*s).size() << endl << endl;

	//cout << "sublist test:\nslist1's sublist from 2 to 5 is: \n" << (*s).subList(2, 5).toString() << endl; // DOESN'T WORK: work on this later

	//cout<< (s->get(6)->code) << (s->get(0)->code)<<endl;
	

	/*(*s).clear();
	cout<<(s->toString())<<endl;*/
//}



