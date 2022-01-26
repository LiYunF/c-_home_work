
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
#include "pvpmode.h"
using namespace std;







void mode_of_wuzi_pvp::v_play_wuzi_game() {
	int x, y;
	now_player = 0;
	while (1) {
		begin_choose_call(somebody[now_player].name);//输出棋盘
		
		vector<int>temp = get_x_and_y();//检查是否输入合格
		x = temp[0], y = temp[1];
		
		if (x == -1 && y == -1) { 
			if(borad.get_back(2))//		悔2步棋
				cout << "悔棋成功！" << endl;
			else {
				cout << endl;
				cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				cout << "!!!!悔棋失败,棋盘棋子数量不足2，您只能反悔您自己的棋子，无法替他人反悔棋子!!!!" << endl;
				cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			}
		continue; 
		}//悔棋

		vector<int>().swap(temp);//去内存

		int temp_check = borad.put_chess_pieces(now_player, x, y);//下棋

		if (!temp_check)continue;//下棋出错

		else if (temp_check != 1) {//游戏结束
			if (new_game_choose(temp_check, now_player,somebody[0].name, somebody[1].name)) {
				now_player = 0; continue;
			}
			break;
		}
		else now_player^= 1;
	}
	return;
}







