#ifndef SIMPLEGPXPARSER_H
#define SIMPLEGPXPARSER_H

#include <Data/data.h>
#include <Common/color.h>
#include <QXmlStreamReader>
#include <QDateTime>
#include <ogr_geometry.h>
#include <ogr_spatialref.h>
#include <vector>
#include <memory>

/*!
 * \brief The TSPoint struct stores a track point with a timestamp and a location
 */
struct TSPoint {
    OGRPoint location;
    QDateTime timestamp;
};

/*!
 * \brief The TrackSequence struct is used to store the track points
 * and an iterator to the current point being rendered.
 */
struct TrackSequence {
    std::vector<TSPoint> track;
    std::vector<TSPoint>::const_iterator current;
};

class SimpleGPXParser {
    std::unique_ptr<OGRSpatialReference> _georef;
    std::vector<TrackSequence> _sequences;

    void parseSegment(QXmlStreamReader &reader);
    TSPoint parsePoint(QXmlStreamReader &reader);

public:
    SimpleGPXParser();
    ~SimpleGPXParser() {}
    void parseFile(const char *filename);
    void parseDir(const char *filename);
    std::unique_ptr<OGRSpatialReference> acquireGeoRef() {return std::move(_georef);}
    std::vector<TrackSequence> acquireTracks() {return std::move(_sequences);}
    const std::unique_ptr<OGRSpatialReference> &getGeoRef()const {return _georef;}
    std::vector<TrackSequence> &getTracks() {return _sequences;}
};

class GPXData: public Data {
    SimpleGPXParser parser;
    Color track_color = {1.0, 1.0, 1.0, 1.0};
    double points_size = 2.0;
    OGRSpatialReference *_viewref;
    OGRCoordinateTransformation *transform = nullptr;

public:
    GPXData(const char *name, OGRSpatialReference *v);
    ~GPXData() {}
    void setColor(const Color &c) {track_color = c;}
    void setPointSize(double s) {points_size = s;}
    void loadFile(const char *name);
    void loadDir(const char *name);
    //virtual void draw() override;
    //virtual void draw(unsigned long long t) override;
};

#endif // SIMPLEGPXPARSER_H
