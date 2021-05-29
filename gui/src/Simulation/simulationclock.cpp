#include "Simulation/simulationclock.h"
#include <cstdlib>
#include <iostream>

using namespace std;

SimulationClock::SimulationClock(): time_scale(60), initial_ts(60), initial_time(0),
                                    current_time(0.0),
                                    running(false) {
}

double SimulationClock::getCurrentTime() const {
    return current_time;
}

double SimulationClock::getInitialTime() const {
    return initial_time;
}

void SimulationClock::start() {
    running = true;
    time_scale = initial_ts;
    gettimeofday(&initial_rt, NULL);
}

void SimulationClock::pause() {
    time_scale = 0;
    initial_time = static_cast<double>(current_time);
}

void SimulationClock::stop() {
    current_time = initial_time;
    running = false;
}

void SimulationClock::update() {
    if (running) {
        struct timeval current;
        gettimeofday(&current, NULL);
        double t = static_cast<double>(current.tv_sec - initial_rt.tv_sec) +
                   static_cast<double>(current.tv_usec - initial_rt.tv_usec) / 1000000.0;
        current_time += t * time_scale;
        initial_rt = current;
    }
}

void SimulationClock::setCurrentTime(double currentTime) {
    current_time = currentTime;
}

void SimulationClock::setTimeScale(double timeScale, bool isRunning) {
    initial_ts = timeScale;
    if (isRunning) time_scale = timeScale;
}

void SimulationClock::setInitialTime(double initialTime) {
    current_time = initial_time = initialTime;
}

SimulationClock::~SimulationClock() {
    //cout << "SimulationClock::~SimulationClock()" << endl;
}
