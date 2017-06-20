LuaWrapper
==========

A simple C++ wrapper class for the [Lua][lua] interpreter. This allows an easy configuration of the C++ application, including quite complex modifications of the runtime functionality. Calls from C++ to Lua code, and callbacks from Lua to hosting C++ code are implemented. Additional improvements are planned, as well as optional use of the [LuaJIT][luajit] compiler.

Current version v1.0 (2017-05-01).  [Feedback][feedback] welcome.


Dependencies
------------

- Needs ```readline``` and ```readline-devel``` packages installed on Linux 

- Lua is installed automatically with the ```./install_lua.sh``` script


Usage
-----

The wrapper class is embedded in the SampleProject, folder toolbox: [link][link].

1) Installation of Lua source code: ```./install_lua.sh``` (*)

2) Building of the sample project: ```./compile.sh``` (*)

3) Run sample program: ```./run_sample_program.sh```

(*) add argument ```mac``` for compilation on MacOS instead of Linux.


License
-------

Copyright (c) 2017 Pirmin Schmid, [MIT license][license].

[lua]:https://www.lua.org
[luajit]:http://luajit.org
[link]:https://github.com/pirminschmid/CppToolbox/tree/master/LuaWrapper/src/SampleProject/toolbox
[license]:LICENSE
[feedback]:mailto:mailbox@pirmin-schmid.ch?subject=LuaWrapper
