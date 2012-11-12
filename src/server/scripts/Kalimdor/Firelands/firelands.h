/*
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
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

#ifndef DEF_FIRELANDS_H
#define DEF_FIRELANDS_H

#define MAX_ENCOUNTERS 7

enum Datas
{
    DATA_BETHILAC               = 1,
    DATA_LORD_RYOLITH           = 2,
    DATA_ALYSRAZAR              = 3,
    DATA_SHANNOX                = 4,
    DATA_BALOROC                = 5,
    DATA_MAJORDOMUS_STANGEHELM  = 6,
    DATA_RAGNAROS               = 7,
};

enum GameObjectIds
{
    GO_RAGNAROS_DOOR            = 209073,
    GO_RAGNAROS_PLATFORM        = 208835,
    GO_CACHE_OF_THE_FIRELORD    = 208967,
};

enum CreatureIds
{
    BOSS_RAGNAROS                   = 52409,
    NPC_ENGULFING_FLAMES_TRIGGER    = 53485,
    NPC_SPLITTING_BLOW_TRIGGER      = 53393,
    NPC_MAGMA_POOL_TRIGGER          = 53729,
    NPC_PLATFORM_TRIGGER            = 53952,
    NPC_MAGMA_TRAP                  = 53086,
    NPC_SULFURAS_HAMMER             = 53420,
    NPC_SULFURAS_FLAME_WALL         = 38327,
    NPC_SULFURAS_SMASH_TARGET_1     = 53268,
    NPC_LAVA_WAVE                   = 53363,
    NPC_SON_OF_FLAME                = 53140,
};

#endif