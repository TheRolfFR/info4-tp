/**
 * \file	customToolbox.cpp
 * \class	customToolbox
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	03/09/2015
 * \brief	Methods of customToolbox object
 *
 * \details Methods of customToolbox object
 */

#include "geologic-core/utils/customToolbox.h"

namespace customToolbox {

    int level = 0;

    /**
     * \brief 	Returns a string corresponding to the date passed in parameters
     *
     * \param 	datetime The value to transform
     * \param   hour        If true will return only the hour
     * \return 	The string corresponding to that value
     *
     * The default format for that string date is <DD/MM/YYYY HH:MM:SS>
     */
    std::string str(struct tm* datetime, bool hour) {
        char date[11];
        char time[9];
        date[10] = '\0';
        time[8] = '\0';

        strftime(date, 11, "%d/%m/%Y", datetime);
        strftime(time, 9, "%H:%M:%S", datetime);

        if (hour) return str(time);
        return (customToolbox::str(date)+" "+customToolbox::str(time));
    }

    /**
     * \brief 	Returns a string corresponding to the date passed in parameters
     *
     * \param 	datetime The value to transform
     * \param   hour        If true will return only the hour
     * \return 	The string corresponding to that value
     *
     * The default format for that string date is <DD/MM/YYYY HH:MM:SS>
     */
    std::string str(time_t datetime, bool hour) {
        return customToolbox::str(gmtime(&datetime), hour);
    }

    /**
     * \brief 	Returns a string corresponding to the value
     *
     * \param 	val The value to transform
     * \return 	The string corresponding to that value
     */
    std::string str(double val, unsigned int precision) {
        std::stringstream out;
        double ent;
        double res = std::modf(val, &ent);
        if (areEquals(res, 0)) {
            out << std::setprecision(precision) << val;
        } else {
            out << std::fixed << std::setprecision(precision) << val;
        }
        return out.str();
    }

    /**
     * \brief 	Transforms a date into a struct tm object
     *
     * \param 	datetime    The date to transform (string)
     * \param   format      The format corresponding to that string date
     * \return 	The struct tm corresponding to that date
     */
    struct tm str2structtm(std::string datetime, std::string format) {
        char delimiterDateTime = ' ';
        char delimiterDate = '/';
        char delimiterTime = ':';
        struct tm timestamp = {0, 0, 0, 0, 0, 0, 0, 0, -1};

        //defaultformat == "DD/MM/YYYY HH:MM:SS"
        std::vector<std::string> strDatetime = customToolbox::split(datetime, delimiterDateTime);
        int posDateYear = 2;
        int posDateDay = 0;

        if (format == "DD-MM-YYYY HH:MM:SS") {
            delimiterDate = '-';
        } else if (format == "YYYY-MM-DD HH:MM:SS") {
            delimiterDate = '-';
            posDateYear = 0;
            posDateDay = 2;
        } else if (format == "YYYY/MM/DD HH:MM:SS") {
            posDateYear = 0;
            posDateDay = 2;
        }

        std::vector<std::string> strDate = customToolbox::split(strDatetime[0], delimiterDate);
        timestamp.tm_year = atoi(strDate[posDateYear].c_str()) - 1900;
        timestamp.tm_mon = atoi(strDate[1].c_str()) - 1;
        timestamp.tm_mday = atoi(strDate[posDateDay].c_str());

        if (strDatetime.size() > 1) {
            std::vector<std::string> strTime = customToolbox::split(strDatetime[1], delimiterTime);
            timestamp.tm_hour = atoi(strTime[0].c_str());
            timestamp.tm_min = atoi(strTime[1].c_str());
            timestamp.tm_sec = atoi(strTime[2].c_str());
        }

        timestamp.tm_isdst = -1;
        return timestamp;
    }

    /**
     * \brief 	Transforms a date into a time_t
     *
     * \param 	datetime    The date to transform (string)
     * \param   format      The format corresponding to that string date
     * \return 	The time_t corresponding to that date
     */
    time_t str2timet(std::string datetime, std::string format) {
        struct tm timetemp = str2structtm(datetime, format);
        return customToolbox::_mkgmtime(&timetemp);
    }

    /**
     * \brief 	Transforms a date into a time_t
     *
     * \param 	datetime    The date to transform (string)
     * \param   format      The format corresponding to that string date
     * \return 	The time_t corresponding to that date
     */
    time_t _mkgmtime(const struct tm* tm) {
        // Month-to-day offset for non-leap-years.
        static const int month_day[12] =
        {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

        // Most of the calculation is easy; leap years are the main difficulty.
        int month = tm->tm_mon % 12;
        int year = tm->tm_year + tm->tm_mon / 12;
        if (month < 0) {   // Negative values % 12 are still negative.
            month += 12;
            --year;
        }

        // This is the number of Februaries since 1900.
        const int year_for_leap = (month > 1) ? year + 1 : year;

        time_t rt = tm->tm_sec                             // Seconds
            + 60 * (tm->tm_min                          // Minute = 60 seconds
            + 60 * (tm->tm_hour                         // Hour = 60 minutes
            + 24 * (month_day[month] + tm->tm_mday - 1  // Day = 24 hours
            + 365 * (year - 70)                         // Year = 365 days
            + (year_for_leap - 69) / 4                  // Every 4 years is     leap...
            - (year_for_leap - 1) / 100                 // Except centuries...
            + (year_for_leap + 299) / 400)));           // Except 400s.
        return rt < 0 ? -1 : rt;
    }

    /**
     * \brief 	Splits a string according to a specified delimiter
     *
     * \param 	str         The string to split
     * \param   delimiter   The delimiter used to split (string)
     * \return 	A vector of string corresponding to the string split
     */
    std::vector<std::string> split(std::string str, std::string delimiter) {
        std::vector<std::string> internal;
        size_t pos;
        std::string tok;

        while((pos = str.find(delimiter)) != std::string::npos) {
            tok = str.substr(0, pos);
            internal.push_back(tok);
            str.erase(0, pos+delimiter.length());
        }

        internal.push_back(str);

        return internal;
    }

    /**
     * \brief 	Splits a string according to a specified delimiter
     *
     * \param 	str         The string to split
     * \param   delimiter   The delimiter used to split (char)
     * \return 	A vector of string corresponding to the string split
     */
    std::vector<std::string> fsplit(std::string str, char delimiter) {
        std::vector<std::string> internal;
        std::stringstream ss(str);
        std::string tok;

        while(getline(ss, tok, delimiter)) {
            internal.push_back(tok);
        }

        return internal;
    }

    /**
     * \brief 	Splits a string according to a specified delimiter
     *
     * \param 	str         The string to split
     * \param   delimiter   The delimiter used to split (char)
     * \return 	A vector of string corresponding to the string split
     */
    std::vector<std::string> split(std::string str, char delimiter) {
        std::vector<std::string> internal;
        int pos = 0;
        int chunk = 0;
        for (std::string::iterator it = str.begin(); it != str.end(); it++) {
            if ((*it) != delimiter) {
                chunk++;
            } else {
                internal.push_back(str.substr(pos, chunk));
                pos += chunk+1;
                chunk = 0;
            }
        }

        internal.push_back(str.substr(pos, chunk));
        return internal;
    }

    /**
     * \brief 	Computes the down limit of the specified datetime according to time-slices aka. a modulo on time
     *
     * \param 	timestamp   The reference of the datetime to modify
     * \param   duration    The duration of a typical time-slice
     * \return 	The new datetime down to the nearest time-slice
     *
     * Duration is always expressed in seconds and starting from 00:00:00
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 4 gives timestamp = "10/04/2016 00:05:04"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 60 gives timestamp = "10/04/2016 00:05:00"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 120 gives timestamp = "10/04/2016 00:04:00"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 360 gives timestamp = "10/04/2016 00:00:00"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 3600 gives timestamp = "10/04/2016 00:00:00"
     */
    struct tm lowerTimestamp(struct tm& timestamp, int duration) {

        struct tm currentTime = timestamp;
        int oneHour = 60*60;
        int oneDay = oneHour*24;
        int oneWeek = oneDay*7;
        int oneMonth = oneWeek*4;
        int oneYear = oneMonth*12;

        if (duration > 0) {
            currentTime.tm_hour = 0;
            currentTime.tm_min = 0;
            currentTime.tm_sec = 0;

            if (duration >= oneWeek) currentTime.tm_mday = 0;
            if (duration >= oneMonth) currentTime.tm_mon = 0;
            if (duration >= oneYear) currentTime.tm_year = 0;

            int diffSeconds = ((int) (customToolbox::_mkgmtime(&timestamp) - customToolbox::_mkgmtime(&currentTime)) / duration)*duration;

            currentTime.tm_year += (int) diffSeconds/oneYear;
            diffSeconds -= ((int) diffSeconds/oneYear)*oneYear;
            currentTime.tm_mon += (int) diffSeconds/oneMonth;
            diffSeconds -= ((int) diffSeconds/oneMonth)*oneMonth;
            currentTime.tm_mday += (int) diffSeconds/oneDay;
            diffSeconds -= ((int) diffSeconds/oneDay)*oneDay;
            currentTime.tm_hour += (int) diffSeconds/oneHour;
            diffSeconds -= ((int) diffSeconds/oneHour)*oneHour;
            currentTime.tm_min += (int) diffSeconds/60;
            diffSeconds -= ((int) diffSeconds/60)*60;
            currentTime.tm_sec += (int) diffSeconds;
        }
        return currentTime;
    }

    /**
     * \brief 	Computes the down limit of the specified datetime according to time-slices aka. a modulo on time
     *
     * \param 	timestamp   The reference of the datetime to modify
     * \param   duration    The duration of a typical time-slice
     * \return 	The new datetime down to the nearest time-slice
     *
     * Duration is always expressed in seconds and starting from 00:00:00
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 4 gives timestamp = "10/04/2016 00:05:04"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 60 gives timestamp = "10/04/2016 00:05:00"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 120 gives timestamp = "10/04/2016 00:04:00"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 360 gives timestamp = "10/04/2016 00:00:00"
     * \n For example: timestamp = "10/04/2016 00:05:06" with duration of 3600 gives timestamp = "10/04/2016 00:00:00"
     */
    time_t lowerTimestamp(time_t timestamp, int duration) {
//        struct tm timetemp = lowerTimestamp(*localtime(&timestamp), duration);
//        return mktime(&timetemp);
        time_t rt = 0;
        if (duration > 0) {
            rt = ((int) (timestamp/duration))*duration;
        }
        return rt;
    }

    /**
     * \brief 	Gets the datetime of yesterday
     *
     * \param 	None
     * \return 	The yesterday datetime as a string
     */
    time_t getYesterdatetimet() {
        return lowerTimestamp(time(0)-3600*24, 3600*24);
    }

    /**
     * \brief 	Gets the datetime of yesterday
     *
     * \param 	None
     * \return 	The yesterday datetime as a string
     */
    std::string getYesterdatetime() {
        return str(customToolbox::getYesterdatetimet());
    }

    /**
     * \brief 	Gets the date of yesterday
     *
     * \param 	None
     * \return 	The yesterday date as a string
     */
    std::string getYesterdate() {
        return split(customToolbox::getYesterdatetime(), " ")[0];
    }

    /**
     * \brief 	Gets the date of yesterday
     *
     * \param 	None
     * \return 	The yesterday date as a string
     */
    std::vector<std::string> generateTimeSlots(unsigned int pas, std::string unit) {
        unsigned int multiplicator = 60;
        if (unit == "seconds") multiplicator = 1;
        if (unit == "hours") multiplicator = 3600;
        pas *= multiplicator;
        unsigned int daySec = 3600*24;

        std::vector<std::string> returnVector;
        if (daySec%pas == 0) {
            time_t currentTime = 0;
            for (unsigned int i=0; i<(daySec/pas); i++) {
                returnVector.push_back(customToolbox::str(currentTime, true));
                currentTime += pas;
            }
        }
        return returnVector;
    }

    /**
     * \brief 	Byte flipping routines to convert big-endian to little-endian
     *
     * \param 	b   The byte the convert
     * \return 	The byte converted
     */
    int flip(const byte *b) {
        return b[0]<<24 | b[1]<<16 | b[2]<<8 | b[3];
    }

    /**
     * \brief 	Converts a byte to int
     *
     * \param 	b   The byte the convert
     * \return 	The byte converted
     */
    int toInt(const byte *b) {
        return *(int*)b;
    }

    /**
     * \brief 	Converts a byte to double
     *
     * \param 	b   The byte the convert
     * \return 	The byte converted
     */
    double toDouble(const byte *b) {
        return *(double*)b;
    }

    /**
     * \brief 	Compares if two doubles are equals
     *
     * \param   a   The first double
     * \param 	b   The second double
     * \return 	If they are "equals"
     */
    bool areEquals(double a, double b, double epsilon) {
        return (fabs(a - b) < epsilon);
    }

    /**
     * \brief 	Checks if an element is within an array
     *
     * \param 	table       An pointer over an array of int
     * \param 	sizeTable   The size of the table
     * \param   value       The value to search
     * \return 	true if the value is in the table, false otherwise
     */
    bool isIn(int* table, int sizeTable, int value) {
        int* it = table;
        bool gotcha = false;
        while (it!=table+sizeTable && !gotcha) {
            gotcha = *it++ == value;
        }
        return gotcha;
    }

    /**
     * \brief 	Checks if an element is within a vector
     *
     * \param 	table       An pointer over a vector of string
     * \param   value       The value to search
     * \return 	true if the value is in the vector, false otherwise
     */
    bool isIn(std::vector<std::string> table, std::string value) {
        return (std::find(table.begin(), table.end(), value) != table.end());
    }

    /**
     * \brief 	Checks if an element is within an array
     *
     * \param 	table       An pointer over an array of int
     * \param 	sizeTable   The size of the table
     * \param   value       The value to search
     * \return 	true if the value is in the table, false otherwise
     */
    void insertMap(std::map<std::string, std::string>& destMap, std::map<std::string, std::string>* origMap) {
        std::map<std::string, std::string>::iterator it = origMap->begin();
        for (; it!=origMap->end(); it++) {
            std::string key = it->first;
            std::string value = it->second;
            if (destMap.find(key) == destMap.end()) destMap.insert(std::pair<std::string, std::string>(key, value));
            destMap.at(key) = value;
        }
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    bool isZeros(std::vector<double> tab) {
        for (unsigned int i=0; i<tab.size(); i++) if (!areEquals(tab[i], 0)) return false;
        return true;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    bool isZeros(std::vector<int> tab) {
        for (unsigned int i=0; i<tab.size(); i++) if (tab[i] != 0) return false;
        return true;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    void print(std::vector<double> tab) {
        std::string pre = "";
        for (unsigned int i=0; i<tab.size(); i++) {
            std::cout << pre << str(tab[i], 2);
            pre = ", ";
        }
        std::cout << "" << std::endl;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    void print(std::vector<int> tab) {
        std::string pre = "[";
        for (unsigned int i=0; i<tab.size(); i++) {
            std::cout << pre << tab[i];
            pre = ", ";
        }
        std::cout << "]" << std::endl;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double min(std::vector<double> tab) {
        double temp = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) temp = std::min(temp, tab[i]);
        return temp;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    int min(std::vector<int> tab) {
        int temp = 0;
        for (unsigned int i=0; i<tab.size(); i++) temp = std::min(temp, tab[i]);
        return temp;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double max(std::vector<double> tab) {
        double temp = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) temp = std::max(temp, tab[i]);
        return temp;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    int max(std::vector<int> tab) {
        int temp = 0;
        for (unsigned int i=0; i<tab.size(); i++) temp = std::max(temp, tab[i]);
        return temp;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double sum(std::vector<double> tab) {
        double sum = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) sum += tab[i];
        return sum;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double sum(std::vector<int> tab) {
        double sum = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) sum += tab[i];
        return sum;
    }

    /**
     * \brief 	Computes the mean of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the mean of the vector of doubles
     */
    double mean(std::vector<double> tab) {
        return (customToolbox::sum(tab) / tab.size());
    }

    /**
     * \brief 	Computes the mean of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the mean of the vector of doubles
     */
    double mean(std::vector<int> tab) {
        return (customToolbox::sum(tab) / tab.size());
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double variance(std::vector<double> tab) {
        double temp = 0.0;
        double mean = customToolbox::mean(tab);
        for (unsigned int i=0; i<tab.size(); i++) temp += pow((tab[i]-mean), 2);
        if (tab.size() == 0) return 0;
        return (temp / tab.size());
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double variance(std::vector<int> tab) {
        double temp = 0.0;
        double mean = customToolbox::mean(tab);
        for (unsigned int i=0; i<tab.size(); i++) temp += pow((tab[i]-mean), 2);
        if (tab.size() == 0) return 0;
        return (temp / tab.size());
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double stddev(std::vector<double> tab) {
        return sqrt(customToolbox::variance(tab));
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double stddev(std::vector<int> tab) {
        return sqrt(customToolbox::variance(tab));
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double stdsco(std::vector<double> tab, double val) {
        double mean = customToolbox::mean(tab);
        double variance = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) variance += pow((tab[i]-mean), 2);
        double stddev = sqrt(variance / tab.size());
        return ((val - mean) / stddev);
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double stdsco(std::vector<int> tab, int val) {
        double mean = customToolbox::mean(tab);
        double variance = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) variance += pow((tab[i]-mean), 2);
        double stddev = sqrt(variance / tab.size());
        return ((val - mean) / stddev);
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double stdsco(unsigned int pos, std::vector<double> tab) {
        double mean = customToolbox::mean(tab);
        double variance = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) variance += pow((tab[i]-mean), 2);
        double stddev = sqrt(variance / tab.size());
        return ((tab[pos] - mean) / stddev);
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double stdsco(unsigned int pos, std::vector<int> tab) {
        double mean = customToolbox::mean(tab);
        double variance = 0.0;
        for (unsigned int i=0; i<tab.size(); i++) variance += pow((tab[i]-mean), 2);
        double stddev = sqrt(variance / tab.size());
        return ((tab[pos] - mean) / stddev);
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double covariance(std::vector<double> tab1, std::vector<double> tab2) {
        assert(tab1.size() == tab2.size());
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double temp = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) temp += (tab1[i]-meant1)*(tab2[i]-meant2);
        return (temp / tab1.size());
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double covariance(std::vector<int> tab1, std::vector<int> tab2) {
        assert(tab1.size() == tab2.size());
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double temp = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) temp += (tab1[i]-meant1)*(tab2[i]-meant2);
        return (temp / tab1.size());
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double sampleCovariance(std::vector<double> tab1, std::vector<double> tab2) {
        assert(tab1.size() == tab2.size());
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double temp = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) temp += (tab1[i]-meant1)*(tab2[i]-meant2);
        return (temp / (tab1.size()-1));
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double sampleCovariance(std::vector<int> tab1, std::vector<int> tab2) {
        assert(tab1.size() == tab2.size());
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double temp = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) temp += (tab1[i]-meant1)*(tab2[i]-meant2);
        return (temp / (tab1.size()-1));
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double customCorrelation(std::vector<double> tab1, std::vector<double> tab2) {
        // = cov(t1, t2) / (stddev(t1) * stddev(t2))
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);

        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = tab1[i] - meant1;
            double dif2 = tab2[i] - meant2;
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }

        double a = 0;
        if (denum1 != 0) a = fabs(1-fabs(1-(num / denum1)));

        double c = 0;
        if (sqrt(denum1*denum2) != 0) c = num / sqrt(denum1*denum2);

        return (a*c);
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double customCorrelation(std::vector<int> tab1, std::vector<int> tab2) {
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);
        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = tab1[i] - meant1;
            double dif2 = tab2[i] - meant2;
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }

        double a = 0;
        if (denum1 != 0) a = fabs(1-fabs(1-(num / denum1)));

        double c = 0;
        if (sqrt(denum1*denum2) != 0) c = num / sqrt(denum1*denum2);

        return (a*c);
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double BPcorrelation(std::vector<double> tab1, std::vector<double> tab2) {
        // = cov(t1, t2) / (stddev(t1) * stddev(t2))
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);

        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = tab1[i] - meant1;
            double dif2 = tab2[i] - meant2;
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }

        if (sqrt(denum1*denum2) == 0) return 0.0;
        return (num / sqrt(denum1*denum2));
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double BPcorrelation(std::vector<int> tab1, std::vector<int> tab2) {
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);
        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = tab1[i] - meant1;
            double dif2 = tab2[i] - meant2;
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }
        if (sqrt(denum1*denum2) == 0) return 0.0;
        return (num / sqrt(denum1*denum2));
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double decreasingBPCorrelation(std::vector<double> tab1, std::vector<double> tab2) {
        // = cov(t1, t2) / (stddev(t1) * stddev(t2))
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);

        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = (tab1[i] - meant1)/(log(i+1)+1); //ln //(log(i+1)+1)
            double dif2 = (tab2[i] - meant2)/(log(i+1)+1); //ln
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }

        if (sqrt(denum1*denum2) == 0) return 0.0;
        return (num / sqrt(denum1*denum2));
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double decreasingBPCorrelation(std::vector<int> tab1, std::vector<int> tab2) {
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);
        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = (tab1[i] - meant1)/(log(i+1)+1);
            double dif2 = (tab2[i] - meant2)/(log(i+1)+1);
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }
        if (sqrt(denum1*denum2) == 0) return 0.0;
        return (num / sqrt(denum1*denum2));
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double customDecreasingCorrelation(std::vector<double> tab1, std::vector<double> tab2) {
        // = cov(t1, t2) / (stddev(t1) * stddev(t2))
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);

        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = (tab1[i] - meant1)/(log(i+1)+1); //ln //(log(i+1)+1)
            double dif2 = (tab2[i] - meant2)/(log(i+1)+1); //ln
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }

        double a = 0;
        if (denum1 != 0) a = fabs(1-fabs(1-(num / denum1)));

        double c = 0;
        if (sqrt(denum1*denum2) != 0) c = num / sqrt(denum1*denum2);

        return (a*c);
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double customDecreasingCorrelation(std::vector<int> tab1, std::vector<int> tab2) {
        assert(tab1.size() == tab2.size());
        assert(tab1.size() > 0);
        //*/
        double meant1 = customToolbox::mean(tab1);
        double meant2 = customToolbox::mean(tab2);
        double num = 0.0;
        double denum1 = 0.0;
        double denum2 = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) {
            double dif1 = (tab1[i] - meant1)/(log(i+1)+1);
            double dif2 = (tab2[i] - meant2)/(log(i+1)+1);
            num += (dif1 * dif2);
            denum1 += pow(dif1, 2);
            denum2 += pow(dif2, 2);
        }

        double a = 0;
        if (denum1 != 0) a = fabs(1-fabs(1-(num / denum1)));

        double c = 0;
        if (sqrt(denum1*denum2) != 0) c = num / sqrt(denum1*denum2);

        return (a*c);
        /*/
        double stddevs = stddev(tab1) * stddev(tab2);
        if (stddevs == 0) return 0;
        return (covariance(tab1, tab2) / stddevs);
        //*/
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double diffs(std::vector<double> tab1, std::vector<double> tab2) {
        assert(tab1.size() == tab2.size());
        double temp = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) temp += fabs(tab1[i] - tab2[i]);
        return temp;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    double diffs(std::vector<int> tab1, std::vector<int> tab2) {
        assert(tab1.size() == tab2.size());
        double temp = 0.0;
        for (unsigned int i=0; i<tab1.size(); i++) temp += abs(tab1[i] - tab2[i]);
        return temp;
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    std::pair<double, double> coeffs(std::vector<double> tab1, std::vector<double> tab2) {
        double a = covariance(tab1, tab2) / variance(tab1);
        return std::pair<double, double>(a, (mean(tab2) - a*mean(tab1)));
    }

    /**
     * \brief 	Computes the sum of a vector of doubles
     *
     * \param 	tab     A vector of doubles
     * \return 	the sum of the vector of doubles
     */
    std::pair<double, double> coeffs(std::vector<int> tab1, std::vector<int> tab2) {
        double a = covariance(tab1, tab2) / variance(tab1);
        return std::pair<double, double>(a, (mean(tab2) - a*mean(tab1)));
    }

    /**
     * \brief Starts printing a message according to the level
     *
     * \param func the message to print
     * \return Nonce
     */
    void start(const char* func __attribute__((unused))) {
        #if 0
            std::string s = "";
            for (int i=0; i<level; ++i)
                s.append("| ");
            std::cout << s << "-> " << func << std::endl;
            ++level;
        #endif
    }

    /**
     * \brief Ends the printing of the initiated message according to the level
     *
     * \param func the message to print
     * \return Nonce
     */
    void end(const char* func __attribute__((unused))) {
        #if 0
            --level;
            std::string s = "";
            for (int i=0; i<level; ++i)
                s.append("| ");
            std::cout << s << "<- " << func << std::endl;
        #endif
    }

    /**
     * \brief Prints the messages
     *
     * \param msg the messages to print
     * \return Nonce
     */
    void message(const char* msg, ...) {
        std::string s = "";
        char buf[2048];
        for (int i=0; i<level; ++i)
            s.append("| ");
        s.append(" > ");
        va_list args;
        va_start(args, msg);
        sprintf(buf, "%s%s", s.c_str(), msg);
        printf(buf, args);
        va_end(args);
    }
}

