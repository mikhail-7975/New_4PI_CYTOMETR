# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'untitled.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1281, 810)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.PlotWidget = PlotWidget(self.centralwidget)
        self.PlotWidget.setGeometry(QtCore.QRect(40, 30, 1191, 501))
        self.PlotWidget.setObjectName("plotWidget")
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(40, 620, 1191, 111))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.buttonsGridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.buttonsGridLayout.setContentsMargins(0, 0, 0, 0)
        self.buttonsGridLayout.setObjectName("buttonsGridLayout")
        self.startShowingPushButton_2 = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.startShowingPushButton_2.setObjectName("startShowingPushButton_2")
        self.buttonsGridLayout.addWidget(self.startShowingPushButton_2, 0, 4, 1, 1)
        self.previousFramePushButton = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.previousFramePushButton.setObjectName("previousFramePushButton")
        self.buttonsGridLayout.addWidget(self.previousFramePushButton, 1, 4, 1, 1)
        self.settingsPushButton = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.settingsPushButton.setObjectName("SettingsPushButton")
        self.buttonsGridLayout.addWidget(self.settingsPushButton, 0, 1, 1, 1)
        self.startReadingPushButton = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.startReadingPushButton.setObjectName("startReadingPushButton")
        self.buttonsGridLayout.addWidget(self.startReadingPushButton, 1, 1, 1, 1)
        self.stopReadingPushButton = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.stopReadingPushButton.setObjectName("stopReadingPushButton")
        self.buttonsGridLayout.addWidget(self.stopReadingPushButton, 1, 2, 1, 1)
        self.nextFramePushButton = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.nextFramePushButton.setObjectName("nextFramePushButton")
        self.buttonsGridLayout.addWidget(self.nextFramePushButton, 1, 5, 1, 1)
        self.pausePushButton = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.pausePushButton.setObjectName("pausePushButton")
        self.buttonsGridLayout.addWidget(self.pausePushButton, 0, 5, 1, 1)
        self.pushButton_5 = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.pushButton_5.setObjectName("pushButton_5")
        self.buttonsGridLayout.addWidget(self.pushButton_5, 0, 6, 1, 1)
        self.SaveInFilePushButton = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.SaveInFilePushButton.setObjectName("SaveInFilePushButton")
        self.buttonsGridLayout.addWidget(self.SaveInFilePushButton, 1, 6, 1, 1)
        self.dataScrollArea = QtWidgets.QScrollArea(self.centralwidget)
        self.dataScrollArea.setGeometry(QtCore.QRect(40, 540, 1191, 71))
        self.dataScrollArea.setWidgetResizable(True)
        self.dataScrollArea.setObjectName("dataScrollArea")
        self.scrollAreaWidgetContents = QtWidgets.QWidget()
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 1189, 69))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.showDataLabel = QtWidgets.QLabel(self.scrollAreaWidgetContents)
        self.showDataLabel.setGeometry(QtCore.QRect(4, 5, 1181, 61))
        self.showDataLabel.setObjectName("showDataLabel")
        self.dataScrollArea.setWidget(self.scrollAreaWidgetContents)
        #MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1281, 26))
        self.menubar.setObjectName("menubar")
        #MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        #MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.startShowingPushButton_2.setText(_translate("MainWindow", "start showing |>"))
        self.previousFramePushButton.setText(_translate("MainWindow", "<< previous frame"))
        self.settingsPushButton.setText(_translate("MainWindow", "setting"))
        self.startReadingPushButton.setText(_translate("MainWindow", "start reading"))
        self.stopReadingPushButton.setText(_translate("MainWindow", "stop reading"))
        self.nextFramePushButton.setText(_translate("MainWindow", "next frame >>"))
        self.pausePushButton.setText(_translate("MainWindow", "pause ||"))
        self.pushButton_5.setText(_translate("MainWindow", "stop and celar"))
        self.SaveInFilePushButton.setText(_translate("MainWindow", "save in file"))
        self.showDataLabel.setText(_translate("MainWindow", "TextLabel"))
from pyqtgraph import PlotWidget


