**FontRouter LT for Symbian 9 Beta (Build 20071109) Unsigned**

仅在20071109版基础上修改了UID，无其它功能变化。
注意：这个版本使用了Symbian非正规发布的UID范围，仅供测试用途。


**FontRouter LT for Symbian 6 / 7 / 8 Beta (Build 20071109)**
**FontRouter LT for Symbian 9 Beta (Build 20071109)**

· 新增全局属性“ZoomRatio”，用于所有字体的按比例缩放，取值为百分比（不含“％”），默认值为100。
· 新增字体映射附加属性“Z”，用于定义针对单项字体映射的缩放比例，缺省为“Z100”。
· 新增可选的全局属性“ZoomMinSize”和“ZoomMaxSize”，限制全局字体比例缩放的作用范围。
· 新增全局属性“Chroma”，用于调节开启反锯齿显示效果后的字体笔画深浅度，取值为百分比（不含“％”），默认值为100。（对未开启反锯齿效果的字体无效）
· 新增字体映射附加属性“C”，用于定义针对单项字体映射的笔画深浅度调节，缺省为“C100”。
· “ExtraFontFile”属性增加了通配符支持（例如“C:\Data\Fonts\`*`.tt?”），并在配置文件中设定了默认值“\Data\Fonts\`*`.`*`”（可修改），Symbian9手机用户的字体文件不再需要放置在隐晦的\Resource\Fonts下了。
· 新增点阵字体的加粗效果支持，现在可以正常使用在所有点阵字体上。在字体映射中使用附加属性“b”可以根据请求应用程序的粗体请求自动将点阵字体加粗，使用“B”可以强制在任何时候均加粗。
· 配置文件“FontRouter.ini”的位置现已移至\Data\Fonts\下（旧位置下的配置文件不再有效），以避免UIQ3手机上可能遭遇的根文件夹下文件丢失的问题。
· 全局属性“ForceAntiAliased”现已更改为更贴切的名称“BitmapType”，为保持兼容，旧属性名仍然有效。
· FontRouter的版本号现在将在启动时加入日志文件“FontRouter.log”中。（仅当开启了日志功能时）
· 修正了当“BitmapType”（原“ForceAntiAliased”）属性设置为3时，点阵字体显示错乱且无法阅读的问题。
· 修正了无法正常启动Nokia手机内置计算机工具的问题。
· 修正了某些字体映射规则意外的不能生效的问题。
· 修正了当安装有多个用户字体时，无法在应用程序中选择除默认字体外其它字体的问题。
· 修正了在使用NAND闪存的机型上错误判断字体是否内置于ROM中的问题。
· 完善了字体驱动内部接口“按最大尺寸获取字体”，希望能修正在UIQ3上出现的“闪屏”问题。（未经验证）


**FontRouter LT for Symbian 6 / 7 / 8 Beta (Build 20070619 端午版)**
**FontRouter LT for Symbian 9 Beta (Build 20070619 端午版)**

· 修正FixFontMetrics=1可能导致异常的过度剃头（尾）问题。
· 修正FixCharMetrics=1导致系统启动失败的问题，现在该特性可以正常使用了。
· 彻底修正开启反锯齿后，LatinBold12字体无法被正确映射的问题。（Thanks to knplogic from Italy）
· 新特性：支持Symbian 9.2所加入的Sub-pixel点阵格式，在手机屏幕上可以提供比“反锯齿”更佳的显示效果。（注：从模拟器的测试结果来看，目前S60 v3FP1和UIQ3.1均尚不支持Sub-pixel效果……）
现在全局选项中的强制反锯齿设置还会作用于那些在字体映射中配置为被FontRouter忽略的字体上。


**FontRouter LT for Symbian 6 / 7 / 8 Beta (Build 20070613)**
**FontRouter LT for Symbian 9 Beta (Build 20070613)**

· 修正LatinBold12等字体无法被映射的问题。
· 修正默认配置文件中的几处字体映射错误，解决计算器无法进入的问题。
· 修正查询字符存在性接口失效的错误，解决中文之星掌上狂拼等中文输入法无法正常显示文字的问题。


**FontRouter LT for Symbian 6 / 7 / 8 Beta (Build 20070609)**
**FontRouter LT for Symbian 9 Beta (Build 20070609)**

· 修正FixFontMetrics功能部分失效的问题，并调整了计算方法
· 重新设计FixCharMetrics的实现方式，避免出现字体高低不一的问题
· 日志中新增显示FixFontMetrics自动计算出的“字模高度调整值（Y修正值）”（以“Y+”表示），以便大家选择合适的Y修正值。


**FontRouter LT for Symbian 6 / 7 / 8 Beta (Build 20070603)**
**FontRouter LT for Symbian 9 Beta (Build 20070603)**

· 提高与Symbian 6的兼容性：ForceAntiAliased设置在Symbian 6中将被忽略。（因为Symbian 6不支持反锯齿效果）
· 提高与UIQ2的兼容性：默认配置文件支持屏幕键盘中特殊字符的正确显示。
· 修正与S60v1/v2的兼容性：通过默认的配置文件，请求字体的大小现在将自动被正确识别。
· 提高与S60v3 FP1（N95等）的兼容性：增加字体上下位置的智能纠正，所有字符的高度将规整如一。请修改配置文件，设置FixCharMetrics=1开启此项功能。


**FontRouter LT for Symbian 6 / 7 / 8 Beta (Build 20070531)**
**FontRouter LT for Symbian 9 Beta (Build 20070531)**

增加对GDR字体的支持。（可通过配置选项“NativeFont=0”关闭）
· 修正“即装即用”功能在部分机型上无法实现的问题。
· 丰富日志打印的信息（增加字体名信息，“即装即用”功能使用的默认字体 等）。
· 调整默认的日志打印级别为4（Info）。


**FontRouter LT for Symbian 6 / 7 / 8 Beta (Build 20070519)**

用于Symbian 6 / 7 / 8的版本。因暂不支持GDR字体，所以目前仅支持S60 第二版非标准分辨率（大于176x208）的机型。

注：与Symbian 9版本不同的是，配置文件FontRouter.ini仍位于\System\Fonts文件夹下。


**FontRouter LT for Symbian 9 Beta (Build 20070516)**

· FontRouter LT的核心机制采用新的方式重新实现，现已正式支持Symbian 9.2 （S60 v3 FP1、UIQ3.1）。使用N95等机型的朋友也可以使用 FontRouter LT 了！

· 新的“即装即用”设计。安装好FontRouter LT后无需对配置文件作任何修改，只要将希望使用的字体复制到\resource\fonts中，重启手机后即可生效！如果安装有多个字体文件，那么默认只使用第一个字体。

· 字体映射语法中新增以下参数：
```
   B      粗体
   b      非粗体
   I      斜体
   i      非斜体
   Y<n>   Y坐标（高度）修正
   W<n>   字符间距（宽度）修正
   L<n>   行间距（行高）修正（只支持Symbian 9）
```


· 【实验性】优化字体高度调整算法，除此前的字体参数调整外，新增的字符参数自动校正功能，进一步消除剃头剃尾的困扰。通过[Global](Global.md)段的“FixCharMetrics”参数设置
FixCharMetrics=0 表示不作任何校正(默认)
FixCharMetrics=1 表示开启自动校正

· 字体映射中的字体名不再区分大小写。

· “DisableFontFile”现在同时支持 含完整路径的文件名 和 不含路径的文件名。

· 从现在开始，字体映射配置中可以用“`*`”作为映射后的字体名，代表“第一个有效的非符号非ROM字体”。通常，如果你只安装了一个自选字体，那么默认ini配置文件无需任何修改即可使用。

· 字体映射配置中“待映射的字体名”也可以使用“`*`”，用以匹配所有未出现在其它字体映射关系中的字体。例如：“`*`=Microsoft YaHei”，或者“`*`@10=FZLiBian-S02”，甚至是“`*`=`*`”。

· 如果你不清楚字体文件中的具体字体名，那么字体映射配置中映射后的字体名可以直接写字体文件名（扩展名可省略），注意不要带路径。例如“Sans MT 936\_S60=msyh.ttf” 或 “Sans MT 936\_S60=msyh”。

· 修正Bug: 某些情况下，FontRouter LT加载的时机较晚，可能造成部分系统字体脱离FontRouter LT的控制。

· 废除“AlterFontFile”参数，请用“ExtraFontFile”代替。


**FontRouter LT for Symbian 9 Beta (Build 20070422)**

完全重新设计字体高度调整算法，原有的两种模式废除，新的“模拟Nokia中文字体”模式可解决“掌讯通”等中文软件中的剃尾问题。通过[Global](Global.md)段的“FixFontMetrics”参数设置
FixFontMetrics=0 表示不作任何调整(默认)
FixFontMetrics=1 “模拟Nokia中文字体”模式


**FontRouter LT for Symbian 9 Beta (Build 20070420)**

调整字体高度算法，现在提供两种模式，通过[Global](Global.md)段的“FixFontMetrics”参数设置
FixFontMetrics=0 表示不作任何调整
FixFontMetrics=1 表示针对中文字体作特殊调整
FixFontMetrics=2 表示基于字模探测进行调整（仅对中文字体有效）

建议：优先使用0，如果没有任何问题；其次选择1，可以解决部分剃头剃尾的问题；最次选择2，能针对一些规格数据有缺陷的字体作出修正。


**FontRouter LT for Symbian 9 Beta (Build 20070418)**

·受Symbian 9安全机制的限制，目前测试阶段只能以未认证安装包的形式发布。请各位参与测试的朋友自行认证后进行安装。（自行认证的步骤相信各位Symbian 9的资深机友都早已有所了解，后续我也会抽时间补充详细说明）
·配置文件的使用方法请参照安装后生成的FontRouter.ini文件。
·请务必安装在MMC，以免导致手机无法启动；
·为了方便修改（不受安全机制限制），实际的配置文件FontRouter.ini暂时放在根目录下的，“C:\Resource\Fonts”中的配置文件并没有实际作用（但不可删除，也不可移至存储卡）。
·安装后请根据实际使用的字体修改配置文件（配置文件中给出了针对简体中文S60 v3使用方正隶变字体和微软雅黑的范例）
·暂不支持Y轴位置调整功能、ExtraFontFile和AlterFontFile
·不支持GDR点阵字体（受LT版本的机制限制无法支持）
·只支持简单映射，不支持中英文分离映射（受LT版本的机制限制无法支持）