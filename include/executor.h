//
// Created by penta on 2020-05-02.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "node.h"
#include "library.h"

#include "tcclibrary.h"

class Executor {
public:
    virtual void execute(AbstractNode*);
};

class TccExecutor : public Executor {
public:
    TccExecutor(TccLibrary* _library, void(*_executefunction)(AbstractNode*));
    ~TccExecutor();
    void execute(AbstractNode* abstractNode);

protected:
    void(*executefunction)(AbstractNode*);
    TccLibrary* library;
};

#endif // EXECUTOR_H
