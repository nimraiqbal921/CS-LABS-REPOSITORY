#include <iostream>
#include <string>
using namespace std;

class Device {
private:
    string name;
    bool isOn;
    int brightness;

public:
    Device() {
        name = "Unknown";
        isOn = false;
        brightness = 50;
    }

    Device(string n, bool status, int b) {
        name = n;
        isOn = status;
        setBrightness(b);
    }

    ~Device() {
        cout << "Device [" << name << "] is being removed" << endl;
    }

    void setName(string n) { name = n; }
    string getName() const { return name; }

    void setBrightness(int b) {
        if (b < 0) brightness = 0;
        else if (b > 100) brightness = 100;
        else brightness = b;
    }
    int getBrightness() const { return brightness; }

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    bool getStatus() const { return isOn; }

    void showInfo() const {
        cout << "Name: " << name
             << ", Status: " << (isOn ? "ON" : "OFF")
             << ", Brightness: " << brightness << endl;
    }
};

class Room {
private:
    string roomName;
    Device devices[5];
    int count;

public:
    Room(string name) {
        roomName = name;
        count = 0;
    }

    ~Room() {
        cout << "Room [" << roomName << "] manager closed" << endl;
    }

    void addDevice(Device d) {
        if (count >= 5) {
            cout << "Room is full! Cannot add more devices" << endl;
            return;
        }
        if (findDevice(d.getName()) != -1) {
            cout << "Device with this name already exists" << endl;
            return;
        }
        devices[count++] = d;
        cout << "Device added " << endl;
    }

    void showAllDevices() const {
        if (count == 0) cout << "No devices in the room" << endl;
        else for (int i = 0; i < count; i++) devices[i].showInfo();
    }

    int findDevice(string name) {
        for (int i = 0; i < count; i++)
            if (devices[i].getName() == name) return i;
        return -1;
    }

    void toggleDevice(string name) {
        int idx = findDevice(name);
        if (idx == -1) cout << "Device not found!" << endl;
        else {
            if (devices[idx].getStatus()) devices[idx].turnOff();
            else devices[idx].turnOn();
            cout << "Device [" << name << "] is now "
                 << (devices[idx].getStatus() ? "ON" : "OFF") << endl;
        }
    }

    void setDeviceBrightness(string name, int b) {
        int idx = findDevice(name);
        if (idx == -1) cout << "Device not found!" << endl;
        else {
            devices[idx].setBrightness(b);
            cout << "Brightness of [" << name << "] set to "
                 << devices[idx].getBrightness() << endl;
        }
    }

    int getCount() const { return count; } // getter for current number of devices
};

int main() {
    string roomName;
    cout << "Enter room name: ";
    getline(cin, roomName);
    Room myRoom(roomName);

    int choice;
    do {
        cout << "\n=== Smart Room Manager ===\n";
        cout << "1. Add a Device\n";
        cout << "2. Show All Devices\n";
        cout << "3. Turn Device ON/OFF\n";
        cout << "4. Change Brightness\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                // Check room full 
                if (myRoom.getCount() >= 5) {
                    cout << "Room is full! Cannot add more devices" << endl;
                    break;
                }

                string name;
                cout << "Enter device name: ";
                getline(cin, name);

                // Check duplicate name
                if (myRoom.findDevice(name) != -1) {
                    cout << "Device with this name already exists!" << endl;
                    break;
                }

                // ON/OFF input validation
                int onOffInput;
                while (true) {
                    cout << "Is device ON? (1 = Yes, 0 = No): ";
                    cin >> onOffInput;

                    if (cin.fail()) { 
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Enter 1 or 0 only\n";
                        continue;
                    }

                    if (onOffInput == 0 || onOffInput == 1) break;
                    else cout << "Invalid input! Enter 1 or 0 only\n";
                }
                bool status = (onOffInput == 1);

                int brightness;
                do {
                    cout << "Enter brightness (0-100): ";
                    cin >> brightness;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Must be a number 0-100\n";
                        brightness = -1; 
                        continue;
                    }

                    if (brightness < 0 || brightness > 100)
                        cout << "Invalid brightness Must be 0-100\n";

                } while (brightness < 0 || brightness > 100);

                cin.ignore(); 
                Device d(name, status, brightness);
                myRoom.addDevice(d);
                break;
            }

            case 2:
                myRoom.showAllDevices();
                break;

            case 3: {
                string name;
                cout << "Enter device name to toggle: ";
                getline(cin, name);
                myRoom.toggleDevice(name);
                break;
            }

            case 4: {
                string name;
                int brightness;
                cout << "Enter device name: ";
                getline(cin, name);

                // Brightness input
                do {
                    cout << "Enter new brightness (0-100): ";
                    cin >> brightness;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input, Must be a number 0-100.\n";
                        brightness = -1;
                        continue;
                    }

                    if (brightness < 0 || brightness > 100)
                        cout << "Invalid brightness Must be 0-100.\n";

                } while (brightness < 0 || brightness > 100);

                cin.ignore();
                myRoom.setDeviceBrightness(name, brightness);
                break;
            }

            case 5:
                cout << "Exiting " << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}
