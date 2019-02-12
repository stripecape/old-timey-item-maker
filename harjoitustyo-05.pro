TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += main.cpp \
    apufunktiot.cpp \
    tiedoston_luku.cpp \
    kayttoliittyma.cpp \
    lista.cpp

HEADERS += \
    apufunktiot.hh \
    tiedoston_luku.hh \
    kayttoliittyma.hh \
    lista.hh

OTHER_FILES += \
    reseptit-complex.txt \
    txt.txt

