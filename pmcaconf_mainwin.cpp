#include "pmcaconf_mainwin.h"
#include "pmcapartlist.h"
#include "ui_pmcaconf_mainwin.h"

pmcaconf_mainwin::pmcaconf_mainwin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pmcaconf_mainwin)
{
    partList = new QVector<QString>(10000);

    partList->begin();

    listIterator=1;

    setLocale(QLocale::English);

    ui->statusBar = new QStatusBar(this);

    ui->actionAbout =new QAction(this);
    ui->actionAdd_part = new QAction(this);

    ui->lineEdit_Name = new QLineEdit();

    setStatusBar(ui->statusBar);
    //QLabel readyMess(tr("Ready"),this);
    //b->addPermanentWidget(&readyMess);
    ui->actionOpen_configuration=new QAction(this);
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(ui->actionOpen_configuration,SIGNAL(triggered()),this,SLOT(openConfig()));
    connect(ui->actionAdd_part,SIGNAL(triggered()),this,SLOT(addNewPart()));
    //mainLayout = new QGridLayout(this);
    //ui->centralWidget->setLayout(mainLayout);
    ui->listView = new QListView();

    registeredParts = new QStringList();
    ui->listView_parts = new QListView();
    partNames = new QStringListModel(*registeredParts,this);

    buildGroupList();
    ui->setupUi(this);

}

pmcaconf_mainwin::~pmcaconf_mainwin()
{
    delete ui;
}

void pmcaconf_mainwin::buildGroupList()
{
    groupList = new QStringList();
    groupList->append("Root");
    groupList->append("Bowtie");
    groupList->append("Head");
    groupList->append("Front hair");
    groupList->append("Back hair");
    groupList->append("Back hair base");
    groupList->append("Back hair pieces");
    groupList->append("Head accessory");
    groupList->append("Hand");
    groupList->append("Hand accessory");
    groupList->append("Skirt");
    groupList->append("Pants");
    groupList->append("Shoes");
    groupList->append("Body accessory");

    groups = new QStringListModel(*groupList,this);



    //groupSelect->setGeometry(5,61,171,521);

    ui->listView_availableGroups = new QListView();
    //ui->listView_availableGroups->setGeometry(100,100,100,100);
    //groups->setParent(ui->listView);
}
void pmcaconf_mainwin::populateLinkList()
{

    ui->listView_availableGroups->setModel(groups);
    ui->listView_availableGroups->update();

    ui->listView_parts->setModel(partNames);
    partNames->setStringList(*registeredParts);
    ui->listView_parts->update();

    ui->listView->setModel(groups);
    ui->listView->update();

    connect(ui->listView_parts,SIGNAL(clicked(QModelIndex)),this,SLOT(changePartName(partAt)));
}
void pmcaconf_mainwin::showAbout()
{
    pmcaAbout=new QDialog(this);
    pmcaAbout->setGeometry(0,0,300,200);
    pmcaAbout->setWindowTitle("About");
    QIcon *logo=new QIcon("://logo/logo.png");
    logo->addPixmap(QPixmap("//logo/logo.png"),QIcon::Normal);
    logo->addPixmap(QPixmap("://logo/logo.png"),QIcon::Disabled);
    QPushButton *logo2 = new QPushButton(this);
    logo2->setGeometry(0,0,100,100);
    logo2->setFlat(true);
    logo2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    logo2->setIcon(*logo);
    logo2->setIconSize(QSize(100,100));
    logo2->setEnabled(false);
    QLabel *aboutText = new QLabel(this);
    aboutText->setFont(QFont("Liberation Sans Bold",16,12,false));
    aboutText->setText("PMCA set configuration tool");
    aboutText->setGeometry(0,0,20,50);
    aboutText->show();
    QBoxLayout *aboutLayout = new QBoxLayout(QBoxLayout::TopToBottom,this);
    aboutLayout->addWidget(logo2,0,Qt::AlignHCenter);
    aboutLayout->addWidget(aboutText,1,Qt::AlignCenter);
    pmcaAbout->setLayout(aboutLayout);
    pmcaAbout->show();
}

void pmcaconf_mainwin::openConfig()
{
    chooseID = new QDialog(this);
    chooseID->setGeometry(100,100,200,100);

    prefixLabel = new QLabel(this);
    prefixLabel->setText("Please enter your list ID.");

    prefixBox = new QLineEdit(this);

    prefixBox->setGeometry(0,0,100,20);

    prefixOk = new QPushButton("OK",this);

    connect(prefixOk,SIGNAL(released()),this,SLOT(loadConf()));

    idLayout = new QGridLayout(this);

    chooseID->setLayout(idLayout);
    chooseID->layout()->addWidget(prefixLabel);
    chooseID->layout()->addWidget(prefixBox);
    chooseID->layout()->addWidget(prefixOk);
    chooseID->show();




}

void pmcaconf_mainwin::loadConf()
{
    prefix = prefixBox->text();
    chooseID->close();

    selDir = new QFileDialog(this);
    selDir->setAcceptMode(QFileDialog::AcceptOpen);
    selDir->setFileMode(QFileDialog::DirectoryOnly);
    selDir->show();

    ui->lineEdit_list->setText(prefix);
    ui->lineEdit_list->update();
}

void pmcaconf_mainwin::addNewPart()
{

    QLabel *pathLabel;

    addPart = new QDialog(this);
    addPart->setWindowTitle("Add part...");
    addPart->setGeometry(0,0,320,150);

    partLayout = new QFormLayout(this);

    addPartLabel = new QLabel(this);
    addPartLabel->setText("Here you can add a new part to your part list.");


    pathLabel = new QLabel(this);
    pathLabel->setText("File: ");

    partName = new QLineEdit(this);

    partPath = new QLineEdit(this);

    openPart = new QPushButton("Browse...",this);

    fileArea = new QWidget();

    typeSelect = new QComboBox(this);
    typeSelect->addItems(*groupList);

    myLayout = new QGridLayout(this);

    fileArea->setGeometry(0,0,200,20);
    fileArea->setLayout(myLayout);

    fileArea->layout()->addWidget(pathLabel);
    myLayout->addWidget(partPath,0,1);
    myLayout->addWidget(openPart,0,2);

    partButs = new QDialogButtonBox(this);
    partButs->addButton("OK",QDialogButtonBox::AcceptRole);
    partButs->addButton("Cancel",QDialogButtonBox::RejectRole);

    connect(partButs,SIGNAL(accepted()),this,SLOT(partAccepted()));

    connect(partButs,SIGNAL(rejected()),this,SLOT(partRejected()));

    connect(openPart,SIGNAL(released()),this,SLOT(selectPart()));

    addPart->setLayout(partLayout);

    partLayout->insertRow(0, addPartLabel);
    partLayout->insertRow(1,"Name: ",partName);
    partLayout->insertRow(2,fileArea);
    partLayout->insertRow(3,"Group: ",typeSelect);
    partLayout->insertRow(4,partButs);


    addPart->show();

}

void pmcaconf_mainwin::selectPart()
{
    selPart = new QFileDialog(this);
    selPart->setAcceptMode(QFileDialog::AcceptOpen);
    selPart->setFileMode(QFileDialog::ExistingFile);
    partFileName = selPart->getOpenFileName(this,tr("Select a part to continue"),"/home",tr("Polygon Model Data(*.pmd)"));
    //connect(selPart,SIGNAL(accepted()),this,SLOT(setLoadedPartName()));
    //For some reason, the signals for file dialogs are buggy
    if (selPart->Accepted)
    {//int countindex = partFileName.lastIndexOf();
        setLoadedPartName();}

}

void pmcaconf_mainwin::setLoadedPartName()
{
    partPath->setText(partFileName);
    partPath->update();
}
void pmcaconf_mainwin::partAccepted()
{
    addPart->close();

    partList->insert(listIterator,sizeof(partName),partName->text());
    registeredParts->insert(listIterator,partName->text());
    populateLinkList();
    ui->lineEdit_Name->setText(partList->value(listIterator));
    ui->lineEdit_Name->update();
    ui->lineEdit_3->setText(partFileName);
    ui->lineEdit_3->update();
    listIterator++;
}
void pmcaconf_mainwin::partRejected()
{

    addPart->close();
}

void pmcaconf_mainwin::changePartName(QModelIndex partAt)
{

}
