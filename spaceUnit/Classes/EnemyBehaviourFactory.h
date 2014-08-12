//
//  EnemyBehaviourFactory.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyBehaviourFactory_h
#define spaceUnit_EnemyBehaviourFactory_h

public class EnemyBehaviourFactory {
    
	public static AEnemyBehaviour createBehaviour(EBehaviourENUM behaviourName, Enemy enemy,
                                                  SpaceObject target, BehaviourOptions options) {
		AEnemyBehaviour result;
		if (behaviourName == EBehaviourENUM.FOLLOW) {
			result = new EnemyFollowBehaviour(enemy, target);
		} else
            if (behaviourName == EBehaviourENUM.ALARM) {
                result = new EnemyAlarmBehaviour(enemy, target, options);
            } else
                if (behaviourName == EBehaviourENUM.ACTIVATE) {
                    result = new EnemyActivateBehaviour(enemy);
                } else
                    if (behaviourName == EBehaviourENUM.SHOOT) {
                        result = new EnemyShootBehaviour(enemy, target, options);
                    } else
                        if (behaviourName == EBehaviourENUM.ALIEN) {
                            result = new EnemyAlienBehaviour(enemy, target, options);
                        } else
                            if (behaviourName == EBehaviourENUM.CRAZY_MINE) {
                                result = new EnemyCrazyMineBehaviour(enemy, options);
                            }
        
                            else {
                                throw new Error("Unknown behaviour");
                            }
        
		return result;
	}
    
	public static AEnemyBehaviour createBehaviour(EBehaviourENUM behaviourName, Enemy enemy,
												  SpaceObject target) {
		return createBehaviour(behaviourName, enemy, target, null);
	}
    
	public static AEnemyBehaviour createBehaviour(EBehaviourENUM behaviourName, Enemy enemy) {
		return createBehaviour(behaviourName, enemy, null, null);
	}
};

#endif
