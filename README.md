# NostraUtils
A Utility Library for the Nostra Game Engine.

It is a project made by students of the htw saar (https://www.htwsaar.de/) and supervised by Dipl-Inf (FH) 
Christopher Olbertz.

GitHub: https://github.com/Lehks/NostraUtils

If you do not have the code yet, use the following command to clone the repository to your local
machine:  
```bash
git clone https://github.com/Lehks/NostraUtils.git
```` 
or download the ZIP-compressed directly from GitHub using the link above.

## Requirements

Nostra Utils was written for the C++17 standard and uses a lot of C++17 features. **Officially, C++17 is the minimum required C++ standard.** There is is however a so-called C++14 compatibility mode which disables or modifies some features in the library to try to enable C++14 support. There are still a lot of C++14 features left (like static_assert without a message or nested namespace definitions) so it is not guaranteed that the compiler actually supports those features.

Tests for the C++14 compatibility mode were run on:
- GCC
    - Linux
        - Version 7.2.0
        - Version 6.3.1
- Clang
    - Linux
        - Version 4.0.1 (with a lot of warnings because of the usage of C++1z features)

## Building the Project
To build this project, CMake is required. See this (https://cmake.org/install/) link for an explanation on how
to install CMake.
On Windows, Visual Studio (https://www.visualstudio.com) is also a requirement.

Building the project is done in two steps: 
1. Generating platform dependent configuration (like a Makefile or Visual Studio Solution) using CMake 
   (Chapter [Calling CMake](#Calling-CMake)).
2. Compiling the code from those configurations (Chapter [Building the Binaries](#Building-the-Binaries)).

### Calling CMake
Calling CMake can be done using the terminal or CMake\'s graphical user interface CMake-GUI.

#### Terminal 
It is assumed, that the command ```cmake``` is in the system\'s PATH variable. Otherwise the entire path to the
CMake executable must be given instead of just ```cmake```.

0. Navigate to the root directory of the source code.
1. ```mkdir Build``` Create the directory to build in.
2. ```cd Build``` Navigate into the build directory.
3. ```cmake ..``` Configure CMake. See note below on how to customize that configuration.
4. ```cmake --build . --target install``` Build the project and export the generated files to the default installation path (with is /usr/local on Linux/Unix and C:\Program Files on Windows).

**Note:** If the build of Nostra Utils should be customized, more parameters need to be passed to CMake (the command from step 3.), but this is generally easier to do with cmake-gui or ccmake (configuring  the build with cmake-gui will be explained in a later chapter).

To change the installation directory, the third command needs to be changed to: 

```
cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/directory ..
``` 

This will change the install directory to the passed one (/path/to/install/directory in this example).

#### CMake-GUI
1. Open the CMake GUI (this can be done from the terminal
   using the command *cmake-gui*).
2. In the GUI, for the folder that is labeled "Where is the source code:" choose the root directory of the 
   project.
3. For the folder that is labeled "Where to build the binaries:" choose the folder "Build" in the root directory of Nostra Utils.
4. Click the button "Configure". When prompted to choose a generator, the default generator is usually a good 
   choice.
5. After CMake is done configuring, click the button "Generate".

### Building the binaries
**Note:** For the sake of generality, the binaries will only be built from the terminal using CMake commands. Otherwise, the process would be very platform- and generator dependent.

Building the binaries is rather simple and can be done using the command

```
cmake --build . --target install
```

**Note:** It is assumed that the previous command was called from the directory that CMake has build in (which was Build/ in the source's root directory during the examples here).

## Dependencies
This Library uses Catch (https://github.com/catchorg/Catch2) as Unit-Test framework. The source file of Catch (Unittests/Catch/catch.hpp) has not been altered.
