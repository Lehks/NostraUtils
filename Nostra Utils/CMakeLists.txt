file(GLOB cpp_files "src/source/nostrautils/*/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/Nostra Utils/src/header")

add_library(NostraUtils SHARED "${cpp_files}")