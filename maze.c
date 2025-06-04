/*
============================================================
  Fichero: laberinto.c
  Creado: 02-06-2025
  Ultima Modificacion: dimecres, 4 de juny de 2025, 07:40:50
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "maze.h"

static Maze maze;
static u2 wmaze=0;
static u2 hmaze=0;
static u4 dmaze=0;

typedef struct {
	u2 size;
	u4 start;
	u1* direction;
} Way;

#define PMA(X,Y) ((X)+(Y)*wmaze)
#define RND(A,B) ((A)+(rand()%((B)-(A)+1)))
#define XFP(P) ((P)%wmaze)
#define YFP(P) ((P)/wmaze)
#define ABS(A) (((A)>0)?(A):(-(A)))

static u1 mazeinit(u2 w,u2 h) {
	//inicia el laberinto y todas sus variables asociadas
	u4 d=w*h;
	maze=malloc(sizeof(u1)*d);
	if(maze) {
		wmaze=w;
		hmaze=h;
		dmaze=d;
		u1* ptr=maze;
		while(ptr!=maze+d) *ptr++=0;
		return 1;
	}
	return 0;
}

static u4 smaze(u4* e,u4* f) {
	//separa el laberinto ocupado del laberinto vacio, devuelve el numero de piezas vacias
	u1* ptr=maze;
	u4 de=0;
	u4 df=0;
	while(ptr!=maze+dmaze) {
		u4 pos=ptr-maze;
		if(*ptr) f[df++]=pos;
		else e[de++]=pos;
		ptr++;
	}
	return de;
}

static u4 rroom(u4 dim,u4* submaze) {
	//de un submaze saca una habitacion al azar (necesario que la dimension sea superior a 1)
	if(dim) return submaze[RND(0,dim-1)];
	return 0;
}

static u4 posdes(u4 actual,u1 dir) {
	//a partir de una posicion y una direccion se da la posicion final
	switch(dir) {
		case NORTH:
			return actual-wmaze;
		case SOUTH:
			return actual+wmaze;
		case EAST:
			return actual+1;
		case WEST:
			return actual-1;
		default:
			return actual;
	}
}

static u1 _waystp(u4* actual,u2 xf,u2 yf) {
	u1 dir=0;
	if(maze[*actual]==0) {
		u1 xa=XFP(*actual);
		u1 ya=YFP(*actual);
		if(xf>xa) dir=EAST;
		else if(xf<xa) dir=WEST;
		if(dir==0 || RND(0,1)==1) {
			if(yf>ya) dir=SOUTH;
			else if(yf<ya) dir=NORTH;
		}
	}
	return dir;
}

static Way waynew(u4 posi,u4 posf) {
	//creacion de un camino entre dos posiciones
	Way w={0,0,NULL};
	u2 xi=XFP(posi);
	u2 yi=YFP(posi);
	u2 xf=XFP(posf);
	u2 yf=YFP(posf);
	u4 dim=ABS(xi-xf)+ABS(yi-yf);
	u1* ptr=malloc(sizeof(u1)*dim);
	if(ptr) {
		w.direction=ptr;
		w.start=posi;
		u4 actual=posi;
		u1 dir=0;
		while((dir=_waystp(&actual,xf,yf))) {
			w.direction[w.size++]=dir;
			actual=posdes(actual,dir);
		}
	}
	return w;
}

static void waydel(Way* w) {
	//liberamos espacio del camino
	if(w) {
		free(w->direction);
		w->size=w->start=0;
	}
}

static void waytomaze(Way way) {
	//ponemos el camino en el interior del laberinto
	u4 actual=way.start;
	u1* dir=way.direction;
	while(dir!=way.direction+way.size) {
		u4 destiny=posdes(actual,*dir);
		maze[actual]|=*dir;
		maze[destiny]|=(8/(*dir));
		actual=destiny;
		dir++;
	}
}

static u1 mazeoneway(u4* smf,u4* smo) {
	//crea un camino para el maze (init quiere decir el camino inicio)
	u4 ssmf,ssmo;
	ssmf=smaze(smf,smo);
	ssmo=dmaze-ssmf;
	if(ssmf) {
		u4 init=rroom(ssmf,smf);
		u4 destiny=init;
		if(ssmo==0) {
			while(destiny==init) destiny=rroom(ssmf,smf);
		} else {
			destiny=rroom(ssmo,smo);
		}
		Way w=waynew(init,destiny);
		waytomaze(w);
		waydel(&w);
		return 1;
	}
	return 0;
}

Maze mazenew(u2 w,u2 h) {
	if(mazeinit(w,h)) {
		u4* smf=malloc(sizeof(u4)*dmaze);
		u4* smo=malloc(sizeof(u4)*dmaze);
		if(smf && smo) {
			while(mazeoneway(smf,smo));
		} else {
			free(maze);
			maze=NULL;
		}
		free(smf);
		free(smo);
	}
	return maze;
}

u1 mazeget(Maze m,u1 x,u1 y) {
	if(maze) return maze[PMA(x,y)];
	return 0;
}

void mazedel(Maze* m) {
	if(m) {
		free(*m);
		*m=NULL;
	}
}
	

		



