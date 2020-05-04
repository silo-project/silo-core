#include <tcclib.h>

void and_gate(void* ac) {
    printf(ac);
}

void not_gate(void* ac) {
    printf(ac);
}

void onLoad() {
    TCC_registerAbstractCircuitExecutor("AND Gate", and_gate);
    TCC_registerAbstractCircuitExecutor("NOT Gate", not_gate);
}