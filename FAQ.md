使用中的常见问题解答 （感谢热心的whyou汇总整理）

  * 在Nokia N8、C7、C6-01等机型上安装 FontRouter 后无法启动

FontRouter的目前版本在Symbian<sup>3下与QT系统存在未知的兼容性问题，目前请勿在Symbian</sup>3系统或者安装了QT运行环境的S60系统上使用FontRouter。如果已经安装，请参照[故障恢复指南]。

  * 每次安装Fontrouter LT都会提示手机不兼容

安装的不兼容提示是因为FontRouter LT本身需要兼容S60和UIQ等不同的平台，所以不能嵌入特定的平台标识，因此手机的安装系统无法识别其兼容性。这个提示请直接忽略。

  * 字体显示位置不正常，有些剃头（向上偏移）或者例如英文字母y，g等剃尾（向下偏移）。最新版的Fontrouter LT不是可以自东调节吗？如何使用？

自动调节的功能默认并未开启，需要手动在配置文件中打开：
FixFontMetrics=1
FixCharMetrics=1

  * 开启上述选项后依然不正常

可能是字体文件不太符合标准的尺寸格式，说实话Symbian下的TrueType字体驱动对中文字体文件实在比较挑剔，不如Windows的兼容性好。虽然FontRouter LT中尽可能的做了修补和调整，但也常常无法完全让人满意。

你不妨试试
FixFontMetrics=0
FixCharMetrics=1
的组合，我不确定是否有效果。

另外，如果有条件的话，可以尝试用Font Creator Program这款软件修正一下ttf文件的自行参数，主要是其中的Ascent/Descent或者Baseline值（因为我不确定你的字体文件哪方面不标准……）。

  * SE W950I每次用数据线跟手机连接后再拨掉就会丢失整个data文件夹

把配置文件设置成只读和系统即可

  * 我的手机是5500，港行，版本是4.6的，用Fontrouter加载微软雅黑字体之后，无法使用UCWEB，卸载之后可以正常使用UCWEB，是何问题？

不是冲突，而是UCWEB请求的字体在FONTROUTER里没有得到回应，而产生这种情况的，在配置文件最下面加如下两行就行了

Sans MT 936\_S16=MicroSoft YaHei
Sans MT 936\_S24=MicroSoft YaHei

  * 下了个FontRouter LT,于是我试图装进我的N95里，我点了安装，屏幕出现：

"Install FontRouter LT?"

然后我点"Yes"，接着出现了下面的字样：

"Certificate error, contact the application supplier"

这个是不是和他们说的什么签名有关呢？我试了下这个网上提供的另外一款：OPEN SIGNED ONLINE版本，出现的情况一模一样，我要怎么解决这个问题呢？

你的问题解决方法是在www.symbiansigned.com的open signed online把fontrouter OPEN SIGNED ONLINE版本签名后安装

  * 方正系列字体，雅黑字体好像都有1到2个像素的轻微剃头，所有显示文字的地方都是如此，可能是FontRouter的默认设置有点问题？如果我想所有地方的字体都下移一个像素，该如何做？

FixCharMetrics=0一定要改成1！如此剃头剃尾现象即可消除

另外，新增全局属性“ZoomRatio”，用于所有字体的按比例缩放，取值为百分比（不含“%”），默认值为100。

  * 经过我的测试, FontRouter.LT.for.v9.Build20071109 与 MSDict Viewer 是有冲突的.进入MSDict Viewer没问题的, 但是一进入词语的解释界面, 机器就重启.

你可以在FontRouter.ini里添加如下所示的语句

ExtraFontFile=C:\Data\Fonts\OyuanMore9\_24.ttf

PS.路径是绝对路径，这是我的配置文件里的 这样可以使用数据线模式

  * 我手机是美版的，安装了Fontrouter LT软件和微软雅黑字体。请问这软件除了能显示中文以外，不能让我发短信也是中文吗??

麻烦你安装个中文输入法

  * 装FONTROUTER后，用USB模式提示 内存占用,不能用USB

因为读取的字体在手机的E盘，可以考虑将其移至C盘中，一般可以解决这个问题。

  * 求n76装少女体后外屏花屏的解决方法!~我的n76装了最新的字体驱动!~里屏用着没问题!~可多翻几次盖,外屏便出现花屏现象!~~有可行的解决方法吗???谢谢老大!~~少女体太可爱了!~

修改配置文件为ForceAntiAliased=0

  * NOKIA6120C发短信打字时输入"横折"(5键)不显示。可以打出字,但那个笔画不显示. 字体用的是:华康少女字体.

是字体没有这个符号，建议找网上别人修改的智能手机专用版或者干脆换字体。

  * 请高人提供一个使用本机字体的INI文件把。

[Global](Global.md)
Enable=1
NativeFont=0
LogLevel=4
ForceAntiAliased=4
FixFontMetrics=1
FixCharMetrics=0
ZoomRatio=100
ZoomMinSize=0
ZoomMaxSize=48
Chroma=100
[FontMap](FontMap.md)
=Sans MT 936\_S60:IB
Sans MT 936\_S60=Sans MT 936\_S60:IB
;Series 60 ZDigi@5=Series 60 ZDigi@7
;Sans MT 936\_S60@34=
;Sans MT 936\_S60@25=
System One=Sans MT 936\_S60:IB
**=Sans MT 936\_S60:IB**

  * ccc字体文件的调用方法与ttf一样吗？

一样

  * 显示输入法使用的小数字不正常，显示时钟数字不正常怎么办

建议加载ceurope.gdr，用原机的，不开nativefont就可以

  * 请问 Disable.frt SafeMode.frt 文件怎么创建？

用读卡器在存储卡根文件夹下创建上述名字的空文件。

  * 请问，N80 读取短信时，字体小得令人受不了。是否可以透过 FONTROUTER 来实现改变字体大小？

可以。

通过定制字体映射，比如：

**@15=**@20

可以增大字体。
建议首先通过日志文件查看有哪些字体大小的请求，然后依次为其定制大小关系。