#include <chrono>
using namespace std::chrono;

typedef high_resolution_clock Clock;

// Credit: Amanpreet Kapoor - Algorithmic Analysis-1.pdf

// Simple Timer class to streamline time measurement
class Timer {
private:
    Clock::time_point t1 = Clock::now();
    Clock::time_point t2 = Clock::now();
public:
    // Start the timer
    void start() {t1 = Clock::now();}
    // Stop the timer
    void stop() {t2 = Clock::now();}
    // Return the time elapsed in seconds
    double time() {
        return duration_cast<duration<double>>(t2 - t1).count();
    }
    // Return the time elapsed in nanoseconds
    long long timeNS() {
        return duration_cast<nanoseconds>(t2 - t1).count();
    }
};