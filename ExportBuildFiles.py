from shutil import copytree, ignore_patterns, copy


#copy include files
copytree("./Nostra Utils/src/header", "./BuildFiles/include")

#copy entire project tree of "Nostra Utils"
copytree("./Nostra Utils/", "./BuildFiles/CMake/Nostra Utils", False, ignore_patterns("*.vcxproj*", "output"))

#copy solution level CMakeLists.txt
copy("./CMakeLists.txt", "./BuildFiles/CMake")