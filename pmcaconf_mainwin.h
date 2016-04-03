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

class pmcaconf_mainwin : public QMainWindow
{
    Q_OBJECT
    QFileDialog *selDir;
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
    QDialog *addPart;
    QPushButton *openPart;
    QStatusBar *b;
    QWidget *fileArea;
    QComboBox *typeSelect;
    QGridLayout *myLayout;
    QDialogButtonBox *partButs;
    QStringList *groupList;
    QStringList *registeredParts;
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
    void partRejected();
    void partAccepted();
    void buildGroupList();
    void populateLinkList();
    void changePartName(QModelIndex partAt);

private:
    Ui::pmcaconf_mainwin *ui;

};

#endif // PMCACONF_MAINWIN_H
