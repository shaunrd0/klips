/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Application that uses a custom Qt Designer widget plugin            ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "widget-app.h"
#include "widget-plugin.h"

WidgetApp::WidgetApp(QWidget *parent) : QMainWindow(parent) {
  m_ui = new Ui::MainWindow;
  m_ui->setupUi(this);
}
