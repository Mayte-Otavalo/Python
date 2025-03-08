#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Mayte Otavalo"; 

/**
 * @param filename  
 * @returns        
 */
std::set<std::string> get_applicants(std::string filename) {
    std::set<std::string> applicants;
    std::ifstream file(filename);
    std::string name;

    if (!file) {
        std::cerr << "Error " << filename << std::endl;
        return applicants;
    }

    while (getline(file, name)) {
        applicants.insert(name);
    }

    file.close();
    return applicants;
}
/**
 *
 * @param name      
 * @param students  
 * @return          
 */

std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
    std::queue<const std::string*> matches;
    
    size_t spaceIndex = name.find(' ');
    if (spaceIndex == std::string::npos) {
        return matches; 
    }

    char firstInitial = name[0];
    char lastInitial = name[spaceIndex + 1];

    for (const std::string& student : students) {
        size_t studentSpace = student.find(' ');
        if (studentSpace != std::string::npos) {
            char studentFirstInitial = student[0];
            char studentLastInitial = student[studentSpace + 1];

            if (studentFirstInitial == firstInitial && studentLastInitial == lastInitial) {
                matches.push(&student);
            }
        }
    }

    return matches;
}


std::string get_match(std::queue<const std::string*>& matches) {
    if (matches.empty()) {
        return "NO MATCHES FOUND.";
    }

    const std::string* bestMatch = matches.front();
    matches.pop();

    while (!matches.empty()) {
        const std::string* current = matches.front();
        matches.pop();
        if (current->length() < bestMatch->length()) {
            bestMatch = current;
        }
    }

    return *bestMatch;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
