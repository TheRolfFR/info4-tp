#ifndef SIMULATIONCLOCK_H
#define SIMULATIONCLOCK_H

#include <sys/time.h>

class SimulationClock {
private:
    double time_scale;
    double initial_ts;
    double initial_time;
    double current_time;
    struct timeval initial_rt; // Used to compute the time between two updates.
    bool running;

public:
    SimulationClock();
    virtual ~SimulationClock();
    virtual void start();
    virtual void pause();
    virtual void stop();
    virtual void update();
    double getCurrentTime() const;
    double getInitialTime() const;
    void setInitialTime(double initialTime);
    void setTimeScale(double timeScale, bool isRunning=true);
    void setCurrentTime(double currentTime);
};

#endif // SIMULATIONCLOCK_H
