//Author: Jacob Gibson

//Header for all file operations of movie ticket program
#include <iostream>
#include <fstream>

#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED
using namespace std;
#endif // FILEIO_H_INCLUDED

//Author: Jacob
void readInData(bool **seatCheck)
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

        //If file fails to open, return to menu
        if(SeatingFile.fail())
        {
            cout << "The seating chart file failed to open." << endl;
            pause();
            return;
        }

        string tempStr;
        int tempInt;

        //Read contents of seating data file into bool array
        for (int i = 0; i < COLUMNS; i++)
        {
            for(int j = 0; j < ROWS; j++)
            {
                getline(SeatingFile, tempStr, ',');
                tempInt = atoi(tempStr.c_str());
                seatCheck[j][i] = static_cast<bool>(tempInt);
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
        for (int i = 0; i < COLUMNS; i++)
        {
            for(int j = 0; j < ROWS; j++)
            {
                seatCheck[j][i] = false;
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
void writeOutData(bool **seatCheck, vector<Seat> soldSeats)
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
    for (int i = 0; i < COLUMNS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            SeatingFile << seatCheck[j][i] << ",";
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

    //generateReport(SeatingReport, soldSeats);

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

    generateReport(SalesReport, soldSeats);

    SalesReport.close();
}
