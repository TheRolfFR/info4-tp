/**
 * \file	customToolbox.h
 */

#ifndef CUSTOMTOOLBOX_H
#define CUSTOMTOOLBOX_H

#define _USE_MATH_DEFINES

#include <assert.h>
#include <algorithm>
#include <ctime>
#include <map>
#include <utility>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <tuple>
#include <ogr_geometry.h>
#include <unordered_map>


namespace customToolbox {

    typedef unsigned char byte;

    std::string str(double val, unsigned int precision);
    template<typename T> std::string str(T val);
    template<typename T> int len(T val);
    template<typename T> void printElement(T t, const int& width, bool alignLeft=true);
    template<typename T> bool isIn(std::vector<T> table, T t);
    template<typename T> std::unordered_map<std::string, T> generateTimeSlotsMap(unsigned int pas, std::string unit="minutes");

    std::string str(struct tm* val, bool hour=false);
    std::string str(time_t val, bool hour=false);

    std::vector<std::string> split(std::string str, std::string delimiter);
    std::vector<std::string> split(std::string str, char delimiter);
    std::vector<std::string> fsplit(std::string str, char delimiter);

    struct tm str2structtm(std::string datetime, std::string format="DD/MM/YYYY HH:MM:SS");
    time_t str2timet(std::string datetime, std::string format="DD/MM/YYYY HH:MM:SS");
    time_t _mkgmtime(const struct tm* tm);

    struct tm lowerTimestamp(struct tm& timestamp, int duration);
    time_t lowerTimestamp(time_t timestamp, int duration);

    time_t getYesterdatetimet();
    std::string getYesterdatetime();
    std::string getYesterdate();

    std::vector<std::string> generateTimeSlots(unsigned int pas, std::string unit="minutes");


    int flip(const byte *b);
    int toInt(const byte *b);
    double toDouble(const byte *b);
    bool areEquals(double a, double b, double epsilon=0.00001);

    bool isIn(int* table, int sizeTable, int value);
    bool isIn(std::vector<std::string>, std::string value);
    void insertMap(std::map<std::string, std::string>& destMap, std::map<std::string, std::string>* origMap);
    bool isZeros(std::vector<double> tab);
    bool isZeros(std::vector<int> tab);

    void print(std::vector<double> tab);
    void print(std::vector<int> tab);

    double min(std::vector<double> tab);
    int min(std::vector<int> tab);
    double max(std::vector<double> tab);
    int max(std::vector<int> tab);
    double sum(std::vector<double> tab);
    double sum(std::vector<int> tab);
    double mean(std::vector<double> tab);
    double mean(std::vector<int> tab);
    double variance(std::vector<double> tab);
    double variance(std::vector<int> tab);
    double stddev(std::vector<double> tab);
    double stddev(std::vector<int> tab);
    double stdsco(std::vector<double> tab, double val);
    double stdsco(std::vector<int> tab, int val);
    double stdsco(unsigned int pos, std::vector<double> tab);
    double stdsco(unsigned int pos, std::vector<int> tab);
    double covariance(std::vector<double> tab1, std::vector<double> tab2);
    double covariance(std::vector<int> tab1, std::vector<int> tab2);
    double sampleCovariance(std::vector<double> tab1, std::vector<double> tab2);
    double sampleCovariance(std::vector<int> tab1, std::vector<int> tab2);
    double customCorrelation(std::vector<double> tab1, std::vector<double> tab2);
    double customCorrelation(std::vector<int> tab1, std::vector<int> tab2);
    double BPcorrelation(std::vector<double> tab1, std::vector<double> tab2);
    double BPcorrelation(std::vector<int> tab1, std::vector<int> tab2);
    double customDecreasingCorrelation(std::vector<double> tab1, std::vector<double> tab2);
    double customDecreasingCorrelation(std::vector<int> tab1, std::vector<int> tab2);
    double decreasingBPCorrelation(std::vector<double> tab1, std::vector<double> tab2);
    double decreasingBPCorrelation(std::vector<int> tab1, std::vector<int> tab2);
    double diffs(std::vector<double> tab1, std::vector<double> tab2);
    double diffs(std::vector<int> tab1, std::vector<int> tab2);
    std::pair<double, double> coeffs(std::vector<double> tab1, std::vector<double> tab2);
    std::pair<double, double> coeffs(std::vector<int> tab1, std::vector<int> tab2);

    void start(const char* func);
    void end(const char* func);
    void message(const char* msg, ...);
}
#include "geologic-core/utils/customToolbox_impl.h"
#endif // CUSTOMTOOLBOX_H
