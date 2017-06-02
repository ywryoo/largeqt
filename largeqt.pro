QWT_ROOT = /usr/local/qwt-6.1.3
HOME=/home/ywryoo
NON_METRIC_SPACE_LIBRARY=$${HOME}/NonMetrLibRelease
NON_METRIC_SPACE_LIBRARY_INC=$${NON_METRIC_SPACE_LIBRARY}/include
NON_METRIC_SPACE_LIBRARY_LIB=$${NON_METRIC_SPACE_LIBRARY}/lib
macx {
    QWT_ROOT = /usr/local/Cellar/qwt/6.1.3_4/features
}
include( $${QWT_ROOT}/qwtconfig.pri )
include( $${QWT_ROOT}/qwtfunctions.pri )
LIBS += -L$${QWT_ROOT}/lib
OUT_ROOT = $${PWD}

TEMPLATE     = app

INCLUDEPATH += $${NON_METRIC_SPACE_LIBRARY_INC}
INCLUDEPATH += $${QWT_ROOT}/src
DEPENDPATH  += $${QWT_ROOT}/src

QT += widgets core
QMAKE_CFLAGS	+=  -ffast-math -march=native -Ofast -fopenmp
QMAKE_CXXFLAGS	+=  -ffast-math -march=native -Ofast -fopenmp
LIBS += -fopenmp
!debug_and_release {

    DESTDIR      = $${OUT_ROOT}/bin
}
else {
    CONFIG(debug, debug|release) {

        DESTDIR      = $${OUT_ROOT}/bin_debug
    }
    else {

        DESTDIR      = $${OUT_ROOT}/bin
    }
}

QMAKE_RPATHDIR *= $${OUT_ROOT}/lib
qwtAddLibrary($${OUT_ROOT}/lib, qwt)

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
    LIBS += -lboost_thread-mt
    LIBS += -lboost_system-mt
}

linux {
    INCLUDEPATH += /usr/include/boost
    LIBS += -lboost_thread 
    LIBS += -lboost_system
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
    pixelsne/ANNOY/annoylib.h \
    pixelsne/sptreeBH.h \
    pixelsne/ANNOY/kissrandom.h \
    pixelsne/vptree.h \
    borderlayout.h \
    workerthread.h \
    neighborthread.h \
    huecolormap.h

LIBS += -L$${NON_METRIC_SPACE_LIBRARY_LIB}
LIBS += -lm
LIBS += -pthread
LIBS += -lgsl
LIBS += -lgslcblas
LIBS += -lNonMetricSpaceLib

SOURCES = \
    main.cpp \
    mainwindow.cpp \
    plot.cpp \
    pixelsne/LargeVis.cpp \
    pixelsne/pixelsne.cpp \
    pixelsne/sptreeBH.cpp \
    pixelsne/ptree.cpp \
    borderlayout.cpp \
    workerthread.cpp \
    neighborthread.cpp

