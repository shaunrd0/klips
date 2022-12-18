/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Main driver fprogram for practice using signals and slots in Qt     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "slots-app.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  SlotsApp slotsApp;
  slotsApp.show();
  return app.exec();
}
