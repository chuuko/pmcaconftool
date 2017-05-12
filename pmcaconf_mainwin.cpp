#include "pmcaconf_mainwin.h"
#include "ui_pmcaconf_mainwin.h"

pmcaPartList plist;

pmcaconf_mainwin::pmcaconf_mainwin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pmcaconf_mainwin)
{
    partList = new QVector<QString>(10000);
    commList = new QVector<QString>(10000);
    fileList = new QVector<QString>(10000);
    group = new QVector<int>(10000);
    partRef = new QVector<int>(10000);
    links = new QVector<QStringList>(10000);

    partList->begin();
    commList->begin();
    fileList->begin();
    group->begin();

    listIterator=0;

    aGr = 0;

    listI = 0;

    pos = 0;

    pos2 = 0;

    setLocale(QLocale::English);

    ui->statusBar = new QStatusBar(this);

    ui->actionAbout =new QAction(this);
    ui->actionAdd_part = new QAction(this);
    ui->actionDelete_part = new QAction(this);

    ui->lineEdit_Name = new QLineEdit();

    setStatusBar(ui->statusBar);
    ui->actionOpen_configuration=new QAction(this);
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(ui->actionOpen_configuration,SIGNAL(triggered()),this,SLOT(openConfig()));
    connect(ui->actionAdd_part,SIGNAL(triggered()),this,SLOT(addNewPart()));
    connect(ui->actionDelete_part,SIGNAL(triggered()),this,SLOT(deletePart()));
    ui->listView = new QListView();
    ui->listView_parts = new QListView();
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
    groupList->append("Full hair");
    groupList->append("Back hair pieces");
    groupList->append("Head accessory");
    groupList->append("Arm");
    groupList->append("Hand");
    groupList->append("Hand accessory");
    groupList->append("Skirt");
    groupList->append("Male pants");
    groupList->append("Female pants");
    groupList->append("Shoes");
    groupList->append("Body accessory");

    aGroups += *groupList;

    groups = new QStringListModel(*groupList,this);

    ll2 = new QStringListModel(aGroups,this);


    ui->listView_availableGroups = new QListView();
    ui->listView_parts = new QListView();

}
void pmcaconf_mainwin::populateLinkList()
{
    ui->listView_availableGroups->setModel(ll2);
    ui->listView_availableGroups->update();
    ll = new QStringListModel(this);
    ui->listView_4->setModel(ll);
    ui->listView_4->update();
    ui->listView->setModel(groups);
    groups->index(0);
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(groupChanged(QModelIndex)));
    connect(ui->listView_availableGroups,SIGNAL(clicked(QModelIndex)),this,SLOT(addLink(QModelIndex)));
    ui->listView->update();   
}

void pmcaconf_mainwin::groupChanged(QModelIndex m)
{
    aGr = m.row();
    populatePartList();
}

void pmcaconf_mainwin::populatePartList()
{
    i = 0;
    pts = new QStringList();
    pts->reserve(10000);
    for(listIterator=0;listIterator<plist.names.length()+listI;listIterator++)
    {

        if(group->at(listIterator)==aGr)
        {
            pts->append(partList->at(listIterator));
            partRef->insert(i,listIterator);
            i++;
        }
    }

    pt = new QStringListModel(*pts);
    ui->listView_parts->setModel(pt);
    connect(ui->listView_parts,SIGNAL(clicked(QModelIndex)),this,SLOT(updateDetails(QModelIndex)));
}

void pmcaconf_mainwin::showAbout()
{
    pmcaAbout=new QDialog(this);
    pmcaAbout->setGeometry(0,0,300,200);
    pmcaAbout->setWindowTitle("About");
    QIcon *logo=new QIcon("://logo/logo.png");
    logo->addPixmap(QPixmap("/home/cincin/PMCAConfTool/logo.png"),QIcon::Normal);
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



    if (selDir->Accepted)
    {
        ui->lineEdit_list->setText(prefix);
        ui->lineEdit_list->update();
        plist.pmcaRead(QString(selDir->getExistingDirectory()+"/"+prefix+"_parts_list.txt"));
        if (plist.status==1)
        {
            QMessageBox::warning(this,"Error","Unsupported part list version");
            ui->lineEdit_list->clear();
            ui->lineEdit_5->clear();
        }

        if (!plist.partsRoot.isNull())
        {
            ui->lineEdit_5->setText(plist.partsRoot);
            ui->lineEdit_5->update();
        }

        populateLinkList();
        for(listIterator;listIterator<plist.names.length()-1;listIterator++)
        {
            partList->insert(listIterator,sizeof(plist.names),plist.names.at(listIterator));
            commList->insert(listIterator,sizeof(plist.com),plist.com.at(listIterator));
            fileList->insert(listIterator,sizeof(plist.files),plist.files.at(listIterator));
            group->insert(listIterator,sizeof(plist.mainGroup),plist.mainGroup[listIterator]);
            links->insert(listIterator,sizeof(plist.linkGroups),plist.linkGroups[listIterator]);
        }

        ui->lineEdit_Name->setText(partList->value(listIterator));
        ui->lineEdit_Name->update();
        ui->lineEdit_2->setText(commList->value(listIterator));
        ui->lineEdit_2->update();
        ui->lineEdit_3->setText(fileList->value(listIterator));
        ui->lineEdit_3->update();
        ll->setStringList(links->value(listIterator));
        ui->listView_4->update();

        populatePartList();
    }
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

    partCom = new QLineEdit(this);

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

    addPart->setLayout(partLayout);

    partLayout->insertRow(0, addPartLabel);
    partLayout->insertRow(1,"Name: ",partName);
    partLayout->insertRow(2,"Comment: ",partCom);
    partLayout->insertRow(3,fileArea);
    partLayout->insertRow(4,"Group: ",typeSelect);
    partLayout->insertRow(5,partButs);


    addPart->show();

}
void pmcaconf_mainwin::partAccepted()
{
    addPart->close();
    populateLinkList();
    partList->insert(listIterator,sizeof(partName),partName->text());
    commList->insert(listIterator,sizeof(partCom),partCom->text());
    fileList->insert(listIterator,sizeof(partPath),partPath->text());
    group->insert(listIterator,sizeof(typeSelect),typeSelect->currentIndex());
    ui->lineEdit_Name->setText(partList->value(listIterator));
    ui->lineEdit_Name->update();
    ui->lineEdit_2->setText(commList->value(listIterator));
    ui->lineEdit_3->setText(fileList->value(listIterator));
    ui->lineEdit_3->update();
    listI++;
    populatePartList();
    listIterator++;
}
void pmcaconf_mainwin::partRejected()
{

    addPart->close();
}
void pmcaconf_mainwin::addLink(QModelIndex m)
{
    QStringList list2 = links->value(pos);
    list2.append(aGroups.at(m.row()));
    list2.removeDuplicates();
    links->replace(pos,list2);
    ll->setStringList(links->value(pos));
    ui->listView_4->update();
    aGroups.removeAt(m.row());
    ll2->setStringList(aGroups);
}
void pmcaconf_mainwin::updateDetails(QModelIndex m)
{
    pos = partRef->at(m.row());
    pos2 = m.row();
    ui->lineEdit_Name->setText(partList->at(pos));
    ui->lineEdit_2->setText(commList->at(pos));
    ui->lineEdit_3->setText(fileList->at(pos));
    ll->setStringList(links->value(pos));
    aGroups.clear();
    aGroups += *groupList;
    for(int d = 0; d<links->at(pos).length();d++)
    {
        QStringList *sr;
        sr = new QStringList(links->value(pos));
        aGroups.removeOne(sr->value(d));
        ll2->setStringList(aGroups);
    }
    ui->listView_4->update();
}
void pmcaconf_mainwin::deletePart()
{
    partList->remove(pos);
    commList->remove(pos);
    fileList->remove(pos);
    group->remove(pos);
    pts->removeAt(pos2);
    listI--;
    ui->lineEdit_Name->setText(partList->at(pos));
    ui->lineEdit_2->setText(commList->at(pos));
    ui->lineEdit_3->setText(fileList->at(pos));
    ll->setStringList(links->value(pos));
    ui->listView_4->update();
}
