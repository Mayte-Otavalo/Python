#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>

#include "CLI11.hpp" 

struct Transaction {
    std::string country;
    int quantity;
    double unit_price;
};

std::vector<Transaction> read_csv(const std::string& filename) {
    std::vector<Transaction> transactions;
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> row;

        while (std::getline(ss, token, ',')) {
            row.push_back(token);
        }

        if (row.size() >= 8) {
            try {
                int quantity = std::stoi(row[3]);
                double unit_price = std::stod(row[5]);
                std::string country = row[7];

                transactions.push_back({country, quantity, unit_price});
            } catch (...) {
                continue;
            }
        }
    }

    return transactions;
}

void show_transactions_per_country(const std::vector<Transaction>& data, const std::string& filter_country = "") {
    std::unordered_map<std::string, int> country_counts;

    for (const auto& t : data) {
        if (filter_country.empty() || t.country == filter_country) {
            country_counts[t.country]++;
        }
    }

    for (const auto& [country, count] : country_counts) {
        std::cout << std::setw(20) << std::left << country << ": " << count << " transactions\n";
    }
}

void show_total_amount(const std::vector<Transaction>& data, bool only_uk = false) {
    double total = 0.0;
    for (const auto& t : data) {
        if (!only_uk || t.country == "United Kingdom") {
            total += t.quantity * t.unit_price;
        }
    }
    std::cout << "Total amount: £" << std::fixed << std::setprecision(2) << total << "\n";
}

int main(int argc, char** argv) {
    CLI::App app{"Retail Data Analyzer"};

    std::string country;
    bool only_uk = false;
    bool show_total = false;

    app.add_option("--country", country, "Show transactions for a specific country");
    app.add_flag("--only-uk", only_uk, "Show only transactions from the UK (for total amount)");
    app.add_flag("--total", show_total, "Show total amount of transactions");

    CLI11_PARSE(app, argc, argv);

    std::string filename = "Online Retail(Online Retail).csv";
    auto data = read_csv(filename);

    if (show_total) {
        show_total_amount(data, only_uk);
    } else {
        show_transactions_per_country(data, country);
    }

    return 0;
}
