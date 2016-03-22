/*	Professor: Dr. Knox
	Class: COSC 1437 Spring 2016
	Assignment: Team Project 1: Movie Theater
	Author: Jacob Gibson, Chris Cavazos, and Celeste Avila
	Leader: Chris Cavazos
	Date: 3/22/2016 */
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
void spinner();
//Author: Chris
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
//Auth: Chris and Jacob
int main() {
	//Awesome logo display
	spinner();
	centerString(cout, "NOW WITH BASICLIB V0.2");
	
	//Declaring Variables
	bool **seatCheck=new bool *[COLUMNS];
	vector<Seat> unsoldSeats;
	vector<Seat> soldSeats;
	
	//Initializing Seat Array with appropriate prices
	initSeatCheck(seatCheck);
	for(int i=0; i < ROWS; i++){
		for(int j=0; j < COLUMNS; j++){
			Seat s;
			s.Number=i;
			s.Row=j;
			if(i>=0 && i<3){
				s.Price=HIGHPRICE;
			}
			else if( i>=4 &&i<7){
				s.Price=MEDIUMPRICE;
			}else if(i>=8 &&i<10){
				s.Price=LOWPRICE;
			}
			unsoldSeats.push_back(s);
		}
	}
	readInData(seatCheck, soldSeats, people); //Reading in data
	mainMenu(unsoldSeats,soldSeats,seatCheck); //Transferring control flow to main menu
	writeOutData(seatCheck, soldSeats); //Writing out reports and data at end of program. 4 files total
	return 0;
}
