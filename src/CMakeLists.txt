cmake_minimum_required(VERSION 2.8)
include_directories (${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${CMAKE_SOURCE_DIR}/src/libshared/src
                     ${ANOMALY_INCLUDE_DIRS})

set (anomaly_SRCS anomaly.cpp Detector.cpp Detector.h)

set (libshared_SRCS
                    libshared/src/format.cpp        libshared/src/format.h
                    libshared/src/shared.cpp        libshared/src/shared.h
                    libshared/src/utf8.cpp          libshared/src/utf8.h
                    libshared/src/wcwidth6.cpp)

add_library (anomaly   STATIC ${anomaly_SRCS})
add_library (libshared STATIC ${libshared_SRCS})
add_executable (anomaly_executable anomaly.cpp)

target_link_libraries (anomaly_executable anomaly libshared ${ANOMALY_LIBRARIES})

set_property (TARGET anomaly_executable PROPERTY OUTPUT_NAME "anomaly")

install (TARGETS anomaly_executable DESTINATION bin)

