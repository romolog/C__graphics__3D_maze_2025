# 3D Maze

That is my graphic project written in **C** for **Linux (Ubuntu)**.<br/>
It renders a 3D view of a maze and allows real-time navigation from a first-person perspective.

I implemented from scratch ray-casting algorithms. The resulting rendering I made using **MiniLibX** library.

---

### Controls

<pre>
W       Move forward
S       Move backward
A       Move left
D       Move right
← / →   Turn left / right
</pre>

---

### System Requirements

- Linux (Ubuntu)
- gcc
- make
- X11
- XShm
- libbsd-dev

You may install required dependencies with: 
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev;
```
---

### Build

```bash
git clone https://github.com/romolog/C__graphics__3D_maze_2025 3D_maze;
cd 3D_maze;
```
---

### Run 
```bash
./cub3D ./maps/valid/regular_1.cub;
```