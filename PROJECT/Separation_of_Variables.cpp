#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
using namespace std;

//__________ Function to trim whitespace from a string_______
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

//__________Function to read CSV header__________________
vector<string> readHeader(ifstream &file) {
    string headerLine;
    getline(file, headerLine);
    vector<string> headers;
    stringstream ss(headerLine);
    string header;
    
    while (getline(ss, header, ';')) {
        headers.push_back(trim(header));
    }
    return headers;
}

// ___________Function to parse CSV line_________________
vector<string> parseCSVLine(const string &line) {
    vector<string> fields;
    bool inQuotes = false;
    string currentField;
    
    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ';' && !inQuotes) {
            fields.push_back(trim(currentField));
            currentField.clear();
        } else {
            currentField += c;
        }
    }
    fields.push_back(trim(currentField));
    return fields;
}

// ________________Function to get user-selected columns_________________
vector<size_t> getSelectedColumns(const vector<string>& headers) {
    vector<size_t> selectedIndices;
    string input;

    while (true) {
        selectedIndices.clear();

        cout << "Columnas disponibles:\n";

            size_t total = headers.size();
            size_t half = (total + 1) / 2;  //Round up if odd

            for (size_t i = 0; i < half; ++i) {
                // First column
                cout << setw(3) << i + 1 << ". " << left << setw(20) << headers[i];

                // Second column (only if it exists)
                size_t j = i + half;
                if (j < total) {
                    cout << " | " << setw(3) << j + 1 << ". " << left << headers[j];
                }

                cout << '\n';
            }

        cout << "\nEnter column numbers or names to keep (comma-separated): ";
        getline(cin, input);

        istringstream iss(input);
        string token;

        while (getline(iss, token, ';')) {
            token = trim(token);
            if (token.empty()) continue;

            bool isNumber = all_of(token.begin(), token.end(), [](char c) { return isdigit(c); });

            if (isNumber) {
                size_t index = stoi(token) - 1;
                if (index < headers.size()) {
                    selectedIndices.push_back(index);
                } else {
                    cerr << "Warning: Index " << index + 1 << " out of range. Ignored.\n";
                }
            } else {
                auto it = find(headers.begin(), headers.end(), token);
                if (it != headers.end()) {
                    selectedIndices.push_back(distance(headers.begin(), it));
                } else {
                    cerr << "Warning: Column '" << token << "' not found. Ignored.\n";
                }
            }
        }

        sort(selectedIndices.begin(), selectedIndices.end());
        selectedIndices.erase(unique(selectedIndices.begin(), selectedIndices.end()), selectedIndices.end());

        if (!selectedIndices.empty()) {
            break;
        }
        cerr << "No valid columns selected. Please try again.\n";
    }

    return selectedIndices;
}

// Function to write filtered CSV
void writeFilteredCSV(const string &inputFile, const string &outputFile, 
                     const vector<size_t> &selectedIndices, const vector<string> &headers) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);
    
    if (!inFile.is_open()) {
        throw runtime_error("Error opening input file");
    }
    
    if (!outFile.is_open()) {
        throw runtime_error("Error creating output file");
    }
    
    // Write header
    for (size_t i = 0; i < selectedIndices.size(); ++i) {
        if (i > 0) outFile << ";";
        outFile << headers[selectedIndices[i]];
    }
    outFile << "\n";
    
    // Skip header in input file
    string line;
    getline(inFile, line);
    
    // Process data lines
    while (getline(inFile, line)) {
        vector<string> fields = parseCSVLine(line);
        bool first = true;
        
        for (size_t index : selectedIndices) {
            if (!first) outFile << ";";
            if (index < fields.size()) {
                if (fields[index].find(';') != string::npos || fields[index].find('"') != string::npos) {
                    outFile << "\"" << fields[index] << "\"";
                } else {
                    outFile << fields[index];
                }
            }
            first = false;
        }
        outFile << "\n";
    }
    
    inFile.close();
    outFile.close();
}

int main() {
    try {
        string inputFile, outputFile;

        while (true) {
            cout << "\nEnter input CSV filename: ";
            getline(cin, inputFile);
            
            if (!inputFile.empty()) {
                break;
            }
            cerr << "\nFilename cannot be empty. Please try again.\n";
        }

        ifstream inFile(inputFile);
        if (!inFile.is_open()) {
            throw runtime_error("\nCould not open input file");
        }

        vector<string> headers = readHeader(inFile);
        inFile.close();

        vector<size_t> selectedIndices = getSelectedColumns(headers);

        cout << "\nEnter output CSV filename: ";
        getline(cin, outputFile);

        writeFilteredCSV(inputFile, outputFile, selectedIndices, headers);
        
        cout << "\nSuccessfully created filtered file: " << outputFile << "\n";
        
    } catch (const exception &e) {
        cerr << "\nError: " << e.what() << "\n";
        return 1;
    }

    return 0;
}