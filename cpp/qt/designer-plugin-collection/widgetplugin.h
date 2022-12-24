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

#include <QDesignerCustomWidgetInterface>

class WidgetPlugin : public QObject, public QDesignerCustomWidgetInterface {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "com.Klips.WidgetPlugin")
  Q_INTERFACES(QDesignerCustomWidgetInterface)

  using Factory = std::function<QWidget *(QWidget *)>;

public:
  WidgetPlugin(QString group, QString name, Factory factory);
  WidgetPlugin(QString group, QString name, QString include, Factory factory);

  explicit WidgetPlugin(QObject *parent = nullptr) : QObject(parent) {}

  ~WidgetPlugin() = default;

public:
  [[nodiscard]] QString group() const override;
  [[nodiscard]] QString name() const override;
  [[nodiscard]] QString includeFile() const override;
  QWidget *createWidget(QWidget *parent) override;

  [[nodiscard]] QString toolTip() const override;
  [[nodiscard]] QString whatsThis() const override;
  [[nodiscard]] QIcon icon() const override;
  [[nodiscard]] bool isContainer() const override;
  [[nodiscard]] bool isInitialized() const override;
  void initialize(QDesignerFormEditorInterface *core) override;

private:
  bool m_initialized = false;

  QString m_group;
  QString m_name;
  QString m_includeFile;
  Factory m_factory;
};

#endif // KLIPS_WIDGETPLUGIN_H
