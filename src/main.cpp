//<TODO> 시뮬레이션 클래스 만들기, 에러/경고 코드 정의, 에러/경고 구현

#include <iostream>
#include "fileloader.h"

#include "tinyxml2.h"

int main(int argc, char** argv) {
    const char* lib = "file#../src/FileLoader/LogisimExample.circ";

    tinyxml2::XMLDocument doc;
    if(doc.LoadFile(static_cast<const char*>(lib + 5)) != tinyxml2::XML_SUCCESS) {
        std::cout << "main.cpp:13 Unable to load XML " << lib + 5 << std::endl;
    }

    Circuit* c = FileLoader::logisim(doc.FirstChild()->NextSibling(), lib, "main");
    std::cout << c->getAttribute("circuit") << "," << c->getAttribute("clabel") << "," << c->getAttribute("clabelup") << "," << c->getAttribute("clabelfont") << std::endl;
    return 0;
}