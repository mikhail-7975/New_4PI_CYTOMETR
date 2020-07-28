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
            print("working")
            while(cytometr_kernel.status == cytoStatuses.readData):
                if(cytometr_kernel.serialPort == None):
                    break
                inputList = []
                while(cytometr_kernel.serialPort.inWaiting()):
                    inputList.append(ord(cytometr_kernel.serialPort.read()) | (ord(cytometr_kernel.serialPort.read()) << 8))
                cytometr_kernel.dataList.append(inputList)

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
