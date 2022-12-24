/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Tree viewer                                                         ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef KLIPS_TREEVIEW_H
#define KLIPS_TREEVIEW_H

#include "widget-plugin-library_export.h"
#include <app-dir.h>

#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QTreeView>

class WIDGET_PLUGIN_LIBRARY_EXPORT TreeView : public QTreeView {
  Q_OBJECT

public:
  explicit TreeView(QWidget *parent = nullptr) : QTreeView(parent) {
    QFileSystemModel *model = new QFileSystemModel;
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    QModelIndex rootModelIndex = model->setRootPath(APP_DIR);
    proxy->setSourceModel(model);
    setModel(proxy);
    setRootIndex(proxy->mapFromSource(rootModelIndex));
  }

  ~TreeView() = default;
};

#endif // KLIPS_TREEVIEW_H
