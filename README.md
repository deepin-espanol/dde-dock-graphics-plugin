# dde-dock-switch_graphics_card (forked from mywhat/DDESwitchCard)

## 功能介绍

由论坛大佬 chanforever 的插件修改得来。

【原贴地址： https://bbs.deepin.org/forum.php?mod=viewthread&tid=197280】

【github原项目地址： https://github.com/mywhat/DDESwitchCard/】

修改了脚本内容以及安装位置等，方便打包成 deb 直接安装，避免文件权限混乱。自动检测配置文件是否缺失，并进行初始化操作。添加了 nvidia-prime 的配置（需要高版本 xserver-xorg 支持）。

P.S.其实，按照大佬的打包，nvidia-prime 的启用就是在 xorg.conf 的 Section "ServerLayout" 里加一行 Option "AllowNVIDIAGPUScreens" 的事，外加一个 prime-run 脚本调用环境变量......前提就是 xserver-xorg 版本和显卡的支持问题了......

## 编译环境依赖

qt-default

libqt5core5a

libqt5gui

libqt5widgets

libdtkcore-dev

libdtkgui-dev

libdtkwidget-dev

dde-dock-dev


nvidia-smi (运行时依赖)

## 源码编译(需要安装qt编译链和DDE的相关依赖)

cd src && mkdir build

cd build && cmake .. && make -j4

## 使用

P.S.建议使用 deb 安装包安装

1.  将 icon 文件夹，Initialize.sh，Intel,sh，NVIDIA.sh 放置在 /opt/durapps/dde-dock-switch_graphics_card 文件夹下；

2.  将编译生成的 libswitch_graphics_card.so 放在 ~/.local/lib/dde-dock/plugins/ 或者 /usr/lib/dde-dock/plugins/ 文件夹下;

3.  等待 dde-dock 自动重新加载，即可在最右侧看到该插件已启用。（好像暂时不能在dock栏设置不启用该插件......）

4.  （可选）将 dde-dock-switch_intel.desktop 和 dde-dock-switch_nvidia.desktop 放入 /usr/share/deepin/dde-file-manager/oem-menuextensions/ ，可以在右键菜单中直接切换显卡。

## 感谢

论坛大佬 chanforever 的插件        https://bbs.deepin.org/forum.php?mod=viewthread&tid=197280

论坛大佬 jfy_99 的显卡切换脚本     https://bbs.deepin.org/forum.php?mod=viewthread&tid=192750

论坛大佬 risez 的 nvidia-prime 方案        https://bbs.deepin.org/forum.php?mod=viewthread&tid=191741