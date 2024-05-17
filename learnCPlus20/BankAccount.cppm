export module bankaccount;
import <string>;
import <stdexcept>;
import <map>;
import <utility>;

export class BankAccount final
{
private:
    int m_accountnumber{ 0 };
    std::string m_clientname;

public:
    BankAccount(int accountnumber, std::string clientname) : m_accountnumber{accountnumber},
        m_clientname {move(clientname)}{}
    
    void setAccountNumber(int accountnumber)
    {
        m_accountnumber = accountnumber;
    }

    int getAccountNumber() const { return m_accountnumber; }

    void setClientName(std::string clientName)
    {
        m_clientname = std::move(clientName);
    }

    std::string getClientName() const { return m_clientname; }
};

export class BankDB final
{
private:
    std::map<int, BankAccount> m_accounts;
public:
    bool addAccount(const BankAccount& bankaccount);
    void deletAccount(int accountNumber);

    BankAccount& findAccount(int accountnumber);
    BankAccount& findAccount(std::string clientName);

    void mergeDataBase(BankDB& db);
};