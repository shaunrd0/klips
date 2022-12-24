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

#include "widget-plugin-library_export.h"
#include <QPlainTextEdit>

class WIDGET_PLUGIN_LIBRARY_EXPORT TextView : public QPlainTextEdit {
  Q_OBJECT

public:
  explicit TextView(QWidget *parent = nullptr) : QPlainTextEdit(parent) {
    appendPlainText("This is an example of a custom QTextView widget.");
  }

  ~TextView() = default;

  QString includeFile() const { return QStringLiteral("text-view.h"); };
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
