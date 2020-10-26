# qAPP

[![Code Grade](https://www.code-inspector.com/project/15241/status/svg)](https://frontend.code-inspector.com/public/project/15241/qAPP/dashboard)
![Code Score](https://www.code-inspector.com/project/15241/score/svg)

بِسْمِ ٱللّٰهِ الرَّحْمٰنِ الرَّحِيْمِ ,
السَّلاَمُ عَلَيْكُمْ وَرَحْمَةُ اللهِ وَبَرَكَاتُهُ

qAPP is an easy to use quran reader with support for translation in multiple languages . Made with Qt5 .

Inspired by the Discord IslamBot Project (https://github.com/galacticwarrior9/IslamBot)

**Screenshots**

![screen1](https://user-images.githubusercontent.com/72482273/97190495-cb354d00-17cb-11eb-8f43-0bb2ef8449ea.jpg)
![screen2](https://user-images.githubusercontent.com/72482273/97190478-c2447b80-17cb-11eb-87f0-911867f12269.png)
![screen3](https://user-images.githubusercontent.com/72482273/97190483-c4a6d580-17cb-11eb-9e87-0f9339a038d5.png)
![screen4](https://user-images.githubusercontent.com/72482273/97191211-a68da500-17cc-11eb-8792-93aadd174fab.png)

**Dependencies**

`libcurl4-openssl-dev , qt5-default, nlohmann json`
* libcurl installation = `sudo apt install libcurl4-openssl-dev`
* nlohmann json = https://github.com/nlohmann/json/releases , Download the latest release and put it in the source folder . Make sure header name is json.hpp
* Qt5 = `sudo apt install qt5-default`

**Installation**

*You can grab binary package from releases page*

1. Install Dependencies
2. clone the repo and cd to repo folder
3. qmake
4. run `make` , it will compile the program
5. run the program `./qapp --h`

*Note: If you get GTK-Warning failed to load canberra-gtk-module , fix it by*
`sudo apt install libcanberra-gtk-module`
