
#include <iostream>

using namespace std;

const int MAX_FLOORS = 10;
const int MAX_TENANTS_PER_FLOOR = 2;

// Forward declarations
class Tenant;
class BillManager;
class Flat;
class Building;

// Class for managing bills
class BillManager {
    friend class Flat;
    friend class Building;
    friend class Tenant;

    float electricityRate = 7.55;
    float gasRate = 1500.0;
    float waterRate = 300.0;
    float maintenanceCost = 0.0;
    float houseRent = 25000.0;

public:
    // Function to calculate electricity bill
    float calculateElectricityBill(float units) {
        return units * electricityRate;
    }
};

// Class representing a Tenant
class Tenant {
    friend class Flat;
    friend class Building;
    friend class BillManager;

    int id;
    string name;
    int length;
    int width;
    int roomCount;
    float maintenanceCost;
    float rent;

public:
    Tenant() : maintenanceCost(0.0), rent(0.0) {}

    // Function to add a new tenant
    void addTenant() {
        cout << "\nEnter tenant ID: ";
        cin >> id;
        cout << "\nEnter tenant name: ";
        cin.ignore();
        getline(cin, name);
        cout << "\nEnter flat length: ";
        cin >> length;
        cout << "\nEnter flat width: ";
        cin >> width;
        cout << "\nEnter room count: ";
        cin >> roomCount;
    }

    // Function to generate the tenant's bill
    void generateBill(BillManager& billManager) {
        cout << "\nHow many units of electricity did the tenant use? : ";
        float units;
        cin >> units;

        maintenanceCost = length * width * 10.0; // maintenance cost is based on apartment size

        float electricityBill = billManager.calculateElectricityBill(units);
        float totalRent = maintenanceCost + electricityBill + billManager.gasRate + billManager.waterRate + billManager.houseRent;
        rent = totalRent;

        cout << "\n\n";
        cout << "\nMaintenance cost: " << maintenanceCost;
        cout << "\nElectricity bill: " << electricityBill;
        cout << "\nGas bill: " << billManager.gasRate;
        cout << "\nWater bill: " << billManager.waterRate;
        cout << "\nHouse rent: " << billManager.houseRent;
        cout << "\n\nTotal rent: " << rent;
        cout << "\n\n";
    }

    // Function to show tenant details
    void showTenant() {
        cout << "\n";
        cout << "\nTenant ID: " << id;
        cout << "\nTenant name: " << name;
        cout << "\nApartment length: " << length << " ft.";
        cout << "\nApartment width: " << width << " ft.";
        cout << "\nApartment size: " << length * width << " sq. ft.";
        cout << "\nApartment no. of rooms: " << roomCount;
        cout << "\nMaintenance cost: " << maintenanceCost;
        cout << "\nRent: " << rent;
        cout << "\n\n";
    }
};

// Class representing a Flat
class Flat {
    friend class Building;
    friend class BillManager;
    friend class Tenant;

    int id;
    Tenant tenants[MAX_TENANTS_PER_FLOOR];
    int numTenants;

public:
    Flat() : numTenants(0) {}

    // Function to add a new tenant to the flat
    void addTenant() {
        if (numTenants >= MAX_TENANTS_PER_FLOOR) {
            cout << "\nFLAT FULL!";
            return;
        }
        Tenant newTenant;
        newTenant.addTenant();
        tenants[numTenants++] = newTenant;
        cout << "\nTENANT ADDED SUCCESSFULLY.";
    }

    // Function to generate bill for a specific tenant in the flat
    void generateBill(BillManager& billManager, int tenantID) {
        for (int i = 0; i < numTenants; i++) {
            if (tenants[i].id == tenantID) {
                tenants[i].generateBill(billManager);
                return;
            }
        }
        cout << "\nTENANT NOT FOUND!";
    }

    // Function to show details of a specific tenant in the flat
    void showTenant(int tenantID) {
        for (int i = 0; i < numTenants; i++) {
            if (tenants[i].id == tenantID) {
                tenants[i].showTenant();
                return;
            }
        }
        cout << "\nTENANT NOT FOUND!";
    }
};

// Class representing a Building
class Building {
    friend class Flat;
    friend class BillManager;
    friend class Tenant;

    int id;
    int floors;
    Flat flats[MAX_FLOORS * MAX_TENANTS_PER_FLOOR];
    int numFlats;

public:
    Building(int id, int floors) : id(id), floors(floors), numFlats(0) {}

    // Function to add a new flat to the building
    void addFlat() {
        if (numFlats >= MAX_FLOORS * MAX_TENANTS_PER_FLOOR) {
            cout << "\nBUILDING FULL!";
            return;
        }

        Flat newFlat;
        newFlat.addTenant();
        flats[numFlats++] = newFlat;
    }

    // Function to generate bill for a specific tenant in the building
    void generateBill(BillManager& billManager, int tenantID) {
        for (int i = 0; i < numFlats; i++) {
            flats[i].generateBill(billManager, tenantID);
        }
    }

    // Function to show details of a specific tenant in the building
    void showTenant(int tenantID) {
        for (int i = 0; i < numFlats; i++) {
            flats[i].showTenant(tenantID);
        }
    }
};

int main() {
    cout << "Welcome to Property Management System!\n";
    cout << "\nEnter building ID: ";
    int id;
    cin >> id;
    cout << "\nEnter number of floors: ";
    int floors;
    cin >> floors;

    Building building(id, floors);
    BillManager billManager;

    while (true) {
        cout << "\nChoose an action: \n 1. Add Tenant\n 2. Generate Bill\n 3. Show Tenant Details\n 4. Exit\n\nEnter the option number: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                building.addFlat();
                break;
            case 2: {
                cout << "Enter Tenant ID: ";
                int tenantID;
                cin >> tenantID;
                building.generateBill(billManager, tenantID);
                break;
            }
            case 3: {
                cout << "Enter Tenant ID: ";
                int tenantID;
                cin >> tenantID;
                building.showTenant(tenantID);
                break;
            }
            case 4:
                cout << "Exiting the Property Management System. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
