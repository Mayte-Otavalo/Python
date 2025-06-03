#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cmath>
#include <numeric>
#include <iomanip>

#define M_PI 3.14159265358979323846
using namespace std;

// ____Structure to store statistics of a class____
struct ClassStats {
    vector<double> means;
    vector<double> variances;
    double prior;
};

// _____Gaussian Naive Bayes Class_____
class GaussianNB {
private:
    map<string, ClassStats> classes;
    vector<string> featureNames;
    
public:
    void fit(const vector<vector<double>>& X, const vector<string>& y) {
        // Number of times each class appears
        map<string, int> classCounts;
        for (const auto& label: y) {
            classCounts[label]++;
        }
        
        // Calculate statistics for each class
        for (const auto& [label, count] : classCounts) {
            ClassStats stats;
            stats.prior = static_cast<double>(count) / y.size();
            
            // Filter samples of this class
            vector<vector<double>> classSamples;
            for (size_t i = 0; i < y.size(); ++i) {
                if (y[i] == label) {
                    classSamples.push_back(X[i]);
                }
            }
            
            if (!classSamples.empty()) {
                size_t numFeatures = classSamples[0].size();
                stats.means.resize(numFeatures);
                stats.variances.resize(numFeatures);
                
                for (size_t j = 0; j < numFeatures; ++j) {
                    // Calculate mean
                    double sum = accumulate(classSamples.begin(), classSamples.end(), 0.0,
                        [j](double acc, const vector<double>& sample) {
                            return acc + sample[j];
                        });
                    stats.means[j] = sum / classSamples.size();
                    
                    // Calculate variance
                    double sqSum = accumulate(classSamples.begin(), classSamples.end(), 0.0,
                        [j, &stats](double acc, const vector<double>& sample) {
                            return acc + pow(sample[j] - stats.means[j], 2);
                        });
                    stats.variances[j] = sqSum / (classSamples.size() - 1);
                    
                    // Avoid zero variance
                    if (stats.variances[j] < 1e-9) {
                        stats.variances[j] = 1e-9;
                    }
                }
            }
            
            classes[label] = stats;
        }
    }
    
    string predict(const vector<double>& sample) const {
        string bestLabel;
        double maxPosterior = -numeric_limits<double>::max();
        
        for (const auto& [label, stats] : classes) {
            double posterior = log(stats.prior);
            
            for (size_t j = 0; j < sample.size(); ++j) {
                double mean = stats.means[j];
                double variance = stats.variances[j];
                double x = sample[j];
                
                posterior += -0.5 * log(2 * M_PI * variance) 
                            - 0.5 * pow(x - mean, 2) / variance;
            }
            
            if (posterior > maxPosterior) {
                maxPosterior = posterior;
                bestLabel = label;
            }
        }
        
        return bestLabel;
    }
    
    vector<string> predict(const vector<vector<double>>& X) const {
        vector<string> predictions;
        predictions.reserve(X.size());
        for (const auto& sample : X) {
            predictions.push_back(predict(sample));
        }
        return predictions;
    }
};

//_______ Function to read labeled CSV file (with true labels)_______________
tuple<vector<string>, vector<vector<double>>, vector<string>> readLabeledCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    vector<string> names;
    vector<vector<double>> features;
    vector<string> labels;
    string line;
    
    // Read header
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ';')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() < 2) continue;
        
        names.push_back(tokens[0]);
        
        vector<double> sample;
        for (size_t i = 1; i < tokens.size() - 1; ++i) {
            try {
                sample.push_back(stod(tokens[i]));
            } catch (...) {
                sample.push_back(0.0);
            }
        }
        features.push_back(sample);
        
        labels.push_back(tokens.back());
    }
    
    return make_tuple(names, features, labels);
}

//________ Function to read unlabeled CSV file (without true labels)___________
pair<vector<string>, vector<vector<double>>> readUnlabeledCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    vector<string> names;
    vector<vector<double>> features;
    string line;
    
    // Read header
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ';')) {
            tokens.push_back(token);
        }
        
        if (tokens.empty()) continue;
        
        names.push_back(tokens[0]);
        
        vector<double> sample;
        for (size_t i = 1; i < tokens.size(); ++i) {
            try {
                sample.push_back(stod(tokens[i]));
            } catch (...) {
                sample.push_back(0.0);
            }
        }
        features.push_back(sample);
    }
    
    return make_pair(names, features);
}

// ______Function to save prediction results to CSV__________
void savePredictionResults(const string& filename, 
                         const vector<string>& names,
                         const vector<string>& predictions) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Could not create output file: " + filename);
    }

    // Write header
    outFile << "Name;Predicted Label\n";
    
    // Write data
    for (size_t i = 0; i < names.size(); ++i) {
        outFile << names[i] << ";" << predictions[i] << "\n";
    }
    
    outFile.close();
}

// ___________Function to save evaluation results to CSV_____________
void saveEvaluationResults(const string& filename, 
                         const vector<string>& names,
                         const vector<string>& yTrue,
                         const vector<string>& yPred,
                         double accuracy) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Could not create output file: " + filename);
    }

    // Write header
    outFile << "Name;True Label;Predicted Label\n";
    
    // Write data
    for (size_t i = 0; i < names.size(); ++i) {
        outFile << names[i] << ";" << yTrue[i] << ";" << yPred[i] << "\n";
    }
    
    // Write accuracy
    outFile << "\nAccuracy;" << fixed << setprecision(2) << accuracy * 100 << "%\n";
    
    outFile.close();
}

double calculateAccuracy(const vector<string>& yTrue, const vector<string>& yPred) {
    if (yTrue.size() != yPred.size() || yTrue.empty()) {
        return 0.0;
    }
    
    int correct = 0;
    for (size_t i = 0; i < yTrue.size(); ++i) {
        if (yTrue[i] == yPred[i]) {
            correct++;
        }
    }
    
    return static_cast<double>(correct) / yTrue.size();
}

int main() {
    GaussianNB model;
    bool modelTrained = false;
    
    try {
        int choice;
        do {
            cout << "\nGaussian Naive Bayes Classifier\n";
            cout << "1. Train model with training data\n";
            cout << "2. Evaluate model with labeled test data\n";
            cout << "3. Predict labels for unlabeled data\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1: {
                    string trainFile;
                    cout << "Enter training CSV filename: ";
                    cin >> trainFile;
                    
                    auto [trainNames, X_train, y_train] = readLabeledCSV(trainFile);
                    model.fit(X_train, y_train);
                    modelTrained = true;
                    cout << "\nModel trained with " << X_train.size() << " samples.\n";
                    break;
                }
                
                case 2: {
                    if (!modelTrained) {
                        cout << "Error: Model not trained yet.\n";
                        break;
                    }
                    
                    string testFile, outputFile;
                    cout << "Enter labeled test CSV filename: ";
                    cin >> testFile;
                    cout << "Enter output CSV filename: ";
                    cin >> outputFile;
                    
                    auto [testNames, X_test, y_test] = readLabeledCSV(testFile);
                    vector<string> y_pred = model.predict(X_test);
                    double accuracy = calculateAccuracy(y_test, y_pred);
                    
                    saveEvaluationResults(outputFile, testNames, y_test, y_pred, accuracy);
                    cout << "\nEvaluation results saved to " << outputFile << "\n";
                    cout << "Accuracy: " << fixed << setprecision(2) << accuracy * 100 << "%\n";
                    break;
                }
                
                case 3: {
                    if (!modelTrained) {
                        cout << "Error: Model not trained yet.\n";
                        break;
                    }
                    
                    string newFile, outputFile;
                    cout << "Enter unlabeled CSV filename: ";
                    cin >> newFile;
                    cout << "Enter output CSV filename: ";
                    cin >> outputFile;
                    
                    auto [newNames, X_new] = readUnlabeledCSV(newFile);
                    vector<string> y_pred = model.predict(X_new);
                    
                    savePredictionResults(outputFile, newNames, y_pred);
                    cout << "\nPredictions saved to " << outputFile << "\n";
                    cout << "Added predicted labels to " << newNames.size() << " samples.\n";
                    break;
                }
                
                case 0:
                    cout << "Exiting...\n";
                    break;
                    
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}