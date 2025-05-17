#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <climits>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct Vehicle {
    string brand;
    string model;
    int budgetMin;
    int budgetMax;
    int rangeMin;
    int rangeMax;
    int maintenance;
    int chargingTime;
    int type;
};

vector<Vehicle> loadEVData(const string& filename) {
    vector<Vehicle> vehicles;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error - Could not open EV data file.\n";
        return vehicles;
    }
    string line;
    getline(file, line); // skip header
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
        getline(ss, temp, ','); v.type = stoi(temp);
        vehicles.push_back(v);
    }
    file.close();
    return vehicles;
}

int getCityRating(const string& cityName) {
    ifstream file("city_ratings.csv");
    if (!file.is_open()) {
        cout << "Error - Could not open city ratings file.\n";
        return 3; // Default rating
    }
    string line, city;
    int rating;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, city, ',');
        ss >> rating;
        if (city == cityName)
            return rating;
    }
    return 3; // Default rating if city not found
}

void recommendEVModels(int budget, int usage, const string& city, int vehicleType, const vector<Vehicle>& vehicles) {
    cout << "\nRank your preferences (1 for most important to 4 for least):\n";
    cout << "1. Range\n2. Budget\n3. Maintenance Cost\n4. Charging Time\n";

    vector<int> preference(4);
    unordered_set<int> usedRanks;
    for (int i = 0; i < 4; ++i) {
        int p;
        cout << "Enter rank for option " << i + 1 << ": ";
        cin >> p;
        if (p < 1 || p > 4 || usedRanks.count(p)) {
            cout << "Invalid or duplicate rank. Please enter values from 1 to 4 without repetition.\n";
            return;
        }
        usedRanks.insert(p);
        preference[i] = p;
    }

    vector<double> weights(4);
    for (int i = 0; i < 4; ++i)
        weights[i] = 5 - preference[i];

    vector<Vehicle> filtered;
    for (const auto& v : vehicles) {
        if (v.type == vehicleType &&
            budget >= v.budgetMin && budget <= v.budgetMax &&
            usage >= v.rangeMin && usage <= v.rangeMax) {
            filtered.push_back(v);
        }
    }

    if (filtered.empty()) {
        cout << "No EVs match your criteria.\n";
        return;
    }

    int minRange = INT_MAX, maxRange = 0, minBudget = INT_MAX, maxBudget = 0;
    int minMaint = INT_MAX, maxMaint = 0, minCharge = INT_MAX, maxCharge = 0;

    for (const auto& v : filtered) {
        minRange = min(minRange, v.rangeMin);
        maxRange = max(maxRange, v.rangeMax);
        minBudget = min(minBudget, v.budgetMin);
        maxBudget = max(maxBudget, v.budgetMax);
        minMaint = min(minMaint, v.maintenance);
        maxMaint = max(maxMaint, v.maintenance);
        minCharge = min(minCharge, v.chargingTime);
        maxCharge = max(maxCharge, v.chargingTime);
    }

    struct ScoredVehicle {
        Vehicle v;
        double score;
    };
    vector<ScoredVehicle> scoredList;
    for (const auto& v : filtered) {
        double rangeScore = (maxRange == minRange) ? 1.0 : (double)(v.rangeMin - minRange) / (maxRange - minRange);
        double budgetScore = (maxBudget == minBudget) ? 1.0 : 1.0 - (double)(v.budgetMin - minBudget) / (maxBudget - minBudget);
        double maintScore = (maxMaint == minMaint) ? 1.0 : 1.0 - (double)(v.maintenance - minMaint) / (maxMaint - minMaint);
        double chargeScore = (maxCharge == minCharge) ? 1.0 : 1.0 - (double)(v.chargingTime - minCharge) / (maxCharge - minCharge);

        double totalScore = rangeScore * weights[0] +
                            budgetScore * weights[1] +
                            maintScore * weights[2] +
                            chargeScore * weights[3];

        scoredList.push_back({v, totalScore});
    }

    sort(scoredList.begin(), scoredList.end(), [](const ScoredVehicle& a, const ScoredVehicle& b) {
        return a.score > b.score;
    });

    cout << "\nTop Recommended EVs -\n";
    for (int i = 0; i < min(3, (int)scoredList.size()); ++i) {
        const auto& v = scoredList[i].v;
        cout << "--------------------------------------------\n";
        cout << "Model           - " << v.brand << " " << v.model << "\n";
        cout << "Starting Price  - Rs. " << v.budgetMin << "\n";
        cout << "Claimed Range   - " << v.rangeMin << " to " << v.rangeMax << " km\n";
        cout << "Maintenance     - Rs. " << v.maintenance << " / month\n";
        cout << "Charging Time   - " << v.chargingTime << " mins\n";
        cout << "Score           - " << scoredList[i].score << "\n";
    }
    cout << "--------------------------------------------\n";
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
    cout << "Data saved successfully.\nOPENING POWER BI...\n";

    string command = "start \"\" \"slicing.pbix\"";
    int result = system(command.c_str());
    if (result != 0) {
        cout << "Could not open the Power BI report. Please ensure slicing.pbix is in the same folder.\n";
    }
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
        getline(cin, city);
        cout << "Enter the type of vehicle (2 for 2-wheeler, 3 for 3-wheeler, 4 for 4-wheeler) - ";
        cin >> vehicleType;

        recommendEVModels(budget, usage, city, vehicleType, evData);
    } else if (choice == 2)
	{
        enterStatistics();
    } else {
        cout << "Invalid choice.\n";
    }
    return 0;
}
