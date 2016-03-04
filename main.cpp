/*
Professor: Dr. Knox
Class: COSC 1437 Spring 2016
Assignment: Team Project 1: Movie Theater
Author: Jacob Gibson, Chris Cavazos, and Celeste Avila
Leader: Chris Cavazos
Date: 3/11/2016
*/

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

//Included here so it can use the above constants

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
			if(i>=0 && i<4){
				s.Price=HIGHPRICE;
			}
			else if( i>=5 &&i<8){
				s.Price=MEDIUMPRICE;
			}else if(i>=8 &&i<10){
				s.Price=LOWPRICE;
			}
			unsoldSeats.push_back(s);
		}
	}
	cout<<"$";

	mainMenu(unsoldSeats,soldSeats,seatCheck);
	
	//Jacob: Plays classic Mario crescendo theme
	//Source: http://cncpp.divilabs.com/2013/12/c-code-for-mario-theme-intro-song.html
	
        Beep (330,100);Sleep(100);
        Beep (330,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (330,100);Sleep(300);
        Beep (392,100);Sleep(700);
        Beep (196,100);Sleep(700);
        Beep (196,100);Sleep(125);
        Beep (262,100);Sleep(125);
        Beep (330,100);Sleep(125);
        Beep (392,100);Sleep(125);
        Beep (523,100);Sleep(125);
        Beep (660,100);Sleep(125);
        Beep (784,100);Sleep(575);
        Beep (660,100);Sleep(575);
        Beep (207,100);Sleep(125);
        Beep (262,100);Sleep(125);
        Beep (311,100);Sleep(125);
        Beep (415,100);Sleep(125);
        Beep (523,100);Sleep(125);
        Beep (622,100);Sleep(125);
        Beep (830,100);Sleep(575);
        Beep (622,100);Sleep(575);
        Beep (233,100);Sleep(125);
        Beep (294,100);Sleep(125);
        Beep (349,100);Sleep(125);
        Beep (466,100);Sleep(125);
        Beep (587,100);Sleep(125);
        Beep (698,100);Sleep(125);
        Beep (932,100);Sleep(575);
        Beep (932,100);Sleep(125);
        Beep (932,100);Sleep(125);
        Beep (932,100);Sleep(125);
        Beep (1046,675);
        

	return 0;
}


