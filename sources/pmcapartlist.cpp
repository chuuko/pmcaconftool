#include "pmcapartlist.h"


pmcaPartList::pmcaPartList()
{
    status = 0;

    pmcaList = new QFile();
    pmcaMatList = new QFile();
    pmcaTexList = new QFile();

}
pmcaPartList::~pmcaPartList()
{}
void pmcaPartList::setPartName(int n, QString &pmcaPartName)
{
    names.append(pmcaPartName);

}
void pmcaPartList::setComment(int n, QString &pmcaComment)
{
    com.append(pmcaComment);
}
void pmcaPartList::setGroup(int n, int gr)
{
    mainGroup[n] = gr;
}
void pmcaPartList::setFileName(int n, QString &pmcaFileName)
{
    files.append(pmcaFileName);
}
void pmcaPartList::fillLink(int n, QString l)
{
    QStringList joint;

    joint.reserve(10000);

    if(l.contains("blz_ribbon"))
    {
        joint.append("Bowtie");
    }

    if(l.contains("head"))
    {
        joint.append("Head");
    }

    if(l.contains("hair_mf1"))
    {
        joint.append("Front hair");
    }

    if(l.contains("hair_mr1"))
    {
        joint.append("Back hair");
    }

    if(l.contains("hair_df1"))
    {
        joint.append("Full hair");
    }

    if(l.contains("hair_op"))
    {
        joint.append("Back hair pieces");
    }

    if(l.contains("head_acce"))
    {
        joint.append("Head accessory");
    }

    if(l.contains("arm"))
    {
        joint.append("Arm");
    }

    if(l.contains("hand"))
    {
        joint.append("Hand");
    }

    if(l.contains("hand_acce"))
    {
        joint.append("Hand accessory");
    }

    if(l.contains("lb_sk"))
    {
        joint.append("Skirt");
    }

    if(l.contains("lb_sl"))
    {
        joint.append("Male pants");
    }

    if(l.contains("lb_fsl"))
    {
        joint.append("Female pants");
    }

    if(l.contains("shoes"))
    {
        joint.append("Shoes");
    }

    if(l.contains("body_acce"))
    {
        joint.append("Body accessory");
    }

    linkGroups.resize(10000);
    linkGroups[n] = joint;
}
void pmcaPartList::pmcaRead(QString path, QString matPath, QString texPath)
{
    pmcaList->setFileName(path);
    pmcaList->open(QIODevice::ReadWrite | QFile::Text);



    names.reserve(10000);
    com.reserve(10000);
    files.reserve(10000);
    linkGroups.reserve(10000);
    pmcaAmb.reserve(10000);
    pmcaDiff.reserve(10000);
    pmcaSpec.reserve(10000);
    pmcaTex.reserve(10000);
    pmcaToon.reserve(10000);
    matGroup.reserve(10000);
    matName.reserve(10000);
    matGrComment.reserve(10000);
    texList.reserve(10000);
    texComment.reserve(10000);
    pmcaTexName.reserve(10000);
    pmcaTexPath.reserve(10000);
    pmcaTexToon.reserve(10000);

    pmcaStream = new QTextStream(pmcaList);


    QString ln, ln2, ln3;

    num = 0;


    while(pmcaStream->atEnd()==false)
    {
        ln = pmcaStream->readLine();
        if (ln.contains("PMCA Parts list v1.0"))
        {
            pmcaList->close();

            status = 1;
        }
        else
        {
            if (ln.contains("SETDIR"))
            {
                partsRoot = ln.remove(0,7);
            }

            else
            {
                if (ln.contains("[name]"))
                {
                    setPartName(num,ln.remove(0,7));
                }

                if (ln.contains("[comment]"))
                {
                    setComment(num,ln.remove(0,10));
                }

                if (ln.contains("[type]"))
                {
                    if(ln.contains("root"))
                    {
                        setGroup(num,0);
                    }

                    if(ln.contains("blz_ribbon"))
                    {
                        setGroup(num,1);
                    }

                    if(ln.contains("head"))
                    {
                        setGroup(num,2);
                    }

                    if(ln.contains("hair_mf1"))
                    {
                        setGroup(num,3);
                    }

                    if(ln.contains("hair_mr1"))
                    {
                        setGroup(num,4);
                    }

                    if(ln.contains("hair_df1"))
                    {
                        setGroup(num,5);
                    }

                    if(ln.contains("hair_op"))
                    {
                        setGroup(num,6);
                    }

                    if(ln.contains("head_acce"))
                    {
                        setGroup(num,7);
                    }

                    if(ln.contains("arm"))
                    {
                        setGroup(num,8);
                    }

                    if(ln.contains("hand"))
                    {
                        setGroup(num,9);
                    }

                    if(ln.contains("hand_acce"))
                    {
                        setGroup(num,10);
                    }

                    if(ln.contains("lb_sk"))
                    {
                        setGroup(num,11);
                    }

                    if(ln.contains("lb_sl"))
                    {
                        setGroup(num,12);
                    }

                    if(ln.contains("lb_fsl"))
                    {
                        setGroup(num,13);
                    }

                    if(ln.contains("shoes"))
                    {
                        setGroup(num,14);
                    }

                    if(ln.contains("body_acce"))
                    {
                        setGroup(num,15);
                    }
                }

                if (ln.contains("[path]"))
                {
                    setFileName(num,ln.remove(0,7));
                }

                if (ln.contains("[joint]"))
                {
                    fillLink(num,ln);
                }

                if (ln.contains("NEXT"))
                {
                    num++;
                }

            }


        }
    }
    num = 0;
    pmcaMatList->setFileName(matPath);
    if(pmcaMatList->exists()==true)
    {
        pmcaMatList->open(QIODevice::ReadWrite | QFile::Text);
        pmcaMatStream = new QTextStream(pmcaMatList);



        while(pmcaMatStream->atEnd()==false)
        {

            ln2 = pmcaMatStream->readLine();
            if(ln2=="PMCA Materials list v1.0")
            {
                std::cout<<"Unsupported material list version"<<std::endl;
                pmcaMatList->close();
                status = 1;
            }
            else
            {
                if (ln.contains("SETDIR"))
                {
                    partsRoot = ln.remove(0,7);
                }
                if(ln2.mid(0,6)=="[name]")
                {
                    matGroup.append(ln2.mid(7));
                    matName.append(QStringList());
                    matName[num].reserve(10000);
                    pmcaDiff.append(QVector<QVector4D>());
                    pmcaDiff[num].reserve(10000);
                    pmcaSpec.append(QVector<QVector3D>());
                    pmcaSpec[num].reserve(10000);
                    pmcaAmb.append(QVector<QVector3D>());
                    pmcaAmb[num].reserve(10000);
                    pmcaTex.append(QStringList());
                    pmcaTex[num].reserve(10000);
                    pmcaToon.append(QStringList());
                    pmcaToon[num].reserve(10000);
                }
                if(ln2.mid(0,9)=="[comment]")
                {
                    matGrComment.append(ln2.mid(10));
                }
                int mn = 0;
                if(ln2.mid(0,7)=="[ENTRY]")
                {
                    matName[num].append(ln2.mid(8));
                    pmcaToon[num].append(QString::number(-1)+" ");
                    mn++;
                }

                if(ln2.mid(0,10)=="[diff_rgb]")
                {
                    pmcaDiff[num].append(QVector4D(ln2.mid(11,8).toFloat(),ln2.mid(20,8).toFloat(),ln2.mid(29,8).toFloat(),255));
                }
                if(ln2.mid(0,10)=="[spec_rgb]")
                {
                    pmcaSpec[num].append(QVector3D(ln2.mid(11,8).toFloat(),ln2.mid(20,8).toFloat(),ln2.mid(29,8).toFloat()));
                }
                if(ln2.mid(0,10)=="[mirr_rgb]")
                {
                    pmcaAmb[num].append(QVector3D(ln2.mid(11,8).toFloat(),ln2.mid(20,8).toFloat(),ln2.mid(29,8).toFloat()));
                }
                if(ln2.mid(0,5)=="[tex]")
                {
                    pmcaTex[num].append(ln2.mid(6));
                }

                if(ln2.mid(0,6)=="[toon]")
                {
                    pmcaToon[num].at(pmcaToon[num].length()-1)=ln2.mid(7);
                }

                if(ln2=="NEXT")
                {
                    num++;
                }
            }
        }
    }
    num = 0;
    pmcaTexList->setFileName(texPath);
    if(pmcaTexList->exists()==true)
    {
        pmcaTexList->open(QIODevice::ReadWrite | QFile::Text);
        pmcaTexStream = new QTextStream(pmcaTexList);
        while(pmcaTexStream->atEnd()==false)
        {
            ln3=pmcaTexStream->readLine();
            if(ln3=="PMCA Materials list v1.0")
            {
                std::cout<<"Unsupported texture list version"<<std::endl;
                pmcaTexList->close();
                status = 1;
            }
            else
            {
                if (ln.contains("SETDIR"))
                {
                    partsRoot = ln.remove(0,7);
                }
                int tCount = 0;
                if(ln3.mid(0,6)=="[name]")
                {
                    texList.append(ln3.mid(7));

                    pmcaTexName.append(QStringList());
                    pmcaTexName[num].reserve(10000);
                    pmcaTexPath.append(QStringList());
                    pmcaTexPath[num].reserve(10000);
                    pmcaTexToon.append(QStringList());
                    pmcaTexToon[num].reserve(10000);
                }
                if(ln3.mid(0,9)=="[comment]")
                {
                    texComment.append(ln3.mid(10));
                }
                if(ln3.mid(0,7)=="[ENTRY]")
                {
                    pmcaTexName[num].append(ln3.mid(8));
                    pmcaTexToon[num].append("-1 ");
                    tCount++;
                }
                if(ln3.mid(0,5)=="[tex]")
                {
                    pmcaTexPath[num].append(ln3.mid(6));
                }
                if(ln3.mid(0,6)=="[toon]")
                {
                    pmcaTexToon[num].at(pmcaTexToon[num].length()-1) = ln3.mid(7);
                }
                if(ln3=="NEXT")
                {
                    num++;
                }
            }
        }
    }
}
void pmcaPartList::pmcaWrite(QString path, QVector<QString> *nm, QVector<QString> *cm, QVector<QString> *fn, QVector<int> *pgr, QVector<QStringList> *lk, QString matPath, QStringList mgr, QStringList mgc, QVector<QStringList> mName,QVector<QVector<QVector4D> > diffs,QVector<QVector<QVector3D> > specs,QVector<QVector<QVector3D> > ambs,QVector<QStringList> mTex,QVector<QVector<int> > mTn,QVector<QStringList> mTt,QString texListPath,QStringList texGroupsList, QStringList texGComm, QVector<QStringList> texNames,QVector<QStringList> texFiles, QVector<QVector<int> > toonNums,QVector<QStringList> toonFiles)
{
    if(nm->size()!=0)
    {
        pmcaList->setFileName(path);
        if(pmcaList->exists()==true)
        {
            pmcaList->remove();
        }
        pmcaList->open(QIODevice::ReadWrite|QIODevice::Text);
        QTextStream writeList(pmcaList);
        writeList << QString("PMCA Parts list v2.0") << endl << endl << QString("SETDIR ")<<partsRoot<< endl;
        QString gStr = "";
        int gC = 0;
        QString gs = "";
        for (int pw = 0; pw < nm->indexOf(nm->last())-gC;pw++)
        {
            if(nm->at(pw).isNull()==true)
            {}
            else
            {
                if(nm->at(pw)!=gStr)
                {
                    if(pw!=0)
                    {
                        writeList << QString("\nNEXT") << endl ;
                    }
                    writeList << QString("\n[name] ") << nm->at(pw) << endl
                                << QString("[comment] ") << cm->at(pw) << endl
                                    << QString("[path] ") <<  fn->at(pw) << endl;

                    switch(pgr->at(pw))
                    {

                        case 1:
                        {
                            gs = "blz_ribbon";
                            break;
                        }

                        case 2:
                        {
                            gs = "head";
                            break;
                        }

                        case 3:
                        {
                            gs = "hair_mf1";
                            break;
                        }

                        case 4:
                        {
                            gs = "hair_mr1";
                            break;
                        }

                        case 5:
                        {
                            gs = "hair_df1";
                            break;
                        }

                        case 6:
                        {
                            gs = "hair_op";
                            break;
                        }

                        case 7:
                        {
                            gs = "head_acce";
                            break;
                        }

                        case 8:
                        {
                            gs = "arm";
                            break;
                        }

                        case 9:
                        {
                            gs = "hand";
                            break;
                        }

                        case 10:
                        {
                            gs = "hand_acce";
                            break;
                        }

                        case 11:
                        {
                            gs = "lb_sk";
                            break;
                        }

                        case 12:
                        {
                            gs = "lb_sl";
                            break;
                        }

                        case 13:
                        {
                            gs = "lb_fsl";
                            break;
                        }

                        case 14:
                        {
                            gs = "shoes";
                            break;
                        }

                        case 15:
                        {
                            gs = "body_acce";
                            break;
                        }
                        default:
                        {
                            gs = "root";
                            break;
                        }

                    }
                    writeList << QString("[type] ") << gs << endl;

                    writeList << QString("[joint] ");

                    QString jt = "";
                    for(int jn = 0; jn < lk->value(pw).length();jn++)
                    {
                        if(lk->value(pw).at(jn)=="Root")
                        {
                            jt = "root";
                        }
                        if(lk->value(pw).at(jn)=="Bowtie")
                        {
                            jt = "blz_ribbon";
                        }
                        if(lk->value(pw).at(jn)=="Head")
                        {
                            jt = "head";
                        }
                        if(lk->value(pw).at(jn)=="Front hair")
                        {
                            jt = "hair_mf1";
                        }
                        if(lk->value(pw).at(jn)=="Back hair")
                        {
                            jt = "hair_mr1";
                        }
                        if(lk->value(pw).at(jn)=="Full hair")
                        {
                            jt = "hair_df1";
                        }
                        if(lk->value(pw).at(jn)=="Back hair pieces")
                        {
                            jt = "hair_op";
                        }
                        if(lk->value(pw).at(jn)=="Head accessory")
                        {
                            jt = "head_acce";
                        }
                        if(lk->value(pw).at(jn)=="Hand")
                        {
                            jt = "hand";
                        }
                        if(lk->value(pw).at(jn)=="Arm")
                        {
                            jt = "arm";
                        }
                        if(lk->value(pw).at(jn)=="Hand accessory")
                        {
                            jt = "hand_acce";
                        }
                        if(lk->value(pw).at(jn)=="Skirt")
                        {
                            jt = "lb_sk";
                        }
                        if(lk->value(pw).at(jn)=="Male pants")
                        {
                            jt = "lb_sl";
                        }
                        if(lk->value(pw).at(jn)=="Female pants")
                        {
                            jt = "lb_fsl";
                        }
                        if(lk->value(pw).at(jn)=="Shoes")
                        {
                            jt = "shoes";
                        }
                        if(lk->value(pw).at(jn)=="Body accessory")
                        {
                            jt = "body_acce";
                        }
                        if(jn<lk->value(pw).length()-1)
			{
			  writeList << jt << ",";
			}
			else
			{
			  writeList << jt;
			}
                    }
                    writeList << endl;

                }
                else
                {
                    gC++;
                }
            }
            gStr = nm->at(pw);
        }
        std::cout << nm->indexOf(nm->last())-gC;
    }
    if(mgr.length()!=0)
    {
        pmcaMatList->setFileName(matPath);
        if(pmcaMatList->exists()==true)
        {
            pmcaMatList->remove();
        }
        pmcaMatList->open(QIODevice::ReadWrite|QIODevice::Text);

        QTextStream matStream(pmcaMatList);

        matStream << "PMCA Materials list v2.0" <<endl <<endl <<"SETDIR " <<partsRoot<<endl<<endl;

        for(int toGo=0;toGo<mgr.size();toGo++)
        {
            matStream << "[name] " << mgr[toGo]<<endl;
            matStream << "[comment] "<< mgc[toGo]<<endl<<endl;

            for(int toGo2=0;toGo2<mName[toGo].size();toGo2++)
            {
                matStream << "[ENTRY] " << mName[toGo].at(toGo2) <<endl<<endl;
                matStream << "[tex] " << mTex[toGo].at(toGo2) <<endl;
                matStream << "[diff_rgb] " <<diffs[toGo].at(toGo2).x()/(float)255<<" "<<diffs[toGo].at(toGo2).y()/(float)255<<" "<< diffs[toGo].at(toGo2).z()/(float)255<<endl;
                matStream << "[spec_rgb] " <<specs[toGo].at(toGo2).x()/(float)255<<" "<<specs[toGo].at(toGo2).y()/(float)255<<" "<< specs[toGo].at(toGo2).z()/(float)255<<endl;
                matStream << "[amb_rgb] " <<ambs[toGo].at(toGo2).x()/(float)255<<" "<<ambs[toGo].at(toGo2).y()/(float)255<<" "<< ambs[toGo].at(toGo2).z()/(float)255<<endl;
                if(mTn[toGo].at(toGo2)!=-1)
                {
                    matStream <<"[toon] "<<mTn[toGo].at(toGo2)<<" "<<mTt[toGo].at(toGo2)<<endl;
                }
                matStream<<endl;
            }
            matStream<<"NEXT"<<endl;
        }
        matStream<<endl;
    }
    if(texGroupsList.length()!=0)
    {
        pmcaTexList->setFileName(texListPath);
        if(pmcaTexList->exists()==true)
        {
            pmcaTexList->remove();
        }

        pmcaTexList->open(QIODevice::ReadWrite|QIODevice::Text);

        QTextStream texStream(pmcaTexList);

        texStream << "PMCA Materials list v2.0" <<endl <<endl <<"SETDIR " <<partsRoot<<endl<<endl;

        for(int toGo3=0;toGo3<texGroupsList.size();toGo3++)
        {
            texStream << "[name] " << texGroupsList[toGo3]<<endl;
            texStream << "[comment] "<< texGComm[toGo3]<<endl<<endl;

            for(int toGo4=0;toGo4<texNames[toGo3].size();toGo4++)
            {
                texStream << "[ENTRY] " << texNames[toGo3].at(toGo4) <<endl<<endl;
                texStream << "[tex] " << texFiles[toGo3].at(toGo4) <<endl;

                if(toonNums[toGo3].at(toGo4)!=-1)
                {
                    texStream <<"[toon] "<<toonNums[toGo3].at(toGo4)<<" "<<toonFiles[toGo3].at(toGo4)<<endl;
                }
                texStream<<endl<<endl;
            }
            texStream<<"NEXT"<<endl;
        }
        texStream<<endl;
    }
    pmcaList->close();
    pmcaMatList->close();
    pmcaTexList->close();
}
