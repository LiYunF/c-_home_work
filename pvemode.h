//#pragma once
#ifdef PVE_OF_WUZI
#else

#define PVE_OF_WUZI

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
#include "player.h"
#include "wuzi_borad.h"
#include "ruler_of_wuzi.h"

using namespace std;

class mode_of_wuzi_pve :public judge {

protected:
	player somebody[2];
	int nNow_player;
	int nPlayer_cloor;
	int nSize_of_borad;
	int nDeep_of_tree;
	stack<chess>stChess_near;
	vector<vector<bool>>bVis;
public:
	void init();
	void play_wuzi_computer_game();
	void choose_choose();
	int get_near_place(chess);//获取附近的空白位置,返回空白位置数
	chess get_computer_decision();

	int dfs_game_tree(chess, int, bool, bool, int);//博弈树
	int get_score(chess, bool);//获取分数
	pair<int, pair<int, int> >the_number_of_cloors_pve(int, bool, int, int);

};






#endif // DEBUG










