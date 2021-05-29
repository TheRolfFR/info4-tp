/**
 * \file	GeologicGeometricalObject.cpp
 * \class	GeologicGeometricalObject
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of GeologicGeometricalObject object
 *
 * \details Methods of GeologicGeometricalObject object
 * GeologicGeometricalObject is a way to store generic geometrical algorithms such as computing crossing points or checking if a point is contained in a segment
 * /// TODO check real usage of this class
 */

#include "geologic-core/graphicTemplates/GeologicGeometricalObject.h"

using namespace customToolbox;
using namespace std;

/**
 * \brief 	Default constructor of class GeologicGeometricalObject
 *
 * \param 	None
 * \return 	None
 */
GeologicGeometricalObject::GeologicGeometricalObject() {}

/**
 * \brief 	Default destructor of class GeologicGeometricalObject
 *
 * \param 	None
 * \return 	None
 */
GeologicGeometricalObject::~GeologicGeometricalObject() {}

/**
 * \brief 	Checks whether a GeoPoint is contained in the bounding box formed by two GeoPoints
 *
 * \param 	pointA  The first point making the bounding box
 * \param 	pointB  The second point making the bounding box
 * \param 	pointP  The point to test
 * \return 	true if pointP is contained in the bounding box made by pointA and pointB, false otherwise
 *
 * pointA and pointB do not need specific order. pointP can lay on the edges (and corners) of this bounding box
 */
//bool GeologicGeometricalObject::isPointWithinBounds(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP) {
//    double minX = min(pointA->x, pointB->x);
//    double maxX = max(pointA->x, pointB->x);
//    double minY = min(pointA->y, pointB->y);
//    double maxY = max(pointA->y, pointB->y);
//
//    if (pointP->x >= minX && pointP->x <= maxX) {
//        if (pointP->y >= minY && pointP->y <= maxY) {
//            return true;
//        }
//    }
//    return false;
//}

/**
 * \brief 	Checks whether a GeoPoint lays on a segment formed by two other GeoPoint
 *
 * \param 	pointA  The first point making the bounding box
 * \param 	pointB  The second point making the bounding box
 * \param 	pointP  The point to test
 * \return 	true if pointP lays on the segment made by pointA and pointB, false otherwise
 *
 * pointA and pointB do not need specific order. pointP can be a corner
 */
//bool GeologicGeometricalObject::segmentContainsPoint(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP) {
//    if (this->isPointWithinBounds(pointA, pointB, pointP))
//        if (areEquals((pointP->x - pointA->x)*(pointB->y - pointA->y), (pointP->y - pointA->y)*(pointB->x - pointA->x))) return true;
//    return false;
//}

/**
 * \brief 	Checks whether two segments are overlapping
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	true if the two segments are overlapping, false otherwise
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments are overlapping if they share the same equation and at least have one point in common
 */
//bool GeologicGeometricalObject::areSegmentsOverlapping(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ) {
//    int sumSeg1 = 0;
//    int sumSeg2 = 0;
//    if (segmentContainsPoint(pointA, pointB, pointP)) sumSeg1++;
//    if (segmentContainsPoint(pointA, pointB, pointQ)) sumSeg1++;
//    if (sumSeg1 == 2) return true;
//    if (segmentContainsPoint(pointP, pointQ, pointA)) sumSeg2++;
//    if (segmentContainsPoint(pointP, pointQ, pointB)) sumSeg2++;
//    if (sumSeg2 == 2) return true;
//    if ((sumSeg1+sumSeg2) <= 1) return false;
//    if (areEquals(pointA->x, pointB->x) && areEquals(pointP->x, pointQ->x)) return true;
//    if (areEquals(((pointB->y - pointA->y)/(pointB->x - pointA->x)), ((pointQ->y - pointP->y)/(pointQ->x - pointP->x)))) return true;
//    return false;
//}

/**
 * \brief 	Checks whether two segments are crossing
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	true if the two segments are crossing, false otherwise
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments are crossing if they at least have one point in common
 * Thus they can be collinear, share a corner, or strictly cross
 */
//bool GeologicGeometricalObject::areSegmentsCrossing(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ) {
//
//    bool touchingAB = this->segmentContainsPoint(pointA, pointB, pointP) || this->segmentContainsPoint(pointA, pointB, pointQ);
//    if (touchingAB) return true;
//    bool touchingPQ = this->segmentContainsPoint(pointP, pointQ, pointA) || this->segmentContainsPoint(pointP, pointQ, pointB);
//    if (touchingPQ) return true;
//    bool collinear = this->areSegmentsOverlapping(pointA, pointB, pointP, pointQ);
//    if (collinear) return true;
//
//    double crossProductP = (pointB->x-pointA->x)*(pointP->y-pointB->y) - (pointB->y-pointA->y)*(pointP->x-pointB->x);
//    double crossProductQ = (pointB->x-pointA->x)*(pointQ->y-pointB->y) - (pointB->y-pointA->y)*(pointQ->x-pointB->x);
//    double crossProductA = (pointQ->x-pointP->x)*(pointA->y-pointP->y) - (pointQ->y-pointP->y)*(pointA->x-pointP->x);
//    double crossProductB = (pointQ->x-pointP->x)*(pointB->y-pointP->y) - (pointQ->y-pointP->y)*(pointB->x-pointP->x);
//    bool cPQisNegative = (crossProductP*crossProductQ) < 0.0;
//    bool cABisNegative = (crossProductA*crossProductB) < 0.0;
//    return (cPQisNegative && cABisNegative);
//}

/**
 * \brief 	Checks whether two segments are strictly crossing
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	true if the two segments are strictly crossing, false otherwise
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments are strictly crossing if they at least have one point in common which is not a corner
 * The two segments cannot be collinear nor share a corner
 */
//bool GeologicGeometricalObject::areSegmentsStrictlyCrossing(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ) {
//
//    double crossProductP = (pointB->x-pointA->x)*(pointP->y-pointB->y) - (pointB->y-pointA->y)*(pointP->x-pointB->x);
//    double crossProductQ = (pointB->x-pointA->x)*(pointQ->y-pointB->y) - (pointB->y-pointA->y)*(pointQ->x-pointB->x);
//    double crossProductA = (pointQ->x-pointP->x)*(pointA->y-pointP->y) - (pointQ->y-pointP->y)*(pointA->x-pointP->x);
//    double crossProductB = (pointQ->x-pointP->x)*(pointB->y-pointP->y) - (pointQ->y-pointP->y)*(pointB->x-pointP->x);
//    bool cPQisNegative = (crossProductP*crossProductQ) < 0.0;
//    bool cABisNegative = (crossProductA*crossProductB) < 0.0;
//    return (cPQisNegative && cABisNegative);
//}

/**
 * \brief 	Computes the intersecting point between two segments
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	The address of a GeoPoint representing the crossing point between these two segments
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments need to be crossing. If they are collinear, nullptr is returned.
 * The returned GeoPoint must be deleted by the calling function in order to avoid memory leaks
 */
//GeoPoint* GeologicGeometricalObject::computeIntersection(GeoPoint* pointA, GeoPoint* pointB, GeoPoint* pointP, GeoPoint* pointQ) {
//
//    if (this->areSegmentsOverlapping(pointA, pointB, pointP, pointQ)) return nullptr;
//
//    double crossPosX = ((pointA->x*pointB->y - pointA->y*pointB->x)*(pointP->x - pointQ->x) - (pointA->x - pointB->x)*(pointP->x*pointQ->y - pointP->y*pointQ->x));
//    crossPosX /= ((pointA->x - pointB->x)*(pointP->y - pointQ->y) - (pointA->y - pointB->y)*(pointP->x - pointQ->x));
//    double crossPosY = ((pointA->x*pointB->y - pointA->y*pointB->x)*(pointP->y - pointQ->y) - (pointA->y - pointB->y)*(pointP->x*pointQ->y - pointP->y*pointQ->x));
//    crossPosY /= ((pointA->x - pointB->x)*(pointP->y - pointQ->y) - (pointA->y - pointB->y)*(pointP->x - pointQ->x));
//
//    //return (new GeoPoint(crossPosX, crossPosY, 0.0, pointA->cs)); //should be deleted by the caller !!
//    return (new GeoPoint(crossPosX, crossPosY, 0.0)); //should be deleted by the caller !!
//}








/**
 * \brief 	Checks whether a OGRPoint is contained in the bounding box formed by two GeoPoints
 *
 * \param 	pointA  The first point making the bounding box
 * \param 	pointB  The second point making the bounding box
 * \param 	pointP  The point to test
 * \return 	true if pointP is contained in the bounding box made by pointA and pointB, false otherwise
 *
 * pointA and pointB do not need specific order. pointP can lay on the edges (and corners) of this bounding box
 */
//bool GeologicGeometricalObject::isPointWithinBounds(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP) {
//    return false;
//}

/**
 * \brief 	Checks whether a OGRPoint lays on a segment formed by two other OGRPoint
 *
 * \param 	pointA  The first point making the bounding box
 * \param 	pointB  The second point making the bounding box
 * \param 	pointP  The point to test
 * \return 	true if pointP lays on the segment made by pointA and pointB, false otherwise
 *
 * pointA and pointB do not need specific order. pointP can be a corner
 */
//bool GeologicGeometricalObject::segmentContainsPoint(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP) {
//    return false;
//}

/**
 * \brief 	Checks whether two segments are overlapping
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	true if the two segments are overlapping, false otherwise
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments are overlapping if they share the same equation and at least have one point in common
 */
//bool GeologicGeometricalObject::areSegmentsOverlapping(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ) {
//    return false;
//}

/**
 * \brief 	Checks whether two segments are crossing
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	true if the two segments are crossing, false otherwise
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments are crossing if they at least have one point in common
 * Thus they can be collinear, share a corner, or strictly cross
 */
//bool GeologicGeometricalObject::areSegmentsCrossing(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ) {
//    return (false);
//}

/**
 * \brief 	Checks whether two segments are strictly crossing
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	true if the two segments are strictly crossing, false otherwise
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments are strictly crossing if they at least have one point in common which is not a corner
 * The two segments cannot be collinear nor share a corner
 */
//bool GeologicGeometricalObject::areSegmentsStrictlyCrossing(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ) {
//    return false;
//}

/**
 * \brief 	Computes the intersecting point between two segments
 *
 * \param 	pointA  The first point making the first segment
 * \param 	pointB  The second point making the first segment
 * \param 	pointP  The first point making the second segment
 * \param 	pointQ  The second point making the second segment
 * \return 	The address of a OGRPoint representing the crossing point between these two segments
 *
 * pointA and pointB do not need specific order. pointP and pointQ do not need specific order.
 * The two segments need to be crossing. If they are collinear, nullptr is returned.
 * The returned OGRPoint must be deleted by the calling function in order to avoid memory leaks
 */
//OGRPoint* GeologicGeometricalObject::computeIntersection(OGRPoint* pointA, OGRPoint* pointB, OGRPoint* pointP, OGRPoint* pointQ) {
//    return nullptr;
//}
