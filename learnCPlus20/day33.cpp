#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>

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
        return;
    }

    m_outstream << getLogLevelString(level) << ":" << message << std::endl;
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

int main()
{
//    Logger con("Log.txt");
//    con.setLogLevel(ILogger::LogLevel::Debug);
//
//    Foo f(con);
//    f.doSomething();
    FordFactory fordfactory;
    ToyotaFactory toyotafactory;

    createSomeCar(fordfactory);
    createSomeCar(toyotafactory);

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
    system("pause");
}
