#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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
    int type;
};
vector<Vehicle> loadEVData(const string& filename) {
    vector<Vehicle> vehicles;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error - Could not open input file.\n";
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
void writeSortedData(const string& filename, const vector<Vehicle>& data) {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Error - Could not write to output file.\n";
        return;
    }
    out << "brand,model,budgetMin,budgetMax,rangeMin,rangeMax,maintenance,chargingTime,type\n";
    for (const auto& v : data) {
        out << v.brand << "," << v.model << "," << v.budgetMin << "," << v.budgetMax << ","
            << v.rangeMin << "," << v.rangeMax << "," << v.maintenance << ","
            << v.chargingTime << "," << v.type << "\n";
    }
    out.close();
    cout << "Sorted data written to '" << filename << "' successfully.\n";
}
int main()
{
    string inputFile = "ev_data.csv";
    string outputFile = "ev_data_sorted.csv";
    vector<Vehicle> allVehicles = loadEVData(inputFile);
    if (allVehicles.empty()) return 1;
    vector<Vehicle> type2, type3, type4;
    for (const auto& v : allVehicles)
	{
        if (v.type == 2) type2.push_back(v);
        else if (v.type == 3) type3.push_back(v);
        else if (v.type == 4) type4.push_back(v);
    }
    auto sorter = [](const Vehicle& a, const Vehicle& b)
	{
        return a.budgetMin > b.budgetMin;
    };
    sort(type2.begin(), type2.end(), sorter);
    sort(type3.begin(), type3.end(), sorter);
    sort(type4.begin(), type4.end(), sorter);
    vector<Vehicle> sortedAll;
    sortedAll.insert(sortedAll.end(), type2.begin(), type2.end());
    sortedAll.insert(sortedAll.end(), type3.begin(), type3.end());
    sortedAll.insert(sortedAll.end(), type4.begin(), type4.end());
    writeSortedData(outputFile, sortedAll);
    return 0;
}
