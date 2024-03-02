#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <cstddef>
#include <functional>

class ILogger
{
public:
    virtual ~ILogger() = default;

    enum class LogLevel
    {
        Error,
        Info,
        Debug
    };

    virtual void setLogLevel(LogLevel level) = 0;

    virtual void log(std::string message, LogLevel loglevel) = 0;
};

class Logger : public ILogger
{
public:
    explicit Logger(std::string fileName);
    virtual ~Logger();
    void setLogLevel(LogLevel level) override;
    void log(std::string message, LogLevel logevel) override;

private:
    std::string getLogLevelString(LogLevel level) const;
    std::ofstream m_outstream;
    LogLevel m_logLevel{LogLevel::Error};
};

Logger::Logger(std::string logFileName) {
    m_outstream.open(logFileName, std::fstream::ios_base::app);
    if (!m_outstream.good())
    {
        throw std::runtime_error{ "unable to initialize the logger" };
    }
}

Logger::~Logger()
{
    m_outstream << "Logger shutting down" << std::endl;
    m_outstream.close();
}

void Logger::setLogLevel(LogLevel level)
{
    m_logLevel = level;
}

std::string Logger::getLogLevelString(Logger::LogLevel level) const
{
    switch (level)
    {
    case Logger::LogLevel::Error:
        return "Error";
    case Logger::LogLevel::Info:
        return "Info";
    case Logger::LogLevel::Debug:
        return "Debug";
    }

    throw std::runtime_error("Invalid log level");
}

void Logger::log(std::string message, Logger::LogLevel level)
{
    if (m_logLevel < level)
    {
        std::cout << static_cast<int>(level) << " is less " << static_cast<int>(m_logLevel) << std::endl;
        return;
    }

    m_outstream << getLogLevelString(level) << ":" << message << std::endl;
}

class NewLoggerInterface
{
public:
    virtual ~NewLoggerInterface() = default;
    virtual void log(std::string message) = 0;
};

class NewLoggerAdapter : public NewLoggerInterface
{
public:
    NewLoggerAdapter();
    void log(std::string message) override;
private:
    Logger m_logger{"info.txt"};
};

NewLoggerAdapter::NewLoggerAdapter() {
    std::cout << "NewLoggerAdapter constructor " << std::endl;
}

void NewLoggerAdapter::log(std::string message) {
    // m_logger.setLogLevel(Logger::LogLevel::Debug);
    m_logger.log(message, Logger::LogLevel::Info);
}

class Foo
{
public:
    explicit Foo(ILogger& logger) : m_logger{ logger } {}

    void doSomething()
    {
        m_logger.log("hello log injection", ILogger::LogLevel::Info);
    }

private:
    ILogger& m_logger;
};

class ICar
{
public:
    virtual ~ICar() = default;
    virtual std::string info() const = 0;
};

class Ford : public ICar {
public:
    std::string info() const override
    {
        return "Ford";
    }
};

class FordSedan : public Ford
{
public:
    std::string info() const override { return "Ford sedan"; }
};

class FordSUV : public Ford
{
public:
    std::string info() const override { return "Ford SUV"; }
};

class Toyota : public ICar {
public:
    std::string info() const override { return "Toyota"; }
};

class ToyotaSedan : public Toyota
{
public:
    std::string info() const override { return "Toyota sedan"; }
};

class ToyotaSUV : public Toyota
{
public:
    std::string info() const override { return "Toyota SUV"; }
};

class IAbstractCarFactory
{
public:
    virtual ~IAbstractCarFactory() = default;
    virtual std::unique_ptr<ICar> makeSUV() = 0;
    virtual std::unique_ptr<ICar> makeSedan() = 0;
}; 

class FordFactory : public IAbstractCarFactory
{
    std::unique_ptr<ICar> makeSUV() override
    {
        return std::make_unique<FordSUV>();
    }

    std::unique_ptr<ICar> makeSedan() override
    {
        return std::make_unique<FordSedan>();
    }
};

class ToyotaFactory : public IAbstractCarFactory
{
    std::unique_ptr<ICar> makeSUV() override
    {
        return std::make_unique<ToyotaSUV>();
    }

    std::unique_ptr<ICar> makeSedan() override
    {
        return std::make_unique<ToyotaSedan>();
    }
};

void createSomeCar(IAbstractCarFactory& carFactory)
{
    auto sedan{ carFactory.makeSedan() };
    auto suv{ carFactory.makeSUV() };

    std::cout << "sedan info:" << sedan->info() << std::endl;
    std::cout << "SUV info:" << suv->info() << std::endl;
}

class CarFactory
{
public:
    virtual ~CarFactory() = default;

    std::unique_ptr<ICar> requestCar()
    {
        ++m_numberofCarsProduced;
        return createCar();
    }

    size_t getNumberofCarProduced() const { return m_numberofCarsProduced; }
protected:
    virtual std::unique_ptr<ICar> createCar() = 0;
private:
    size_t m_numberofCarsProduced{ 0 };
};

class FordFactory2 : public CarFactory
{
protected:
    std::unique_ptr<ICar> createCar() override
    {
        return std::make_unique<Ford>();
    }
};

class ToyotaFactory2 :public CarFactory
{
protected:
    std::unique_ptr<ICar> createCar() override
    {
        return std::make_unique<Toyota>();
    }
};

class LeastBusyFactory :public CarFactory
{
public:
    explicit LeastBusyFactory(std::vector<std::unique_ptr<CarFactory>>&& factories);
protected:
    std::unique_ptr<ICar> createCar() override;

private:
    std::vector<std::unique_ptr<CarFactory>> m_factories;
};

LeastBusyFactory::LeastBusyFactory(std::vector<std::unique_ptr<CarFactory>>&& factories) : m_factories(move(factories))
{
    if (m_factories.empty())
    {
        throw std::runtime_error("no factor");
    }
}

std::unique_ptr<ICar> LeastBusyFactory::createCar()
{
    CarFactory* bestsofar{ m_factories[0].get() };
    for (auto& factory: m_factories)
    {
        if (factory->getNumberofCarProduced() < bestsofar->getNumberofCarProduced())
        {
            bestsofar = factory.get();
        }
    }
    return bestsofar->requestCar();
}

class IPlayer
{
public:
    virtual ~IPlayer() = default;
    virtual std::string getName() const = 0;
    virtual std::string sendMessage(std::string message) const = 0;
};

class Player : public IPlayer
{
public:
    Player(std::string& name);
    std::string getName() const override;
    std::string sendMessage(std::string message) const override;
private:
    std::string m_name;
};

Player::Player(std::string& name) : m_name(name) {
    std::cout << "Player construction" << std::endl;
}

std::string Player::getName() const {
    return m_name;
}

std::string Player::sendMessage(std::string message) const {
    return "yes";
}

class PlayerProxy : public IPlayer
{
public:
    PlayerProxy(std::unique_ptr<IPlayer> player);
    std::string getName() const override;
    std::string sendMessage(std::string message) const override;
private:
    std::unique_ptr<IPlayer> m_player;
};

PlayerProxy::PlayerProxy(std::unique_ptr<IPlayer> player) : m_player(move(player)) {

}

std::string PlayerProxy::sendMessage(std::string message) const {
    return m_player->sendMessage(message);
}

std::string PlayerProxy::getName() const {
    return m_player->getName();
}

using EventHandle = size_t;

template <typename... Args>
class Event
{
public:
    virtual ~Event() = default;
    [[nodiscard]] EventHandle operator+=(std::function<void(Args...)> observer)
    {
        auto number{ ++m_counter };
        m_observers[number] = observer;
        return number;
    }

    Event& operator-=(EventHandle handle)
    {
        m_observers.erase(handle);
        return *this;
    }

    void raise(Args... args)
    {
        for (auto& observer : m_observers) {
            (observer.second)(args...);
        }
    }
private:
    size_t m_counter{ 0 };
    std::map<EventHandle, std::function<void(Args...)>> m_observers;
};

class ObservableSubject
{
public:
    auto& getEventDataModified() { return m_eventDataModified; }
    auto& getEventDataDeleted() { return m_eventDataDeleted; }

    void modifyData()
    {
        getEventDataModified().raise(1, 2.4);
    }

    void deleteData()
    {
        getEventDataDeleted().raise();
    }

private:
    Event<int, double> m_eventDataModified;
    Event<> m_eventDataDeleted;
};

void modified(int, double)
{
    std::cout << "modified" << std::endl;
}

class Observer
{
public:
    Observer(ObservableSubject& subject) : m_subject{ subject }
    {
        m_subjectModifiedHandle = m_subject.getEventDataModified() +=
            [this](int i, double d) {onSubjectModified(i, d); };
    }

    virtual ~Observer()
    {
        m_subject.getEventDataModified()-=m_subjectModifiedHandle;
    }
private:
    void onSubjectModified(int, double)
    {
        std::cout << "Observer::onSubjectModified()" << std::endl;
    }

    ObservableSubject& m_subject;
    EventHandle m_subjectModifiedHandle;
};

class IParagraph
{
public:
    virtual ~IParagraph() = default;
    virtual std::string getHMTL() const = 0;
};

class Paragraph : public IParagraph
{
public:
    Paragraph(std::string text) : m_text{ std::move(text) } {}
    std::string getHMTL() const override { return "<P>" + m_text + "</P>"; }
private:
    std::string m_text;
};

class BoldParagraph : public IParagraph
{
public:
    BoldParagraph(const IParagraph& paragraph) : m_paragraph{ paragraph } {}
    std::string getHMTL() const override {
        return "<B>" + m_paragraph.getHMTL() + "</B>";
    }
private:
    const IParagraph& m_paragraph;
};

class ItaliParagraph : public IParagraph
{
public:
    ItaliParagraph(const IParagraph& paragraph) : m_paragraph{ paragraph } {}
    std::string getHMTL() const override {
        return "<I>" + m_paragraph.getHMTL() + "</I>";
    }
private:
    const IParagraph& m_paragraph;
};

void testInject()
{
	Logger con("Log.txt");
	con.setLogLevel(ILogger::LogLevel::Debug);
}

void testFactory()
{
    //Foo f(con);
    // f.doSomething();
    FordFactory fordfactory;
    ToyotaFactory toyotafactory;

    createSomeCar(fordfactory);
    createSomeCar(toyotafactory);
}

void testFactory2()
{
    ToyotaFactory2 tofactory2;
    auto myCar{ tofactory2.requestCar() };
    std::cout << " factory2 " << myCar->info() << std::endl;

    std::vector<std::unique_ptr<CarFactory>> factories;

    factories.push_back(std::make_unique<FordFactory2>());
    factories.push_back(std::make_unique<FordFactory2>());
    factories.push_back(std::make_unique<FordFactory2>());
    factories.push_back(std::make_unique<ToyotaFactory2>());

    factories[0]->requestCar();
    factories[0]->requestCar();
    factories[1]->requestCar();
    factories[3]->requestCar();

    LeastBusyFactory leastfactory{ move(factories) };
    for (size_t i = 0; i < 10; i++)
    {
        auto car{ leastfactory.requestCar() };
        std::cout << car->info() << std::endl;
    }
}

void testAdapter() {
    NewLoggerAdapter newloggerAdapter;
    newloggerAdapter.log("new adapter log");
}

void testObserver()
{
    ObservableSubject subject;
    auto handleModifi{ subject.getEventDataModified() += modified };
    auto handleDelete{ subject.getEventDataDeleted() += [] {std::cout << "delete" << std::endl; } };
    Observer obser{ subject };
    subject.modifyData();
    subject.deleteData();

    std::cout << std::endl;

    subject.getEventDataModified() -= handleModifi;
    subject.modifyData();
    subject.deleteData();
}

void testDecorator()
{
	Paragraph p{ "A party?" };
	std::cout << BoldParagraph{ p }.getHMTL() << std::endl;
    std::cout << ItaliParagraph{ BoldParagraph{p } }.getHMTL() << std::endl;
}
int main()
{
    testDecorator();
    system("pause");
}
