#include <tcclib.h>

void ground(void* ac) {
    printf(ac);
}

void power(void* ac) {
    printf(ac);
}

void constant(void* ac) {
    printf(ac);
}

void splitter(void* ac) {
    printf(ac);
}

void tunnel(void* ac) {
    printf(ac);
}

void pin(void* ac) {
    printf(ac);
}

void bit_extender(void* ac) {
    printf(ac);
}

void transistor(void* ac) {
    printf(ac);
}

void pull_resistor(void* ac) {
    printf(ac);
}

void transmission_gate(void* ac) {
    printf(ac);
}

void probe(void* ac) {
    printf(ac);
}

void clock(void* ac) {
    printf(ac);
}

void onLoad(void* workinglib) {
    TCC_registerAbstractCircuitExecutor(workinglib, "Ground", ground);
    TCC_registerAbstractCircuitExecutor(workinglib, "Power", power);
    TCC_registerAbstractCircuitExecutor(workinglib, "Constant", constant);
    TCC_registerAbstractCircuitExecutor(workinglib, "Splitter", splitter);
    TCC_registerAbstractCircuitExecutor(workinglib, "Tunnel", tunnel);
    TCC_registerAbstractCircuitExecutor(workinglib, "Pin", pin);
    TCC_registerAbstractCircuitExecutor(workinglib, "Bit Extender", bit_extender);
    TCC_registerAbstractCircuitExecutor(workinglib, "Transistor", transistor);
    TCC_registerAbstractCircuitExecutor(workinglib, "Pull Resistor", pull_resistor);
    TCC_registerAbstractCircuitExecutor(workinglib, "Transmission Gate", transmission_gate);
    TCC_registerAbstractCircuitExecutor(workinglib, "Probe", probe);
    TCC_registerAbstractCircuitExecutor(workinglib, "Clock", clock);
}