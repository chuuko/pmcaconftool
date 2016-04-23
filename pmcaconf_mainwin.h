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

namespace Ui {
class pmcaconf_mainwin;
}
QT_BEGIN_NAMESPACE
class QVector<QStringList>;
class QStringList;
QT_END_NAMESPACE
class pmcaconf_mainwin : public QMainWindow
{
    Q_OBJECT
    QFileDialog *selDir;
    QDialog *chooseID;
    QFileDialog *selPart;
    QVector<QStringList*> pmcaGroups;

public:
    explicit pmcaconf_mainwin(QWidget *parent = 0);

    QDialog *pmcaAbout;
    QString prefix;
    QLabel *prefixLabel;
    QLineEdit *prefixBox;
    QLineEdit *groupArea;
    QPushButton *prefixOk;
    QGridLayout *idLayout;
    QFormLayout *grLayout;
    QFormLayout *partLayout;
    QLabel *addPartLabel;
    QLineEdit *partName;
    QLineEdit *partPath;
    QDialog *addPart;
    QDialog *addGroup;
    QPushButton *openPart;
    QStatusBar *b;
    QWidget *fileArea;
    QComboBox *typeSelect;
    QGridLayout *myLayout;
    QDialogButtonBox *partButs;
    QDialogButtonBox *groupButs;
    QStringList *groupList;
    QStringListModel *groups;
    QStringListModel *partNames;
    QListView *groupSelect;
    QVector<QString> *partList;
    QString partFileName;
    QModelIndex partAt2;
    int listIterator;
    ~pmcaconf_mainwin();

public slots:

    void showAbout();
    void openConfig();
    void loadConf();
    void setLoadedPartName();
    void selectPart();
    void addNewPart();
    void addNewGroup();
    void createGroup();
    void partRejected();
    void partAccepted();
    void buildGroupList();
    void populateLinkList();
    void changePartName(QModelIndex partAt);
    void switchPartGroup();

private:
    Ui::pmcaconf_mainwin *ui;

};

#endif // PMCACONF_MAINWIN_H
