# 3D Maze

This is my graphics project written in **C** for **Linux (Ubuntu)**.  
It renders a **3D view of a maze** and allows **real-time navigation from a first-person perspective**.

I implemented the **ray-casting algorithm from scratch**, and the rendering is handled using the **MiniLibX** library.


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