#pragma once
class Teller {
public:
    bool available;
    int leaveTime;

    Teller() {
        available = true;
        leaveTime = 0;
    }
};

