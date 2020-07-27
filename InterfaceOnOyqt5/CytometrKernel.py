class portStatuses:
    disconnect = 0
    connect = 1
    problems = 2

class cytoStatuses:
    readData = 1
    notReadData = 0

class cytometr:
    serialPort = None
    serialPortStatus = portStatuses.disconnect
    status = cytoStatuses.notReadData
    gain = 0
    triggerLevel = 0
