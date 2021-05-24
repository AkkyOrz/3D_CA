#ifndef _CONGIG_H_
#define _CONGIG_H_




/*****************************************************************
 * ここで初期値の変更を行う
 * ここ以外は基本的にいじらない。
 * ***************************************************************/
const int N_STATE = 5;
const double INIT_CELL_PROPOTION = 0.2; // 初期のcellの割合 0はすべて死滅(のはず)
const double DEG_RATE = 15.0;           // グラデーションの差分割合

/*****************************************************************
 * 以上
 * ***************************************************************/


const int GRID_SIZE_X = 100;              //gridの縦と横
const int GRID_SIZE_Y = 100;
const int GRID_SIZE_Z = 100;


using CELL_TYPE = char;

static const CELL_TYPE birth[] = {4};                                                                                      //,5,6,7,8};
static const CELL_TYPE survive[] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
constexpr int CELL_SIZE     = GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z;
constexpr int XY_PLANE_SIZE = GRID_SIZE_X * GRID_SIZE_Y;

static CELL_TYPE cell[CELL_SIZE];
static CELL_TYPE cell_next[CELL_SIZE];


static int counter = 0;
static int speed = 1;

static int INPUT_NUM = 1; //0 なら　tmp.txtから持ってくる
                         //1 はランダム
                         //2はN_STATE-1のランダムは
                         //3は固定値
                         //4は固定値

static int color_ver = 1; // 0 は原点から最奥までのグラデーション,
                   	      // 1は状態ごとの色分け
                          // 2は単色,
                          // 3は中心からのグラデーション



//#define USE_OPENMP
//#define OPENMP_THREAD 2

//#define USE_OPENCL

#endif
