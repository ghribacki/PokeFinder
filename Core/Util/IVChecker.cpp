/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2020 by Admiral_Fish, bumba, and EzPzStreamz
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

#include "IVChecker.hpp"
#include <Core/Parents/PersonalInfo.hpp>
#include <Core/Util/Nature.hpp>
#include <QSet>
#include <cmath>

namespace
{
    QVector<QSet<u8>> calculateIVs(const PersonalInfo &info, const QVector<u16> &stats, u8 level, u8 nature, u8 characteristic)
    {
        QVector<u8> minIVs(6, 31);
        QVector<u8> maxIVs(6, 0);
        QVector<u8> baseStats = info.getBaseStats();

        for (u8 i = 0; i < 6; i++)
        {
            for (u8 iv = 0; iv < 32; iv++)
            {
                double stat;
                if (i == 0)
                {
                    stat = std::floor(((2 * baseStats.at(i) + iv) * level) / 100.0) + level + 10;
                }
                else
                {
                    stat = (std::floor(((2 * baseStats.at(i) + iv) * level) / 100.0) + 5) * Nature::getNatureModifier(nature, i);
                }

                if (static_cast<u16>(stat) == stats.at(i))
                {
                    if (iv > maxIVs.at(i))
                    {
                        maxIVs[i] = iv;
                    }
                    if (iv < minIVs.at(i))
                    {
                        minIVs[i] = iv;
                    }
                }
            }
        }

        QVector<QSet<u8>> possible(6);
        QVector<u8> indexes = { 0, 1, 2, 3, 4, 5 };

        u8 characteristicHigh = 31;
        if (characteristic != 255)
        {
            u8 stat = characteristic / 5;
            u8 result = characteristic % 5;

            indexes.removeAll(stat);

            for (u8 i = minIVs.at(stat); i <= maxIVs.at(stat); i++)
            {
                if ((i % 5) == result)
                {
                    possible[stat].insert(i);
                    characteristicHigh = i;
                }
            }
        }

        for (u8 i : indexes)
        {
            for (u8 j = minIVs.at(i); j <= maxIVs.at(i); j++)
            {
                if (j <= characteristicHigh)
                {
                    possible[i].insert(j);
                }
            }
        }

        return possible;
    }
}

QVector<QVector<u8>> IVChecker::calculateIVRange(const PersonalInfo &info, const QVector<QVector<u16>> &stats, const QVector<u8> &level,
                                                 u8 nature, u8 characteristic, u8 hiddenPower)
{
    QVector<QSet<u8>> first = calculateIVs(info, stats.at(0), level.at(0), nature, characteristic);

    for (int i = 1; i < stats.size(); i++)
    {
        auto next = calculateIVs(info, stats.at(i), level.at(i), nature, characteristic);

        for (u8 j = 0; j < 6; j++)
        {
            first[j].intersect(next.at(j));
        }
    }

    if (hiddenPower != 255)
    {
        QVector<QSet<u8>> final(6);
        for (u8 hp : first.at(0))
        {
            for (u8 atk : first.at(1))
            {
                for (u8 def : first.at(2))
                {
                    for (u8 spa : first.at(3))
                    {
                        for (u8 spd : first.at(4))
                        {
                            for (u8 spe : first.at(5))
                            {
                                u8 hpType
                                    = ((((hp & 1) + 2 * (atk & 1) + 4 * (def & 1) + 8 * (spe & 1) + 16 * (spa & 1) + 32 * (spd & 1)) * 15)
                                       / 63);
                                if (hpType == hiddenPower)
                                {
                                    final[0].insert(hp);
                                    final[1].insert(atk);
                                    final[2].insert(def);
                                    final[3].insert(spa);
                                    final[4].insert(spd);
                                    final[5].insert(spe);
                                }
                            }
                        }
                    }
                }
            }
        }
        first = final;
    }

    QVector<QVector<u8>> ivs(6);
    for (u8 i = 0; i < 6; i++)
    {
        for (const u8 num : first.at(i))
        {
            ivs[i].append(num);
        }
        std::sort(ivs[i].begin(), ivs[i].end());
    }
    return ivs;
}
