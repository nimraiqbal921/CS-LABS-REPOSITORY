#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

// Contact Class 
class ItemType {
private:
    string name;
    string phone;
    string address;

    bool nameOnlyAlphabets(string str) {
        if (str.empty()) return false;
        for (int i = 0; str[i] != '\0'; i++) {
            char c = str[i];
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' '))
                return false;
        }
        return true;
    }

    bool isValidPhoneNumber(string str) {
        if (str.length() != 6) return false;  
        for (int i = 0; str[i] != '\0'; i++) {
            if (!(str[i] >= '0' && str[i] <= '9')) return false;
        }
        return true;
    }

    bool isValidAddress(string str) {
        return !str.empty();
    }

public:
    bool SetContact(string n, string p, string a) {
        if (!nameOnlyAlphabets(n)) { cout << "Invalid name!\n"; return false; }
        if (!isValidPhoneNumber(p)) { cout << "Invalid phone number!\n"; return false; }
        if (!isValidAddress(a)) { cout << "Invalid address!\n"; return false; }

        name = n; phone = p; address = a;
        return true;
    }

    string GetName() { return name; }
    string GetPhone() { return phone; }
    string GetAddress() { return address; }

    void PrintContact() {
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "--------------------\n";
    }
};

// Sorted Contact List
class SortedList {
private:
    ItemType list[MAX_SIZE];
    int length;

public:
    SortedList() { length = 0; }

    bool IsFull() { return length == MAX_SIZE; }
    ItemType GetContactAt(int index) { return list[index]; }
    string GetNameAt(int index) { return list[index].GetName(); }
    int GetLength() { return length; }

    bool Add(ItemType newContact) {
        if (IsFull()) return false;
        int pos = 0;
        while (pos < length && newContact.GetName() > list[pos].GetName()) pos++;
        for (int i = length; i > pos; i--) list[i] = list[i - 1];
        list[pos] = newContact;
        length++;
        return true;
    }

    int Search(string name) {
        for (int i = 0; i < length; i++) {
            if (list[i].GetName() == name) return i;
        }
        return -1;
    }

    bool Delete(string name) {
        int pos = Search(name);
        if (pos == -1) return false;
        for (int i = pos; i < length - 1; i++) list[i] = list[i + 1];
        length--;
        return true;
    }

    void DisplayAll() {
        if (length == 0) { cout << "No contacts to display.\n"; return; }
        for (int i = 0; i < length; i++) list[i].PrintContact();
    }

    // ========== File Handling ==========
    void SaveToFile() {
        ofstream fout("ContactNumbers.txt"); 
        for (int i = 0; i < length; i++) {
            fout << list[i].GetName() << endl;
            fout << list[i].GetPhone() << endl;
            fout << list[i].GetAddress() << endl;
        }
        fout.close();
    }

    void LoadFromFile() {
        length = 0;
        ifstream fin("ContactNumbers.txt");
        if (!fin) return;  // file not found
        string n, p, a;
        while (getline(fin, n) && getline(fin, p) && getline(fin, a)) {
            ItemType c;
            if (c.SetContact(n, p, a)) Add(c);
        }
        fin.close();
    }
};

// ========== MENU ==========
int main() {
    SortedList contacts;
    contacts.LoadFromFile(); // load contacts at start

    int choice;
    do {
        cout << "\n===== Contact Manager =====\n";
        cout << "1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Display All\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // ignore newline

        switch (choice) {
            case 1: {
                string n, p, a;
                cout << "Enter name: "; getline(cin, n);
                cout << "Enter phone: "; getline(cin, p);
                cout << "Enter address: "; getline(cin, a);
                ItemType c;
                if (c.SetContact(n, p, a)) {
                    contacts.Add(c);
                    contacts.SaveToFile();
                    cout << "Contact added successfully.\n";
                }
                break;
            }
            case 2: {
                string n;
                cout << "Enter name to search: "; getline(cin, n);
                int pos = contacts.Search(n);
                if (pos != -1) {
                    cout << "Contact found:\n";
                    for (int i = 0; i < contacts.GetLength(); i++) {
                        if (contacts.GetNameAt(i) == n) {
                            contacts.GetContactAt(i).PrintContact();
                            break;
                        }
                    }
                } else cout << "Contact not found.\n";
                break;
            }
            case 3: {
                string n;
                cout << "Enter name to delete: "; getline(cin, n);
                if (contacts.Delete(n)) {
                    contacts.SaveToFile();
                    cout << "Contact deleted.\n";
                } else cout << "Contact not found.\n";
                break;
            }
            case 4:
                contacts.DisplayAll();
                break;
            case 5:
                cout << "Exiting...\n"; break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
