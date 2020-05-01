//
// Created by penta on 2020-05-01.
//

#include <map>
#include <string>

#include "fileloader.h"
#include "tinyxml2.h"
#include "circuit.h"

#include <iostream>

using libraryid_t = int;

using namespace tinyxml2;
using std::map;
using std::string;

Circuit* FileLoader::logisim(const char* file) {
    XMLDocument circ;

    if (circ.LoadFile(file) != XML_SUCCESS) return nullptr;

    std::cout << "Opened" << std::endl;

    map<libraryid_t, string> libraryfilemap;

    XMLNode* project = circ.FirstChild()->NextSibling();

    for (XMLElement* libelement = project->FirstChildElement("lib"); libelement != nullptr; libelement = libelement->NextSiblingElement("lib")) {
        const char *librarypath;
        libelement->QueryStringAttribute("desc", &librarypath);
        libraryfilemap[libelement->IntAttribute("name")] = string(librarypath);
    }

    Circuit *tc = new Circuit();
    return tc;
}

Circuit* FileLoader::logisim(XMLNode* node) {
    Circuit* tc = new Circuit();
    return tc;
}