#include <iostream>
#include <queue> 
#include"Teller.h"
#include"Customer.h"
#include "Bank.h"

using namespace std;

int main() {
    
     /*int numTellers = 3;
       Bank bank(numTellers);

       bank.enqueueCustomer("sara", 62, 35,false);
       bank.enqueueCustomer("alaa", 57, 35, true);
       bank.enqueueCustomer("amal", 124, 78, false);
       bank.enqueueCustomer("mohamed", 32,79, true);
       bank.enqueueCustomer("ahmed", 15, 80, false);
       bank.enqueueCustomer("mayar", 10, 90, true);
       bank.enqueueCustomer("ronaa", 20, 95, true);
       bank.enqueueCustomer("mona", 20, 107, false);
       bank.serveCustomers();*/


   
    int numofteller;
    cout << "enter number of tellers: ";
    cin >> numofteller;
    cout << "\n";
    Bank bank(numofteller); // Assuming 3 tellers
    string name;
    int serviceTime, arrivalTime;
    char choice, vip;

    do {
       
        cout << "enter customer name: ";
        cin >> name;
        cout << "enter service time for customer " << name << ": ";
        cin >> serviceTime;
        cout << "enter arrival time for customer " << name << ": ";
        cin >> arrivalTime;
        cout<< name << "is a vip customer? (y/n): ";
        cin >> vip;
        bool isVIP = (vip == 'y' || vip == 'Y');
        bank.enqueueCustomer(name, serviceTime, arrivalTime, isVIP);

        cout << "Do you want to add another customer? (y/n): ";
        cin >> choice;
        cout << "\n";
    } while (choice == 'y' || choice == 'Y');

    bank.serveCustomers();
  

    return 0;
}