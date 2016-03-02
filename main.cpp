/*
Professor: Dr. Knox
Class: COSC 1437 Spring 2016
Assignment: Team Project 1: Movie Theater
Author: Jacob Gibson, Chris Cavazos, and Celeste Avila
Leader: Chris Cavazos
Date: 3/11/2016
*/
//hello
/////////////////////////////////////////////////////Change
//Library Class Reader Files
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <cctype>
#include <cstring>
#include <algorithm>
#include "basiclib.h"
#include "fileIO.h"

using namespace std;

//Constants for theater dimensions
const int COLUMNS = 16, ROWS = 10;
//Constants for theater seating prices
const float LOWPRICE = 25.00, MEDIUMPRICE = 35.00, HIGHPRICE = 50.00;

//Author: Jacob
//Patron structure to hold ID, name, and number
struct Patron
{
    string ID; //Patron number from 001 to 160
    string Name; //Patron first and last name
    string PhoneNumber;
};

//Author: Jacob
//Seat structure to hold location, price, status, and patron ID
struct Seat
{
    int Row; //Row number 1 through 10
    int Number; //Seat number 1 through 16
    float Price; //Price of seat
    bool SoldStatus; //True = sold
    string SeatID = "MT"; //Default SeatID = "MT" for empty

    //Set SeatID equal to PatronID of person who purchased it
    void SetID(Patron& p)
    {
        SeatID = p.ID;
    }
};


//Reads in Seating Chart data and sales revenue data from .txt files
void readInData();
//Outputs Seating Chart data and sales revenue data to .txt files
void writeOutData(bool arr[ROWS][COLUMNS]);
//Outputs seating chart report to console or file
//void displaySeatingChart(ostream & str, bool arr[ROWS][CLM]);

//Auth:Chris
void displaySeatingChart(ostream & str,bool** arr){
	centerString(str,"HUNTINGTON PLAYHOUSE");
	centerString(str,"SEATING CHART");
	str<<endl;
	centerString(str, "Rear");
	for(int i=0; i < ROWS; i++){
		string temp="";
		for(int j=0; j < COLUMNS; j++){
			char c='O';
			if(arr[i][j])c='X';
			temp.append(" ");
			temp+=c;
			if(j== (COLUMNS / 2) - 1){
				temp.append(" ");
			}
		}
		centerString(str,temp);
	}
	str<<endl;
}



//////////////////////////////////////////////////////////////////////////////
void PhoneNumberFormatter(string PhoneNumber)
{
    int count;
    bool testNumber = false; // bool to check if numbers are digits

    // uses .length to check how many numbers are in the string
    // also checks if values in the string are numeric values
   while (PhoneNumber.length () != 10 || testNumber == false)
    {
        testNumber =  true;
        if(PhoneNumber.length() == 10)
        {
            for (count = 0; count < 10; count ++)
            {
            	/*  This needs to be fixed -chris
                if (!isdigit (custNum[count]))
                {
                    testNumber = false;
                }*/
            }
        }
        else
        {
            testNumber = false;
        }
        if(testNumber ==  false)
        {
            cout << "Please use the proper format of (999)999-9999, Try again.";  // prompts user to enter a new number
            cin >> PhoneNumber;
        }
    // formats the phone number
     PhoneNumber = PhoneNumber.insert( 0, "(" );
     PhoneNumber = PhoneNumber.insert( 3, ")" );
     PhoneNumber = PhoneNumber.insert( 6, "-" );
     // displays phone number
     cout << PhoneNumber << endl;
    }

}

//Auth:Chris
void updateSeatCheckArr(int x, int y, vector<Seat> sold, vector<Seat> unsold, bool **seatCheck){
	bool cont=true;
	try{
		for(int i=0;i<sold.size() && sold.size()>0;i++){
		Seat s=sold.at(i);
		if(x==s.Row && y==s.Number){
			cont=false;
		}
	}
	}
	catch(...){
		cout<<"Size err"<<endl;
	}

	if(cont){
		int temp=0;
		Seat tempSeat;
		cout<<"@";
	try{
		for(int i=0;i<unsold.size();i++){
			Seat s=sold.at(i);
			if(x==s.Row && y==s.Number){
			seatCheck[x][y]=false;
			temp=i;
			tempSeat=s;
		}
		cout<<"#";
		}


		unsold.erase(unsold.begin()+temp-1);
	}
	catch(...){
		cout<<"Size err"<<endl;
	}
		sold.push_back(tempSeat);
	}

}
//////////////////////////////////////////////////////////////////////////////
//Auth:Chris
void purchaceSingleSeat(vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck) {
	Seat temp;
	int index ,x,y;
	bool check=false;

	cout<<"Please enter seat row and seat number separated by a space.\n(ex. \"2 5\")\n";
	cin>>x>>y;

	cout<<endl;
	for(int i=0; i<unsold.size();i++){
		Seat s = unsold.at(i);
		if(s.Number==x-1 && s.Row==y-1){
			temp=s;
			index=i;
			sold.push_back(temp);
			check=true;
			seatCheck[x-1][y-1]=check;
		}
	}
	if(check) {
		cout << "Seat Col:" << x << " Row:" << y << " purchased." << endl;
		unsold.erase(unsold.begin() + index);
		cout << unsold.size() << " seats remaining" << endl;
		displaySeatingChart(cout, seatCheck);
	}
}
//Auth:Chris
void purchaceBlockSeat(int x, int y, int x2, int y2, vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck) {
	if(x2<=x || y2<=x){
		cout<<"INVALID SELECTION"<<endl;
	}
	else{
		Seat temp;
		int index;
		for(int j=x; j<x2; j++){
			for(int k=y;k<y2;k++){
				for(int i=0; i<unsold.size();i++){
				Seat s = unsold.at(i);
				if(s.Number==j && s.Row==k){
					temp=s;
					index=i;
					sold.push_back(temp);
				}
			}
			unsold.erase(unsold.begin()+index);
				}
			}

}
}

void printMenuOptions(){
	cout<< setw(61)<< " ______________________________________ \n"
	<< endl
	<< setw(61)<< "|              TICKET MENU             |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| A. Ticket Sales                      |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| B. Patron Information Search         |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| C. Current Revenue                   |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| D. Information                       |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| #. Exit                              |\n"
	<< setw(61)<< " ______________________________________  "<< endl;
}

void mainMenu(vector<Seat> &unsold, vector<Seat> &sold, bool **seatCheck){
	char choice;
	printMenuOptions();

	cin >> choice;


	while(choice!='#'){
		switch(choice)
		{
		    case 'a':
			case 'A': //call

				purchaceSingleSeat(unsold,sold,seatCheck);

				break;

            case 'b':
			case 'B': //call
				cout<<endl;
				break;

            case 'c':
			case 'C': //call
				cout<<endl;
				break;

            case 'd':
			case 'D': //call
				cout<<endl;
				break;

			case '#':
				cout<<"EXIT"<<endl;
				break;
			default:
				cout<<setw(47)<<endl<<"Invalid choice."<<endl<<endl<<endl;
				cin>>choice;
		}
		printMenuOptions();
		cin>>choice;
	}



}
int main() {
	cout<<"#";
	bool **seatCheck=new bool *[COLUMNS];
	for(int i=0; i < ROWS; i++){
		seatCheck[i]=new bool[COLUMNS];
	}
	for(int i=0; i < ROWS; i++){
		for(int j=0; j < COLUMNS; j++){
		seatCheck[i][j]=false;
		}
	}
	vector<Seat> unsoldSeats;
	vector<Seat> soldSeats;
	cout<<"!";

	for(int i=0; i < ROWS; i++){
		for(int j=0; j < COLUMNS; j++){
			Seat s;
			s.Number=i;
			s.Row=j;
			if(i>0 || i<5){
				s.Price=HIGHPRICE;
			}
			else if( i>=5 ||i<9){
				s.Price=MEDIUMPRICE;
			}else if(i>=9 ||i<16){
				s.Price=LOWPRICE;
			}
			unsoldSeats.push_back(s);
		}
	}
	cout<<"$";

	mainMenu(unsoldSeats,soldSeats,seatCheck);

	return 0;
}


