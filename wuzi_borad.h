//#pragma once
#ifdef WUZI_BORAD_GAME
#else

#define WUZI_BORAD_GAME

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

class borad_wuzi :public draw_b 
{
public:
	

public:

	inline void print_bd() {//»­³öÆåÅÌ
		draw_board();
	}

	void get_new_play();
	bool check_pieces_legitimate(bool, int, int);//·¶Î§
	bool check_the_winer(bool, int, int);
	pair<int,pair<int,int> > the_number_of_cloors(int, bool, int, int);

	int put_chess_pieces(bool, int, int);//ÏÂÆå
	bool get_back(int);//»ÚÆå

	bool check_jinshou(int , int );//½ûÊÖ


};





#endif  //WUZI_BORAD_GAME


