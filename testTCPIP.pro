#-------------------------------------------------
#
# Project created by QtCreator 2019-05-28T17:23:56
#
#-------------------------------------------------

QT += core gui network widgets

TARGET = testTCPIP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
		actions/actionwidgetbase.cpp \
		actions/testpacket.cpp \
		client/client.cpp \
		client/clientsocketadapter.cpp \
		clientproc.cpp \
		clientwidget.cpp \
		common/isocketadapter.cpp \
		common/socketadapter.cpp \
		cyclewidget.cpp \
		main.cpp \
		mainwindow.cpp \
		packetwidget.cpp \
		receivewidget.cpp \
		sendwidget.cpp \
		server/server.cpp \
		server/serversocketadapter.cpp \
		serverwidget.cpp \
		serverproc.cpp \
		tcpheader.cpp \
		widgetfactory.cpp

HEADERS += \
	actions/actionwidgetbase.h \
	actions/testpacket.h \
	client/client.h \
	client/clientsocketadapter.h \
	clientproc.h \
	clientwidget.h \
	common/isocketadapter.h \
	common/socketadapter.h \
	cyclewidget.h \
	logging.h \
		mainwindow.h \
	packetwidget.h \
	receivewidget.h \
	sendwidget.h \
	server/server.h \
	server/serversocketadapter.h \
		serverwidget.h \
		serverproc.h \
		tcpheader.h \
	widgetfactory.h

FORMS += \
	clientwidget.ui \
	cyclewidget.ui \
		mainwindow.ui \
	packetwidget.ui \
	receivewidget.ui \
	sendwidget.ui \
		serverwidget.ui \
		tcppacket.ui \
	tcpheader.ui

#LIBS += -L/home/baldina/qt5/qtbase/lib -lQt5Network
#INCLUDEPATH += /home/baldina/qt5/qtbase/include/QtNetwork
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
	CmakeLists.txt
