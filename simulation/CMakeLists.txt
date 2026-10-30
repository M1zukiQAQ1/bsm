cmake_minimum_required(VERSION 3.16)
project(MuonB10 LANGUAGES CXX)

# Generate build/compile_commands.json for clangd.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The conda Geant4 build ships without Qt, so treat it as optional.
find_package(Geant4 REQUIRED ui_all vis_all OPTIONAL_COMPONENTS qt)

add_executable(muonB10 main.cpp DetectorConstruction.cpp MyPhysicsList.cpp PrimaryGeneratorAction.cpp)

target_compile_features(muonB10 PRIVATE cxx_std_17)

target_include_directories(muonB10 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Geant4_INCLUDE_DIRS}
)

target_compile_definitions(muonB10 PRIVATE ${Geant4_DEFINITIONS})

target_link_libraries(muonB10 PRIVATE ${Geant4_LIBRARIES})
