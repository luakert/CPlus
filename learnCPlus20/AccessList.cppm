export module access_list;
import <string>;
import <vector>;
import <set>;

export class AccessList final
{
private:
    std::set<std::string> m_allowed;
public:
    AccessList() = default;
    AccessList(std::initializer_list<std::string> users)
    {
        m_allowed.insert(begin(users), end(users));
    }

    void addUser(std::string user)
    {
        m_allowed.emplace(user);
    }

    void removeUser(const std::string& user)
    {
        m_allowed.erase(user);
    }

    bool isAllowed(std::string& user) const
    {
        return (m_allowed.count(user) != 0);
    }

    std::vector<std::string> getAllUser() const
    {
        return { begin(m_allowed), end(m_allowed) };
    }
};
