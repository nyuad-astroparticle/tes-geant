cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

link_directories(${CRYHOME})

# file(GLOB CRYsources ${PROJECT_SOURCE_DIR}/*.cc)
# file(GLOB CRYheaders ${PROJECT_SOURCE_DIR}/*.cc)

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(sim sim.cc ${sources} ${headers}) 
target_link_libraries(sim ${Geant4_LIBRARIES} ${CRYHOME}/lib/libCRY.a)


add_custom_target(Simulation DEPENDS sim)
