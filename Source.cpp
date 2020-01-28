/*
	Author: Fabian Torres
	Project: Carwash sales program

	Project Requirements:
		0) Comments
		1) Appropiate Data Types
		2) Local, constant and global variables
		3) Input validation
		4) Control statements
		5) Switch statements
		6) Loops (While,Do-while,Range-based,For-loop)
		7) Functions passing parameters
		8) Arrays: Multidimensional array and parallel array
		9) Output program data to a text file
		10) Vectors

*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;

//Const Global Variable Deleclartions 
const double sales_tax = 0.0725;

const int PLANS_AMOUNT = 4;

const double car_wash_plan_prices[PLANS_AMOUNT] = {4.87, 9.81, 14.87, 19.87};
const string car_wash_plan_names[PLANS_AMOUNT] = {"Basic", "Ultra", "Super", "Premium"};

const string car_wash_plan_details[PLANS_AMOUNT][2] = { 
	{"Basic", "This plan comes with a basic rinse and wash for your car."}, 
	{"Ultra", "This plan comes with a rinse and wash for your car.\n Along with your car being vaccumed and a free air freshener."}, 
	{"Super", "This plan comes with a rinse and wash for your car.\n Along with your car being vaccumed and a free air freshener.\n With your tires being polished."},
	{"Premium", "This plan comes with a rinse and wash with the best soap for your car.\n Along with your car being vaccumed and with a long during air freshener.\n With your tires being polished till they look new."}
};

//Purchased Information
vector<string> purchase_info;

//Function prototypes
void print_main_menu();
void print_help_menu();
void print_view_packages_menu();
void print_confirm_package_menu(string plan_name);
void print_invalid_input_message();
void print_package_confirmation_message(string name, double price);
bool valid_selection_input(char c);
int clamp(int min, int max, int c);
void write_sales();
string get_input();

int main() {
	//The reason for this is that there needs to be two characters reserved for the help and exit/back options 
	if (PLANS_AMOUNT > 23) {
		cout << "Too many options given during setup." << endl;
		cout << "Exiting program." << endl;
	}
	else {
		//If you're here current then you are in the main menu 
		bool main_menu = true;
		while (main_menu) {
			print_main_menu();
			string input = get_input();
			//Making sure the user input entered a single character if not then
			if (input.size() == 0 || input.size() > 1)
				print_invalid_input_message();
			else {
				char c = input[0];
				if (valid_selection_input(c)) {
					print_invalid_input_message();
					continue;
				}
				if (static_cast<int>(c) == (97 + PLANS_AMOUNT)) {
					//If you're here current then you are in the help menu 
					bool help_menu = true;
					while (help_menu) {
						print_help_menu();
						string input = get_input();
						if (input.size() == 0 || input.size() > 1) {
							print_invalid_input_message();
							continue;
						}
						char c = input[0];
						if (valid_selection_input(c)) {
							print_invalid_input_message();
							continue;
						}
						switch (c) {
						case 'a':
							for (int i = 0; i < PLANS_AMOUNT; ++i) {
								cout << "\t\tPlan: " << car_wash_plan_details[i][0] << endl;
								cout << "\t\tDetails: " << car_wash_plan_details[i][1] << endl;
							}
							help_menu = false;
							break;
						case 'b':
							help_menu = false;
							break;
						default:
							print_invalid_input_message();
							break;
						}
					}
					continue;
				}
				if (static_cast<int>(c) == (97 + PLANS_AMOUNT + 1)) {
					//If you're here current then you decided to exit the program 
					cout << "Exiting program!" << endl;
					main_menu = false;
					continue;
				}
				if (static_cast<int>(c) >= 97 && static_cast<int>(c) <= (122 - PLANS_AMOUNT - 1)) {
					//If you're here then your are in the confirmation menu
					bool confirm_package = true;
					while (confirm_package) {
						//Making sure with the clamp function we do not have an index out of range
						int index = clamp(0, PLANS_AMOUNT, (static_cast<int>(c) - 97));
						print_confirm_package_menu(car_wash_plan_names[index ]);
						string input = get_input();
						if (input.size() != 1) {
							print_invalid_input_message();
							continue;
						}
						char c = input[0];
						if (valid_selection_input(c)) {
							print_invalid_input_message();
							continue;
						}
						bool confirmation = false;
						switch (c) {
						case 'a':
							confirmation = true;
							confirm_package = false;
							break;
						case 'b':
							confirm_package = false;
							break;
						default:
							print_invalid_input_message();
							break;
						}
						if (confirmation) {
							cout << "What is your name?" << endl;
							string name = get_input();
							double price = car_wash_plan_prices[index];
							price = price + (price * sales_tax);
							print_package_confirmation_message(name, price);
							string info = name;
							info.push_back('\t');
							info.append(car_wash_plan_names[index]);
							info.push_back('\t');
							info.push_back('$');
							info.append(to_string(price));
							purchase_info.push_back(info);
						}
					}
				}
			}
		}
		write_sales();
	}
	return 0;
}
//All print... functions are functions that display a menu or a message
void print_main_menu()
{
	cout << "What kind of carwash would you like?" << endl;
	for (int i = 0; i < PLANS_AMOUNT; ++i) {
		cout << "\t" << static_cast<char>(97 + i) << ") " << car_wash_plan_names[i] << "\t$" << car_wash_plan_prices[i] << endl;
	}
	cout << "\t" << static_cast<char>(97 + PLANS_AMOUNT) << ") " << "Help" << endl;
	cout << "\t" << static_cast<char>(97 + PLANS_AMOUNT + 1) << ") " << "Exit" << endl;
}

void print_help_menu()
{
	cout << "What would you like help with?" << endl;
	cout << "\ta) View packages" << endl;
	cout << "\tb) Back" << endl;
}

void print_view_packages_menu()
{
	cout << "What kind of package would you like to view?" << endl;
	for (int i = 0; i < PLANS_AMOUNT; ++i) {
		cout << "\t" << static_cast<char>(97 + i) << ") " << car_wash_plan_names[i] << "\t$" << car_wash_plan_prices[i] << endl;
	}
	cout << "\t" << static_cast<char>(97 + PLANS_AMOUNT) << ") " << "Back" << endl;
}

void print_confirm_package_menu(string plan_name)
{
	cout << "You have selected the " << plan_name << " plan!" << endl;
	cout << "Are you sure?" << endl;
	cout << "Please type a) yes or b) no." << endl;
}

void print_invalid_input_message()
{
	cout << "What you inputed was not a valid input please try inputting a valid option!" << endl;
}

void print_package_confirmation_message(string name, double price)
{
	cout << "Okay " << name << " your total will be $" << setprecision(3) << price << "." << endl;
	cout << "Your vehicle will be ready in 30 mintues!" << endl;
	cout << "Type anything to continue." << endl;
	get_input();
}

//Only valid options are any character that are a-z
bool valid_selection_input(char c)
{
	return (static_cast<int>(c) < 97 || static_cast<int>(c) > 127);
}

int clamp(int min, int max, int c)
{
	if (c <= min)
		return min;
	if (c >= max)
		return max;
	return c;
}

void write_sales()
{
	time_t ttime = time(0);
	char* time = ctime(&ttime);
	string stime(time);
	replace(stime.begin(), stime.end(), ':', '_');
	if (purchase_info.size() != 0) {
		try {

			ofstream purchased_file;
			purchased_file.open(stime);
			for (auto var : purchase_info) {
				purchased_file << var << endl;
			}
			purchased_file.close();
		}
		catch (const exception& e) {
			cout << e.what() << endl;
		}
	}
}

//Function to retrive user input
string get_input()
{
	string line;
	cout << "Input>> ";
	getline(cin, line);
	return line;
}
