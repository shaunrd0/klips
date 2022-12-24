/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Application that uses a custom Qt Designer widget plugin            ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef KLIPS_WIDGETAPP_H
#define KLIPS_WIDGETAPP_H

#include <QDockWidget>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "ui_widget-app.h"

class WidgetApp : public QMainWindow {
  Q_OBJECT

public:
  WidgetApp(QWidget *parent = nullptr);
  ~WidgetApp() = default;

  Ui::MainWindow *m_ui;

public:
signals:
  void sendTest();

public slots:
  void test(){};
};

#endif // KLIPS_WIDGETAPP_H
