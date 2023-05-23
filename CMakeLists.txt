cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Simulation)

file(COPY ${PROJECT_SOURCE_DIR}/macros DESTINATION .)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sim sim.cc ${sources} ${headers})

add_library(libCRY STATIC IMPORTED)
set_target_properties(libCRY PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/cry_v1.7/lib/libCRY.a")
set_target_properties(libCRY PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/cry_v1.7/src")

target_link_libraries(sim ${Geant4_LIBRARIES} libCRY)


add_custom_target(Simulation DEPENDS sim)
