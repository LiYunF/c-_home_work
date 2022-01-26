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
	//bVis[x][y] = 1;//ֻ����near
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

	//��ȡ�ٽ��㼯
	stack<chess>temp_s = borad.s_process;
	if (temp_s.empty()) {//Ϊ��ʱ��˵��û�����κ����ӣ��������ĵ�
		chess ans;
		ans.x = 7, ans.y = 7, ans.cloor = 0, ans.val = 2;
		return ans;
	}
	chess last_place = borad.s_process.top();
	bool have_4 = (get_score(last_place,last_place.cloor) % 2);

	stack<chess>().swap(stChess_near);//���near
	for (int i = 0; i < borad.size_of_borad; i++)//���bVis
		for (int j = 0; j < borad.size_of_borad; j++)
			bVis[i][j] = 0;


	while (!temp_s.empty()) {//�������ٽ��㶼�Ž���,ͬʱ����vis����
		get_near_place(temp_s.top());
		temp_s.pop();
	}
	//  |chess_near|  and  |B_vis|  is ready
	stack<chess>vChae = stChess_near;


	int nThe_optimal_scores;//��ɫ�����ɫ��С�ķ���
	nThe_optimal_scores = somebody[0].tag == "computer" ? -10000000 : 10000000;//Ϊ��������󣬷�������С
	chess ceThe_optimal_chess;//���ѡ�����
	ceThe_optimal_chess.x = -1, ceThe_optimal_chess.y = -1;
	int scores;
	while (!vChae.empty()) {
		chess i = vChae.top();//65 a9
		if (somebody[0].tag == "computer")//������Ϊ����ʱ����������
		{

			scores = dfs_game_tree(i, 1, 0, have_4, nThe_optimal_scores);//��dfs�����Զ������������
			if (nThe_optimal_scores < scores) {
				ceThe_optimal_chess = i;
				nThe_optimal_scores = scores;
				if (nThe_optimal_scores >= 1000000)break;
			}
		}
		else//Ϊ��ɫ����min
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
			9:��    blak_put
			10����	last blak put
			11:	��	white put
			12:	��  last white put
	*/
	int ans_score= get_score(now, cloor);
	if (ans_score == 1000000 || ans_score == -1000000)return ans_score;

	
	if (!last_place_have_4) {//�ж���һ���ĵ�����û����
			//���û���ģ��������ʤ̬ʱ�����ر�ʤ̬��������dfs
		if (ans_score >= 50000 || ans_score <= -50000) {
			return ans_score;
		}
	}
	else {//�����һ�����ģ�
		//���ȣ����ڲ��������ɵ�ǰ������ɫ����������Ϊ�����˾���ǰ���Ѿ�����1e6 or -1e6��
		//��ô��ǰ״̬�޷���ʤ��ֻ��ȥ����һ��������//������ֻ���жϵ�ǰ����λ���Ƿ��ܰ�����һ���ճ��������ɣ�
		//�ܴճ�������˵����ǰλ�ÿ��Զ�ס��һ��������dfs,���򷵻رذ�̬
		int ni_s = get_score(now, cloor ? 0 : 1);
		if (ni_s != 1000000 && ni_s != -1000000) {//���ܺ��ϲ��ճ�5��
			//����ans_score+nThe_optimal_scores
			ni_s = cloor ? 10000000 : -10000000;//��ǰΪ�ף�����һ���Ǻ�,+1e6��������һ��Ϊ�ף�-1e6
			return ans_score+ni_s;
		}
	}
	
	
	last_best_score -= ans_score;
	bool have_4 = (ans_score%2);//�ж��ⲽ��û�в�����

	int hold_the_msg = borad.vt_board[now.x][now.y];
	borad.vt_board[now.x][now.y] = cloor ? 11 : 9;//��ɫΪ����9������Ϊ����11

	int nera_number = get_near_place(now);//��õ�ǰ�ڵ㸽���Ŀսڵ����
	stack<chess>vChae = stChess_near;//��ȡnearջ

	int nThe_optimal_scores;//��ɫ�����ɫ��С�ķ���
	nThe_optimal_scores = cloor ? -10000000 : 10000000;//��ǰΪ�ڣ�����һ��Ϊ�ף��׷�����Ϊ������С����
	chess ceThe_optimal_chess;//���ѡ�����
	ceThe_optimal_chess.x = -1, ceThe_optimal_chess.y = -1;


	while (!vChae.empty()) {
		chess i = vChae.top();
		if (borad.vt_board[i.x][i.y] < 9)//�����߹��ĵ��ʱ��
		{
			if (cloor)//��ǰΪ����ʱ����һ��Ϊ�ڣ�������max
			{
				int scores = dfs_game_tree(i, deep + 1, 0, have_4, nThe_optimal_scores);

				if (nThe_optimal_scores < scores) {//�˴�����һ��ľ���
					ceThe_optimal_chess = i;
					nThe_optimal_scores = scores;
					//�����ǰ��壬�����Ƿ��ص�ֵΪ��С�ģ�Ҳ����˵��
					//�ϲ��last_best_score���ϲ�ö�ٵĵ�ǰ����Сֵ
					//�������������ֵ����ô��nThe_optimal_scores+ans_score>last_best_scoreʱ���Ͳ���ö����,
					//��������last-=score , ����Ҫע��,����nThe_optimal_scores=last_best_score=-1e7
					if (nThe_optimal_scores > last_best_score)break;
				}

				
			}
			else//Ϊ��ɫ����һ��Ϊ�ף�Ҫ����min
			{
				int scores = dfs_game_tree(i, deep + 1, 1, have_4, nThe_optimal_scores);//��dfs�����Զ������������
				if (nThe_optimal_scores > scores) {
					ceThe_optimal_chess = i;
					nThe_optimal_scores = scores;
					//�����Ǻ��壬�����Ƿ��ص�ֵΪ���ģ�Ҳ����˵��
					//�ϲ��last_best_score���ϲ�ö�ٵĵ�ǰ�����ֵ
					//������������Сֵ����ô��nThe_optimal_scores<last_best_score-ans_scoreʱ���Ͳ���ö����
					if (nThe_optimal_scores < last_best_score)break;
				}
			}
		}
		vChae.pop();
	}

	//����
	borad.vt_board[now.x][now.y] = hold_the_msg;
	chess tempq;
	while (nera_number--) {
		tempq = stChess_near.top();
		bVis[tempq.x][tempq.y] = 0;
		stChess_near.pop();
	}

	//ans_score+
	return  ans_score + nThe_optimal_scores;//���ص�ǰ��ķ���+��һ�����ŵķ���
}

int mode_of_wuzi_pve::get_score(chess now, bool cloor) {
	//�������÷֣����帺�÷�
	int max_score[2] = {1000000,-1000000};//100000Ϊʤ����-100000Ϊʧ��
	int x = now.x, y = now.y;
	pair<int, pair<int, int> >  a[8];
	pair<int, pair<int, int> > tx, ty;
	int num3, num4, num2; num2 = num3 = num4 = 0;
	
	int score = 0;

	if (!cloor) {//Ϊ��,֮�����������ֱ����cloor����Ϊ�˼����������,
		//����Ҫд�ܶ�if else ���߽��кܶ�γ˷�����

		/*
	0	  6 	5

	2	(x,y)	3

	4	  7		1


	*/
		for (int i = 0; i < 8; i += 2) {
			a[i] = the_number_of_cloors_pve(i, 0, x, y);
			a[i + 1] = the_number_of_cloors_pve(i + 1, 0, x, y);
			if (a[i].first + a[i + 1].first >= 5) {//����
				return max_score[1];//-100000
			}
			else if (a[i].first + a[i + 1].first == 4) {
				return max_score[0];//��ʤ,��Ϊ����ai��ai+1��û�м���chess now��
				//��������Ҫ�ߵģ�����4+1=5��
			}
			if (a[i].second.first == -1 && a[i + 1].second.first == -1) {
				//score += 0;//��ʱ����·���޹���
				continue;
			}
			tx = ty = { 0,{0,0} };
			if (a[i].second.first != -1) {
				tx = the_number_of_cloors_pve(i, 0, a[i].second.first, a[i].second.second);
			}
			if (a[i + 1].second.first != -1)ty = the_number_of_cloors_pve(i + 1, 0, a[i + 1].second.first, a[i + 1].second.second);


			if (a[i].first + a[i + 1].first == 3) {
				//such as :�񨋡��etc
				if (a[i].second.first != -1) {
					num4++;//��
					if (a[i + 1].second.first != -1)score += 50000;//��4
					else score += 6000;//����
				}
				else if (a[i + 1].second.first != -1)score += 6000, num4++;//��
				//else �����= ��ͷ���Ƕ��ŵ�=û����=score+=0
			}

			else if (a[i].first + a[i + 1].first == 2) {
				//such as :�����etc
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1����Ϊ��
					if (!tx.first && !ty.first) {// |��������|
						score += 3000;//����+3000
						num3++;
					}
					else
					{
						if (tx.first == 1 && ty.first == 1)// |�������������|
						{
							//����-1000000
							return max_score[1];
						}
						else if (ty.first == 1 || tx.first == 1) // |?����������|->num4>1
						{//|����������|
							score += 6000;
							num4++;//����
						}
						//else score+=0 //// |���������������|��һ���ͳ���
					}

				}
				else if (a[i].second.first != -1)//i����Ϊ��
				{
					//|��������|
					if (tx.first == 1) {
						score += 6000; num4++;
					}
					//|���������|
					//else if(tx.first){}//��һ���������޹���
					//|������|
					//else if(!tx.first){}
					else if (tx.second.first != -1)score += 300;//����/|��������
				}
				else if (a[i + 1].second.first != -1)//i+1����Ϊ��
				{
					//ͬ��
					if (ty.first == 1) {
						score += 6000; num4++;
					}
					else if (ty.second.first != -1)score += 300;//����
				}
				//else //�������򶼶��ˣ���û�й���

			}
			else if (a[i].first + a[i + 1].first == 1) {
				//����
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1����Ϊ��
					//�������
					//if(!tx.first&&!ty.first) s+=0
					if (tx.second.first != -1 && tx.first == 1) {//Ϊ�������һ����
						num3++;//��������������
						score += 2000;
						if (ty.second.first != -1 && ty.first == 1)score += 800;
						//��������������������ɸ���ˣ���Ϊ�����ǽ��ֵĻ����Ժڷ�̫�ϸ���
					}
					else if (ty.second.first != -1 && ty.first == 1)num3++, score += 2000;

					//���������
					else if (tx.first + ty.first == 0 && (ty.second.first != -1 || tx.second.first != -1))score += 300, num2++;
					
					//else��Ϊ0����
				}
				if (tx.first == 2)score += 6000, num4++;//�� ��������
				if (ty.first == 2)score += 6000, num4++;//�� ��������
				
				
				//else��������ǿ����������޹���
				//������������Ϊ���֣���Ϊ��ʤ��

			}
			else {//a[i].first + a[i + 1].first == 0  |��|

				if (tx.first == 2) {//�������
					if (a[i + 1].second.first != -1 && tx.second.first != -1)//˫��Ϊ�� ����������
					{//���������� ����
						score += 2000, num3++;
						if (ty.first == 2 && ty.second.first != -1)score += 800; // ˫��Ϊ�� �����������������ǽ��֣���Ϊ�Ǳ�ʤ
					}
					else if (tx.second.first != -1 || a[i + 1].second.first != -1)score += 300;//��3  ���������|
				}
				else if (ty.first == 2) {//������ tx!=2 && ty==2
					if (a[i].second.first != -1 && ty.second.first != -1)//˫��Ϊ�� ����������
					{
						score += 3000, num3++;
					}
					else if (ty.second.first != -1 || a[i].second.first != -1)score += 300;//��3  |��������
				}
				if (tx.first == 3)score += 6000, num4++;// ��������
				if (ty.first == 3)score += 6000, num4++;//�������
				if (tx.first == 1 && a[i + 1].second.first != -1) {
					if(tx.second.first!=-1|| ty.second.first != -1) score += 200, num2++;//���������
				}
				if (ty.first == 1 && a[i].second.first != -1) {
					if (tx.second.first != -1 || ty.second.first != -1) score += 200, num2++;//���������
				}
				//����������������ǽ���

				// �����������ȼ��� �� s+=20
				else if (tx.second.first != -1 && ty.second.first != -1)score += 20;
				//else û����
			}


		}

		if (num3 > 1 || num4 > 1)return -1000000;//����
		else if (num3 == 1 && num4 == 1)score += 50000;
		else if (num3 + num4 == 0)score = score * (num2+1);
	}


	else//��ɫ
	{
	/*
	0	  6 	5

	2	(x,y)	3

	4	  7		1


	*/
	//flagΪ��λ
		for (int i = 0; i < 8; i += 2)
		{
			a[i] = the_number_of_cloors_pve(i, 1, x, y);
			a[i + 1] = the_number_of_cloors_pve(i + 1, 1, x, y);
			if (a[i].first + a[i + 1].first >= 4) {//��ʤ
				return max_score[1];//-100000
			}
			if (a[i].second.first == -1 && a[i + 1].second.first == -1) {
				//score += 0;//��ʱ����·���޹���
				continue;
			}
			tx = ty = { 0,{0,0} };
			if (a[i].second.first != -1) {
				tx = the_number_of_cloors_pve(i, 1, a[i].second.first, a[i].second.second);
			}
			if (a[i + 1].second.first != -1)ty = the_number_of_cloors_pve(i + 1, 1, a[i + 1].second.first, a[i + 1].second.second);


			if (a[i].first + a[i + 1].first == 3) {
				//such as :�񨋡��etc
				if (a[i].second.first != -1) {
					num4++;//��
					if (a[i + 1].second.first != -1)score += -50000;//��4
					else score += -6000;//����
				}
				else if (a[i + 1].second.first != -1)score += -6000, num4++;//��
				//else �����= ��ͷ���Ƕ��ŵ�=û����=score+=0
			}

			else if (a[i].first + a[i + 1].first == 2) {
				//such as :�����etc
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1����Ϊ��
					if (!tx.first && !ty.first) {// |��������|
						score += -3000;//����+3000
						num3++;
					}
					else
					{
						if (tx.first >= 1)// ���������|
						{
							score += -6000;
							num4++;//��,�򼴽�����
						}
						if (ty.first >= 1 ) // ���������|
						{//|����������|
							score += -6000;
							num4++;//��
						}
					}

				}
				else if (a[i].second.first != -1)//i����Ϊ��
				{
					//|���������|
					if (tx.first >= 1) {
						score += -6000; num4++;
					}
				
					//|������|
					//else if(!tx.first){}
					else if (tx.second.first != -1)score += -300;//����/|��������
				}
				else if (a[i + 1].second.first != -1)//i+1����Ϊ��
				{
					//ͬ��
					if (ty.first >= 1) {
						score += -6000; num4++;
					}
					else if (ty.second.first != -1)score += -300;//����
				}
				//else //�������򶼶��ˣ���û�й��� ,ʵ���ϲ������У�ǰ���й���

			}
			else if (a[i].first + a[i + 1].first == 1) {
				//����
				if (a[i].second.first != -1 && a[i + 1].second.first != -1) {//i,i+1����Ϊ��
					//�������
					//if(!tx.first&&!ty.first) s+=0
					if (tx.second.first != -1 && tx.first == 1) {//Ϊ�������һ����
						num3++;//��������������
						score += -2000;
						if (ty.second.first != -1 && ty.first == 1)score += -800;
						//��������������������ɸ���ˣ���Ϊ�����ǽ��ֵĻ����Ժڷ�̫�ϸ���
					}
					else if (ty.second.first != -1 && ty.first == 1)num3++, score += -2000;
				}
				if (tx.first >= 2)score += -6000, num4++;//�� ��������
				if (ty.first >= 2)score += -6000, num4++;//�� ��������
				else if (tx.first + ty.first == 0 && (ty.second.first != -1 || tx.second.first != -1))score += -300, num2++;

				//else��������ǿ����������޹���
				//������������Ϊ���֣���Ϊ��ʤ��

			}
			else {//a[i].first + a[i + 1].first == 0  |��|

				if (tx.first == 2) {//�������
					if (a[i + 1].second.first != -1 && tx.second.first != -1)//˫��Ϊ�� ����������
					{
						//���������� ����
						score += -2000, num3++;
						if (ty.first == 2 && ty.second.first != -1)score += -800; // ˫��Ϊ�� �����������������ǽ��֣���Ϊ�Ǳ�ʤ
					}
					else if (tx.second.first != -1 || a[i + 1].second.first != -1)score += -800;//��3  ���������|
				}
				else if (ty.first == 2) {//������ tx!=2 && ty==2
					if (a[i].second.first != -1 && ty.second.first != -1)//˫��Ϊ�� ����������
					{
						score += -3000, num3++;
					}
					else if (ty.second.first != -1 || a[i].second.first != -1)score += -800;//��3  |��������
				}
				if (tx.first >= 3)score += -6000, num4++;// ��������
				if (ty.first >= 3)score += -6000, num4++;//�������
				if (tx.first == 1 && a[i + 1].second.first != -1) {
					if (tx.second.first != -1 || ty.second.first != -1) score += -200, num2++;//���������
				}
				if (ty.first == 1 && a[i].second.first != -1) {
					if (tx.second.first != -1 || ty.second.first != -1) score += -200, num2++;//���������
				}
				//����������������ǽ���

				// �����������ȼ��� �� s+=2
				else if (tx.second.first != -1 && ty.second.first != -1)score -= 2;
				//else û����
			}


		}

		if (num3 + num4 >1)score += -50000;//˫����˫�Ļ�����
		else if (num3 + num4 == 0)score = score * (num2  + 1);
	}


	return score+(num4>0);//score��������¶���ż�������������˵���С��ġ�
}




pair<int, pair<int, int> > mode_of_wuzi_pve::the_number_of_cloors_pve(int flag, bool cloor, int x, int y) {//��ѯ�˸�������ͬɫ����������
	/*
	0	  6 	5

	2	(x,y)	3

	4	  7		1


	*/
	//flagΪ��λ


	int ans = 0;
	int tp = cloor ? 11 : 9;
	int retp = cloor ? 9 : 11;//tp�ķ�
	int tx = -1, ty = -1;//-1Ϊ�ǿ�λ�ã�������Ϊ��λ��
	switch (flag)
	{
	case 0:
		for (int i = 1; i < 5; i++) {//����жϵ���4���͹���
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






