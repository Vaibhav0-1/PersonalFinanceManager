#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

class Transaction {
protected:
    double amount;
    string description;

public:
    Transaction(double amt, const string &des){
        amount = amt;
        description = des;
    }

    virtual void display() {
        cout << setw(15) << amount << setw(20) << description << endl;
    }
};

class Income : public Transaction {
public:
    Income(double amt, const string& des) : Transaction(amt, des) {}

    void display() {
        cout << setw(15) << "Income" << setw(20);
        Transaction::display();
    }
};

class Expenditure : public Transaction {
public:
    Expenditure(double amt, const string &des) : Transaction(amt, des) {}

    void display() {
        cout << setw(15) << "Expenditure" << setw(20);
        Transaction::display();
    }
};

class Investment {
protected:
    double amount;
    int duration;

public:
    Investment(double amt, int dur) {
        amount = amt;
        duration = dur;
    }

    virtual void display() {
        cout << setw(15) << amount << setw(15) << duration;
    }
    virtual double maturityAmount() {
        return amount;
    }
};

class SIP : public Investment {
    private:
    double monthly;
    double interestRate; // Annual interest rate for SIP
    int compoundingFrequency; // Compounding frequency (monthly, quarterly, etc.)
    vector<double> customMonthlyInvestments; // Vector to store variable monthly investments
    string fundName;
    string startDate;

public:
    SIP(double amt, int dur, double monAmt, double rate, int compFreq, const string& fName, const string& sDate)
        : Investment(amt, dur), monthly(monAmt), interestRate(rate), compoundingFrequency(compFreq), fundName(fName), startDate(sDate) {}

    void addCustomMonthlyInvestment(double amount, int month) {
        // Add custom monthly investments for specific months
        if (month >= 1 && month <= duration) {
            customMonthlyInvestments.resize(duration, monthly); // Initialize with default monthly amount
            customMonthlyInvestments[month - 1] = amount; // Update the specific month's investment
        } else {
            cout << "Invalid month. Custom monthly investment not added." << endl;
        }
    }

    double maturityAmount() override {
        double totalInvestment = 0;
        double finalAmount = 0;

        // Calculate total investment based on regular and custom monthly investments
        for (int i = 0; i < duration; ++i) {
            totalInvestment += (i < customMonthlyInvestments.size()) ? customMonthlyInvestments[i] : monthly;
        }

        // Calculate maturity amount using compound interest formula
        finalAmount = totalInvestment * pow(1 + (interestRate / (compoundingFrequency * 100)), (compoundingFrequency * duration) / 12.0);

        return finalAmount;
    }
        void display() override {
        cout << setw(15) << "SIP" << setw(15) << amount << setw(15) << duration << setw(15) << fundName << setw(15) << startDate << endl;
        cout << setw(15) << "Month" << setw(25) << "Investment Amount" << endl;

        for (int i = 0; i < duration; ++i) {
            double currentMonthlyInvestment = (i < customMonthlyInvestments.size()) ? customMonthlyInvestments[i] : monthly;
            cout << setw(15) << i + 1 << setw(25) << currentMonthlyInvestment << endl;
        }

        cout << "---------------------------------------------" << endl;
    }
};

class FD : public Investment {
private:
    double interestRate;
    int compoundingFrequency; // 1 for annually, 12 for monthly, etc.
    double penaltyRate;
    int minDuration;

public:
    FD(double amt, int dur, double rate, int frequency, double penalty, int minDur)
        : Investment(amt, dur), interestRate(rate), compoundingFrequency(frequency), penaltyRate(penalty), minDuration(minDur) {}

    void updateInterestRate(double newRate) {
        interestRate = newRate;
    }

    double maturityAmount() {
        if (duration < minDuration) {
            double penaltyAmount = amount * (penaltyRate / 100);
            return amount - penaltyAmount;
        }
        double totalAmount = amount * pow((1 + (interestRate / compoundingFrequency)), (compoundingFrequency * duration));
        return totalAmount;
    }
};
class Node {
public:
    Transaction* data;
    Node* next;

    Node(Transaction* t) : data(t), next(nullptr) {}
    // Node(Investment *i) : data(i) , next(nullptr) {}

};
class Node2{
    public:
    Investment* data;
    Node2 * next;
    Node2(Investment * i) : data(i) , next(nullptr) {}
};



// class FinanceManager {
//     private:
//     FinanceNode * head;
// public:
//     Transaction* transactions[100];
//     Investment* investments[50];
//     int tcount;
//     int icount;

//     FinanceManager() {
//         tcount = 0;
//         icount = 0;
//     }

//     void addTransaction(Transaction* t) {
//         transactions[tcount++] = t;
//     }
//     void add_Trans_invest(int transaction , double investments);

//     void addInvestment(Investment* i) {
//         investments[icount++] = i;
//     }

//     void displayRecord(double balance) {
//         cout << "-----------------------------------\n";
//         cout << "|        Personal Finance        |\n";
//         cout << "-----------------------------------\n";

//         cout << "\n||--BALANCE--: " << balance << "||" << endl;

//         cout << "\n--SAVINGS--: \n";
//         cout << setw(15) << "Type"<<setw(15)<<"Amount" << setw(20) << "Description" << endl;
//         for (int i = 0; i < tcount; i++) {
//             transactions[i]->display();
//         }

//         cout << "\n--INVESTMENTS--\n";
//         cout << setw(15) << "Type" << setw(15) << "Amount" << setw(15) << "Duration"<<setw(30)<<"Monthly amount invested"<<endl;
//         for (int i = 0; i < icount; i++) {
//             investments[i]->display();
//         }
//     }
// };
class FinanceManager {


public:
Node* transactionsListHead;
    Node2* investmentsListHead;
    FinanceManager() {
        transactionsListHead = nullptr;
        investmentsListHead = nullptr;
    }

    void addTransaction(Transaction* t) {
        Node* newNode = new Node(t);
        newNode->next = transactionsListHead;
        transactionsListHead = newNode;
    }

    void addInvestment(Investment* i) {
        Node2* newNode = new Node2(i);
        newNode->next = investmentsListHead;
        investmentsListHead = newNode;
    }

    void displayRecord(double balance) {
        // ... existing displayRecord function code
        // Modify the display logic to traverse the linked lists.
        Node* temp = transactionsListHead;
        Node2* temp2;
        cout << "\n--SAVINGS--: \n";
        cout << setw(15) << "Type" << setw(15) << "Amount" << setw(20) << "Description" << endl;
        while (temp != nullptr) {
            temp->data->display();
            temp = temp->next;
        }

        temp2 = investmentsListHead;
        cout << "\n--INVESTMENTS--\n";
        cout << setw(15) << "Type" << setw(15) << "Amount" << setw(15) << "Duration" << setw(30) << "Monthly amount invested" << endl;
        while (temp2 != nullptr) {
            temp2->data->display();
            temp2 = temp2->next;
        }
    }

    ~FinanceManager() {
        // Deallocate memory for linked lists in the destructor
        Node* temp = transactionsListHead;
        Node2 * temp2;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp->data;
            delete temp;
            temp = next;
        }

        temp2 = investmentsListHead;
        while (temp2 != nullptr) {
            Node2* next = temp2->next;
            delete temp2->data;
            delete temp2;
            temp2 = next;
        }
    }
};

class User {
public:
    FinanceManager manager;
    double balance;
    double needsAmount;
    double wantsAmount;
    double savingsAmount;

    User(double initialBalance) {
        balance = initialBalance;
        needsAmount = 0;
        wantsAmount = 0;
        savingsAmount = balance;
    }

    void operations() {
        int choice = -1;
        while (choice != 0) {
            cout << "\n--OPTIONS--\n";
            cout << "1. Record INCOME\n";
            cout << "2. Record EXPENDITURE\n";
            cout << "3. Make Investment\n";
            cout << "4. Finance Information\n";
            cout << "5. Investment Information\n";
            cout << "0. Exit\n";
            cout << "Enter choice : ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double amt;
                    string desc;
                    cout << "Enter amount : ";
                    cin >> amt;
                    cout << "Enter description : ";
                    cin.ignore();
                    getline(cin, desc);

                      // Categorize income based on the 50-30-20 rule
                    double needsPercentage = 0.5; // 50%
                    double wantsPercentage = 0.3; // 30%
                    double savingsPercentage = 0.2; // 20%
                    
                    manager.addTransaction(new Income(amt, desc));
                    //balance += amt;
                    needsAmount += amt * needsPercentage;
                    wantsAmount += amt * wantsPercentage;
                    savingsAmount += amt * savingsPercentage;
                    break;
                }

                case 2: {
                    double amt;
                    string desc;
                    cout << "Enter amount: ";
                    cin >> amt;
                    if (balance - amt < 1000) {
                        cout << "Error: Balance cannot go below 1000." << endl;
                        continue;
                    }
                    cin.ignore();
                    cout << "Enter description: ";
                    getline(cin, desc);
                    manager.addTransaction(new Expenditure(amt, desc));
                    //balance -= amt;
                    needsAmount += amt;
                    break;
                }

                case 3: {
                    displayInvestmentGuidelines();
                    makeInvestment();
                    break;
                }

                case 4: {
                    manager.displayRecord(balance);
                    break;
                }

                case 5: {
                
                cout << "--INVESTMENTS--\n";
                Node2* temp = manager.investmentsListHead;
                while (temp != nullptr) {
                    Investment* inv = dynamic_cast<Investment*>(temp->data);
                    if (inv) {
                        cout << "Type: " << typeid(*inv).name() << endl; 
                        cout << "Amount: " << inv->maturityAmount() << " Rs" << endl;
                        inv->display(); 
                        cout << "--------------------\n";
                    }
                    temp = temp->next;
                
        
        }
        break;
                }


                //     cout << "--MATURITY AMOUNTS--||\n";
                //     for (int i = 0; i < manager.icount; i++) {
                //         Investment* inv = manager.investments[i];
                //         cout << "\nInvestment " << i + 1 << " : " << inv->maturityAmount() << " Rs" << endl;
                //         cout<<setw(15)<<"Type"<<setw(15)<<"Amount"<<setw(20)<<"Duration"<<setw(30)<<"Monthly amount invested"<<endl;
                //         inv->display();
                //     }
                //     break;
                

                case 0:
                    break;

                default:
                    cout << "\nNo such option:(";
                    break;
            }
                        // Display 50-30-20 rule information
        cout << "\n--50-30-20 Rule--\n";
        cout << "Needs: " << needsAmount << " Rs\n";
        cout << "Wants: " << wantsAmount << " Rs\n";
        cout << "Savings: " << savingsAmount << " Rs\n";
        }
    };
    

    void makeInvestment() {
        int sub = -1;
        while (sub != 0) {
            cout << "\nWhich one:\n";
            cout << "1. SIP\n";
            cout << "2. FD\n";
            cout << "0. Go back\n";
            cout << "Enter your choice : ";
            cin >> sub;

            switch (sub) {
                case 1: {
                    displaySIPRules(); 
                    makeSIPInvestment();
                        break;
                }

                case 2: {
                    displayFDRules();
                   makeFDInvestment();
                }

                case 0:
                    break;

                default:
                    cout << "Invalid choice.";
                    break;
            }
        }
    }

    void makeSIPInvestment() {
            double amt, monthly, rate;
            int dur, compFreq;
            string fundName, startDate;

            cout << "Enter SIP amount : ";
            cin >> amt;
            if (balance - amt < 1000) {
                cout << "ERROR : Min Balance=1000";
                return;
            }
            cout << "Enter SIP duration in years : ";
            cin >> dur;
            cout << "Enter monthly investment amount : ";
            cin >> monthly;
            cout << "Enter annual interest rate (%) : ";
            cin >> rate;
            cout << "Enter compounding frequency (1 for monthly, 4 for quarterly, etc.) : ";
            cin >> compFreq;

            cout << "Enter SIP Fund Name: ";
            cin.ignore();
            getline(cin, fundName);
            cout << "Enter SIP Start Date (MM/YYYY): ";
            getline(cin, startDate);

            SIP* sip = new SIP(amt, dur, monthly, rate, compFreq, fundName, startDate);
            manager.addInvestment(sip);
            balance -= amt;

            // Add custom monthly investments
            for (int i = 1; i <= dur; ++i) {
                double customMonthly;
                cout << "Enter custom monthly investment amount for month " << i << ": ";
                cin >> customMonthly;
                sip->addCustomMonthlyInvestment(customMonthly, i);
            }
        }
        void makeFDInvestment() {
        double amt;
        int dur, compFreq, minDur;
        double interestRate, penaltyRate;

        cout << "Enter amount: ";
        cin >> amt;
        cout << "Enter duration in years: ";
        cin >> dur;
        cout << "Enter compounding frequency (e.g., 1 for annually, 12 for monthly): ";
        cin >> compFreq;
        cout << "Enter minimum duration for penalty (in years): ";
        cin >> minDur;
        cout << "Enter interest rate (%): ";
        cin >> interestRate;
        cout << "Enter penalty rate for early withdrawal (%): ";
        cin >> penaltyRate;

        manager.addInvestment(new FD(amt, dur, interestRate / 100, compFreq, penaltyRate, minDur));
        balance -= amt;
    }
    void displaySIPRules() {
        cout << "\n--- SIP Investment Rules ---\n";
        // Display SIP rules here
        cout << "\n--SIP (SYSTEMATIC INVESTMENT PLAN) RULES--\n";
        cout << "1. Investment Period: Minimum 1 year, maximum 10 years.\n";
        cout << "2. Minimum Investment Amount: Rs. 500 per installment.\n";
        cout << "3. Frequency of Investment: Monthly.\n";
        cout << "4. Lock-In Period: None.\n";
        cout << "5. Returns and Risk: Subject to market risks.\n";
        cout << "6. Termination and Redemption: Allowed with applicable charges.\n";
        cout << "7. NAV (Net Asset Value) Calculation: Daily.\n";
        cout << "8. Automatic Renewal: Optional.\n";
        // Add more rules as needed
    }

       void displayFDRules() {
        cout << "\n--- FD Investment Rules ---\n";
        cout << "\n--FD (FIXED DEPOSIT) RULES--\n";
        cout << "1. Investment Period: 1 year to 5 years.\n";
        cout << "2. Interest Rate: Fixed, as per the prevailing rates.\n";
        cout << "3. Minimum and Maximum Deposit Amount: Rs. 10,000 to Rs. 10,00,000.\n";
        cout << "4. Premature Withdrawal: Allowed with applicable charges.\n";
        cout << "5. Renewal Process: Automatic renewal at the end of the tenure.\n";
        cout << "6. Interest Payment Frequency: Quarterly.\n";
        cout << "7. Tax Deducted at Source (TDS): Applicable as per income tax regulations.\n";
        cout << "8. Loan Against FD: Available.\n";
        cout << "9. Nomination Facility: Available.\n";
        cout << "10. Documentation Required: PAN card, address proof, and passport-size photos.\n";
        // Add more rules as needed
    }
     void displayInvestmentGuidelines() {
        cout << "\n--- Investment Guidelines ---\n";
        cout << "Before making an investment, please review the following guidelines:\n";
        cout << "1. Invest wisely based on your financial goals.\n";
        cout << "2. Diversify your investments to manage risk.\n";
        cout << "3. Understand the terms and conditions of the investment.\n";
        // Add more guidelines as needed
    }
 };
 
     


int main() {
    cout << "---Welcome to Finance Management System!!---\n";
    User user(2000); //create user with initial balance 2000
    user.operations();

return 0;
}