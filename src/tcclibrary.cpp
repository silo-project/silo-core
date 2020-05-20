//
// Created by penta on 2020-05-06.
//

#include "tcclibrary.h"

#include <iostream>
#include <filesystem>
#include <string>

#include "Crc32.h"

#include "miniz.h"

std::vector<std::string>* TccLibraryFileType = nullptr;

extern "C" {

static int TCC_registerAbstractCircuitExecutor(void* _workinglib, const char* compname, void* executorPointer) {
    //puts("registerAbstractCircuitExecutor()");
    AbstractCircuit *ac = new AbstractCircuit();

    TccLibrary* workinglib = reinterpret_cast<TccLibrary*>(_workinglib);

    ac->executor = executorPointer;
    workinglib->registerAbstractCircuit(ac, compname);
    //lua_settop(L, 0);
    return 0;
}
}

using std::string;
namespace {
    template<typename I>
    std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1) {
        static const char *digits = "0123456789ABCDEF";
        std::string rc(hex_len, '0');
        for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
            rc[i] = digits[(w >> j) & 0x0f];
        return rc;
    }
}

//TCCState* TccLibrary::s;

TccLibrary::TccLibrary(const char *_tccfile) {

    if(!TccLibraryFileType) {
        TccLibraryFileType = new std::vector<std::string>();
        TccLibraryFileType->push_back("code");
        TccLibraryFileType->push_back("data");
    }

    if(!filemap) filemap = new std::map<int, std::map<int, std::string*>*>();

    for(int i = 0; i < TccLibraryFileType->size(); i++)
        filemap->insert(std::pair<int, std::map<int, std::string*>*>(i, new std::map<int, std::string*>()));

    tccfile = _tccfile;
    std::cout << "INIT TCC LIBRARY " << tccfile << std::endl;

    mz_zip_archive* zip = static_cast<mz_zip_archive*>(calloc(1, sizeof(mz_zip_archive)));
    //memset(zip, 0, sizeof(mz_zip_archive));

    mz_zip_reader_init_file(zip, tccfile, 0);

    //std::filesystem::
    templibdir = std::filesystem::temp_directory_path().u8string() + "/tcc-" + n2hexstr(crc32_1byte_tableless(tccfile, strlen(tccfile)), 8);

    std::cout << "WorkingDir " << templibdir << std::endl;

    std::filesystem::remove_all(templibdir);
    std::filesystem::create_directory(templibdir);

    int zipfilecount = mz_zip_reader_get_num_files(zip);

    mz_zip_archive_file_stat* stat = static_cast<mz_zip_archive_file_stat*>(malloc(sizeof(mz_zip_archive_file_stat)));

    for(int i = 0; i < zipfilecount ; i++) {
        memset(stat, 0, sizeof(mz_zip_archive_file_stat));
        mz_zip_reader_file_stat(zip, i, stat);
        if(!stat->m_is_directory) {
            string fn(templibdir + "/" + stat->m_filename);
            std::cout << "Unzipping " << fn << std::endl;
            mz_zip_reader_extract_to_file(zip, i, fn.c_str(), 0);
        }
    }

    libinfo = new tinyxml2::XMLDocument;
    int xmlflag = libinfo->LoadFile((templibdir + "/libinfo.xml").c_str());
    if(xmlflag != tinyxml2::XML_SUCCESS)
        std::cout << "Unable to load TCCLIBRARY: Unable to open XML. Code " << xmlflag << std::endl;

    tinyxml2::XMLElement* libinfoelement = libinfo->FirstChildElement("library");

    if(libinfoelement->IntAttribute("version") != 1) {
        std::cout << "Unknown Library Version" << std::endl;
    }

    for(auto fileelement = libinfoelement->FirstChildElement("file"); fileelement != nullptr; fileelement = fileelement->NextSiblingElement("file")) {
        const char* filetype = nullptr;
        fileelement->QueryStringAttribute("type", &filetype);
        if(!filetype)
            std::cout << "NO FILE TYPE FIELD" << std::endl;

        auto it = std::find(TccLibraryFileType->begin(), TccLibraryFileType->end(), string(filetype));
        if(it == TccLibraryFileType->end()) {
            std::cout << "UNREGISTERED FILE TYPE FIELD" << std::endl;
        } else {
            int id = fileelement->IntAttribute("id", -1);
            if(id == -1)
                std::cout << "NO ID FIELD" << std::endl;
            else {
                const char* n = nullptr;
                fileelement->QueryStringAttribute("name", &n);
                if(!n)
                    std::cout << "NO NAME FIELD" << std::endl;
                else
                    filemap->at(std::distance(TccLibraryFileType->begin(), it))->insert(std::pair<int, std::string*>(id, new string(n)));
            }
        }
    }

    s = tcc_new();
    if(!s) std::cout << "Can’t create a TCC context" << std::endl;
    else std::cout << "TCC context Created" << std::endl;
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

    for(auto i : *(filemap->at(std::distance(TccLibraryFileType->begin(), std::find(TccLibraryFileType->begin(), TccLibraryFileType->end(), "code"))))) {
        if(tcc_add_file(s, (templibdir + "/" + *(i.second)).c_str()) > 0)
            std::cout << "Compilation error at ID " << i.first << std::endl;
    }

    std::cout << "FILEREADY TCC LIBRARY " << tccfile << std::endl;

    tcc_add_symbol(s, "TCC_registerAbstractCircuitExecutor", reinterpret_cast<void*>(TCC_registerAbstractCircuitExecutor));

    tcc_relocate(s, TCC_RELOCATE_AUTO);

    for(auto funcelement = libinfoelement->FirstChildElement("event")->FirstChildElement("func"); funcelement != nullptr; funcelement = funcelement->NextSiblingElement("func")) {
        const char* call = "";
        funcelement->QueryStringAttribute("call", &call);
        const char* name = nullptr;
        funcelement->QueryStringAttribute("name", &name);
        if(!name) continue;
        if(strcmp(call, "onLoad") == 0) {
            onLoad = tcc_get_symbol(s, name);
        } else if(strcmp(call, "onUnload") == 0) {
            onUnload = tcc_get_symbol(s, name);
        }
    }

    if(onLoad) {
        (reinterpret_cast<int(*)(void*)>(onLoad))(reinterpret_cast<void*>(this));
    }

    std::cout << "LOADED TCC LIBRARY " << tccfile << std::endl;
}

TccLibrary::~TccLibrary() {
    if(onUnload) {
        (reinterpret_cast<int(*)(void*)>(onUnload))(reinterpret_cast<void*>(this));
    }
    tcc_delete(s);
    std::filesystem::remove_all(templibdir);
}
