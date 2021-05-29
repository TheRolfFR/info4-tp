/**
 * \file	DataManager.h
 */

#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <ogr_geometry.h>
class SignalManager {

    public:
        // -------------------------------------------------
        SignalManager();
        virtual ~SignalManager();

        // -------------------------------------------------
        virtual void hoverTrackSignal(OGRPoint* location, time_t t) = 0;
        virtual void hoverClickSignal(OGRPoint* location, time_t t) = 0;
        virtual void hoverReleaseSignal() = 0;

};
#endif // SIGNALMANAGER_H
