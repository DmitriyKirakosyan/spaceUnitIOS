//
//  AlarmBehaviourOptions.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//



#ifndef spaceUnit_AlarmBehaviourOptions_h
#define spaceUnit_AlarmBehaviourOptions_h

#include "BehaviourOptions.h"
#include "AEnemyBehaviour.h"
#include <list>
class AlarmBehaviourOptions : public BehaviourOptions {
public:
    
    float distance;
    std::list<AEnemyBehaviour *> executeBehaviours;
    
    AlarmBehaviourOptions(float distance, AEnemyBehaviour * behaviours[], int size) : BehaviourOptions(){
        this->distance = distance;
        for(int i = 0; i < size; i++) {
            executeBehaviours.push_back(behaviours[i]);
        }
    }
};


#endif
