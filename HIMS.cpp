#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>

class SparePart {
public:
    std::string name;
    int number;
    double cost;
    int quantity;

    void setdata(const std::string& name, int number, double cost, int quantity) {
        this->name = name;
        this->number = number;
        this->cost = cost;
        this->quantity = quantity;
    }

    void display() const {
        std::cout << "Part Name: " << name << "\n"
                  << "Part Number: " << number << "\n"
                  << "Cost: " << cost << "\n"
                  << "Quantity: " << quantity << "\n";
    }
};

class Supplier {
public:
    std::string name;
    int code;
    std::string address;
    std::string phone;
    std::string email;

    void setdata(const std::string& name, int code, const std::string& address, const std::string& phone , const std::string& email) {
        this->name = name;
        this->code = code;
        this->address = address;
        this->phone = phone;
        this->email = email;
    }

    void display() const {
        std::cout << "Supplier Name: " << name << "\n"
                  << "Supplier Code: " << code << "\n"
                  << "Address: " << address << "\n"
                  << "Phone: " << phone << "\n"
                  << "Email: " << email << "\n";
    }
};

class HIMS {
private:
    std::unordered_map<int, SparePart> spareParts;
    std::unordered_map<int, Supplier> suppliers;  
    std::unordered_map<int, std::vector<int>> partToSuppliers;
    std::unordered_map<int, std::vector<int>> supplierToParts;
    std::stack<std::string> history;
    std::set<int> sparePartNumbers;
    std::set<int> supplierCodes;

public:
    void addSparePart(const SparePart& part) {
        if (spareParts.size() >= 100) {
            std::cout << "Cannot add more than 100 spare parts.\n";
            return;
        }
        if (spareParts.find(part.number) == spareParts.end()) {
            spareParts[part.number] = part;
            sparePartNumbers.insert(part.number);
            history.push("Added Spare Part number " + std::to_string(part.number));
        } else {
            std::cout << "Spare Part with this number already exists.\n";
        }
    }

    void addSupplier(const Supplier& supplier) {
        if (suppliers.size() >= 20) {
            std::cout << "Cannot add more than 20 suppliers.\n";
            return;
        }
        if (suppliers.find(supplier.code) == suppliers.end()) {
            suppliers[supplier.code] = supplier;
            supplierCodes.insert(supplier.code);
            history.push("Added Supplier code " + std::to_string(supplier.code));
        } else {
            std::cout << "Supplier with this code already exists.\n";
        }
    }

    void linkSparePartWithSupplier(int sparepartNumber, int supplierCode) {
        if (spareParts.find(sparepartNumber) == spareParts.end()) {
            std::cout << "Spare Part with this number does not exist.\n";
            return;
        }
        if (suppliers.find(supplierCode) == suppliers.end()) {
            std::cout << "Supplier with this code does not exist.\n";
            return;
        }
        partToSuppliers[sparepartNumber].push_back(supplierCode);
        supplierToParts[supplierCode].push_back(sparepartNumber);
        history.push("Linked Spare Part number " + std::to_string(sparepartNumber) + " with Supplier code " + std::to_string(supplierCode));
    }

    void displaySpareParts() const {
        for (const auto& [number, part] : spareParts) {
            part.display();
            std::cout << "Suppliers: ";
            if (partToSuppliers.find(number) != partToSuppliers.end()) {
                for (int code : partToSuppliers.at(number)) {
                    std::cout << code << " ";
                }
            }
            std::cout << "\n";
        }
    }

    void displaySuppliers() const {
        for (const auto& [code, supplier] : suppliers) {
            supplier.display();
            std::cout << "Supplies Parts: ";
            if (supplierToParts.find(code) != supplierToParts.end()) {
                for (int number : supplierToParts.at(code)) {
                    std::cout << number << " ";
                }
            }
            std::cout << "\n";
        }
    }

    void printHistory() const {
        std::stack<std::string> temp = history;
        while (!temp.empty()) {
            std::cout << temp.top() << "\n";
            temp.pop();
        }
    }

    bool partNumberExists(int number) const {
        return spareParts.find(number) != spareParts.end();
    }

    bool supplierCodeExists(int code) const {
        return suppliers.find(code) != suppliers.end();
    }

    void searchSparePartByNumber(int partNumber) const {
        auto it = spareParts.find(partNumber);
        if (it != spareParts.end()) {
            std::cout << "Spare Part found:\n";
            it->second.display();
            std::cout << "Suppliers: ";
            if (partToSuppliers.find(partNumber) != partToSuppliers.end()) {
                for (int code : partToSuppliers.at(partNumber)) {
                    std::cout << code << " ";
                }
            }
            std::cout << "\n";
        } else {
            std::cout << partNumber << " not found.\n";
        }
    }

    void searchSupplierByCode(int supplierCode) const {
        auto it = suppliers.find(supplierCode);
        if (it != suppliers.end()) {
            std::cout << "Supplier found:\n";
            it->second.display();
            std::cout << "Supplies Parts: ";
            if (supplierToParts.find(supplierCode) != supplierToParts.end()) {
                for (int number : supplierToParts.at(supplierCode)) {
                    std::cout << number << " ";
                }
            }
            std::cout << "\n";
        } else {
            std::cout << supplierCode << " not found.\n";
        }
    }
};
int main() {
    HIMS hims;
    int choice;

    do {
        std::cout << "1. Add Spare Part\n"
                  << "2. Add Supplier\n"
                  << "3. Link Spare Part with Supplier\n"
                  << "4. Display Spare Parts\n"
                  << "5. Display Suppliers\n"
                  << "6. Print History\n"
                  << "7. Search for Spare Part by Number\n"
                  << "8. Search for Supplier by Code\n"
                  << "9. Cancel\n"
                  << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1: {
                if (hims.partNumberExists(100)) {
                    std::cout << "Maximum spare parts limit reached.\n";
                    break;
                }
                SparePart part;
                std::string name;
                int number;
                double cost;
                int quantity;

                std::cout << "Enter part name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter part number: ";
                std::cin >> number;
                if (hims.partNumberExists(number)) {
                    std::cout << "Part number already exists. Enter another part number.\n";
                    break;
                }
                std::cout << "Enter cost: ";
                std::cin >> cost;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                part.setdata(name, number, cost, quantity);
                hims.addSparePart(part);
                break;
            }
            case 2: {
                if (hims.supplierCodeExists(20)) {
                    std::cout << "Maximum suppliers limit reached.\n";
                    break;
                }
                Supplier supplier;
                std::string name, address, phone, email;
                int code;

                std::cout << "Enter supplier name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter supplier code: ";
                std::cin >> code;
                if (hims.supplierCodeExists(code)) {
                    std::cout << "Supplier code already exists. Try again.\n";
                    break;
                }
                std::cout << "Enter address: ";
                std::cin.ignore();
                std::getline(std::cin, address);
                std::cout << "Enter phone: ";
                std::getline(std::cin, phone);
                std::cout << "Enter email: ";
                std::getline(std::cin, email);

                supplier.setdata(name, code, address, phone, email);
                hims.addSupplier(supplier);
                break;
            }
            case 3: {
                int partNumber, supplierCode;

                std::cout << "Enter part number: ";
                std::cin >> partNumber;
                std::cout << "Enter supplier code: ";
                std::cin >> supplierCode;

                hims.linkSparePartWithSupplier(partNumber, supplierCode);
                break;
            }
            case 4: {
                hims.displaySpareParts();
                break;
            }
            case 5: {
                hims.displaySuppliers();
                break;
            }
            case 6: {
                hims.printHistory();
                break;
            }
            case 7: {
                int partNumber;
                std::cout << "Enter part number to search: ";
                std::cin >> partNumber;
                hims.searchSparePartByNumber(partNumber);
                break;
            }
            case 8: {
                int supplierCode;
                std::cout << "Enter supplier code to search: ";
                std::cin >> supplierCode;
                hims.searchSupplierByCode(supplierCode);
                break;
            }
            case 9: {
                std::cout << "done\n";
                break;
            }
            default: {
                std::cout << "Invalid choice,try again.\n";
                break;
            }
        }
    } while (choice != 9);
    return 0;
}