
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
#include "ruler_of_wuzi.h"
#include "pvemode.h"


using namespace std;

void mode_of_wuzi_pve::init() {
	somebody[0].tag = "human";
	somebody[1].tag = "computer";

	somebody[0].name = "black"; somebody[1].name = "white";
	somebody[0].cloor = 0; somebody[1].cloor = 1;
	nNow_player = 0;//黑棋先手
	nPlayer_cloor = 0;//默认玩家是黑色
	nDeep_of_tree = 5;//默认博弈树的深度为5
	for (int i = 0; i < borad.size_of_borad; i++)
	{
		vector<bool>temp;
		for (int j = 0; j < borad.size_of_borad; j++)
			temp.push_back(0);
		bVis.push_back(temp);
	}

}

void mode_of_wuzi_pve::choose_choose() {
	cout << "请选择您所使用的棋子颜色，黑色为0,白为1" << endl;
	int x, q = 1;
	 while (q) {
		cin >> x;
		getchar();
		if (x == 0) {
			nPlayer_cloor = 0, q = 0;
		}
		else if (x == 1) {
			nPlayer_cloor = 1, q = 0;
			somebody[0].tag = "computer";
			somebody[1].tag = "human";

		}
		else cout << "输入错误请重新输入" << endl;
	 }
	 q = 1; int m;
	 cout << "请选择电脑的难度，简单为1，普通为2，困难为3" << endl;
	 cout << "困难难度时，电脑思考的时快时慢，平均思考时间在5-10秒左右" << endl;
	 while (q) {
		 cin >> m;
		 getchar();
		 if (m == 3) {
			 nDeep_of_tree = 4; q = 0;
		 }
		 else if (m == 2) {
			 nDeep_of_tree = 3; q = 0;
		 }
		 else if(m==1)nDeep_of_tree = 2, q = 0;
		 else cout << "输入错误请重新输入" << endl;
	 }
	 return;
}



void mode_of_wuzi_pve::play_wuzi_computer_game() {
	int x, y;
	init();
	nNow_player = 0;
	int temp;
	choose_choose();//获取玩家棋子颜色
	

	while (1) {
		begin_choose_call(somebody[nNow_player].tag);//输出棋盘
		int temp_check;

		if (somebody[nNow_player].tag == "human") {//当前为人类在下的时候
			vector<int>temp = get_x_and_y();//检查是否输入合格
			x = temp[0], y = temp[1];
			if (x == -1 && y == -1) {
				if (borad.get_back(2))
					cout << "悔棋成功！" << endl;
				else
				{
					cout << endl;
					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
					cout << "!!!!悔棋失败,棋盘棋子数量不足2，您只能反悔您自己的棋子，无法替他人反悔棋子!!!!" << endl;
					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

				}
				continue;
			}//悔棋
			vector<int>().swap(temp);//去内存
			temp_check = borad.put_chess_pieces(nNow_player, x, y);//下棋

		}
		else//当前为机器人在下的时候
		{
			chess temp= get_computer_decision();
			x = temp.x, y = temp.y;
			temp_check = borad.put_chess_pieces(nNow_player, x, y);//下棋

		}



		if (!temp_check)continue;//下棋出错

		else if (temp_check != 1) {//游戏结束
			if (new_game_choose(temp_check, nNow_player, somebody[0].tag, somebody[1].tag)) {
				nNow_player = 0; continue;
			}
			break;
		}
		else nNow_player ^= 1;
	}
	return;
}









