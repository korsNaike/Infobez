# CMakeList.txt: проект CMake для InfoBez_Lab2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project (
    "InfoBez_Lab2"
    VERSION 1.0
    LANGUAGES CXX
)

include_directories (src)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")

add_executable(main ${SOURCES} ${HEADERS})

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG 9cca280a4d0ccf0c08f47a99aa71d1b0e52f8d03 # Здесь можно указать актуальную версию
)
FetchContent_MakeAvailable(nlohmann_json)


target_link_libraries(main PUBLIC nlohmann_json::nlohmann_json)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
