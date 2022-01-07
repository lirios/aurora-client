Aurora Client
=============

[![License](https://img.shields.io/badge/license-GPLv3.0-blue.svg)](http://www.gnu.org/licenses/gpl.txt)
[![GitHub release](https://img.shields.io/github/release/lirios/aurora-client.svg)](https://github.com/lirios/aurora-client)
[![GitHub issues](https://img.shields.io/github/issues/lirios/aurora-client.svg)](https://github.com/lirios/aurora-client/issues)
[![CI](https://github.com/lirios/aurora-client/workflows/CI/badge.svg?branch=develop)](https://github.com/lirios/aurora-client/actions?query=workflow%3ACI)

Qt-style API to interact with Wayland protocols inside Qt-based graphical applications.

## Dependencies

Qt >= 5.15.0 with at least the following modules is required:

 * [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
 * [qtwayland](http://code.qt.io/cgit/qt/qtwayland.git)

The following modules and their dependencies are required:

 * [cmake](https://gitlab.kitware.com/cmake/cmake) >= 3.10.0
 * [cmake-shared](https://github.com/lirios/cmake-shared.git) >= 2.0.0
 * [wayland-protocols](https://gitlab.freedesktop.org/wayland/wayland-protocols) >= 1.15

Build-time only dependencies:

 * [aurora-scanner](https://github.com/lirios/aurora-scanner.git) >= 0.0.0

Optional dependencies:

 * [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)

## Installation

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/path/to/prefix ..
make
make install # use sudo if necessary
```

Replace `/path/to/prefix` to your installation prefix.
Default is `/usr/local`.

## Logging categories

Qt 5.2 introduced logging categories and we take advantage of
them to make debugging easier.

Please refer to the [Qt](http://doc.qt.io/qt-5/qloggingcategory.html) documentation
to learn how to enable them.

Available categories:

  * **aurora.client.wlrforeigntoplevelmanagementv1:** Foreign toplevel management client extension.
  * **aurora.client.wlrlayershellv1:** Layer shell client extension.
  * **aurora.client.wlrscreencopyv1:** Screencopy client extension.
  * **aurora.client.lirishellv1:** Shell client extension.

## Licensing

Licensed under the terms of the GNU General Public License version 3 or,
at your option, any later version.
