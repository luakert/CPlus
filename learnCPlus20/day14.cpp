#include <iostream>
#include <filesystem>
#include <fstream>
#include <source_location>
#include <ostream>
#include <vector>
#include <format>
#include <stdexcept>

using namespace std;
using namespace std::filesystem;

vector<int> readIntegerFile(string_view fileName)
{
    ifstream inputstream{ fileName.data() };
    if (inputstream.fail())
    {
        throw invalid_argument{ "unable to open the file" };
    }

    vector<int> ints;
    int temp;
    while (inputstream >> temp)
    {
        ints.push_back(temp);
    }

    if (!inputstream.eof())
    {
        throw runtime_error{ " Error reading the files" };
    }

    return ints;
}

void test1401()
{
    path pth{ current_path() };
    pth /= "day14.tt";

    try
    {
        vector<int> result = readIntegerFile(pth.string());
        for (const auto& value : result)
        {
            cout << value << " ";
        }
        cout << endl;

    }
    catch (const invalid_argument& e)
    {
        cout << " open file fail " << e.what() << endl;
    }
    catch (const runtime_error& e)
    {
        cout << " read file error " << e.what() << endl;
    }
    catch (...)
    {
        cout << " occur other error " << endl;
    }
}

class FileError : public exception
{
public:
    FileError(string filename) : m_filename {move(filename)} {}
    const char* what() const noexcept override { return m_message.c_str(); }
    virtual const string& getFileName() const noexcept { return m_filename; }
protected:
    virtual void setMessage(string message) { m_message = move(message); }

private:
    string m_filename;
    string m_message;
};

class FileOpenError : public FileError
{
public:
    FileOpenError(string fileName) :FileError{ move(fileName) }
    {
        setMessage(format("unable to open {}", getFileName()));
    }
};

class FileReadError : public FileError
{
public:
    FileReadError(string filename, size_t lineNumber) : FileError{ move(filename) }, m_lineNumber{ lineNumber }
    {
        setMessage(format("Error reading {}, line {}", getFileName(), lineNumber));
    }

    virtual size_t getlineNumber() const noexcept { return m_lineNumber; }
private:
    size_t m_lineNumber{ 0 };
};

void logMessage(string_view message, const source_location& location = source_location::current())
{
    cout << format("{}({}): {}: {}", location.file_name(), location.line(), location.function_name(), message) << endl;
}

void test1402()
{
    logMessage("starting exception of test ");
}

class Myexception : public exception
{
public:
    Myexception(string message, source_location location = source_location::current())
        :m_message{ move(message) }, m_location{ location } {}
    
    const char* what() const noexcept override { return m_message.c_str(); }
    virtual const source_location& where()const noexcept { return m_location; }
private:
    string m_message;
    source_location m_location;
};

void doSomethingException()
{
    throw Myexception("throwing myexception");
}

void test1403()
{
    try
    {
        doSomethingException();
    }
    catch (const Myexception& e)
    {
        const auto& location{ e.where() };
        cout << format("Caught:'{}' at line {} in  {} filename:{}",
            e.what(), location.line(), location.function_name(), location.file_name()) << endl;
    }
}

class MyNestException : public exception
{
public:
    MyNestException(string name) : m_message{ move(name) } {}
    virtual const char* what() const noexcept override { return m_message.c_str(); }
private:
    string m_message;
};

void doSomeNestException()
{
    try
    {
        throw runtime_error{ "Throwing a runtime_error exception" };
    }
    catch (const runtime_error& e)
    {
        cout << format("{} caught a runtime_error ", __func__) << endl;
        throw_with_nested(MyNestException{ "MyNestException with nested runtime_error" });
    }
}

void test1404()
{
    try
    {
        doSomeNestException();
    }
    catch (const MyNestException& e)
    {
        cout << format("{} caught Myexception: {}", __func__, e.what()) << endl;
            
        const auto* nest{ dynamic_cast<const nested_exception*>(&e) };
        if (nest)
        {
            try
            {
                nest->rethrow_nested();
            }
            catch (const runtime_error& re)
            {
                cout << format(" nested exception {}", e.what()) << endl;
            }
        }

        try
        {
            rethrow_if_nested(e);
        }
        catch (const runtime_error& rerror)
        {
            cout << format("if nestthrow {} ", e.what()) << endl;
        }
    }
}

int main14()
{
    test1404();
    system("pause");
    return 0;
}

