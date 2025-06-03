#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>
#include <ctime>

using namespace std;

// ________Function to split a CSV line___________
vector<string> parseCSVLine(const string& line) {
    vector<string> tokens;
    string token;
    bool inQuotes = false;
    
    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ';' && !inQuotes) {
            tokens.push_back(token);
            token.clear();
        } else {
            token += c;
        }
    }
    tokens.push_back(token);
    return tokens;
}
// _________Function to read CSV file___________
pair<vector<vector<string>>, vector<string>> readCSV(const string& filename, bool hasHeader = true) {
    ifstream file(filename);
    vector<vector<string>> X;
    vector<string> y;
    string line;
    
    if (hasHeader && file.good()) {
        getline(file, line); // Skip header
    }
    
    while (getline(file, line)) {
        vector<string> tokens = parseCSVLine(line);
        if (tokens.empty()) continue;
        
// We assume that the last column is the target variable
        y.push_back(tokens.back());
        tokens.pop_back();
        X.push_back(tokens);
    }
    
    return make_pair(X, y);
}

// Function to write data to CSV
void writeCSV(const string& filename, const vector<vector<string>>& X, const vector<string>& y, const vector<string>& header = {}) {
    ofstream file(filename);
    
    if (!header.empty()) {
        for (size_t i = 0; i < header.size(); ++i) {
            file << header[i];
            if (i < header.size() - 1) file << ";";
        }
        file << "\n";
    }
    
// Write rows of data
    for (size_t i = 0; i < X.size(); ++i) {
        //  X[i] values
        for (size_t j = 0; j < X[i].size(); ++j) {
            file << X[i][j];
            if (j < X[i].size() - 1) file << ";";
        }

        // Add column y[i] to the end (only if X[i] has data)
        if (!X[i].empty()) {
            file << ";" << y[i];
        } else {
            file << y[i];
        }

        file << "\n";
    }
}

// Function to split data into train/test/prediction
tuple<vector<vector<string>>, vector<string>, 
      vector<vector<string>>, vector<string>,
      vector<vector<string>>, vector<string>> 
trainTestPredSplit(const vector<vector<string>>& X, const vector<string>& y, 
                  float testSize = 0.2, float predSize = 0.1, int randomSeed = 42) {
    
    // Validate sizes
    if (testSize + predSize >= 1.0) {
        throw invalid_argument("La suma de testSize y predSize debe ser menor que 1.0");
    }
    
    // Create indexes and merge them
    vector<size_t> indices(X.size());
    iota(indices.begin(), indices.end(), 0);
    
   // Mix with fixed seed for reproducibility
    shuffle(indices.begin(), indices.end(), default_random_engine(randomSeed));
    
    // Calculate split points
    size_t testSplit = static_cast<size_t>(X.size() * (1.0 - testSize - predSize));
    size_t predSplit = static_cast<size_t>(X.size() * (1.0 - predSize));
    
   // Vectors for results
    vector<vector<string>> X_train, X_test, X_pred;
    vector<string> y_train, y_test, y_pred;
    
    // Split the data
    for (size_t i = 0; i < indices.size(); ++i) {
        if (i < testSplit) {
            X_train.push_back(X[indices[i]]);
            y_train.push_back(y[indices[i]]);
        } else if (i < predSplit) {
            X_test.push_back(X[indices[i]]);
            y_test.push_back(y[indices[i]]);
        } else {
            X_pred.push_back(X[indices[i]]);
            y_pred.push_back(y[indices[i]]);
        }
    }
    
    return make_tuple(X_train, y_train, X_test, y_test, X_pred, y_pred);
}

int main() {
    string inputFilename;
    cout << "Ingrese el nombre del archivo CSV: ";
    cin >> inputFilename;
    
    // read data
    auto [X, y] = readCSV(inputFilename);
    
    if (X.empty() || y.empty()) {
        cerr << "Error: No se pudieron leer datos del archivo.\n";
        return 1;
    }
    
    cout << "Datos leídos: " << X.size() << " muestras con " 
         << (X.empty() ? 0 : X[0].size()) << " características cada una.\n";
    
    try {
        //Split the data (70% train, 20% test, 10% prediction)
        auto [X_train, y_train, X_test, y_test, X_pred, y_pred] = trainTestPredSplit(X, y, 0.20, 0.4, 42);
        
        cout << "\nDivisión realizada:\n";
        cout << " - Conjunto de entrenamiento: " << X_train.size() << " muestras\n";
        cout << " - Conjunto de prueba: " << X_test.size() << " muestras\n";
        cout << " - Conjunto de predicción: " << X_pred.size() << " muestras\n";
        
        // Save results
        string trainFilename = "train_" + inputFilename;
        string testFilename = "test_" + inputFilename;
        string predFilename = "pred_" + inputFilename;
        
        // Read original header if it exists
        ifstream originalFile(inputFilename);
        string headerLine;
        getline(originalFile, headerLine);
        originalFile.close();
        
        vector<string> header;
        if (!headerLine.empty()) {
            header = parseCSVLine(headerLine);
            if (!header.empty()) header.pop_back(); // Quitar columna objetivo
        }
        
        writeCSV(trainFilename, X_train, y_train, header);
        writeCSV(testFilename, X_test, y_test, header);
        writeCSV(predFilename, X_pred, y_pred, header);
        
        cout << "\nArchivos guardados:\n";
        cout << " - Entrenamiento: " << trainFilename << "\n";
        cout << " - Prueba: " << testFilename << "\n";
        cout << " - Predicción: " << predFilename << "\n";
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}