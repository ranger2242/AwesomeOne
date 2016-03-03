/*hhjhsyt
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
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <windows.h>
#include <string>
#include "menulib.h"
#include "fileIO.h"

using namespace std;
void displayLogo();
void spinner();

//Included here so it can use the above constants

//Author: Jacob
//Displays awesome logo for the team at start of program
void displayLogo()
{
        sep(cout);
        Sleep(750);
        cout << "" << endl;
        Sleep(750);
        cout << "   |__   __|                       /\\                                          " << endl;
        Sleep(750);
        cout << "      | | ___  __ _ _ __ ___      /  \\__      _____  ___  ___  _ __ ___   ___" << endl;
        Sleep(750);
        cout << "      | |/ _ \\/ _` | '_ ` _ \\    / /\\ \\ \\ /\\ / / _ \\/ __|/ _ \\| '_ ` _ \\ / _ \\ " << endl;
        Sleep(750);
        cout << "      | |  __/ (_| | | | | | |  / ____ \\ V  V /  __/\\__ \\ (_) | | | | | |  __/" << endl;
        Sleep(750);
        cout << "      |_|\\___|\\__,_|_| |_| |_| /_/    \\_\\_/\\_/ \\___||___/\\___/|_| |_| |_|\\___|\n\n" << endl;
        Sleep(750);
        sep(cout);
        
}
void spinner(){
	 string arr[]={	                                                                                                                                                                                                                                                                    
             ":''''''''''';+''''''''''':'''''''''''#+'''''''''''`                                                       ",                
             ":           @.           @           @.           @",               
             ":           @.           @           @.           @",               
             ".@@@     @@@@.       +@@@@           @.           @",               
             "   ,     @   .           @    @@@    @.           @",               
             "   ,     @   .           @           @.           @",               
             "   ,     @   .           @           @.           @",               
             "   ,     @   .           @           @.           @",               
             "   ,     @   .       +@@@@     '     @.  '    ;   @",               
             "   ,     @   .           @     @     @.  @    #   @",               
             "   ,     @   .           @     @     @.  @    #   @",               
             "   ,     @   .           @     @     @.  @    #   @",               
             "    @@@@@@   ,@@@@@@@@@@@@@@@@@@@@@@@@,@@@@@@@@#@@@",               
             "                  :'''''''''''#+''#''''@''':'''''''''''++''''''''''':'''''''''''#+''''''''''':'''''''''''+",               
             "                  :           @.  @    #   @           @.           @           @.           @           @",               
             "                  :           @.  @    #   @           @.           @           @.           @           @",               
             "                  :           @.  @    #   @        @@@@.        @@@@           @.           @        @@@@",               
             "                  :    @@@    @.           @           @.           @     @     @.           @           @",               
             "                  :           @.           @           @.           @     @     @.           @           @",               
             "                  :           @.           @           @.           @     @     @.           @           @",               
             "                  :           @.           @           @.           @     @     @.           @           @",               
             "                  :     '     @.           @        @@@@#@@         @     '     @.  '    ;   @        @@@@",               
             "                  :     @     @.           @           @.           @           @.  @    #   @           @",               
             "                  :     @     @.           @           @.           @           @.  @    #   @           @",               
             "                  :     @     @.           @           @.           @           @.  @    #   @           @",               
             "                   @@@@@@@@@@@@,@@@@@@@@@@@@@@@@@@@@@@@@,@@@@@@@@@@@@@@@@@@@@@@@@,@@@@@@@@#@@@@@@@@@@@@@@@"}; 
	int rates[27];
	int counts[27];
	for(int i=0; i<27;i++){
		rates[i]=rand()%5;
		counts[i]=0;
	}
		
	
	string temp="";
		int c=0;
		for(int i=0;i<27;i++){
			for(int j=0;j<arr[i].length();j++){
			
			cout<<arr[i].at(j);
			Sleep(1);
		}
		cout<<endl;
	}
	
}

int main() {
	spinner();
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


