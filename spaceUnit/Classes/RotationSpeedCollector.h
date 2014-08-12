//
//  RotationSpeedCollector.h
//  spaceUnit
//
//  Created by PC on 8/9/14.
//
//

#ifndef spaceUnit_RotationSpeedCollector_h
#define spaceUnit_RotationSpeedCollector_h

class RotationSpeedCollector {
    
public:
	static float getRotationTurboSpeed() { return 25.0f; }
    
	static float getEnemyRotation() { return (((arc4random() % 100) / 100.0f)  * 2 - 1) * 5; }
};

#endif
