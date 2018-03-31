# NostraUtils
A Utility Library for the Nostra Game Engine.


# Building the Project
To build this project, CMake is required. See this (https://cmake.org/install/) link for an explanation on how to install CMake.
On Windows, Visual Stuido (www.visualstudio.com) is also a requirement.

Building the project is done in two steps: 
1. Generating platform dependent configuration (like a Makefile Solution or Visual Studio) using CMake.
2. Compiling the code from those configurations. 

## Calling CMake
Calling CMake can be done using the terminal or CMake's graphical user iterface CMake-GUI.

### Terminal 
#### Unix/Linux
Call the command "mkdir Build/ ; cd Build/ ; cmake ../" from the project's root directory.

#### Windows
Call the command "md Build\ & cd Build\ & cmake ..\" from the project's root directory.

### CMake-GUI
1. Open the CMake GUI (this can be done from the terminal [Windows and Unix/Linux] using the command "cmake-gui").
2. In the GUI, for the folder that is labeled "Where the source code:" choose the root directory of the project.
3. For the folder that is labeled "Where to build the binaries:" choose "RootDirectory/Build/" (RootDirectory is the root directory of the project)
4. Click the button "Configure". When prompted to choose a generator, the default generator is usually a good choice.
5. After CMake is done configuring, click the button "Generate".

## Building the binaries
This is very platform and generator dependent. At this point, it is assumed that the generators that were choosen are Makefile on Unix/Linux and VisualStudio on Windows.

### Unix/Linux
1. Navigate to the folder "Build/" in the project root folder. If in the previous step, CMake was called using the termian, this should still be the case.
2. Call the command "make". This will build the project and place the output files in the folder "Build/bin/".

### Windows
1. Open the file "Build/NostraUtils.sln" using Visual Studio.
2. In the toolbar at the top,choose "Release" as configuration. The default value is "Debug".
3. In the solution explorer, right click the project "ALL_BUILD" and from the context menu select "Build". This will build the project and place the output files in the folder "Build/bin/".
