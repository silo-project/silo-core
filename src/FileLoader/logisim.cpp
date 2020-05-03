//
// Created by penta on 2020-05-01.
//

#include <map>
#include <string>

#include "fileloader.h"
#include "tinyxml2.h"
#include "circuit.h"
#include "library.h"

#include <iostream>
#include <filesystem>

//#define std::filesystem std::filesystem::__cxx11

using libraryid_t = int;

using namespace tinyxml2;
using std::map;
using std::string;

AbstractCircuit* FileLoader::logisimAbstract(XMLNode* project, const char* localfiletag, const char* name) {

    std::cout << "ABSTRACT " << name << std::endl; // TODO DEBUG

    map<libraryid_t, string> libraryFileMap;

    AbstractCircuit* tc = new AbstractCircuit();


    size_t localpathlen = strlen(localfiletag);
    const char* localrelpath = nullptr;

    if(localpathlen > 4) {
        if(localfiletag[3] == '#') { // Lua
            localrelpath = localfiletag + 4;
        }
    }
    if(localpathlen > 5) {
        if(localfiletag[4] == '#') { // File
            localrelpath = localfiletag + 5;
        }
    }

    std::filesystem::path localpath;
    if(localrelpath != nullptr) localpath = std::filesystem::absolute(std::filesystem::path(string(localrelpath)));

    for (XMLElement* libelement = project->FirstChildElement("lib"); libelement != nullptr; libelement = libelement->NextSiblingElement("lib")) {
        const char* librarypath;
        libelement->QueryStringAttribute("desc", &librarypath);

        size_t librarypathlen = strlen(librarypath);
        const char* relpath = nullptr;

        if(librarypathlen > 4) {
            if(librarypath[3] == '#') { // Lua
                relpath = librarypath + 4;
            }
        }
        if(librarypathlen > 5) {
            if(librarypath[4] == '#') { // File
                relpath = librarypath + 5;
            }
        }
        if(relpath) {
            std::filesystem::path abspath = std::filesystem::absolute(
                    std::filesystem::relative(std::filesystem::path(string(relpath)), localpath));
            string abspathstr(abspath.u8string());
            std::cout << "logisim.cpp:71 " << localrelpath << " " << localpath << " " << abspathstr << std::endl;
            libraryFileMap[libelement->IntAttribute("name")] = abspathstr;
        } else {
            std::cout << "logisim.cpp:74 " << librarypath << " ";
            libraryFileMap[libelement->IntAttribute("name")] = librarypath;
        }
    }

    for (XMLElement* circelement = project->FirstChildElement("circuit"); circelement != nullptr; circelement = circelement->NextSiblingElement("circuit")) {
        const char* circname;
        circelement->QueryStringAttribute("name", &circname);
        std::cout << circname << std::endl; // TODO DEBUG
        if(strcmp(circname, name) != 0) continue;
        /*
        for (XMLElement* aelement = circelement->FirstChildElement("a"); aelement != nullptr; aelement = aelement->NextSiblingElement("a")) {
            const char* attrname;
            const char* attrvalue;
            aelement->QueryStringAttribute("name", &attrname);
            aelement->QueryStringAttribute("val", &attrvalue);
            tc->setAttribute(string(attrname), string(attrvalue));
        }*/
        for (XMLElement* wireelement = circelement->FirstChildElement("wire"); wireelement != nullptr; wireelement = wireelement->NextSiblingElement("wire")) {
            const char* from;
            const char* to;

            wireelement->QueryStringAttribute("from", &from);
            wireelement->QueryStringAttribute("to", &to);

            size_t fromstrlen = (strlen(from) - 2) * sizeof(char);
            size_t tostrlen = (strlen(to) - 2) * sizeof(char);

            char* fromtrim = static_cast<char *>(malloc(fromstrlen + sizeof(char)));
            char* totrim = static_cast<char *>(malloc(tostrlen + sizeof(char)));

            memcpy(fromtrim, (void*)((int8_t*)from + 1), fromstrlen);
            memcpy(totrim, (void*)((int8_t*)to + 1), tostrlen);

            int32_t ax = atoi(strtok(fromtrim, ","));
            int32_t ay = atoi(strtok(NULL, ","));
            int32_t bx = atoi(strtok(totrim, ","));
            int32_t by = atoi(strtok(NULL, ","));

            tc->placeWire(ax, ay, bx, by, 0);

            std::cout << ax << " " <<  ay << " " << bx << " " << by << std::endl; // TODO DEBUG

        }

        for (XMLElement* compelement = circelement->FirstChildElement("comp"); compelement != nullptr; compelement = compelement->NextSiblingElement("comp")) {
            AbstractCircuit *lc;
            const char *loc;

            compelement->QueryStringAttribute("loc", &loc);

            size_t locstrlen = (strlen(loc) - 2) * sizeof(char);
            char *loctrim = static_cast<char *>(malloc(locstrlen + sizeof(char)));

            memcpy(loctrim, (void *) ((int8_t *) loc + 1), locstrlen);

            int32_t x = atoi(strtok(loctrim, ","));
            int32_t y = atoi(strtok(NULL, ","));
            int libid = compelement->IntAttribute("lib", -1);
            const char *compname;

            compelement->QueryStringAttribute("name", &compname);

            std::cout << "logisim.cpp:92 " << compname << " " << libid << std::endl;

            LibraryManager libman;
            const char *libfile;
            if(libid != -1) libfile = libraryFileMap.find(libid)->second.c_str();
            else libfile = localfiletag;
            std::cout << libfile << std::endl;

            lc = loadAbstract(libfile, compname);

            tc->placeAbstractCircuit(lc, new Position{x, y});
        }
    }

    return tc;
}

Circuit* FileLoader::logisim(XMLNode* project, const char* localfiletag, const char* name) {
    map<libraryid_t, string> libraryfilemap;

    std::cout << "REAL " << name << std::endl; // TODO DEBUG

    AbstractCircuit* as = logisimAbstract(project, localfiletag, name);

    std::cout << as->abstractCircuitVector.size() << std::endl;

    Circuit* tc = new Circuit(as);

    for (XMLElement* circelement = project->FirstChildElement("circuit"); circelement != nullptr; circelement = circelement->NextSiblingElement("circuit")) {
        const char* circname;
        circelement->QueryStringAttribute("name", &circname);

        std::cout << name << " " << circname << std::endl; // TODO DEBUG

        if(strcmp(circname, name) != 0) continue;

        for (XMLElement* aelement = circelement->FirstChildElement("a"); aelement != nullptr; aelement = aelement->NextSiblingElement("a")) {
            const char* attrname;
            const char* attrvalue;

            aelement->QueryStringAttribute("name", &attrname);
            aelement->QueryStringAttribute("val", &attrvalue);

            tc->setAttribute(string(attrname), string(attrvalue));
        }
    }

    return tc;
}
