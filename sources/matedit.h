#ifndef MATEDIT
#define MATEDIT

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

namespace Ui {
class matEdit;
class QDialog;
}

class matEdit: public QDialog
{
    Q_OBJECT



public:
    explicit matEdit(QWidget *parent);
    void populateWindow(int state = 1);
    void updateValues();
    void lockElements();
    QSlider *rS;
    QSlider *gS;
    QSlider *bS;
    QSlider *aS;
    QWidget *sliderC;
    QWidget *buttonC;
    QWidget *boxC;
    QRadioButton *db;
    QRadioButton *sb;
    QRadioButton *ab;
    QSpinBox *rC;
    QSpinBox *gC;
    QSpinBox *bC;
    QSpinBox *aC;
    QVector<QVector<QVector4D> > diff;
    QVector<QVector<QVector3D> > spec;
    QVector<QVector<QVector3D> > amb;
    QVector<QStringList> matN;
    QVector<QStringList> matT;
    QVector<QStringList> matTn;
    QVector<QVector<int> > toonR;
    QComboBox *mats;
    QPushButton *addMat;
    QLineEdit *matLine;
    QStringListModel matM;
    QStringList matGr;
    QStringList matGc;
    QStringListModel *matGrM;
    QLineEdit *grLine;
    QComboBox *matGroups;
    QPushButton *addGroup;
    QLineEdit *cLine;
    QCheckBox *texEnabled;
    QLineEdit *txLine;
    QPushButton *addTex;
    QComboBox *toonSlot;
    QCheckBox *toonEnabled;
    QLineEdit *toonPath;
    QPushButton *setToon;
    int matI;
    int groupI;
    int grI = 0;
    QVector<int> mI;

    int comb = 1;
    QVector<QStringList> texN;
    QVector<QStringList> texP;
    QVector<QStringList> texTn;
    QVector<QVector<int> > toonT;
    QStringListModel texM;
    QStringList texGr;
    QStringList texGc;
    QStringListModel *texGrM;
    QVector<int> tI;
    int tGroupI;
    int texI;
    int tgI = 0;
    QWidget texSpace;
    QComboBox *texGroups;
    QLineEdit *tgrLine;
    QPushButton *addTGroup;
    QLineEdit *tgcLine;
    QComboBox *texSelect;
    QLineEdit *texName;
    QLineEdit *texPath;
    QPushButton *addTex2;
    QCheckBox *toonBox;
    QComboBox *toonSlots;
    QLineEdit *toonFile;
    QPushButton *setTexToon;
    ~matEdit();

public slots:
    void changeR(int value);
    void changeG(int value);
    void changeB(int value);
    void changeA(int value);
    void switchDiffuse();
    void switchSpecular();
    void switchAmbient();
    void addMatGroup();
    void addMaterial();
    void enableTex();
    void changeMaterial(int m);
    void changeGroup(int gr1);
    void renameComment();
    void renameTexture();
    void setTexture();
    void overrideToon();
    void setToonSlot();
    void setToonFile();
    void renameToon();

private:
    Ui::matEdit *ui;

};

class colorArea: public QWidget
{
    Q_OBJECT


public:
    explicit colorArea(QWidget *parent = 0);
    QVector4D rdiff;
    QVector3D rspec;
    QVector3D ramb;
    ~colorArea();

protected:
    void paintEvent(QPaintEvent *event);
};
#endif // MATEDIT

