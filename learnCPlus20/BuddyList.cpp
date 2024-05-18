module buddy_list;

void BuddyList::addBuddy(const std::string_view name, const std::string_view buddy)
{
    if (!isBuddy(name, buddy))
    {
        m_buddies.insert({ name.data(), buddy.data()});
    }
}

void BuddyList::removeBuddy(const std::string_view name, const std::string_view buddy)
{
    auto begin{ m_buddies.lower_bound(name.data()) };
    auto end { m_buddies.upper_bound(name.data()) };

    for (auto iter {begin}; iter != end; ++iter)
    {
        if (iter->second == buddy)
        {
            m_buddies.erase(iter);
            break;
        }
    }
}

bool BuddyList::isBuddy(const std::string_view name, const std::string_view buddy) const
{
    auto [begin, end] {m_buddies.equal_range(name.data())};
    for (auto iter {begin}; iter != end; ++iter)
    {
        if (iter->second == buddy)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::string> BuddyList::getBuddies(const std::string_view name) const
{
    auto [begin, end] {m_buddies.equal_range(name.data())};

    std::vector<std::string> buddies;
    for (auto iter{begin}; iter != end; ++iter)
    {
        buddies.push_back(iter->second);
    }

    return buddies;
}