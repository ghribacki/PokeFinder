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

#ifndef EVENT5_HPP
#define EVENT5_HPP

#include <QWidget>

class EventGeneratorModel5;
class EventSearcherModel5;
class PGF;
class Profile5;
class QMenu;

namespace Ui
{
    class Event5;
}

class Event5 : public QWidget
{
    Q_OBJECT
signals:
    void alertProfiles(int);

public:
    explicit Event5(QWidget *parent = nullptr);
    ~Event5() override;
    void updateProfiles();
    bool hasProfiles() const;

private:
    Ui::Event5 *ui;
    EventGeneratorModel5 *generatorModel;
    EventSearcherModel5 *searcherModel;
    std::vector<Profile5> profiles;
    Profile5 *currentProfile;
    QMenu *generatorMenu;
    QMenu *searcherMenu;

    void setupModels();
    PGF getGeneratorParameters() const;
    PGF getSearcherParameters() const;

private slots:
    void generate();
    void search();
    void generatorImportEvent();
    void searcherImportEvent();
    void calculateInitialAdvances();
    void profileIndexChanged(int index);
    void tableViewGeneratorContextMenu(QPoint pos);
    void tableViewSearcherContextMenu(QPoint pos);
    void profileManager();
};

#endif // EVENT5_HPP
