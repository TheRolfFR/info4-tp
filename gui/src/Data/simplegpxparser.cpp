#include <Data/simplegpxparser.h>
#include <QXmlInputSource>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QtOpenGL/QtOpenGL>
#include <algorithm>

#include <iostream>
#include <Common/utils.hpp>

using namespace std;

void SimpleGPXParser::parseSegment(QXmlStreamReader &reader) {
    TrackSequence trkseq;
    QXmlStreamReader::TokenType tok = reader.readNext();
    while (!reader.atEnd() && !reader.hasError() /*&& tok != QXmlStreamReader::EndElement*/) {
        if (reader.name().toString() == "trkpt")
            trkseq.track.push_back(parsePoint(reader));
//        else
        tok = reader.readNext();
//        cout << reader.name().toString().toStdString() << endl;
        if (tok == QXmlStreamReader::EndElement && reader.name().toString() == "trkseg") {
            trkseq.current = trkseq.track.begin();
            _sequences.push_back(move(trkseq));
            break;
        }
    }
}

TSPoint SimpleGPXParser::parsePoint(QXmlStreamReader &reader) {
    TSPoint trkpt;
    QXmlStreamReader::TokenType tok = reader.tokenType();
    while (!reader.atEnd() && !reader.hasError() /*&& tok != QXmlStreamReader::EndElement*/) {
        if (reader.name().toString() == "trkpt") {
            trkpt.location.setX(reader.attributes().value("lon").toDouble());
            trkpt.location.setY(reader.attributes().value("lat").toDouble());
            trkpt.location.assignSpatialReference(_georef.get());
        } else if (reader.name().toString() == "time" && tok == QXmlStreamReader::StartElement) {
            tok = reader.readNext();
            trkpt.timestamp = QDateTime::fromString(reader.text().toString(), "yyyy-MM-ddThh:mm:ssZ");
        }
        tok = reader.readNext();
        if (tok == QXmlStreamReader::EndElement && reader.name().toString() == "trkpt") {
            break;
        }
    }
    return trkpt;
}

SimpleGPXParser::SimpleGPXParser() {
    _georef = make_unique<OGRSpatialReference>();
    _georef->importFromEPSG(4326); // Create a WGS84 spatial reference to assign to track points
}

void SimpleGPXParser::parseFile(const char *filename) {
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QXmlStreamReader reader(&f);
    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType tok = reader.readNext();
        if (tok == QXmlStreamReader::StartElement) {
            if (reader.name().toString() == "trkseg") {
                //cout << "Segment" << endl;
                parseSegment(reader);
            } else {
                tok = reader.readNext();
            }
        }
    }
}

void SimpleGPXParser::parseDir(const char *filename) {
    QDir directory(filename);
    if (directory.exists()) {
        QStringList filter;
        QString base_name(filename);
        filter << "*.gpx";
        directory.setNameFilters(filter);
        auto files = directory.entryList();
        if (filename[strlen(filename)-1] != '/') {
            base_name += "/";
        }
        for (const auto &file: files) {
            parseFile((base_name + file).toStdString().c_str());
        }
    }
}

GPXData::GPXData(const char *name, OGRSpatialReference *v): Data(name), _viewref(v) {
    transform = OGRCreateCoordinateTransformation(parser.getGeoRef().get(), _viewref);
}

void GPXData::loadFile(const char *name) {
    parser.parseFile(name);
}

void GPXData::loadDir(const char *name) {
    parser.parseDir(name);
}
/*
void GPXData::draw() {
    // Draw all ?
}

void GPXData::draw(unsigned long long t) {
    vector<TrackSequence> &tracks = parser.getTracks();
    glColor4d(track_color.red, track_color.green, track_color.blue, track_color.alpha);
    glPointSize(static_cast<GLfloat>(points_size));
    glBegin(GL_POINTS);
    for (TrackSequence &seq: tracks) {
        if (seq.track.empty())
            continue;
        // Find the right element given time
        auto it = find_if(seq.track.begin(), seq.track.end(), [t](const TSPoint &p){
            return p.timestamp.time().msecsSinceStartOfDay()/1000 > t;
        });
        // Three cases:
        // 1) we are before the beginning of the track: display first location
        if (it == seq.track.begin()) {
            if (it->location.getSpatialReference()->IsSame(_viewref) == 0)
                it->location.transform(transform);
            glVertex3d(it->location.getX(), it->location.getY(), it->location.getZ());
        } else if (it == seq.track.end()) {
            // 2) we are at the end of the track: display last location
            if (seq.track.back().location.getSpatialReference()->IsSame(_viewref) == 0)
                seq.track.back().location.transform(transform);
            glVertex3d(seq.track.back().location.getX(), seq.track.back().location.getY(), seq.track.back().location.getZ());
        } else {
            // 3) t is during the track: interpolate location between *(it-1) and *it
            if (it->location.getSpatialReference()->IsSame(_viewref) == 0)
                it->location.transform(transform);
            if ((it-1)->location.getSpatialReference()->IsSame(_viewref) == 0)
                (it-1)->location.transform(transform);
            unsigned long long start_t = (it-1)->timestamp.time().msecsSinceStartOfDay()/1000;
            unsigned long long end_t = it->timestamp.time().msecsSinceStartOfDay()/1000;
            double advance = (t - end_t) / (start_t - end_t);
            glVertex3d((1.0 - advance) * (it-1)->location.getX() + advance * it->location.getX(),
                       (1.0 - advance) * (it-1)->location.getY() + advance * it->location.getY(),
                       (1.0 - advance) * (it-1)->location.getZ() + advance * it->location.getZ());
        }
    }
    glEnd();
}*/
