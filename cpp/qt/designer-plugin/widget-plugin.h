/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Example Qt Designer widget plugin                                   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
*/

#ifndef KLIPS_WIDGETPLUGIN_H
#define KLIPS_WIDGETPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class WidgetPlugin : public QObject, public QDesignerCustomWidgetInterface {
Q_OBJECT
Q_PLUGIN_METADATA(IID "com.Klips.WidgetPlugin")
Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
  explicit WidgetPlugin(QObject *parent = nullptr) : QObject(parent) {}

  ~WidgetPlugin() = default;
public:
  QString group() const override;
  QString name() const override;
  QString includeFile() const override;
  QWidget *createWidget(QWidget *parent) override;

  QString toolTip() const override;
  QString whatsThis() const override;
  QIcon icon() const override;
  bool isContainer() const override;
  bool isInitialized() const override;
  void initialize(QDesignerFormEditorInterface *core) override;

private:
  bool m_initialized = false;

  QString m_group;
  QString m_name;
  QString m_includeFile;
};

#endif // KLIPS_WIDGETPLUGIN_H
