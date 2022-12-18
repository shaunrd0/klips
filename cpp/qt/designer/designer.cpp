/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: MainWindow for Qt Designer desktop application                      ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include <QtWidgets>

#include "debugconsole.h"
#include "designer.h"
#include "texteditor.h"
#include "treeview.h"

Designer::Designer(QWidget *parent)
    : QMainWindow(parent), designer_(new Ui::Designer) {
  designer_->setupUi(this);
  setCentralWidget(new TextEditor);
  auto debugConsole = new DebugConsole;
  debugConsole->getConsole()->appendPlainText("Test 1");
  debugConsole->getConsole()->appendPlainText("Test 2");

  auto treeView = new TreeView;

  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, debugConsole);
  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, treeView);
  sendTest();
}
