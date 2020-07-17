from mainWindowController import *

if __name__ == "__main__":
    import sys
    #orderDB = db.create_db("orderDB")
    #db.save_to_file(orderDB, "orderdb.txt")
    app = QtWidgets.QApplication(sys.argv)
    w1 = mainWindowController()  # = QtWidgets.QMainWindow()
    # ui = Ui_MainWindow()
    # ui.setupUi(MainWindow)
    w1.show()  # MainWindow.show()
    app.exec_()