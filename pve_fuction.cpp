
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
	nNow_player = 0;//��������
	nPlayer_cloor = 0;//Ĭ������Ǻ�ɫ
	nDeep_of_tree = 5;//Ĭ�ϲ����������Ϊ5
	for (int i = 0; i < borad.size_of_borad; i++)
	{
		vector<bool>temp;
		for (int j = 0; j < borad.size_of_borad; j++)
			temp.push_back(0);
		bVis.push_back(temp);
	}

}

void mode_of_wuzi_pve::choose_choose() {
	cout << "��ѡ������ʹ�õ�������ɫ����ɫΪ0,��Ϊ1" << endl;
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
		else cout << "�����������������" << endl;
	 }
	 q = 1; int m;
	 cout << "��ѡ����Ե��Ѷȣ���Ϊ1����ͨΪ2������Ϊ3" << endl;
	 cout << "�����Ѷ�ʱ������˼����ʱ��ʱ����ƽ��˼��ʱ����5-10������" << endl;
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
		 else cout << "�����������������" << endl;
	 }
	 return;
}



void mode_of_wuzi_pve::play_wuzi_computer_game() {
	int x, y;
	init();
	nNow_player = 0;
	int temp;
	choose_choose();//��ȡ���������ɫ
	

	while (1) {
		begin_choose_call(somebody[nNow_player].tag);//�������
		int temp_check;

		if (somebody[nNow_player].tag == "human") {//��ǰΪ�������µ�ʱ��
			vector<int>temp = get_x_and_y();//����Ƿ�����ϸ�
			x = temp[0], y = temp[1];
			if (x == -1 && y == -1) {
				if (borad.get_back(2))
					cout << "����ɹ���" << endl;
				else
				{
					cout << endl;
					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
					cout << "!!!!����ʧ��,����������������2����ֻ�ܷ������Լ������ӣ��޷������˷�������!!!!" << endl;
					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

				}
				continue;
			}//����
			vector<int>().swap(temp);//ȥ�ڴ�
			temp_check = borad.put_chess_pieces(nNow_player, x, y);//����

		}
		else//��ǰΪ���������µ�ʱ��
		{
			chess temp= get_computer_decision();
			x = temp.x, y = temp.y;
			temp_check = borad.put_chess_pieces(nNow_player, x, y);//����

		}



		if (!temp_check)continue;//�������

		else if (temp_check != 1) {//��Ϸ����
			if (new_game_choose(temp_check, nNow_player, somebody[0].tag, somebody[1].tag)) {
				nNow_player = 0; continue;
			}
			break;
		}
		else nNow_player ^= 1;
	}
	return;
}









