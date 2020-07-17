from mainWindow import *
from settingsWindow import *

class mainWindowController(QtWidgets.QDialog, Ui_MainWindow):
    def __init__(self, parent = None):
        super(mainWindowController, self).__init__(parent)
        self.setupUi(self)
        self.settingsPushButton.clicked.connect(self.settingsButtonCliked)

    @QtCore.pyqtSlot()
    def settingsButtonCliked(self):
        settingsWindow = settingsWindowController()
        settingsWindow.exec_()