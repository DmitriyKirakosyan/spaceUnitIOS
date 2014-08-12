//
//  Score.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_Score_h
#define spaceUnit_Score_h

#include "GameStatus.h"
#include <stdio.h>

class Score {
public:
	static int SECONDS;
	static int KILLS;
    
	int type;
	int score;
    
	static int getScoreTypeByGameType(int gameType) {
		if (gameType == SHOOT_GAME) {
            return KILLS;
        } else {
            return SECONDS;
        }
	}
    
	Score(int type, float score) {
		this->type = type;
		this->score = score;
	}
    
	void getPrintableScore(char *scoreStr) {
		if (type == SECONDS) {
			float cutedScore = ((int)(score / 10))/100.0f;
			int s = (int) (cutedScore);
			int m = (int) (s / 60.0f);
			int ms = (int) ((cutedScore - s) * 10);
			s = (int) (s % 60);
            
            char m_time[5], s_time[5], ms_time[5];
            stringifyTime(m, m_time);
            stringifyTime(s, s_time);
            stringifyTime(ms, ms_time);
            
            sprintf(scoreStr, "%s:%s:%s", m_time, s_time, ms_time);
		} else {
            sprintf(scoreStr, "%d", score);
        }
	}
    
	void stringifyTime(int time, char *timeStr) {
        if(time < 10) {
            sprintf(timeStr, "0%d", time);
        } else {
            sprintf(timeStr, "%d", time);
        }
	}
    
};
#endif
