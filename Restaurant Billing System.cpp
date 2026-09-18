#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

class Menu {
public:
    int code[6] = {101, 102, 201, 202, 301, 302};
    string name[6] = {
        "Veg Burger", "French Fries",
        "Margherita Pizza", "White Sauce Pasta",
        "Cold Coffee", "Chocolate Ice Cream"
    };
    string category[6] = {
        "Snacks", "Snacks",
        "Main Course", "Main Course",
        "Dessert", "Dessert"
    };
    double price[6] = {120, 80, 250, 180, 90, 100};
    void displayMenu() {
        cout << "\n====================================================================\n";
        cout << "                    WELCOME TO DINE-IN RESTAURANT\n";
        cout << "====================================================================\n";

        cout << left << setw(12) << "Item Code"
             << setw(25) << "Item Name"
             << setw(18) << "Category"
             << "Price\n";

        cout << "--------------------------------------------------------------------\n";

        for (int i = 0; i < 6; i++) {
            cout << left << setw(12) << code[i]
                 << setw(25) << name[i]
                 << setw(18) << category[i]
                 << "Rs. " << fixed << setprecision(2) << price[i] << endl;
        }
        cout << "====================================================================\n";
    }
    void saveMenuToFile() {
        ofstream file("menu.txt");
        if (!file) {
            cout << "Error opening menu file.\n";
            return;
        }
        file << "====================================================================\n";
        file << "                    DINE-IN RESTAURANT MENU\n";
        file << "====================================================================\n";
        file << left << setw(12) << "Item Code"
             << setw(25) << "Item Name"
             << setw(18) << "Category"
             << "Price\n";
        file << "--------------------------------------------------------------------\n";
        for (int i = 0; i < 6; i++) {
            file << left << setw(12) << code[i]
                 << setw(25) << name[i]
                 << setw(18) << category[i]
                 << "Rs. " << fixed << setprecision(2) << price[i] << endl;
        }
        file << "====================================================================\n";
        file.close();
        cout << "Menu saved successfully in menu.txt\n";
    }

    int findItem(int itemCode) {
        for (int i = 0; i < 6; i++) {
            if (code[i] == itemCode) {
                return i;
            }
        }
        return -1;
    }
};

   class Billing {
public:
    void createBill(Menu menu) {
        string customerName;
        int itemCode, quantity;
        int itemIndex[20], itemQuantity[20];
        int count = 0;
        char choice;
        double subtotal = 0;
        cout << "\nEnter customer name: ";
        getline(cin >> ws, customerName);
        do {
            cout << "\nEnter item code: ";
            cin >> itemCode;
            int index = menu.findItem(itemCode);
            if (index == -1) {
                cout << "Invalid item code.\n";
            } else {
                cout << "Enter quantity: ";
                cin >> quantity;
                if (quantity <= 0) {
                    cout << "Invalid quantity.\n";
                } else {
                    itemIndex[count] = index;
                    itemQuantity[count] = quantity;
                    subtotal += menu.price[index] * quantity;
                    count++;
                    cout << "Item added successfully.\n";
                }
            }
            cout << "Do you want to order another item? (Y/N): ";
            cin >> choice;
        } while ((choice == 'Y' || choice == 'y') && count < 20);
        if (count == 0) {
            cout << "\nNo valid items were ordered.\n";
            return;
        }
        double tax = subtotal * 0.05;
        double total = subtotal + tax;
        cout << "\n================================================\n";
        cout << "                    BILL RECEIPT\n";
        cout << "================================================\n";
        cout << "Customer Name : " << customerName << endl;
        cout << "------------------------------------------------\n";
        cout << left << setw(25) << "Item Name"
             << setw(12) << "Quantity"
             << "Amount\n";
        cout << "------------------------------------------------\n";
        for (int i = 0; i < count; i++) {
            double amount = menu.price[itemIndex[i]] * itemQuantity[i];

            cout << left << setw(25) << menu.name[itemIndex[i]]
                 << setw(12) << itemQuantity[i]
                 << "Rs. " << fixed << setprecision(2) << amount << endl;
        }
        cout << "------------------------------------------------\n";
        cout << "                      Subtotal      : Rs. " << subtotal << endl;
        cout << "                      Tax (5%)      : Rs. " << tax << endl;
        cout << "------------------------------------------------\n";
        cout << "                      Total Amount  : Rs. " << total << endl;
        cout << "================================================\n";
        saveBillToFile(customerName, menu, itemIndex, itemQuantity,
                       count, subtotal, tax, total);
        cout << "Thank you for visiting Dine-In Restaurant!\n";
    }
    void saveBillToFile(string customerName, Menu menu,
                        int itemIndex[], int itemQuantity[], int count,
                        double subtotal, double tax, double total) {
        ofstream file("bill.txt", ios::app);
        if (!file) {
            cout << "Error opening bill file.\n";
            return;
        }
        file << "\n================================================\n";
        file << "                    BILL RECEIPT\n";
        file << "================================================\n";
        file << "Customer Name : " << customerName << endl;
        file << "------------------------------------------------\n";
        file << left << setw(25) << "Item Name"
             << setw(12) << "Quantity"
             << "Amount\n";
        file << "------------------------------------------------\n";
        for (int i = 0; i < count; i++) {
            double amount = menu.price[itemIndex[i]] * itemQuantity[i];

            file << left << setw(25) << menu.name[itemIndex[i]]
                 << setw(12) << itemQuantity[i]
                 << "Rs. " << fixed << setprecision(2) << amount << endl;
        }
        file << "------------------------------------------------\n";
        file << "Subtotal      : Rs. " << subtotal << endl;
        file << "Tax (5%)      : Rs. " << tax << endl;
        file << "------------------------------------------------\n";
        file << "Total Amount  : Rs. " << total << endl;
        file << "================================================\n";
        file.close();
        cout << "Bill saved successfully in bill.txt\n";
    }
};
int main() {
    Menu menu;
    Billing bill;
    menu.saveMenuToFile();
    menu.displayMenu();
    bill.createBill(menu);
    return 0;
}
