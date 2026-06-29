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

#include "Configuration/Config.h"
#include "Chat.h"
#include "ScriptMgr.h"
#include "Player.h"

#include "ExpRateTuner.h"

using namespace std;

const uint32 EXP_RATE_TUNER_DEFAULT_RATE = 100;

ExpRateTunerMod::ExpRateTunerMod() :
    IsEnabled(true),
    DisplayMessageRateOnLogin(true)
{
}

ExpRateTunerMod::~ExpRateTunerMod()
{

}

uint32 ExpRateTunerMod::GetExpRateForPlayer(Player* player)
{
    auto rateIter = ExpRateByPlayerGUID.find(player->GetGUID().GetCounter());
    if (rateIter != ExpRateByPlayerGUID.end())
        return rateIter->second;
    // Default to the normal rate when no preference has been stored or loaded
    return EXP_RATE_TUNER_DEFAULT_RATE;
}

void ExpRateTunerMod::LoadExpRateForPlayer(Player* player)
{
    uint32 playerGUID = player->GetGUID().GetCounter();
    uint32 expRate = EXP_RATE_TUNER_DEFAULT_RATE;
    QueryResult queryResult = CharacterDatabase.Query("SELECT `exprate` FROM mod_exp_rate_tuner_character_settings WHERE guid = {}", playerGUID);
    if (queryResult && queryResult->GetRowCount() > 0)
    {
        Field* fields = queryResult->Fetch();
        expRate = fields[0].Get<uint32>();
    }
    ExpRateByPlayerGUID[playerGUID] = expRate;
}

void ExpRateTunerMod::SetExpRateForPlayer(Player* player, uint32 expRate)
{
    uint32 playerGUID = player->GetGUID().GetCounter();
    CharacterDatabase.DirectExecute("REPLACE INTO `mod_exp_rate_tuner_character_settings` (`guid`, `exprate`) VALUES ({}, {})", playerGUID, expRate);
    ExpRateByPlayerGUID[playerGUID] = expRate;
}

void ExpRateTunerMod::AnnounceCurrentExpRate(Player* player)
{
    if (DisplayMessageRateOnLogin == false)
        return;

    // Show the current rate green when at or above the normal rate and red when reduced
    uint32 expRate = GetExpRateForPlayer(player);
    string rateFragment = expRate >= EXP_RATE_TUNER_DEFAULT_RATE ? fmt::format("|cff4CFF00{}%|r", expRate) : fmt::format("|cffff0000{}%|r", expRate);
    string text = fmt::format("Kill experience rate is currently {} for this character. Type '.exprate set <0-100>' to change it.", rateFragment);
    ChatHandler(player->GetSession()).SendSysMessage(text);
}

void ExpRateTunerMod::PerformPlayerDelete(ObjectGuid guid)
{
    uint32 playerGUID = guid.GetCounter();
    CharacterDatabase.DirectExecute("DELETE FROM mod_exp_rate_tuner_character_settings WHERE guid = {}", playerGUID);
    ExpRateByPlayerGUID.erase(playerGUID);
}
