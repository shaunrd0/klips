/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Dockable tree view widget made in Qt Designer with C++              ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "treeview.h"
#include "ui_treeview.h"

TreeView::TreeView(QWidget *parent) :
  QDockWidget(parent),
  ui(new Ui::TreeView)
{
  ui->setupUi(this);
}

TreeView::~TreeView()
{
  delete ui;
}
