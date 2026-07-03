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
#include "StringConvert.h"

#include "ExpRateTuner.h"

using namespace Acore::ChatCommands;
using namespace std;

class ExpRateTuner_CommandScript : public CommandScript
{
public:
    ExpRateTuner_CommandScript() : CommandScript("ExpRateTuner_CommandScript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> ExpRateTunerCommandTable =
        {
            { "set",  HandleExpRateSet,  SEC_PLAYER, Console::No },
        };

        static std::vector<ChatCommand> commandTable =
        {
            { "exprate", ExpRateTunerCommandTable },
        };
        return commandTable;
    }

    static bool HandleExpRateSet(ChatHandler* handler, const char* args)
    {
        if (ExpRateTuner->IsEnabled == false)
            return true;

        Player* player = handler->GetPlayer();
        if (!player)
            return true;

        // A value is required
        if (!args || !*args)
        {
            handler->PSendSysMessage("Usage: .exprate set <0-100>");
            return true;
        }

        // The rate is a whole percentage between 0 (no experience) and 100 (normal experience)
        Optional<int32> expRate = Acore::StringTo<int32>(args);
        if (!expRate || *expRate < 0 || *expRate > 100)
        {
            handler->PSendSysMessage("Experience rate must be a value between 0 and 100.");
            return true;
        }

        ExpRateTuner->SetExpRateForPlayer(player, (uint32)*expRate);
        handler->PSendSysMessage("Experience rate is now set to {}% for this character.", *expRate);
        return true;
    }
};

void AddExpRateTunerCommandScript()
{
    new ExpRateTuner_CommandScript();
}
