#include <stdio.h>
#include <stdlib.h>     //求绝对值所需要用到的头文件
#include <time.h>        //随机下棋rand函数所需要用到的头文件
#include <graphics.h>    //图形库所需要用到的头文件
#include <Windows.h>     //
#include <mmsyscom.h>
#pragma comment(lib,"winmm.lib")

void BGM();
//=============================双人对战==========================
int player();  //双人对战
void initGame();

//============================玩家和AI下棋=========================
void AI();           //玩家和AI下棋
void initGame1();    //初始化游戏

//************player下棋的函数部分**************

void playerplaychess();

//*************AI下棋的函数部分****************
void AIplaychess();          //AI下棋一
void AIplaychess1();         //AI下棋二

//||||||||||这是连续的情况|||||||||||
int judge1();      //AI对战中的判断输赢           
int judge3();      //判断玩家棋子将要为4时的应对（为4后两边棋子都没有电脑棋子堵住）
int judge33();     //判断电脑棋子为将要4时的应对（不管为4后两边之一是否有玩家棋子）  
int judge4();       //判断电脑和玩家棋子将要为5时的应对
int judge7();       //判断电脑棋子将要为3时的应对
int judge8();       //判断电脑棋子将要为2时的应对
int judge9();       //判断电脑棋子将要为4（为4后两旁都没有棋子堵住）

//||||||||||这是不连续的情况|||||||||||||
int judge5();      //判断电脑棋子将要为4时的应对（不管为4后两边之一是否有玩家棋子，能构成四个就下）
int judge6();     //判断电脑和玩家棋子将要为5时的应对
int judge10();    //判断玩家棋子将要为4是的应对（为4后两边棋子都没有电脑棋子堵住）


//***************战绩存储部分****************
void save_record(int a);    //存储当前战绩进入AI.txt文件里
void load_record();         //查阅历史战绩
int save_count(int j);      //存储当前下棋次数进入AI.dat文件里
int load_count();           //查阅总下棋次数
 

