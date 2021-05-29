#pragma once

#include <Simulation/simulationclock.h>

#include <Scene/view.h>
#include <Scene/movableview.h>
#include <Scene/fixedview.h>
#include <Common/controller.h>

class SceneManager
{
protected:
    std::unique_ptr<MovableView> m_main_view;     ///< View list to draw and update
    SimulationClock m_simu_clock;                   ///< Simulation time manager
    int m_screen_width;	///< Screen/frame width, pixels
    int m_screen_height;	///< Screen/frame height, pixels
    bool m_is_running;                              ///< true when playing a simulation or record
    bool m_is_paused;                               ///< true when pausing a simulation or record
    unsigned long long m_simu_start;                ///< Simulation time start date
    unsigned long long m_simu_end;                  ///< Simulation time end date
    std::unique_ptr<Controller> m_controller;
    std::string m_label;
    bool m_needs_view_update;

public:
    SceneManager();

    virtual ~SceneManager();
    
    /*!
     * \brief initiate the default views 
     */
    virtual void init();

    /*!
     * \brief update the simulation timestamp and updates the GeographicalObject reference of the Objects
     * \return return the new simulation timestamp 
     */
    virtual double update();

    virtual void realUpdate(double t);

    /*!
     * \brief Update the resolution of the scene
     */
    virtual void resize(QVector2D& size);

    /*!
     * \brief update the simulation timestamp and updates the GeographicalObject reference of the Objects
     * \return return the new simulation timestamp 
     */
    virtual void needsViewUpdate();
    
    /*!
     * \brief simply draws the scene views
     */
    virtual void draw();


    virtual MovableView* getMainView() { return m_main_view.get(); };
    
    virtual Controller* getController() { return m_controller.get(); };
    
    /*!
     * \brief start starts a simulation / replay: animates the required
     * data, and counts time from simu start to simu end.
     */
    virtual void start();

    /*!
     * \brief stop stops the simulation and reinitializes current simu time.
     */
    virtual void stop();

    /*!
     * \brief pause pauses the simulation (it keeps current time)
     */
    virtual void pause();

    /*!
     * \brief setSimulationTimeScale defines the simulation speed up
     * \param s the number of seconds elapsed in simulation for each real time second.
     */
    virtual void setSimulationTimeScale(double s) {
        m_simu_clock.setTimeScale(s, !m_is_paused);
    }

    /*!
     * \brief setSimulationStartTime defines the time (may be the date) the simulation
     * is starting from.
     * \param d the time/date in seconds
     */
    virtual void setSimulationStartTime(unsigned long long d) {
        m_simu_start = d;
    }

    /*!
     * \brief setSimulationEndTime defines the time (may be the date) the simulation
     * is ending.
     * \param d the time/date in seconds
     */
    virtual void setSimulationEndTime(unsigned long long d) {
        m_simu_end = d;
    }

    /*!
     * \brief setSimulationCurrentTime defines current time in simulation
     * \param d the current time in seconds
     */
    virtual void setSimulationCurrentTime(unsigned long long d) {
        m_simu_clock.setCurrentTime(d);
        needsViewUpdate();
    }

    virtual bool isRunning() { return m_is_running; };
    virtual bool isPaused() { return m_is_paused; };

    virtual void updateLabel(QVector2D pos);
    virtual std::string getLabel() { return m_label; };

    virtual double getCurrentTime() { return m_simu_clock.getCurrentTime(); };

    virtual void drawCheckboxes(QWidget*, QVBoxLayout*) {};

    virtual void setWindowSize(QVector2D& s);

    virtual void wheelEvent(QWheelEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
};
