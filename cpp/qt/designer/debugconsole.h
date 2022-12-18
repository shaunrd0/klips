/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Debug console widget made in Qt Designer with C++                   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef DEBUGCONSOLE_H
#define DEBUGCONSOLE_H

#include "ui_debugconsole.h"
#include <QDockWidget>

class DebugConsole : public QDockWidget {
  Q_OBJECT

public:
  explicit DebugConsole(QWidget *parent = nullptr);
  ~DebugConsole();

  inline QPlainTextEdit *getConsole() { return ui->plainTextEdit; }

private:
  Ui::DebugConsole *ui;
};

#endif // DEBUGCONSOLE_H
