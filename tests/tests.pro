######################################################################
# Test project file: tests/tests.pro
######################################################################

TEMPLATE = app
TARGET = tests.exe
INCLUDEPATH += ../include

QT += testlib gui core widgets multimedia

CONFIG += console c++11 warn_off

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = ..

OBJECTS_DIR = ../build/tests/obj
MOC_DIR = ../build/tests/moc

# Input
HEADERS += WindowGenerationTests.h \
           PlayerInteractionsTests.h \
           LevelSceneGeneration.h \
           TestsGlobal.h \
           ../include/Arrow.h \
           ../include/ArrowLeft.h \
           ../include/ArrowRight.h \
           ../include/ArrowUp.h \
           ../include/ArrowDown.h \
           ../include/ArrowThrower.h \
           ../include/BreakablePlatform.h \
           ../include/Button.h \
           ../include/Coin.h \
           ../include/EventItem.h \
           ../include/Flag.h \
           ../include/Infos.h \
           ../include/Lava.h \
           ../include/LevelChoiceButton.h \
           ../include/LevelEnd.h \
           ../include/Login.h \
           ../include/MainWindow.h \
           ../include/Menu.h \
           ../include/MovingPlatform.h \
           ../include/MyScene.h \
           ../include/Pause.h \
           ../include/Platform.h \
           ../include/Player.h \
           ../include/PlayerData.h \
           ../include/PushablePlatform.h \
           ../include/SecretRoom.h \
           ../include/SemiPassablePlatform.h \
           ../include/SkillPlatform.h \
           ../include/SlidingPlatform.h \
           ../include/SpecialInitialStateEventItem.h \
           ../include/TextArea.h

SOURCES += WindowGenerationTests.cpp \
           PlayerInteractionsTests.cpp \
           LevelSceneGeneration.cpp \
           TestsGlobal.cpp \
           main.cpp \
           ../src/Arrow.cpp \
           ../src/ArrowLeft.cpp \
           ../src/ArrowRight.cpp \
           ../src/ArrowUp.cpp \
           ../src/ArrowDown.cpp \
           ../src/ArrowThrower.cpp \
           ../src/BreakablePlatform.cpp \
           ../src/Button.cpp \
           ../src/Coin.cpp \
           ../src/EventItem.cpp \
           ../src/Flag.cpp \
           ../src/Infos.cpp \
           ../src/Lava.cpp \
           ../src/LevelChoiceButton.cpp \
           ../src/LevelEnd.cpp \
           ../src/Login.cpp \
           ../src/MainWindow.cpp \
           ../src/Menu.cpp \
           ../src/MovingPlatform.cpp \
           ../src/MyScene.cpp \
           ../src/Pause.cpp \
           ../src/Platform.cpp \
           ../src/Player.cpp \
           ../src/PlayerData.cpp \
           ../src/PushablePlatform.cpp \
           ../src/SecretRoom.cpp \
           ../src/SemiPassablePlatform.cpp \
           ../src/SkillPlatform.cpp \
           ../src/SlidingPlatform.cpp \
           ../src/SpecialInitialStateEventItem.cpp \
           ../src/TextArea.cpp

QMAKE_CXXFLAGS += -fPIC
