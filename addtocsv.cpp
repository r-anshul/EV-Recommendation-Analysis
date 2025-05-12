#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void addVehicleToCSV()
{
    ofstream file("ev_data.csv", ios::app);
    if (!file.is_open())
    {
        cout << "Error - Could not open the file for appending.\n";
        return;
    }
    while(true)
	{
        int cont;
        string vehicleType, brand, model;
        int budgetMin, budgetMax, rangeMin, rangeMax, maintenance,ctime;
        cout << "\nEnter Vehicle Type (2-wheeler, 3-wheeler, or 4-wheeler) - ";
        cin.ignore();
        getline(cin, vehicleType);
        cout << "Enter Brand - ";
        getline(cin, brand);
        cout << "Enter Model - ";
        getline(cin, model);
        cout << "Enter Minimum Budget (in Rs) - ";
        cin >> budgetMin;
        cout << "Enter Maximum Budget (in Rs) - ";
        cin >> budgetMax;
        cout << "Enter Minimum Range (in km) - ";
        cin >> rangeMin;
        cout << "Enter Maximum Range (in km) - ";
        cin >> rangeMax;
        cout << "Enter Estimated Monthly Maintenance Cost (in Rs) - ";
        cin >> maintenance;
        cout << "Enter Charging time (in hours) - ";
        cin >> ctime;
        file<<vehicleType<<","<<brand<<","<<model<<","<<budgetMin<<","<<budgetMax<<","<<rangeMin<<","<<rangeMax<<","<<maintenance<<","<<ctime<<"\n";
        cout << "Vehicle added successfully.\n";
        cout << "Press 0 to stop or 1 to add another vehicle - ";
        cin >> cont;
        if
			(cont == 0)
		break;
    }
    file.close();
    cout << "All entries saved to ev_data.csv.\n";
}
int main()
{
    cout << "**** EV Data Entry Tool ****\n";
    addVehicleToCSV();
    return 0;
}
