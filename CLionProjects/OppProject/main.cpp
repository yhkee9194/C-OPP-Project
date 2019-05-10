#include <iostream>


const int NAME_MAX_LEN = 10; // maximum size of Customer Name



class Account{

private:
    int accountNum;
    double balance;
    char* customerName;
public:
    Account(int accountNum, double balance, char* cusName) //constructor
    {
        this->accountNum = accountNum;
        this->balance = balance;
        customerName = new char [strlen(cusName)+1];
        strcpy(customerName, cusName);
    }

    Account(Account& ref):accountNum(ref.accountNum),balance(ref.balance) //user-defined copy constructor
    {
        customerName = new char [strlen(ref.customerName)+1];
        strcpy(customerName, ref.customerName);
    }

    int const GetAccountNum()
    {
        return accountNum;
    }

    double Deposit(double money)
    {
        balance += money;
        std::cout << "New Balance is: " << balance << std::endl;
        return balance;
    }

    double Withdraw(double money)
    {
        if (balance < money)
        {
            std::cout << "Withdrawl money is greater than current balance" << std::endl;
            return 0;
        }
        balance -= money;
        std::cout << "New Balance is: " << balance << std::endl;
        return balance;
    }

    void ShowAccountInfo()
    {
        std::cout << "Account Number Is: " << accountNum << std::endl;
        std::cout << "Current Balance Is: " << balance << std::endl;
        std::cout << "Customer Name is: " << customerName << std::endl;

    }
    ~Account()
    {
        delete []customerName;
    }
};


class AccountHandler // deal with data pertaining to Account Activities
{
private:
    Account *accountArray[100]; // account array pointing to Account class
    int accountNumberTracker; // track numbers of customer accounts
public:
    AccountHandler():accountNumberTracker(0) // constructor
    {
    }
    void DisplayMenu(void);
    void OpenAccount(void);
    void DepositMoney(void);
    void WithdrawMoney(void);
    void DisplayAllAccount(void);
};


int main()
{

    AccountHandler teller;

    while(true)
    {
        teller.DisplayMenu();

        int user_input;
        std::cout << "Please Select Options:"; std::cin >> user_input;
        std::cout << std::endl;

        switch(user_input)
        {
            case 1: teller.OpenAccount();
                break;
            case 2: teller.DepositMoney();
                break;
            case 3: teller.WithdrawMoney();
                break;
            case 4: teller.DisplayAllAccount();
                break;
            case 5: return 0; // Terminate the program
                break;
            default:
                std::cout << "Invalid Option" << std::endl;
        }
    }
    return 0;
}


void AccountHandler::DisplayMenu(void)
{
    std::cout << "----- Menu -----" << std::endl;
    std::cout << "1. Open Account" << std::endl;
    std::cout << "2. Deposit Money" << std::endl;
    std::cout << "3. Withdraw Money" << std::endl;
    std::cout << "4. Display balance" << std::endl;
    std::cout << "5. Terminate Program" << std::endl;
    std::cout << "----------------" << std::endl;
}


void AccountHandler::OpenAccount(void)
{
    int id = 0;
    int depositedMoney = 0;
    char name[NAME_MAX_LEN];
    std::cout << "[Opening New Account]" << std::endl;
    std::cout << "Account Number: "; std::cin >> id;
    std::cout << "Account Holder Name: "; std::cin >> name;
    std::cout << "Money Deposited: "; std::cin >> depositedMoney;

    accountArray[accountNumberTracker] = new Account(id, depositedMoney, name);
    accountNumberTracker ++;
}


void AccountHandler::DepositMoney(void)
{
    int deposit_money = 0;
    int account_id = 0;
    std::cout << "[Deposit]" << std::endl;
    std::cout << "Enter Account Number: "; std::cin >> account_id;
    std::cout << "Enter Deposit Amount: "; std::cin >> deposit_money;

    for(int i = 0;i < accountNumberTracker; i++)
    {
        if(accountArray[i] -> GetAccountNum() == account_id)
        {
            accountArray[i] -> Deposit(deposit_money);
            std::cout << "Deposit Succeeded" << std::endl;
            std::cout << std::endl;
            return;
        }
    }
    std::cout << "Invalid Account Number" << std::endl;
}

void AccountHandler::WithdrawMoney(void)
{
    int withdraw_money = 0;
    int account_id = 0;
    std::cout << "[Withdrawal]" << std::endl;
    std::cout << "Enter Account Number: "; std::cin >> account_id;
    std::cout << "Enter Withdrawal Amount: "; std::cin >> withdraw_money;

    for(int i = 0;i < accountNumberTracker; i++)
    {
        if(accountArray[i] -> GetAccountNum() == account_id)
        {
            accountArray[i] -> Withdraw(withdraw_money);
            std::cout << "Withdrawal Succeeded" << std::endl;
            std::cout << std::endl;
            return;
        }
    }
    std::cout << "Invalid Account Number" << std::endl;
}

void AccountHandler::DisplayAllAccount(void)
{
    for (int i = 0; i < accountNumberTracker; i++) {
        accountArray[i] ->ShowAccountInfo();
        std::cout << std::endl;
    }
}