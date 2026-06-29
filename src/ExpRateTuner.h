//  Author: Nathan Handley (nathanhandley@protonmail.com)
//  Copyright (c) 2026 Nathan Handley
//
//  This program is free software; you can redistribute it and/or modify it
//  under the terms of the GNU Affero General Public License as published by the
//  Free Software Foundation; either version 3 of the License, or (at your
//  option) any later version.
//  
//  This program is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.See the GNU Affero General Public License for
//  more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef EXPRATETUNER_H
#define EXPRATETUNER_H

#include "Common.h"
#include "Player.h"

#include <vector>
#include <map>
#include <set>

class ExpRateTunerMod
{
private:
    ExpRateTunerMod();

public:
    static ExpRateTunerMod* instance()
    {
        static ExpRateTunerMod instance;
        return &instance;
    }
    ~ExpRateTunerMod();

    bool IsEnabled;
    bool DisplayMessageRateOnLogin;
    std::map<ObjectGuid::LowType, uint32> ExpRateByPlayerGUID;

    uint32 GetExpRateForPlayer(Player* player);
    void LoadExpRateForPlayer(Player* player);
    void SetExpRateForPlayer(Player* player, uint32 expRate);
    void AnnounceCurrentExpRate(Player* player);
    void PerformPlayerDelete(ObjectGuid guid);
};

#define ExpRateTuner ExpRateTunerMod::instance()

#endif //EXPRATETUNER_H
