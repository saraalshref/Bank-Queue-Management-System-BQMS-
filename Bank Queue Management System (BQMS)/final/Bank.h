#include "Teller.h"
#include "Customer.h"
#include <iostream>
#include <queue>




struct CustomerCompare {
    bool operator()(const Customer& c1, const Customer& c2) {
        if (c1.arrivalTime == c2.arrivalTime) {
            // priority based on  isVip flag
            return c1.isVip < c2.isVip; 
        }
        return c1.arrivalTime > c2.arrivalTime; 
    }
};


class Bank {
private:
    priority_queue<Customer, vector<Customer>, CustomerCompare> bankQueue;
    Teller* tellers;
    int numTellers;
    int totalCustomers = 0;
    int totalWaitingTime = 0;
    int totalServiceTime = 0;

public:
    Bank(int num) {
        numTellers = num;
        tellers = new Teller[numTellers];
    }


    void enqueueCustomer(string name, int serviceTime, int arrivalTime,bool isVip) {
        Customer newCustomer(name, serviceTime, arrivalTime,isVip);
        bankQueue.push(newCustomer);
        totalCustomers++;
    }

    void serveCustomers() {
        int currentTime = 0;

        int* customersServed = new int[numTellers]();
        int* totalWorkTime = new int[numTellers]();

        while (!bankQueue.empty()) {
            serveNextCustomer(currentTime, customersServed, totalWorkTime);
            updateCurrentTime(currentTime);
            availablitiOfTeller(currentTime);
        }

        displayStatistics(customersServed, totalWorkTime);

    }

private:
    void serveNextCustomer(int& currentTime, int* customersServed, int* totalWorkTime) {
        int availableTellers = numOfTellerAvailable();
        int maxCustomers = min(availableTellers, (int)bankQueue.size());

        for (int i = 0; i < maxCustomers; ++i) {
            int tellerIndex = nextAvailableTeller();
            if (tellerIndex == -1)
                break;

            Customer currentCustomer = bankQueue.top();
            bankQueue.pop();

            CustomerprocessDisplay(currentTime, tellerIndex, currentCustomer, customersServed, totalWorkTime);
        }
    }

    int numOfTellerAvailable() {
        int availableTellers = 0;
        for (int i = 0; i < numTellers; ++i) {
            if (tellers[i].available) {
                ++availableTellers;
            }
        }
        return availableTellers;
    }

    int nextAvailableTeller() {
        for (int i = 0; i < numTellers; ++i) {
            if (tellers[i].available) {
                return i;
            }
        }
        return -1;
    }

    void CustomerprocessDisplay(int& currentTime, int tellerIndex, Customer& currentCustomer, int* customersServed, int* totalWorkTime) {
        if (currentTime > currentCustomer.arrivalTime) {
            currentCustomer.startServiceTime = currentTime;
        }
        else {
            currentCustomer.startServiceTime = currentCustomer.arrivalTime;
        }

        currentCustomer.leaveTime = currentCustomer.startServiceTime + currentCustomer.serviceTime;
        totalWaitingTime += currentCustomer.startServiceTime - currentCustomer.arrivalTime;
        totalServiceTime += currentCustomer.serviceTime;
        tellers[tellerIndex].available = false;
        tellers[tellerIndex].leaveTime = currentCustomer.leaveTime;

        customersServed[tellerIndex]++;
        totalWorkTime[tellerIndex] += currentCustomer.serviceTime;

        cout << "\ncustomer: " << currentCustomer.name << endl;
        cout << "arrival Time: " << currentCustomer.arrivalTime << endl;
        cout << "service Time: " << currentCustomer.serviceTime << " units." << endl;
        cout << "waiting time: " << (currentCustomer.startServiceTime - currentCustomer.arrivalTime) << " units." << endl;
        cout << "Served by Teller: " << (tellerIndex + 1) << endl;
        cout << "leave time: " << currentCustomer.leaveTime << endl;
        cout << "total time take in bank: " << currentCustomer.getTotalTime() << " units." << endl;
        cout << "-----------------------------------------------------------------------------" << endl;
    }

    void updateCurrentTime(int& currentTime) {
        currentTime = 10000000;
        for (int i = 0; i < numTellers; ++i) {
            if (!tellers[i].available) {
                if (currentTime > tellers[i].leaveTime) {
                    currentTime = tellers[i].leaveTime;
                }
            }
        }
    }

    void availablitiOfTeller(int currentTime) {
        for (int i = 0; i < numTellers; ++i) {
            if (!tellers[i].available && currentTime >= tellers[i].leaveTime) {
                tellers[i].available = true;
            }
        }
    }

    void displayStatistics(int* customersServed, int* totalWorkTime) {
        cout << "\nAverage\n";
        cout << "average waiting time: " << (double)totalWaitingTime / totalCustomers << " units" << endl;
        cout << "average service time: " << (double)totalServiceTime / totalCustomers << " units" << endl;

        cout << "\nTeller Utilization:\n";
        for (int i = 0; i < numTellers; ++i) {
            cout << "teller " << (i + 1) << " served " << customersServed[i] << " customers, working for a total of " << totalWorkTime[i] << " units." << endl;
        }
    }
};
