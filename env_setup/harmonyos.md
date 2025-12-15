# 鸿蒙 PC 上的 C/C++ 环境

虽然当前的鸿蒙 PC 对开发者还很不友好，我们很不建议使用鸿蒙 PC 写代码，但是自 HarmonyOS 6.0.0.115 起，同时也伴随着 CodeArts IDE 加入了部分 C/C++ 开发工具链，我们确实可以在鸿蒙 PC 上不借助虚拟机编译运行一些简单的 C/C++ 程序了。

可以参考[这个视频](https://www.bilibili.com/video/BV12E28ByEuQ?spm_id_from=333.788.videopod.sections&vd_source=7940495b5667750a71bfa10a4c6eb2d9)，但该 up 主账号似乎有一些问题，所以还是在这里写一下大致的情况。未来如果鸿蒙 PC 支持了更多工具，我也会在这里同步更新。也可以参考[这个文档](https://ai.feishu.cn/wiki/C0kHwGtgYi1ZT6kCzApcV1awnGg)。

## 编译器和 IDE

在 AppGallery 搜索安装“CodeArts IDE”。目前该 App 在“应用尝鲜”里。 CodeArts IDE 非常大，它提供了一系列开发者工具，如 Python 、 SSH 、 Git 。最新的版本也提供了 LLVM 的大部分工具（其中包括 C/C++ 的编译器 `clang` 和 `clang++`）以及 `cmake` 。目前的 `clang` 版本是 15.0.4 ，且带有“BiSheng”字样，大概率就是来自毕昇编译器（华为基于 LLVM 做的编译器）； `cmake` 的版本是 3.26 ， `python` 的版本是 3.12 ，基本都是够用的。

CodeArts IDE 我不太清楚是不是在 JetBrains 的某个 IDE 基础上改的，我对 JetBrains 的东西非常不了解。在 CodeArts IDE 里打开终端，它所提供的各种开发工具所在的路径都会被自动加进 `PATH` 里，你可以直接调用。在外部的终端是没有办法直接调用这些开发工具的。

由于我自己没有鸿蒙 PC ，没有尝试过安装其它版本的编译器或其它工具，或者从源码编译一些工具。目前鸿蒙依然没有包管理器，所以除了使用 CodeArts IDE 提供的工具之外，想自己安装些别的工具可能有一定难度。

## 编译、运行

打开 CodeArts IDE ，创建一个项目，选择“C/C++”，语言和标准可以自己选。以 C++ 为例，它会自动创建好一个 `main.cpp` 、一个 `CMakeLists.txt` 和一个 `cmake-build-debug` 文件夹。代码就在 `main.cpp` 里写，右上角有一些触发编译、运行、调试的图标。默认情况下它会采用 Ninja 作为 build system ，我试了一下改成 Makefiles 也是可以的。这里涉及到一些 CMake 的知识，我暂时没想好怎么讲给初学者，你可以自己上网搜（问 AI）。

当你第一次尝试运行的时候，它会跳转到系统设置-隐私和安全-高级-运行外部来源的扩展程序，把这个选项打开，我们就可以运行自己编译出来的可执行文件了。

调试我暂时没玩明白，只是打了断点并成功触发了，但我似乎没找到调试时交互用的终端在哪，以及 `gdb` 或者 `lldb` 在哪。有待进一步探索。

## 其它

据[这个文档](https://ai.feishu.cn/wiki/C0kHwGtgYi1ZT6kCzApcV1awnGg)所说， clang 还缺失一些库需要手动下载安装，具体的方法在文档里有写。

另外，我之前一直比较担心文件访问权限问题，因为鸿蒙的 App 正常来说是需要调用 FilePicker 来让用户选择文件进行访问的。但我试了一下文件 IO 以及重定向（终端是 `zsh` 支持 `<` 和 `>` 的重定向语法）发现都没什么问题。
