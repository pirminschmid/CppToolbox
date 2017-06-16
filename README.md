CppToolbox
==========
[![Build Status](https://travis-ci.org/pirminschmid/CppToolbox.svg?branch=master)](https://travis-ci.org/pirminschmid/CppToolbox)

A collection of various C++ helper classes. They are written for C++14. Cmake is used for compilation.
The code has been tested on macOS (Xcode Clang 8.1) and Linux (Fedora, gcc 6.3).
See the documentation of each class for additional information.

- [FileSystemHelper][filesystemhelper]: A few helper functions for using the filesystem.

- [LinkedMap][linkedmap]: An implementation of a std::unordered_map, additionally keeping insertion/refresh order.

- [LuaWrapper][luawrapper]: A simple C++ wrapper class for the [Lua][lua] interpreter.

- [SimpleTextTemplate][simpletexttemplate]: A simple text templating engine.

- [StatisticsHelper][statisticshelper]: This class provides some basic descriptive statistics functions.

Current version April/May 2017.  [Feedback][feedback] welcome.


License
-------

Copyright (c) 2017 Pirmin Schmid, [MIT license][license].

[filesystemhelper]:FileSystemHelper
[linkedmap]:LinkedMap
[luawrapper]:LuaWrapper
[simpletexttemplate]:SimpleTextTemplate
[statisticshelper]:StatisticsHelper
[lua]:https://www.lua.org
[license]:LICENSE
[feedback]:mailto:mailbox@pirmin-schmid.ch?subject=CppToolbox
