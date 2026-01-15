# 如何调试

## 太长，不想看

### 安装依赖

```bash
sudo apt install libwebkit2gtk-4.0-dev libgtkmm-3.0-dev pkgconf g++

```

### 编译

```bash
make -j2
```

### 运行

```bash
GTK_RENDERER=cairo LIBGL_ALWAYS_SOFTWARE=1 ./kbrowser
```

---

## 选择渲染后端

启动时，通过环境变量 GDK_BACKEND 设置。

例如：

```bash
GDK_BACKEND=x11 ./kbrowser
```

## 纯软件运行

```bash
GTK_RENDERER=cairo LIBGL_ALWAYS_SOFTWARE=1 ./kbrowser
```
