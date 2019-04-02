CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(server)
SET(SRC_PATH . )
INCLUDE_DIRECTORIES(.)

#ADD_EXECUTABLE(threadPoolHttpServer ${SRC_PATH}/processHttp.cpp ${SRC_PATH}/tcpThread.cpp ${SRC_PATH}/utilSocket.cpp ${SRC_PATH}/threadPoolServer.cpp)
#TARGET_LINK_LIBRARIES(threadPoolHttpServer pthread)

ADD_EXECUTABLE(threadPoolSimpleServer ${SRC_PATH}/processSimple.cpp ${SRC_PATH}/tcpThread.cpp ${SRC_PATH}/utilSocket.cpp ${SRC_PATH}/threadPoolServer.cpp)
TARGET_LINK_LIBRARIES(threadPoolSimpleServer pthread)

ADD_EXECUTABLE(threadPoolArrayServer ${SRC_PATH}/threadPoolArrayServer.cpp ${SRC_PATH}/utilSocket.cpp)
TARGET_LINK_LIBRARIES(threadPoolArrayServer pthread)

ADD_EXECUTABLE(stopWaitServer ${SRC_PATH}/stopWaitServer.cpp ${SRC_PATH}/utilSocket.cpp)

ADD_EXECUTABLE(client client.cpp utilSocket.cpp)
