/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Text viewer for signals and slots examples                          ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef KLIPS_TEXTVIEW_H
#define KLIPS_TEXTVIEW_H

#include <QPlainTextEdit>

class TextView : public QPlainTextEdit {
  Q_OBJECT

public:
  TextView(QWidget *parent = nullptr) {}

  ~TextView() = default;

public:
signals:
  void sendTest();

private:
signals:
  void sentTestPrivate();

public slots:
  void test() { appendPlainText("Test signal received by TextView."); }

  void testArgs(const QString &message) { appendPlainText(message); }

private slots:
  void testPrivate() {}
};

#endif // KLIPS_TEXTVIEW_H
