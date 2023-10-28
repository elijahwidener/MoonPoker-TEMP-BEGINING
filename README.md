#This repository is no longer active, and has been moved to the MoonPoker organization to be worked in private amoungst team members.
![banner](https://gitmsplib.github.io/MP/banner.png)

# MoonPoker: Online Home Games

## Table of Contents

1. [Introduction](#Introduction)
    - [Features](#Features)
    - [Technologies Used](#Technologies-Used)
2. [Contribution Guide](#Contribution-Guide)
    - [Getting Started](#Getting-Started)
    - [Project Structure](#Project-Structure)
    - [Development Flow](#Development-Flow)
3. [Code Style Guide](#code-style-guide)
    - [C++ Style Guide](#c-style-guide)
    - [CMake Style Guide](#cmake-style-guide)
    - [Other](#other-style-guides)


## Introduction

Welcome to MoonPoker, an online web app that lets you play poker in your browser with your friends.
MoonPoker allows users to customize their tables, offering the ability to play mixed games and add unique table modifications like bounties or bomb pots.
Looking ahead, we plan to introduce advanced analytics that will enable you to compare your gameplay to GTO standards.
Engineered for reliability and designed for an intuitive user experience, MoonPoker aims to set a new standard in online poker games.

### Features

- **Multi-Game Support**: Play Stud, Draw, and Community Card Variants of Poker.
- **Game-Modifications**: Play variants Hi-Lo, as well as add bounties and bomb pots to the table rules.
- **User Profiles**: Create and customize your own profile.
- **Premium Features**: From advanced statistics to enhanced customization, unlock an array of premium features to elevate your game.
- **Responsive Design**: Built with Flutter, our UI is fully optimized for both web and mobile.
- **Future Enhancement/Spitballing**: Handle banking using Venmo API, host public tables, ability to create clubs, allow game host to add rake, allow players to "Tip the dealer" which host can claim.


### Technologies Used

- **Frontend**: Flutter
- **Backend**: C++
- **Database**: ?
- **Other**: Google Test, Google Protobuf [Any other technologies, APIs, or frameworks]


## Contribution Guide

### Getting Started

To get started with developing this project, all that is currently needed is to clone this repository using:

```sh
git clone git@github.com:gitmsplib/Moon-Poker.git
```

### Project Structure

The project consists of two portions: the server back-end, and the gui frontend client.
The project will entirely be managed by CMake build automation for consistency.
Language/Framework-specific build systems should be wrapped in CMake for automation.

### Development Flow

Since the project is currently under active development, it will follow the classic github-flow branching policy.
Once the project matures past alpha `v0.x.x` stage, then it may transition to a more structured gitflow branching policy.
More on branching policies can be seen [here](https://medium.com/@patrickporto/4-branching-workflows-for-git-30d0aaee7bf).

Issues and tasks will be tracked using the GitHub issues system.
The typical flow will revolve around creating and resolving issues in a scrum-like fashion.
Issues will be categorized into four work categories by using labels:

- Epic: Top-level issue in a hierarchy, is an aggregate of stories that defines a base project requirement.
- Story: An issue representing a unique feature at a high level that satisfies some requirement.
- Task: Free-standing issue to break down stories into technically actionable items.
- Subtask: A support issue to break down a task into smaller bits that may have to be developed sequentially.

The typical individual development flow will be to assess a group-created story, and break it down into smaller tasks. 
Each task should then have an issue created and assigned to a developer, and can be worked on in parallel to others.

Because we are using the github flow policy, all development should be done in feature branches, and then merged into the main branch when ready.
In greater detail, the flow should be as follows:

1. Create a `level: task` issue with a descriptive header and in-depth description of the problem to be solved.
2. Create a feature branch off of the main branch with the name `feature/T<issue-number>`.
    - It may be handy to have a different _local_ branch name for this feature.
    If it is so desired, then in order to push changes to the correctly named upstream branch, do the following:
        ```sh
        git checkout -b <local_name> # create a new local branch
        ... # commit any changes that need to be done
        git push --set-upstream origin <local_name>:feature/T<issue_number>
        ```
    - Link the issue to the newly-created feature branch using the `Development` section on the issue page.
3. Commit changes to the feature branch, and push to remote.
4. When ready, create a pull request to merge the feature branch into the main branch.
    - Name the pull request with the same name as the issue. In the description, copy the issue description/motivation, and also summarize all of the changes done by the commits in the pull request.
    - This message will be used as the commit message for the merge commit, so make sure it is useful.
5. Add reviewers and request a review.
6. Once approved, create a **SQUASH** merge into main.
    - This is important to keep the commit history clean and readable, as we are using a linear commit history on main. PR's will retain the history of the merged and deleted branches, so nothing is lost by doing this, and the history becomes cleaner and smaller.
7. You are done! If you did everything correct, the issue should be automatically closed by the merge commit.

If an issue is reopened sometime in the future, a fix should be done in a new feature branch, and then merged into main using the same process, with perhaps a different PR description.

## Code Style Guide

### C++ Style Guide

The style is based on the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html), and should be adhered to as a general rule of thumb, but not overly stressed.
Some key differences in style are noted below, and supersede the Google guide.
Other deviations from the style guide are permissible, but should be done sparingly and in good taste.

#### Formatting

All checked-in files should be formatted by the root `.clang-format` file, which is  based on the [Mozilla style guide](https://firefox-source-docs.mozilla.org/code-quality/coding-style/coding_style_cpp.html) due to its consistent use of indentation.

In addition, here are some other guidelines:

##### Class Format

A typical class should follow the `public`, `protected`, `private` order that [Google prescribes](https://google.github.io/styleguide/cppguide.html#Class_Format), but in addition, may include implicitly private helper type declarations before the first `public` section.

Within each section follow a similar [class declaration order](https://google.github.io/styleguide/cppguide.html#Class_Format) that is specified by the guide with the following elaborations:

1. Types and type aliases.
2. Friend function declarations.
3. Static constants.
4. Static functions.
5. Factory functions.
6. Constructors (not copy/move).
7. Destructor.
8. Copy/move constructors + operators.
9. General member functions.
10. Accessor / mutator inline functions.
11. Static/instance data members.

#### Naming

Naming conventions should mirror those of the [Google guide](https://google.github.io/styleguide/cppguide.html#Naming) with the following exceptions:

##### Filenames

- Should only use underscores (_) as word delimiters.
- C++ headers should always end in `.hpp` to distinguish them from regular C headers.
  - It should be an error to include a `.hpp` file from C.
  - If a C file optionally (`#ifdef __cplusplus`) includes a C++ interface, then it is acceptable to use `.h` extension.
- C++ files should always use `.cpp` extension.

##### Function Names

All functions/methods should be named using _**lowerCamelCase**_.
Short accessor/mutator functions are encouraged to have single-word lowercase names, but are not exempt from this rule.
For example: `int count()` and `void setCount(int)`.

##### Global Names

While global non-const variables are bad, there may be a need for some.
The Google guide says nothing about non-const [global variable naming](https://google.github.io/styleguide/cppguide.html#Constant_Names).

As such, global variables shall be named similar to constants (`kConstant`), but with a preceding "g" (`gGlobalVar`).

#### Includes

As opposed to the [Google guide](https://google.github.io/styleguide/cppguide.html#Names_and_Order_of_Includes), the general include order should be the following, with blank lines delimiting each section:

- Related header.
- C Standard Library headers (\<cstddef\>).
- C++ Standard Library headers (\<vector>).
- C system headers (\<unistd.h>).
- Other library headers.
- Local project headers ("foo.h").

Includes should be sorted in case-sensitive order (clang-format should handle that).

#### Comments

Refer to [Google guide](https://google.github.io/styleguide/cppguide.html#Comments) for best practices.

Always avoid `/* */` C-style comments, and always prefer to use `//` comments for block and inline comments.

##### Doxygen

The project uses [Doxygen](https://www.doxygen.nl/manual/docblocks.html) for documentation generation.
Javadoc and Qt style comments are disallowed - use `///` for all doxygen block comments for functions and classes.

Document entities at their declaration - out of line documentation blocks are discouraged.

Do not use large block comments such as these:

```cpp
/********************************************//**
 *  ... text
 ***********************************************/
```

All [special commands](https://www.doxygen.nl/manual/commands.html) should be prefixed with a backslash (`\tag`) as opposed to the @ symbol (`@tag`).

Require `\brief` for all doxygen block comments.

##### File Comments

Every file should begin with the following header:

```cpp
/// \file <filename>
///
/// \brief <file description>
```

where \<filename> is the full path of the file with respect to the source root.

#### Language Features

The project targets C++20, and may anticipate a switch to a newer version, ideally without sacrificing backwards-compatibility.
C++ is a very powerful language, and as such, it should be utilized in full to reduce the amount of manual work required.

##### Filesystem Standard Library

Use of the `<filesystem>` header is currently permitted (while it is [expressly disallowed](https://google.github.io/styleguide/cppguide.html#Other_Features) by Google) in order to speed up initial development.

This may be reevaluated in the future if necessary/possible.

##### Exceptions

Exceptions _**are used**_ in this codebase.

Exceptions are commonly frowned-upon for a variety reasons, but the cons listed in the [Google style guide](https://google.github.io/styleguide/cppguide.html#Exceptions) are among the most reasonable.
The majority of the cons listed, however, deal with dependency management and integration into existing systems, which are rightfully problematic issues.
This project, however, is a standalone application, and does not have the issue of having to deal with legacy code.

The pros listed by Google outweigh the cons, and as such, exceptions are allowed to be used.
Using exceptions liberally is highly discouraged, as there are much better alternatives in normal control flow.
Exceptions should be the last line of error propagation, for example when routine error checking returns a non-recoverable error from the current scope that has to propagate far up the stack.

Regardless, exceptions and other error checking should be used robustly, and adhere to well-though out design.
Refer to the [C++ core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e-error-handling) for more ideas on what that may mean.

##### New Language Features

While the project targets C++20, since most major compilers already fully support it (and more will likely come), prefer to avoid new language features unless they make code substantially clearer/more effective.

Examples:

###### Constraints and Concepts

While C++20 concepts and constraints can make complex template matching more concise, it should first be evaluated if the template metaprogramming [is necessary](https://google.github.io/styleguide/cppguide.html#Template_metaprogramming) in the first place.
If it is, still consider using older techniques such as SFINAE if practical.

For example:

```cpp
template<class A, class B>
requires std::is_base_of_v<B, A>
B&
downcast(A& x) 
{
  return x;
}
```

is not substantially more readable than the older alternative:

```cpp
template<class A, class B>
std::enable_if_t<std::is_base_of_v<B, A>, B&>
downcast(A& x)
{
  return x;
}
```

but is much harder to refactor back into the older alternative if ever needed to be ported to an older compiler (for some reason).

###### Designated Initializers

Designated initializers are an example of a beneficial trade-off, since they significantly increase readability of code.

[Google encourages them](https://google.github.io/styleguide/cppguide.html#Designated_initializers), and they are free to be used without compatibility concerns.

##### Pragmas

Pragmas are disallowed with the exception of `#pragma once`, which is a virtually portable replacement for include guards, and `#pragma region`, which improves readability and navigability of code.

### CMake Style Guide

CMake is used to automate the often confusing and long build process.
As such, CMakeLists files should be as concise and readable as possible.

For formatting CMake files, use [cmake-format](https://github.com/cheshirekow/cmake_format), which offers [vscode integration](https://marketplace.visualstudio.com/items?itemName=cheshirekow.cmake-format), as well as standalone CLI.

For now, the default formatting style is used, which may change the with addition of a `.cmake-format` file in project root.

### Other Style Guides

Any C dialect (C, C#, Obj-C) and any other supported language should be formatted using the default C++ .clang-format file. (C/C++/Java/JavaScript/JSON/Objective-C/Protobuf/C#).

Other styling decisions are up for later decision.
