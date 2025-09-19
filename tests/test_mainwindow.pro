QT += core widgets testlib
CONFIG += console c++11
SOURCES += test_mainwindow.cpp \
	../src/mainwindow.cpp \
	../src/datawidget.cpp \
	../src/animatedprogressbar.cpp \
	../src/graphwidget.cpp
HEADERS += ../src/mainwindow.h \
		   ../src/datawidget.h \
		   ../src/animatedprogressbar.h \
		   ../src/graphwidget.h
INCLUDEPATH += ../src
