from settingsWindow import *

class settingsWindowController(QtWidgets.QDialog, Ui_SettingsWindow):
    def __init__(self, parent = None):
        super(settingsWindowController, self).__init__(parent)
        self.setupUi(self)