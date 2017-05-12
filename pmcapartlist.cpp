#include "pmcapartlist.h"


pmcaPartList::pmcaPartList()
{
    status = 0;
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
void pmcaPartList::pmcaRead(QString path)
{
    pmcaList = new QFile(path);
    pmcaList->open(QIODevice::ReadWrite);

    names.reserve(10000);
    com.reserve(10000);
    files.reserve(10000);
    linkGroups.reserve(10000);

    pmcaStream = new QTextStream(pmcaList);

    QString ln;

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

}
void pmcaPartList::pmcaWrite()
{}
