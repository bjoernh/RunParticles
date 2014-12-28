#include "Util.h"

#include <Qt>

#ifdef Q_OS_WIN
#include <QDateTime>
#else
#include <time.h>
#endif

unsigned int 
Util::parseTime(const char* timeCStr) 
{
#ifdef Q_OS_WIN
    // 2014-12-06T15:00:06Z
    QDateTime myDate = QDateTime::fromString(timeCStr, "yyyy-MM-ddThh:mm:ssZ");
    return static_cast<uint>(myDate.toTime_t());
#else
    struct tm thisTime;
    strptime(timeCStr, "%Y-%m-%dT%H:%M:%SZ", &thisTime);
    return static_cast<uint>(timegm(&thisTime));
#endif
};

QString
Util::secondsToString(int seconds)
{
    int hours = seconds / 3600;
    int modhrs = int(seconds) % 3600;
    int mins = modhrs / 60;
    int secs = modhrs % 60;
    QChar zero('0');
    if (hours >= 1)
        return QString("%1hr%2m%3s").arg(hours)
                                    .arg(mins, 2, 10, zero)
                                    .arg(secs, 2, 10, zero);
    else
        return QString("%1m%2s").arg(mins, 2, 10, zero)
                                .arg(secs, 2, 10, zero);
}

