#pragma once

#include <chrono>
#include <string>
#include <iostream>

class Timer
{
private:
    std::string m_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTp;

public:
    Timer(const std::string &name = "Timer") : m_name(name)
    {

        m_startTp = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        auto endTp = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTp).time_since_epoch().count();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTp).time_since_epoch().count();

        std::cout << m_name << ": " << ((end - start) * 0.001l) << " ms\n";
    }
};
