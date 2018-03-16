#include "matedit.h"
#include "ui_matedit.h"
#include <QGraphicsWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QGridLayout>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

colorArea *df;
int r,g,b,a;
int i = 0;
int u = 1;

colorArea::colorArea(QWidget *parent):
    QWidget(parent)
{
    rdiff.setX(125);
    r = 125;
    rdiff.setY(125);
    g = 125;
    rdiff.setZ(125);
    b = 125;
    rdiff.setW(255);
    a = 255;
    rspec.setX(0);
    rspec.setY(0);
    rspec.setZ(0);
    ramb.setX(100);
    ramb.setY(100);
    ramb.setZ(100);
    setGeometry(0,0,100,100);
    setMinimumSize(100,100);
    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}
colorArea::~colorArea()
{

}
void colorArea::paintEvent(QPaintEvent *event)
{
    QPainter *p;
    p = new QPainter(this);
    QPen pineapple;
    QBrush br;
    QColor c(r,g,b,a);
    br.setStyle(Qt::SolidPattern);
    br.setColor(c);
    pineapple.setColor(c);
    p->setBrush(br);
    p->setPen(pineapple);
    p->drawRect(0,0,100,100);
    p->end();
}

matEdit::matEdit(QWidget *parent):
    QDialog(parent),
    ui(new Ui::matEdit())
{
    mI.reserve(10000);
    matI = 0;
    matN.resize(10000);
    matN.reserve(10000);
    matT.resize(10000);
    matT.reserve(10000);
    matTn.resize(10000);
    matTn.reserve(10000);
    toonR.resize(10000);
    toonR.reserve(10000);
    matGr.reserve(10000);
    matGc.reserve(10000);

    texN.resize(10000);
    texN.reserve(10000);
    texI = 0;
    texP.resize(10000);
    texP.reserve(10000);
    texTn.resize(10000);
    texTn.reserve(10000);
    toonT.resize(10000);
    toonT.reserve(10000);
    texGc.reserve(10000);
    texGr.reserve(10000);
    tI.reserve(10000);

    matGrM = new QStringListModel(matGr);
    matGroups = new QComboBox(this);
    matGroups->setModel(matGrM);
    mats = new QComboBox(this);
    matM.setStringList(matN.at(0));
    mats->setModel(&matM);
    connect(mats,SIGNAL(currentIndexChanged(int)),this,SLOT(changeMaterial(int)));
    connect(matGroups,SIGNAL(currentIndexChanged(int)),this,SLOT(changeGroup(int)));
    diff.resize(10000);
    diff.reserve(10000);
    spec.resize(10000);
    spec.reserve(10000);
    amb.resize(10000);
    amb.reserve(10000);
    texGrM = new QStringListModel(texGr);
    texM.setStringList(texN.at(0));
    grLine = new QLineEdit(this);
    matLine = new QLineEdit(this);
    addMat = new QPushButton("Add material",this);
    addGroup = new QPushButton("Add material slot",this);
    cLine = new QLineEdit(this);
    texEnabled = new QCheckBox("Add texture",this);
    txLine = new QLineEdit(this);
    addTex = new QPushButton("Add texture",this);
    toonEnabled = new QCheckBox("Change toon",this);
    toonSlot = new QComboBox(this);
    toonPath = new QLineEdit(this);
    setToon =  new QPushButton("Set toon",this);
    for(int tni=0;tni<11;tni++)
    {
        toonSlot->addItem(QString::number(tni));
    }
    toonSlot->update();
    toonSlot->show();
    connect(addMat,SIGNAL(released()),this,SLOT(addMaterial()));
    connect(addGroup,SIGNAL(released()),this,SLOT(addMatGroup()));
    connect(cLine,SIGNAL(editingFinished()),this,SLOT(renameComment()));
    connect(texEnabled,SIGNAL(clicked()),this,SLOT(enableTex()));
    connect(toonEnabled,SIGNAL(clicked()),this,SLOT(overrideToon()));
    connect(toonSlot,SIGNAL(currentIndexChanged(int)),this,SLOT(setToonSlot()));
    connect(toonPath,SIGNAL(textChanged(QString)),this,SLOT(renameToon()));
    connect(setToon,SIGNAL(released()),this,SLOT(setToonFile()));
    connect(txLine,SIGNAL(textChanged(QString)),this,SLOT(renameTexture()));
    connect(addTex,SIGNAL(released()),this,SLOT(setTexture()));
    db = new QRadioButton("Diffuse",this);
    sb = new QRadioButton("Specular",this);
    ab = new QRadioButton("Ambient",this);
    rC = new QSpinBox(this);
    rC->setRange(0,255);
    gC = new QSpinBox(this);
    gC->setRange(0,255);
    bC = new QSpinBox(this);
    bC->setRange(0,255);
    aC = new QSpinBox(this);
    aC->setRange(0,255);
    connect(db,SIGNAL(toggled(bool)),this,SLOT(switchDiffuse()));
    connect(sb,SIGNAL(toggled(bool)),this,SLOT(switchSpecular()));
    connect(ab,SIGNAL(toggled(bool)),this,SLOT(switchAmbient()));
    df = new colorArea(this);
    rS = new QSlider(Qt::Horizontal,this);
    gS = new QSlider(Qt::Horizontal,this);
    bS = new QSlider(Qt::Horizontal,this);
    aS = new QSlider(Qt::Horizontal,this);
    rS->setMaximum(255);
    rS->setGeometry(0,0,255,20);
    rS->setValue(df->rdiff.x());
    rC->setValue(df->rdiff.x());
    gS->setMaximum(255);
    gS->setGeometry(0,0,255,20);
    gS->setValue(df->rdiff.y());
    gC->setValue(df->rdiff.y());
    bS->setMaximum(255);
    bS->setGeometry(0,0,255,20);
    bS->setValue(df->rdiff.z());
    bC->setValue(df->rdiff.z());
    aS->setMaximum(255);
    aS->setGeometry(0,0,255,20);
    aS->setValue(df->rdiff.w());
    aC->setValue(df->rdiff.w());
    connect(rS,SIGNAL(valueChanged(int)),this,SLOT(changeR(int)));
    connect(rC,SIGNAL(valueChanged(int)),this,SLOT(changeR(int)));
    connect(gS,SIGNAL(valueChanged(int)),this,SLOT(changeG(int)));
    connect(gC,SIGNAL(valueChanged(int)),this,SLOT(changeG(int)));
    connect(bS,SIGNAL(valueChanged(int)),this,SLOT(changeB(int)));
    connect(bC,SIGNAL(valueChanged(int)),this,SLOT(changeB(int)));
    connect(aS,SIGNAL(valueChanged(int)),this,SLOT(changeA(int)));
    connect(aC,SIGNAL(valueChanged(int)),this,SLOT(changeA(int)));
    db->setChecked(true);
    sliderC = new QWidget(this);
    buttonC = new QWidget(this);
    boxC = new QWidget(this);
    QFormLayout *sL;
    sL = new QFormLayout(this);
    QGridLayout *bL;
    bL =  new QGridLayout(this);
    QFormLayout *spL;
    spL = new QFormLayout(this);
    bL->addWidget(matGroups,0,3);
    bL->addWidget(grLine,0,4);
    bL->addWidget(addGroup,0,5);
    bL->addWidget(cLine,1,4);
    bL->addWidget(texEnabled,3,2);
    bL->addWidget(txLine,3,4);
    bL->addWidget(addTex,3,5);
    bL->addWidget(toonEnabled,4,2);
    bL->addWidget(toonSlot,4,3);
    bL->addWidget(toonPath,4,4);
    bL->addWidget(setToon,4,5);
    bL->addWidget(db,2,0);
    bL->addWidget(sb,2,1);
    bL->addWidget(ab,2,2);
    bL->addWidget(mats,2,3);
    bL->addWidget(matLine,2,4);
    bL->setColumnMinimumWidth(4,100);
    bL->addWidget(addMat,2,5);
    buttonC->setLayout(bL);
    sL->addRow("Red",rS);
    sL->addRow("Green",gS);
    sL->addRow("Blue",bS);
    sL->addRow("Alpha",aS);
    spL->addWidget(rC);
    spL->addWidget(gC);
    spL->addWidget(bC);
    spL->addWidget(aC);
    sliderC->setLayout(sL);
    boxC->setLayout(spL);
    texGroups = new QComboBox(this);
    tgrLine = new QLineEdit(this);
    addTGroup = new QPushButton("Add texture group", this); 
    tgcLine = new QLineEdit(this);
    texSelect = new QComboBox(this);
    texName = new QLineEdit(this);
    texPath = new QLineEdit(this);
    addTex2 = new QPushButton("Add texture",this);
    toonBox = new QCheckBox("Override toon",this);
    toonSlots = new QComboBox(this);
    toonFile = new QLineEdit(this);
    setTexToon = new QPushButton("Set toon",this);
    texSelect->setModel(&texM);
    for(int i2=0;i2<11;i2++)
    {
        toonSlots->addItem(QString::number(i2));
    }
    connect(addTGroup,SIGNAL(released()),this,SLOT(addMatGroup()));
    connect(tgcLine,SIGNAL(editingFinished()),this,SLOT(renameComment()));
    //connect(texPath,SIGNAL(textChanged(QString)),this,SLOT(renameTexture()));
    connect(texGroups,SIGNAL(currentIndexChanged(int)),this,SLOT(changeGroup(int)));
    connect(texSelect,SIGNAL(currentIndexChanged(int)),this,SLOT(changeMaterial(int)));
    connect(addTex2,SIGNAL(released()),this,SLOT(addMaterial()));
    connect(toonBox,SIGNAL(clicked()),this,SLOT(overrideToon()));
    connect(toonSlots,SIGNAL(currentIndexChanged(int)),this,SLOT(setToonSlot()));
    connect(toonFile,SIGNAL(textChanged(QString)),this,SLOT(renameToon()));
    connect(setTexToon,SIGNAL(released()),this,SLOT(setToonFile()));

    QGridLayout *txL;
    txL = new QGridLayout(this);
    txL->addWidget(texGroups,0,2);
    txL->addWidget(tgrLine,0,3);
    txL->addWidget(addTGroup,0,4);
    txL->addWidget(tgcLine,1,3);
    txL->addWidget(texSelect,2,1);
    txL->addWidget(texName,2,2);
    txL->addWidget(texPath,2,3);
    txL->addWidget(addTex2,2,4);
    txL->addWidget(toonBox,3,1);
    txL->addWidget(toonSlots,3,2);
    txL->addWidget(toonFile,3,3);
    txL->addWidget(setTexToon,3,4);
    texSpace.setLayout(txL);
    ui->setupUi(this);
    ui->gridLayout->addWidget(buttonC,0,1);
    ui->gridLayout->addWidget(&texSpace,0,0);
    ui->gridLayout->addWidget(df,0,0);
    ui->gridLayout->addWidget(sliderC,1,0);
    ui->gridLayout->addWidget(boxC,1,1);
    ui->gridLayout->addWidget(ui->buttonBox,2,0);


}
matEdit::~matEdit()
{
    delete ui;
}
void matEdit::populateWindow(int state)
{
    comb=state;
    if(comb==1)
    {
        texSpace.hide();
        buttonC->show();
        df->show();
        sliderC->show();
        boxC->show();
        grLine->show();

    }
    else
    {
        buttonC->hide();
        df->hide();
        sliderC->hide();
        boxC->hide();
        texSpace.show();

    }
    lockElements();
}
void matEdit::changeR(int value)
{
    switch(i)
    {
        case 0:
        {
            df->rdiff.setX(value);
            diff.at(groupI).at(matI).setX(value);
            break;
        }
        case 1:
        {
            df->rspec.setX(value);
            spec.at(groupI).at(matI).setX(value);
            break;
        }
        case 2:
        {
            df->ramb.setX(value);
            amb.at(groupI).at(matI).setX(value);
            break;
        }
    }
    r = value;
    updateValues();
    df->update();
}
void matEdit::changeG(int value)
{
    switch(i)
    {
        case 0:
        {
            df->rdiff.setY(value);
            diff.at(groupI).at(matI).setY(value);
            break;
        }
        case 1:
        {
            df->rspec.setY(value);
            spec.at(groupI).at(matI).setY(value);
            break;
        }
        case 2:
        {
            df->ramb.setY(value);
            amb.at(groupI).at(matI).setY(value);
            break;
        }
    }
    g = value;
    updateValues();
    df->update();
}
void matEdit::changeB(int value)
{
    switch(i)
    {
        case 0:
        {
            df->rdiff.setZ(value);
            diff.at(groupI).at(matI).setZ(value);
            break;
        }
        case 1:
        {
            df->rspec.setZ(value);
            spec.at(groupI).at(matI).setZ(value);
            break;
        }
        case 2:
        {
            df->ramb.setZ(value);
            amb.at(groupI).at(matI).setZ(value);
            break;
        }
    }
    b = value;
    updateValues();
    df->update();
}
void matEdit::changeA(int value)
{
    df->rdiff.setW(value);
    diff.at(groupI).at(matI).setW(value);
    a = value;
    aS->setValue(value);
    aC->setValue(value);
    df->update();
}
void matEdit::switchDiffuse()
{
    i = 0;
    r = df->rdiff.x();
    g = df->rdiff.y();
    b = df->rdiff.z();
    a = df->rdiff.w();
    updateValues();
    aS->setValue(a);
    aC->setValue(a);
    aS->setEnabled(true);
    aC->setEnabled(true);
    df->update();
}
void matEdit::switchSpecular()
{
    i = 1;
    r = df->rspec.x();
    g = df->rspec.y();
    b = df->rspec.z();
    a = 255;
    updateValues();
    aS->setEnabled(false);
    aC->setEnabled(false);
    df->update();
}
void matEdit::switchAmbient()
{
    i = 2;
    r = df->ramb.x();
    g = df->ramb.y();
    b = df->ramb.z();
    a = 255;
    updateValues();
    aS->setEnabled(false);
    aC->setEnabled(false);
    df->update();
}
void matEdit::updateValues()
{
    rS->setValue(r);
    rC->setValue(r);
    gS->setValue(g);
    gC->setValue(g);
    bS->setValue(b);
    bC->setValue(b);
}
void matEdit::addMatGroup()
{
    if(comb==1)
    {
        matGr.append(grLine->text());
        matGc.append(cLine->text());
        mI.append(0);
        diff.at(grI).reserve(10000);
        spec.at(grI).reserve(10000);
        amb.at(grI).reserve(10000);
        matN.at(grI).reserve(10000);
        matT.at(grI).reserve(10000);
        matTn.at(grI).reserve(10000);
        toonR.at(grI).reserve(10000);
        grLine->clear();
        cLine->blockSignals(true);
        cLine->clear();
        cLine->blockSignals(false);
        matGroups->blockSignals(true);
        matGrM->setStringList(matGr);
        matGroups->setModel(matGrM);
        matGroups->update();
        matGroups->blockSignals(false);
        groupI = grI;
        grI++;
        matGroups->setCurrentIndex(matGr.size()-1);

    }
    else
    {
        texGr.append(tgrLine->text());
        texGc.append(tgcLine->text());
        tI.append(0);
        texP.at(tgI).reserve(10000);
        texN.at(tgI).reserve(10000);
        texTn.at(tgI).reserve(10000);
        toonT.at(tgI).reserve(10000);
        tgrLine->clear();
        tgcLine->blockSignals(true);
        tgcLine->clear();
        tgcLine->blockSignals(false);
        texGroups->blockSignals(true);
        texGrM->setStringList(texGr);
        texGroups->setModel(texGrM);
        texGroups->update();
        texGroups->blockSignals(false);
        tGroupI = tgI;
        tgI++;
        texGroups->setCurrentIndex(texGr.size()-1);
    }
    lockElements();
}
void matEdit::addMaterial()
{
    if(comb==1)
    {

        matN[matGroups->currentIndex()].append(matLine->text());
        diff[matGroups->currentIndex()].append(QVector4D(125,125,125,255));
        spec[matGroups->currentIndex()].append(QVector3D(0,0,0));
        amb[matGroups->currentIndex()].append(QVector3D(100,100,100));
        matT[matGroups->currentIndex()].append(QString("0"));
        matTn[matGroups->currentIndex()].append(QString(""));
        toonR[matGroups->currentIndex()].append(-1);
        matLine->clear();
        mats->blockSignals(true);
        matM.setStringList(matN.at(matGroups->currentIndex()));
        mats->setModel(&matM);
        mats->update();
        mats->blockSignals(false);
        mI[matGroups->currentIndex()]= mI[matGroups->currentIndex()] + 1;
        mats->setCurrentIndex(matN.size()-1);
    }
    else
    {
        texN[texGroups->currentIndex()].append(texName->text());
        texP[texGroups->currentIndex()].append(texPath->text());
        toonT[texGroups->currentIndex()].append(-1);
        texTn[texGroups->currentIndex()].append("");
        texName->clear();
        texSelect->blockSignals(true);
        texM.setStringList(texN.at(texGroups->currentIndex()));
        texSelect->setModel(&texM);
        texSelect->update();
        texSelect->blockSignals(false);
        tI[texGroups->currentIndex()]= tI[texGroups->currentIndex()] + 1;
        texSelect->setCurrentIndex(texN.size()-1);
        setTexture();
    }
    lockElements();
}
void matEdit::changeMaterial(int m)
{
    if(m == -1)
    {
        m=0;
    }

    if(comb==1)
    {
        matI = m;
        df->rdiff = diff.at(matGroups->currentIndex()).at(m);
        df->rspec = spec.at(matGroups->currentIndex()).at(m);
        df->ramb = amb.at(matGroups->currentIndex()).at(m);
        switch(i){
            case 0:
            {
                r = df->rdiff.x();
                g = df->rdiff.y();
                b = df->rdiff.z();
                a = df->rdiff.w();
                switchDiffuse();
                break;
            }
            case 1:
            {
                r = df->rspec.x();
                g = df->rspec.y();
                b = df->rspec.z();
                a = 255;
                switchSpecular();
                break;
            }
            case 2:
            {
                r = df->ramb.x();
                g = df->ramb.y();
                b = df->ramb.z();
                a = 255;
                switchAmbient();
                break;
            }
        }
        rS->setValue(r);
        gS->setValue(g);
        bS->setValue(b);
        aS->setValue(a);
        df->update();
        df->repaint();
        txLine->blockSignals(true);
        toonPath->blockSignals(true);
        toonSlot->blockSignals(true);

        if(mats->currentIndex()==-1)
        {
            mats->setCurrentIndex(0);
        }
        if(matT[matGroups->currentIndex()].at(mats->currentIndex())=="0")
        {
            txLine->clear();
            texEnabled->setChecked(false);
        }
        else
        {
            txLine->setText(matT[matGroups->currentIndex()].at(mats->currentIndex()));
            texEnabled->setChecked(true);
        }
        if(toonR[matGroups->currentIndex()].at(mats->currentIndex())==-1)
        {
            toonPath->clear();
            toonEnabled->setChecked(false);
        }
        else
        {
            toonSlot->setCurrentIndex(toonR[matGroups->currentIndex()].at(mats->currentIndex()));
            toonPath->setText(matTn[matGroups->currentIndex()].at(mats->currentIndex()));
            toonEnabled->setChecked(true);
        }
        txLine->blockSignals(false);
        toonPath->blockSignals(false);
        toonSlot->blockSignals(false);

    }
    else
    {
        texI = m;

        texPath->blockSignals(true);
        toonFile->blockSignals(true);
        toonSlots->blockSignals(true);
        if(texSelect->currentIndex()==-1)
        {
            texSelect->setCurrentIndex(0);
        }
        texName->setText(texN[texGroups->currentIndex()].at(texSelect->currentIndex()));
        texPath->setText(texP[texGroups->currentIndex()].at(texSelect->currentIndex()));
        if(toonT[texGroups->currentIndex()].at(texSelect->currentIndex())==-1)
        {
            toonFile->clear();
            toonBox->setChecked(false);
        }
        else
        {
            toonSlots->setCurrentIndex(toonT[texGroups->currentIndex()].at(texSelect->currentIndex()));
            toonFile->setText(texTn[texGroups->currentIndex()].at(texSelect->currentIndex()));
            toonBox->setChecked(true);
        }
        texPath->blockSignals(false);
        toonFile->blockSignals(false);
        toonSlots->blockSignals(false);
    }
    lockElements();
}
void matEdit::renameComment()
{
    if(comb==1)
    {
        matGc[matGroups->currentIndex()] = cLine->text();
    }
    else
    {
        texGc[texGroups->currentIndex()] = tgcLine->text();
    }
}
void matEdit::renameTexture()
{
    if(comb==1)
    {
        matT[matGroups->currentIndex()].at(mats->currentIndex()) = txLine->text();
    }
    else
    {
        std::cout<<texSelect->currentIndex()<<std::endl;
        texP[texGroups->currentIndex()].at(texSelect->currentIndex()) = texPath->text();
    }
}
void matEdit::setTexture()
{
    if(comb==1)
    {
        txLine->setText(QFileDialog::getOpenFileName(this,"Select a texture",QString(getenv("HOME")),"Bitmap images (*.bmp);;Portable Network Graphics (*.png);;JPEG images (*.jpg, *.jpeg)"));
        int tx = txLine->text().lastIndexOf("/");
        txLine->setText(txLine->text().mid(tx+1));

    }
    else
    {
        texSelect->setCurrentIndex(texN[texGroups->currentIndex()].size()-1);
        texPath->setText(QFileDialog::getOpenFileName(this,"Select a texture",QString(getenv("HOME")),"Bitmap images (*.bmp);;Portable Network Graphics (*.png);;JPEG images (*.jpg, *.jpeg)"));
        int tx2 = texPath->text().lastIndexOf("/");
        texPath->setText(texPath->text().mid(tx2+1));
        texP[texGroups->currentIndex()].at(texSelect->currentIndex()) = texPath->text();
        //texPath->clear();

    }
}
void matEdit::changeGroup(int gr1)
{
    if(comb==1)
    {
        groupI = gr1;
        matGroups->blockSignals(true);
        cLine->blockSignals(true);
        txLine->blockSignals(true);
        toonPath->blockSignals(true);
        toonSlot->blockSignals(true);
        std::cout<<gr1<<std::endl;
        matLine->clear();
        cLine->setText(matGc.at(gr1));

        if(mI[gr1]==0)
        {
        }
        else
        {
            matM.stringList().detach();
            matM.setStringList(matN.at(gr1));
            mats->setModel(&matM);
            mats->update();
            changeMaterial(0);
        }
        matGroups->blockSignals(false);
        cLine->blockSignals(false);
        txLine->blockSignals(false);
        toonPath->blockSignals(false);
        toonSlot->blockSignals(false);
    }
    else
    {
        tGroupI = gr1;
        texGroups->blockSignals(true);
        tgcLine->blockSignals(true);
        texPath->blockSignals(true);
        toonFile->blockSignals(true);
        toonSlots->blockSignals(true);
        std::cout<<gr1<<std::endl;
        texName->clear();
        tgcLine->setText(texGc.at(gr1));

        if(tI[gr1]==0)
        {
        }
        else
        {
            texM.setStringList(texN.at(gr1));
            texSelect->setModel(&texM);
            texSelect->update();
            changeMaterial(0);
        }
        texGroups->blockSignals(false);
        tgcLine->blockSignals(false);
        texPath->blockSignals(false);
        toonFile->blockSignals(false);
        toonSlots->blockSignals(false);

    }
    lockElements();
}
void matEdit::enableTex()
{
    if(texEnabled->isChecked()==true)
    {
        if(matT[matGroups->currentIndex()].at(mats->currentIndex())=="0")
        {
            matT[matGroups->currentIndex()].at(mats->currentIndex()) = QString("");
        }
    }
    else
    {
        matT[matGroups->currentIndex()].at(mats->currentIndex()) = QString("0");
        txLine->clear();
        txLine->update();
    }
    lockElements();
}
void matEdit::overrideToon()
{
    if(comb==1)
    {
        if(toonEnabled->isChecked()==true)
        {
            if(toonR[matGroups->currentIndex()].at(mats->currentIndex()) == -1)
            {
                toonR.at(matGroups->currentIndex()).replace(mats->currentIndex(),0);
                toonSlot->setCurrentIndex(0);
                toonSlot->update();
            }
        }
        else
        {
            toonR.at(matGroups->currentIndex()).replace(mats->currentIndex(),-1);
            matTn[matGroups->currentIndex()].at(mats->currentIndex()) = QString("");
            toonPath->clear();
            toonPath->update();
        }

    }
    else
    {
        if(toonBox->isChecked()==true)
        {
            if(toonT[texGroups->currentIndex()].at(texSelect->currentIndex()) == -1)
            {
                toonT.at(texGroups->currentIndex()).replace(texSelect->currentIndex(),0);
                toonSlots->setCurrentIndex(0);
                toonSlots->update();
            }
        }
        else
        {
            toonT.at(texGroups->currentIndex()).replace(texSelect->currentIndex(),-1);
            texTn[texGroups->currentIndex()].at(texSelect->currentIndex()) = QString("");
            toonFile->clear();
            toonFile->update();
        }
    }
    lockElements();
}
void matEdit::setToonSlot()
{
    if(comb==1)
    {
        toonR[matGroups->currentIndex()].replace(mats->currentIndex(),toonSlot->currentIndex());
    }
    else
    {
        toonT[texGroups->currentIndex()].replace(texSelect->currentIndex(),toonSlots->currentIndex());
    }
}
void matEdit::setToonFile()
{
    if(comb==1)
    {
        toonPath->setText(QFileDialog::getOpenFileName(this,"Select toon",QString(),QString("Bitmap images (*.bmp);;Portable Network Graphics (*.png);;JPEG images (*.jpg, *.jpeg)")));
        int tx3 = toonPath->text().lastIndexOf("/");
        toonPath->setText(toonPath->text().mid(tx3));
        matTn[matGroups->currentIndex()].at(mats->currentIndex()) = toonPath->text();
    }
    else
    {
        toonFile->setText(QFileDialog::getOpenFileName(this,"Select toon",QString(),QString("Bitmap images (*.bmp);;Portable Network Graphics (*.png);;JPEG images (*.jpg, *.jpeg)")));
        int tx4 = toonFile->text().lastIndexOf("/");
        toonFile->setText(toonFile->text().mid(tx4));
        texTn[texGroups->currentIndex()].at(texSelect->currentIndex()) = toonFile->text();
    }
}
void matEdit::renameToon()
{
    if(comb==1)
    {
        matTn[matGroups->currentIndex()].at(mats->currentIndex()) = toonPath->text();
    }
    else
    {
        texTn[texGroups->currentIndex()].at(texSelect->currentIndex()) = toonFile->text();
    }
}
void matEdit::lockElements()
{
    if(comb==1)
    {
        if(grI==0)
        {
            matLine->setEnabled(false);
            mats->setEnabled(false);
            addMat->setEnabled(false);
            cLine->setEnabled(false);
        }
        else
        {
            matLine->setEnabled(true);
            mats->setEnabled(true);
            addMat->setEnabled(true);
            cLine->setEnabled(true);
        }

        if(mI.size()==0||mI.at(groupI)==0)
        {
            db->setEnabled(false);
            sb->setEnabled(false);
            ab->setEnabled(false);
            rS->setEnabled(false);
            gS->setEnabled(false);
            bS->setEnabled(false);
            aS->setEnabled(false);
            rC->setEnabled(false);
            gC->setEnabled(false);
            bC->setEnabled(false);
            aC->setEnabled(false);
            texEnabled->setEnabled(false);
            toonEnabled->setEnabled(false);
            toonSlot->setEnabled(false);
            toonPath->setEnabled(false);
            setToon->setEnabled(false);
        }
        else
        {
            db->setEnabled(true);
            sb->setEnabled(true);
            ab->setEnabled(true);
            rS->setEnabled(true);
            gS->setEnabled(true);
            bS->setEnabled(true);
            aS->setEnabled(true);
            rC->setEnabled(true);
            gC->setEnabled(true);
            bC->setEnabled(true);
            aC->setEnabled(true);
            texEnabled->setEnabled(true);
            txLine->setEnabled(true);
            addTex->setEnabled(true);
            toonEnabled->setEnabled(true);
            toonSlot->setEnabled(true);
            toonPath->setEnabled(true);
            setToon->setEnabled(true);
        }
        if(texEnabled->checkState()==Qt::Unchecked)
        {
            txLine->setEnabled(false);
            addTex->setEnabled(false);
        }
        else
        {
            txLine->setEnabled(true);
            addTex->setEnabled(true);
        }
        if(toonEnabled->checkState()==Qt::Unchecked)
        {
            toonSlot->setEnabled(false);
            toonPath->setEnabled(false);
            setToon->setEnabled(false);
        }
        else
        {
            toonSlot->setEnabled(true);
            toonPath->setEnabled(true);
            setToon->setEnabled(true);
        }
    }
    else
    {
        if(tgI==0)
        {
            texPath->setEnabled(false);
            texSelect->setEnabled(false);
            addTex2->setEnabled(false);
            tgcLine->setEnabled(false);
        }
        else
        {
            texPath->setEnabled(true);
            texSelect->setEnabled(true);
            addTex2->setEnabled(true);
            tgcLine->setEnabled(true);
        }

        if(tI.size()==0||tI.at(tGroupI)==0)
        {
            toonBox->setEnabled(false);
            toonSlots->setEnabled(false);
            toonFile->setEnabled(false);
            setTexToon->setEnabled(false);
        }
        else
        {
            toonBox->setEnabled(true);
            toonSlots->setEnabled(true);
            toonFile->setEnabled(true);
            setTexToon->setEnabled(true);
        }
        if(toonBox->checkState()==Qt::Unchecked)
        {
            toonSlots->setEnabled(false);
            toonFile->setEnabled(false);
            setTexToon->setEnabled(false);
        }
        else
        {
            toonSlots->setEnabled(true);
            toonFile->setEnabled(true);
            setTexToon->setEnabled(true);
        }
    }
}
