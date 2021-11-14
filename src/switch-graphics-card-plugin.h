#ifndef SWITCHCARD_H
#define SWITCHCARD_H

#include <QGSettings>

#include "pluginsiteminterface.h"
#include "tipswidget.h"

#include "ddeUtil.h"
#include "switchgraphicscardwidget.h"
#include "switchgraphicscardappletwidget.h"

namespace Dock {
class TipsWidget;
}

class SwitchGraphicsCardPlugin : public QObject
    , PluginsItemInterface
{
    Q_OBJECT

    // 声明实现了的接口
    Q_INTERFACES(PluginsItemInterface)
    // 插件元数据
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "switch-graphics-card.json")

public:
    explicit SwitchGraphicsCardPlugin(QObject *parent = nullptr);
    ~SwitchGraphicsCardPlugin() override;

    // 返回插件的名称，必须是唯一值，不可以和其它插件冲突
    const QString pluginName() const override;
    const QString pluginDisplayName() const override;

    // 插件初始化函数
    void init(PluginProxyInterface *proxyInter) override;

    // 控制插件启用或禁用
    bool pluginIsAllowDisable() override;
    bool pluginIsDisable() override;
    void pluginStateSwitched() override;

    // 返回插件的 widget
    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    // 右键菜单
    const QString itemContextMenu(const QString &itemKey) override;
    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;

    // dock 栏显示模式改变
    void displayModeChanged(const Dock::DisplayMode displayMode) override;

    // dock 栏插件排序
    int itemSortKey(const QString &itemKey) override;
    void setSortKey(const QString &itemKey, const int order) override;

    // 插件状态改变（启用或禁用）
    void pluginSettingsChanged() override;

private:
    void loadPlugin();
    void refreshPluginItemsVisible();
    void updateTranslator();

private slots:
    void onGsettingsChanged(const QString &key);

private:
    SwitchGraphicsCardWidget *m_pluginWidget;
    Dock::TipsWidget *m_tipsWidget;
    SwitchGraphicsCardAppletWidget *m_appletWidget;

    QGSettings *m_gsettings;
    QProcess *process;
    bool m_pluginLoaded;
    QTranslator *ts;
};

#endif // HOMEMONITORPLUGIN_H
