#include <tcclib.h>

void and_gate(void* ac) {

}

void not_gate(void* ac) {

}

void onLoad(void* workinglib) {
    TCC_registerAbstractCircuitExecutor(workinglib, "AND Gate", and_gate);
    TCC_registerAbstractCircuitExecutor(workinglib, "NOT Gate", not_gate);
}