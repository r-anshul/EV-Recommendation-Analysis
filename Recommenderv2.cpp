#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class EVData {
public:
    int budget;
    int usageDistance;
    int chargingStationAvailability; // (1 to 5 scale)
    int maintenanceCost;
    string city;
};

int getChargingAvailability(const string &city) {
    ifstream fin("city_charging_data.csv");
    string line, fileCity;
    int stations;
    while (getline(fin, line)) {
        size_t comma = line.find(',');
        fileCity = line.substr(0, comma);
        stations = stoi(line.substr(comma + 1));
        if (fileCity == city) {
            if (stations >= 100) return 5;
            else if (stations >= 75) return 4;
            else if (stations >= 50) return 3;
            else if (stations >= 25) return 2;
            else return 1;
        }
    }
    return 3; // Default value if city not found
}

void recommendEV(EVData &ev) {
    cout << "Let's begin the EV recommendation process -\n";
    cout << "Enter your city - ";
    cin >> ev.city;
    
    ev.chargingStationAvailability = getChargingAvailability(ev.city);

    cout << "Enter your estimated budget (in lakhs) - ";
    cin >> ev.budget;

    cout << "Enter your average daily usage distance (in km) - ";
    cin >> ev.usageDistance;

    cout << "Enter estimated yearly maintenance cost (in INR) - ";
    cin >> ev.maintenanceCost;

    if (ev.budget < 15) {
        if (ev.usageDistance < 40) {
            if (ev.maintenanceCost < 15000)
                cout << "Recommendation - Budget EV under 15L: Tata Tiago EV or MG Comet EV\n";
            else
                cout << "Recommendation - Budget EV under 15L: Consider MG ZS EV Base variant\n";
        } else {
            if (ev.maintenanceCost < 20000)
                cout << "Recommendation - Budget EV under 15L: Tata Nexon EV Base Model\n";
            else
                cout << "Recommendation - Budget EV under 15L: Mahindra XUV400 EC Variant\n";
        }
    } else if (ev.budget <= 25) {
        if (ev.usageDistance < 50) {
            if (ev.maintenanceCost < 25000)
                cout << "Recommendation - Mid-Range EV (15L-25L): Hyundai Kona or Tata Nexon EV Long Range\n";
            else
                cout << "Recommendation - Mid-Range EV (15L-25L): MG ZS EV Exclusive variant\n";
        } else {
            cout << "Recommendation - Mid-Range EV (15L-25L): Mahindra XUV400 EL or BYD e6 for long range usage\n";
        }
    } else {
        if (ev.usageDistance < 50) {
            cout << "Recommendation - Premium EV 25L+: Hyundai Ioniq 5 or Kia EV6\n";
        } else {
            cout << "Recommendation - Premium EV 25L+: Volvo XC40 Recharge or BMW iX1\n";
        }
    }
}

void collectStats() {
    int year, month, vehicleType;
    cout << "Enter year - ";
    cin >> year;
    cout << "Enter month (1-12) - ";
    cin >> month;
    cout << "Enter vehicle type (2 for 2W, 3 for 3W, 4 for 4W) - ";
    cin >> vehicleType;

    ofstream fout("ev_stats.csv", ios::app);
    if (fout.is_open()) {
        fout << year << "," << month << "," << vehicleType << "\n";
        fout.close();
        cout << "Data saved. Load this CSV into Power BI to view visualizations.\n";
    } else {
        cout << "Failed to open file.\n";
    }
}

int main() {
    char choice;
    cout << "**** Welcome to the EV Application ****\n";
    cout << "Enter 'R' to run the EV Recommender or 'S' to enter statistics mode - ";
    cin >> choice;

    if (choice == 'R' || choice == 'r') {
        EVData ev;
        recommendEV(ev);
    } else if (choice == 'S' || choice == 's') {
        collectStats();
    } else {
        cout << "Invalid input. Exiting.\n";
    }

    return 0;
}

