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
	cout << "������" << s << "��ҽ���ѡ��"<<endl;
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
			cout << "!!!!!!!!!!!!!!!!!!!!!!��ע��!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			cout << "!!!!!!!��ϲ ���婖 ѡ��"<<white<<"��ʤ!!!!!!!:)" << endl;
		}
		else {
			cout << endl << endl;
			cout << "!!!!!!!!!!!!!!!!!!!!!!��ע��!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			cout << "!!!!!!!��ϲ �����  ѡ�ֻ�" << black << "ʤ!!!!!!!:)" << endl;
		}
		cout << "��������棬������1����������0" << endl;
		cin >> new_choose;

		if (new_choose) {
			//!!!!!!!!!!!!!!!!!!!!!!!!!!
			borad.get_new_play();
		}

	}
	else if (temp_check == 3 && !cloor_now) {
		cout << endl << endl;
		cout << "!!!!!!!!!!!!!!!!!!!!!!��ע��!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cout << "!!!!!!!!!!!!!!!!!!!���ںڷ�ѡ��" << black << "Υ�����ֹ��򣬰׷�ѡ�ֻ�ʤ��������������" << endl << endl;
		cout << "��������棬������1����������0" << endl;
		cin >> new_choose;
		if (new_choose) {
		//!!!!!!!!!!!!!!!!!!!!!!!!!!
		borad.get_new_play();
		}

	}
	else if (temp_check == 4) {
		cout << endl << endl;
		cout << "!!!!!!!!!!!!!!!!!!!!!!��ע��!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cout << "!!!!!!!!!!!!!!!!!!!��Ȼƽ���ˣ�������������" << endl << endl;
		cout << "��������棬������1����������0" << endl;
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






int judge::check_xory(char tx) {//���x��y��ֵ
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

vector<int> judge::get_x_and_y() {//���x��y��ֵ
	string s;
	int x = 0, y = 0;
	//fg:1==x,0==y;
	vector<int>ans;
	ans.push_back(-1), ans.push_back(-1);

	while (1) {
		cout << "����������λ��xy����a5���Ⱥ������������)������zz���л���" << endl;
		cin >> s;
		getchar();
		if (s.size() != 2) {
			cout << "�����������������" << endl;
		}
		else {
			char tx = s[0], ty = s[1];
			y = check_xory(tx);
			x = check_xory(ty);
			if (x == -2 || y == -2) {
				cout << "�����������������" << endl; continue;
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

