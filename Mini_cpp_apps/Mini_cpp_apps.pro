
QT += widgets
QT += core
TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle


SOURCES += \
        main.cpp \
    arb_selection_move.cpp \
    count_adj_equals.cpp \
    Fraction.cpp \
    is_sorted.cpp \
    equality.cpp \
    partition.cpp \
    raii.cpp \
    sharedptr_singleton.cpp \
    split_string.cpp \
    vocab.cpp \
    integer_base.cpp \
    getpairscount.cpp \
    pattern.cpp

HEADERS += \
    function_declarations.h \
    Fraction.h \
    linkedlist.h \
    raii.h \
    integer_base.h

DISTFILES += \
    words
