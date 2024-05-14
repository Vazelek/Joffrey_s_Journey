# Joffrey's Journey
2d platformer game made for a school project using Qt C++

![image](https://github.com/Vazelek/Joffrey_s_Journey/assets/84991031/0f976cf8-3b19-4066-b992-02d8b8c022e1)

## Overview
Join botanist Joffrey on an adventure in search of the world's rarest flower. The road to finding it is not without its dangers. Can you overcome all the obstacles that will stand in your way?

## Setup
### Debian
Install packages
```sh
sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools qtmultimedia5-dev libqt5multimedia5-plugins -y
```

Compiling
```sh
cd Joffrey_s_Journey
qmake
make
```

Execute
```sh
./build/Joffrey_s_Journey
```

### Centos
Intal packages
```sh
sudo yum install qt5-qtbase-devel qt5-qtmultimedia-devel
```

Compiling
```sh
cd Joffrey_s_Journey
qmake-qt5
make
```

Execute
```sh
./build/Joffrey_s_Journey
```

