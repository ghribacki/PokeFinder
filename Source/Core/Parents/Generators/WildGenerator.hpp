/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2022 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef WILDGENERATOR_HPP
#define WILDGENERATOR_HPP

#include <Core/Enum/Lead.hpp>
#include <Core/Parents/Generators/Generator.hpp>

class WildGenerator : public Generator
{
public:
    WildGenerator(u32 initialAdvances, u32 maxAdvances, u16 tid, u16 sid, u8 genderRatio, Method method, const StateFilter &filter) :
        Generator(initialAdvances, maxAdvances, tid, sid, genderRatio, method, filter), lead(Lead::None)
    {
    }

    void setEncounter(Encounter encounter)
    {
        this->encounter = encounter;
    }

    void setLead(Lead lead)
    {
        this->lead = lead;
    }

    void setSynchNature(u8 synchNature)
    {
        this->synchNature = synchNature;
    }

protected:
    Encounter encounter;
    Lead lead;
    u8 synchNature;
};

#endif // WILDGENERATOR_HPP
