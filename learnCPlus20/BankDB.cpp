module bankaccount;

// import <utility>;
//import <stdexcept>;


bool BankDB::addAccount(const BankAccount& account)
{
    auto ret{ m_accounts.emplace(account.getAccountNumber(), account) };
    // auto ret{ m_accounts.insert(pair{account.getAccountNumber(), account}) };
    return ret.second;
}

void BankDB::deletAccount(int accountNumber)
{
    m_accounts.erase(accountNumber);
}

BankAccount& BankDB::findAccount(int accountNumber)
{
    auto it{ m_accounts.find(accountNumber) };
    if (it == std::end(m_accounts))
    {
        throw std::out_of_range("not find accountnumber");
    }

    return it->second;
}

BankAccount& BankDB::findAccount(std::string name)
{
    for (auto& [accountnumber, bankaccount] : m_accounts)
    {
        if (bankaccount.getClientName() == name)
        {
            return bankaccount;
        }
    }

    throw std::out_of_range("No account with that name");
}

void BankDB::mergeDataBase(BankDB& db)
{
    m_accounts.merge(db.m_accounts);
    db.m_accounts.clear();
}

