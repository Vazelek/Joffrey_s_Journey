# Debian
FROM debian:latest

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && apt-get install -y \
    qtbase5-dev \
    qtchooser \
    qt5-qmake \
    qtbase5-dev-tools \
    qtmultimedia5-dev \
    libqt5multimedia5-plugins \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /usr/src/app

# Copy the project files into the container
COPY . .

# Run qmake and make to build the application
RUN qmake Joffrey_s_Journey.pro && make

# Specify the command to run the application
CMD ["./Joffrey_s_Journey.exe"]
