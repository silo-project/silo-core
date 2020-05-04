//
// Created by penta on 2020-05-02.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "node.h"
#include "library.h"

class Executor {
public:
    virtual void execute(AbstractNode*);
};

class TccExecutor : public Executor {
public:
    TccExecutor(TccLibrary* _library, const char* _executorname);
    ~TccExecutor();
    void execute(AbstractNode* abstractNode);

protected:
    const char* executorname;
    TccLibrary* library;
};

#endif // EXECUTOR_H
