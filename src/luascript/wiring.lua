function regAbstractCircuit()
    print("regAbstractCircuit()")
    registerAbstractCircuit("Splitter", "splitter")
    registerAbstractCircuit("Pull Resistor", "pullresistor")
    registerAbstractCircuit("Constant", "constant")
    registerAbstractCircuit("Clock", "clock")
    registerAbstractCircuit("Ground", "ground")
    registerAbstractCircuit("Tunnel", "tunnel")
    registerAbstractCircuit("Transistor", "transistor")
    registerAbstractCircuit("Power", "power")
    registerAbstractCircuit("Pin", "pin")
    registerAbstractCircuit("Probe", "probe")
    registerAbstractCircuit("Bit Extender", "bitextender")
    registerAbstractCircuit("Transmission Gate", "transmissiongate")
    print("regAbstractCircuit() returning")
    return 0
end

function notgate()

end