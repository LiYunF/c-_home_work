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
//
#include "base_borad.h"
//#include "wuzi_borad.h"
//#include "chess.h"
//#include "player.h"
//#include "action_fuction.cpp"

#include "pvpmode.h"
#include "pvemode.h"
using namespace std;





int main() {
	

	system("color 70");

	bool moding = 1;//对战模式，1为人人对战，0为人机对战

	cout << "欢迎使用五子棋程序，请输入你要选择的游戏模式" << endl;
	cout << "输入1，开始人人对战模式。输入 0，开始人机对战模式" << endl;
	cin >> moding;
	//debug
	//moding = 1;

	if (moding) {
		mode_of_wuzi_pvp pvpwuzi_game;
		pvpwuzi_game.v_play_wuzi_game();
	}
	else
	{
		mode_of_wuzi_pve pvpwuzi_game;
		pvpwuzi_game.play_wuzi_computer_game();
	}
	

	return 0;
}







/*

	if (moding) {
		borad_wuzi pvp_borad;//声明
		player somebody[2];

		//初始化
		bool new_or_old = 0;//是否读取存储，1为是，0为否
		if (new_or_old)cout << "有待开发" << endl;

		somebody[0].tag = somebody[1].tag="human";
		somebody[0].name = "黑棋"; somebody[1].name = "白棋";
		somebody[0].cloor = 0; somebody[1].cloor = 1;


		bool cloor_now = 0;		//现在执棋者的身份，0为黑，1为白
		int x, y;				//x为横坐标，y为纵坐标
		string tx, ty;
		int action = 1;//动作参数，1为下棋，0为悔棋


		while (1) {
			pvp_borad.print_bd();
			cout << "======================================================" << endl;
			if (cloor_now)cout << "现在是白棋玩家进行选择" << endl;
			else cout << "现在是黑棋玩家进行选择" << endl;

			///
			vector<int>temp = get_x_and_y();
			x = temp[0], y = temp[1];
			if (x == -1 && y == -1) {pvp_borad.get_back();continue;}
			vector<int>().swap(temp);//去内存
			///

			int temp_check=pvp_borad.put_chess_pieces(cloor_now, x, y);

			if (!temp_check)continue;


			else if (temp_check == 2) {
				int new_choose;
				pvp_borad.print_bd();

				if (cloor_now) {
					cout << "!!!!!!!恭喜 白棋〇 选手获胜!!!!!!!:)" << endl;
				}
				else cout << "!!!!!!!恭喜 黑棋●  选手获胜!!!!!!!:)" << endl;
				cout << "若想继续玩，请输入1，否则输入0" << endl;
				cin >> new_choose;
				if (new_choose) {
					//!!!!!!!!!!!!!!!!!!!!!!!!!!
					cloor_now = 0;
					pvp_borad.get_new_play();
					continue;
				}
				break;
			}
			else if (temp_check == 3) {
				int new_choose;
				pvp_borad.print_bd();
				cout << "!!!!!!!!!!!!!!!!!!!由于黑方选手违反禁手规则，白方选手获胜！！！！！！！" << endl;
				cout << "若想继续玩，请输入1，否则输入0" << endl;
				cin >> new_choose;
				if (new_choose) {
					//!!!!!!!!!!!!!!!!!!!!!!!!!!
					cloor_now = 0;
					pvp_borad.get_new_play();
					continue;
				}
				break;

			}

			cloor_now ^= 1;
		}
	}



	*/



