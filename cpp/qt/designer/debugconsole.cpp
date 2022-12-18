/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Debug console widget made in Qt Designer with C++                   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "debugconsole.h"
#include "ui_debugconsole.h"

DebugConsole::DebugConsole(QWidget *parent)
    : QDockWidget(parent), ui(new Ui::DebugConsole) {
  ui->setupUi(this);
}

DebugConsole::~DebugConsole() { delete ui; }
