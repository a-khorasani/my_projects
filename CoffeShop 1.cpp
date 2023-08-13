#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
fstream loginFile("login.txt", ios::in);
fstream priceFile("price.txt", ios::in);
fstream mojodiFile("mojodi.txt", ios::in );
fstream hesab("soorathesab.txt", ios::app);
class date {
private :
	int day, month, year;
public:
	date(int ,int ,int );
	friend ostream& operator << (ostream&, const date&);
	date get_date();
};
date::date(int year,int month,int day) {
	this->day = day;
	this->month = month;
	this->year = year;
}
date date::get_date() {
	date d(0, 0, 0);
	d.day = day;
	d.month = month;
	d.year = year;
	return d;
}
ostream& operator<<(ostream& ostr, const date& d) {
	return ostr << d.year << "/" << d.month << "/" << d.day;
}
class Customer {
private :
	string name, number;
	int cost = 0;
	string ordered;
public :
	Customer(string,string);
	friend class HotDrink;
	friend class ColdDrink;
	friend class Food;
	void soorat(string);
	void costsoorat() {
		hesab << "cost is : " << cost << endl;
		hesab << endl << "----------------------------" << endl;
	}
};
Customer::Customer(string name,string number) {
	this->name = name;
	this->number = number;
	fstream customerFile("Customers.txt", ios::app);
	if (!customerFile) {
		cout << "Something went wrong !!!";
		exit(0);
	}
	customerFile << "Name : " << this->name <<endl<< "Number : " << this->number<< endl;
	customerFile << "----------------------" << endl;
	hesab << "Name : " << this->name << endl << "Number : " << this->number << endl;
}
void Customer::soorat(string ordered) {
	hesab << ordered<< endl;
}
class ColdDrink;
class Food;
class HotDrink {
private:
	string name, p, m;
	int price;
	int mojodi;
public:
	HotDrink();
	string get_name();
	void customerCost(Customer&,int&);
	friend void replace(HotDrink [],ColdDrink [],Food []);
};
HotDrink::HotDrink() {
	priceFile >> name >> p >> p;
	mojodiFile >> m >> m;
	price = atoi(p.c_str());
	mojodi = atoi(m.c_str());
}
void HotDrink::customerCost(Customer& customer,int& todayIncome) {
	customer.cost += price;
	todayIncome += price;
	mojodi--;
}
string HotDrink::get_name() {
	return name;
}
class ColdDrink {
private:
	string name, p, m;
	int price;
	int mojodi;
public:
	ColdDrink();
	string get_name();
	friend class HotDrink;
	void customerCost(Customer&, int&);
	friend void replace(HotDrink[], ColdDrink[],Food []);
};
ColdDrink::ColdDrink() {
	priceFile >> name >> p >> p;
	mojodiFile >> m >> m;
	price = atoi(p.c_str());
	mojodi = atoi(m.c_str());
}
void ColdDrink::customerCost(Customer& customer, int& todayIncome) {
	customer.cost += price;
	todayIncome += price;
	mojodi--;
}
string ColdDrink::get_name() {
	return name;
}
class Food {
private:
	string name, p, m;
	int price;
	int mojodi;
public:
	Food();
	string get_name();
	void customerCost(Customer&, int&);
	friend void replace(HotDrink[], ColdDrink[], Food[]);
};
Food::Food() {
	priceFile >> name >> p >> p;
	mojodiFile >> m >> m;
	price = atoi(p.c_str());
	mojodi = atoi(m.c_str());
}
void Food::customerCost(Customer& customer, int& todayIncome) {
	customer.cost += price;
	todayIncome += price;
	mojodi--;
}
string Food::get_name() {
	return name;
}
void replace(HotDrink h[],ColdDrink c[],Food f[]) {
	fstream MojodiUpdate("mojodi.txt", ios::out);
	if (!MojodiUpdate) {
		cout << "Something went wrong !!!";
		exit(0);
	}
	for (int i = 0; i < 4; i++) {
		MojodiUpdate << h[i].name << " " << h[i].mojodi << endl;
	}
	for (int i = 0; i < 4; i++) {
		MojodiUpdate << c[i].name << " " << c[i].mojodi << endl;
	}
	for (int i = 0; i < 4; i++) {
		MojodiUpdate << f[i].name << " " << f[i].mojodi << endl;
	}
	MojodiUpdate.close();
} // to update the inventory
void login();
void menu(int&, HotDrink[], ColdDrink[], Food[]);
void set_customer(string&, string&);
void menuFile();
void alert();
void inventory();
void order(int&,Customer&,HotDrink [],ColdDrink [], Food []);
int main() {
	login();
	int day, month, year,todayIncome=0;
	HotDrink* h;
	h = new HotDrink[4];
	ColdDrink* c;
	c = new ColdDrink[4];
	Food* f;
	f = new Food[4];
	cout << "Please enter the date : (yyyy/mm/dd) " << endl;
	cin >> year >> month >> day;
	date d(year, month, day);
	hesab << "DATE :" << endl;
	hesab << d.get_date() << endl;
	hesab << "----------------------------" << endl;
	menu(todayIncome, h, c, f);
	hesab << "Today Income : "<< todayIncome << endl;
	hesab.close();
	priceFile.close();
	mojodiFile.close();
	delete[]h; delete[]c; delete[]f;
	return 0;
}
void login() {
	string u, p;
	string username, password;
	loginFile >> username >> username;
	loginFile >> password >> password;
	cout << "-----------------LOGIN-----------------" << endl;
	cout << "User Name : ";
	cin >> u;
	cout << "Password : ";
	cin >> p;
	while (u != username || p != password)
	{
		cout << "The username or password is incorrect !" << endl << endl;
		cout << "-----------------LOGIN-----------------" << endl<< endl;
		cout << "User Name : ";
		cin >> u;
		cout << "Password : ";
		cin >> p;
	}
	cout <<endl<< "Wellcome..." << endl<< endl;
} // the login page 
void alert() {
	fstream mojodiDisplay("mojodi.txt", ios::in);
	if (!mojodiDisplay) {
		cout << "Something went wrong !!!";
		exit(0);
	}
	string name,str_number;
	int int_number;
	while (mojodiDisplay >> name >> str_number) {
		int_number = atoi(str_number.c_str());
		if (int_number < 20) {
			cout << name << " must be purchased"<< endl;
		}
	}
	mojodiDisplay.close();
} //If the stock of coffee shop products is less than 20 pieces, give us a warning
void inventory() {
	fstream inventoryFile("mojodi.txt", ios::in);
	if (!inventoryFile) {
		cout << "Something went wrong !!!";
		exit(0);
	}
	string name, num;
	while (!inventoryFile.eof()) {
		inventoryFile >> name >> num;
		cout << name << " : " << num<< endl;
	}
	inventoryFile.close();
} //To see our inventory
void menu(int& todayIncome, HotDrink h[], ColdDrink c[], Food f[]) {
	bool exit = false;
	while (exit==false) {
		int num = 0;
		string name, number;
		cout << "-------------------- Coffee Land --------------------"<< endl;
		cout << "1. New Order" << endl;
		cout << "2. View inventory " << endl;
		cout << "3. View warehouse alerts " << endl;
		cout << "4. Today Income" << endl;
		cout << "5. Exit" << endl << endl;
		cout << "Please choose a number : ";
		cin >> num;
		cout << endl;
		switch (num)
		{
		case 1: {set_customer(name, number); Customer customer(name, number); menuFile(); order(todayIncome, customer, h, c, f); } break;
		case 2: inventory(); break;
		case 3: alert(); break;
		case 4: {cout << "Today Income is : " << todayIncome << endl; } break;
		case 5: exit = true; break;
		default: cout << "The number is incorrect ! " << endl; break;
		}
	}
} // List of things we can do
void set_customer(string& name, string& number) {
	cout << "Please enter the name of customer : ";
	cin >> name;
	cout << "Please enter the number of customer : ";
	cin >> number;
} // For customer registration
void menuFile() {
	string print;
	fstream menuFile("menu.txt", ios::in);
	if (!menuFile) {
		cout << "Something went wrong !!!";
		exit(0);
	}
	while (!menuFile.eof()) {
		menuFile >> print;
		cout << print<< endl;
	}
	cout << endl<< "Please Select your favorite Drinks or Foods : (To finish please enter 0) "<< endl;
} // to see the menu of coffee shop
void order(int& todayIncome,Customer& customer,HotDrink h[],ColdDrink c[], Food f[]) {
	int o = 100;
	while (o != 0) {
		cin >> o;
		switch (o)
		{
		case 0: o = 0; replace(h,c,f); customer.costsoorat(); break;
		case 1: h[0].customerCost(customer, todayIncome); customer.soorat(h[0].get_name());  break;
		case 2: h[1].customerCost(customer, todayIncome); customer.soorat(h[1].get_name());  break;
		case 3: h[2].customerCost(customer, todayIncome); customer.soorat(h[2].get_name());  break;
		case 4: h[3].customerCost(customer, todayIncome); customer.soorat(h[3].get_name());  break;
		case 5: c[0].customerCost(customer, todayIncome); customer.soorat(c[0].get_name());  break;
		case 6: c[1].customerCost(customer, todayIncome); customer.soorat(c[1].get_name());  break;
		case 7: c[2].customerCost(customer, todayIncome); customer.soorat(c[2].get_name());  break;
		case 8: c[3].customerCost(customer, todayIncome); customer.soorat(c[3].get_name());  break;
		case 9: f[0].customerCost(customer, todayIncome); customer.soorat(f[0].get_name());  break;
		case 10: f[1].customerCost(customer, todayIncome); customer.soorat(f[1].get_name());  break;
		case 11: f[2].customerCost(customer, todayIncome); customer.soorat(f[0].get_name());  break;
		case 12: f[3].customerCost(customer, todayIncome); customer.soorat(f[0].get_name());  break;
		}
	}
} // to order things
