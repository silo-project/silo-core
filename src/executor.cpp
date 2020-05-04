//
// Created by penta on 2020-05-02.
//


#include "executor.h"

TccExecutor::TccExecutor(TccLibrary* _library, void(*_executefunction)(AbstractNode*)) {
    library = _library;
    executefunction = _executefunction;
}

void TccExecutor::execute(AbstractNode* abstractNode) {

}

void Executor::execute(AbstractNode *) { }
