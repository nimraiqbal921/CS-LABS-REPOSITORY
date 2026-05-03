#include <iostream>
#include <vector>
#include <string>
using namespace std;

class libraryresource {
protected:
    int resource_id;
    string title;
    string author;
    bool is_available;

public:
    libraryresource(int id, string t, string a, bool avail) {
        // this pointer usage 1: distinguishing member variables from parameters
        this->resource_id = id;
        this->title = t;
        this->author = a;
        this->is_available = avail;
    }

    int get_resource_id() { return resource_id; }
    string get_title() { return title; }
    string get_author() { return author; }
    bool get_availability() { return is_available; }

    void set_resource_id(int id) { resource_id = id; }
    void set_title(string t) { title = t; }
    void set_author(string a) { author = a; }
    void set_availability(bool avail) { is_available = avail; }

    void display_details() {
        cout << "id: " << resource_id << endl;
        cout << "title: " << title << endl;
        cout << "author: " << author << endl;
        cout << "available: " << (is_available ? "yes" : "no") << endl;
    }

    int calculate_late_fee(int days_late) {
        return 0;
    }
};


class book : public libraryresource {
    string isbn;
    int page_count;

public:
    book(int id, string t, string a, bool avail, string i, int pages)
        : libraryresource(id, t, a, avail) {
        isbn = i;
        page_count = pages;
    }

    string get_isbn() { return isbn; }
    int get_page_count() { return page_count; }
    void set_isbn(string i) { isbn = i; }
    void set_page_count(int pages) { page_count = pages; }

    // function hiding: hides libraryresource::calculate_late_fee()
    int calculate_late_fee(int days_late) {
        return days_late * 5;
    }

    void display_details() {
        cout << "type: book" << endl;
        libraryresource::display_details();
        cout << "isbn: " << isbn << endl;
        cout << "pages: " << page_count << endl;
    }
};


class magazine : public libraryresource {
    int issue_number;

public:
    magazine(int id, string t, string a, bool avail, int issue)
        : libraryresource(id, t, a, avail) {
        issue_number = issue;
    }

    int get_issue_number() { return issue_number; }
    void set_issue_number(int issue) { issue_number = issue; }

    // function hiding: hides libraryresource::calculate_late_fee()
    int calculate_late_fee(int days_late) {
        return days_late * 3;
    }

    void display_details() {
        cout << "type: magazine" << endl;
        libraryresource::display_details();
        cout << "issue: " << issue_number << endl;
    }
};


class dvd : public libraryresource {
    int duration;

public:
    dvd(int id, string t, string a, bool avail, int d)
        : libraryresource(id, t, a, avail) {
        duration = d;
    }

    int get_duration() { return duration; }
    void set_duration(int d) { duration = d; }

    // function hiding: hides libraryresource::calculate_late_fee()
    int calculate_late_fee(int days_late) {
        return days_late * 10;
    }

    void display_details() {
        cout << "type: dvd" << endl;
        libraryresource::display_details();
        cout << "duration: " << duration << " min" << endl;
    }
};


class librarymember {
    int member_id;
    string name;
    // composition: borrowed_items stored by value ,will be destroyed when member is destroyed
    vector<libraryresource> borrowed_items;

public:
    librarymember(int id, string n) {
        member_id = id;
        name = n;
    }

    int get_member_id() { return member_id; }
    string get_name() { return name; }

    void set_member_id(int id) { member_id = id; }

    // this pointer usage no 2  returning current object to allow method chaining
    librarymember& set_name(string n) {
        this->name = n;
        return *this;
    }

    void add_borrowed_item(libraryresource res) {
        borrowed_items.push_back(res);
    }

    bool has_borrowed(int rid) {
        for (int i = 0; i < borrowed_items.size(); i++) {
            if (borrowed_items[i].get_resource_id() == rid)
                return true;
        }
        return false;
    }

    bool remove_borrowed_item(int rid) {
        for (int i = 0; i < borrowed_items.size(); i++) {
            if (borrowed_items[i].get_resource_id() == rid) {
                borrowed_items.erase(borrowed_items.begin() + i);
                return true;
            }
        }
        return false;
    }

    void display_borrowed_items() {
        if (borrowed_items.size() == 0) {
            cout << "no borrowed items.\n" << endl;
            return;
        }
        for (int i = 0; i < borrowed_items.size(); i++) {
            borrowed_items[i].display_details();
            cout << "---\n" << endl;
        }
    }

    int calculate_total_late_fee(int days_late) {
        int total = 0;
        for (int i = 0; i < borrowed_items.size(); i++) {
            total += borrowed_items[i].calculate_late_fee(days_late);
        }
        return total;
    }

    friend void admin_view(class library&, vector<librarymember>&);
};


class library {
public:
    vector<book> books;
    vector<magazine> magazines;
    vector<dvd> dvds;

    void add_book(book b) { books.push_back(b); }
    void add_magazine(magazine m) { magazines.push_back(m); }
    void add_dvd(dvd d) { dvds.push_back(d); }

    void display_all() {
        if (books.size() == 0 && magazines.size() == 0 && dvds.size() == 0) {
            cout << "no resources in library.\n" << endl;
            return;
        }
        for (int i = 0; i < books.size(); i++) {
            books[i].display_details();
            cout << "\n" << endl;
        }
        for (int i = 0; i < magazines.size(); i++) {
            magazines[i].display_details();
            cout << "\n" << endl;
        }
        for (int i = 0; i < dvds.size(); i++) {
            dvds[i].display_details();
            cout << "\n" << endl;
        }
    }

    void borrow_resource(int rid, librarymember& member) {
        if (member.has_borrowed(rid)) {
            cout << "already borrowed this resource!\n" << endl;
            return;
        }
        for (int i = 0; i < books.size(); i++) {
            if (books[i].get_resource_id() == rid) {
                if (!books[i].get_availability()) {
                    cout << "resource already borrowed!\n" << endl;
                    return;
                }
                books[i].set_availability(false);
                member.add_borrowed_item(books[i]);
                cout << "borrowed successfully!\n" << endl;
                return;
            }
        }
        for (int i = 0; i < magazines.size(); i++) {
            if (magazines[i].get_resource_id() == rid) {
                if (!magazines[i].get_availability()) {
                    cout << "resource already borrowed!\n" << endl;
                    return;
                }
                magazines[i].set_availability(false);
                member.add_borrowed_item(magazines[i]);
                cout << "borrowed successfully!\n" << endl;
                return;
            }
        }
        for (int i = 0; i < dvds.size(); i++) {
            if (dvds[i].get_resource_id() == rid) {
                if (!dvds[i].get_availability()) {
                    cout << "resource already borrowed!\n" << endl;
                    return;
                }
                dvds[i].set_availability(false);
                member.add_borrowed_item(dvds[i]);
                cout << "borrowed successfully!\n" << endl;
                return;
            }
        }
        cout << "resource not found!\n" << endl;
    }

    void return_resource(int rid, librarymember& member) {
        if (!member.has_borrowed(rid)) {
            cout << "you did not borrow this resource!\n" << endl;
            return;
        }
        member.remove_borrowed_item(rid);
        for (int i = 0; i < books.size(); i++) {
            if (books[i].get_resource_id() == rid) {
                books[i].set_availability(true);
                cout << "returned successfully!\n" << endl;
                return;
            }
        }
        for (int i = 0; i < magazines.size(); i++) {
            if (magazines[i].get_resource_id() == rid) {
                magazines[i].set_availability(true);
                cout << "returned successfully!\n" << endl;
                return;
            }
        }
        for (int i = 0; i < dvds.size(); i++) {
            if (dvds[i].get_resource_id() == rid) {
                dvds[i].set_availability(true);
                cout << "returned successfully!\n" << endl;
                return;
            }
        }
    }

    friend void admin_view(library&, vector<librarymember>&);
};


void admin_view(library& lib, vector<librarymember>& members) {
    cout << "\n admin view\n" << endl;

    cout << "all resources:\n" << endl;
    lib.display_all();

    cout << "all members:\n" << endl;
    if (members.size() == 0) {
        cout << "no members registered.\n" << endl;
    } else {
        for (int i = 0; i < members.size(); i++) {
            cout << "member id: " << members[i].member_id << endl;
            cout << "name: " << members[i].name << endl;
            cout << "borrowed items:" << endl;
            members[i].display_borrowed_items();
            cout << "---\n" << endl;
        }
    }
}


int find_member(vector<librarymember>& members, int mid) {
    for (int i = 0; i < members.size(); i++) {
        if (members[i].get_member_id() == mid)
            return i;
    }
    return -1;
}


int main() {
    library lib;
    vector<librarymember> members;
    int choice;

    do {
        cout << "    library management system\n" << endl;
        cout << "1. add a new resource" << endl;
        cout << "2. register a new member" << endl;
        cout << "3. borrow a resource" << endl;
        cout << "4. return a resource" << endl;
        cout << "5. display all resources" << endl;
        cout << "6. display member's borrowed items" << endl;
        cout << "7. calculate late fee" << endl;
        cout << "8. admin view" << endl;
        cout << "9. exit" << endl;
        cout << "\nenter choice: ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        if (choice == 1) {
            int rtype;
            cout << "select resource type:" << endl;
            cout << "1. book" << endl;
            cout << "2. magazine" << endl;
            cout << "3. dvd" << endl;
            cout << "choice: ";
            cin >> rtype;
            cin.ignore();

            int id;
            string title, author;
            cout << "resource id: "; cin >> id; cin.ignore();
            cout << "title: "; getline(cin, title);
            cout << "author: "; getline(cin, author);

            if (rtype == 1) {
                string isbn;
                int pages;
                cout << "isbn: "; getline(cin, isbn);
                cout << "pages: "; cin >> pages; cin.ignore();
                lib.add_book(book(id, title, author, true, isbn, pages));
                cout << "book added successfully!\n" << endl;
            } else if (rtype == 2) {
                int issue;
                cout << "issue number: "; cin >> issue; cin.ignore();
                lib.add_magazine(magazine(id, title, author, true, issue));
                cout << "magazine added successfully!\n" << endl;
            } else if (rtype == 3) {
                int duration;
                cout << "duration (min): "; cin >> duration; cin.ignore();
                lib.add_dvd(dvd(id, title, author, true, duration));
                cout << "dvd added successfully!\n" << endl;
            } else {
                cout << "invalid resource type!\n" << endl;
            }
        }

        else if (choice == 2) {
            int id;
            string name;
            cout << "member id: "; cin >> id; cin.ignore();
            cout << "name: "; getline(cin, name);
            if (find_member(members, id) != -1) {
                cout << "member id already exists!\n" << endl;
            } else {
                members.push_back(librarymember(id, name));
                cout << "member registered successfully!\n" << endl;
            }
        }

        else if (choice == 3) {
            int mid, rid;
            cout << "member id: "; cin >> mid;
            cout << "resource id: "; cin >> rid; cin.ignore();
            int idx = find_member(members, mid);
            if (idx == -1)
                cout << "member not found!\n" << endl;
            else
                lib.borrow_resource(rid, members[idx]);
        }

        else if (choice == 4) {
            int mid, rid;
            cout << "member id: "; cin >> mid;
            cout << "resource id: "; cin >> rid; cin.ignore();
            int idx = find_member(members, mid);
            if (idx == -1)
                cout << "member not found!\n" << endl;
            else
                lib.return_resource(rid, members[idx]);
        }

        else if (choice == 5) {
            lib.display_all();
        }

        else if (choice == 6) {
            int mid;
            cout << "member id: "; cin >> mid; cin.ignore();
            int idx = find_member(members, mid);
            if (idx == -1)
                cout << "member not found!\n" << endl;
            else
                members[idx].display_borrowed_items();
        }

        else if (choice == 7) {
            int mid, days;
            cout << "member id: "; cin >> mid;
            cout << "days late: "; cin >> days; cin.ignore();
            int idx = find_member(members, mid);
            if (idx == -1)
                cout << "member not found!\n" << endl;
            else
                cout << "total fee: rs. " << members[idx].calculate_total_late_fee(days) << "\n" << endl;
        }

        else if (choice == 8) {
            admin_view(lib, members);
        }

        else if (choice == 9) {
            cout << "goodbye!\n" << endl;
        }

        else {
            cout << "invalid choice! please enter 1-9.\n" << endl;
        }

    } while (choice != 9);

    return 0;
}
