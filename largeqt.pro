QWT_ROOT = /usr/local/qwt-6.1.3
macx {
QWT_ROOT = /usr/local/Cellar/qwt/6.1.3_4/features
}
include( $${QWT_ROOT}/qwtconfig.pri )
include( $${QWT_ROOT}/qwtfunctions.pri )

QWT_OUT_ROOT = $${PWD}

TEMPLATE     = app

INCLUDEPATH += $${QWT_ROOT}/src
DEPENDPATH  += $${QWT_ROOT}/src

!debug_and_release {

    DESTDIR      = $${QWT_OUT_ROOT}/bin
}
else {
    CONFIG(debug, debug|release) {

        DESTDIR      = $${QWT_OUT_ROOT}/bin_debug
    }
    else {

        DESTDIR      = $${QWT_OUT_ROOT}/bin
    }
}

QMAKE_RPATHDIR *= $${QWT_OUT_ROOT}/lib
qwtAddLibrary($${QWT_OUT_ROOT}/lib, qwt)

greaterThan(QT_MAJOR_VERSION, 4) {

    QT += printsupport
    QT += concurrent
}

contains(QWT_CONFIG, QwtOpenGL ) {

    QT += opengl
}
else {

    DEFINES += QWT_NO_OPENGL
}

contains(QWT_CONFIG, QwtSvg) {

    QT += svg
}
else {

    DEFINES += QWT_NO_SVG
}


win32 {
    contains(QWT_CONFIG, QwtDll) {
        DEFINES    += QT_DLL QWT_DLL
    }
}

macx {
   LIBS += -L/usr/local/lib
   INCLUDEPATH += /usr/local/include
}
CONFIG += qwt
CONFIG += c++11

TARGET       = scatterplot

HEADERS = \
    mainwindow.h \
    plot.h \
    pixelsne/LargeVis.h \
    pixelsne/pixelsne.h \
    pixelsne/ptree.h \
    pixelsne/vptree.h



LIBS += -lm
LIBS += -pthread
LIBS += -lgsl
LIBS += -lgslcblas

SOURCES = \
    main.cpp \
    mainwindow.cpp \
    plot.cpp \
    pixelsne/LargeVis.cpp \
    pixelsne/pixelsne.cpp \
    pixelsne/ptree.cpp
