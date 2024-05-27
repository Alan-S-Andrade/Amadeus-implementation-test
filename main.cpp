// Amadeus - Assessment - Alan Andrade

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "employee.h"
#include "tinyxml2.h"
#include "nlohmann/json.hpp"

using namespace tinyxml2;

// Methods to parse data for each format (XML/JSON)

std::vector<Employee> parseXML(const std::string &filename) {
    std::vector<Employee> employees;
    XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) == XML_SUCCESS) {
        XMLElement *root = doc.RootElement();
        for (XMLElement *elem = root->FirstChildElement("employee"); elem != nullptr; elem = elem->NextSiblingElement("employee")) {
            Employee emp;
            emp.name = elem->FirstChildElement("name")->GetText();
            emp.id = std::stoi(elem->FirstChildElement("id")->GetText());
            emp.department = elem->FirstChildElement("department")->GetText();
            emp.salary = std::stod(elem->FirstChildElement("salary")->GetText());
            employees.push_back(emp);
        }
    } else {
        std::cerr << "Failed to load XML file: " << filename << std::endl;
    }
    return employees;
}

std::vector<Employee> parseJSON(const std::string &filename) {
    std::vector<Employee> employees;
    std::ifstream file(filename);
    if (file.is_open()) {
        nlohmann::json j;
        file >> j;
        for (const auto &item : j["employees"]) {
            Employee emp;
            emp.name = item["name"];
            emp.id = item["id"];
            emp.department = item["department"];
            emp.salary = item["salary"];
            employees.push_back(emp);
        }
    } else {
        std::cerr << "Failed to open JSON file: " << filename << std::endl;
    }
    return employees;
}

void calculateAndDisplayResults(const std::vector<Employee> &employees) {
    if (employees.empty()) {
        std::cerr << "No employees found." << std::endl;
        return;
    }

    double totalSalary = std::accumulate(employees.begin(), employees.end(), 0.0, 
        [](double sum, const Employee &emp) { return sum + emp.salary; });
    double averageSalary = totalSalary / employees.size();

    auto highestPaidIt = std::max_element(employees.begin(), employees.end(), 
        [](const Employee &a, const Employee &b) { return a.salary < b.salary; });

    std::vector<Employee> sortedEmployees = employees;
    std::sort(sortedEmployees.begin(), sortedEmployees.end(), 
        [](const Employee &a, const Employee &b) { return a.id < b.id; });

    std::cout << "Average Salary: " << averageSalary << std::endl;
    std::cout << "Highest Paid Employee: " << highestPaidIt->name 
              << ", ID: " << highestPaidIt->id 
              << ", Department: " << highestPaidIt->department 
              << ", Salary: " << highestPaidIt->salary << std::endl;

    std::cout << "Employees sorted by ID:" << std::endl;
    for (const auto &emp : sortedEmployees) {
        std::cout << "Name: " << emp.name 
                  << ", ID: " << emp.id 
                  << ", Department: " << emp.department 
                  << ", Salary: " << emp.salary << std::endl;
    }
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <xml|json> <filename>" << std::endl;
        return 1;
    }

    std::string format = argv[1];
    std::string filename = argv[2];
    std::vector<Employee> employees;

    if (format == "xml") {
        employees = parseXML(filename);
    } else if (format == "json") {
        employees = parseJSON(filename);
    } else {
        std::cerr << "Unsupported format: " << format << std::endl;
        return 1;
    }

    calculateAndDisplayResults(employees);
    return 0;
}