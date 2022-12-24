/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Collection of widget plugins for Qt Designer                        ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "widgetplugincollection.h"
#include "textview.h"
#include "treeview.h"
#include "widgetplugin.h"

WidgetPluginCollection::WidgetPluginCollection(QObject *parent)
    : QObject(parent), m_collectionName("Klips Widget Plugin Collection") {
  m_collection = {
      new WidgetPlugin(m_collectionName, "Text View Widget", "text-view.h",
                       [](QWidget *parent) { return new TextView(parent); }),
      new WidgetPlugin(m_collectionName, "tree-view",
                       [](QWidget *parent) { return new TreeView(parent); }),

  };
}
QList<QDesignerCustomWidgetInterface *>
WidgetPluginCollection::customWidgets() const {
  return m_collection;
}
