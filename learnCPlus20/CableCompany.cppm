export module cable_company;
import <map>;
import <string>;
import <string_view>;
import <bitset>;

export class CableCompany final
{
public:
    static const size_t NumChannels{ 10 };
    void addPackages(std::string_view packageName, const std::bitset<NumChannels> channels);
    void addPackages(std::string_view packagName, std::string_view channels);

    void removePackages(std::string_view packageName);

    const std::bitset<NumChannels>& getPackage(std::string_view packageName) const;

    void newCustomer(std::string_view name, std::string_view package);
    void newCustomer(std::string_view nae, const std::bitset < NumChannels>& channels);

    void addChannerl(std::string_view name, int channel);

    void removeChannel(std::string_view name, int channel);
    
    void addPackageToCustomer(std::string_view  name, std::string_view package);
    void  deleteCustomer(std::string_view name);

    const std::bitset<NumChannels>& getCustomerChannels(std::string_view name);


private :
    std::bitset<NumChannels>& getCustomerChannelsHelper(std::string_view name);

    using MapType = std::map<std::string, std::bitset<NumChannels>>;
    MapType m_packages, m_customers;
};
