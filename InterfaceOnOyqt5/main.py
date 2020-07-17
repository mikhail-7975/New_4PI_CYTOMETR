from mainWindowController import *

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w1 = mainWindowController()
    w1.show()
    app.exec_()