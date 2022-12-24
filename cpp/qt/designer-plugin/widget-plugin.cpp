/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Example Qt Designer widget plugin                                   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#include "widget-plugin.h"
#include "text-view.h"

#include <QtPlugin>

QString WidgetPlugin::toolTip() const
{
    return {};
}

QString WidgetPlugin::whatsThis() const
{
    return {};
}

QIcon WidgetPlugin::icon() const
{
    return {};
}

bool WidgetPlugin::isContainer() const
{
    return false;
}

QString WidgetPlugin::group() const
{
    return m_group;
}

QString WidgetPlugin::name() const
{
  return QStringLiteral("KlipsWidgetPlugin");
}

QString WidgetPlugin::includeFile() const
{
  return QStringLiteral("widget-plugin.h");
}

QWidget *WidgetPlugin::createWidget(QWidget *parent)
{
  return new TextView(parent);
}

bool WidgetPlugin::isInitialized() const
{
    return m_initialized;
}

void WidgetPlugin::initialize(QDesignerFormEditorInterface *)
{

  if (m_initialized)
    return;

  m_initialized = true;
}
