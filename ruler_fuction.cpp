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

#include "ruler_of_wuzi.h"
/*


class ruler {
protected:
	borad_wuzi borad;
public:
	void v_init();
	void v_begin_choose_call();
};
*/
void judge::begin_choose_call(string s) {
	borad.draw_board();
	cout << "======================================================" << endl;
	cout << "现在是" << s << "玩家进行选择"<<endl;
}
void judge::init() {
	borad.get_new_play();
}
int judge::new_game_choose(int temp_check, int cloor_now,string black,string white) {
	borad.draw_board();
	int new_choose = 0;

	if (temp_check == 2) {

		if (cloor_now) {
			cout << endl << endl;
			cout << "!!!!!!!!!!!!!!!!!!!!!!请注意!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			cout << "!!!!!!!恭喜 白棋〇 选手"<<white<<"获胜!!!!!!!:)" << endl;
		}
		else {
			cout << endl << endl;
			cout << "!!!!!!!!!!!!!!!!!!!!!!请注意!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			cout << "!!!!!!!恭喜 黑棋●  选手获" << black << "胜!!!!!!!:)" << endl;
		}
		cout << "若想继续玩，请输入1，否则输入0" << endl;
		cin >> new_choose;

		if (new_choose) {
			//!!!!!!!!!!!!!!!!!!!!!!!!!!
			borad.get_new_play();
		}

	}
	else if (temp_check == 3 && !cloor_now) {
		cout << endl << endl;
		cout << "!!!!!!!!!!!!!!!!!!!!!!请注意!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cout << "!!!!!!!!!!!!!!!!!!!由于黑方选手" << black << "违反禁手规则，白方选手获胜！！！！！！！" << endl << endl;
		cout << "若想继续玩，请输入1，否则输入0" << endl;
		cin >> new_choose;
		if (new_choose) {
		//!!!!!!!!!!!!!!!!!!!!!!!!!!
		borad.get_new_play();
		}

	}
	else if (temp_check == 4) {
		cout << endl << endl;
		cout << "!!!!!!!!!!!!!!!!!!!!!!请注意!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cout << "!!!!!!!!!!!!!!!!!!!居然平局了！！！！！！！" << endl << endl;
		cout << "若想继续玩，请输入1，否则输入0" << endl;
		cin >> new_choose;
		if (new_choose) {
			//!!!!!!!!!!!!!!!!!!!!!!!!!!
			borad.get_new_play();
		}
	}
	else {
		cout << "ERROR" << endl; return -1;
	}
	return new_choose;
}






int judge::check_xory(char tx) {//检测x和y的值
	int x;
	if (tx >= '0' && tx <= '9') {
		x = tx - '0'; return x;
	}
	if (tx >= 'a' && tx <= 'e')//a10,b11,c12,d13,e14
	{
		x = tx - 'a' + 10; return x;
	}
	if (tx == 'z')return -1;

	return -2;
}

vector<int> judge::get_x_and_y() {//获得x或y的值
	string s;
	int x = 0, y = 0;
	//fg:1==x,0==y;
	vector<int>ans;
	ans.push_back(-1), ans.push_back(-1);

	while (1) {
		cout << "请输入落子位置xy，如a5（先横坐标后纵坐标)，输入zz进行悔棋" << endl;
		cin >> s;
		getchar();
		if (s.size() != 2) {
			cout << "输入错误，请重新输入" << endl;
		}
		else {
			char tx = s[0], ty = s[1];
			y = check_xory(tx);
			x = check_xory(ty);
			if (x == -2 || y == -2) {
				cout << "输入错误，请重新输入" << endl; continue;
			}
			else if (x == -1 && y == -1) {
				//if (pvp_mode.get_back())continue;
				return ans;
			}
			ans[0] = x, ans[1] = y; break;

		}
	}
	return ans;
}

