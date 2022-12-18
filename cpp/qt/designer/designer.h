/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: MainWindow for Qt Designer desktop application                      ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef KLIPS_SLOTSAPP_H
#define KLIPS_SLOTSAPP_H

#include <QDockWidget>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "ui_designer.h"

class Designer : public QMainWindow {
  Q_OBJECT

public:
  Designer(QWidget *parent = nullptr);
  ~Designer() = default;

public:
signals:
  void sendTest();

public slots:
  void test(){};

private:
  Ui::Designer *designer_;
};

#endif // KLIPS_SLOTSAPP_H
