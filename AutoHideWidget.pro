# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = AutoHideWidget
DESTDIR = ./x64/Debug
QT += core sql gui widgets
CONFIG += debug
DEFINES += _UNICODE _ENABLE_EXTENDED_ALIGNED_STORAGE WIN64 QT_DLL QT_WIDGETS_LIB QT_SQL_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName)
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(AutoHideWidget.pri)
RC_ICONS = myico.ico
TARGET = output/param_config
MOC_DIR = debug/
RCC_DIR = debug/
UI_DIR = debug/
OBJECTS_DIR = debug/