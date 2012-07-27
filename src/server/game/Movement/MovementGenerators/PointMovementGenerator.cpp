/*
 * Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
 *
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

#include "gamePCH.h"
#include "PointMovementGenerator.h"
#include "Errors.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "World.h"

//----- Point Movement Generator
template<class T>
void PointMovementGenerator<T>::Initialize (T &unit)
{
    if (!unit.IsStopped())
        unit.StopMoving();

    unit.AddUnitState(UNIT_STAT_ROAMING | UNIT_STAT_ROAMING_MOVE);
    Movement::MoveSplineInit init(unit);
    init.MoveTo(i_x, i_y, i_z);
    if (speed > 0.0f)
        init.SetVelocity(speed);
    init.Launch();
}

template<class T>
bool PointMovementGenerator<T>::Update (T &unit, const uint32 &diff)
{
    if (!&unit)
        return false;

    if (unit.HasUnitState(UNIT_STAT_ROOT | UNIT_STAT_STUNNED))
    {
        unit.ClearUnitState(UNIT_STAT_ROAMING_MOVE);
        return true;
    }

    unit.AddUnitState(UNIT_STAT_ROAMING_MOVE);
    return !unit.movespline->Finalized();
}

template<class T>
void PointMovementGenerator<T>::Finalize (T &unit)
{
    unit.ClearUnitState(UNIT_STAT_ROAMING | UNIT_STAT_ROAMING_MOVE);

    if (unit.movespline->Finalized())
        MovementInform(unit);
}

template<class T>
void PointMovementGenerator<T>::Reset(T &unit)
{
    if (!unit.IsStopped())
        unit.StopMoving();

    unit.AddUnitState(UNIT_STAT_ROAMING|UNIT_STAT_ROAMING_MOVE);
}

template<class T>
void PointMovementGenerator<T>::MovementInform (T & /*unit*/)
{
}

template<> void PointMovementGenerator<Creature>::MovementInform (Creature &unit)
{
    if (unit.AI())
        unit.AI()->MovementInform(POINT_MOTION_TYPE, id);
}

template void PointMovementGenerator<Player>::Initialize (Player&);
template void PointMovementGenerator<Creature>::Initialize (Creature&);
template void PointMovementGenerator<Player>::Finalize(Player&);
template void PointMovementGenerator<Creature>::Finalize (Creature&);
template void PointMovementGenerator<Player>::Reset(Player&);
template void PointMovementGenerator<Creature>::Reset(Creature&);
template bool PointMovementGenerator<Player>::Update(Player &, const uint32 &);
template bool PointMovementGenerator<Creature>::Update(Creature&, const uint32 &);

void AssistanceMovementGenerator::Finalize (Unit &unit)
{
    unit.ToCreature()->SetNoCallAssistance(false);
    unit.ToCreature()->CallAssistance();
    if (unit.isAlive())
        unit.GetMotionMaster()->MoveSeekAssistanceDistract(sWorld->getIntConfig(CONFIG_CREATURE_FAMILY_ASSISTANCE_DELAY));
}

bool EffectMovementGenerator::Update(Unit &unit, const uint32)
{
    return !unit.movespline->Finalized();
}

void EffectMovementGenerator::Finalize(Unit &unit)
{
    if (unit.GetTypeId() != TYPEID_UNIT)
        return;

    if (((Creature&)unit).AI() && unit.movespline->Finalized())
        ((Creature&)unit).AI()->MovementInform(EFFECT_MOTION_TYPE, m_Id);
    // Need restore previous movement since we have no proper states system
    //if (unit.isAlive() && !unit.HasUnitState(UNIT_STAT_CONFUSED|UNIT_STAT_FLEEING))
    //{
    //    if (Unit * victim = unit.getVictim())
    //        unit.GetMotionMaster()->MoveChase(victim);
    //    else
    //        unit.GetMotionMaster()->Initialize();
    //}
}
