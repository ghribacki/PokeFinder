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

#ifndef EVENTSTATE5_HPP
#define EVENTSTATE5_HPP

#include <Core/Gen5/States/State5.hpp>

template <class StateType>
class SearcherState5 : public State5
{
public:
    SearcherState5(const DateTime &dt, u64 initialSeed, Buttons buttons, u16 timer0, const StateType &state) :
        State5(dt, initialSeed, buttons, timer0), state(state)
    {
    }

    StateType getState() const
    {
        return state;
    }

private:
    StateType state;
};

#endif // EVENTSTATE5_HPP
