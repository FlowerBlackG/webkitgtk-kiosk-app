# 如何调试

## 选择渲染后端

启动时，通过环境变量 GDK_BACKEND 设置。

例如：

```
GDK_BACKEND=x11 ./kbrowser
```

## 纯软件运行

```
GTK_RENDERER=cairo LIBGL_ALWAYS_SOFTWARE=1 ./kbrowser
```
