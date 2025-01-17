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

#ifndef STATIC5_HPP
#define STATIC5_HPP

#include <QWidget>

class Profile5;
class StaticGeneratorModel5;
class StaticSearcherModel5;
class QMenu;

namespace Ui
{
    class Static5;
}

class Static5 : public QWidget
{
    Q_OBJECT
signals:
    void alertProfiles(int);

public:
    explicit Static5(QWidget *parent = nullptr);
    ~Static5() override;
    void updateProfiles();
    bool hasProfiles() const;

private:
    Ui::Static5 *ui;
    StaticGeneratorModel5 *generatorModel;
    StaticSearcherModel5 *searcherModel;
    std::vector<Profile5> profiles;
    Profile5 *currentProfile;
    QMenu *generatorMenu;
    QMenu *searcherMenu;

    void setupModels();

private slots:
    void generate();
    void search();
    void profileIndexChanged(int index);
    void generatorLead();
    void calculateInitialAdvances();
    void generatorMethodIndexChanged(int index);
    void searcherMethodIndexChanged(int index);
    void tableViewGeneratorContextMenu(const QPoint &pos);
    void tableViewSearcherContextMenu(const QPoint &pos);
    void profileManager();
};

#endif // STATIC5_HPP
