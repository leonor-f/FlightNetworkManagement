#ifndef AIRLINE_H
#define AIRLINE_H

#include<string>

using namespace std;

class Airline {
    public:
        Airline(const string& code, const string& name, const string& callSign, const string& country);

        string getCode() const;
        string getName() const;
        string getCountry() const;

        bool operator==(const Airline &t) const;
        bool operator<(const Airline& t) const;

    private:
        string code_;
        string name_;
        string country_;
};

#endif
