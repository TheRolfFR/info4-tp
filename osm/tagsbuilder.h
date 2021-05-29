#ifndef TAGSBUILDER_H
#define TAGSBUILDER_H

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

/*!
 * \brief The TagsBuilder is used to create the OSM query
 */

class TagsBuilder
{
public:

    /*!
    * \brief TagsBuilder is the constructor
    */

   TagsBuilder(const string &url);
   TagsBuilder(const string &url, string element);

   /*!
    * \brief tag to build a tag with key, operator and value
    * \param key
    * \param op
    * \param value
    */

   void tag(string key, string op, string value);

   void is(string key) { this->tag(key,"","");}
   void equal(string key, string value) {this->tag(key, "=", value);}
   void notequal(string key, string value) {this->tag(key, "!=", value);}
   void regex(string key, string value)  {this->tag(key, "~", value);}
   void notregex(string key, string value) {this->tag(key, "!~", value);}

   /*!
    * \brief setRecursion to set recursion or not
    * \param recurs
    */

   void setRecursion(bool recurs);

   /*!
    * \brief toString converts the query to string
    * \return
    */

   string toString();

   /*!
    * \brief setoutputformat to choose an output format
    * \param format
    */

   void setoutputformat(string format);

   /*!
    * \brief setserver to choose a server
    * \param server
    */

   void setserver(string server);

   void setBoudingBox(float* bbox);
   void setBoudingBox(double* bbox);
   double* getBoundingBox() { return this->boundingbox;}

private:

   string outputformat;
   string server;
   bool recursion = true;
   double* boundingbox;
   string element;
   int currentIndex;
   map<int, ///<tag number
       map<string, string> >  ///<this map contains 3 keys: "key", "operator", "value"
           tags;
};

#endif // TAGSBUILDER_H

