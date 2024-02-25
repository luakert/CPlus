#include <iostream>
#include <string>

using namespace std;

class Fish;
class Bear;
class TRex;
// Ë«·ÖÅÉ
class Animal
{
public:
    virtual bool eats(const Animal& prey) const = 0;
    virtual bool eatenBy(const Bear&) const = 0;
    virtual bool eatenBy(const Fish&) const = 0;
    virtual bool eatenBy(const TRex&) const = 0;
};

class Bear : public Animal
{
public:
    bool eats(const Animal& prey) const override {
        return prey.eatenBy(*this);
    }

    bool eatenBy(const Bear&) const override { return false; }
    bool eatenBy(const Fish&) const override { return false; }
    bool eatenBy(const TRex&) const override { return true; }
};

class Fish : public Animal
{
public:
    bool eats(const Animal& prey) const override {
        return prey.eatenBy(*this);
    }

    bool eatenBy(const Bear&) const override { return true; }
    bool eatenBy(const Fish&) const override { return true; }
    bool eatenBy(const TRex&) const override { return true; }
};

class TRex : public Animal
{
public:
    bool eats(const Animal& prey) const override {
        return prey.eatenBy(*this);
    }

    bool eatenBy(const Bear&) const override { return false; }
    bool eatenBy(const Fish&) const override { return false; }
    bool eatenBy(const TRex&) const override { return true; }
};
int main2()
{
    cout << "hello world" << endl;
    system("pause");
    return 0;
}