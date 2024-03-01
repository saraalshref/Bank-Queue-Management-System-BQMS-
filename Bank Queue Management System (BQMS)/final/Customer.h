#ifndef Customer_h
#define Customer_h

#include <string>
using namespace std;


class Customer {
public:
    string name;
    int serviceTime;
    int arrivalTime;
    int startServiceTime = 0;
    int leaveTime = 0;
    bool isVip;


    Customer(string n, int service, int arrival, bool isvip) {
        name = n;
        serviceTime = service;
        arrivalTime = arrival;
        isVip = isvip;
    }

    int getTotalTime()  {
        return leaveTime - arrivalTime;
    }

    bool operator<(const Customer& s) const {
        return arrivalTime > s.arrivalTime;
    }

};

#endif