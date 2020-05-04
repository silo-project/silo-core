#include <tcclib.h>

static int TCC_registerAbstractCircuitExecutor(const char* compname, void(*executorPointer)(void* abstractNode));

void ground(void* ac) {

}

void power(void* ac) {

}

void constant(void* ac) {

}

void splitter(void* ac) {

}

void tunnel(void* ac) {

}

void pin(void* ac) {

}

void bit_extender(void* ac) {

}

void transistor(void* ac) {

}

void pull_resistor(void* ac) {

}

void transmission_gate(void* ac) {

}

void probe(void* ac) {

}

void clock(void* ac) {

}

void onLoad() {
    printf("Loading Start");
    TCC_registerAbstractCircuitExecutor("Ground", ground);
    TCC_registerAbstractCircuitExecutor("Power", power);
    TCC_registerAbstractCircuitExecutor("Constant", constant);
    TCC_registerAbstractCircuitExecutor("Splitter", splitter);
    TCC_registerAbstractCircuitExecutor("tunnel", tunnel);
    TCC_registerAbstractCircuitExecutor("Pin", pin);
    TCC_registerAbstractCircuitExecutor("Bit Extender", bit_extender);
    TCC_registerAbstractCircuitExecutor("Transistor", transistor);
    TCC_registerAbstractCircuitExecutor("Pull Resistor", pull_resistor);
    TCC_registerAbstractCircuitExecutor("Transmission Gate", transmission_gate);
    TCC_registerAbstractCircuitExecutor("Probe", probe);
    TCC_registerAbstractCircuitExecutor("Clock", clock);
    printf("Loading End");
}