//Author: Jacob
//Patron structure to hold ID, name, and number
struct Patron
{
    std::string ID; //Patron number from 1 to 160
    std::string Name; //Patron first and last name
    std::string PhoneNumber; //Done as string for formatting
};
//Author: Jacob
//Seat structure to hold location, price, status, and patron ID
struct Seat
{
	Patron p;
    int Row; //Row number 1 through 10
    int Number; //Seat number 1 through 16
    float Price; //Price of seat
    bool SoldStatus; //True = sold
    std::string SeatID = "MT"; //Default SeatID = "MT" for empty

    //Set SeatID equal to PatronID of person who purchased it
    void SetID(Patron& temp)
    {
    	p=temp;
        SeatID = p.ID;
    }
};
