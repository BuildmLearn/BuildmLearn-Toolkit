#Installation

##Linux:

This project depends on Qt 4.8.You should get and install Qt 4.8. 
You can get compiled binaries and source 
code from [qt-project website](http://qt-project.org/downloads).

This gets repo and build the GUI

```bash
git clone https://github.com/BuildmLearn/BuildmLearn-Toolkit.git
cd buildmlearn-toolkit-src 
mkdir build && cd build
qmake -Wall ../BuildmLearn-Toolkit.pro
make
```

On success, this will build a `TFT` executable.

Also, using make with `-jN` parameter, where `N` is a number of cores your 
processor has + 1, should decrease build time greatly. For example, if your 
machine is dual core, use `make -j3`.

If you want to build the GUI by using Qt Creator, rather than terminal commands,
follow the Windows guide starting at "Then open the Qt Creator...".
