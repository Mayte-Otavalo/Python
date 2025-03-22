/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

 #include "class.h"
 #include <iostream>

void sandbox() {


  
      ClinicalLaboratory lab1;
      lab1.displayInfo(); 
  
      ClinicalLaboratory lab2("Central Lab", "123 ABC", 1000);
      lab2.displayInfo(); 
  
      lab1.setName("Downtown Lab");
      lab1.setAddress("456 DEF");
      lab1.setNumberOfTests(500);
      lab1.displayInfo(); 
  
      std::cout << "Lab 2 Name: " << lab2.getName() << std::endl;
      std::cout << "Lab 2 Address: " << lab2.getAddress() << std::endl;
      std::cout << "Lab 2 Tests: " << lab2.getNumberOfTests() << std::endl;
  
      lab2.setNumberOfTests(-10);
  


}