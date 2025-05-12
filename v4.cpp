#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
struct Vehicle {
    string brand;
    string model;
    int budgetMin;
    int budgetMax;
    int rangeMin;
    int rangeMax;
    int maintenance;
};
vector<Vehicle> loadEVData(const string& filename) {
    vector<Vehicle> vehicles;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error - Could not open EV data file.\n";
        return vehicles;
    }
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Vehicle v;
        getline(ss, v.brand, ',');
        getline(ss, v.model, ',');
        getline(ss, temp, ','); v.budgetMin = stoi(temp);
        getline(ss, temp, ','); v.budgetMax = stoi(temp);
        getline(ss, temp, ','); v.rangeMin = stoi(temp);
        getline(ss, temp, ','); v.rangeMax = stoi(temp);
        getline(ss, temp, ','); v.maintenance = stoi(temp);
        vehicles.push_back(v);
    }
    file.close();
    return vehicles;
}
void recommendEVModels(int budget, int usage, const vector<Vehicle>& vehicles) {
    bool found = false;
    cout << "\nRecommended EV Models based on your inputs -\n";
    for (const auto& v : vehicles) {
        if (budget >= v.budgetMin && budget <= v.budgetMax &&
            usage >= v.rangeMin && usage <= v.rangeMax) {
            cout << "- " << v.brand << " " << v.model 
                 << " (Maintenance- ?" << v.maintenance << "/month)\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No EVs match your criteria.\n";
    }
}
void enterStatistics() {
    ofstream file("ev_statistics.csv", ios::app);
    if (!file) {
        cout << "Error - Could not open the file for writing.\n";
        return;
    }
    int year, month, type;
    cout << "Enter Year - ";
    cin >> year;
    cout << "Enter Month (1-12) - ";
    cin >> month;
    cout << "Enter Vehicle Type (2 for 2-wheeler, 3 for 3-wheeler, 4 for 4-wheeler) - ";
    cin >> type;
    file << year << "," << month << "," << type << "\n";
    file.close();
    cout << "Data saved successfully.\n";
}
int main() {
    int choice;
    cout << "Welcome to the EV Portal\n";
    cout << "Enter 1 to get a recommendation\n";
    cout << "Enter 2 to enter EV statistics\n";
    cout << "Choice - ";
    cin >> choice;
    if (choice == 1) {
        vector<Vehicle> evData = loadEVData("ev_data.csv");
        if (evData.empty()) {
            cout << "Recommendation system unavailable. Data file missing or invalid.\n";
            return 1;
        }
        int budget, usage;
        cout << "Enter your budget (in INR) - ";
        cin >> budget;
        cout << "Enter your average daily usage (in km) - ";
        cin >> usage;
        recommendEVModels(budget, usage, evData);
    } else if (choice == 2) {
        enterStatistics();
    } else {
        cout << "Invalid choice.\n";
    }
    return 0;
}
