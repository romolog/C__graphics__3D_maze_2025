# 3D Maze

That is a graphic project written in C language for Linux (Ubuntu) - first person view going through a maze.
Graphic library used is MiniLibX (https://github.com/42paris/minilibx-linux).
<br>
- W - forward
- S - backward
- A - left
- D - right
- arrow-left - turn left
- arrow-right - turn right

### Deployment prerequisits

- Linux (Ubuntu)
- gcc
- make
- X11
- XShm
- libbsd-dev

To install necessary packages to Ubuntu run: 
<br>&emsp;&emsp;$ sudo apt-get install gcc make xorg libxext-dev libbsd-dev

### Build and Launch

- copy repo 
- in Shell go to the folder and run:
<br>&emsp;&emsp;$ make
- launch: 
<br>&emsp;&emsp;$ ./cub3D ./maps/valid/regular_1.cub


