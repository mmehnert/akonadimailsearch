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
#include <QTextStream>

using namespace Akonadi;

akonadimailsearch::akonadimailsearch()
{
	activeFetchJobsCount=0;
}

akonadimailsearch::~akonadimailsearch()
{
}

void akonadimailsearch::query(QString &search)
{
	mysearch=search;
	CollectionFetchJob *fetchJob = new CollectionFetchJob(Collection::root(), CollectionFetchJob::Recursive, this);
	fetchJob->fetchScope().setContentMimeTypes( QStringList() << "text/directory" );
	connect(fetchJob, SIGNAL(finished(KJob*)), SLOT(onCollectionsFetched(KJob*)));
}

void akonadimailsearch::onCollectionsFetched(KJob* job)
{
	if (job->error()) {
		kWarning() << job->errorString();
		emit finished();
	} else {
		CollectionFetchJob *fetchJob = qobject_cast<CollectionFetchJob*>(job);
		QList<Collection> contactCollections;
		foreach (const Collection &collection, fetchJob->collections()) {
			if (collection.isVirtual()) {
				continue;
			}
			if (collection.contentMimeTypes().contains( KABC::Addressee::mimeType() ) ) {
				ItemFetchJob *itemFetchJob = new ItemFetchJob(collection);
				itemFetchJob->fetchScope().fetchFullPayload();
				connect(itemFetchJob, SIGNAL(finished(KJob*)), SLOT(onItemsFetched(KJob*)));
				++activeFetchJobsCount;
			}
		}
		if (activeFetchJobsCount == 0) {
			emit finished();
		}
	}
}
void akonadimailsearch::onItemsFetched(KJob *job)
{
	if (job->error()) {
		kWarning() << job->errorString();
	} else {
		ItemFetchJob *itemFetchJob = qobject_cast<ItemFetchJob*>(job);
		foreach (const Item &item, itemFetchJob->items()) {
			if(item.hasPayload<KABC::Addressee>()) {
				const QString id = item.url().prettyUrl();
				const KABC::Addressee contact = item.payload<KABC::Addressee>();
				QTextStream out(stdout);
				if(contact.preferredEmail().size() > 0 && \
					( contact.preferredEmail().contains(mysearch) || contact.formattedName().contains(mysearch) )){
					out << contact.formattedName() << " <" << contact.preferredEmail()<< ">" <<endl;
				}
			}
		}
	}
	if (--activeFetchJobsCount == 0) {
		emit finished();
	}
}
