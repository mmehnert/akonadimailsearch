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

// application header
#include "akonadimailsearch.h"
// KDE headers
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>
#include <QTextStream>

static const char description[] =
    I18N_NOOP("akonadi email address search for notmuch");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    QTextStream out(stdout);
    KAboutData about("simple", 0, ki18n("akonadimailsearch"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2011 Maximilian Mehnert"), KLocalizedString(), 0, "maximilian.mehnert@gmx.de");
    about.addAuthor( ki18n("Maximilian Mehnert"), KLocalizedString(), "maximilian.mehnert@gmx.de" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[search]", ki18n( "string to search for" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    QString search=QString();

    if( args->count() > 0){
        search=args->arg(0);
    }


    akonadimailsearch *mainSearch = new akonadimailsearch;
    QObject::connect(mainSearch,SIGNAL(finished()),&app,SLOT(quit()));
    
    mainSearch->query(search);
    
    return app.exec();
}
