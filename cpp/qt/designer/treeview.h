/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Dockable tree view widget made in Qt Designer with C++              ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QDockWidget>

namespace Ui {
  class TreeView;
}

class TreeView : public QDockWidget
{
  Q_OBJECT

public:
  explicit TreeView(QWidget *parent = nullptr);
  ~TreeView();

private:
  Ui::TreeView *ui;
};

#endif // TREEVIEW_H
