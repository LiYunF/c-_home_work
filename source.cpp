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

	bool moding = 1;//��սģʽ��1Ϊ���˶�ս��0Ϊ�˻���ս

	cout << "��ӭʹ�������������������Ҫѡ�����Ϸģʽ" << endl;
	cout << "����1����ʼ���˶�սģʽ������ 0����ʼ�˻���սģʽ" << endl;
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
		borad_wuzi pvp_borad;//����
		player somebody[2];

		//��ʼ��
		bool new_or_old = 0;//�Ƿ��ȡ�洢��1Ϊ�ǣ�0Ϊ��
		if (new_or_old)cout << "�д�����" << endl;

		somebody[0].tag = somebody[1].tag="human";
		somebody[0].name = "����"; somebody[1].name = "����";
		somebody[0].cloor = 0; somebody[1].cloor = 1;


		bool cloor_now = 0;		//����ִ���ߵ���ݣ�0Ϊ�ڣ�1Ϊ��
		int x, y;				//xΪ�����꣬yΪ������
		string tx, ty;
		int action = 1;//����������1Ϊ���壬0Ϊ����


		while (1) {
			pvp_borad.print_bd();
			cout << "======================================================" << endl;
			if (cloor_now)cout << "�����ǰ�����ҽ���ѡ��" << endl;
			else cout << "�����Ǻ�����ҽ���ѡ��" << endl;

			///
			vector<int>temp = get_x_and_y();
			x = temp[0], y = temp[1];
			if (x == -1 && y == -1) {pvp_borad.get_back();continue;}
			vector<int>().swap(temp);//ȥ�ڴ�
			///

			int temp_check=pvp_borad.put_chess_pieces(cloor_now, x, y);

			if (!temp_check)continue;


			else if (temp_check == 2) {
				int new_choose;
				pvp_borad.print_bd();

				if (cloor_now) {
					cout << "!!!!!!!��ϲ ���婖 ѡ�ֻ�ʤ!!!!!!!:)" << endl;
				}
				else cout << "!!!!!!!��ϲ �����  ѡ�ֻ�ʤ!!!!!!!:)" << endl;
				cout << "��������棬������1����������0" << endl;
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
				cout << "!!!!!!!!!!!!!!!!!!!���ںڷ�ѡ��Υ�����ֹ��򣬰׷�ѡ�ֻ�ʤ��������������" << endl;
				cout << "��������棬������1����������0" << endl;
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



