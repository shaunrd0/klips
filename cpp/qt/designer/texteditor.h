/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Dockable text editor widget made in Qt Designer with C++            ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QDockWidget>

namespace Ui {
  class TextEditor;
}

class TextEditor : public QDockWidget
{
  Q_OBJECT

public:
  explicit TextEditor(QWidget *parent = nullptr);
  ~TextEditor();

private:
  Ui::TextEditor *ui;
};

#endif // TEXTEDITOR_H
