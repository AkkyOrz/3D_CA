#pragma once

/*****************************************************************
 * ここで初期値の変更を行う
 * ここ以外は基本的にいじらない。
 * ***************************************************************/
static constexpr int N_STATE = 5;
static constexpr double INIT_CELL_PROPOTION = 0.2; // 初期のcellの割合 0はすべて死滅(のはず)
static constexpr double DEG_RATE = 15.0;           // グラデーションの差分割合

/*****************************************************************
 * 以上
 * ***************************************************************/

static constexpr int GRID_SIZE_X = 100;              //gridの縦と横
static constexpr int GRID_SIZE_Y = 100;
static constexpr int GRID_SIZE_Z = 100;

using CELL_TYPE = char;

static constexpr CELL_TYPE birth[] = {4};                                                                                      //,5,6,7,8};
static constexpr CELL_TYPE survive[] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};

static constexpr int CELL_SIZE     = GRID_SIZE_X * GRID_SIZE_Y * GRID_SIZE_Z;
static constexpr int XY_PLANE_SIZE = GRID_SIZE_X * GRID_SIZE_Y;

static constexpr int TIME_SLICE = 1;


static constexpr int DEFULAT_INPUT_NUM = 1;
                         //0 なら　tmp.txtから持ってくる
                         //1 はランダム
                         //2はN_STATE-1のランダムは
                         //3は固定値
                         //4は固定値


static constexpr int DEFAULT_COLOR_VERSION = 1;
                          // 0 は原点から最奥までのグラデーション,
                   	      // 1は状態ごとの色分け
                          // 2は単色,
                          // 3は中心からのグラデーション
