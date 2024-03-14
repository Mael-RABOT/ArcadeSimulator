# Documentation

This is the documentation for the arcade project.

## Table of Contents
### [1. Interfaces](#1-interfaces)
### [2. How to create a display](#2-how-to-create-a-display)
### [3. How to create a game](#3-how-to-create-a-game)
### [4. Commit message conventions](#4-commit-message-conventions)


## 1. Interfaces

The project is divided into 2 main interfaces:

- [IDisplayModule](IDisplayModule.md)
- [IGameModule](IGameModule.md)

These interfaces are used to create the graphical and game modules.<br>
They are used to create the dynamic libraries that will be loaded at runtime by the core of the program.

## 2. How to create a display

In `./lib/`, create a new directory with the name of your display module.<br>
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

Alongside those functions, you should implement the `IDisplayModule` interface. See [IDisplayModule](IDisplayModule.md) for more details.
Create a `Makefile` to compile your display module. See [Makefile](LibMakefile.md) for a template.

Finally, add your display module to the `./lib/Makefile` to compile it.

## 3. How to create a game

...

## 4. Commit message conventions

We use the following conventions for commit messages:<br>
`<type>(<scope>): <subject>`

### Type
- `feat`: A new feature
- `fix`: A bug fix
- `hotfix`: A hotfix
- `docs`: Documentation only changes
- `refacto`: A code refactoring
- `style`: Change the code style
- `test`: Adding tests
- `wip`: Work in progress
