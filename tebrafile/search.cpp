#include "search.h"

Search::Search(QSharedPointer<ListFiles> treeWidget, QString filename, QString path)
    :_treeWidget(treeWidget), _filename(filename), _path(path)
{

}
