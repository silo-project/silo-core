//
// Created by penta on 2020-05-06.
//

#include "tcclibrary.h"

#include "executor.h"

#include <iostream>
#include <filesystem>
#include <string>

#include "Crc32.h"

#include "../miniz-2.1.0/miniz.h"

extern "C" {

static int TCC_registerAbstractCircuitExecutor(void* _workinglib, const char* compname, void(*executorPointer)(void* abstractNode)) {
    //puts("registerAbstractCircuitExecutor()");
    AbstractCircuit *ac = new AbstractCircuit();

    TccLibrary* workinglib = reinterpret_cast<TccLibrary*>(_workinglib);

    ac->executor = new TccExecutor(workinglib, reinterpret_cast<void (*)(AbstractNode *)>(executorPointer));
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

    tccfile = _tccfile;
    std::cout << "INIT TCC LIBRARY " << tccfile << std::endl;

    mz_zip_archive* zip = static_cast<mz_zip_archive*>(calloc(1, sizeof(mz_zip_archive)));
    //memset(zip, 0, sizeof(mz_zip_archive));

    mz_zip_reader_init_file(zip, tccfile, 0);

    //std::filesystem::
    const char* _templibdir = (std::filesystem::temp_directory_path().u8string() + "/tcc-" + n2hexstr(crc32_1byte_tableless(tccfile, strlen(tccfile)), 8)).c_str();

    templibdir = static_cast<char *>(calloc(strlen(_templibdir) + 1, sizeof(char)));

    strcpy(templibdir, _templibdir);

    std::filesystem::remove_all(templibdir);
    std::filesystem::create_directory(templibdir);

    int zipfilecount = mz_zip_reader_get_num_files(zip);

    mz_zip_archive_file_stat* stat = static_cast<mz_zip_archive_file_stat*>(malloc(sizeof(mz_zip_archive_file_stat)));

    for(int i = 0; i < zipfilecount ; i++) {
        memset(stat, 0, sizeof(mz_zip_archive_file_stat));
        mz_zip_reader_file_stat(zip, i, stat);
        if(!stat->m_is_directory) {
            char* fn = static_cast<char *>(calloc(256, sizeof(char)));
            strcpy_s(fn, 256, templibdir);
            strcat_s(fn, 256, "/");
            strcat_s(fn, 256, stat->m_filename);
            std::cout << "Unzipping " << fn << std::endl;
            mz_zip_reader_extract_to_file(zip, i, fn, 0);
        }
    }

    // TODO TMP

    s = tcc_new();
    if(!s) std::cout << "Can’t create a TCC context" << std::endl;
    else std::cout << "TCC context Created" << std::endl;
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

    if (tcc_add_file(s, tccfile) > 0) {
        std::cout << "Compilation error !" << std::endl;
    }

    std::cout << "FILEREADY TCC LIBRARY " << tccfile << std::endl;

    tcc_add_symbol(s, "TCC_registerAbstractCircuitExecutor", reinterpret_cast<void*>(TCC_registerAbstractCircuitExecutor));

    tcc_relocate(s, TCC_RELOCATE_AUTO);

    void* onload = tcc_get_symbol(s, "onLoad");

    if(!onload) {
        std::cout << "NO onLoad()" << std::endl;
    }

    (reinterpret_cast<int(*)(void*)>(onload))(reinterpret_cast<void*>(this));
    std::cout << "LOADED TCC LIBRARY " << tccfile << std::endl;
}

TccLibrary::~TccLibrary() {
    tcc_delete(s);
    std::filesystem::remove_all(templibdir);
}
