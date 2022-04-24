#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

static int NUMBER_OF_TICKETS = 0;
struct schedule
{
	string time;
	string movie;
	string genre;
	int roomnumber;
	string day;
	string month;
};

struct roominfomation
{
	int number_of_filled_seat;
	int max_occupants;

	string time;
	string day;
	string month;
	int roomnumber;
	char seat[50];
	char seatrow[5] = { 'A', 'B', 'C', 'D', 'E' };

	roominfomation()
	{
		for (int i = 0; i < 50; i++)
			seat[i] = char(1);
		max_occupants = 50;
		number_of_filled_seat = 0;
	}
	void roomprint()
	{
		cout << "There are " << 50 - number_of_filled_seat << " seats available in the room " << endl;
		cout << "Available: " << char(2) << endl;
		cout << "    1 2 3 4 5 6 7 8 9 10" << endl;
		for (int i = 0; i < 50;i++)
		{

			if (i % 10 == 0)
				cout << seatrow[i / 10] << "   ";

			cout << seat[i] << " ";

			if ((i + 1) % 10 == 0)
				cout << '\n';
		}
	}
	int convertSeatToIndex(char a, int b)
	{
		int index;
		if (a == 'A' || a == 'a')
			index = b - 1;
		else if (a == 'B' || a == 'b')
			index = 10 + b - 1;
		else if (a == 'C' || a == 'c')
			index = 20 + b - 1;
		else if (a == 'D' || a == 'd')
			index = 30 + b - 1;
		else if (a == 'E' || a == 'e')
			index = 40 + b - 1;

		return index;
	}



	void chooseSeat()
	{
		if (number_of_filled_seat == 50)
			cout << "No more seat avaiable. Please choose another day." << endl;
		else
		{
			roomprint();
			bool check = false;
			int counter = 0;
			int numberofticket;
			char row;
			int number;
			cout << "How many tickets you want? " << endl;
			cin >> numberofticket;
			NUMBER_OF_TICKETS += numberofticket;
			while (!check)
			{
				if (1 <= numberofticket && numberofticket<=(50 - number_of_filled_seat))
				{
					check = true;
					cout << "Enter the Row and Seat Number you like: " << endl;
					while (counter < numberofticket)
					{
						cout << "Row: ";
						bool check1 = false;
						cin >> row;
						while (!check1)
						{
							if (row == 'A' || row == 'a' || row == 'B' || row == 'b' || row == 'c' || row == 'C' || row == 'D' || row == 'd' || row == 'E' || row == 'e')
								check1 = true;
							else
							{
								cout << "Enter row again: ";
								cin >> row;
							}
						}
						check1 = false;
						cout << "Seat Number: ";
						cin >> number;
						while (!check1)
						{
							if (number == 1 || number == 2 || number == 3 || number == 4 || number == 5 || number == 6 || number == 7 || number == 8 || number == 9 || number == 10)
								check1 = true;
							else
							{
								cout << "Enter seat number again: ";
								cin >> number;
							}
						}
						
						if (0 <= convertSeatToIndex(row, number) && convertSeatToIndex(row, number) <= 49)
						{
							number_of_filled_seat += 1;
							if (seat[convertSeatToIndex(row, number)] == char(1))
								seat[convertSeatToIndex(row, number)] = 'X';
							else
							{
								cout << "Unavailable Seat" << endl;
								number_of_filled_seat -= 1;
								counter--;
							}
							counter++;
							roomprint();
						}

					}
				}
				else
				{
					cout << "Enter valid number of tickets. Enter again: ";
					cin >> numberofticket;
				}
			}

		}
	}

};

struct moviebooking
{

	schedule s[84];
	roominfomation roominfo[84];
	string moviename[6] = { "" };
	int movieindex[6] = { 0 };

	void mostpopular()
	{
		int index = 0;
		int max = movieindex[0];
		for (int i = 0; i < 6;i++)
		{
			if (movieindex[i] > max)
			{
				index = i;
				max = movieindex[i];
			}
		}
		if(max!=0)
		cout << moviename[index] << " is the most popular booking movie in our website." << endl;
	}
	void loadData()
	{
		int i = 0;
		int j = 0;
		ifstream infile;
		string a, b;
		infile.open("input.txt");
		while (!infile.eof())
		{
			infile >> s[i].movie;
			infile >> s[i].genre;
			infile >> s[i].time;
			infile >> s[i].roomnumber;
			infile >> s[i].month;
			infile >> s[i].day;
			i++;
		}
		infile.close();
		infile.open("input.txt");
		while (!infile.eof())
		{
			infile >> a;
			infile >> b;
			infile >> roominfo[j].time;
			infile >> roominfo[j].roomnumber;
			infile >> roominfo[j].month;
			infile >> roominfo[j].day;
			j++;
		}

		

	}

	bool isThere(string name)
	{
		for (int i = 0;i < 6;i++)
			if (moviename[i] == name)
				return true;
		return false;
	}

	void MovieCollection()
	{
		int j = 0;
		for(int i = 0; i<84; i++)
			if (!isThere(s[i].movie))
			{
				moviename[j] = s[i].movie;
				j++;
			}
	}

	void printMovieCollection()
	{
		MovieCollection();
		for (int i = 0; i < 6;i++)
			cout << i + 1 << ". " << moviename[i] << endl;
	}
	

	void printMovieTimeByName()
	{
		int j = 0;
		bool check = false;
		string name;
		cout << "Below is the movies we offer: " << endl;
		printMovieCollection();
		cout << "Enter the name of movie you want to see: ";
		cin >> name;

		while (!check)
		{
			if (isThere(name))
			{
				check = true;
				for (int i = 0; i < 84;i++)
					if (s[i].movie == name)
					{
						cout << right << setw(3) << j + 1 << "." << right << setw(15) << s[i].time << " " << setw(9) << s[i].month << "/" <<setw(2)<< s[i].day << right << setw(15) << " Room: " << s[i].roomnumber << endl;
						j++;
					}
			}
			else
			{
				cout << "You entered wrong movie name. Enter again: " << endl;
				cin >> name;
			}
		}
	}
	bool checkroominfo(string month, string day, string time)
	{
		for (int i = 0; i < 84;i++)
			if (roominfo[i].month == month && roominfo[i].day == day && roominfo[i].time == time)
				return true;
		return false;
	}
	
	void welcome()
	{
		int transaction = 0;
		int score;
		double rating = 0;
		int m;
		string name;
		char key;
		char key2 = 'Y';
		string month;
		string day;
		string time;
		int monthnumber;
		int preferroom; 
		while (transaction < 10000 && (key2 == 'Y' || key2 == 'y'))
		{

			cout << "Welcome to our E-Ordering Movie Ticket." << endl;
			mostpopular();
			cout << "We have been selling " << NUMBER_OF_TICKETS << " tickets" << endl;
			cout << "You are the " << transaction << " customer today." << endl;
			cout << "Do you know the movie you want to see yet? (Y/N) ";
			cin >> key;
			while (key != 'Y' && key != 'y' && key != 'n' && key != 'N')
			{
				cout << "Enter Y/N again: ";
				cin >> key;
			}

			if (key == 'Y' || key == 'y')
			{
				bool check = false;
				printMovieTimeByName();
				cout << "What date and time you want to see the movie: ";
				cout << endl;
				cout << "Month: ";
				cin >> month;
				cout << "Day: ";
				cin >> day;
				cout << "Time: ";
				cin >> time;
				while (!check)
				{
					if (checkroominfo(month, day, time))
					{
						check = true;
						for (int i = 0; i < 84;i++)
							if (roominfo[i].month == month && roominfo[i].day == day && roominfo[i].time == time)
								m = i;
						for (int i = 0;i < 6;i++)
							if (moviename[i] == s[m].movie)
								movieindex[i]++;
					}
					else
					{
						cout << "No information. Type again: " << endl;
						cout << "Month: ";
						cin >> month;
						cout << "Day: ";
						cin >> day;
						cout << "Time: ";
						cin >> time;
					}
				}
				roominfo[m].chooseSeat();
				
			}
			else if (key == 'N' || key == 'n')
			{
				bool check = false;
				int j = 0;
				cout << "What month you want to book the movie ticket: ";
				cin >> month;
				while (!check)
				{
					if (month != "4" && month != "5")
					{
						cout << "We have only movies schedule in month 4 and 5 only. Please type the month you want to book the movie ticket: ";
						cin >> month;
					}
					else
						check = true;
				}

				if (month == "4")
					monthnumber = 4;
				if (month == "5")
					monthnumber = 5;
				calendar(2022, monthnumber);

				cout << "What day you want to come: ";
				cin >> day;
				cout << "What time you want to see the movie: ";
				cin >> time;
				check = false;
				while (!check)
				{
					if (checkroominfo(month, day, time))
					{
						check = true;
						for (int i = 0; i < 84;i++)
							if (roominfo[i].month == month && roominfo[i].day == day && roominfo[i].time == time)
								m = i;
						for (int i = 0;i < 6;i++)
							if (moviename[i] == s[m].movie)
								movieindex[i]++;
					}
					else
					{
						j = 0;
						cout << "No information. Type again: " << endl;
						cout << "Check schedule below: " << endl;
						cout << endl;
						for(int i = 0; i<84; i++)
							if (roominfo[i].month == month && roominfo[i].day == day)
							{
								cout << setw(3) << j + 1 << "." << right << setw(13) << s[i].movie << setw(15) << s[i].genre << setw(15) << s[i].time << " " << setw(9) << s[i].month << "/" << setw(2) << s[i].day << right << setw(15) << " Room: " << s[i].roomnumber << endl;
								j++;
							}

						cout << "Day: ";
						cin >> day;
						cout << "Time: ";
						cin >> time;
					}
				}
				roominfo[m].chooseSeat();


			}

			cout << "Can you rate our transaction today from 1 to 10? ";
			bool check = false;
			cin >> score;

			while (!check)
			{
				if (score >= 1 && score <= 10)
					check = true;
				else
				{
					cout << "Enter your rating again: ";
					cin >> score;
				}
			}

			
			
			rating += score;
			transaction++;
			cout << "Next Transaction: Y/N" << endl;
			cin >> key2;
		}

		cout << "There are " << transaction << " transactions today." << endl;
		cout << "The average of customer satisfication with the platform is: " << rating / transaction << endl;
		cout << "Finish Running" << endl;
	}

	

	int isLeapYear(int y) /* True if leap year */
	{
		return(y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
	}

	int leapYears(int y) /* The number of leap year */
	{
		return y / 4 - y / 100 + y / 400;
	}

	int todayOf(int y, int m, int d) /* The number of days since the beginning of the year */
	{
		static int DayOfMonth[] =
		{ -1/*dummy*/,0,31,59,90,120,151,181,212,243,273,304,334 };

		return DayOfMonth[m] + d + ((m > 2 && isLeapYear(y)) ? 1 : 0);
	}

	long days(int y, int m, int d) /* Total number of days */
	{
		int lastYear;

		lastYear = y - 1;

		return 365L * lastYear + leapYears(lastYear) + todayOf(y, m, d);
	}

	void calendar(int y, int m) /* display calendar at m y */
	{
		const char* NameOfMonth[] = { NULL/*dummp*/,
			"January", "February", "March", "April", "May", "June",
			"July", "August", "September", "October", "November", "December"
		};
		char Week[] = "Su Mo Tu We Th Fr Sa";
		int DayOfMonth[] =
		{ -1/*dummy*/,31,28,31,30,31,30,31,31,30,31,30,31 };
		int weekOfTopDay;
		int i, day;

		weekOfTopDay = days(y, m, 1) % 7;
		if (isLeapYear(y))
			DayOfMonth[2] = 29;
		printf("\n     %s %d\n%s\n", NameOfMonth[m], y, Week);

		for (i = 0;i < weekOfTopDay;i++)
			printf("   ");
		for (i = weekOfTopDay, day = 1;day <= DayOfMonth[m];i++, day++) {
			printf("%2d ", day);
			if (i % 7 == 6)
				printf("\n");
		}
		printf("\n");
	}

};
