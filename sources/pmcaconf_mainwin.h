#ifndef PMCACONF_MAINWIN_H
#define PMCACONF_MAINWIN_H

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
#include <QMessageBox>


#include <sources/pmcapartlist.h>
#include "matedit.h"
namespace Ui {
class pmcaconf_mainwin;
class pmcaPartList;
}

class pmcaconf_mainwin : public QMainWindow
{
    Q_OBJECT
    QFileDialog *selDir;
    QFileDialog *saveDir;
    QDialog *chooseID;
    QFileDialog *selPart;


public:
    explicit pmcaconf_mainwin(QWidget *parent = 0);
    QDialog *pmcaAbout;
    QString prefix;
    QLabel *prefixLabel;
    QLineEdit *prefixBox;
    QPushButton *prefixOk;
    QGridLayout *idLayout;
    QFormLayout *partLayout;
    QLabel *addPartLabel;
    QLineEdit *partName;
    QLineEdit *partPath;
    QLineEdit *partCom;
    QDialog *addPart;
    QPushButton *openPart;
    QStatusBar *b;
    QWidget *fileArea;
    QComboBox *typeSelect;
    QGridLayout *myLayout;
    QDialogButtonBox *partButs;
    QStringList *groupList;
    QStringListModel *groups;
    QStringListModel *ll;
    QStringListModel *ll2;
    QListView *groupSelect;
    QVector<QString> *partList;
    QVector<QString> *partBox;
    QVector<int> *partRef;
    QVector<QString> *commList;
    QVector<QString> *fileList;
    QVector<QStringList> *links;
    QStringListModel *pt;
    QStringList *pts;
    QVector<int> *group;
    QStringList aGroups;
    QString lf;
    QVector<QVector<QVector4D> > diffs;
    int listIterator;
    int i;
    int aGr;
    int listI;
    int pos;
    int pos2;
    matEdit *material;
    pmcaPartList plist;
    ~pmcaconf_mainwin();

public slots:

    void showAbout();
    void openConfig();
    void loadConf();
    void saveConfig();
    void addNewPart();
    void populatePartList();
    void partRejected();
    void partAccepted();
    void buildGroupList();
    void populateLinkList();
    void groupChanged(QModelIndex m);
    void updateDetails(QModelIndex m);
    void addLink(QModelIndex m);
    void removeLink(QModelIndex m);
    void deletePart();
    void loadPart();
    void openMat();
    void aboutQt();

private:
    Ui::pmcaconf_mainwin *ui;

};

#endif // PMCACONF_MAINWIN_H
