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
//#include "ruler_fuction.cpp" //get_x_and_y





int mode_of_wuzi_pve::get_near_place(chess now) {
	chess temp;
	int x = now.x, y = now.y;
	//int cloor = now.cloor;
	//bVis[x][y] = 1;//只是求near
	int cnt = stChess_near.size();
	temp.cloor = 6;//=whatevery
	int tx, ty;
	for (int i = -2; i <= 2; i++) {//1
		ty = y + i;
		if (ty >= 0 && ty < borad.size_of_borad && 
			borad.vt_board[x][ty] < 9 && !bVis[x][ty]) {
			temp.x = x, temp.y = y + i;
			//temp.cloor = whatevey
			stChess_near.push(temp);
			bVis[temp.x][temp.y] = 1;
		}
	}
	for (int i = -2; i <= 2; i++) {//2
		tx = x + i;
		if (tx >= 0 && tx < borad.size_of_borad && 
			borad.vt_board[tx][y] < 9 && !bVis[tx][y]) {
			temp.x = x + i, temp.y = y;
			//temp.cloor = whatevey
			stChess_near.push(temp);
			bVis[temp.x][temp.y] = 1;
		}
	}
	for (int i = -1; i <= 1; i++) {//3
		tx = x + i;
		ty = y + i;
		if (tx >= 0 && tx < borad.size_of_borad &&
			ty >= 0 && ty < borad.size_of_borad &&
			borad.vt_board[tx][ty] < 9&&
			!bVis[tx][ty]) {

			temp.x = x + i, temp.y = y + i;
			//temp.cloor = whatevey
			stChess_near.push(temp);
			bVis[temp.x][temp.y] = 1;
		}
	}
	for (int i = -1; i <= 1; i++) {//4
		tx = x + i;
		ty = y - i;
		if (tx >= 0 && tx < borad.size_of_borad &&
			ty >= 0 && ty < borad.size_of_borad &&
			borad.vt_board[tx][ty] < 9 &&
			!bVis[tx][ty]) 
		{

			temp.x = x + i, temp.y = y - i;
			//temp.cloor = whatevey
			//bVis[temp.x][temp.y]
			stChess_near.push(temp);
			bVis[temp.x][temp.y] = 1;
		}
	}
	return  stChess_near.size()-cnt;
}



chess mode_of_wuzi_pve::get_computer_decision() {

	//获取临近点集
	stack<chess>temp_s = borad.s_process;
	if (temp_s.empty()) {//为空时，说明没有下任何棋子，返回中心点
		chess ans;
		ans.x = 7, ans.y = 7, ans.cloor = 0, ans.val = 2;
		return ans;
	}
	chess last_place = borad.s_process.top();
	bool have_4 = (get_score(last_place,last_place.cloor) % 2);

	stack<chess>().swap(stChess_near);//清空near
	for (int i = 0; i < borad.size_of_borad; i++)//清空bVis
		for (int j = 0; j < borad.size_of_borad; j++)
			bVis[i][j] = 0;


	while (!temp_s.empty()) {//将所有临近点都放进来,同时更新vis矩阵
		get_near_place(temp_s.top());
		temp_s.pop();
	}
	//  |chess_near|  and  |B_vis|  is ready
	stack<chess>vChae = stChess_near;


	int nThe_optimal_scores;//白色最大或黑色最小的分数
	nThe_optimal_scores = somebody[0].tag == "computer" ? -10000000 : 10000000;//为黑则求最大，否则求最小
	chess ceThe_optimal_chess;//最佳选择落点
	ceThe_optimal_chess.x = -1, ceThe_optimal_chess.y = -1;
	int scores;
	while (!vChae.empty()) {
		chess i = vChae.top();//65 a9
		if (somebody[0].tag == "computer")//当黑棋为电脑时，求最大分数
		{

			scores = dfs_game_tree(i, 1, 0, have_4, nThe_optimal_scores);//在dfs里面自动放入该棋子了
			if (nThe_optimal_scores < scores) {
				ceThe_optimal_chess = i;
				nThe_optimal_scores = scores;
				if (nThe_optimal_scores >= 1000000)break;
			}
		}
		else//为白色，求min
		{
			scores = dfs_game_tree(i, 1, 1, have_4, nThe_optimal_scores);

			if (nThe_optimal_scores > scores) {
				ceThe_optimal_chess = i;
				nThe_optimal_scores = scores;
				if (nThe_optimal_scores <= -1000000)break;
			}

		}
		vChae.pop();
	}


	//cout << "debug" << endl;

	
	return ceThe_optimal_chess;

}




int mode_of_wuzi_pve::dfs_game_tree(chess now, int deep,bool cloor,bool last_place_have_4,int last_best_score ) {
	if (deep == nDeep_of_tree) {
		return get_score(now, cloor);
	}
	/*
			9:●    blak_put
			10：▼	last blak put
			11:	〇	white put
			12:	▽  last white put
	*/
	int ans_score= get_score(now, cloor);
	if (ans_score == 1000000 || ans_score == -1000000)return ans_score;

	
	if (!last_place_have_4) {//判断上一步的敌人有没有四
			//如果没有四，当到达必胜态时，返回必胜态，不必再dfs
		if (ans_score >= 50000 || ans_score <= -50000) {
			return ans_score;
		}
	}
	else {//如果上一步有四，
		//首先，现在不可能练成当前棋子颜色的五连，因为连成了就在前面已经返回1e6 or -1e6了
		//那么当前状态无法获胜，只能去堵上一步的四了//于是则只需判断当前落点的位置是否能帮助上一步凑成五连即可，
		//能凑成五连就说明当前位置可以堵住上一步，继续dfs,否则返回必败态
		int ni_s = get_score(now, cloor ? 0 : 1);
		if (ni_s != 1000000 && ni_s != -1000000) {//不能和上步凑成5连
			//返回ans_score+nThe_optimal_scores
			ni_s = cloor ? 10000000 : -10000000;//当前为白，则下一步是黑,+1e6，反则下一步为白，-1e6
			return ans_score+ni_s;
		}
	}
	
	
	last_best_score -= ans_score;
	bool have_4 = (ans_score%2);//判断这步有没有产生四

	int hold_the_msg = borad.vt_board[now.x][now.y];
	borad.vt_board[now.x][now.y] = cloor ? 11 : 9;//黑色为黑棋9，否则为白棋11

	int nera_number = get_near_place(now);//获得当前节点附近的空节点个数
	stack<chess>vChae = stChess_near;//获取near栈

	int nThe_optimal_scores;//白色最大或黑色最小的分数
	nThe_optimal_scores = cloor ? -10000000 : 10000000;//当前为黑，则下一层为白，白方策略为返回最小分数
	chess ceThe_optimal_chess;//最佳选择落点
	ceThe_optimal_chess.x = -1, ceThe_optimal_chess.y = -1;


	while (!vChae.empty()) {
		chess i = vChae.top();
		if (borad.vt_board[i.x][i.y] < 9)//不是走过的点的时候
		{
			if (cloor)//当前为白棋时，下一层为黑，于是求max
			{
				int scores = dfs_game_tree(i, deep + 1, 0, have_4, nThe_optimal_scores);

				if (nThe_optimal_scores < scores) {//此处是下一层的决策
					ceThe_optimal_chess = i;
					nThe_optimal_scores = scores;
					//本层是白棋，期望是返回的值为最小的，也就是说，
					//上层的last_best_score是上层枚举的当前的最小值
					//而现在在求最大值，那么当nThe_optimal_scores+ans_score>last_best_score时，就不用枚举了,
					//于是我让last-=score , 这里要注意,可能nThe_optimal_scores=last_best_score=-1e7
					if (nThe_optimal_scores > last_best_score)break;
				}

				
			}
			else//为黑色，下一层为白，要返回min
			{
				int scores = dfs_game_tree(i, deep + 1, 1, have_4, nThe_optimal_scores);//在dfs里面自动放入该棋子了
				if (nThe_optimal_scores > scores) {
					ceThe_optimal_chess = i;
					nThe_optimal_scores = scores;
					//本层是黑棋，期望是返回的值为最大的，也就是说，
					//上层的last_best_score是上层枚举的当前的最大值
					//而现在在求最小值，那么当nThe_optimal_scores<last_best_score-ans_score时，就不用枚举了
					if (nThe_optimal_scores < last_best_score)break;
				}
			}
		}
		vChae.pop();
	}

	//回溯
	borad.vt_board[now.x][now.y] = hold_the_msg;
	chess tempq;
	while (nera_number--) {
		tempq = stChess_near.top();
		bVis[tempq.x][tempq.y] = 0;
		stChess_near.pop();
	}

	//ans_score+
	return  ans_score + nThe_optimal_scores;//返回当前点的分数+下一步最优的分数
}

int mode_of_wuzi_pve::get_score(chess now, bool cloor) {
	//黑棋正得分，白棋负得分
	int max_score[2] = {1000000,-1000000};//100000为胜利，-100000为失败
	int x = now.x, y = now.y;
	pair<int, pair<int, int> >  a[8];
	pair<int, pair<int, int> > tx, ty;
	int num3, num4, num2; num2 = num3 = num4 = 0;
	
	int score = 0;

	if (!cloor) {//为黑,之所以在这里就直接用cloor，是为了减少运算次数,
		//否则要写很多if else 或者进行很多次乘法运算

		/*
	0	  6 	5

	2	(x,y)	3

	4	  7		1


	*/
		for (int i = 0; i < 8; i += 2) {
			a[i] = the_number_of_cloors_pve(i, 0, x, y);
			a[i + 1] = the_number_of_cloors_pve(i + 1, 0, x, y);
			if (a[i].first + a[i + 1].first >= 5) {//长连
				return max_score[1];//-100000
			}
			else if (a[i].first + a[i + 1].first == 4) {
				return max_score[0];//获胜,因为这里ai和ai+1是没有计算chess now，
				//算上现在要走的，就是4+1=5了
			}
			if (a[i].second.first == -1 && a[i + 1].second.first == -1) {
				//score += 0;//此时是死路，无贡献
				continue;
			}
			tx = ty = { 0,{0,0} };
			if (a[i].second.first != -1) {
				tx = the_number_of_cloors_pve(i, 0, a[i].second.first, a[i].second.second);
			}
			if (a[i + 1].second.first != -1)ty = the_number_of_cloors_pve(i + 1, 0, a[i + 1].second.first, a[i + 1].second.second);


			if (a[i].first + a[i + 1].first == 3) {
				//such as :●▼●●etc
				if (a[i].second.first != -1) {
					num4++;//四
					if (a[i + 1].second.first != -1)score += 50000;//活4
					else score += 6000;//冲四
				}
				else if (a[i + 1].second.first != -1)score += 6000, num4++;//四
				//else 的情况= 两头都是堵着的=没贡献=score+=0
			}

			else if (a[i].first + a[i + 1].first == 2) {
				//such as :▼●●etc
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1方向都为空
					if (!tx.first && !ty.first) {// |□▼●●□|
						score += 3000;//活三+3000
						num3++;
					}
					else
					{
						if (tx.first == 1 && ty.first == 1)// |□●□▼●●□●|
						{
							//禁手-1000000
							return max_score[1];
						}
						else if (ty.first == 1 || tx.first == 1) // |?□▼●●□●|->num4>1
						{//|□▼●●□●|
							score += 6000;
							num4++;//冲四
						}
						//else score+=0 //// |□●●□▼●●□●●|下一步就长连
					}

				}
				else if (a[i].second.first != -1)//i方向为空
				{
					//|▼●●□●|
					if (tx.first == 1) {
						score += 6000; num4++;
					}
					//|▼●●□●●|
					//else if(tx.first){}//下一步长连，无贡献
					//|▼●●□|
					//else if(!tx.first){}
					else if (tx.second.first != -1)score += 300;//冲三/|▼●●□□
				}
				else if (a[i + 1].second.first != -1)//i+1方向为空
				{
					//同理
					if (ty.first == 1) {
						score += 6000; num4++;
					}
					else if (ty.second.first != -1)score += 300;//冲三
				}
				//else //两个方向都堵了，则没有贡献

			}
			else if (a[i].first + a[i + 1].first == 1) {
				//▼●
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1方向都为空
					//□▼●□
					//if(!tx.first&&!ty.first) s+=0
					if (tx.second.first != -1 && tx.first == 1) {//为活的且有一个字
						num3++;//活三□▼●□●□
						score += 2000;
						if (ty.second.first != -1 && ty.first == 1)score += 800;
						//□●□▼●□●□的情况被筛掉了，因为这里是禁手的话，对黑方太严格了
					}
					else if (ty.second.first != -1 && ty.first == 1)num3++, score += 2000;

					//□□▼●□
					else if (tx.first + ty.first == 0 && (ty.second.first != -1 || tx.second.first != -1))score += 300, num2++;
					
					//else均为0贡献
				}
				if (tx.first == 2)score += 6000, num4++;//四 ▼●□●●
				if (ty.first == 2)score += 6000, num4++;//四 ▼●□●●
				
				
				//else的情况都是靠近长连，无贡献
				//●●□▼●□●●为禁手，因为必胜了

			}
			else {//a[i].first + a[i + 1].first == 0  |▼|

				if (tx.first == 2) {//▼□●●
					if (a[i + 1].second.first != -1 && tx.second.first != -1)//双向为空 □▼□●●□
					{//□▼□●●□ 活三
						score += 2000, num3++;
						if (ty.first == 2 && ty.second.first != -1)score += 800; // 双向为空 □●●□▼□●●□，非禁手，因为非必胜
					}
					else if (tx.second.first != -1 || a[i + 1].second.first != -1)score += 300;//冲3  □▼□●●|
				}
				else if (ty.first == 2) {//●●□▼ tx!=2 && ty==2
					if (a[i].second.first != -1 && ty.second.first != -1)//双向为空 □●●□▼□
					{
						score += 3000, num3++;
					}
					else if (ty.second.first != -1 || a[i].second.first != -1)score += 300;//冲3  |▼□●●□
				}
				if (tx.first == 3)score += 6000, num4++;// ▼□●●●
				if (ty.first == 3)score += 6000, num4++;//●●●□▼
				if (tx.first == 1 && a[i + 1].second.first != -1) {
					if(tx.second.first!=-1|| ty.second.first != -1) score += 200, num2++;//●□▼□□
				}
				if (ty.first == 1 && a[i].second.first != -1) {
					if (tx.second.first != -1 || ty.second.first != -1) score += 200, num2++;//●□▼□□
				}
				//●●●□▼□●●●算是禁手

				// □□▼□□等价于 ▼ s+=20
				else if (tx.second.first != -1 && ty.second.first != -1)score += 20;
				//else 没贡献
			}


		}

		if (num3 > 1 || num4 > 1)return -1000000;//禁手
		else if (num3 == 1 && num4 == 1)score += 50000;
		else if (num3 + num4 == 0)score = score * (num2+1);
	}


	else//白色
	{
	/*
	0	  6 	5

	2	(x,y)	3

	4	  7		1


	*/
	//flag为方位
		for (int i = 0; i < 8; i += 2)
		{
			a[i] = the_number_of_cloors_pve(i, 1, x, y);
			a[i + 1] = the_number_of_cloors_pve(i + 1, 1, x, y);
			if (a[i].first + a[i + 1].first >= 4) {//获胜
				return max_score[1];//-100000
			}
			if (a[i].second.first == -1 && a[i + 1].second.first == -1) {
				//score += 0;//此时是死路，无贡献
				continue;
			}
			tx = ty = { 0,{0,0} };
			if (a[i].second.first != -1) {
				tx = the_number_of_cloors_pve(i, 1, a[i].second.first, a[i].second.second);
			}
			if (a[i + 1].second.first != -1)ty = the_number_of_cloors_pve(i + 1, 1, a[i + 1].second.first, a[i + 1].second.second);


			if (a[i].first + a[i + 1].first == 3) {
				//such as :●▼●●etc
				if (a[i].second.first != -1) {
					num4++;//四
					if (a[i + 1].second.first != -1)score += -50000;//活4
					else score += -6000;//冲四
				}
				else if (a[i + 1].second.first != -1)score += -6000, num4++;//四
				//else 的情况= 两头都是堵着的=没贡献=score+=0
			}

			else if (a[i].first + a[i + 1].first == 2) {
				//such as :▼●●etc
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1方向都为空
					if (!tx.first && !ty.first) {// |□▼●●□|
						score += -3000;//活三+3000
						num3++;
					}
					else
					{
						if (tx.first >= 1)// ▼●●□●●|
						{
							score += -6000;
							num4++;//四,或即将长连
						}
						if (ty.first >= 1 ) // ▼●●□●●|
						{//|□▼●●□●|
							score += -6000;
							num4++;//四
						}
					}

				}
				else if (a[i].second.first != -1)//i方向为空
				{
					//|▼●●□●●|
					if (tx.first >= 1) {
						score += -6000; num4++;
					}
				
					//|▼●●□|
					//else if(!tx.first){}
					else if (tx.second.first != -1)score += -300;//冲三/|▼●●□□
				}
				else if (a[i + 1].second.first != -1)//i+1方向为空
				{
					//同理
					if (ty.first >= 1) {
						score += -6000; num4++;
					}
					else if (ty.second.first != -1)score += -300;//冲三
				}
				//else //两个方向都堵了，则没有贡献 ,实际上不可能有，前面判过了

			}
			else if (a[i].first + a[i + 1].first == 1) {
				//▼●
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1方向都为空
					//□▼●□
					//if(!tx.first&&!ty.first) s+=0
					if (tx.second.first != -1 && tx.first == 1) {//为活的且有一个字
						num3++;//活三□▼●□●□
						score += -2000;
						if (ty.second.first != -1 && ty.first == 1)score += -800;
						//□●□▼●□●□的情况被筛掉了，因为这里是禁手的话，对黑方太严格了
					}
					else if (ty.second.first != -1 && ty.first == 1)num3++, score += -2000;
				}
				if (tx.first >= 2)score += -6000, num4++;//四 ▼●□●●
				if (ty.first >= 2)score += -6000, num4++;//四 ▼●□●●
				else if (tx.first + ty.first == 0 && (ty.second.first != -1 || tx.second.first != -1))score += -300, num2++;

				//else的情况都是靠近长连，无贡献
				//●●□▼●□●●为禁手，因为必胜了

			}
			else {//a[i].first + a[i + 1].first == 0  |▼|

				if (tx.first == 2) {//▼□●●
					if (a[i + 1].second.first != -1 && tx.second.first != -1)//双向为空 □▼□●●□
					{
						//□▼□●●□ 活三
						score += -2000, num3++;
						if (ty.first == 2 && ty.second.first != -1)score += -800; // 双向为空 □●●□▼□●●□，非禁手，因为非必胜
					}
					else if (tx.second.first != -1 || a[i + 1].second.first != -1)score += -800;//冲3  □▼□●●|
				}
				else if (ty.first == 2) {//●●□▼ tx!=2 && ty==2
					if (a[i].second.first != -1 && ty.second.first != -1)//双向为空 □●●□▼□
					{
						score += -3000, num3++;
					}
					else if (ty.second.first != -1 || a[i].second.first != -1)score += -800;//冲3  |▼□●●□
				}
				if (tx.first >= 3)score += -6000, num4++;// ▼□●●●
				if (ty.first >= 3)score += -6000, num4++;//●●●□▼
				if (tx.first == 1 && a[i + 1].second.first != -1) {
					if (tx.second.first != -1 || ty.second.first != -1) score += -200, num2++;//●□▼□□
				}
				if (ty.first == 1 && a[i].second.first != -1) {
					if (tx.second.first != -1 || ty.second.first != -1) score += -200, num2++;//●□▼□□
				}
				//●●●□▼□●●●算是禁手

				// □□▼□□等价于 ▼ s+=2
				else if (tx.second.first != -1 && ty.second.first != -1)score -= 2;
				//else 没贡献
			}


		}

		if (num3 + num4 >1)score += -50000;//双三或双四或三四
		else if (num3 + num4 == 0)score = score * (num2  + 1);
	}


	return score+(num4>0);//score正常情况下都是偶数，如果是奇数说明有“四”
}




pair<int, pair<int, int> > mode_of_wuzi_pve::the_number_of_cloors_pve(int flag, bool cloor, int x, int y) {//查询八个方向上同色的棋子数量
	/*
	0	  6 	5

	2	(x,y)	3

	4	  7		1


	*/
	//flag为方位


	int ans = 0;
	int tp = cloor ? 11 : 9;
	int retp = cloor ? 9 : 11;//tp的反
	int tx = -1, ty = -1;//-1为非空位置，其他都为空位子
	switch (flag)
	{
	case 0:
		for (int i = 1; i < 5; i++) {//最多判断到第4个就够了
			if (x - i < 0 || y - i < 0)break;
			if (borad.vt_board[x - i][y - i] == tp)ans++;
			else if (borad.vt_board[x - i][y - i] == retp)break;
			else {
				tx = x - i, ty = y - i;
				break;
			}
		}
		break;
	case 1:
		for (int i = 1; i < 5; i++) {
			if (x + i > 14 || y + i > 14)break;
			if (borad.vt_board[x + i][y + i] == tp)ans++;
			else if (borad.vt_board[x + i][y + i] == retp)break;
			else {
				tx = x + i, ty = y + i;

				break;
			}
		}
		break;

	case 2:
		for (int i = 1; i < 5; i++) {
			if (y - i < 0)break;
			if (borad.vt_board[x][y - i] == tp)ans++;
			else if (borad.vt_board[x][y - i] == retp)break;
			else {
				tx = x, ty = y - i;
				break;
			}
		}
		break;

	case 3:
		for (int i = 1; i < 5; i++) {
			if (y + i > 14)break;
			if (borad.vt_board[x][y + i] == tp)ans++;
			else if (borad.vt_board[x][y + i] == retp)break;
			else {
				tx = x, ty = y + i;
				break;
			}
		}
		break;

	case 4:
		for (int i = 1; i < 5; i++) {
			if (x + i > 14 || y - i < 0)break;
			if (borad.vt_board[x + i][y - i] == tp)ans++;
			else if (borad.vt_board[x + i][y - i] == retp)break;
			else {
				tx = x + i, ty = y - i;
				break;
			}
		}
		break;
	case 5:
		for (int i = 1; i < 5; i++) {
			if (x - i < 0 || y + i > 14)break;
			if (borad.vt_board[x - i][y + i] == tp)ans++;
			else if (borad.vt_board[x - i][y + i] == retp)break;
			else {
				tx = x - i, ty = y + i;
				break;
			}
		}
		break;


	case 6:
		for (int i = 1; i < 5; i++) {
			if (x - i < 0)break;
			if (borad.vt_board[x - i][y] == tp)ans++;
			else if (borad.vt_board[x - i][y] == retp)break;
			else {
				tx = x - i, ty = y;
				break;
			}
		}
		break;

	case 7:
		for (int i = 1; i < 5; i++) {
			if (x + i > 14)break;
			if (borad.vt_board[x + i][y] == tp)ans++;
			else if (borad.vt_board[x + i][y] == retp)break;
			else {

				tx = x + i, ty = y;
				break;
			}
		}
		break;

	default:
		break;
	}
	return { ans,{tx,ty} };
}






