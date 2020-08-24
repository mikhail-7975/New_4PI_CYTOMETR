from mainWindowController import *
from threading import Thread
from CytometrKernel import *

class CytometrKernelThread(Thread):
   def __init__(self):
        """Инициализация потока"""
        Thread.__init__(self)


   def run(self):
        """Запуск потока"""
        while(cytometr_kernel.status != cytoStatuses.off):
            while(cytometr_kernel.status == cytoStatuses.readData):
                if(cytometr_kernel.triggerSerialPort == None):
                    print("port == None!!!")
                    break
                inputList = []
                while(cytometr_kernel.triggerSerialPort.inWaiting()):
                    inputList.append(ord(cytometr_kernel.triggerSerialPort.read()) | (ord(cytometr_kernel.triggerSerialPort.read()) << 8))
                cytometr_kernel.dataList.append(inputList)
            if(cytometr_kernel.status == cytoStatuses.writingInFile):
                cytometr_kernel.fileCounter += 1
                outFile = open("ExperimentalData_" + str(cytometr_kernel.fileCounter) + ".txt", 'w')
                outFile.write()

if __name__ == "__main__":
    import sys
    cytKerThread = CytometrKernelThread()
    cytometr_kernel.status = cytoStatuses.on
    app = QtWidgets.QApplication(sys.argv)
    w1 = mainWindowController()
    w1.show()
    cytKerThread.start()
    exitCode = app.exec_()
    cytometr_kernel.status = cytoStatuses.off
    cytKerThread.join()
    exit(exitCode)
