#pragma once

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <list>

//Movement
#define D_RIGHT     1
#define D_LEFT     -1

//Input keys
#define ESC        27
#define MOVE_LEFT  'j'
#define MOVE_RIGHT 'k'
#define FIRE_LEFT  'h'
#define FIRE_RIGHT 'l'

//Timers
#define T_ENEMY     30
#define T_MUSHROOM 100
#define T_RAIN       5

//Console size and colors
#define WIDTH        90
#define COLOR_RED    FOREGROUND_RED
#define COLOR_GREEN  FOREGROUND_GREEN
#define COLOR_BLUE   FOREGROUND_BLUE | FOREGROUND_GREEN
#define COLOR_YELLOW FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define COLOR_WHITE  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
