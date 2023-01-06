#include "../header/Airline.h"

Airline::Airline(const string &code, const string &name, const string &callSign, const string &country) {
    code_ = code;
    name_ = name;
    callSign_ = callSign;
    country_ = country;
}

string Airline::getCode() const { return code_; }

string Airline::getName() const { return name_; }

string Airline::getCallSign() const { return callSign_; }

string Airline::getCountry() const { return country_; }

bool Airline::operator==(const Airline &t) const {
    return code_ == t.getCode();
}

bool Airline::operator<(const Airline &t) const {
    return code_ < t.getCode();
}
