#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void recommendEVModels(int budget, int usage) {
    cout << "Recommended EV Models based on your inputs-\n";
    if (budget <= 1500000 && usage <= 50) {
        cout << "- Tata Tiago EV (Maintenance- ?200–?300/month)\n";
        cout << "- MG Comet EV (Maintenance- ?250–?350/month)\n";
    } else if (budget <= 1500000 && usage > 50) {
        cout << "- Tata Nexon EV (Maintenance- ?300–?400/month)\n";
        cout << "- Mahindra XUV400 (Maintenance- ?350–?450/month)\n";
    } else if (budget <= 2500000 && usage <= 50) {
        cout << "- MG ZS EV (Maintenance- ?400–?500/month)\n";
        cout << "- Hyundai Kona Electric (Maintenance- ?450–?550/month)\n";
    } else if (budget <= 2500000 && usage > 50) {
        cout << "- BYD Atto 3 (Maintenance- ?500–?600/month)\n";
        cout << "- Hyundai Kona Electric (Maintenance- ?450–?550/month)\n";
    } else {
        cout << "- Kia EV6 (Maintenance- ?700–?900/month)\n";
        cout << "- Volvo XC40 Recharge (Maintenance- ?800–?1000/month)\n";
    }
}

void enterStatistics() {
    ofstream file("ev_statistics.csv", ios::app);
    if (!file) {
        cout << "Error- Could not open the file for writing.\n";
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
        int budget, usage;
        cout << "Enter your budget (in INR) - ";
        cin >> budget;
        cout << "Enter your average daily usage (in km) - ";
        cin >> usage;
        recommendEVModels(budget, usage);
    } else if (choice == 2) {
        enterStatistics();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}

