# Python命名规则

| 类型              | 公有       | 内部                       |
| ----------------- | ---------- | -------------------------- |
| 包                | 小写下划线 |                            |
| 模块              | 小写下划线 | 下划线+小写下划线          |
| 类                | 大驼峰     | 下划线+大驼峰              |
| 异常              | 大驼峰     |                            |
| 函数              | 小写下划线 | 下划线+小写下划线          |
| 全局常量/类常量   | 大写下划线 | 下划线+大写下划线          |
| 全局变量/类变量   | 小写下划线 | 下划线+小写下划线          |
| 实例变量          | 小写下划线 | 下划线+小写下划线 (受保护) |
| 方法名            | 小写下划线 | 下划线+小写下划线 (受保护) |
| 函数参数/方法参数 | 小写下划线 |                            |
| 局部变量          | 小写下划线 |                            |

| 类型              | 公有                 | 内部                  |
| ----------------- | -------------------- | --------------------- |
| 包                | `lower_with_under`   |                       |
| 模块              | `lower_with_under`   | `_lower_with_under`   |
| 类                | `CapWords`           | `_CapWords`           |
| 异常              | `CapWords`           |                       |
| 函数              | `lower_with_under()` | `_lower_with_under()` |
| 全局常量/类常量   | `CAPS_WITH_UNDER`    | `_CAPS_WITH_UNDER`    |
| 全局变量/类变量   | `lower_with_under`   | `_lower_with_under`   |
| 实例变量          | `lower_with_under`   | `_lower_with_under`   |
| 方法名            | `lower_with_under()` | `_lower_with_under()` |
| 函数参数/方法参数 | `lower_with_under`   |                       |
| 局部变量          | `lower_with_under`   |                       |

