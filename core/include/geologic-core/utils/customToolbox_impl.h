/**
 * \file	customToolbox_impl.h
 */

#ifndef CUSTOMTOOLBOX_IMPL_H_INCLUDED
#define CUSTOMTOOLBOX_IMPL_H_INCLUDED

#include <iomanip>


namespace customToolbox {

    /**
     * \brief 	Prints an element like a mysql table
     *
     * \param 	t       The element to print
     * \param 	width   The size of a cell
     * \return 	None
     */
    template<typename T> void printElement(T t, const int& width, bool alignLeft) {
        const char separator = ' ';
        if (alignLeft) {
            std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
        } else {
            std::cout << std::right << std::setw(width) << std::setfill(separator) << t;
        }

    }

    /**
     * \brief 	Returns a string corresponding to the value
     *
     * \param 	val The value to transform
     * \return 	The string corresponding to that value
     */
    template<typename T> std::string str(T val) {
        std::stringstream out;
        out << std::setprecision(12) << val;
        return out.str();
    }

    /**
     * \brief 	Returns the length (number of characters) of that value
     *
     * \param 	val The value to analyze
     * \return 	The number of characters corresponding to that value
     */
    template<typename T> int len(T val) {
        if (std::is_same<T, std::string>::value) return val.size();
        return str(val).size();
    }

    /**
     * \brief 	Checks if an element is within a vector
     *
     * \param 	table       An pointer over a vector of string
     * \param   value       The value to search
     * \return 	true if the value is in the vector, false otherwise
     */
    template<typename T> bool isIn(std::vector<T> table, T t) {
        return (std::find(table.begin(), table.end(), t) != table.end());
    }

    /**
     * \brief 	Checks if an element is within a vector
     *
     * \param 	table       An pointer over a vector of string
     * \param   value       The value to search
     * \return 	true if the value is in the vector, false otherwise
     */
    template<typename T> std::unordered_map<std::string, T> generateTimeSlotsMap(unsigned int pas, std::string unit) {
        unsigned int multiplicator = 60;
        if (unit == "seconds") multiplicator = 1;
        if (unit == "hours") multiplicator = 3600;
        pas *= multiplicator;
        unsigned int daySec = 3600*24;

        std::unordered_map<std::string, T> returnMap;
        if (daySec%pas == 0) {
            time_t currentTime = 0;
            for (unsigned int i=0; i<(daySec/pas); i++) {
                returnMap.insert(std::pair<std::string, T>(customToolbox::str(currentTime), sizeof(T)));
                currentTime += pas;
            }
        }
        return returnMap;
    }
}

#endif // CUSTOMTOOLBOX_IMPL_H_INCLUDED
