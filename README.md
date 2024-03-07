## Overview
A simple cmake template 
- Works with VS Code and Visual Studio 2022
- Works on Windows (probably Linux as well but have not tested)
- Initialize with : `cmake -S . -B ./_build`
- Pulls down 3rd party dependancies with CMake Fetch
- Makes `ASSETS_PATH` macro available to code
## Structure
```
_build/ - Location for build artifacts (gitignore)  
_external/ (Compiled/src 3rd party libraries and headers)  
assets/ - binary assets (textures, audio files, compiled shaders)  
sources/ (Source files for project)  
.gitattributes  
.gitignore  
LICENCE  
CMakeLists.txt  
README  
```
## Asset handling
CMAKE implements `ASSETS_PATH` as either a relative or absolute path to assets/
