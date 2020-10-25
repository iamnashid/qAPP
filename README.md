# qAPP

An easy to use quran reader made with Qt4

**Dependencies**

`libcurl4-openssl-dev , qt4-dev-tools, nlohmann json`
* libcurl installation = `sudo apt install libcurl4-openssl-dev`
* nlohmann json = https://github.com/nlohmann/json
* Qt4 = `sudo add-apt-repository ppa:rock-core/qt4` (Ubuntu 20.04 LTS)

**Installation**

1. clone the repo and cd to repo folder
2. qmake -project && qmake
3. open Makefile in a text editor and add `-lcurl` at the end of `LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread` line .
4. After edit the line will be : `LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread -lcurl`
5. `make` , it will compile the program
6. run the program `./qAPP --h`

*Note: If you get GTK-Warning failed to load canberra-gtk-module , fix it by*
`sudo apt install libcanberra-gtk-module`
