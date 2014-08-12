//
//  GameStrategyFactory.h
//  spaceUnit
//
//  Created by PC on 8/9/14.
//
//

#ifndef spaceUnit_GameStrategyFactory_h
#define spaceUnit_GameStrategyFactory_h


class GameStrategyFactory {
    
	/**
	 *
	 * @param ship
	 * @param gameType
	 * @return
	 * @throws Error "unknown game type"
	 */
public:
    static GameStrategy *createStrategy(cocos2d::CCNode* screenContainer, Ship *ship, int gameType)
	{
		GameStrategy *result;
		if (gameType == RUN_GAME) {
			result = new GameRunStrategy(screenContainer, ship, gameType);
		} else if (gameType == SHOOT_GAME) {
			result = new GameShootStrategy(screenContainer, ship, gameType);
		} else {
            //throw new Error("unknown game type");
        }
		return result;
	}
};

#endif
