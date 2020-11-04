#-------------------------------------------------
#
# Project created by QtCreator 2020-10-14T02:03:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../TEMU/temu/src/initsys.c \
    ../TEMU/temu/src/cpu/exec.c \
    ../TEMU/temu/src/cpu/i-type.c \
    ../TEMU/temu/src/cpu/r-type.c \
    ../TEMU/temu/src/cpu/reg.c \
    ../TEMU/temu/src/cpu/special.c \
    ../TEMU/temu/src/memory/dram.c \
    ../TEMU/temu/src/memory/memory.c \
    ../TEMU/temu/src/monitor/cpu-exec.c \
    ../TEMU/temu/src/monitor/expr.c \
    ../TEMU/temu/src/monitor/monitor.c \
    ../TEMU/temu/src/monitor/ui.c \
    ../TEMU/temu/src/monitor/watchpoint.c \
    ../TEMU/temu/src/decode_tool/decode.c \
    ../TEMU/temu/src/decode_tool/fake_exec.c \
    ../TEMU/temu/src/decode_tool/d_i_type.c \
    ../TEMU/temu/src/decode_tool/d_r_type.c \
    ../TEMU/temu/src/decode_tool/d_special.c


HEADERS += \
        mainwindow.h \
    ../TEMU/temu/include/common.h \
    ../TEMU/temu/include/debug.h \
    ../TEMU/temu/include/macro.h \
    ../TEMU/temu/include/misc.h \
    ../TEMU/temu/include/temu.h \
    ../TEMU/temu/include/cpu/all-instr.h \
    ../TEMU/temu/include/cpu/helper.h \
    ../TEMU/temu/include/cpu/i-type.h \
    ../TEMU/temu/include/cpu/operand.h \
    ../TEMU/temu/include/cpu/reg.h \
    ../TEMU/temu/include/cpu/r-type.h \
    ../TEMU/temu/include/cpu/special.h \
    ../TEMU/temu/include/memory/burst.h \
    ../TEMU/temu/include/memory/memory.h \
    ../TEMU/temu/include/monitor/expr.h \
    ../TEMU/temu/include/monitor/monitor.h \
    ../TEMU/temu/include/monitor/watchpoint.h \
    ui_buffer.h \
    outputfunc.h \
    inst_decode.h \

FORMS += \
        mainwindow.ui
