# Read Me

## 目标

完成属性计算与代码生成

- 属性计算

  - 实现`CSymbolTable.h`中的函数`genSymbolTable`

    - 要求遍历AST树，填充节点属性（如每个节点所从属的命名空间）
    - 填充每一个`CNameSpace`的`name_table`
    - 生成常量，计算常量表达式（并应当将值放入表达式节点中），并都统计到符号表中（将会提供字符串到常量的函数`fromString`）

  - 类型和语法检查

    检查类型的应用是否一致（如传入函数，赋值，返回值等），以及某些CFG语法是否正确（比如数组大小不是常量等），若出错则该节点标位错误。（值得注意的是，有些节点在parser阶段就产生了错误）

    并继续检查。

    检查完毕后，若产生错误，则将错误信息输出到`Context`的错误流中。

- 代码生成

  - 遍历AST树，调用LLVM库，生成目标代码
  - 若产生错误，若产生错误，则将错误信息输出到`Context`的错误流中。

在语法方面，由于CFG规则众多，不必一次性实现全部规则，有关`_NoReturn`,`Atomic`,`__func__`,`Generic`,`Alignment`,`Imagenary`,`Complex`,`static_assert`,`Thread_local`等不那么重要的功能可以先不实现。

另外，由于[lexer hack](https://en.wikipedia.org/wiki/Lexer_hack), scanner还没有办法识别自定类型名和变量名，所以`typedef`和`enum`将不实现。

总之，在语法的实现上，大家量力而行即可。

## 基本策略

这只是我的想法，仅供大家参考。

- 属性计算

  - 根据需求，扩展`Csymbols.hpp`中的节点属性
  - 根据不同的CFG，实现`C_rule_attr.cpp`中的各个`ProductionInfo`接口（一般是填入函数，遍历AST时，访问节点的production.getAttrs()获取`ProductionInfo`对象，自动执行其中的函数）.
- 代码生成
  - 根据不同的CFG，实现`C_rule_code.cpp`中的各个`ProductionInfo`接口（一般是填入函数，遍历AST时，访问节点的production.getGenCodeInfo)获取`ProductionInfo`对象，自动执行其中的函数）
  - 需要命名空间信息时，除了全局命名空间，各个节点还含有其所从属的命令空间指针（`owner`）。
  - 遇到一些表达式的值为常量的，可以不必继续解析，因为常量已经在属性计算阶段计算好了。


