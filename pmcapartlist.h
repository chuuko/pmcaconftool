#ifndef PMCAPARTLIST_H
#define PMCAPARTLIST_H

#include <QObject>
#include "pmcaconf_mainwin.h"

class pmcaPartList: public QObject
{
    Q_OBJECT
    int nums[10000];
    QVector<QString> names;
public:
    explicit pmcaPartList(int num, int gr, QString &pmcaPartName, QString &pmcaComment, QString &pmcaFileName, QStringList &pmcaLinkGroups);
    ~pmcaPartList();
    void setPartName(int num, QString &pmcaPartName);
    void setComment(int num, QString &pmcaComment);
    void setGroup(int num, int gr);
    QString getPartName(int num);

};
#endif // PMCAPARTLIST_H
