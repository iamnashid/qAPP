# qAPP

[![Code Grade](https://www.code-inspector.com/project/15241/status/svg)](https://frontend.code-inspector.com/public/project/15241/qAPP/dashboard)
![Code Score](https://www.code-inspector.com/project/15241/score/svg)

بِسْمِ ٱللّٰهِ الرَّحْمٰنِ الرَّحِيْمِ ,
السَّلاَمُ عَلَيْكُمْ وَرَحْمَةُ اللهِ وَبَرَكَاتُهُ

qAPP is an easy to use quran reader with support for translation in multiple languages . Made with Qt5 .

Inspired by the Discord IslamBot Project (https://github.com/galacticwarrior9/IslamBot)

**Screenshots**

![Screenshot 1](https://user-images.githubusercontent.com/72482273/97117939-06cd0a00-172d-11eb-96d8-d80272441425.png)
![Screenshot 2](https://user-images.githubusercontent.com/72482273/97117993-73e09f80-172d-11eb-8c83-33f6d86ec2a3.png)

**Dependencies**

`libcurl4-openssl-dev , qt5-default, nlohmann json`
* libcurl installation = `sudo apt install libcurl4-openssl-dev`
* nlohmann json = https://github.com/nlohmann/json , Download the latest release and put it in the source folder . Make sure header name is json.hpp
* Qt5 = `sudo apt install qt5-default`

**Installation**

*  Install Dependencies and follow the below steps
1. clone the repo and cd to repo folder
2. qmake
3. run `make` , it will compile the program
4. run the program `./qAPP --h`

*Note: If you get GTK-Warning failed to load canberra-gtk-module , fix it by*
`sudo apt install libcanberra-gtk-module`
