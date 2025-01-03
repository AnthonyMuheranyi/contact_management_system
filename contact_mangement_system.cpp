#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

void saveContact(const Contact& contact) {
    ofstream file("contacts.txt", ios::app);
    if (file.is_open()) {
        file << contact.name << "," << contact.phone << "," << contact.email << "\n";
        file.close();
        cout << "Contact saved successfully.\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
}
vector<Contact> loadContacts() {
    vector<Contact> contacts;
    ifstream file("contacts.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, phone, email;
            getline(ss, name, ',');
            getline(ss, phone, ',');
            getline(ss, email, ',');
            contacts.push_back({name, phone, email});
        }
        file.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
    return contacts;
}
void searchContact(const string& name) {
    vector<Contact> contacts = loadContacts();
    bool found = false;
    for (const auto& contact : contacts) {
        if (contact.name == name) {
            cout << "Contact found:\n";
            cout << "Name: " << contact.name << "\n";
            cout << "Phone: " << contact.phone << "\n";
            cout << "Email: " << contact.email << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Contact not found.\n";
    }
}

