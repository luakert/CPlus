module cable_company;

using namespace std;
void CableCompany::addPackages(string_view packagname, const bitset<NumChannels>& channel)
{
    m_packages.emplace(packagname, channel);
}

void CableCompany::addPackages(string_view packagname, string_view channel)
{
    addPackages(packagname, bitset<NumChannels> {channel.data()});
}

void CableCompany::removePackages(string_view packagename)
{
    m_packages.erase(packagename.data());
}

const bitset<CableCompany::NumChannels>& CableCompany::getPackage(string_view packagename) const
{
    if (auto it {m_packages.find(packagename.data())}; it!=end(m_packages))
    {
        return it->second;
    }

    throw out_of_range("Invalid package");
}

void CableCompany::newCustomer(string_view name, string_view package)
{
    auto& packageChannels{ getPackage(package) };
    newCustomer(name, packageChannels);
}

void CableCompany::newCustomer(string_view name, const bitset<NumChannels>& channels)
{
    if (auto[iter, success] {m_customers.emplace(name, channels)}; !success)
    {
        throw invalid_argument("Duplicate customer");
    }
}

void CableCompany::addChannerl(string_view name, int channel)
{
    auto& channels{ getCustomerChannelsHelper(name) };
    channels.set(channel);
}

void CableCompany::removeChannel(string_view name, int channel)
{
    auto& channels{ getCustomerChannelsHelper(name) };
    channels.reset(channel);
}

void CableCompany::addPackageToCustomer(string_view name, string_view package)
{
    auto& packagechannel{ getPackage(package) };
    auto& customerchannel{ getCustomerChannelsHelper(name) };
    customerchannel |= packagechannel;
}

void CableCompany::deleteCustomer(string_view name)
{
    m_customers.erase(name.data());
}

const bitset<CableCompany::NumChannels>& CableCompany::getCustomerChannels(string_view name) const
{
    if (auto it{m_customers.find(name.data())}; it != end(m_customers))
    {
        return it->second;
    }

    throw invalid_argument{ "UnKnown customer" };
}

bitset<CableCompany::NumChannels>& CableCompany::getCustomerChannelsHelper(string_view name)
{
    return const_cast<bitset<NumChannels>&>(as_const(*this).getCustomerChannels(name));
}
