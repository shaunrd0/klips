
#ifndef DESIGNERPLUGINCOLLECTION_WIDGETPLUGINCOLLECTION_H
#define DESIGNERPLUGINCOLLECTION_WIDGETPLUGINCOLLECTION_H

#include <QDesignerCustomWidgetCollectionInterface>

class WidgetPluginCollection : public QObject,
                               public QDesignerCustomWidgetCollectionInterface {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "com.Klips.WidgetPluginCollection")
  Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
  explicit WidgetPluginCollection(QObject *parent = nullptr);
  [[nodiscard]] QList<QDesignerCustomWidgetInterface *> customWidgets() const;

private:
  QList<QDesignerCustomWidgetInterface *> m_collection;
  QString m_collectionName;
};

#endif // DESIGNERPLUGINCOLLECTION_WIDGETPLUGINCOLLECTION_H
