#include "pmcapartlist.h"

pmcaPartList::pmcaPartList(int num, int gr, QString &pmcaPartName, QString &pmcaComment, QString &pmcaFileName, QStringList &pmcaLinkGroups)
{num=0;}
pmcaPartList::~pmcaPartList()
{}
void pmcaPartList::setPartName(int num, QString &pmcaPartName)
{names[num]=pmcaPartName;
 num++;}
void pmcaPartList::setComment(int num, QString &pmcaComment)
{}
void pmcaPartList::setGroup(int num, int gr)
{}
QString pmcaPartList::getPartName(int num)
{return names[num];}
