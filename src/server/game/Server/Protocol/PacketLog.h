/*
 * Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010 - 2012 ProjectSkyfire <http://www.projectskyfire.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef ARKCORE_PACKETLOG_H
#define ARKCORE_PACKETLOG_H

#include "Common.h"
#include <ace/Singleton.h>

enum Direction
{
    CLIENT_TO_SERVER,
    SERVER_TO_CLIENT
};

/// %Log packets to a file
class PacketLog
{
    friend class ACE_Singleton<PacketLog, ACE_Thread_Mutex> ;
    PacketLog();
    ~PacketLog();

public:
    void Initialize();
    bool CanLogPacket() const { return (_file != NULL); }
    void LogPacket(WorldPacket const& packet, Direction direction);

private:
    FILE* _file;
};

#define sPacketLog ACE_Singleton<PacketLog, ACE_Thread_Mutex>::instance()

#endif

