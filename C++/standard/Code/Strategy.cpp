#include<iostream>
#include<memory>
#include<string>
#include<string_view>
#include<sstream>

class Formatter {
public:
    virtual ~Formatter() = default;
    Formatter& withCustomerId(std::string_view customerId) {
        this->customerId = customerId;
        return *this;
    }
    Formatter& withForename(std::string_view forename) {
        this->forename = forename;
        return *this;
    }
    Formatter& withSurname(std::string_view surname) {
        this->surname = surname;
        return *this;
    }
    Formatter& withStreet(std::string_view street) {
        this->street = street;
        return *this;
    }
    Formatter& withZipCode(std::string_view zipCode) {
        this->zipCode = zipCode;
        return *this;
    }
    Formatter& withCity(std::string_view city) {
        this->city = city;
        return *this;
    }
    virtual std::string format() const = 0;
protected:
    std::string customerId { "000000" };
    std::string forename { "n/a" };
    std::string surname { "n/a" };
    std::string street { "n/a" };
    std::string zipCode { "n/a" };
    std::string city { "n/a" };
};

using FormatterPtr = std::unique_ptr<Formatter>;

class PlainTextFormatter : public Formatter {
public:
    std::string format() const override {
        std::stringstream formattedString { };
        formattedString<<"["<<customerId<<"]: "
            <<forename<<" "<<surname<<", "
            <<street<<", "<<zipCode<<" "
            <<city<<".";
        return formattedString.str();
    }
};

class XmlFormatter : public Formatter {
public:
    std::string format() const override {
        std::stringstream formattedString { };
        formattedString<<
            "customer id=\""<<customerId<<"\">\n"<<
            " <forename>"<<forename<<"</forename>\n"<<
            " <surname>"<<surname<<"</surname>\n"<<
            " <street>"<<street<<"</street>\n"<<
            " <zipCode>"<<zipCode<<"</zipCode>\n"<<
            " <city>"<<city<<"</city>\n"<<
            "</customer>\n";
        return formattedString.str();
    }
};

class JsonFormatter : public Formatter {
public:
    std::string format() const override {
        std::stringstream formattedString { };
        formattedString<<
            "{\n"<<
            " \"CustomerId: \""<<customerId<<END_OF_PROPERTY<<
            " \"Forename: \""<<forename<<END_OF_PROPERTY<<
            " \"Surname: \""<<surname<<END_OF_PROPERTY<<
            " \"Street: \""<<street<<END_OF_PROPERTY<<
            " \"Zip Code: \""<<zipCode<<END_OF_PROPERTY<<
            " \"City: \""<<city<<END_OF_PROPERTY<<
            "}\n";
        return formattedString.str();
    }
};

class Customer {
public:
    std::string getAsFormattedString(const FormatterPtr& formatter) const {
        return formatter->
            withCustomerId(customerId.to_string()).
            withForename(forename).
            withSurname(surname).
            withStreet(address.getStreet()).
            withZipCode(address.getZipCodeAsString()).
            withCity(address.getCity()).
            format();
    }
private:
    CustomerId customerId;
    std::string forename;
    std::string surname;
    Address address;
};

