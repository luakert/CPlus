#include <iostream>
#include <string>
#include <fstream>

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

int main()
{
    Logger con("Log.txt");
    con.setLogLevel(ILogger::LogLevel::Debug);

    Foo f(con);
    f.doSomething();
    system("pause");
}
