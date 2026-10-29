
cmake_minimum_required(VERSION 3.16)
project(MuonB10 LANGUAGES CXX)

find_package(Geant4 REQUIRED qt ui_all vis_all)

add_executable(muonB10 main.cpp DetectorConstruction.cpp MyPhysicsList.cpp PrimaryGeneratorAction.cpp)

target_compile_features(muonB10 PRIVATE cxx_std_17)

target_include_directories(muonB10 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Geant4_INCLUDE_DIRS}
)

target_link_libraries(muonB10 PRIVATE ${Geant4_LIBRARIES})