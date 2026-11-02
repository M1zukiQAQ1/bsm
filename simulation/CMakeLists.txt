cmake_minimum_required(VERSION 3.16)
project(MuonB10 LANGUAGES CXX)

# Generate build/compile_commands.json for clangd.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The conda Geant4 build ships without Qt, so treat it as optional.
find_package(Geant4 REQUIRED ui_all vis_all OPTIONAL_COMPONENTS qt)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(muonB10
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/ActionInitialization.cpp
    ${SRC_DIR}/DetectorConstruction.cpp
    ${SRC_DIR}/actions/PrimaryGeneratorAction.cpp
    ${SRC_DIR}/actions/RunAction.cpp
    ${SRC_DIR}/actions/MuonMinusSteppingAction.cpp
    ${SRC_DIR}/physics/MyPhysicsList.cpp
    # physics/BSMProcess.cpp is still an empty stub; add it once implemented.
)

target_compile_features(muonB10 PRIVATE cxx_std_17)

target_include_directories(muonB10 PRIVATE
    ${SRC_DIR}
    ${SRC_DIR}/actions
    ${SRC_DIR}/physics
    ${Geant4_INCLUDE_DIRS}
)

target_compile_definitions(muonB10 PRIVATE ${Geant4_DEFINITIONS})

target_link_libraries(muonB10 PRIVATE ${Geant4_LIBRARIES})
