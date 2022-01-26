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

#include "base_borad.h"
#include "chess.h"

vector<vector<int>> draw_b:: get_init_score(int size_of_borad) {
	vector<vector<int>> res;
	for (int i = 0; i < size_of_borad; i++) {
		vector<int>temp;
		for (int j = 0; j < size_of_borad; j++)temp.push_back(0);
		res.push_back(temp);
		vector<int>().swap(temp);//防止内存泄漏,彻底杀死temp占用的内存

	}
	return res;
}
vector<vector<int>>draw_b::get_init_board(int size) {
	vector<vector<int>> test;

	for (int i = 0; i < size; i++)
	{

		vector<int>temp;
		if (!i) {
			temp.push_back(0);
		}
		else if (i == size - 1) {
			temp.push_back(6);
		}
		else temp.push_back(3);
		for (int j = 1; j < size-1; j++) {
			if (!i) {
				temp.push_back(1);
			}
			else if (i == size -1) {
				temp.push_back(7);
			}
			else temp.push_back(4);
		}

		if (!i) {
			temp.push_back(2);
		}
		else if (i == size - 1) {
			temp.push_back(8);
		}
		else temp.push_back(5);
		test.push_back(temp);
		vector<int>().swap(temp);//防止内存泄漏,彻底杀死temp占用的内存


	}

	return test;
}


void draw_b::draw_board() {//画棋盘
			/*
			0	1	2
			3	4	5
			6	7	8
			┏0		┯1		┓2
			┠3		┼4		┨5
			┗6		┷7		┛8

			9:●    blak_put
			10：▼	last blak put
			11:	〇	white put
			12:	▽  last white put



			*/

			//printf("●〇");
	int hold_last_place;
	chess last_place;
	if (!s_process.empty())
	{
		last_place =s_process.top();
		vt_board[last_place.x][last_place.y] = last_place.cloor ? 12 : 10;//上次下棋的位置为白色时，放▽，否则放▼
	}

	cout << "┏ ";
	for (int i = 0; i < size_of_borad + 4; i++)printf("━ ");
	cout << "┓ " << endl;



	cout << "┃     ";
	for (int j = 0; j < size_of_borad; j++)cout << "  ";
	cout << "   y┃";
	cout << endl;

	cout << "┃     ";
	for (int j = 0; j < size_of_borad; j++)cout << "  ";
	cout << "  ↓┃";
	cout << endl;


	for (int i = 0; i < size_of_borad; i++)
	{
		cout << "┃     ";
		for (int j = 0; j < size_of_borad; j++)
		{
			switch (vt_board[i][j])
			{
			case 0:
				printf("┏ ");
				break;
			case 1:
				printf("┯ ");
				break;

			case 2:
				printf("┓ ");
				break;

			case 3:
				printf("┠ ");
				break;

			case 4:
				printf("┼ ");
				break;

			case 5:
				printf("┨ ");
				break;

			case 6:
				printf("┗ ");
				break;

			case 7:
				printf("┷ ");
				break;

			case 8:
				printf("┛ ");
				break;

			case 9:
				printf("●");
				break;

			case 10:
				printf("▼");
				break;

			case 11:
				printf("〇");
				break;

			case 12:
				printf("▽");
				break;


			}
		}
		if (i < 10)cout << "  " << i << " ┃" << endl;
		else {
			char tqp = i - 10 + 'a';
			cout << "  " << tqp << " ┃" << endl;
		}
		//cout << endl;

	}
	cout << "┃   x:";
	for (int i = 0; i < 10; i++) {
		cout << i << " ";
	}
	cout << "a " << "b " << "c " << "d " << "e";//16进制下的10 11 12 13 14
	cout << "     ┃" << endl;


	for (int i = 0; i < 1; i++) {
		cout << "┃     ";
		for (int j = 0; j < size_of_borad; j++)cout << "  ";
		cout << "    ┃";
		cout << endl;
	}

	cout << "┗ ";
	for (int i = 0; i < size_of_borad + 4; i++)printf("━ ");
	cout << "┛ ";

	cout << endl;
	cout << "黑棋：●      白棋：〇      倒三角为上次下过的位置" << endl;
	//cout << "x为纵轴，y为横轴" << endl;

	if (!s_process.empty())
	{
		last_place = s_process.top();
		vt_board[last_place.x][last_place.y] = last_place.cloor ? 11 : 9;
		//上次下棋的位置为白色时，放〇，否则放●
		/*
		
		9:●    blak_put
			10：▼	last blak put
			11:	〇	white put
			12:	▽  last white put
		*/
	}

}




