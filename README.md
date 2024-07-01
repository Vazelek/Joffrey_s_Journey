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

Compile
```sh
cd Joffrey_s_Journey
qmake
make
```

Execute
```sh
./Joffrey_s_Journey.exe
```

### Centos
Intal packages
```sh
sudo yum install qt5-qtbase-devel qt5-qtmultimedia-devel
```

Compile
```sh
cd Joffrey_s_Journey
qmake-qt5
make
```

Execute
```sh
./Joffrey_s_Journey.exe
```

## Containerize

### On windows

#### Requirements

- Docker Desktop intalled (https://www.docker.com/products/docker-desktop/) 
- MobaXterm installed (https://mobaxterm.mobatek.net/)

#### Build the image

- Start the Docker Desktop app so that the docker deamon is running
- Open the cmd

```sh
docker build -t joffrey_journey_app .
```

#### Run the container

- Start MobaXterm and ensure the X server is running (for GUI display)
- Find your host's IP address with `ipconfig`

```sh
ipconfig
```
- Run the docker container

```sh
docker run -it --rm -e DISPLAY=<WINDOWS_HOST_IP>:0.0 -v /tmp/.X11-unix:/tmp/.X11-unix joffrey_journey_app
```
Replace `<WINDOWS_HOST_IP>` by your local IPv4 address