QT += widgets

SOURCES += src/main.cpp \
    src/huffman.cpp \
    src/occurences.cpp \
    src/fenetreprincipale.cpp \
    src/codage.cpp \
    src/dialogmodifnoeud.cpp \
    src/arbrehuff.cpp \
    src/cliste.cpp \
    src/cnoeud.cpp

HEADERS  += \
    include/huffman.h \
    include/occurences.h \
    include/fenetreprincipale.h \
    include/codage.h \
    include/arbrehuff.h \
    include/cliste.h \
    include/cnoeud.h \
    include/dialogmodifnoeud.h

RESOURCES += \
    res/images.qrc

RC_ICONS += res/images/app.ico
