#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

struct Vehicle
{
    string brand;
    string model;
    int budgetMin;
    int budgetMax;
    int rangeMin;
    int rangeMax;
    int maintenance;
    int chargingTime;
    int type;  // 2 for 2-wheeler, 3 for 3-wheeler, 4 for 4-wheeler
};

vector<Vehicle> loadEVData(const string& filename)
{
    vector<Vehicle> vehicles;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error - Could not open EV data file.\n";
        return vehicles;
    }
    string line;
    getline(file, line);  // Skip header
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
        getline(ss, temp, ','); v.chargingTime = stoi(temp);
        getline(ss, temp, ','); v.type = stoi(temp);  // Add type
        vehicles.push_back(v);
    }
    file.close();
    return vehicles;
}

int getCityRating(const string& cityName) {
    ifstream file("city_ratings.csv");
    if (!file.is_open()) {
        cout << "Error - Could not open city ratings file.\n";
        return 3;
    }
    string line, city;
    int rating;
    getline(file, line);  // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, city, ',');
        ss >> rating;
        if (city == cityName) {
            return rating;
        }
    }
    return 3;
}
void recommendEVModels(int budget, int usage, const string& city, int vehicleType, const vector<Vehicle>& vehicles) {
    bool found = false;
    int cityRating = getCityRating(city);
    cout << "\nRecommended EV Models based on your inputs:\n\n";
    if (cityRating < 5) {
        int minChargingTime = INT_MAX;
        vector<Vehicle> filteredVehicles;
        for (const auto& v : vehicles) {
            if (v.type == vehicleType && budget >= v.budgetMin && budget <= v.budgetMax &&
                usage >= v.rangeMin && usage <= v.rangeMax) {
                if (v.chargingTime < minChargingTime) {
                    minChargingTime = v.chargingTime;
                    filteredVehicles.clear();
                    filteredVehicles.push_back(v);
                } else if (v.chargingTime == minChargingTime) {
                    filteredVehicles.push_back(v);
                }
            }
        }
        if (!filteredVehicles.empty()) {
            for (const auto& v : filteredVehicles) {
                cout << "--------------------------------------------\n";
                cout << "Model           - " << v.brand << " " << v.model << "\n";
                cout << "Starting Price  - Rs. " << v.budgetMin << "\n";
                cout << "Claimed Range   - " << v.rangeMin << " to " << v.rangeMax << " km\n";
                cout << "Maintenance     - Rs. " << v.maintenance << " / month\n";
                cout << "Charging Time   - " << v.chargingTime << " mins\n";
            }
            cout << "--------------------------------------------\n";
        } else {
            cout << "No EVs match your criteria.\n";
        }
    } else {
        for (const auto& v : vehicles) {
            if (v.type == vehicleType && budget >= v.budgetMin && usage <= v.rangeMax) {
                cout << "--------------------------------------------\n";
                cout << "Model           - " << v.brand << " " << v.model << "\n";
                cout << "Starting Price  - Rs. " << v.budgetMin << "\n";
                cout << "Claimed Range   - " << v.rangeMin << " to " << v.rangeMax << " km\n";
                cout << "Maintenance     - Rs. " << v.maintenance << " / month\n";
                cout << "Charging Time   - " << v.chargingTime << " mins\n";
                found = true;
            }
        }
        if (found)
            cout << "--------------------------------------------\n";
        else
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
        int budget, usage, vehicleType;
        string city;
        cout << "Enter your budget (in INR) - ";
        cin >> budget;
        cout << "Enter your average daily usage (in km) - ";
        cin >> usage;
        cout << "Enter your city - ";
        cin.ignore();
        getline(cin, city);
        cout << "Enter the type of vehicle (2 for 2-wheeler, 3 for 3-wheeler, 4 for 4-wheeler) - ";
        cin >> vehicleType;
        recommendEVModels(budget, usage, city, vehicleType, evData);
    } else if (choice == 2) {
        enterStatistics();
    } else {
        cout << "Invalid choice.\n";
    }
    return 0;
}

