#Generated by VisualGDB project wizard. 
#Feel free to modify any flags you want.
#Visit http://visualgdb.com/makefiles for more details.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conservatoryShader
TEMPLATE = app

#By default the following file lists are updated automatically by VisualGDB.

SOURCES   += conservatoryShader.cpp MainWindow.cpp
HEADERS   += MainWindow.h
FORMS     += MainWindow.ui
RESOURCES += 

include($$lower($$join(CONFIGNAME,,,.pro)))

QMAKE_CFLAGS 	+= $$COMMONFLAGS
QMAKE_CXXFLAGS 	+= $$COMMONFLAGS
QMAKE_LFLAGS 	+= $$COMMONFLAGS

OBJECTS_DIR = $$DESTDIR
MOC_DIR     = $$DESTDIR
RCC_DIR     = $$DESTDIR
UI_DIR      = $$DESTDIR
