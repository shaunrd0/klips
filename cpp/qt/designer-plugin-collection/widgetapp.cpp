/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Application that uses widget from the collection                    ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "widgetapp.h"

WidgetApp::WidgetApp(QWidget *parent) : QMainWindow(parent) {
  m_widgetApp = new Ui::MainWindow;
  m_widgetApp->setupUi(this);
}
