#ifdef BASE_BORAD
#else

#define BASE_BORAD

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
using namespace std;

class draw_b {
public:
	int size_of_borad;//���̴�С��Ĭ��Ϊ15*15
	vector<vector<int>>vt_board;//����
	vector<vector<int>>vt_board_sorce;//���̷���
	stack<chess> s_process;//������̵���ջ
	
public:
		

		draw_b() {
			size_of_borad = 15;
			vt_board = get_init_board(size_of_borad);
			vt_board_sorce = get_init_score(size_of_borad);

		}
		

		void draw_board();
		vector<vector<int>> get_init_score(int);//��ʼ�����̷���
		vector<vector<int>> get_init_board(int);//��ʼ�����̸�ʽ


		





};







#endif //BASE_BORAD




