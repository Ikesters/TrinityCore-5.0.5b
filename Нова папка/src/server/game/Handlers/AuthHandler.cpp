/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Opcodes.h"
#include "WorldSession.h"
#include "WorldPacket.h"

void WorldSession::SendAuthResponse(uint8 code, bool queued, uint32 queuePos)
{
    QueryResult result = LoginDatabase.PQuery("SELECT class, expansion FROM realm_classes WHERE realmId = %u", realmID);
    QueryResult result2 = LoginDatabase.PQuery("SELECT race, expansion FROM realm_races WHERE realmId = %u", realmID);
    if (!result || !result2)
    {
        sLog->outError(LOG_FILTER_GENERAL, "AuthHandler SendAuthResponse could not get db realm_classes and realm_races");
        return;
    }
    WorldPacket packet(SMSG_AUTH_RESPONSE, 1 /*bits*/ + 4 + 1 + 4 + 1 + 4 + 1 + 1 + (queued ? 4 : 0));

    packet.WriteBit(1);                                    // has account info

    // account info
    packet.WriteBit(0);                                     // IsInQueue
    packet.WriteBits(result->GetRowCount(), 25);           // Activation count for races
    packet.WriteBits(0, 22);                                // Activate character template windows/button
    packet.WriteBits(result2->GetRowCount(), 25);            // Activation count for classes
    packet.WriteBit(queued);
    packet.FlushBits();

    packet << uint8(0);
    packet << uint8(Expansion());                          // Unknown, these two show the same

    do
    {
        Field* fields = result->Fetch();

        packet << fields[0].GetUInt8();
        packet << fields[1].GetUInt8();
    } while (result->NextRow());

    packet << uint32(0);
    packet << uint32(0);
    packet << uint32(0);

    do
    {
        Field* fields = result2->Fetch();

        packet << fields[0].GetUInt8();
        packet << fields[1].GetUInt8();
    } while (result2->NextRow());

    packet << uint8(Expansion());                          // Unknown, these two show the same
    packet << uint8(code);

    SendPacket(&packet);
}

void WorldSession::SendClientCacheVersion(uint32 version)
{
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}
