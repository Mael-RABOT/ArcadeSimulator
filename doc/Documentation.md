# Documentation

This is the documentation for the arcade project.

# Table of contents
<!-- TOC -->
- [1. Interfaces](#1-interfaces)
    - [IDisplayModule](IDisplayModule.md)
    - [IGameModule](IGameModule.md)
- [2. How to create a display](#2-how-to-create-a-display)
    - [2.1 Entry point](#21-entry-point)
    - [2.2 Display module](#22-display-module)
    - [2.3 Makefile](#23-makefile)
- [3. How to create a game](#3-how-to-create-a-game)
    - [3.1 Entry point](#31-entry-point)
    - [3.2 Game module](#32-game-module)
    - [3.3 Makefile](#33-makefile)
    - [3.1 Game instructions](#31-game-instructions)
- [4. File structure](#4-file-structure)
- [5. Commit message conventions](#5-commit-message-conventions)
    - [5.1 Type](#51-type)

## 1. Interfaces

The project is divided into 2 main interfaces:

- [IDisplayModule](IDisplayModule.md)
- [IGameModule](IGameModule.md)

These interfaces are used to create the graphical and game modules.<br>
They are used to create the dynamic libraries that will be loaded at runtime by the core of the program.

Shared interfaces are stored in the `./include/` directory.<br>
The `make` command will update a [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) that contains the shared interfaces.<br>
The git repository for the shared interfaces is [here](https://github.com/ASM-Studios/ArcadeInterfaces).<br>

## 2. How to create a display

In `./lib/`, create a new directory with the name of your display module.<br>

### 2.1 Entry point

In this directory, create a `.cpp` file and implement the following functions:

```c++
extern "C" {
    IDisplayModule *entryPoint();
    Signature getSignature();
}
```

`entryPoint` is a function that will be called by the core of the program to create an instance of your display module.<br>
It should return a pointer to a new instance of your display module.

`getSignature` is a function that will be called by the core of the program to get the signature of your display module.<br>
It should return a `Signature` type that checks if the display module is compatible with the core of the program. See [Type](Type.md) for more details.

### 2.2 Display module

Alongside those functions, you should implement the `IDisplayModule` interface. See [IDisplayModule](IDisplayModule.md) for more details.<br>

### 2.3 Makefile

Create a `Makefile` to compile your display module. See [Makefile](LibMakefile.md) for a template.<br>
Place your `Makefile` in the same directory as your `.cpp` file.

The library should be named `arcade_<name>.so` where `<name>` is the name of your display module.<br>

Finally, add your display module to the `./lib/Makefile` to compile it.

## 3. How to create a game

In `./lib/`, create a new directory with the name of your game module.<br>

### 3.1 Entry point

In this directory, create a `.cpp` file and implement the following functions:

```c++
extern "C" {
    IGameModule *entryPoint();
    Signature getSignature();
}
```

The `entryPoint` and `getSignature` functions work the same way as for the display module.<br>

### 3.2 Game module

Alongside those functions, you should implement the `IGameModule` interface. See [IGameModule](IGameModule.md) for more details.<br>

### 3.3 Makefile

Create a `Makefile` to compile your game module. See [Makefile](LibMakefile.md) for a template.<br>
Place your `Makefile` in the same directory as your `.cpp` file.

The library should be named `arcade_<name>.so` where `<name>` is the name of your game module.<br>

Finally, add your game module to the `./lib/Makefile` to compile it.

### 3.1 Game instructions

The game module can send instructions to the core of the program.<br>
To see the list of available instructions, see [Instruction](Instruction.md).

## 4. File structure

The structure of your library folder should look like this:
```
.
└── lib
    ├── Makefile
    └── arcade_<name>
        ├── Makefile
        ├── arcade_<name>.cpp
        └── src
            └── <...>.cpp
```

## 5. Commit message conventions

We use the following conventions for commit messages:<br>
`<type>(<scope>): <subject>`

### 5.1 Type
- `feat`: A new feature
- `fix`: A bug fix
- `hotfix`: A hotfix
- `docs`: Documentation only changes
- `refacto`: A code refactoring
- `style`: Change the code style
- `test`: Adding tests
- `wip`: Work in progress
