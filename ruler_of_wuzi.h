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


class judge {//����
protected:
//public:
	borad_wuzi borad;
public:
	void init();
	void begin_choose_call(string);
	int new_game_choose(int,int,string ,string );//�Ƿ��������Ϸ����������Ϸ��1�����򷵻�0
	int check_xory(char);//���x��y��ֵ
	vector<int> get_x_and_y();//���x��y��ֵ

};




