/**
 * \file	Bbox.h
 */

#ifndef BBOX_H
#define BBOX_H

#include "ogr_geometry.h"
#include <memory>


class Bbox: public OGRLinearRing {

    public:
        //*/ -------------------------------------------------
        Bbox();
        virtual ~Bbox();

        Bbox(Bbox& bbox);
        Bbox(double minx, double maxx, double miny, double maxy);

        //*/ -------------------------------------------------
        void update(OGRPoint* point);
        void update(const Bbox& bbox);
        void set(double minx, double maxx, double miny, double maxy);
        void set(Bbox& bbox);
        void setWGS84Bbox(OGRPoint* point, int width, int height, const int zoom);
        void clear();

        Bbox& operator =(const std::tuple<double, double, double, double>& bbox);
        Bbox& operator =(Bbox& bbox);
        bool operator !=(Bbox& bbox);
        friend std::ostream& operator <<(std::ostream& os, Bbox& me);

        //*/ -------------------------------------------------
        std::shared_ptr<OGRPoint> getBL();
        std::shared_ptr<OGRPoint> getBR();
        std::shared_ptr<OGRPoint> getTL();
        std::shared_ptr<OGRPoint> getTR();

        //*/ -------------------------------------------------
        double minx = 0;
        double miny = 0;
        double maxx = 0;
        double maxy = 0;

        double width = 0;
        double height = 0;
        double diagonal = 0;

        //*/ -------------------------------------------------
        void createOGRPoints();
        bool first = true;
};

#endif // BBOX_H
