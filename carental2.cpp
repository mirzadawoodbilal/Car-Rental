#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void printmainmenu(); void logout(); void printmanagement(); void cancelbooking(); void viewbookings(); void listofcars(); void employetab();
void viewemployelist();
void addEmployeeToList();
void saveAdminCredentials(const string& name, const string& email, const string& phone);
void saveUserCredentials(const string& name, const string& email, const string& phone);
void saveEmployeCredentials(const string& ename, const string& eemail, const string& ephone);

class Car {
public:
    string name;        // Name of the car
    string model;       // Model of the car
    string year;        // Year of the car
    int rentCost;       // Rent cost per day
    bool available;     // Whether the car is available for rent

    // Default constructor
    Car() {
        name = "";
        model = "";
        year = "";
        rentCost = 0;
        available = true;
    }

    // Parameterized constructor
    Car(string name, string model, string year, int rentCost, bool available = true) {
        this->name = name;
        this->model = model;
        this->year = year;
        this->rentCost = rentCost;
        this->available = available;
    }
    void addcar() {
    cout << "Enter the name of the car: ";
    cin >> name;
    cout << "Enter the model of the car: ";
    cin >> model;
    cout << "Enter the year of the car: ";
    cin >> year;
    cout << "Enter the rentcost of the car: ";
    cin >> rentCost;
    ofstream carFile;
    carFile.open("carsdata.txt", std::ios_base::app); // open the file in append mode

    if (carFile.is_open()) {
        carFile << name << " " << model << " " << year << " " << rentCost << " " << available << endl;
        carFile.close();
        cout << "Car added successfully!" << endl;
        printmanagement();
    } else {
        cout << "Unable to open file." << endl;
        printmanagement();
    }
}
    void removecar() {
        string cname;
        cout << "Enter the name of the car to remove: ";
        cin>> cname;
        ifstream carFile;
        carFile.open("carsdata.txt");

        if (carFile.is_open()) {
        ofstream tempFile;
            tempFile.open("temp.txt");

            bool found = false;
            while (carFile >> name >> model >> year >> rentCost >> available) {
                if (name == cname) {
                    found = true;
                    continue; // skip writing the car to the temporary file
            }   
                tempFile << name << " " << model << " " << year << " " << rentCost << " " << available << endl;
        }
            carFile.close();
            tempFile.close();

        if (found) {
            remove("carsdata.txt");
            rename("temp.txt", "carsdata.txt");
            cout << "Car removed successfully!" << endl;
            printmanagement();
        } else {
            cout << "Car not found." << endl;
            printmanagement();
        }
    } 
        else {
        cout << "Unable to open file." << endl;
        printmanagement();
    }
}
void showCars() {
    cout << "Following cars are available:" << endl;
    ifstream carFile("carsdata.txt");
    Car c;

    if (carFile.is_open()) {
        cout << "\nAvailable Cars:\n";
        cout << "-------------------------------------------------\n";
        cout << "Name\t\tModel\t\tYear\t\tRent Cost per Day\n";
        cout << "-------------------------------------------------\n";

        // Read car data from the file and print it to the console
        while (carFile >> c.name >> c.model >> c.year >> c.rentCost >> c.available) {
            if (c.available == true) {
                cout << c.name << "\t\t" << c.model << "\t\t" << c.year << "\t\t" << c.rentCost << " RS\n";
            }
        }
        carFile.close();
    }
    else {
        cout << "Error: Unable to open file.\n";
    }

    int y, x;
    cout << "Please select any car from the above list:" << endl;
    cin >> y;

    if (y > 0) {
        ofstream bookingsFile("bookings.txt", ios::app);

        if (bookingsFile.is_open()) {
            bookingsFile << c.name << " " << c.model << " " << c.year << " " << c.rentCost << " " << endl;
            bookingsFile.close();
            cout << "Booking saved successfully!" << endl;
        } else {
            cout << "Error: Unable to open bookings file." << endl;
        }

        cout << "\n\t\t\t\t\t Your Booking has been Finalised Booking Number is: "<<y<<" Thank You!"<<"\n\t\t\t\t\t To views bookings press 1 \n\t\t\t\t\t To cancel booking press 2 \n\t\t\t\t\t To navigate back press 3" << endl;
        cin >> x;
        if (x==1)
        {
            viewbookings();
        }
        else if (x == 2) {
            cancelbooking();
        } else if (x == 3) {
            printmainmenu();
        }
    } else {
        cout << "Wrong command!" << endl;
        printmainmenu();
    }
}
//end of car class
};

class user{
    
    private:
        vector<Car> cars;
        string name;
        string email;
        string phone;

    public:
        user(string uname, string uemail, string uphone){
            name=uname;
            email=uemail;
            phone=uphone;
        }

    void booking() const{
        int a;
        cout<<"\n\t\t\t\t\t Would you like to book any car? press 1 \n\t\t\t\t\t if not press 2"<<endl;cin>>a;
        if (a==1)
        {
            Car c;
            c.showCars();
        }
        else if (a==2){
            cout<<"Navigating Back to Main menu!"<<endl;
            printmainmenu();
        }
        else{
            cout<<"\n\t\t\t\t\t Wrong Command Navigating Back to Main Menu."<<endl;
            printmainmenu();
        }
    }
};
    void cancelbooking(){
        string line;
        vector<string> bookings; // Store all existing bookings

        ifstream bookingsFile("bookings.txt");
        if (bookingsFile.is_open()) {
        // Read all existing bookings and store them in the vector
        while (getline(bookingsFile, line)) {
            bookings.push_back(line);
        }
        bookingsFile.close();
        } else {
        cout << "Error: Unable to open bookings file." << endl;
        printmainmenu();
        return;
        }

    int choice;
    cout << "Please enter the booking number you wish to cancel: ";
    cin >> choice;

    // Check if the choice is valid
    if (choice > 0 && choice <= bookings.size()) {
        // Remove the chosen booking from the vector
        bookings.erase(bookings.begin() + choice - 1);

        // Rewrite all remaining bookings to the file
        ofstream bookingsFile("bookings.txt");
        if (bookingsFile.is_open()) {
            for (string booking : bookings) {
                bookingsFile << booking << endl;
            }
            bookingsFile.close();
            cout << "Booking canceled successfully!" << endl;
            printmainmenu();
            return;
        } else {
            cout << "Error: Unable to open bookings file." << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
        printmainmenu();
    }
    cout<<"would you like to view any bookings? if Yes press 1 if not press 2 to navigate back"<<endl;
    int x;cin>>x;
    if (x==1)
    {
        viewbookings();
    }
    else{
    printmainmenu();}
}
void viewbookings() {
    ifstream bookingsFile("bookings.txt");
    string name, model, year;
    int rentCost, count = 0;

    if (bookingsFile.is_open()) {
        cout << "Bookings:\n";
        cout << "----------------------------------------------------\n";
        cout << "No.\tName\t\tModel\t\tYear\tRent Cost per Day\n";
        cout << "----------------------------------------------------\n";

        while (bookingsFile >> name >> model >> year >> rentCost) {
            // Print the booking data to the console
            cout << ++count << ".\t" << name << "\t" << model << "\t" << year
                 << "\t" << rentCost << endl;
        }

        bookingsFile.close();
    } else {
        cout << "Error: Unable to open bookings file." << endl;
    }
    cout<<"Would you like to cancel any bookings? if Yes press 1.\nif you want to add new booking then press 2\nelse press 3 to navigate back."<<endl;
    int x;cin>>x;
    Car c;
    if (x==1)
    {
        cancelbooking();
    }
    else if (x==2)
    {
        c.showCars();
    }
    else if(x==3){
        printmainmenu();
    }
}
class employee{
        public:
        string ename, eemail, ephone;

        public:
     void removeEmployee()
     {
        string eename;
        cout << "Enter the name of the employee to remove: ";
        cin>> eename;
        ifstream empFile;
        empFile.open("Employeecredentials.txt");

        if (empFile.is_open()) {
        ofstream tempFile;
            tempFile.open("temp.txt");

            bool found = false;
            while (empFile >> ename >> eemail >> ephone) {
                if (eename == ename) {
                    found = true;
                    continue; 
            }   
                tempFile << ename << " " << eemail << " " << ephone << endl;
        }
            empFile.close();
            tempFile.close();

        if (found) {
            remove("Employeecredentials.txt");
            rename("temp.txt", "Employeecredentials.txt");
            cout << "Employee removed successfully!" << endl;
            printmanagement();
        } else {
            cout << "Employee not found." << endl;
            printmanagement();
        }
    } 
        else {
        cout << "Unable to open file." << endl;
        printmanagement();
    }
    printmanagement();
}
};

class management:public employee{
    public:
        string mname;
        string memail;
        string mphone;

    
    void admintab(){
        cout<<"\n\t\t\t\t\t Welcome to Admin Tab:\n"<<endl;
        int q;
    Car c;
    cout<<"\n\t\t\t\t\t Choose any of the options"<<endl;
    cout<<"\n\t\t\t\t\t 1.Add Car \n\t\t\t\t\t 2.Remove Car \n\t\t\t\t\t 3.list of Cars \n\t\t\t\t\t 4.View Bookings \n\t\t\t\t\t 5.Cancel Bookings \n\t\t\t\t\t 6.Logout"<<endl;
    cout<<"\n\n\n\t\t\t\t\t OR USE ANY OF THESE OPTIONS \n\t\t\t\t\t 7.Add Employee \n\t\t\t\t\t 8.Remove Employee \n\t\t\t\t\t 9.View Employee List"<<endl;
    cin>>q; if (q==1)
    {
        cout<<"Navigating to ADD CAR:"<<endl;
        c.addcar();
    }
    else if (q==2)
    {
        cout<<"Navigating to REMOVE CAR:"<<endl;
        c.removecar();
    }
    else if(q==3){
        cout<<"Navigating to List of All CARS AVAILABLE:"<<endl;
        listofcars();
    }
    else if(q==4){
        cout<<"Navigating to VIEW BOOKINGS:"<<endl;
        viewbookings();
    }
    else if(q==5){
        cout<<"Navigating to CANCEL BOOKINGS:"<<endl;
        cancelbooking();
    }
    else if (q==6){
        logout();
    }else if (q==7)
    {
        addEmployeeToList();
        admintab();
    }else if (q==8)
    {
        removeEmployee();
    }
    else if(q==9){
        viewemployelist();
        admintab();
    }    
    else{
        cout<<"Wrong command!"<<endl;
        admintab();     }
}
};

class carrental : public management, public user {
private:
    vector<Car> cars;
public:
    // Default constructor
    carrental(string uname, string uemail, string uphone) : user(uname, uemail, uphone) {}

    void printusertab() const {
        int x;
        cout << "Welcome to User Tab! \nPlease Select anyone of the following." << endl;
        cout << "1.Book any Ride.\n2.Cancel any Ride.\n3.View Previous Bookings. \n4.Logout" << endl;
        cin >> x;
        if (x == 1) {
            cout << "\t\t\t\t\t Navigating to Booking Section." << endl;
            booking();
        } else if (x == 2) {
            cout << "\t\t\t\t\t Navigating to Cancel Section" << endl;
            cancelbooking();
        } else if (x == 3) {
            viewbookings();
        }
        else if (x == 4) {
            logout();
        } else {
            cout << "\t\t\t\t\t Wrong Selection Navigating back!" << endl;
            printmainmenu();
        }
    }
};

void viewemployelist() {
    ifstream file("Employeecredentials.txt");
    if (file.is_open()) {
        string name, email, phone;
        cout << "Employee List:\n";
        cout << "----------------------------------------------------\n";
        cout << "No.\tName\t\tEmail\t\t\tPhone\n";
        cout << "----------------------------------------------------\n";
        int count = 0;
        while (file >> name >> email >> phone) {
            ++count;
            cout << count << ".\t" << name << "\t" << email << "\t" << phone << endl;
        }
        file.close();
    } else {
        cout << "Error: Unable to open employee file." << endl;
    }
}

void addEmployeeToList() {
    management m1; string ename, eemail, ephone;
    cout<<"Enter Name of Employee"<<endl;cin>>ename;
    cout<<"Enter email of Employee"<<endl;cin>>eemail;
    cout<<"Enter phone of Employee"<<endl;cin>>ephone;
    saveEmployeCredentials(ename, eemail, ephone);
    cout << "Employee added successfully!" << endl;
    m1.admintab();
}

void employetab(){
    int q;
    Car c;
    cout<<"\n\t\t\t\t\t Choose any of the options"<<endl;
    cout<<"\n\t\t\t\t\t 1.Add Car \n\t\t\t\t\t 2.Remove Car \n\t\t\t\t\t 3.list of Cars \n\t\t\t\t\t 4.View Bookings \n\t\t\t\t\t 5.Cancel Bookings \n\t\t\t\t\t 6.Logout"<<endl;
    cin>>q; if (q==1)
    {
        cout<<"Navigating to ADD CAR:"<<endl;
        c.addcar();
    }
    else if (q==2)
    {
        cout<<"Navigating to REMOVE CAR:"<<endl;
        c.removecar();
    }
    else if(q==3){
        cout<<"Navigating to List of All CARS AVAILABLE:"<<endl;
        listofcars();
    }
    else if(q==4){
        cout<<"Navigating to VIEW BOOKINGS:"<<endl;
        viewbookings();
    }
    else if(q==5){
        cout<<"Navigating to CANCEL BOOKINGS:"<<endl;
        cancelbooking();
    }
    else if (q==6){
        logout();
    }
    else{
        cout<<"Wrong command!"<<endl;
        employetab();
    }
}
void listofcars(){

    cout << "Following cars are available:" << endl;
    ifstream carFile("carsdata.txt");
    Car c;

    if (carFile.is_open()) {
        cout << "\nAvailable Cars:\n";
        cout << "-------------------------------------------------\n";
        cout << "Name\t\tModel\t\tYear\t\tRent Cost per Day\n";
        cout << "-------------------------------------------------\n";

        // Read car data from the file and print it to the console
        while (carFile >> c.name >> c.model >> c.year >> c.rentCost >> c.available) {
            if (c.available == true) {
                cout << c.name << "\t\t" << c.model << "\t\t" << c.year << "\t\t" << c.rentCost << " RS\n";
            }
        }
        carFile.close();
    }
    else {
        cout << "Error: Unable to open file.\n";
    }
    cout<<"Would You Like to Add another car? If yess press 1 if you want to remove any car press 2. else press 3 to g0 back"<<endl;
    int x; cin>>x;
    if (x==1)
    {
        c.addcar();
    }
    else if (x==2)
    {
        c.removecar();
    }
    else if(x==3){
        printmanagement();
    }
    else{cout<<"Wrong command navigating back!"<<endl; printmainmenu();}
}

void saveBooking(const string& carname, const string& renterName ){
    Car car;
    ofstream bookingsFile("bookings.txt", ios::app);
    if (bookingsFile.is_open()) {
        bookingsFile << car.name << " " << car.model << " " << car.year << " "
            << car.rentCost << " " << renterName << " " << endl;
        bookingsFile.close();
        cout << "Booking saved successfully!" << endl;
    } else {
        cout << "Error: Unable to open bookings file." << endl;
    }
}

void saveAdminCredentials(const string& name, const string& email, const string& phone) {
    ofstream file("Admincredentials.txt", ios::app);
    if (file.is_open()) {
        // Write the credentials to the file
        file << name << " " << email << " "<< phone << endl;
        file.close();
        cout << "Credentials of Admin "<<name<<" saved."<< endl;
    } else {
        cout << "Error opening file." << endl;
    }
}
void saveEmployeCredentials(const string& name, const string& email, const string& phone) {
    ofstream file("Employeecredentials.txt", ios::app);
    if (file.is_open()) {
        // Write the credentials to the file
        file << name << " " << email << " "<< phone << endl;
        file.close();
        cout << "Credentials of Employee "<<name<<" saved."<< endl;
    } else {
        cout << "Error opening file." << endl;
    }
}
void saveUserCredentials(const string& name, const string& email, const string& phone) {
    ofstream file("Usercredentials.txt", ios::app);
    if (file.is_open()) {
        // Write the credentials to the file
        file << name << " " << email << " "<< phone << endl;
        file.close();
        cout << "Credentials of User "<<name<<" saved."<< endl;
    } else {
        cout << "Error opening file." << endl;
    }
}

void printmanagement(){
    string mname; string memail; string mphone; 
    employee e,em,ep;
    int y;
    cout<<"Welcome to Managment Tab."<<endl;
        cout<<"Press 1 for Administration Tab. \nPress 2 for Employee tab. \nPress 3 to logout."<<endl;
        cin>>y;
        if (y==1)
        {
            cout<<"Admin:\n\t\t\t\t\t Enter name to Login:"<<endl;
            cin>>mname;
            cout<<"\t\t\t\t\t Enter your email:"<<endl;
            cin >> memail;
            cout<<"\t\t\t\t\t Enter your phone:"<<endl;
            cin >> mphone;
            cout<<"\t\t\t\t\t Logged in as "<<mname<<" successfully! \n\t\t\t\t\t NAVIGATING TO MAIN MENU \n"<<endl;
            saveAdminCredentials(mname, memail, mphone);
            management m1;
            mname=m1.mname; memail=m1.memail; mphone=m1.mphone;
            m1.admintab();
        }
        if (y==2)
        {
            cout<<"Employee:\n\t\t\t\t\t Enter Name to login:"<<endl;
            cin>>e.ename;
            cout<<"\t\t\t\t\t Enter your email:"<<endl;
            cin >> e.eemail;
            cout<<"\t\t\t\t\t Enter your phone:"<<endl;
            cin >> e.ephone;
            cout<<"\t\t\t\t\t Logged in as "<<e.ename<<" successfully! \n\t\t\t\t\t NAVIGATING TO MAIN MENU \n"<<endl;
            saveEmployeCredentials(e.ename,e.eemail,e.ephone);
            employetab();
        }
        else if (y==3)
        {
            logout();
        }
        else{
            cout<<"Exiting... GOOD BYE :-)"<<endl;  
        }
}

void printmainmenu(){
    string name, email, phone;
    carrental c2(name, email, phone);
    int x;
    // cout<<"\t\t\t\t\t Welcome to GIKI Car Rental Sytem \t\t\t\t"<<endl;
    cout<<"Select User: \n1.Management. \n2.User. \n3.Exit. "<<endl;
    cin>>x;
    if (x==1)
    {
        printmanagement();
    }
    else if (x==2)
    {
        cout<<"User:\n\t\t\t\t\t Enter your name to login:"<<endl;
        cin >> name;
        cout<<"\t\t\t\t\t Enter your email:"<<endl;
        cin >> email;
        cout<<"\t\t\t\t\t Enter your phone:"<<endl;
        cin >> phone;
        cout<<"\t\t\t\t\t Logged in as "<<name<<" successfully! \n\t\t\t\t\t NAVIGATING TO MAIN MENU \n"<<endl;
        saveUserCredentials(name, email, phone);
        c2.printusertab();
    }
    else if (x==3)
    {
        cout<<"Exiting... GOOD BYE :-)"<<endl;  
    }
};

void logout(){
    cout<<"Logging out."<<endl;
    printmainmenu();
}

int main(){
    cout<<"\t\t\t\t\t Welcome to GIKI Car Rental Sytem \t\t\t\t"<<endl;
    printmainmenu();

    return 0;
}

