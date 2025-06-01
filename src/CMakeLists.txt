find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB SRC_FILES *.cpp)

add_executable(${appname} ${SRC_FILES})
target_include_directories(${appname} PRIVATE ${PROJECT_SRC_DIR}/include)
target_link_libraries(${appname} PRIVATE ${CURSES_LIBRARIES})
