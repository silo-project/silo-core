//
// Created by penta on 2020-05-02.
//


#include "executor.h"

TccExecutor::TccExecutor(TccLibrary* _library, const char* _executorname) {
    library = _library;
    executorname = _executorname;
}

void TccExecutor::execute(AbstractNode* abstractNode) {

}

void Executor::execute(AbstractNode *) { }
