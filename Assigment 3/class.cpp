#include "class.h"
#include <iostream>

ClinicalLaboratory::ClinicalLaboratory() 
    : name("Unknown"), address("Unknown"), numberOfTests(0) {}

ClinicalLaboratory::ClinicalLaboratory(std::string name, std::string address, int numberOfTests)
    : name(name), address(address), numberOfTests(numberOfTests) {}

void ClinicalLaboratory::updateTestCount(int newTests) {
    numberOfTests += newTests; 
    std::cout << "Test count updated. New count: " << numberOfTests << std::endl;
}

std::string ClinicalLaboratory::getName() const {
    return name;
}

std::string ClinicalLaboratory::getAddress() const {
    return address;
}

int ClinicalLaboratory::getNumberOfTests() const {
    return numberOfTests;
}

void ClinicalLaboratory::setName(std::string newName) {
    name = newName;
}

void ClinicalLaboratory::setAddress(std::string newAddress) {
    address = newAddress;
}

void ClinicalLaboratory::setNumberOfTests(int newNumberOfTests) {
    if (newNumberOfTests >= 0) {
        updateTestCount(newNumberOfTests - numberOfTests); 
    } else {
        std::cerr << "Error: Number of tests cannot be negative." << std::endl;
    }
}

void ClinicalLaboratory::displayInfo() const {
    std::cout << "Laboratory Name: " << name << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Number of Tests: " << numberOfTests << std::endl;
}