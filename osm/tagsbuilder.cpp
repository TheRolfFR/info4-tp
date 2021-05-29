#include "tagsbuilder.h"
#include <cstdio>
#include <clocale>

using namespace std;

TagsBuilder::TagsBuilder(const string &url, string element) {
    this->tags = map<int, map<string, string> >();
    this->currentIndex = 0;
    this->element = element;
    this->server=url;
//    this->server="http://overpass-api.de/api/interpreter?data=";
}

TagsBuilder::TagsBuilder(const string &url) {
    TagsBuilder(url, "way");
    this->server=url;
//     this->server="http://overpass-api.de/api/interpreter?data=";
}

void TagsBuilder::setserver(string server) {
    this->server=server;
}

void TagsBuilder::setoutputformat(string format)
{
    // transforms format to lowercase

    //std::transform(format.begin(), format.end(), format.begin(), ::tolower);

    /*if(format == "xml" || format == "json") {
        this->outputformat = format;
    } else {
        cerr << format << " is not a valid format! (xml or json only)" << endl;
    }*/
}

void TagsBuilder::setBoudingBox(float* bbox) {
    double bboxf[] = {bbox[0], bbox[1], bbox[2], bbox[3]};
    //std::cout << "TagsBuilder::setBoundingBox(" << bbox[0] << "," << bbox[1] << "," << bbox[2] << "," << bbox[3] << ")" << std::endl;
    this->boundingbox = bboxf;
}
void TagsBuilder::setBoudingBox(double* bbox) {
    //std::cout << "TagsBuilder::setBoundingBox(" << bbox[0] << "," << bbox[1] << "," << bbox[2] << "," << bbox[3] << ")" << std::endl;

    this->boundingbox = bbox;
}

void TagsBuilder::tag(string key, string op, string value) {
    map<string, string> tag;
    tag["key"] = key;
    tag["operator"] = op;
    tag["value"] = value;
    this->tags[this->currentIndex] = tag;
    this->currentIndex++;
}

void TagsBuilder::setRecursion(bool recurs) {
    this->recursion = recurs;
}

string TagsBuilder::toString() {
    // final string begins with the requested element

    string final=this->server + "way";
    //final+= "[out:"+this->outputformat+"];";
    final += this->element;

    // loop through the tags
    map<int, map<string, string> >::iterator i;
    for(i=this->tags.begin();i!=this->tags.end();++i) {

        map<string, string> tag = i->second;
        if(tag["operator"] != "") // if tag has operator, append [key operator value]
            final+= "[" + tag["key"] + tag["operator"] + "\"" + tag["value"] + "\"]";
        else // if tag has no operator (for example in "is" method), then just append [key]
            final += "["+tag["key"]+"]";
    }
    char f[10000];
    // append the bounding box
    setlocale(LC_ALL, "C");
    sprintf(f,"%.15lf,%.15lf,%.15lf,%.15lf",this->boundingbox[0] ,this->boundingbox[1] ,this->boundingbox[2],this->boundingbox[3]);
    setlocale(LC_ALL, "");
    final += "(";
    final+= f;
    final+=");";

    // append recursion if any
    if(this->recursion) {
        final += "(._;>;);";
    }
    final += "out;";

    return final;
}
