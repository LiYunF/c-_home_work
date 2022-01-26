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
#include "wuzi_borad.h"
#include "chess.h"


void borad_wuzi::get_new_play() {
	vt_board = get_init_board(size_of_borad);
	vt_board_sorce = get_init_score(size_of_borad);
	while (!s_process.empty())s_process.pop();
}




bool borad_wuzi::check_pieces_legitimate(bool cloor, int x, int y) {//�ж������Ƿ�Ϸ�,1Ϊ�Ϸ���0Ϊ�Ƿ�
	if (x < 0 || x>size_of_borad-1) {
		printf("!!!!!!!!!!!!!!!!!!!!��ע���������ݷ�Χ!!!!!!!!!!!!!!!!!!!!!\n"); return 0;
	}
	if (y < 0 || y>size_of_borad - 1) {
		printf("!!!!!!!!!!!!!!!!!!!!��ע���������ݷ�Χ!!!!!!!!!!!!!!!!!!!!!\n"); return 0;
	}
	if (vt_board[x][y] >= 9 && vt_board[x][y] <= 12)//���¹���
	{
		printf("!!!!!!!!!!!!!!!!!!!!���ڿհ���������!!!!!!!!!!!!!!!!!!!!!!!\n"); return 0;
	}
	return 1;
}

pair<int,pair<int,int> >  borad_wuzi::the_number_of_cloors(int flag, bool cloor,int x, int y ) {//��ѯ�˸�������ͬɫ����������
	/*
	0	  2		4	

	6	(x,y)	7

	5	  3		1
	
	
	*/
	//flagΪ��λ
	
	
	int ans = 0;
	int tp = cloor ? 11 : 9;
	int retp = cloor ? 9 : 11;//tp�ķ�
	int tx=-1,ty = -1;//-1Ϊ�ǿ�λ�ã�������Ϊ��λ��
	switch (flag)
	{
	case 0:
		for (int i = 1; i <5; i++) {//����жϵ���4���͹���
			if (x - i < 0 || y - i < 0)break;
			if (vt_board[x - i][y - i] == tp)ans++;
			else if (vt_board[x - i][y - i] == retp)break;
			else {
				tx = x - i, ty = y - i;
				break;
			}
		}
		break;
	case 1:
		for (int i = 1; i < 5; i++) {
			if (x + i > 14 || y + i > 14)break;
			if (vt_board[x + i][y + i] == tp)ans++;
			else if (vt_board[x + i][y + i] == retp)break;
			else {
				tx = x + i, ty = y + i;

				break;
			}
		}
		break;

	case 2:
		for (int i = 1; i < 5; i++) {
			if ( y - i <0)break;
			if (vt_board[x][y - i] == tp)ans++;
			else if (vt_board[x][y - i] == retp)break;
			else {
				tx = x, ty = y - i;
				break;
			}
		}
		break;

	case 3:
		for (int i = 1; i < 5; i++) {
			if (y + i > 14)break;
			if (vt_board[x][y + i] == tp)ans++;
			else if (vt_board[x][y + i] == retp)break;
			else {
				tx = x, ty = y + i;
				break;
			}
		}
		break;

	case 4:
		for (int i = 1; i < 5; i++) {
			if (x + i > 14 || y - i < 0)break;
			if (vt_board[x + i][y - i] == tp)ans++;
			else if (vt_board[x + i][y - i] == retp)break;
			else {
				tx = x+i, ty = y - i;
				break;
			}
		}
		break;
	case 5:
		for (int i = 1; i < 5; i++) {
			if (x - i <0  || y + i > 14)break;
			if (vt_board[x - i][y + i] == tp)ans++;
			else if (vt_board[x - i][y + i] == retp)break;
			else {
				tx = x - i, ty = y + i;
				break;
			}
		}
		break;


	case 6:
		for (int i = 1; i < 5; i++) {
			if (x - i < 0)break;
			if (vt_board[x - i][y] == tp)ans++;
			else if (vt_board[x - i][y] == retp)break;
			else {
				tx = x - i, ty = y;
				 break;
			}
		}
		break;

	case 7:
		for (int i = 1; i < 5; i++) {
			if (x + i > 14)break;
			if (vt_board[x + i][y] == tp)ans++;
			else if (vt_board[x + i][y] == retp)break;
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


bool borad_wuzi::check_the_winer(bool cloor, int x, int y) {
	int maxx = 0;
	for (int i = 0; i < 8; i+=2) {
		maxx = max(maxx, the_number_of_cloors(i,cloor,x, y).first+ the_number_of_cloors(i+1,cloor, x, y).first);
	}
	return maxx >= 4;
}

bool borad_wuzi::check_jinshou(int x, int y) {//only black
	//�ϸ񷵻�0��Υ���˽��ֹ����򷵻�1
	pair<int,pair<int,int> >  a[8];
	pair<int, pair<int, int> > tx, ty;
	int num3, num4; num3 = num4 = 0;
	for (int i = 0; i < 8; i += 2) {
		a[i]=the_number_of_cloors(i, 0, x, y);
		a[i+1] = the_number_of_cloors(i + 1, 0, x, y);
		if (a[i].first + a[i + 1].first >=5)return 1;//����
		
		tx = ty = { 0,{0,0} };
		if (a[i].second.first!=-1) {
			tx = the_number_of_cloors(i, 0, a[i].second.first ,  a[i].second.second);
		}
		if(a[i+1].second.first != -1)ty = the_number_of_cloors(i+1, 0, a[i+1].second.first,  a[i+1].second.second);
		
		//ͳ�ƻ��� ��Ϊ�հף���Ϊ��ǰλ��,��Ϊͬɫ���ӣ���Ϊ����
		if (a[i].second.first != -1 && a[i + 1].second.first != -1)
		{//��֤���߶��ǿյ�λ�ã����ǲ������ӵ�λ��

			//  ���������� 
			if (a[i].first + a[i + 1].first == 0) {
				if (tx.second.first != -1 && tx.first == 2) {//Ϊ������ж�����
					num3++;
				}
				else if (ty.second.first != -1 && ty.first == 2)num3++;
			}
			
			//���񨋡���� and ����������
			if (a[i].first + a[i + 1].first == 1) {
				if (tx.second.first != -1 && tx.first == 1) {//Ϊ�������һ����
					
					num3++;
				}
				else if (ty.second.first != -1 && ty.first == 1)num3++;
				//��ô������񨋡���� and ���������������������������𣿣�����
				//�����ҵ��߼�Ϊ���ǽ��֣���Ϊ�о������Ժ��岻̫��ƽ��
				//��Ȼ����������3����ʵ���ϰ�����뿿�������ǵ�����һ����λ����һͷ����һ����3��
			}

			//�����񨋡� ���� and ������������
			if (a[i].first + a[i + 1].first == 2&&!tx.first && !ty.first)num3++;

		}
		


		//ͳ������
		if (a[i].first + a[i + 1].first == 3) {
			//such as :�񨋡��etc 
			//ֻҪ�������ģ����߽磩|�񨋡�� ��Ӧ�ö���
			if (a[i].second.first != -1 || a[i + 1].second.first != -1)num4++;
		}
		else if (a[i].first + a[i + 1].first == 2) {
			if (a[i].second.first != -1 && tx.first == 1)num4++;
			if (a[i+1].second.first != -1 && ty.first == 1)num4++;
			//��ô����񨋡���� �������������𣿣�����
				//�����ҵ��߼�Ϊ�ǽ��֣���Ϊ
				//��2���ģ��Ҷ�סһͷ֮�󣬺�����Ȼ��Ӯ
		}
		else if (a[i].first + a[i + 1].first == 1) {
			if (a[i].second.first != -1 && tx.first == 2)num4++;
			if (a[i + 1].second.first != -1 && ty.first == 2)num4++;
		}

	}
	if (num3 > 1 || num4 > 1)return 1;


	return 0;
}





int borad_wuzi::put_chess_pieces(bool cloor, int x, int y) {
	//�������Ӻ���,����0����ʧ�ܣ�����1���óɹ�������2�ɹ��һ�ʤ,����3��˵��Υ�����ֹ��� ����4˵��ƽ��
	//cloor=0Ϊ��,1Ϊ��

	if (!check_pieces_legitimate(cloor, x, y))return 0;


	vt_board[x][y] = cloor ? 11 : 9;//����
	
	/*
	if (!s_process.empty()) {//�޸���һ������״,����Ҫ���޸����жϽ���
		chess temp;
		int tx, ty;
		temp = s_process.top();
		tx = temp.x, ty = temp.y;
		bool cloor_s_temp = temp.cloor;
		vt_board[tx][ty] = cloor_s_temp ? 11 : 9;
	}
	*/
	
	chess temp;
	temp.cloor = cloor;
	temp.x = x, temp.y = y;
	temp.val = 0;
	s_process.push(temp);

	//�ж��Ƿ���Ϸ����
	if (!cloor&&check_jinshou(x, y)) {
		return 3;
	}
	if (check_the_winer(cloor, x, y)) {
		return 2;
	}
	if (s_process.size() == size_of_borad * size_of_borad)return 4;//û�ط������ˣ��Ǿ�ƽ����
	return 1;
}


bool borad_wuzi::get_back(int cyc_number) {
	if (s_process.size() < cyc_number) {
		
		return 0;
	}
	
	for (int i = 0; i < cyc_number; i++) {
		chess temp = s_process.top();
		//if(temp.cloor==0)//black
		if (temp.x == 0) {
			if(temp.y==0)
				vt_board[temp.x][temp.y]=0;
			else if(temp.y==14)
				vt_board[temp.x][temp.y] = 2;
			else 
				vt_board[temp.x][temp.y] = 1;
		}
		if (temp.x == 14) {
			if (temp.y == 0)
				vt_board[temp.x][temp.y] = 6;
			else if (temp.y == 14)
				vt_board[temp.x][temp.y] = 8;
			else
				vt_board[temp.x][temp.y] = 7;
		}
		else  {
			if (temp.y == 0)
				vt_board[temp.x][temp.y] = 3;
			else if (temp.y == 14)
				vt_board[temp.x][temp.y] = 5;
			else
				vt_board[temp.x][temp.y] = 4;
		}

		//do something about the val?

		s_process.pop();

	}
	
	return 1;
}





/*
	


*/











