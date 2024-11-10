#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

class MenuItem {
public:
    string name;
    int price;

    MenuItem(string itemName, int itemPrice) : name(itemName), price(itemPrice) {}
};

class Order {
public:
    MenuItem* items[10];
    int itemCount;
    bool paymentStatus;

    Order() : itemCount(0), paymentStatus(false) {}

    void addItem(MenuItem* item) {
        if (itemCount < 10) {
            items[itemCount++] = item;
        }
    }

    void removeItem(int index) {
        if (index >= 0 && index < itemCount) {
            for (int i = index; i < itemCount - 1; ++i) {
                items[i] = items[i + 1];
            }
            itemCount--;
        }
    }

    void displayOrder() {
        cout << "Order Summary:\n";
        int total = 0;
        for (int i = 0; i < itemCount; ++i) {
            cout << items[i]->name << ": Rs." << items[i]->price << endl;
            total += items[i]->price;
        }
        cout << "Total: Rs." << total << endl;
    }

    void updatePaymentStatus(bool status) {
        paymentStatus = status;
    }

    int getTotalAmount() {
        int total = 0;
        for (int i = 0; i < itemCount; ++i) {
            total += items[i]->price;
        }
        return total;
    }
};

class User {
protected:
    string email;
    string password;
    Order currentOrder;
    bool orderPlaced;

public:
    User() : orderPlaced(false) {}

    virtual void registerUser(const string& userType) {
        cout << "Enter Email ID: ";
        cin >> email;
        cout << "Enter Password: ";
        cin >> password;
        ofstream userFile(userType + "_users.txt", ios::app);
        if (userFile.is_open()) {
            userFile << email << " " << password << "\n";
            userFile.close();
        }
        cout << "Registration Successful!\n";
    }

    bool login(const string& userType) {
        string inputEmail, inputPassword;
        cout << "Enter Email ID: ";
        cin >> inputEmail;
        cout << "Enter Password: ";
        cin >> inputPassword;

        ifstream userFile(userType + "_users.txt");
        string line;
        bool found = false;

        while (getline(userFile, line)) {
            size_t pos = line.find(' ');
            string storedEmail = line.substr(0, pos);
            string storedPassword = line.substr(pos + 1);

            if (storedEmail == inputEmail && storedPassword == inputPassword) {
                email = storedEmail;
                password = storedPassword;
                found = true;
                break;
            }
        }
        userFile.close();

        if (found) {
            cout << "Login Successful!\n";
            return true;
        } else {
            cout << "Invalid Email or Password.\n";
            return false;
        }
    }

    void placeOrder(MenuItem menu[], int menuCount) {
        cout << "Select items to place an order:\n";
        int choice;
        bool ordering = true;
        while (ordering) {
            displayMenu(menu, menuCount);
            cout << "Enter item number to add to order (0 to finish): ";
            cin >> choice;
            if (choice == 0) {
                ordering = false;
            } else if (choice > 0 && choice <= menuCount) {
                currentOrder.addItem(&menu[choice - 1]);
                cout << menu[choice - 1].name << " added to your order.\n";
            } else {
                cout << "Invalid choice.\n";
            }
        }

        cout << "Order placed successfully!\n";
        currentOrder.displayOrder();
        saveTransaction();
        checkOrderStatus();
        processPayment();
    }

    void saveTransaction() {
        ofstream transFile(email + "_transactions.txt", ios::app);
        if (transFile.is_open()) {
            transFile << "Order placed: ";
            for (int i = 0; i < currentOrder.itemCount; ++i) {
                transFile << currentOrder.items[i]->name << ", ";
            }
            transFile << "Total: Rs." << currentOrder.getTotalAmount() << "\n";
            transFile.close();
        }
    }

    static void displayMenu(MenuItem menu[], int menuCount) {
        cout << "**** MENU ****\n";
        for (int i = 0; i < menuCount; ++i) {
            cout << (i + 1) << ". " << menu[i].name << ": Rs." << menu[i].price << endl;
        }
    }

    void cancelOrder() {
        cout << "Are you sure you want to cancel the order? (yes/no): ";
        string response;
        cin >> response;
        if (response == "yes") {
            cout << "Order cancelled.\n";
            currentOrder = Order(); // Reset order
        }
    }

    void updateOrder(MenuItem menu[], int menuCount) {
        cout << "Select item number to remove from the order: ";
        int choice;
        cin >> choice;
        if (choice > 0 && choice <= currentOrder.itemCount) {
            currentOrder.removeItem(choice - 1);
            cout << "Item removed from your order.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }

private:
    void checkOrderStatus() {
        string received;
        while (true) {
            cout << "Have you received the order? (yes/no): ";
            cin >> received;
            if (received == "yes") {
                break;
            }
        }
    }

    void processPayment() {
        string paymentStatus;
        while (true) {
            cout << "Complete payment? (paid/unpaid): ";
            cin >> paymentStatus;
            if (paymentStatus == "paid") {
                currentOrder.updatePaymentStatus(true);
                break;
            }
        }
    }
};

class Admin : public User {
public:
    void addItemToMenu(MenuItem menu[], int& menuCount) {
        string itemName;
        int itemPrice;
        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, itemName);
        cout << "Enter item price: ";
        cin >> itemPrice;

        menu[menuCount++] = MenuItem(itemName, itemPrice);
        cout << "Item added to menu successfully.\n";
    }

    void removeItemFromMenu(MenuItem menu[], int& menuCount) {
        cout << "Enter item number to remove from the menu: ";
        int choice;
        cin >> choice;
        if (choice > 0 && choice <= menuCount) {
            for (int i = choice - 1; i < menuCount - 1; ++i) {
                menu[i] = menu[i + 1];
            }
            menuCount--;
            cout << "Item removed from menu successfully.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }

    void displayMenu(MenuItem menu[], int menuCount) {
        cout << "**** MENU ****\n";
        for (int i = 0; i < menuCount; ++i) {
            cout << (i + 1) << ". " << menu[i].name << ": Rs." << menu[i].price << endl;
        }
    }

    void viewOrders(Order pendingOrders[], int pendingCount) {
        cout << "**** Pending Orders ****\n";
        for (int i = 0; i < pendingCount; ++i) {
            cout << "Order " << (i + 1) << ":\n";
            pendingOrders[i].displayOrder();
        }
    }
};

int main() {
    MenuItem menu[20] = {
        MenuItem("Espresso", 150), MenuItem("Cappuccino", 180), MenuItem("Latte", 200), MenuItem("Americano", 170),
        MenuItem("Mocha", 210), MenuItem("Hot Chocolate", 180), MenuItem("Iced Coffee", 160), MenuItem("Iced Tea", 140),
        MenuItem("Veg Sandwich", 100), MenuItem("Chicken Sandwich", 200), MenuItem("Paneer Wrap", 180),
        MenuItem("Veg Burger", 160), MenuItem("Chicken Burger", 200), MenuItem("French Fries", 120),
        MenuItem("Pasta Alfredo", 270), MenuItem("Pizza", 350),
        MenuItem("Tea", 50), MenuItem("Black Coffee", 120), MenuItem("Lemonade", 90), MenuItem("Smoothie", 220)
    };
    int menuCount = 20;
    Order pendingOrders[10];
    int pendingCount = 0;

    User* user;
    Admin admin;

    while (true) {
        cout<<"\n*****CAFE MANAGEMENT SYSTEM*****\n";
        cout << "Choose user type (1: User, 2: Admin): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            user = new User();

            while (true) {
                cout << "Choose action (1: Register, 2: Login): ";
                cin >> choice;

                if (choice == 1) {
                    user->registerUser("user");
                } else if (choice == 2 && user->login("user")) {
                    break;
                } else {
                    cout << "Invalid choice.\n";
                }
            }

            while (true) {
                cout << "Choose action (1: Display Menu, 2: Place Order, 3: Update Order, 4: Cancel Order, 0: Logout): ";
                cin >> choice;

                if (choice == 1) {
                    user->displayMenu(menu, menuCount);
                } else if (choice == 2) {
                    user->placeOrder(menu, menuCount);
                } else if (choice == 3) {
                    user->updateOrder(menu, menuCount);
                } else if (choice == 4) {
                    user->cancelOrder();
                } else if (choice == 0) {
                    delete user;
                    break;
                }
            }
        } else if (choice == 2) {
            while (true) {
                cout << "Admin actions (1: Add Item, 2: Remove Item, 3: Display Menu, 0: Logout): ";
                cin >> choice;

                if (choice == 1) {
                    admin.addItemToMenu(menu, menuCount);
                } else if (choice == 2) {
                    admin.removeItemFromMenu(menu, menuCount);
                } else if (choice == 3) {
                    admin.displayMenu(menu, menuCount);
                } else if (choice == 0) {
                    break;
                }
            }
        }
    }

    return 0;
}
