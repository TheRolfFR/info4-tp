/**
 * \file	Parser.cpp
 * \class	Parser
 * \author	Etienne Thuillier (etienne.thuillier@utbm.fr)
 * \date	10/04/2016
 * \brief	Methods of Parser object
 *
 * Methods of Parser object
 */

#include "geologic-core/superClasses/Parser.h"


/**
 * \brief 	Default constructor of class Parser
 *
 * \param 	None
 * \return 	None
 */
Parser::Parser() {
    this->shapefileReader = ShapefileReader::getInstance();
}

/**
 * \brief 	Default destructor of class Parser
 *
 * \param 	None
 * \return 	None
 */
Parser::~Parser() {}
