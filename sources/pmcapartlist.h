#ifndef PMCAPARTLIST_H
#define PMCAPARTLIST_H

#include <stdio.h>
#include <iostream>
#include <QObject>
#include <QMessageBox>
#include <QTextStream>
#include <QIODevice>
#include <QFile>
#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QListView>
#include <QDialogButtonBox>
#include <QStringListModel>
#include <QVector>
#include <QDialog>
#include <QGraphicsWidget>
#include <QVector4D>
#include <QVector3D>
#include <QFormLayout>
#include <QSlider>
#include <QRadioButton>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QStringListModel>
#include <QFileDialog>
#include <QCheckBox>

//#include "pmcaconf_mainwin.h"

class pmcaPartList: public QObject
{
    Q_OBJECT
    int nums[10000];
    QFile *pmcaList, *pmcaMatList, *pmcaTexList;
    QByteArray bt;
    QTextStream* pmcaStream, *pmcaMatStream, *pmcaTexStream;
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
    QStringList matGrComment;
    QStringList matGroup;
    QVector<QStringList> matName;
    QVector<QVector<QVector4D> > pmcaDiff;
    QVector<QVector<QVector3D> > pmcaSpec;
    QVector<QVector<QVector3D> > pmcaAmb;
    QVector<QStringList> pmcaToon;
    QVector<QStringList> pmcaTex;
    QStringList texList;
    QStringList texComment;
    QVector<QStringList> pmcaTexName;
    QVector<QStringList> pmcaTexPath;
    QVector<QStringList> pmcaTexToon;
    int grMem[10000];
    void pmcaRead(QString path, QString matPath, QString texPath);
    void pmcaWrite(QString path, QVector<QString> *nm, QVector<QString> *cm, QVector<QString> *fn, QVector<int> *pgr, QVector<QStringList> *lk, QString matPath, QStringList mgr, QStringList mgc, QVector<QStringList> mName,QVector<QVector<QVector4D> > diffs,QVector<QVector<QVector3D> > specs,QVector<QVector<QVector3D> > ambs,QVector<QStringList> mTex,QVector<QVector<int> > mTn,QVector<QStringList> mTt,QString texListPath,QStringList texGroupsList, QStringList texGComm, QVector<QStringList> texNames,QVector<QStringList> texFiles, QVector<QVector<int> > toonNums,QVector<QStringList> toonFiles);
    void setPartName(int n, QString &pmcaPartName);
    void setComment(int n, QString &pmcaComment);
    void setFileName(int n, QString &pmcaFileName);
    void setGroup(int n, int gr);
    void fillLink(int n, QString l);

};
#endif // PMCAPARTLIST_H
