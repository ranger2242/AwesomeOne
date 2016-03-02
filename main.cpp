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

using namespace std;

//Constants for theater dimensions
const int ROWS = 16, COLUMNS = 10;
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

void pause();

//Reads in Seating Chart data and sales revenue data from .txt files
void readInData();
//Outputs Seating Chart data and sales revenue data to .txt files
void writeOutData(bool arr[COLUMNS][ROWS]);
//Outputs seating chart report to console or file
void displaySeatingChart(ostream & str, bool arr[COLUMNS][ROWS]);

//Author: Jacob
void pause()
{
	system("PAUSE");
	system("CLS");
}

//Author: Jacob
void readInData(bool arr[COLUMNS][ROWS])
{
    system("CLS");
    //Ask user to read file data or a new blank set of data
    char answer;
    cout << "Do you want to read data from a file instead of starting with blank data? (Y/N)" << endl;
    cin >> answer;

    if (answer == 'Y' || answer == 'y')
    {
        cout << "Reading data from file ..." << endl;

        //Read in seating data
        ifstream SeatingFile;
        SeatingFile.open("SeatingData.csv");

        //If file fails to open, return to menu so user can exit program
        if(SeatingFile.fail())
        {
            cout << "The seating chart file failed to open." << endl;
            pause();
            return;
        }

        string tempStr;
        int tempInt;

        //Read contents of seating data file into bool array
        for (int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                getline(SeatingFile, tempStr, ',');
                tempInt = atoi(tempStr.c_str());
                arr[j][i] = static_cast<bool>(tempInt);
            }
        }

        SeatingFile.close();

        //Input Sales data
        ifstream SalesFile;
        SalesFile.open("SalesData.csv");

        //If file fails to open, inform user
        if(SalesFile.fail())
        {
            cout << "The sales file failed to open." << endl;
            pause();
        }

//        //Temporary values for amount of seats sold
//        int tempInts[3];
//
//        //Get seat sale numbers from file
//        for(int i = 0; i < 3; i++)
//        {
//            getline(SalesFile, tempStr, ',');
//            tempInts[i] = atoi(tempStr.c_str());
//        }
//
//        lowSeatsSold = tempInts[0];
//        medSeatsSold = tempInts[1];
//        highSeatsSold = tempInts[2];
//
//       //Get totalIncome amount from file
//       getline(SalesFile, tempStr, ',');
//       totalIncome = atof(tempStr.c_str());


        SalesFile.close();

        cout << "All data read in correctly!" << endl;
        pause();
    }

    else
    {
        cout << "Resetting all data values" << endl;

        //Fill seating chart with empty, default value
        for (int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                arr[j][i] = false;
            }
        }

        //Set seatsSold counters and total income to zero
//        lowSeatsSold = 0;
//        medSeatsSold = 0;
//        highSeatsSold = 0;
//        totalIncome = 0;

        cout << "Data values reset." << endl;
        pause();
    }
}

//Author: Jacob
void writeOutData(bool arr[COLUMNS][ROWS])
{
    //Output seating data
    ofstream SeatingFile;
    SeatingFile.open("SeatingData.csv");

    //If file fails to open, inform user
    if(SeatingFile.fail())
    {
        cout << "The seating chart file failed to open." << endl;
        pause();
    }

    //Write contents of bool array as 1's and 0's to file
    for (int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            SeatingFile << arr[j][i] << ",";
        }
        SeatingFile << endl;
    }

    SeatingFile.close();

    //Output Seating Chart report as shown in console
    ofstream SeatingReport;
    SeatingReport.open("SeatingReport.rpt");

    //If file fails to open, inform user
    if(SeatingReport.fail())
    {
        cout << "The seating report file failed to open." << endl;
        pause();
    }

    displaySeatingChart(SeatingReport, arr);

    SeatingReport.close();

    //Output Sales data
    ofstream SalesFile;
    SalesFile.open("SalesData.csv");

    //If file fails to open, inform user
    if(SalesFile.fail())
    {
        cout << "The sales file failed to open." << endl;
        pause();
    }

//    SalesFile << lowSeatsSold << ",";
//    SalesFile << medSeatsSold << ",";
//    SalesFile << highSeatsSold << ",";
//    SalesFile << totalIncome << endl;

    SalesFile.close();

    //Output Sales report as shown in console
    ofstream SalesReport;
    SalesReport.open("SalesReport.rpt");

    if(SalesReport.fail())
    {
        cout << "The sales file failed to open." << endl;
        pause();
    }

    //displayCurrentRevenue(SalesReport);

    SalesReport.close();
}


//Auth:Chris
void displaySeatingChart(ostream & str,bool arr[COLUMNS][ROWS]){
	centerString(str,"HUNTINGTON PLAYHOUSE");
	centerString(str,"SEATING CHART");
	str<<endl;
	centerString(str, "Rear");
	for(int i=0;i<COLUMNS;i++){
		string temp="";
		for(int j=0;j<ROWS;j++){
			char c='O';
			if(arr[i][j])c='X';
			temp.append(" ");
			temp+=c;
			if(j==(ROWS/2)-1){
				temp.append(" ");
			}
		}
		centerString(str,temp);
	}
	str<<endl;
}



//Auth:Chris
void updateSeatCheckArr(int x, int y, vector<Seat> sold, vector<Seat> unsold, bool seatCheck[COLUMNS][ROWS]){
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

void mainMenu(){
	       int choice;
       string separatorLine;
       separatorLine.assign(40,'-');

        cout << setw(40)<< " TICKET MENU\n" ;
        cout << setw(20) << " " << separatorLine << "\n\n";
        cout << setw(30)<< "1. Ticket Sales \n";
        cout << setw(30)<< "2. Patron Information Search\n";
        cout << setw(30)<< "3. Current Revenue\n";
        cout << setw(30)<< "4. Information\n";
        cout << setw(30)<< "5. Exit Program\n\n\n";

        cin >> choice;

    if (choice == 1) // Ticket Sales
    {

    }
     else if (choice == 2) // Patron Information
     {

     }
       else if (choice == 3)// Current Revenue
        {

        }
        else if (choice == 4)// Information
          {

          }
       else if (choice == 5)// Exit
        {

        }
    else // error check
    {
        cout << " Invalid Choice.";
    }

}

//////////////////////////////////////////////////////////////////////////////
//Auth:Chris
void purchaceSingleSeat(int x, int y, vector<Seat> & unsold, vector<Seat>&sold) {
	Seat temp;
	int index;
	for(int i=0; i<unsold.size();i++){
		Seat s = unsold.at(i);
		if(s.Number==x && s.Row==y){
			temp=s;
			index=i;
			sold.push_back(temp);
		}
	}
	unsold.erase(unsold.begin()+index);
}
int main() {
	mainMenu();
	bool seatCheck[COLUMNS][ROWS];
	for(int i=0;i<COLUMNS;i++){
		for(int j=0;j<ROWS;j++){
		seatCheck[i][j]=false;
		}
	}
	vector<Seat> unsoldSeats; 
	vector<Seat> soldSeats; 

	for(int i=0;i<COLUMNS;i++){
		for(int j=0;j<ROWS;j++){
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
	cout<<"3, 5 purchaced\n";
	purchaceSingleSeat(3,5,unsoldSeats,soldSeats);
	cout<<unsoldSeats.size()<<endl;
	updateSeatCheckArr(3,5,soldSeats,unsoldSeats,seatCheck);
	displaySeatingChart(cout,seatCheck);
	return 0;
}


