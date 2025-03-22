#ifndef CLINICALLABORATORY_H
#define CLINICALLABORATORY_H

#include <string>

class ClinicalLaboratory{
private:
    std::string name;
    std::string address;
    int numberOfTests;

    void updateTestCount(int newTests); 

public:
    ClinicalLaboratory();

    ClinicalLaboratory(std::string name, std::string address, int numberOfTests);

    std::string getName() const;
    std::string getAddress() const;
    int getNumberOfTests() const;

    void setName(std::string newName);
    void setAddress(std::string newAddress);
    void setNumberOfTests(int newNumberOfTests);

    
    void displayInfo() const;
};

#endif 