#include <iostream>
#include <thread>
#include <chrono>
#include <syncstream>
#include <mutex>
#include <atomic>
#include <format>
#include <vector>

using namespace std;

std::atomic_flag spinlock = ATOMIC_FLAG_INIT;
static const size_t NumberofThread{ 50 };
static const size_t LoopsPerThread{ 100 };

void dowork(size_t threadNumber, vector<size_t>& data)
{
    for (size_t i = 0; i < LoopsPerThread; ++i)
    {
        while(spinlock.test_and_set()){}

        data.push_back(threadNumber);
        spinlock.clear();
    }
}

void test2701()
{
    vector<size_t> data;
    vector<thread> threads;
    for (size_t i = 0; i < NumberofThread; i++)
    {
        threads.push_back(thread{ dowork, i, ref(data) });
    }

    for (auto& t :threads)
    {
        t.join();
    }

    cout << format("data contains {} elements expected{}.\n", data.size(), NumberofThread * LoopsPerThread);
}

once_flag g_once_flag;

void initializeShareResources()
{
    cout << "resource share initialized " << endl;
}

void processFunction()
{
    call_once(g_once_flag, initializeShareResources);
    cout << "Processing " << endl;
}

void test2702()
{
    vector<thread> threads{ 3 };
    for (auto& t : threads)
    {
        t = thread{ processFunction };
    }

    for(auto& t : threads)
    {
        t.join();        
    }
}

void increment(atomic<int>& counter)
{
    for (int i{ 0 }; i < 100; ++i)
    {
        ++counter;
        this_thread::sleep_for(1ms);
    }
}

void test2703()
{
    atomic<int>counter{ 0 };
    vector<thread> threads;
    threads.reserve(10);
    for (int i{ 0 }; i < 10; ++i)
    {
        threads.push_back(thread{ increment, ref(counter) });
    }

    for (auto& t :threads)
    {
        t.join();
    }
    
    cout << "Result =" << counter << endl;
}

class Counter
{
public:
    Counter(int id, int numberIterator): m_id{id}, m_number{numberIterator}{}
    void operator()() const
    {
        for (int i {0}; i < m_number; ++i)
        {
           // osyncstream{ cout } << "Counter " << m_id << " has value " << i << endl;
            lock_guard lock{ ms_mutex };
            cout << "Counter " << m_id << " has value " << i << endl;

        }
    }
private:
    int m_id;
    int m_number;
    inline static mutex ms_mutex;
};

void test2704()
{
    atomic<int>counter{ 0 };
    vector<thread> threads;
    threads.reserve(10);
    for (int i{ 0 }; i < 10; ++i)
    {
        threads.push_back(thread{ Counter{i, 10} });
    }

    for (auto& t : threads)
    {
        t.join();
    }
}

int main()
{    
    test2704();
    system("pause");
}