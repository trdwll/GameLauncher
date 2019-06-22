#-------------------------------------------------
#
# Project created by QtCreator 2019-06-21T16:52:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameLauncher
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
        http.cpp \
        libHDiffPatch/HDiff/diff.cpp \
        libHDiffPatch/HDiff/private_diff/bytes_rle.cpp \
        libHDiffPatch/HDiff/private_diff/compress_detect.cpp \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort.c \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort64.c \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/adler_roll.c \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/digest_matcher.cpp \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/stream_serialize.cpp \
        libHDiffPatch/HDiff/private_diff/suffix_string.cpp \
        libHDiffPatch/HPatch/patch.c \
        logindialog.cpp \
        main.cpp \
        mainwindow.cpp \
        user.cpp

HEADERS += \
        http.h \
        libHDiffPatch/HDiff/diff.h \
        libHDiffPatch/HDiff/diff_types.h \
        libHDiffPatch/HDiff/private_diff/bytes_rle.h \
        libHDiffPatch/HDiff/private_diff/compress_detect.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/config.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort.c.inc.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort64.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/divsufsort_private.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/sssort.c.inc.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/trsort.c.inc.h \
        libHDiffPatch/HDiff/private_diff/libdivsufsort/utils.c.inc.h \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/adler_roll.h \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/bloom_filter.h \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/covers.h \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/digest_matcher.h \
        libHDiffPatch/HDiff/private_diff/limit_mem_diff/stream_serialize.h \
        libHDiffPatch/HDiff/private_diff/mem_buf.h \
        libHDiffPatch/HDiff/private_diff/pack_uint.h \
        libHDiffPatch/HDiff/private_diff/sais.hxx \
        libHDiffPatch/HDiff/private_diff/suffix_string.h \
        libHDiffPatch/HPatch/checksum_plugin.h \
        libHDiffPatch/HPatch/patch.h \
        libHDiffPatch/HPatch/patch_private.h \
        libHDiffPatch/HPatch/patch_types.h \
        logindialog.h \
        mainwindow.h \
        user.h

FORMS += \
        logindialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
