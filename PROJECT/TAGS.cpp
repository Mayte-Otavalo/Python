#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <iomanip>

using namespace std;

// _________Function to check if a file exists__________
bool fileExists(const string &filename) {
    ifstream file(filename);
    return file.good();
}

//______________Function to remove whitespace___________
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

//_____________Function to split CSV line_____________
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

// ______________Function to convert string to safe double________
double safeStod(const string &str) {
    if (str.empty()) return 0.0;
    try {
        return stod(str);
    } catch (...) {
        return 0.0;
    }
}

//______________ Function to find column index___________
int findColumnIndex(const vector<string> &headers, const string &columnName) {
    auto it = find(headers.begin(), headers.end(), columnName);
    if (it != headers.end()) {
        return distance(headers.begin(), it);
    }
    return -1;
}

int main() {
  string inputFilename, outputFilename;
    
    // Validate input file (repeat until it exists)
    do {
        cout << "Ingrese el nombre del archivo CSV de entrada: ";
        getline(cin, inputFilename);
        
        if (!fileExists(inputFilename)) {
            cerr << "File don't find. Please try again.\n";
        }
    } while (!fileExists(inputFilename));
    
    ifstream inputFile(inputFilename);
    
    // Read header
    string headerLine;
    getline(inputFile, headerLine);
    vector<string> headers = parseCSVLine(headerLine);
    
    //Check required columns
    vector<string> requiredColumns = {
        "MA3168", "Agua sin tratar", "MA224_RP_C_ND_ZU", "MA224_RP_C_ND_ZR",
        "MA225_RP_C_NH_ZU", "MA225_RP_C_NH_ZR", "MA3345", "MA3344" };
    
    map<string, int> columnIndices;
    for (const auto &col : requiredColumns) {
        columnIndices[col] = findColumnIndex(headers, col);
        if (columnIndices[col] == -1) {
            cerr << "Error: Columna requerida '" << col << "' no encontrada\n";
            return 1;
        }
    }
    
    // Prepare output file
    cout << "Ingrese el nombre del archivo CSV de salida: ";
    getline(cin, outputFilename);
    
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Error al crear el archivo de salida.\n";
        return 1;
    }
    
    // Write header with new column
    outputFile << headerLine << ";Desnutricion\n";
    
    // Accountants
    int bajoRiesgo = 0;
    int altoRiesgo = 0;
    int lineCount = 0;
    
    // Process each line
string line;
while (getline(inputFile, line)) {
    lineCount++;
    vector<string> fields = parseCSVLine(line);
    
    // Initialize point counter
    int puntajeDesnutricion = 0;
    int desnutricion = 0;  // Default: 0 (low risk)
    
    // Evaluate all conditions (add points)
    try {
        // MA3168 == "2" → +1 point
        if (columnIndices["MA3168"] < fields.size() && fields[columnIndices["MA3168"]] == "2") {
            puntajeDesnutricion++;
        }
        
        // Raw water > 25000 → +1 point
        if (columnIndices["Agua sin tratar"] < fields.size() && safeStod(fields[columnIndices["Agua sin tratar"]]) > 25000) {
            puntajeDesnutricion++;
        }
        
        // MA224_RP_C_ND_ZU < 15 → +1 point
        if (columnIndices["MA224_RP_C_ND_ZU"] < fields.size() && safeStod(fields[columnIndices["MA224_RP_C_ND_ZU"]]) < 15) {
            puntajeDesnutricion++;
        }
        
        // MA224_RP_C_ND_ZR < 15 → +1 point
        if (columnIndices["MA224_RP_C_ND_ZR"] < fields.size() && safeStod(fields[columnIndices["MA224_RP_C_ND_ZR"]]) < 15) {
            puntajeDesnutricion++;
        }
        
        // MA225_RP_C_NH_ZU < 10 → +1 point
        if (columnIndices["MA225_RP_C_NH_ZU"] < fields.size() && safeStod(fields[columnIndices["MA225_RP_C_NH_ZU"]]) < 10) {
            puntajeDesnutricion++;
        }
        
        // MA225_RP_C_NH_ZR < 10 → +1 point
        if (columnIndices["MA225_RP_C_NH_ZR"] < fields.size() && safeStod(fields[columnIndices["MA225_RP_C_NH_ZR"]]) < 10) {
            puntajeDesnutricion++;
        }
        
        // MA3345 == "2" → +1 point
        if (columnIndices["MA3345"] < fields.size() && fields[columnIndices["MA3345"]] == "2") {
            puntajeDesnutricion++;
        }
        
        // MA3344 == "2" → +1 point
        if (columnIndices["MA3344"] < fields.size() && fields[columnIndices["MA3344"]] == "2") {
            puntajeDesnutricion++;
        }
        
        // Final classification (≥ 2 points = malnutrition)
        if (puntajeDesnutricion >= 2) {
            desnutricion = 1;
            altoRiesgo++;
        } else {
            bajoRiesgo++;
        }
        
    } catch (const exception &e) {
        cerr << "Error processing line" << lineCount << ": " << e.what() << endl;
        desnutricion = 0;  // Por defecto: bajo riesgo si hay error
        bajoRiesgo++;
    }
    
    // Write line with new column
    outputFile << line << ";" << desnutricion << "\n";
}
    inputFile.close();
    outputFile.close();
    
    // Show statistics
    cout << "_____________________________________________";
    cout << "\n         Classification summary\n";
    cout << "|____________________________________________";
    cout << "\n|Total records processed: " << lineCount << "\n";
    cout << "|Low risk(0): " << bajoRiesgo << " (" 
         << fixed << setprecision(1) << (bajoRiesgo * 100.0 / lineCount) << "%)\n";
    cout << "|High risk (1): " << altoRiesgo << " (" 
         << fixed << setprecision(1) << (altoRiesgo * 100.0 / lineCount) << "%)\n";
    cout << "______________________________________________";
    
    return 0;
}