#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <random>
#include <string.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include "opencl.h"
#include "config.h"

#define WINDOW_X (1000)
#define WINDOW_Y (1000)
#define WINDOW_NAME "test2"

class Point {
public:
    double x, y, z;
    Point() {
        x = y = z = 0.0;
    }
    Point(double point_x, double point_y, double point_z) {
        x = point_x;
        y = point_y;
        z = point_z;
    }
};

// GL関係のプロトタイプ宣言
void init_GL(int argc, char *argv[]);
void init();
void set_callback_functions();

void glut_display();
void glut_keyboard(unsigned char key, int x, int y);
void glut_special_keyboard(int key, int x, int y);
void glut_mouse(int button, int state, int x, int y);
void glut_motion(int x, int y);
void glut_idle();
void timer(int value);

extern CELL_TYPE cell[CELL_SIZE];
extern CELL_TYPE cell_next[CELL_SIZE];

// lifegame関連のプロトタイプ宣言
int cycle_x(int x);
int cycle_y(int y);
int cycle_z(int z);
void init_cells();
int count_adjacent_cells(int x, int y, int z);
int count_adjacent_cells_2(int x, int y, int z);
void update_cells();
bool check_around(int dx, int dy, int dz, int state);

bool check_near(int x, int y, int z);

int grid_index(const int x, const int y, const int z);

// 色変換のプロトタイプ宣言
void rgbTolab(GLfloat rgb_color[], GLfloat lab_color[]);
void labtoRGB(GLfloat lab_color[], GLfloat rgb_color[]);
void hsv2rgb(GLfloat hsv_color[], GLfloat rgb_color[]);
void rgb2hsv(GLfloat rgb_color[], GLfloat hsv_color[]);

// 物体描画関連のプロトタイプ宣言
void draw_pyramid();
void draw_cube(Point p, GLfloat cube_color[]);
void draw_cube_trans(Point p, GLfloat cube_color[]); 
void draw_grid();
void draw_cubic_line(int mode);
void draw_lifegame();
void draw_axis(double length);
void draw_string(std::vector<std::string> strs, int w, int h, int x0, int y0);
