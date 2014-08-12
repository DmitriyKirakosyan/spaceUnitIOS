//
//  Ability.cpp
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#include "Ability.h"
#include "BlowAbility.h"
#include "MultigunAbility.h"

Ability * Ability::create(int ability, Ship *heroShip, IImpactMaker *impactMaker) {
    Ability *result = NULL;
    if (ability == BLOW) {
        if (impactMaker == NULL) {
            //    throw new Error("impact maker cant be null for ability : " + ability);
        }
        result = new BlowAbility(heroShip, impactMaker);
    } else if (ability == MULTIGUN) {
        result = new MultigunAbility(heroShip);
    }
    return result;
}

Ability * Ability::create(int ability, Ship *heroShip) {
    return create(ability, heroShip, NULL);
}