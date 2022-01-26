
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
		begin_choose_call(somebody[now_player].name);//�������
		
		vector<int>temp = get_x_and_y();//����Ƿ�����ϸ�
		x = temp[0], y = temp[1];
		
		if (x == -1 && y == -1) { 
			if(borad.get_back(2))//		��2����
				cout << "����ɹ���" << endl;
			else {
				cout << endl;
				cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				cout << "!!!!����ʧ��,����������������2����ֻ�ܷ������Լ������ӣ��޷������˷�������!!!!" << endl;
				cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			}
		continue; 
		}//����

		vector<int>().swap(temp);//ȥ�ڴ�

		int temp_check = borad.put_chess_pieces(now_player, x, y);//����

		if (!temp_check)continue;//�������

		else if (temp_check != 1) {//��Ϸ����
			if (new_game_choose(temp_check, now_player,somebody[0].name, somebody[1].name)) {
				now_player = 0; continue;
			}
			break;
		}
		else now_player^= 1;
	}
	return;
}







