### 调用流程及各个类型的介入时机

整体分为 call 和 callback

函数的每个参数及返回值均有一个tag, 可以针对每个tag定制化操作.

#### call 调用

```
declare outer_state
foreach arg
  prepare_state()
foreach arg
  if is_input
    json_to_arg()
call function
foreach arg
  if is_output
    arg_to_json()
```

##### `lhg::call::prepare_state`

准备状态, 通常用于初始化输出参数

##### `lhg::call::json_to_arg`

将`json`值转换为实际调用时的参数

##### `lhg::call::arg_to_json`

将(输出/返回)参数转换为`json`值

##### `lhg::call::json_to_arg_schema` `lhg::call::arg_to_json_schema`

对应位置的schema

##### `lhg::call::type_is_handle`

类型是否是句柄, 用于给`is_handle`提供默认值

##### `lhg::call::is_handle`

参数是否是句柄, 句柄的行为是什么

##### `lhg::call::is_input`

参数是否是输入, 如果是输入才会触发`json_to_arg`调用

##### `lhg::call::is_output`

参数是否是输出, 如果是输出才会触发`arg_to_json`调用

##### `lhg::call::type_is_outer_state`

类型是否需要外部状态, 外部状态是什么类型, 用于给`is_outer_state`提供默认值

##### `lhg::call::is_outer_state`

参数是否需要外部状态, 外部状态是什么类型

#### callback 回调

```
declare outer_state
get_context()
foreach arg
  if is_input
    arg_to_json()
call function
foreach arg
  if is_output
    json_to_arg()
```

> 虽然大部分和call是一致的, 但是input/output和arg_to_json/json_to_arg的对应关系交换了

##### `lhg::callback::get_context`

从参数中获取context

##### `lhg::callback::arg_to_json`

将(输出/返回)参数转换为`json`值

##### `lhg::callback::json_to_arg`

将`json`值转换为实际调用时的参数

##### `lhg::callback::json_to_arg_schema` `lhg::callback::arg_to_json_schema`

对应位置的schema

##### `lhg::callback::type_is_handle`

类型是否是句柄, 用于给`is_handle`提供默认值

##### `lhg::callback::is_handle`

参数是否是句柄, 句柄的行为是什么

##### `lhg::callback::is_input`

参数是否是输出, 如果是输出才会触发`arg_to_json`调用

##### `lhg::callback::is_output`

参数是否是输入, 如果是输入才会触发`json_to_arg`调用

##### `lhg::callback::type_is_outer_state`

类型是否需要外部状态, 外部状态是什么类型, 用于给`is_outer_state`提供默认值

##### `lhg::callback::is_outer_state`

参数是否需要外部状态, 外部状态是什么类型

