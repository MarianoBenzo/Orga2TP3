/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "colors.h"
#include "defines.h"
#include "sched.h"

unsigned int screen_paginas_tareas[CANT_TAREAS][3];
coordenada ultimo_misil;
unsigned char modo = 0;         //0 = ninguno; 1 = modo mapa; 2 = modo estado

void pintar_buffer_bandera(unsigned int dir_buffer){
    unsigned int dir_video;
    int flag = current_flag();
    int it = 0;
    while (it < 2){
        if (modo != 2)
            it = 2;

        if (it == 1)
            dir_video = VIDEO_SCREEN;
        else
            dir_video = VIDEO_ESTADO;

        unsigned char *dst = (unsigned char*) dir_video;
        unsigned char *src = (unsigned char*) dir_buffer;
        unsigned char fila;
        unsigned char col;

        if (flag < 4)
            fila = 3;
        else
            fila = 10;

        if (flag == 0 || flag == 4)
            col = 2;
        else if (flag == 1 || flag == 5)
            col = 14;
        else if (flag == 2 || flag == 6)
            col = 26;
        else
            col = 38;

        dst += (fila * 160) + (col * 2);

        int i;
        int j = 0;
        for(i = 0; i < 100; i++){
            if (j == 20){
                fila++;
                dst = (unsigned char*) dir_video + (fila * 160) + (col * 2); // Salto a la proxima linea
                j = 0;
            }
            *(dst) = *(src);
            dst++;
            src++;
            j++;
        }

        it++;
    }
}

void borrar(int tarea){
    ca (*m)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_MAPA;
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    unsigned char nro_pag;
    //La borro del mapa
    int f;
    int c;
    for (nro_pag = 1; nro_pag < 4; nro_pag++){
        if (screen_paginas_tareas[tarea][nro_pag - 1] != 0){
            coordenada repetido;
            int tareaRepetida;
            int cantRepetidos = 0;
            for (f = 0; f < CANT_TAREAS; f++){
                for (c = 0; c < 3; c++){
                    if (f != tarea){
                        if (screen_paginas_tareas[f][c] == screen_paginas_tareas[tarea][nro_pag - 1]){
                            cantRepetidos++;
                            repetido = coordenadas(screen_paginas_tareas[f][c]);
                            tareaRepetida = f;
                        }
                    }
                }
            }
            //Si hay mas de una tarea mapeada ahi, la dejo
            coordenada coord_vieja = coordenadas(screen_paginas_tareas[tarea][nro_pag - 1]);
            if (cantRepetidos == 1){
                print_int(tareaRepetida + 1, repetido.col, repetido.fila, C_FG_WHITE + C_BG_BROWN, VIDEO_MAPA);
            }else if (cantRepetidos == 0){
                if (nro_pag == 3)
                    pintar(&(m[coord_vieja.fila][coord_vieja.col]), C_BG_GREEN, 0);
                else
                    pintar(&(m[coord_vieja.fila][coord_vieja.col]), C_BG_CYAN, 0);
            }
            if (modo == 1){
                if (cantRepetidos == 1){
                    print_int(tareaRepetida + 1, repetido.col, repetido.fila, C_FG_WHITE + C_BG_BROWN, VIDEO_SCREEN);
                }else if (cantRepetidos == 0){
                    if (nro_pag == 3)
                        pintar(&(p[coord_vieja.fila][coord_vieja.col]), C_BG_GREEN, 0);
                    else
                        pintar(&(p[coord_vieja.fila][coord_vieja.col]), C_BG_CYAN, 0);
                }
            }
            screen_paginas_tareas[tarea][nro_pag - 1] = 0;
        }
    }

    ca (*e)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_ESTADO;
    //Borro su bandera
    if (tarea < 4)
        f = 3;
    else
        f = 10;

    if (tarea == 0 || tarea == 4)
        c = 2;
    else if (tarea == 1 || tarea == 5)
        c = 14;
    else if (tarea == 2 || tarea == 6)
        c = 26;
    else
        c = 38;

    unsigned char fila;
    unsigned char col;
    for (fila = f; fila < f + 5; fila++){
        for (col = c; col < c + 10; col++){
            if (fila == f || fila == f + 4){
                if (col < c + 2 || col > c + 7)
                    pintar(&(e[fila][col]), C_BG_RED, 0);
                else
                    pintar(&(e[fila][col]), C_BG_BLACK, 0);
            }else if (fila == f + 1 || fila == f + 3){
                if ((col < c + 4 && col > c + 1) || (col < c + 8 && col > c + 5))
                    pintar(&(e[fila][col]), C_BG_RED, 0);
                else
                    pintar(&(e[fila][col]), C_BG_BLACK, 0);
			}else{
            	if (col < c + 6 && col > c + 3)
                    pintar(&(e[fila][col]), C_BG_RED, 0);
                else
                    pintar(&(e[fila][col]), C_BG_BLACK, 0);
            }
        }
    }
    if (modo == 2){
        for (fila = f; fila < f + 5; fila++){
            for (col = c; col < c + 10; col++){
                if (fila == f || fila == f + 4){
                    if (col < c + 2 || col > c + 7)
                        pintar(&(p[fila][col]), C_BG_RED, 0);
                    else
                        pintar(&(p[fila][col]), C_BG_BLACK, 0);
                }else if (fila == f + 1 || fila == f + 3){
                    if ((col < c + 4 && col > c + 1) || (col < c + 8 && col > c + 5))
                        pintar(&(p[fila][col]), C_BG_RED, 0);
                    else
                        pintar(&(p[fila][col]), C_BG_BLACK, 0);
                }else{
                    if (col < c + 6 && col > c + 3)
                        pintar(&(p[fila][col]), C_BG_RED, 0);
                    else
                        pintar(&(p[fila][col]), C_BG_BLACK, 0);
                }
            }
        }       
    }
}

void redirigir_misil(unsigned int dir){
    coordenada nuevo_misil = coordenadas(dir);
    ca (*m)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_MAPA;
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;

    pintar(&(m[nuevo_misil.fila][nuevo_misil.col]), C_BG_RED, 0);

    if (ultimo_misil.fila != 0)
        pintar(&(m[ultimo_misil.fila][ultimo_misil.col]), C_BG_CYAN, 0);

    if (modo == 1){
        pintar(&(p[nuevo_misil.fila][nuevo_misil.col]), C_BG_RED, 0);

        if (ultimo_misil.fila != 0)
            pintar(&(p[ultimo_misil.fila][ultimo_misil.col]), C_BG_CYAN, 0);       
    }

    ultimo_misil.fila = nuevo_misil.fila;
    ultimo_misil.col  = nuevo_misil.col;
}

void asignar_dir(unsigned int tarea, unsigned int dir, unsigned char nro_pag){
    // Rango tarea: [0;7]
    // Rango nro_pag: [1;3]

    //Actualizo la pantalla de estado
    unsigned char columna = 6 + (nro_pag - 1) * 14;
    unsigned char fila = 16 + tarea;
    print_hex(dir, 8, columna, fila, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO, 1);
    if (modo == 2)
        print_hex(dir, 8, columna, fila, C_FG_BLACK + C_BG_CYAN, VIDEO_SCREEN, 1);

    //Si ya estaba dibujada en el mapa, la borro
    ca (*m)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_MAPA;
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    if (screen_paginas_tareas[tarea][nro_pag - 1] != 0){
        coordenada coord_vieja = coordenadas(screen_paginas_tareas[tarea][nro_pag - 1]);
        int f;
        int c;
        coordenada repetido;
        int tareaRepetida;
        int cantRepetidos = 0;
        for (f = 0; f < CANT_TAREAS; f++){
        	for (c = 0; c < 3; c++){
        		if (f != tarea && c != (nro_pag - 1)){
        			if (screen_paginas_tareas[f][c] == screen_paginas_tareas[tarea][nro_pag - 1]){
        				cantRepetidos++;
        				repetido = coordenadas(screen_paginas_tareas[f][c]);
        				tareaRepetida = f;
        			}
        		}
        	}
        }
        //Si hay mas de una tarea mapeada ahi, la dejo
        if (cantRepetidos == 1){
        	print_int(tareaRepetida + 1, repetido.col, repetido.fila, C_FG_WHITE + C_BG_BROWN, VIDEO_MAPA);
        }else if (cantRepetidos == 0){
        	if (nro_pag == 3)
            	pintar(&(m[coord_vieja.fila][coord_vieja.col]), C_BG_GREEN, 0);
        	else
            	pintar(&(m[coord_vieja.fila][coord_vieja.col]), C_BG_CYAN, 0);
        }
        if (modo == 1){
            if (cantRepetidos == 1){
                print_int(tareaRepetida + 1, repetido.col, repetido.fila, C_FG_WHITE + C_BG_BROWN, VIDEO_SCREEN);
            }else if (cantRepetidos == 0){
                if (nro_pag == 3)
                    pintar(&(p[coord_vieja.fila][coord_vieja.col]), C_BG_GREEN, 0);
                else
                    pintar(&(p[coord_vieja.fila][coord_vieja.col]), C_BG_CYAN, 0);
            }
        }
    }

    //Dibujo en la nueva coordenada
    coordenada coord_nueva = coordenadas(dir);
    unsigned char x = coord_nueva.col;
    unsigned char y = coord_nueva.fila;
    
    if (m[y][x].c != 0){
        //Hay otra pagina mapeada en el mismo lugar!
        print("X", x, y, C_FG_WHITE + C_BG_MAGENTA, VIDEO_MAPA);
    } else{
        print_int(tarea + 1, x, y, C_FG_WHITE + C_BG_BROWN, VIDEO_MAPA);
    }
    if (modo == 1){
        if (p[y][x].c != 0){
            //Hay otra pagina mapeada en el mismo lugar!
            print("X", x, y, C_FG_WHITE + C_BG_MAGENTA, VIDEO_SCREEN);
        } else{
            print_int(tarea + 1, x, y, C_FG_WHITE + C_BG_BROWN, VIDEO_SCREEN);
        }
    }
    //Actualizo la matriz
    screen_paginas_tareas[tarea][nro_pag - 1] = dir;
}

void pintar_reloj_tarea(int tarea){
    int f = VIDEO_FILS - 1;
    int c_new = 4 + (tarea * 3);

    int navio = 1;
    int c;
    for (c = 4; c < 28; c += 3){
        print_int(navio, c, f, C_BG_LIGHT_GREY + C_FG_WHITE, VIDEO_SCREEN);
        print("*", c + 1, f, C_BG_LIGHT_GREY + C_FG_WHITE, VIDEO_SCREEN);
        navio++;
    }

    print_int(tarea + 1, c_new, f, C_FG_WHITE + C_BG_RED, VIDEO_SCREEN);
    print(" ", c_new + 1, f, C_BG_RED, VIDEO_SCREEN);
}

void pintar_reloj_bandera(int bandera){
    int f = VIDEO_FILS - 1;
    int c_new = 32 + (bandera * 3);

    int navio = 1;
    int c;
    for (c = 32; c < 56; c += 3){
        print_int(navio, c, f, C_BG_MAGENTA + C_FG_WHITE, VIDEO_SCREEN);
        print("*", c + 1, f, C_BG_MAGENTA + C_FG_WHITE, VIDEO_SCREEN);
        navio++;
    }

    if (bandera < CANT_TAREAS){
    	print_int(bandera + 1, c_new, f, C_FG_WHITE + C_BG_RED, VIDEO_SCREEN);
    	print(" ", c_new + 1, f, C_BG_RED, VIDEO_SCREEN);
    }
}

coordenada coordenadas(unsigned int dir){
    coordenada coord;
    coord.fila = ((dir / 0x1000) / 80);
    coord.col = ((dir / 0x1000) % 80);
    return coord;
}

unsigned char modo_pantalla(){
    return modo;
}

void pintar(ca* p, unsigned char a, unsigned char c)
{
	p->a = a;
	p->c = c;
}

void limpiar_pantalla()
{
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int f;
    for (f = 0; f < VIDEO_FILS; f++)
    {
        int c;
        for (c = 0; c < VIDEO_COLS; c++)
            pintar(&(p[f][c]), 0, 0);
    }    
}

void screen_pintar_pantalla()
{
	ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
	int f;
	for (f = 0; f < VIDEO_FILS; f++)
	{
		int c;
		for (c = 0; c < VIDEO_COLS; c++)
		{
			if (f == 0 || f == (VIDEO_FILS - 1))
				pintar(&(p[f][c]), C_FG_WHITE, 65);
			else
				pintar(&(p[f][c]), 0, 0);
		}
	}
}

void screen_modo_mapa()
{
    unsigned char *src = (unsigned char*) VIDEO_MAPA;
    unsigned char *dst = (unsigned char*) VIDEO_SCREEN;
    int i;
    for(i = 0; i < 3840; i++){
        *(dst) = *(src);
        dst++;
        src++;
    }
    modo = 1;
}

void screen_modo_estado()
{
    unsigned char *src = (unsigned char*) VIDEO_ESTADO;
    unsigned char *dst = (unsigned char*) VIDEO_SCREEN;
    int i;
    for(i = 0; i < 3840; i++){ // 3840 = 4000 - 160
        *(dst) = *(src);
        dst++;
        src++;
    }
    modo = 2;
}

void pintar_scheduler(){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int c;
    int f = VIDEO_FILS - 1;
    for (c = 0; c < VIDEO_COLS; c++)
    {
        if (c == 0)
            print("*", c, f, C_BG_LIGHT_GREY + C_FG_BLACK, VIDEO_SCREEN);
        else if (c == VIDEO_COLS - 1)
            print("*", c, f, C_BG_BLACK + C_FG_WHITE, VIDEO_SCREEN);
        else
            pintar(&(p[f][c]), C_BG_BLACK, 0);
    }
    //Relojes tareas
    int navio = 1;
    for (c = 4; c < 28; c += 3){
        print_int(navio, c, f, C_BG_LIGHT_GREY + C_FG_WHITE, VIDEO_SCREEN);
        print("*", c + 1, f, C_BG_LIGHT_GREY + C_FG_WHITE, VIDEO_SCREEN);
        navio++;
    }
    //Relojes banderas
    navio = 1;
    for (c = 32; c < 55; c += 3){
        print_int(navio, c, f, C_BG_MAGENTA + C_FG_WHITE, VIDEO_SCREEN);
        print("*", c + 1, f, C_BG_MAGENTA + C_FG_WHITE, VIDEO_SCREEN);
        navio++;
    }
}

void pintar_buffer_mapa()
{
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_MAPA;
    int f;
    for (f = 0; f < VIDEO_FILS - 1; f++)
    {
        int c;
        for (c = 0; c < VIDEO_COLS; c++)
        {
            if (f < 3 || (f == 3 && c < 16))
                pintar(&(p[f][c]), C_BG_GREEN, 0);
            else
                pintar(&(p[f][c]), C_BG_CYAN, 0);           
        }
    }
}

void pintar_buffer_estado()
{
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_ESTADO;
    int f = 0;
    int c;
    //imprimo cabecera
    print("Francesco Tamburini/Teatro Colon", 0, 0, C_BG_BLACK + C_FG_WHITE, VIDEO_ESTADO);
    for (c = 32; c < VIDEO_COLS; c++)
        pintar(&(p[f][c]), C_BG_BLACK, 0);

    //imprimo fondo
    for (f = 1; f < VIDEO_FILS; f++)
        for (c = 0; c < VIDEO_COLS; c++)
            pintar(&(p[f][c]), C_BG_LIGHT_GREY, 0);

    //imprimo letras de los navios
    int navio = 1;
    for (f = 2; f < 10; f += 7)
    {
        for (c = 5; c < 51; c += 12)
        {
            print("NAVIO ", c, f, C_BG_LIGHT_GREY + C_FG_BLACK, VIDEO_ESTADO);
            print_int(navio, c + 6, f, C_BG_LIGHT_GREY + C_FG_BLACK, VIDEO_ESTADO);
            navio++;
        }
    }

    //pinto las banderas
    int i;
    for(i = 0; i < 8; i++){
    	pintar_banderas(i);
	}

    //imprimo pantalla de debug
    for (f = 2; f < 15; f++)
        for (c = 50; c < 78; c++)
            pintar(&(p[f][c]), C_BG_BLACK, 0);

    //imprimo pantalla de estados
    navio = 1;
    for (f = 16; f < VIDEO_FILS - 1; f++)
    {
        for (c = 0; c < VIDEO_COLS; c++)
        {
            if (c == 0 || c == VIDEO_COLS - 1)
                pintar(&(p[f][c]), C_BG_BLACK, 0);
            else if (c == 1)
                print_int(navio, c, f, C_BG_LIGHT_GREY + C_FG_BLACK, VIDEO_ESTADO);
            else
                pintar(&(p[f][c]), C_BG_CYAN, 0);
        }
        navio++;
    }
    for (f = 16; f < VIDEO_FILS - 1; f++){
        for (c = 3; c < 35; c += 14){
            if (c == 3)
                print("P1:", c, f, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            else if (c == 17)
                print("P2:", c, f, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
            else
                print("P3:", c, f, C_FG_BLACK + C_BG_CYAN, VIDEO_ESTADO);
        }
    }
}

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr, unsigned int dir) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) dir;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr, unsigned int dir, unsigned char ox) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) dir;
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    if (ox){
        print("0x", x, y, attr, dir);
        x += 2;
    }
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr, unsigned int dir) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) dir;
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr, dir);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}

void pintar_banderas(unsigned int navio)
{	
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_ESTADO;
	
	int i;
	int j;
					
	if(navio == 0)
	{
		int f = 3;
		for(i = f; i < f + 5; i++)
		{	
            int c = 2;
            for(j = c; j < c + 10;j++)
            {
                if(i == f + 4)
                {
                    if(j > c+1 && j < c+8)
                        pintar(&(p[i][j]),C_BG_RED,0);
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                }
                else
                {
                    if(j > c + 3 && j < c + 6)
                        pintar(&(p[i][j]),C_BG_RED,0);
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                }
            }
		}
	}
	if(navio == 1)
	{	
		int f = 3;
		for(i = f; i < f + 5;i++)
		{	
			int c = 14;
            for(j = c; j < c+10;j++)
            {
                if(i == f)
                {
                    if(j > c + 1 && j < c+8)
                        pintar(&(p[i][j]),C_BG_RED,0);                      
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                }
                if(i == f+1)
                {
                    if((j > c && j < c+3) || (j > c+6 && j < c+9))
                        pintar(&(p[i][j]),C_BG_RED,0);                      
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                }
                if(i == f+2)
                {
                    if(j > c+4 && j < c+7)
                        pintar(&(p[i][j]),C_BG_RED,0);                      
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                }
                if(i == f+3)
                {
                    if(j > c+2 && j < c+5)
                        pintar(&(p[i][j]),C_BG_RED,0);                      
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                }
                if(i == f+4)
                {
                    if(j > c && j < c+9)
                        pintar(&(p[i][j]),C_BG_RED,0);                      
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                }
            }
		}
	}
	if(navio == 2)
	{
		int f = 3;
		for(i = f; i < f+5;i++)
		{
			int c = 26;
            for(j = c; j < c+10;j++)
            {
                if(i == f || i == f+4)
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else
                {
                    if(j == c+9 || (i == f+2 && j > c+5))
                        pintar(&(p[i][j]),C_BG_RED,0);
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);             
                }
            }
		}
	}
	if(navio == 3)
	{
		int f = 3;
		for(i = f; i < f+5;i++)
		{
			int c = 38;
            for(j = c; j < c+10;j++)
            {
                if((j>c && j < c+3 && i< f+2) || (j>c+5 && j <c+8))
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else if(i == f+2 && j > c+1 && j < c+8)
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else
                {
                    pintar(&(p[i][j]),C_BG_CYAN,0);
                }
            }
		}
	}
	if(navio == 4)
	{
		int f = 10;
		for(i = f; i < f + 5; i++)
		{
            int c = 2;
            for(j = c; j < c+10;j++)
            {
                if(i % 2 == 0)
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else if((j == c && i < f+2) || (j == c+9 && i > f+1))
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else
                {
                    pintar(&(p[i][j]),C_BG_CYAN,0);
                }
            }
		}
	}
	if(navio == 5)
	{	
		int f = 10;
		for(i = f; i < f+5;i++)
		{
            int c = 14;
            for(j = c; j < c+10;j++)
            {
                if(i % 2 == 0)
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else if(j == c || (j == c+9 && i > f+1))
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else
                {
                    pintar(&(p[i][j]),C_BG_CYAN,0);
                }
            }
		}
	}
	if(navio == 6)
	{
        int f = 10;
        int a = 7;
        int b = 10;
        for(i = f; i < f+5;i++)
        {
            int c = 26;
            for(j = c; j < c+10;j++)
            {
                if(i == f)
                {
                    pintar(&(p[i][j]),C_BG_RED,0);
                }
                else
                {
                    if(j > c + a && j < c + b)
                        pintar(&(p[i][j]),C_BG_RED,0);
                    else
                        pintar(&(p[i][j]),C_BG_CYAN,0);
                    
                }
            }
            a = a-2;
            b = b-2;
        }
	}
	if(navio == 7)
	{
		int f = 10;
       
        for(i=f; i < f + 5; i++)
        {   int c = 38;
            for(j = c; j < c + 10;j++)
            {
                if((i == f || i == f+2 || i == f+4) &&(j > c+2 && j< c+7))
                    pintar(&(p[i][j]),C_BG_RED,0);
                else if ((j == c +2 || j == c+7) && (i == f+1 || i == f+3))
                    pintar(&(p[i][j]),C_BG_RED,0);
                else
                    pintar(&(p[i][j]),C_BG_CYAN,0);
            }   
	   }
    }
}



