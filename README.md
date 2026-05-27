_This project has been created as part of the 42 curriculum by gfuster, aiguerre_

# 💬 **Description**

This project is inspired by the world-famous Wolfenstein 3D game. The goal of the project is to create a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective. We have to create this representation using ray-casting principles.

It must manage window rendering, colors, events (such as minimizing or switching windows seamlessly), and texture mapping. The program reads a scene description file with a `.cub` extension containing the map and asset configurations.

Overall, the project recreates how old 3D games work by calculating where vision lines hit walls (early FPS engines) by calculating ray intersections and projecting walls dynamically onto a 2D screen window.

# 📝 **Instructions**
First of all, you must do make in the teminal inside the directory. Once that is done, you must write:

```
git clone
make
./cub3D maps/map.cub
```

From now on you will be inside the cub3D game window. To interact with the environment, you can use the following control implementations:

* **W, A, S, D** keys to move the point of view through the maze.
* **Left and Right arrow** keys to move the point of view rotation.

There are two options will ensure the window closes and the program exits cleanly:
pressing the ESC key or licking on the cross on the window's frame

# 🔎 **Resources**
- [Subject](https://cdn.intra.42.fr/pdf/pdf/199705/en.subject.pdf)
- [Wolfenstein 3D game](http://users.atw.hu/wolf3d/)
- [Lodev's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Seno, coseno y tangente](https://www.disfrutalasmatematicas.com/seno-coseno-tangente.html)
- [Physics - Raycasting](https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/1raycasting/Physics%20-%20Raycasting.pdf)
- [Cómo hacer un Raycaster (con DDA)](https://www.youtube.com/watch?v=IzimG4VuW0Q)
- [MiniLibX / MLX42 Documentation](https://github.com/codam-coding-college/MLX42)
- [Valgrind manual](https://valgrind.org/docs/manual/manual-core.html)
- [Github basic writing and formatting syntax](https://docs.github.com/es/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)

## How AI was used:
AI was used as a tool to understand some complex new concepts such as parsing data architectures, math-driven algorithms like DDA vs Naive raycasting, and project structuring. We have used it to ask and understand from the provided documentation and asking for examples to understand it better. Besides to argue which structure was better and why.

# 🧠 **Technical decisions**

How do we realized the project?
Since we read the `.cub` file, we start the parsing part. It basically consists of analyzing data strings to fetch configurations and the map layout. Our structure is split into **4 main decoupled phases** following an approach similar to the MVC (Model-View-Controller) pattern:

1. **Parsing & Validation:** Reads scene elements (textures paths, RGB colors) and checks map validity. We implemented a **FAIL FAST** approach to trigger validation errors as early as possible during data processing.

2. **Library Implementation:** Handling the MLX window system, managing hooks, images, and smooth execution loops.

3. **Mathematical Logic (Raycasting):** Running the algorithmic rendering calculations.

4. **Error Management:** Centralized system to ensure clean exits with customized explicit error messages on failure.

### Memory Architecture: Anchor on Stack, Data on Heap
We chose a structure called "Anchor on Stack, Data on Heap". This means our main box of variables stays safely in the program's quick memory (Stack), while large data like the map grid or texture paths are stored in the flexible memory (Heap).

This architecture keeps the project safe, organized, and easy to read by preventing unexpected crashes such as Segfaults, ensuring a clean memory cleanup with a single function call, and providing quick, legible access to all map and path data

### Algorithmic Strategy: DDA
For rendering intersections, we implemented the **DDA (Digital Differential Analysis)** algorithm to map ray impacts precisely on grid boundaries, maximizing stability and performance.
