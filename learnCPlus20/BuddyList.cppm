export module buddy_list;
import <map>;
import <string_view>;
import <vector>;

export class BuddyList final
{
private:
    std::multimap<std::string, std::string> m_buddies;
public:
    void addBuddy(const std::string_view name, const std::string_view buddy);

    void removeBuddy(const std::string_view name, const std::string_view buddy);

    bool isBuddy(const std::string_view name, const std::string_view buddy) const;

    std::vector<std::string> getBuddies(const std::string_view name) const;
};