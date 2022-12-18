/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: MainWindow application for practice using signals and slots in Qt   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "slots-app.h"
#include "text-view.h"

SlotsApp::SlotsApp(QWidget *parent) : QMainWindow(parent) {

  auto textBox = new QPlainTextEdit;
  auto textView = new TextView;
  auto frame = new QFrame;

  auto dock = new QDockWidget(this);
  auto dockWidget = new QWidget;
  auto dockWidgetLayout = new QVBoxLayout;
  dockWidgetLayout->addWidget(frame);
  dockWidgetLayout->addWidget(textBox);
  dockWidget->setLayout(dockWidgetLayout);
  dock->setWidget(dockWidget);

  auto dock2 = new QDockWidget(this);
  auto dockWidget2 = new QWidget;
  auto dockWidgetLayout2 = new QVBoxLayout;
  dockWidgetLayout2->addWidget(textView);
  dockWidget2->setLayout(dockWidgetLayout2);
  dock2->setWidget(dockWidget2);

  textBox->setReadOnly(true);
  textBox->appendPlainText("Test 1");
  textBox->appendPlainText("Test 2");

  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dock);
  addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dock2);
  connect(this, &SlotsApp::sendTest, textView, &TextView::test);
  sendTest();
}
