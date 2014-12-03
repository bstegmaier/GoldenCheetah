/*
 * Copyright (c) 2006 Sean C. Rhea (srhea@srhea.net)
 *           (c) 2014 Mark Liversedge (liversedge@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _GC_RideItem_h
#define _GC_RideItem_h 1
#include "GoldenCheetah.h"

#include "RideMetric.h"

class RideFile;
class Context;

Q_DECLARE_METATYPE(RideItem*)

class RideItem : public QObject
{

    Q_OBJECT
    G_OBJECT


    protected:

        RideFile *ride_;

        QStringList errors_;
        Context *context; // to notify widgets when date/time changes
        bool isdirty;

    public slots:
        void modified();
        void reverted();
        void saved();
        void notifyRideDataChanged();
        void notifyRideMetadataChanged();

    signals:
        void rideDataChanged();
        void rideMetadataChanged();

    public:

        bool isedit; // is being edited at the moment

        QString path;
        QString fileName;
        QDateTime dateTime;
        const QStringList errors() { return errors_; }

        // ride() will open the ride if it isn't already when open=true
        // if we pass false then it will just return ride_ so we can
        // traverse currently open rides when config changes
        RideFile *ride(bool open=true);

        // create and destroy
        RideItem(RideFile *ride, Context *context);
        RideItem(QString path, QString fileName, QDateTime &dateTime, Context *context);
        RideItem(RideFile *ride, QDateTime &dateTime, Context *context);
        void freeMemory();

        // state
        void setDirty(bool);
        bool isDirty() { return isdirty; }
        bool isRun() { return ride_ ? ride_->isRun() : false; }

        // get/set
        void setRide(RideFile *);
        void setFileName(QString, QString);
        void setStartTime(QDateTime);
};

#endif // _GC_RideItem_h
