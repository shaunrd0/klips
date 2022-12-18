/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: MainWindow application for practice using signals and slots in Qt   ##
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

class SlotsApp : public QMainWindow {
  Q_OBJECT

public:
  SlotsApp(QWidget *parent = nullptr);
  ~SlotsApp() = default;

public:
signals:
  void sendTest();

public slots:
  void test(){};
};

#endif // KLIPS_SLOTSAPP_H
