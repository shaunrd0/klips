/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Example of a generic Qt Designer widget plugin                      ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "widgetplugin.h"
#include "textview.h"

#include <QtPlugin>
#include <utility>

WidgetPlugin::WidgetPlugin(QString group, QString name,
                           WidgetPlugin::Factory factory)
    : m_group(std::move(group)), m_name(std::move(name)),
      m_includeFile(name + ".h"), m_factory(std::move(factory)) {}

WidgetPlugin::WidgetPlugin(QString group, QString name, QString include,
                           WidgetPlugin::Factory factory)
    : m_group(std::move(group)), m_name(std::move(name)),
      m_includeFile(std::move(include)), m_factory(std::move(factory)) {}

QString WidgetPlugin::toolTip() const { return {}; }

QString WidgetPlugin::whatsThis() const { return {}; }

QIcon WidgetPlugin::icon() const { return {}; }

bool WidgetPlugin::isContainer() const { return false; }

QString WidgetPlugin::group() const { return m_group; }

QString WidgetPlugin::name() const { return m_name; }

// TODO: The generated UI headers do not use this member appropriately.
QString WidgetPlugin::includeFile() const { return m_includeFile; }

QWidget *WidgetPlugin::createWidget(QWidget *parent) {
  return m_factory(parent);
}

bool WidgetPlugin::isInitialized() const { return m_initialized; }

void WidgetPlugin::initialize(QDesignerFormEditorInterface *) {
  if (m_initialized)
    return;

  m_initialized = true;
}
