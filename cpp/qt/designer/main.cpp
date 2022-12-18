/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Main driver program for Qt Designer desktop application..           ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "designer.h"
#include <QApplication>

int main(int argc, char * argv[]) {
  QApplication app(argc, argv);
  Designer qtk;
  qtk.show();
  // Show widget.
  return app.exec();
}
