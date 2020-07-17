class portStatuses:
    disconnect = 0
    connect = 1
    problems = 2

class cytometr:
    serialPort = None
    serialPortStatus = portStatuses.disconnect
    gain = 0
    triggerLevel = 0
