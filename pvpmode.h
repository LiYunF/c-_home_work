//#pragma once
#ifdef PVP_OF_WUZI
#else

#define PVP_OF_WUZI

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

using namespace std;

class mode_of_wuzi_pvp:public judge {
protected:
	player somebody[2];
	int now_player;
public:
	mode_of_wuzi_pvp() {
		somebody[0].tag = somebody[1].tag = "human";
		somebody[0].name = "black"; somebody[1].name = "white";
		somebody[0].cloor = 0; somebody[1].cloor = 1;
		now_player = 0;//∫⁄∆Âœ» ÷
	}
	void v_play_wuzi_game();

	



};





#endif // DEBUG










