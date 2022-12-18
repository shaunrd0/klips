/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Dockable text editor widget made in Qt Designer with C++            ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "texteditor.h"
#include "ui_texteditor.h"

TextEditor::TextEditor(QWidget *parent) :
  QDockWidget(parent),
  ui(new Ui::TextEditor)
{
  ui->setupUi(this);
}

TextEditor::~TextEditor()
{
  delete ui;
}
