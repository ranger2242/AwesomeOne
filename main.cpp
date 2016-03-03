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

void initSeatCheck(bool** arr){
		for(int i=0; i < ROWS; i++){
		arr[i]=new bool[COLUMNS];
	}
	for(int i=0; i < ROWS; i++){
		for(int j=0; j < COLUMNS; j++){
		arr[i][j]=false;
		}
	}
}
int main() {
	spinner();
	centerString(cout, "NOW WITH BASICLIB V0.2");
	bool **seatCheck=new bool *[COLUMNS];
	vector<Seat> unsoldSeats;
	vector<Seat> soldSeats;

	initSeatCheck(seatCheck);
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


