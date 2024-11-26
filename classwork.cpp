#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Employee {
public:
    int id;
    std::string name;
    std::string position;

    void display() const {
        std::cout << "ID: " << id << ", Name: " << name << ", Position: " << position << std::endl;
    }

    std::string to_string() const {
        return std::to_string(id) + "," + name + "," + position;
    }

    void from_string(const std::string& str) {
        size_t pos1 = str.find(',');
        size_t pos2 = str.find(',', pos1 + 1);
        id = std::stoi(str.substr(0, pos1));
        name = str.substr(pos1 + 1, pos2 - pos1 - 1);
        position = str.substr(pos2 + 1);
    }
};

class EmployeeManager {
    std::vector<Employee> employees;

public:
    void add(const Employee& emp) {
        for (const auto& e : employees) {
            if (e.id == emp.id) {
                std::cerr << "Employee with ID " << emp.id << " already exists.\n";
                return;
            }
        }
        employees.push_back(emp);
    }

    void editById(int id, const Employee& newEmp) {
        for (auto& e : employees) {
            if (e.id == id) {
                e = newEmp;
                return;
            }
        }
        std::cerr << "Employee with ID " << id << " not found.\n";
    }

    void editByName(const std::string& name, const Employee& newEmp) {
        for (auto& e : employees) {
            if (e.name == name) {
                e = newEmp;
                return;
            }
        }
        std::cerr << "Employee with name " << name << " not found.\n";
    }

    Employee* searchById(int id) {
        for (auto& e : employees) {
            if (e.id == id) {
                return &e;
            }
        }
        std::cerr << "Employee with ID " << id << " not found.\n";
        return nullptr;
    }

    Employee* searchByName(const std::string& name) {
        for (auto& e : employees) {
            if (e.name == name) {
                return &e;
            }
        }
        std::cerr << "Employee with name " << name << " not found.\n";
        return nullptr;
    }

    void showAll() const {
        for (const auto& e : employees) {
            e.display();
        }
    }

    void sortById() {
        std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
            return a.id < b.id;
        });
    }

    void sortByName() {
        std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
            return a.name < b.name;
        });
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& e : employees) {
                file << e.to_string() << "\n";
            }
            file.close();
        } else {
            std::cerr << "Unable to open file for writing.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            employees.clear();
            std::string line;
            while (std::getline(file, line)) {
                Employee emp;
                emp.from_string(line);
                employees.push_back(emp);
            }
            file.close();
        } else {
            std::cerr << "Unable to open file for reading.\n";
        }
    }
};

void displayMenu() {
    std::cout << "1. Show all information\n";
    std::cout << "2. Add (id cannot duplicate)\n";
    std::cout << "3. Edit\n";
    std::cout << "    1. Edit by id\n";
    std::cout << "    2. Edit by name\n";
    std::cout << "4. Search\n";
    std::cout << "    1. Search by id\n";
    std::cout << "    2. Search by name\n";
    std::cout << "5. Sort\n";
    std::cout << "    1. Sort by id\n";
    std::cout << "    2. Sort by name\n";
    std::cout << "6. Save data to file\n";
    std::cout << "7. Load data from file\n";
    std::cout << "8. Exit\n";
}

int main() {
    EmployeeManager manager;
    int choice;
    
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                manager.showAll();
                break;
            }
            case 2: {
                Employee emp;
                std::cout << "Enter ID, Name, Position: ";
                std::cin >> emp.id >> emp.name >> emp.position;
                manager.add(emp);
                break;
            }
            case 3: {
                int subchoice;
                std::cout << "1. Edit by ID\n2. Edit by Name\n";
                std::cout << "Enter your choice: ";
                std::cin >> subchoice;
                if (subchoice == 1) {
                    int id;
                    Employee emp;
                    std::cout << "Enter ID to edit: ";
                    std::cin >> id;
                    std::cout << "Enter new ID, Name, Position: ";
                    std::cin >> emp.id >> emp.name >> emp.position;
                    manager.editById(id, emp);
                } else if (subchoice == 2) {
                    std::string name;
                    Employee emp;
                    std::cout << "Enter Name to edit: ";
                    std::cin >> name;
                    std::cout << "Enter new ID, Name, Position: ";
                    std::cin >> emp.id >> emp.name >> emp.position;
                    manager.editByName(name, emp);
                }
                break;
            }
            case 4: {
                int subchoice;
                std::cout << "1. Search by ID\n2. Search by Name\n";
                std::cout << "Enter your choice: ";
                std::cin >> subchoice;
                if (subchoice == 1) {
                    int id;
                    std::cout << "Enter ID to search: ";
                    std::cin >> id;
                    Employee* emp = manager.searchById(id);
                    if (emp) emp->display();
                } else if (subchoice == 2) {
                    std::string name;
                    std::cout << "Enter Name to search: ";
                    std::cin >> name;
                    Employee* emp = manager.searchByName(name);
                    if (emp) emp->display();
                }
                break;
            }
            case 5: {
                int subchoice;
                std::cout << "1. Sort by ID\n2. Sort by Name\n";
                std::cout << "Enter your choice: ";
                std::cin >> subchoice;
                if (subchoice == 1) {
                    manager.sortById();
                } else if (subchoice == 2) {
                    manager.sortByName();
                }
                break;
            }
            case 6: {
                std::string filename;
                std::cout << "Enter filename to save: ";
                std::cin >> filename;
                manager.saveToFile(filename);
                break;
            }
            case 7: {
                std::string filename;
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                manager.loadFromFile(filename);
                break;
            }
            case 8: {
                std::cout << "Exiting...\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } while (choice != 8);

    return 0;
}


