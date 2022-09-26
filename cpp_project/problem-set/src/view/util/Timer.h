#ifndef PROBLEM_SET_UTIL_TIMER_H
#define PROBLEM_SET_UTIL_TIMER_H
#include <chrono>
class ScopedTimer {
    public:
        ScopedTimer(const char* name)
        : m_name(name),
        m_beg(std::chrono::high_resolution_clock::now()) { }
        ~ScopedTimer() {
            auto end = std::chrono::high_resolution_clock::now();
            auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_beg);
            std::cout << m_name << " : " << dur.count() << " ns\n";
        }
    private:
        const char* m_name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
};
#endif //PROBLEM_SET_UTIL_TIMER_H