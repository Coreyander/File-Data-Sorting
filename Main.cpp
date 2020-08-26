
#include <iostream>
#include <iomanip>
#include<fstream>
#include<string>
#include<vector>
#include <sstream>
using namespace std;

void readCSV(const char*, vector<unsigned int>&, vector<string>&, vector<string>&, vector<unsigned int>&, vector<unsigned int>&, vector<double>&);
void mostExpensiveSet(vector<unsigned int>&, vector<string>&, vector<string>&, vector<unsigned int>&, vector<unsigned int>&, vector<double>&);
void largestPieceCount(vector<unsigned int>&, vector<string>&, vector<string>&, vector<unsigned int>&, vector<unsigned int>&, vector<double>&);
void searchSetName(vector<unsigned int>&, vector<string>&, vector<double>&);
void searchTheme(vector<unsigned int>&, vector<string>&, vector<string>&, vector<double>&);
void partCount(vector<unsigned int>&, vector<unsigned int>&);
void priceInfo(vector<unsigned int>&, vector<string>&, vector<string>&, vector<unsigned int>&, vector<unsigned int>&, vector<double>&);
void minifigureInfo(vector<unsigned int>&, vector<string>&, vector<string>&, vector<unsigned int>&, vector<unsigned int>&, vector<double>&);
void buyEverything(vector<unsigned int>&, vector<unsigned int>&, vector<unsigned int>&, vector<double>&);

int main()
{
	vector<unsigned int> number;
	vector<string> theme;
	vector<string> name;
	vector<unsigned int> minifigs;
	vector<unsigned int> pieces;
	vector<double> price;
	string line = "";
	stringstream s(line);

	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	ifstream fileIn;
	if (option == 1) {
		fileIn.open("lego1.csv");
		readCSV("lego1.csv", number, theme, name, minifigs, pieces, price);
	}
	else if (option == 2) {
		fileIn.open("lego2.csv");
		readCSV("lego2.csv", number, theme, name, minifigs, pieces, price);
	}
	else if (option == 3) {
		fileIn.open("lego3.csv");
		readCSV("lego3.csv", number, theme, name, minifigs, pieces, price);
	}
	else if (option == 4) {
		fileIn.open("lego1.csv");
		readCSV("lego1.csv", number, theme, name, minifigs, pieces, price);
		fileIn.close();
		fileIn.open("lego2.csv");
		readCSV("lego2.csv", number, theme, name, minifigs, pieces, price);
		fileIn.close();
		fileIn.open("lego3.csv");
		readCSV("lego3.csv", number, theme, name, minifigs, pieces, price);
		fileIn.close();
	}


	if (!fileIn) {
		cerr << "Unable to open file datafile.txt";
		exit(1);
	}


	/*======= Load data from file(s) =======*/


	cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;

	int choice;
	cin >> choice;
	cin.get();  // Clear newline character for any later input

	/*======= Print out how many sets were loaded =======*/
	/*======= Based on the choice, execute the appropriate task and show the results =======*/
	if (choice == 0)
		return 0;
	if (choice == 1)
		mostExpensiveSet(number, theme, name, minifigs, pieces, price);
	if (choice == 2)
		largestPieceCount(number, theme, name, minifigs, pieces, price);
	if (choice == 3)
		searchSetName(number, name, price);
	if (choice == 4)
		searchTheme(number, theme, name, price);
	if (choice == 5)
		partCount(number, pieces);
	if (choice == 6)
		priceInfo(number, theme, name, minifigs, pieces, price);
	if (choice == 7)
		minifigureInfo(number, theme, name, minifigs, pieces, price);
	if (choice == 8)
		buyEverything(number, minifigs, pieces, price);

	return 0;
}
void readCSV(const char* filePath, vector<unsigned int>& number, vector<string>& theme, vector<string>& name, vector<unsigned int>& minifigs, vector<unsigned int>& pieces, vector<double>& price) {

	char delim = ',';
	ifstream file(filePath);

	if (file.is_open()) {

		string line;

		getline(file, line);

		while (!file.eof()) {
			getline(file, line);
			istringstream stream(line);

			string first, second, third, fourth, fifth, sixth;
			getline(stream, first, delim);
			number.push_back(stoi(first));

			getline(stream, second, delim);
			theme.push_back(second);

			getline(stream, third, delim);
			name.push_back(third);

			getline(stream, fourth, delim);
			minifigs.push_back(stoi(fourth));

			getline(stream, fifth, delim);
			pieces.push_back(stoi(fifth));

			getline(stream, sixth, delim);
			price.push_back(stod(sixth));
		}
	}
}
void mostExpensiveSet(vector<unsigned int>& number, vector<string>& theme, vector<string>& name, vector<unsigned int>& minifigs, vector<unsigned int>& pieces, vector<double>& price) {
	int superPricySet = 0;
	double superPricyPrice = 0;
	for (unsigned int i = 0; i < price.size(); ++i) {
		if (price.at(i) > superPricyPrice) {
			superPricyPrice = price.at(i);
			superPricySet = i;
		}
	}
	cout << "\nTotal number of sets: \n" << price.size() << endl <<
		"The most expensive set is: " << endl <<
		"Name: " << name.at(superPricySet) << endl <<
		"Number: " << number.at(superPricySet) << endl <<
		"Theme: " << theme.at(superPricySet) << endl <<
		"Price: $" << price.at(superPricySet) << endl <<
		"Minifigures: " << minifigs.at(superPricySet) << endl <<
		"Piece count: " << pieces.at(superPricySet) << endl;
}
void largestPieceCount(vector<unsigned int>& number, vector<string>& theme, vector<string>& name, vector<unsigned int>& minifigs, vector<unsigned int>& pieces, vector<double>& price) {
	unsigned int mostPieces = 0;
	int p = 0;
	for (unsigned int i = 0; i < pieces.size(); ++i) {
		if (pieces.at(i) > mostPieces) {
			mostPieces = pieces.at(i);
			p = i;
		}
	}
	cout << "\nTotal number of sets: \n" << price.size() << endl <<
		"The set with the highest parts count: " << endl <<
		"Name: " << name.at(p) << endl <<
		"Number: " << number.at(p) << endl <<
		"Theme: " << theme.at(p) << endl <<
		"Price: $" << price.at(p) << endl <<
		"Minifigures: " << minifigs.at(p) << endl <<
		"Piece count: " << pieces.at(p) << endl;
}
void searchSetName(vector<unsigned int>& number, vector<string>& name, vector<double>& price) {
	string search = "", lookFor;
	vector<int> copyLocations;
	bool found = false;
	getline(cin, lookFor);
	for (unsigned int i = 0; i < number.size(); ++i) {

		if (name.at(i).find(lookFor) != string::npos) {
			copyLocations.push_back(i);
			found = true;
		}
	}

	if (!found) {
		cout << "\nTotal number of sets: " << number.size() << endl <<
			"No sets found matching that search term" << endl;
	}
	else if (found) {
		cout << "\nTotal number of sets: " << number.size() << endl << "Sets matching \"" << lookFor << "\":" << endl;
		for (unsigned int i = 0; i < copyLocations.size(); ++i)
			cout << number.at(copyLocations.at(i)) << " " << name.at(copyLocations.at(i)) << " $" << price.at(copyLocations.at(i)) << endl;
	}
}
void searchTheme(vector<unsigned int>& number, vector<string>& theme, vector<string>& name, vector<double>& price) {
	string search = "", lookFor;
	vector<int> copyLocations;
	bool found = false;
	getline(cin, lookFor);
	for (unsigned int i = 0; i < number.size(); ++i) {

		if (theme.at(i).find(lookFor) != string::npos) {
			copyLocations.push_back(i);
			found = true;
		}
	}

	if (!found) {
		cout << "\nTotal number of sets: " << number.size() << endl <<
			"No themes found matching that search term" << endl;
	}
	else if (found) {
		cout << "\nTotal number of sets: " << number.size() << "Sets matching \"" << lookFor << "\":" << endl;
		for (unsigned int i = 0; i < copyLocations.size(); ++i)
			cout << number.at(copyLocations.at(i)) << " " << name.at(copyLocations.at(i)) << " $" << price.at(copyLocations.at(i)) << endl;
	}


}
void partCount(vector<unsigned int>& number, vector<unsigned int>& pieces) {
	int total = 0;
	for (unsigned int i = 0; i < number.size(); ++i)
		total = total + pieces.at(i);
	cout << "\nTotal number of sets: " << number.size() << "Average part count for " << number.size() << " sets: " << total / number.size() << endl;
}
void priceInfo(vector<unsigned int>& number, vector<string>& theme, vector<string>& name, vector<unsigned int>& minifigs, vector<unsigned int>& pieces, vector<double>& price) {
	double total = 0;
	double maxPrice = 0, maxCeiling = 0;
	int high = 0, low = 0;
	for (unsigned int i = 0; i < number.size(); ++i) {
		if (price.at(i) > maxPrice) {
			maxPrice = price.at(i);
			high = i;
		}
	}
	maxCeiling = maxPrice;
	for ( unsigned int i = 0; i < number.size(); ++i) {
		if (price.at(i) < maxCeiling) {
			maxCeiling = price.at(i);
			low = i;
		}
	}

	for (unsigned int i = 0; i < number.size(); ++i)
		total = total + price.at(i);
	cout << "\nTotal number of sets: " << number.size() << "\nAverage price for " << number.size() << " sets: $" << total / number.size() << endl;
	cout << "\nLeast expensive set: " << endl <<
		"Name: " << name.at(low) << endl <<
		"Number: " << number.at(low) << endl <<
		"Theme: " << theme.at(low) << endl <<
		"Price: $" << price.at(low) << endl <<
		"Minifigures: " << minifigs.at(low) << endl <<
		"Piece count: " << pieces.at(low) << endl;
	cout << "\nMost expensive set: " << endl <<
		"Name: " << name.at(high) << endl <<
		"Number: " << number.at(high) << endl <<
		"Theme: " << theme.at(high) << endl <<
		"Price: $" << price.at(high) << endl <<
		"Minifigures: " << minifigs.at(high) << endl <<
		"Piece count: " << pieces.at(high) << endl;
}
void minifigureInfo(vector<unsigned int>& number, vector<string>& theme, vector<string>& name, vector<unsigned int>& minifigs, vector<unsigned int>& pieces, vector<double>& price) {
	int total = 0;
	unsigned int mostminis = 0;
	int m = 0;
	for (unsigned int i = 0; i < number.size(); ++i) {
		total = total + minifigs.at(i);
	}

	for (unsigned int i = 0; i < pieces.size(); ++i) {
		if (minifigs.at(i) > mostminis) {
			mostminis = minifigs.at(i);
			m = i;
		}
	}
	cout << "\nTotal number of sets: " << number.size() << "\nAverage number of minifigures: " << total / number.size() << endl <<
		"Set with the most minifigures: " << endl <<
		"Name: " << name.at(m) << endl <<
		"Number: " << number.at(m) << endl <<
		"Theme: " << theme.at(m) << endl <<
		"Price: $" << price.at(m) << endl <<
		"Minifigures: " << minifigs.at(m) << endl <<
		"Piece count: " << pieces.at(m) << endl;
}
void buyEverything(vector<unsigned int>& number, vector<unsigned int>& minifigs, vector<unsigned int>& pieces, vector<double>& price) {
	double priceTotal = 0;
	int pieceTotal = 0;
	int miniTotal = 0;

	for (unsigned int i = 0; i < number.size(); ++i) {
		priceTotal = priceTotal + price.at(i);
		pieceTotal = pieceTotal + pieces.at(i);
		miniTotal = miniTotal + minifigs.at(i);
	}
	cout << "\nTotal number of sets: " << number.size() << endl <<
		"If you bought one of everything... " << endl << "\nIt would cost : $" << priceTotal << endl <<
		"You would have " << pieceTotal << " pieces in your collection" << endl <<
		"You would have an army of " << miniTotal << " minifigures!" << endl;
}