#pragma once
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>		
#include <vector>		
#include <queue>		
#include <string>
#include <cstring>      
#include <map>			
#include <stack>		
#include <set>	

#include "chess.h"
#include "wuzi_borad.h"


class judge {//裁判
protected:
//public:
	borad_wuzi borad;
public:
	void init();
	void begin_choose_call(string);
	int new_game_choose(int,int,string ,string );//是否进行新游戏，进行新游戏则返1，否则返回0
	int check_xory(char);//检测x和y的值
	vector<int> get_x_and_y();//获得x或y的值

};




