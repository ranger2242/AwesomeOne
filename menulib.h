#include <vector>
#include <iostream>
#include "Seat.h"
#include "basiclib.h"
using namespace std;
void ticketSalesMenu ();
void printMenuOptions();
void displaySeatingChart(ostream &,bool**);
void purchaceSingleSeat(vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck) ;

//Constants for theater dimensions
const int COLUMNS = 16, ROWS = 10;
//Constants for theater seating prices
const float LOWPRICE = 25.00, MEDIUMPRICE = 35.00, HIGHPRICE = 50.00;

//////////////////////////////////////////////////////////////////////////////
//Author: Celeste
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
	}else{
		cout<<"Seat is unavalable for purchase."<<endl;
	}

}
//Auth:Chris
void purchaceBlockSeat(vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck) {
	int x,x2,y,y2;
	cout<<"Block Seat purchase.";
	cout<<"Please enter seat row and seat number separated by a space.\n(ex. \"x y x2 y2\")\n";
	cin>>x>>y>>x2>>y2;
	vector<Seat> conflicts;
	bool cont=true;
	for(int j=x; j<x2; j++) {
		for (int k = y; k < y2; k++) {
			for (int i = 0; i < sold.size(); i++) {
				Seat s = sold.at(i);
				if (s.Number == j - 1 && s.Row == k - 1) {
					cont = false;
					conflicts.push_back(s);
				}
			}
		}
	}
	if(!cont){
		for(int i=0;i<conflicts.size();i++){
			Seat s = conflicts.at(i);
			cout<<"Seat at Col:"<<s.Number<<" Row:"<<s.Row<<" already purchased.";
		}
	}
	if(!((x2>=x || y2>=y) && cont)){
		cout<<"INVALID SELECTION"<<endl;
	}
	else{
		Seat temp;
		int index;
		bool check=false;
		for(int j=x; j<=x2; j++){
			for(int k=y;k<=y2;k++){
				for(int i=0; i<unsold.size();i++){
				Seat s = unsold.at(i);
				if(s.Number==j-1 && s.Row==k-1){
					temp=s;
					index=i;
					sold.push_back(temp);
					check=true;
					seatCheck[j-1][k-1]=check;
				}
			}
				if(check) {
					cout << "Seat Col:" << j << " Row:" << k << " purchased." << endl;
					unsold.erase(unsold.begin() + index);
					cout << unsold.size() << " seats remaining" << endl;
					displaySeatingChart(cout, seatCheck);
				}else{
					cout<<"Seat is unavalable for purchase."<<endl;
				}
			}
			}

}
}
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
void ticketSalesMenu(vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck)
{
    char c;

    cout<< setw(61)<< " _______________________________________________\n"
        << endl
        << setw(61)<< "|    How many tickets would you like to buy?    |\n"
        << setw(61)<< "|                                               |\n"
        << setw(61)<< "|  A. One Ticket(1)                             |\n"
        << setw(61)<< "|                                               |\n"
        << setw(61)<< "|  B. Block of Tickets(2+)                      |\n"
        << setw(61)<< "|                                               |\n"
        << setw(61)<< " _______________________________________________  "<< endl;
        cin.ignore();
		cin >> c;

switch(c)
    {
        case 'A':{
        	        	purchaceSingleSeat(unsold, sold, seatCheck);
			break;
		}
        case 'B':{ //call
        	 purchaceBlockSeat(unsold, sold, seatCheck);
                  cout<<endl;
                    break;
}
        default: //call
                 cout<<setw(47)<<endl<<"Invalid choice."<<endl<<endl<<endl;
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
				ticketSalesMenu(unsold, sold, seatCheck);
				break;

            case 'b':
			case 'B': //call
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