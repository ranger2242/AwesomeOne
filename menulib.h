#include <vector>
#include <iostream>
#include "Seat.h"
#include "basiclib.h"
using namespace std;
void ticketSalesMenu ();
void printMenuOptions();
void displaySeatingChart(ostream &,bool**);
void purchaceSingleSeat(vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck) ;

static vector<Patron> people;

//Constants for theater dimensions
const int COLUMNS = 16, ROWS = 10;
//Constants for theater seating prices
const float LOWPRICE = 25.00, MEDIUMPRICE = 35.00, HIGHPRICE = 50.00;


//Author: Celeste
bool numberIsGood(string PhoneNumber){
    bool isGood = true; 

    if (PhoneNumber.length() == 10) // checks is string array contains 10 characters
    {
        for (int i = 0; i < PhoneNumber.length(); i++)
        {
            if (!isdigit(PhoneNumber[i]))  // checks is every character is a numeric value
            {
                isGood = false;
            }
        }
    }

    return isGood;
}

//Auth:Chris
void generateReport(ostream & str, vector<Seat> sold){
	cls();
	title(str,"REVENUE REPORT");
	int total=0;
	for(int i=0; i<sold.size();i++){
		Seat s = sold.at(i);
		str<<"("<<s.Number<<","<<s.Row<<")"<<"\t\t"<<s.SeatID<<"\t\t"<<s.p.Name<<"\t\t"<<s.Price<<endl;
		total+=s.Price;
	}
	sep(str);
	str<<"TOTAL: $"<<total << endl << endl;
	sep(str);
	pause();
}

//Author: Chris and Jacob
Patron searchPatron(){
			cls();
			int id;
		title(cout, "ACCOUNT SEARCH");
		cout<<"Please enter your ID number:";
		cin>>id;
		int index;
		bool found=false;
		for(int i=0;i<people.size();i++){
			if(to_string(id)==people.at(i).ID){
				index=i;
				found=true;
			}
		}
		if(found){
			return people.at(index);
		}
		else{
			centerString(cout,"---RECORD NOT FOUND---");
		}
}
Patron createPatron(){
	//cls();
			Patron p;

	title(cout,"ACCOUNT INFO");
	cout<<"Do you have an existing account? (y/n):";
	char input;
	cin>>input;
	if(input=='y'){
		searchPatron();
	}else if(input =='n'){
			cls();
		title(cout,"ACCOUNT SETUP");
		cout<<"Please enter your first name, last name, and phone number below."<<endl;
		cout<<"(ex. Dingus McNugget 3613459876)";
		string full,first,last,number;
		cin.ignore();
		cin>>first>>last>>number;
		full=first+" "+last;
		p.Name=full;
		p.PhoneNumber=number;
		bool check=false;
		int id;
		while(!check){
			id=(rand()%160)+1;
			bool match = false;
			for(int i=0;i<people.size();i++){
				if(to_string(id)==people.at(i).ID){
					match=true;
				}
			}
			if(!match){
				check=true;
			}
		}
		p.ID= to_string(id);
		title(cout,"Your ID is:"+p.ID);
		sep(cout);
	}
	return p;
}
//Auth:Chris
void purchaceSingleSeat(vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck) {
	Patron p=createPatron();
	Seat temp;
	int index ,x,y;
	bool check=false;
	cout<<endl<<endl;
	title(cout,"PURCHASE SINGLE SEAT");
	cout<<"Please enter seat row and seat number separated by a space.\n(ex. \"2 5\")\n";
	cin.ignore();
	cin>>x>>y;

	cout<<endl;
	for(int i=0; i<unsold.size();i++){
		Seat s = unsold.at(i);
		if(s.Number==x-1 && s.Row==y-1){
			s.SetID(p);
				people.push_back(p);
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
	Patron p=createPatron();
	int x,x2,y,y2;
	cout<<endl<<endl;
	title(cout,"PURCHASE SEAT BLOCK");
	cout<<"Seats must be in either a column, row, or rectangle"<<endl;
	cout<<"Please enter seat row and seat number separated by a space.\n(ex. \"x1 y1 x2 y2\")\n";

	centerString(cout,"   _______________" );
	centerString(cout,"  |        (x2,y2)|" );
	centerString(cout,"  |               |" );
	centerString(cout,"  |               |" );
	centerString(cout,"  |               |" );
	centerString(cout,"  |               |" );
	centerString(cout,"  |               |" );
	centerString(cout,"  |(x1,y1)        |" );
	centerString(cout,"   ---------------" );

	cout<<"Enter Here:";
	cin.ignore();
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
					s.SetID(p);
						people.push_back(p);

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
					cout << unsold.size() << " seats remaining" << endl<<endl;
					//displaySeatingChart(cout, seatCheck);
				}else{
					cout<<"Seat is unavalable for purchase."<<endl;
				}
				//Sleep(16);
			}
			}

}
	
displaySeatingChart(cout,seatCheck);
}
//Auth:Chris and Jacob
void displaySeatingChart(ostream & str,bool** arr){
	//Heading to chart
	//cls();
	str << endl;
	centerString(str,"HUNTINGTON PLAYHOUSE");
	centerString(str,"SEATING CHART");
	str<<endl;
	centerString(str, "Rear\n");
	str << setw(21) << " " << "Seat                   1 1 1 1 1 1 1" << endl;
	str << setw(19) << " " << "Row   1 2 3 4 5 6 7 8  9 0 1 2 3 4 5 6" << endl;
	centerString(str, " Aisle");
	
	string temp;
	for(int i=ROWS - 1; i >= 0; i--){
		temp="";
		for(int j=0; j < COLUMNS; j++){
			char c='O';
			if(arr[i][j])c='X';
			temp.append(" ");
			temp+=c;
			if(j== (COLUMNS / 2) - 1){
				temp.append(" ");
			}
		}
		//Add line numbers to display
		//If line is 10, append a space so centerString works correctly
		if(i == 9)
			temp.append(" ");
			
		temp=to_string(i+1)+" "+temp;
		centerString(str,temp);
	}
	//Footing
	centerString(str, " Front");
}
//second menu prompts user how many tickets they want to buy
void ticketSalesMenu(vector<Seat> & unsold, vector<Seat>&sold, bool**seatCheck)
{
    char c;

    cout<< setw(64)<< " _______________________________________________\n"
        << endl
        << setw(64)<< "|    How many tickets would you like to buy?    |\n"
        << setw(64)<< "|                                               |\n"
        << setw(64)<< "|  A. One Ticket(1)                             |\n"
        << setw(64)<< "|                                               |\n"
        << setw(64)<< "|  B. Block of Tickets(2+)                      |\n"
        << setw(64)<< "|                                               |\n"
        << setw(64)<< " _______________________________________________  "<<endl;
        cout << setw(40)<< "Enter menu choice:";
        cin.ignore();
		cin >> c;

switch(c)
    {
        case 'A':
        case 'a':
        	        	purchaceSingleSeat(unsold, sold, seatCheck);//call
			break;
		
        case 'B': 
        case 'b':
        	 purchaceBlockSeat(unsold, sold, seatCheck);//call
                  cout<<endl;
                    break;
	
        default: 
                 cout<<setw(47)<<endl<<"Invalid choice."<<endl<<endl<<endl;
    }
}
// main menu
void printMenuOptions(){
	cout<< setw(61)<< " ______________________________________ \n"
	<< endl
	<< setw(61)<< "|              TICKET MENU             |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| A. Display Seating Chart             |\n"
    << setw(61)<< "|                                      |\n"
	<< setw(61)<< "| B. Ticket Sales                      |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| C. Patron Information Search         |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| D. Current Revenue                   |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| E. Program Information               |\n"
	<< setw(61)<< "|                                      |\n"
	<< setw(61)<< "| #. Exit                              |\n"
	<< setw(61)<< " ______________________________________  "<<endl;
	cout << setw(40)<< "Enter menu choice:";
}

//Author: Jacob
//Gives Program information and Technical Support while playing Mario theme music
//MMusic Source: http://cncpp.divilabs.com/2013/12/c-code-for-mario-theme-intro-song.html
void programCredits()
{
	cls();
		Beep (330,100);Sleep(100);
    	Beep (330,100);Sleep(300);
		Beep (330,100);Sleep(300);
	sep(cout);	
		Beep (262,100);Sleep(100);
    	Beep (330,100);Sleep(300);
    	Beep (392,100);Sleep(700);
    centerString(cout, "Movie Theater Program by Team Awesome");
    	Beep (196,100);Sleep(700);
        Beep (196,100);Sleep(125);
        Beep (262,100);Sleep(125);
    sep(cout);    
    	Beep (330,100);Sleep(125);
        Beep (392,100);Sleep(125);
        Beep (523,100);Sleep(125);
    centerString(cout, "Lead Programmer: Chris \'Code Monkey\' Cavazos");    
    	Beep (660,100);Sleep(125);
        Beep (784,100);Sleep(575);
        Beep (660,100);Sleep(575);
    centerString(cout, "Programmers: Jacob \'The Error\' Gibson");  
		Beep (207,100);Sleep(125);
        Beep (262,100);Sleep(125);
        Beep (311,100);Sleep(125);
    centerString(cout,"              Celeste \'Bug Buster\' Avila");    
		Beep (415,100);Sleep(125);
        Beep (523,100);Sleep(125);
        Beep (622,100);Sleep(125);
    sep(cout);    
		Beep (830,100);Sleep(575);
        Beep (622,100);Sleep(575);
        Beep (233,100);Sleep(125);
    centerString(cout,"   Tech Support\n");  
		Beep (294,100);Sleep(125);
        Beep (349,100);Sleep(125);
        Beep (466,100);Sleep(125);
    centerString(cout,"E-mail:  NotAFakeEmail@gmail.com\n");    
		Beep (587,100);Sleep(125);
        Beep (698,100);Sleep(125);
        Beep (932,100);Sleep(575);
	centerString(cout, "Phone Number:  (555)-968-7223\n");
        Beep (932,100);Sleep(125);
        Beep (932,100);Sleep(125);
        Beep (932,100);Sleep(125);
        Beep (1046,675);
}

void mainMenu(vector<Seat> &unsold, vector<Seat> &sold, bool **seatCheck){
	char choice;
	printMenuOptions();
	
	cin >> choice;
	
	while(choice!='#'){
		switch(choice)
		{
		    case 'a':
			case 'A':
				displaySeatingChart(cout, seatCheck);
				break;

            case 'b':
			case 'B':
			    ticketSalesMenu(unsold, sold, seatCheck);
				break;

            case 'c':
			case 'C': 
			    searchPatron();
				cout<<endl;
				break;

            case 'd':
			case 'D': 
				generateReport(cout,sold);
				cout<<endl;
				break;

            case 'e':
            case 'E':
                programCredits();
                pause();
                break;

			case '#':
				cout<<"EXIT"<<endl;
				break;
			default:
				cout<<setw(47)<<endl<<"Invalid choice. Press Enter to try again."<<endl<<endl<<endl;
				pause();
		}
		printMenuOptions();
		cin>>choice;
	}



}
