#include <iostream>
#include <functional>

using namespace std;

class GameTest;
int defaultHealthCalc(const GameTest& ct)
{
    return 2;
}

class GameTest
{
public:
    typedef std::function<int (const GameTest&)> HealthCalcFunc;
    explicit GameTest(HealthCalcFunc hcf = defaultHealthCalc): healthFunc {hcf}{}
    int healthValue() const
    {
        return healthFunc (*this);
    }
private:
    HealthCalcFunc healthFunc;
};

short calcHealth(const GameTest&)
{
    cout << "short return value" << endl;
    return 11;
}

struct HealthCalculator {
    int operator()(const GameTest&) const
    {
        cout << "struct health " << endl;
        return 111;
    }
};

class GameLevel
{
public:
    float health(const GameTest&) const
    {
        cout << "Game level return value" << endl;
        return 1.234;
    }
};

class EvilBadGuy :public GameTest
{
public:
explicit EvilBadGuy(HealthCalcFunc hcf=defaultHealthCalc) :GameTest{hcf}{}
};

class EyeCandy : public GameTest
{
public:
    explicit EyeCandy(HealthCalcFunc hcf=defaultHealthCalc) : GameTest(hcf){}
};

void testItem01()
{
    EvilBadGuy ebg1(calcHealth);
    cout << ebg1.healthValue() << endl;

    //    HealthCalculator hc;
    // EyeCandy ec(hc);
    // EyeCandy ec ( HealthCalculator()) : �����Ǿ���most vexing parse�����⣬�����ʽ��heal������һ������
    // ����ʹ��ͳһ��ʼ������ ����չʾ
    EyeCandy ec{ HealthCalculator() };
    cout << ec.healthValue() << endl;

    GameLevel currentLevel;
    EvilBadGuy ebg2(std::bind(&GameLevel::health, currentLevel, std::placeholders::_1));
    cout << ebg2.healthValue() << endl;
}

int mainitem31()
{
    testItem01();
    system("pause");
    return 1;
}

