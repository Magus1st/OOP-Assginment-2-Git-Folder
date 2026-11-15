//XYZ bank atm interface
//Author: David Russell
/*
==================================
==================================
Menu Options: 
    checking the account balance, 
    debiting the account 
    crediting the account 
    exit program.
==================================
==================================
*/
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class BankAccount {
    
    
    protected:    
    double accountBalance;// Private member variable to store the account balance
        // Parameterized constructor


    public:
        
        string accountHolderName; // Public member variable to store the account holder's name
        string accountNumber; // Public member variable to store the account number
        string accountType; // Public member variable to store the account type (savings or checking)

        BankAccount(){
            //initializeAccount(); // Call the initializeAccount function in the constructor

        } 
        void initializeAccount() {
            cout << accountType << endl << endl;
            cout << "Enter Initial account balance: ";
            cin >> accountBalance;
            system("cls"); // Clear the console screen
            
            // if (accountBalance < 1000) {
            //     accountBalance = 0; // Set balance to 0 if it's less than 1000
            //     cout << "The balance is invalid." << endl;
            //     cout << "\n\nPress enter to continue" << endl;
            //     cin.ignore(); // Clear the input buffer
            //     cin.get(); // Wait for user input before returning
            //     system("cls"); // Clear the console screen
            // }
            // else {
            //     cout << "The balance is: $" << accountBalance << endl;
            //     cout << "\n\nPress enter to continue" << endl;
            //     cin.ignore(); // Clear the input buffer
            //     cin.get(); // Wait for user input before returning
            //     system("cls"); // Clear the console screen
            // }
        }

        void setBalance() 
        {
            
            // Function to set the account balance
            cout << "Enter account balance: ";
            cin >> accountBalance;
            system("cls"); // Clear the console screen
            if (accountBalance < 1000) {
                accountBalance = 0; // Set balance to 0 if it's less than 1000
                cout << "The balance is invalid." << endl;
                cout << "The balance is set to $0.00." << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls"); // Clear the console screen
            }
            else {
                cout << "The balance is: $" << accountBalance << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls"); // Clear the console screen
            }
            
            
            
        }
        double getBalance() {// Function to check account balance
            return accountBalance; // Return the current account balance
        }
        virtual bool withdraw(double amount) {
            // Function to withdraw from the account
            if (amount > accountBalance) { // Check for insufficient funds or invalid amount
                cout << "Debit amount exceeded account balance." << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls");
                return false; // sets the account balance to the same value, indicating failure
            }
            else if (amount <= 0) {
                cout << "Invalid amount. Transaction declined." << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls");
                return false; // Return an error code
            }
            else {
                accountBalance -= amount; // Deduct the amount from the account balance
                cout << "Withdrew $" << amount << ". New balance: $" << accountBalance << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls");
                return true; // Indicate success
            }
        }
        double deposit(double amount) {// Function to credit the account
            if (amount <= 0) {
                cout << "Invalid amount. Transaction declined." << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls");
                return -1; // Return an error code
            }
            else {
                accountBalance += amount; // Add the amount to the account balance
                cout << "Deposited $" << amount << ". New balance: $" << accountBalance << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls"); // Clear the console screen
                return accountBalance; // Indicate success
            }
        }
        
        
};



class SavingAccount : public BankAccount {
    protected:
        double interestRate; // Private member variable to store the interest rate

    public:
        SavingAccount(double rate) : BankAccount() { // Constructor to initialize the interest rate
            interestRate = rate;
            accountType = "Saving Account"; // Set the account type to "Saving Account"
            initializeAccount(); // Call the initializeAccount function in the constructor
        }
        void setInterestRate(double rate) { // Function to set the interest rate
            interestRate = rate;
        }
        double getInterestRate() { // Function to get the interest rate
            return interestRate;
        }
        void CalculateInterest() { // Function to apply interest to the account balance
            double interest = getBalance() * (interestRate); // Calculate the interest
            deposit(interest); // Deposit the interest into the account
        }
};

class CheckingAccount : public BankAccount {
    protected:
        double fee; // Private member variable to store the transaction fee

    public:
        CheckingAccount(double initFee) : BankAccount() { // Constructor to initialize the transaction fee
            fee = initFee;
            accountType = "Checking Account"; // Set the account type to "Checking Account"
            initializeAccount(); // Call the initializeAccount function in the constructor
        }
        void setFee(double fee) { // Function to set the transaction fee
            this->fee = fee;
        }
        double getFee() { // Function to get the transaction fee
            return fee;
        }
        bool withdraw(double amount) override { // Override the withdraw function to allow overdrafts
            if (amount > getBalance()) { // Check for insufficient funds or invalid amount
                cout << "Withdrawal amount exceeded account balance." << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls");
                return false; // sets the account balance to the same value, indicating failure
            }
            else if (amount <= 0) {
                cout << "Invalid amount. Transaction declined." << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls");
                return false; // Return an error code
            }
            else {
                accountBalance -= amount + fee; // Deduct the amount and fee from the account balance
                cout << "===============================" << endl;
                cout << "Withdrew $" << amount << endl << "New balance: $" << accountBalance << endl << "Fee: $" << fee << endl;
                cout << "===============================" << endl << endl;
                cout << "\n\nPress enter to continue" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
                system("cls");
                return true; // Indicate success
            }
        }
};

void displayMenu() {
    // Function to display the menu options
    cout << "===============================" << endl;
    cout << "Please select an option:" << endl;
    cout << "1. Account Balance" << endl;
    cout << "2. Withdraw " << endl;
    cout << "3. Deposit" << endl;
    cout << "4. Exit" << endl;
    cout << "===============================" << endl;
}
void selectAccountMenu() {
    // Function to display the menu options
    cout << "===============================" << endl;
    cout << "Welcome to XYZ Bank ATM " << endl;
    cout << "Please select an Account:" << endl;
    cout << "1. Saving Account" << endl;
    cout << "2. Checking Account" << endl;
    cout << "===============================" << endl;
}
void calculateInterestDisplay() {
    // Function to display the menu options
    cout << "===============================" << endl;
    cout << "Options:" << endl;
    cout << "1. Add Interest" << endl;
    cout << "2. Back to Main Menu" << endl;
    cout << "===============================" << endl;
}

int main(){
    system("cls");

    class SavingAccount sAccount(.05); // Create an instance of the SavingAccount class
    class CheckingAccount cAccount(100); // Create an instance of the CheckingAccount class
    //sAccount.accountHolderName = "David Russell"; // Set the account holder's name
    //sAccount.accountNumber = "123";
    
    
    int choice; // Variable to store the user's menu choice
    double creditAmount=0; // Variable to store the amount to credit
    double debitAmount=0; // Variable to store the amount to debit
    double balance=0; // Variable to store the account balance
    class BankAccount* selectedAccount; // Variable to store the selected account type (1 for savings, 2 for checking)
    
    while (choice != 4) { // Loop until the user chooses to exit
        system ("cls");

        selectAccountMenu(); // Display the account selection menu
        cin >> choice; // Get the user's choice for account selection
        if (choice == 1) {
            selectedAccount = &sAccount; // Set the selected account to savings
        }
        else if (choice == 2) {
            selectedAccount = &cAccount; // Set the selected account to checking
        }
        else {
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(); // Clear the input buffer
            cin.get(); // Wait for user input before returning
            system("cls"); // Clear the console screen
            continue; // Restart the loop for account selection
        }
        system ("cls");
        displayMenu(); // Display the menu options
        cin >> choice; // Get the user's choice
        system("cls"); // Clear the console screen
        
        switch (choice) { // Handle the user's choice
            case 1:
                if (selectedAccount == &sAccount) {
                    cout << "Interest Rate: " << sAccount.getInterestRate()*100 << "%" << endl << endl;
                

                
                    cout << "Your account balance is: $" << selectedAccount->getBalance() << endl << endl;
                    
                    if (selectedAccount == &sAccount){
                        calculateInterestDisplay(); // Display the interest calculation menu
                        cin >> choice; // Get the user's choice for interest calculation
                    }
                    
                    
                    system("cls"); // Clear the console screen
                    
                    if (choice == 1) {
                        sAccount.CalculateInterest(); // Calculate interest for savings account
                    }
                    else if (choice == 2) {
                        system("cls"); // Clear the console screen
                    }
                    else {
                        cout << "Invalid option. Exiting to main menu." << endl;
                        cin.ignore(); // Clear the input buffer
                        cin.get(); // Wait for user input before returning
                        system("cls"); // Clear the console screen
                    }

                    
                }
                if (selectedAccount == &cAccount) {
                        
                    cout << "Your account balance is: $" << selectedAccount->getBalance() << endl << endl;
                    cout << "press enter to continue" << endl;
                    cin.ignore(); // Clear the input buffer
                    cin.get(); // Wait for user input before returning
                    system("cls"); // Clear the console screen
                }
                
                break;
            case 2:
                if (selectedAccount == &cAccount) {
                    cout << "Transaction Fee: $" << cAccount.getFee() << endl << endl;
                }
                cout << "Enter amount to withdraw: "; // Prompt the user to enter the amount to withdraw
                cin >> debitAmount;
                system("cls"); // Clear the console screen
                selectedAccount->withdraw(debitAmount); // Attempt to withdraw from the account
                system("cls"); // Clear the console screen
                break;
            case 3:
                cout << "Enter amount to deposit: ";
                cin >> creditAmount;
                system("cls"); // Clear the console screen
                selectedAccount->deposit(creditAmount); // Attempt to deposit into the account
                system("cls"); // Clear the console screen
                break;
            case 4:
                cout << "Thank you for using XYZ Bank ATM. Goodbye!" << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before exiting    
                system("cls"); // Clear the console screen
                exit(0); // Exit the program
                
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                cin.ignore(); // Clear the input buffer
                cin.get(); // Wait for user input before returning
        }
    }
    
    

    return 0;
};


