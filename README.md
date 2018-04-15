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

Nostra Utils war written for the C++17 standard and uses a lot of C++17 features. **Officially, C++17 is the minimum required C++ standard.** There is is however a so-called C++14 compatibility mode, which disables or modifies some features in the library to try to enable C++14 support. There are still a lot of C++14 features left (like static_assert without a message or nested namespace definitions) so it is not guaranteed that the compiler actually supports those features.

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
Calling CMake can be done using the terminal or CMake's graphical user interface CMake-GUI.

#### Terminal 
It is assumed, that the command *cmake* is in the system's PATH variable. Otherwise the entire path to the
CMake executable must be given instead of just *cmake*.

##### Unix/Linux
Call the command 
```bash
mkdir Build/ ; cd Build/ ; cmake ../ ; cmake --build . --target --install
``` 
from the project's root directory.

This will compile and install the binaries in the default install location (which is "/usr/local" on Linux/Unix and "C:/Program Files" on Windows)

To change the installation directory, the above command needs to be changed to: 

```bash
mkdir Build/ ; cd Build/ ; cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/directory ../ ; cmake --build . --target --install
``` 

**Note:** If more CMake options need to be changed, it is generally easier to use cmake-gui or ccmake.

**Note:** If any other compiler than GCC should be used, it is necessary to call these commands before:  

```bash
export CC=/absolute/path/to/the/c/compiler/executable
export CXX=/absolute/path/to/the/c++/compiler/executable
```

##### Windows
Call the command 
```bash
md Build & cd Build & cmake ../ & 
``` 
from the project's root directory.

**Note:** This command only works with the cmd.exe, if the Powershell used, the command from 
[Unix/Linux](#Unix/Linux) 
should be used.

#### CMake-GUI
1. Open the CMake GUI (this can be done from the terminal
   using the command *cmake-gui*).
2. In the GUI, for the folder that is labeled "Where the source code:" choose the root directory of the 
   project.
3. For the folder that is labeled "Where to build the binaries:" choose "/Path/To/Project/Root/Build/" 
   (/Path/To/Project/Root/ is the path to the root directory of the project; this is the directory that 
   contains the file NostraUtils.sln)
4. Click the button "Configure". When prompted to choose a generator, the default generator is usually a good 
   choice.
5. After CMake is done configuring, click the button "Generate".

### Building the binaries
**Note:** For the sake of generality, the binaries will only be built from the terminal using CMake commands. Otherwise, the process would be very platform- and generator dependent.

Building the binaries is rather simple and can be done using the command

```
cmake --build . --target install
```

**Note:** It is assumed that the previous command was called from the directory that CMake has build in (which was Build/ in the source's root directory).

## Dependencies
This Library uses Catch (https://github.com/catchorg/Catch2) as Unit-Test framework. The source file of Catch (Unittests/Catch/catch.hpp) has not been altered.
