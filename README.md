# NRgine
NRgine is my 3d engine for training C++ skills. Also it provides access for any recruitment managers to check my source code quality.

## Installation
- ### Environment setup: 
    ### Ubuntu:
    - Install libraries:
    ```
    sudo apt install \
    libglew-dev \
    libstb-dev \
    libgtest-dev \
    libglm-dev \
    libassimp-dev
    ```
    ### Windows:
    - Install msys2
    - Run command to intall packages:
    ```
    pacman -S \
    mingw-w64-x86_64-glew \
    mingw-w64-x86_64-glfw \
    mingw-w64-x86_64-freeglut \
    mingw-w64-x86_64-assimp \
    mingw-w64-x86_64-gtest \
    mingw-w64-x86_64-stb \
    mingw-w64-x86_64-glade \
    mingw-w64-x86_64-glm \
    mingw-w64-x86_64-gegl \
    mingw-w64-x86_64-toolchain
    ```
    Ensure that environment path "C:\msys64\mingw64\bin\" before "C:\msys64\usr\bin\".
    
    ### Docker:
    This command will build executable for unix. Can be started via windows.
    ```
    docker compose up gcc --build
    ```

- ### Build & Run
    Open terminal and run next command:
    ```
    make release
    ```
    And run executable from directory ./release