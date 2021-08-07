# ucfg

## 依赖

编译器: gcc

## 怎么使用

代码库使用cmake构建, 包含两个代码库`ucfg`和`ucfg_param`:

* `ucfg`包含一个ini文件格式解析和管理器, 可用于读取和修改ini格式的参数文件.

* `ucfg_param`依赖`ucfg`, 包含一个参数定义库, 提供了方便的宏API定义操作参数文件的函数, 设置默认值等功能, 底层依赖`ucfg`实现.

下载源码后使用cmake脚本集成到项目中:

```cmake
add_subdirectory(ucfg)
target_link_libraries(xxx PUBLIC ucfg) # or ucfg_param
```

目前文档仅描述`ucfg_param`库的使用, `ucfg`请参考源码使用.

### 定义和声明参数

创建一个参数管理器需要包含头文件然后使用对应函数宏定义:

```C
// param_define.c:
#include <ucfg/param/param_define.h>

// Define a parameter manager
UCFG_DEFINE_PARAM_MANAGER(param, "./param.cfg");

// Define parameter default value, the parameter can be bool/int/float/string types
UCFG_DEFINE_PARAM_BOOL(param, control, enable, true);
UCFG_DEFINE_PARAM_INT(param, control, max_speed, 10);
UCFG_DEFINE_PARAM_FLOAT(param, control, acceleration, 1);
UCFG_DEFINE_PARAM_STRING(param, server, domain, "www.server.com");
```

`UCFG_DEFINE_PARAM_MANAGER`用来设置参数管理器名字和参数文件存储路径.

参数声明, 声明每个参数的读取和写入函数接口:

```C
// param_define.h
#include <ucfg/param/param_declare.h>

// Declare parameter manager
UCFG_DECLARE_PARAM_MANAGER(param);

// Declare parameter
UCFG_DECLARE_PARAM_BOOL(param, control, enable);
UCFG_DECLARE_PARAM_INT(param, control, max_speed);
UCFG_DECLARE_PARAM_FLOAT(param, control, acceleration);
UCFG_DECLARE_PARAM_STRING(param, server, domain);
```

参数管理器的声明定义了一些对于当前参数管理器的参数管理函数, 比如`UCFG_DECLARE_PARAM_MANAGER(param);`会生成:

* 擦除所有参数`void param_erase_all()`
* 待补充...

参数声明为每个参数定义读写函数, 比如`UCFG_DECLARE_PARAM_INT(param, control, max_speed);`生成的读写函数为:

* 参数获取:`int param_get_control_max_speed()`, 返回参数值, 没有设置则返回默认值.
* 参数设置: `void param_save_control_max_speed(int value)`, 设置并保存参数到文件中.

字符串类型生成的读写函数略有区别, 比如`UCFG_DECLARE_PARAM_STRING(param, server, domain);`生成的读写函数为:

* 参数获取:`void param_get_server_domain(char *out_str, size_t size)`, 自动在out_str末尾补充结束符`'\0'`;
* 参数设置:`void param_save_section_domain(const char *value)`, 设置并保存参数到文件中.

### 读取和保存参数

在源文件中包含参数的声明头文件, 调用对应的参数读写接口:

```C
#include <stdio.h>

#include "param_define.h"

int main() {
    char server[100];
    param_get_server_domain(server, sizeof(server));
    printf("server domain -> %s", server);
    
    param_save_server_domain("www.unknown.com");
    printf("expected: www.unknown.com, server domain -> %s", server);
    
    param_save_control_max_speed(30);
    printf("expected: 30, control_max_speed -> %d", param_get_control_max_speed());
    
    param_save_control_max_speed(20);
    printf("expected: 20, control_max_speed -> %d", param_get_control_max_speed());
}

```

具体可参考[examples](examples)文件夹中的例子.

### 外部实时修改文件参数（谨慎使用）

在文件中修改完参数保存后，参数管理器会根据文件的修改时间刷新内部参数，从而达到实时修改参数的目的。

## 相关技术

1. 借助gcc的`__attribute((__section__(section_name))) __attribute((__used__))`属性, 把默认参数值放到同一个section名中.
2. 借助gcc编译源文件后会给section添加`__start_section`和`__stop_section`两个符号的特性, 获取默认参数数组的起始位置和结束位置.
