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
void modifyContact(const string& name) {
    vector<Contact> contacts = loadContacts();
    bool found = false;

    for (auto& contact : contacts) {
        if (contact.name == name) {
            cout << "Contact found. Enter new details:\n";
            cout << "New Name: ";
            getline(cin, contact.name);
            cout << "New Phone: ";
            getline(cin, contact.phone);
            cout << "New Email: ";
            getline(cin, contact.email);
            found = true;
            break;
        }
    }

    if (found) {
        ofstream file("contacts.txt", ios::trunc);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.name << "," << contact.phone << "," << contact.email << "\n";
            }
            file.close();
            cout << "Contact modified successfully.\n";
        } else {
            cout << "Error: Unable to open file for writing.\n";
        }
    } else {
        cout << "Contact not found.\n";
    }
}

void displayContacts() {
    vector<Contact> contacts = loadContacts();
    if (contacts.empty()) {
        cout << "No contacts found.\n";
    } else {
        cout << "Contacts:\n";
        for (const auto& contact : contacts) {
            cout << "Name: " << contact.name << ", Phone: " << contact.phone << ", Email: " << contact.email << "\n";
        }
    }
}
int main() {
    int choice;
   do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Modify Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: {
                Contact contact;
                cout << "Enter Name: ";
                getline(cin, contact.name);
                cout << "Enter Phone: ";
                getline(cin, contact.phone);
                cout << "Enter Email: ";
                getline(cin, contact.email);
                saveContact(contact);
                break;
            }
            case 2: {
                string name;
                cout << "Enter Name to Search: ";
                getline(cin, name);
                searchContact(name);
                break;
            }
            case 3: {
                string name;
                cout << "Enter Name to Modify: ";
                getline(cin, name);
                modifyContact(name);
                break;
            }
            case 4:
                displayContacts();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0; 

}



