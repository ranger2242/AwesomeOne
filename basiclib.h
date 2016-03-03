//
// Created by Chris on 2/23/2016.
//
//"Basic library of reusable code for C++ labs written by Chris Cavazos."
//basiclib ver 0.2!!!!!!!!!!!!!!!11
#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

#ifndef HEADER_BASICLIB_H
#define HEADER_BASICLIB_H
using namespace std;
#endif //HEADER_BASICLIB_H
#define _CRT_SECURE_NO_WARNINGS 

void sep(ostream &);

int width=80;
//Auth:Chris
void spinner(){
	 string arr[]={	                                                                                                                                                                                                                                                                    
             "    :''''''''''';+''''''''''':'''''''''''#+'''''''''''`",               
             "     :           @.           @           @.           @",               
             "      :           @.           @           @.           @",               
             "       .@@@     @@@@.       +@@@@           @.           @",               
             "           ,     @   .           @    @@@    @.           @",               
             "            ,     @   .           @           @.           @",               
             "             ,     @   .           @           @.           @",               
             "              ,     @   .           @           @.           @",               
             "               ,     @   .       +@@@@     '     @.  '    ;   @",               
             "                ,     @   .           @     @     @.  @    #   @",               
             "                 ,     @   .           @     @     @.  @    #   @",               
             "                  ,     @   .           @     @     @.  @    #   @",               
             "                   @@@@@@   ,@@@@@@@@@@@@@@@@@@@@@@@@,@@@@@@@@#@@@",               
             ":''''''''''#+''#'''@''':'''''''''++''''''''''':'''''''''#+''''''''''':'''''''''+",               
             ":          @.  @   #   @          @.          @          @.          @         @",               
             ":          @.  @   #   @          @.          @          @.          @         @",               
             ":          @.  @   #   @       @@@@.       @@@@          @.          @      @@@@",               
             ":    @@@   @.          @          @.          @    @     @.          @         @",               
             ":          @.          @          @.          @    @     @.          @         @",               
             ":          @.          @          @.          @    @     @.          @         @",               
             ":          @.          @          @.          @    @     @.          @         @",               
             ":     '    @.          @       @@@@#@@        @    '     @.  '   ;   @      @@@@",               
             ":     @    @.          @          @.          @          @.  @   #   @         @",               
             ":     @    @.          @          @.          @          @.  @   #   @         @",               
             ":     @    @.          @          @.          @          @.  @   #   @         @",               
             "@@@@@@@@@@@,@@@@@@@@@@@@@@@@@@@@@@,@@@@@@@@@@@@@@@@@@@@@@,@@@@@@@#@@@@@@@@@@@@@@"}; 
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
void sep(ostream &str){
    string s="";
    s.append(width,'-');
    str<<s<<endl;
}

void cls(){
	system("CLS");
}

//Author: Jacob
void pause()
{
	system("PAUSE");
	system("CLS");
}

string calcDate(){
    time_t current = time(0);
    string date=ctime(&current);
    tm *gmtm =gmtime(&current);
    date =asctime(gmtm);
    date=(string)date;
    date.erase(remove(date.begin(), date.end(), '\n'),date.end());
    return date;
}
void centerString(ostream& str, string s){
    int halfWid=width/2;
    int halfStr=s.length()/2;
    int offset=halfWid+halfStr;
    str<<setw(offset)<<right<<s<<endl;
}
void title(ostream& str, string t){
    sep(str);
    centerString(str,t);
    sep(str);
}
void studentHeader(ostream& str, string s){
    title(str, s);
    centerString(str,"Christopher Cavazos");
    centerString(str,"COSC 1437");
    centerString(str,calcDate());
    sep(str);
}
string allUpper(string s){
    locale lc;
    string capString="";
    for(int i=0; i<s.length();i++){
        char pos=toupper(s.at(i));
        capString+=pos;
    }
    return capString;
}
string filterStringNonApha(string s){
    string filterString="";
    for(int i=0; i<s.length();i++){
        char c=s.at(i);
        if(c>=65 && c<=65+26) {
            filterString+=s.at(i);
        }
    }
    return filterString;
}
