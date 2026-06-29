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

#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"

#include "ExpRateTuner.h"

using namespace std;

class ExpRateTuner_PlayerScript : public PlayerScript
{
public:
    ExpRateTuner_PlayerScript() : PlayerScript("ExpRateTuner_PlayerScript") {}

    void OnPlayerLogin(Player* player) override
    {
        if (ExpRateTuner->IsEnabled == false)
            return;
        ExpRateTuner->LoadExpRateForPlayer(player);
        ExpRateTuner->AnnounceCurrentExpRate(player);
    }

    void OnPlayerLogout(Player* player) override
    {
        ExpRateTuner->ExpRateByPlayerGUID.erase(player->GetGUID().GetCounter());
    }

    void OnPlayerDelete(ObjectGuid guid, uint32 /*accountId*/) override
    {
        ExpRateTuner->PerformPlayerDelete(guid);
    }

    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* /*victim*/, uint8 xpSource) override
    {
        if (ExpRateTuner->IsEnabled == false)
            return;
        // Only kill-based experience is tuned for now, leaving quest/explore/battleground gains untouched
        if (xpSource != XPSOURCE_KILL)
            return;
        uint32 expRate = ExpRateTuner->GetExpRateForPlayer(player);
        amount = (uint32)((uint64)amount * expRate / 100);
    }
};

void AddExpRateTunerPlayerScript()
{
    new ExpRateTuner_PlayerScript();
}
