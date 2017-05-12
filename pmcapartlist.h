#ifndef PMCAPARTLIST_H
#define PMCAPARTLIST_H

#include <stdio.h>
#include <iostream>
#include <QObject>
#include <QMessageBox>
#include <QTextStream>
#include <QIODevice>

#include "pmcaconf_mainwin.h"

class pmcaPartList: public QObject
{
    Q_OBJECT
    int nums[10000];
    QFile *pmcaList;
    QByteArray bt;
    QTextStream* pmcaStream;
public:
    explicit pmcaPartList();
    ~pmcaPartList();
    int mainGroup[10000];
    QStringList names;
    QStringList com;
    QStringList files;
    QVector<QString> textFile;
    int status;
    int num;
    QString partsRoot;
    QVector<QStringList> linkGroups;
    void pmcaRead(QString path);
    void pmcaWrite();
    void setPartName(int n, QString &pmcaPartName);
    void setComment(int n, QString &pmcaComment);
    void setFileName(int n, QString &pmcaFileName);
    void setGroup(int n, int gr);
    void fillLink(int n, QString l);

};
#endif // PMCAPARTLIST_H
