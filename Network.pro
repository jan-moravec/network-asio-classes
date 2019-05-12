TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        library/client/networkclient.cpp \
        library/client/networkclientbase.cpp \
        library/client/networkclienticmp.cpp \
        library/client/networkclienttcp.cpp \
        library/client/networkclientudp.cpp \
        library/server/networkserver.cpp \
        library/server/networkserverbase.cpp \
        library/server/networkservericmp.cpp \
        library/server/networkservertcp.cpp \
        library/server/networkserverudp.cpp \
        library/server/networksession.cpp \
        library/server/networksessionbase.cpp \
        library/server/networksessionicmp.cpp \
        library/server/networksessiontcp.cpp \
        library/server/networksessionudp.cpp \
        main.cpp

win32 {
    INCLUDEPATH += C:/Boost/include/boost-1_70
    LIBS += -L C:/Boost/lib -lboost_thread-mgw73-mt-x64-1_70 -lboost_system-mgw73-mt-x64-1_70  \
            -lboost_timer-mgw73-mt-x64-1_70 -lboost_exception-mgw73-mt-x64-1_70 -lboost_filesystem-mgw73-mt-x64-1_70 \
            -lboost_serialization-mgw73-mt-x64-1_70 -lboost_coroutine-mgw73-mt-x64-1_70 -lboost_atomic-mgw73-mt-x64-1_70 \
            -lboost_chrono-mgw73-mt-x64-1_70 -lboost_wserialization-mgw73-mt-x64-1_70 -lws2_32 -lwsock32
}

HEADERS += \
    library/client/networkclient.h \
    library/client/networkclientbase.h \
    library/client/networkclienticmp.h \
    library/client/networkclienttcp.h \
    library/client/networkclientudp.h \
    library/server/networkserver.h \
    library/server/networkserverbase.h \
    library/server/networkservericmp.h \
    library/server/networkservertcp.h \
    library/server/networkserverudp.h \
    library/server/networksession.h \
    library/server/networksessionbase.h \
    library/server/networksessionicmp.h \
    library/server/networksessiontcp.h \
    library/server/networksessionudp.h
