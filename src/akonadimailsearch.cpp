/***************************************************************************
 *   Copyright (C) 2013 by  Maximilian Mehnert <maximilian.mehnert@gmx.de> *
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

#include "akonadimailsearch.h"
#include <akonadi/contact/contactsearchjob.h>
#include <QTextStream>


akonadimailsearch::akonadimailsearch()
{
}

akonadimailsearch::~akonadimailsearch()
{
}

void akonadimailsearch::query(QString &search)
{
	Akonadi::ContactSearchJob *job = new Akonadi::ContactSearchJob();
	
	if (search.length() >0 ){
		job->setQuery( Akonadi::ContactSearchJob::NameOrEmail, search,	Akonadi::ContactSearchJob::ContainsMatch );
	}
	connect( job, SIGNAL( result( KJob* ) ), this, SLOT( searchResult( KJob* ) ) );
}

void akonadimailsearch::searchResult( KJob *job )
{
	QTextStream out(stdout);
	Akonadi::ContactSearchJob *searchJob = qobject_cast<Akonadi::ContactSearchJob*>( job );
	const KABC::Addressee::List contacts = searchJob->contacts();
 
	foreach ( const KABC::Addressee &contact, contacts ) 
	{
		out << contact.formattedName() << " <" << contact.preferredEmail()<< ">" <<endl;
	}
	emit finished();
}


