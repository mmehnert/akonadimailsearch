/***************************************************************************
 *   Copyright (C) 2013 by  <>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#ifndef AKONADIMAILSEARCH_H
#define AKONADIMAILSEARCH_H


#include <KDE/KMainWindow>

#include "ui_akonadimailsearch.h"


/**
 * This class serves as the main window for akonadimailsearch.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author Your Name <mail@example.com>
 * @version 0.1
 */
class akonadimailsearch : public KMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    akonadimailsearch();

    /**
     * Default Destructor
     */
    virtual ~akonadimailsearch();

private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::mainWidget m_ui;
};

#endif // _AKONADIMAILSEARCH_H_
