QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LAverageBot.cpp \
    LBeginBot.cpp \
    LBiGame.cpp \
    LBoard.cpp \
    LBotGame.cpp \
    LBotTree.cpp \
    LChessBoard.cpp \
    LClient.cpp \
    LConfirm.cpp \
    LDesk.cpp \
    LElephant.cpp \
    LFigure.cpp \
    LGame.cpp \
    LHorse.cpp \
    LKing.cpp \
    LLoadGame.cpp \
    LMain.cpp \
    LNetGame.cpp \
    LNewGame.cpp \
    LOptions.cpp \
    LPath.cpp \
    LPawn.cpp \
    LPlayer.cpp \
    LQueen.cpp \
    LRook.cpp \
    LSaveGame.cpp \
    LSaveKeeper.cpp \
    LSquare.cpp \
    LStrongBot.cpp \
    LTcpClient.cpp \
    LTcpServer.cpp \
    LTransform.cpp \
    LWeakBot.cpp \
    LWebClient.cpp \
    main.cpp

HEADERS += \
    LAverageBot.h \
    LBeginBot.h \
    LBiGame.h \
    LBoard.h \
    LBotGame.h \
    LBotTree.h \
    LChessBoard.h \
    LClient.h \
    LConfirm.h \
    LConst.h \
    LDesk.h \
    LElephant.h \
    LFigure.h \
    LGame.h \
    LHorse.h \
    LKing.h \
    LLoadGame.h \
    LMain.h \
    LNetGame.h \
    LNewGame.h \
    LOptions.h \
    LPath.h \
    LPawn.h \
    LPlayer.h \
    LQueen.h \
    LRook.h \
    LSaveGame.h \
    LSaveKeeper.h \
    LSquare.h \
    LStrongBot.h \
    LTcpClient.h \
    LTcpServer.h \
    LTransform.h \
    LWeakBot.h \
    LWebClient.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    LChess2.qrc

DISTFILES += \
    LBElephant.png \
    LBHorse.png \
    LBKing.png \
    LBPawn.png \
    LBQueen.png \
    LBRook.png \
    LWElephant.png \
    LWHorse.png \
    LWKing.png \
    LWPawn.png \
    LWQueen.png \
    LWRook.png \
    PreView.png
