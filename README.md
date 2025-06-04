# maze
Crea un laberinto bidimensional de dimensiones w,h que son del tipo unsigned short.
Cada habitacion del laberinto contiene las salidas NORTH, SOUTH, EAST, WEST como bits de un byte.
Tipos disponibles:
  u1 = unsigned char
  u2 = unsigned short
  u4 = unsigned int
  Maze = u1*
Funciones disponibles:
Maze mazenew(u2 w,u2 h) -> Creacion de un laberinto de dimensiones w,h
u1 mazeget(Maze m,u2 x,u2 y) -> Consigue las caracteristicas (salidas) de una habitacion en posicion x,y. Si esta fuera de rango devuelve 0.
void mazedel(Maze* m) -> Libera el espacio del laberinto


