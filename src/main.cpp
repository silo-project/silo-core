//<TODO> 시뮬레이션 클래스 만들기, 에러/경고 코드 정의, 에러/경고 구현

#include <iostream>
#include "fileloader.h"

int main(int argc, char** argv) {
    FileLoader::logisim("../src/FileLoader/LogisimExample.circ");
    return 0;
}