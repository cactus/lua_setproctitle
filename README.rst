===============
luasetproctitle
===============

.. contents::

Requirements
------------

Build requirements:

- gcc
- cmake
- linux >= 2.6.11
- lua (or luajit)

Run requirements:

- lua (or luajit)


Building
--------

There are a few build options, and their defaults, that you can specify:

- **CMAKE_INSTALL_PREFIX** = ``/usr/local``

  | The target prefix that make install will install to.
  | This is what you would expect from ``./configure --prefix=foo``

- **CMAKE_BUILD_TYPE** = ``Release``

  | Specifies the build type for make based generators.
  | Possible values: Debug, Release, MinSizeRel

An example of the build steps::

    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
    $ make


Installing
----------

After building, while in the build directory::

    $ make install


Usage
-----

::

    #!/usr/bin/env lua
    s = require "setproctitle"
    print(s.getproctitle())
    s.setproctitle('bill')
    print(s.getproctitle())


License
-------

Free use of this software is granted under the terms of the MIT (X11) License.
See LICENSE file for more information.
