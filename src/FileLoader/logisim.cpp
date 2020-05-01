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

Circuit* FileLoader::logisim(XMLNode* project, const char* name) {
    map<libraryid_t, string> libraryfilemap;

    Circuit* tc = new Circuit();

    for (XMLElement* libelement = project->FirstChildElement("lib"); libelement != nullptr; libelement = libelement->NextSiblingElement("lib")) {
        const char* librarypath;
        libelement->QueryStringAttribute("desc", &librarypath);
        libraryfilemap[libelement->IntAttribute("name")] = string(librarypath);
    }

    for (XMLElement* circelement = project->FirstChildElement("circuit"); circelement != nullptr; circelement = circelement->NextSiblingElement("circuit")) {
        const char* circname;
        circelement->QueryStringAttribute("name", &circname);
        if(strcmp(circname, name) != 0) continue;
        for (XMLElement* aelement = circelement->FirstChildElement("a"); aelement != nullptr; aelement = aelement->NextSiblingElement("a")) {
            const char* attrname;
            const char* attrvalue;
            aelement->QueryStringAttribute("name", &attrname);
            aelement->QueryStringAttribute("val", &attrvalue);
            tc->setAttribute(string(attrname), string(attrvalue));
        }
        for (XMLElement* wireelement = circelement->FirstChildElement("wire"); wireelement != nullptr; wireelement = wireelement->NextSiblingElement("wire")) {
            const char* from;
            const char* to;
            wireelement->QueryStringAttribute("from", &from);
            wireelement->QueryStringAttribute("to", &to);
            size_t fromstrlen = (strlen(from) - 2) * sizeof(char);
            size_t tostrlen = (strlen(to) - 2) * sizeof(char);
            char* fromtrim = static_cast<char *>(malloc(fromstrlen + sizeof(char)));
            char* totrim = static_cast<char *>(malloc(tostrlen + sizeof(char)));
            memcpy_s(fromtrim, fromstrlen + sizeof(char), (void*)((int8_t*)from + 1), fromstrlen);
            memcpy_s(totrim, tostrlen + sizeof(char), (void*)((int8_t*)to + 1), tostrlen);
            int32_t ax = atoi(strtok(fromtrim, ","));
            int32_t ay = atoi(strtok(NULL, ","));
            int32_t bx = atoi(strtok(totrim, ","));
            int32_t by = atoi(strtok(NULL, ","));
            tc->placeWire(ax, ay, bx, by);
        }
        for (XMLElement* compelement = circelement->FirstChildElement("comp"); compelement != nullptr; compelement = compelement->NextSiblingElement("comp")) {
            Circuit* lc;
            const char* loc;
            compelement->QueryStringAttribute("loc", &loc);
            size_t locstrlen = (strlen(loc) - 2) * sizeof(char);
            char* loctrim = static_cast<char *>(malloc(locstrlen + sizeof(char)));
            memcpy_s(loctrim, locstrlen + sizeof(char), (void*)((int8_t*)loc + 1), locstrlen);
            int32_t x = atoi(strtok(loctrim, ","));
            int32_t y = atoi(strtok(NULL, ","));
            int lib = compelement->IntAttribute("lib" , -1);
            const char* compname;
            compelement->QueryStringAttribute("name", &compname);
            if(lib == -1) lc = logisim(project, compname);
            else lc = new Circuit(); // TODO Load Circuit
            lc->position.x = x; lc->position.y = y;
            tc->placeCircuit(lc);
        }
    }

    return tc;
}

Circuit* FileLoader::logisim(const char* file, const char* name) {
    XMLDocument circ;

    if (circ.LoadFile(file) != XML_SUCCESS) return nullptr;

    std::cout << "Opened" << std::endl;

    map<libraryid_t, string> libraryfilemap;

    XMLNode* project = circ.FirstChild()->NextSibling();

    return logisim(project, name);
}

Circuit* FileLoader::logisim(const char* file) {
    XMLDocument circ;

    if (circ.LoadFile(file) != XML_SUCCESS) return nullptr;

    map<libraryid_t, string> libraryfilemap;

    XMLNode* project = circ.FirstChild()->NextSibling();

    const char* maincirc;
    project->FirstChildElement("main")->QueryStringAttribute("name", &maincirc);

    return logisim(project, maincirc);
}