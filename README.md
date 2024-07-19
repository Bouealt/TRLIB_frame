# TRLib

## 想法

以前师兄写的代码已经用`QT的信号槽机制`解耦的很好了，但是随着项目扩展，需要对代码再升级。QT的信号槽是这两个样子的：

```
// QT 5.0以前的定义方式
connect(this,                                      // 发送者
	SIGNAL(SendMsg(const QByteArray &)),           // 发送信号
	mqtt,                                          // 接收者
	SLOT(SendMessageToWeb(const QByteArray &)));   // 接收对象

// QT 5.0以后
connect(reconnect_timer,
	&QTimer::timeout,
	this,
	&Mqtt::MqttReConnect);
```

可以看到信号槽机制需要绑定四个约束：信号的发送和使用者、信号本身和信号的接收处理函数。

**约束越多，程序耦合性越高**，本来这样也是无所谓的，但是有些功能需求下，可能需要我们重新利用以往的代码模块或者，架构复用，在这样的需求下，单纯使用信号槽机制进行模块间的通信，可能会对后面的代码升级造成很多麻烦，最后实现较为困难且不优雅。

所以，如何将约束降维，是当前程序所要面临的一个问题，由此，我们引入并开发了**基于QT设计的通用软件DCI架构-TRLib**。

## 面向对象程序设计

“面向对象”是高级语言的共同点，也是程序设计的难点，但是其实是程序设计的捷径。

我们主要是使用`C++`作为项目的开发语言，C++的类，在C语言的`struct`的基础上，进行封装，加入了权限属性等等，能够帮我们很好的封装代码，C语言的struct本身来讲，是一个默认`public`的类定义。

面向对象程序设计的难点只有一个——它是抽象的。克服这个难点，基本上全是优点。一套软件开发流程一般也分为四个阶段：需求设计、系统分析、架构设计、编码实现。需求设计和系统分析其实是最难的，需要我们拥有丰富的开发经验和行业经验，在公司的话，一般需要产品经理和专业的解决方案工程师来负责，而架构设计就是CTO的活了，需要通过设计使得前面两步的成果实现，一般使用面向对象方法设计软件系统，将功能模块拆分成基本组件，通过对整体功能的完整性和模块组件粒度的考察来设计软件架构平台。

软件架构，只是为实现软件各组件正常运行合作的组织策略。链接：[十大软件架构](https://zhuanlan.zhihu.com/p/258814587)

## DCI架构和TRLib

DCI（Data Context Interactions）架构，是一个强调模块组件的耦合关联的架构，**只关注消息（Data）**，将消息注入模块场景以完成消息的交互，发送者不关心消息谁来消费，接受者不关心消息来自于哪里，**将模块间的交互约束降低到一维**。

**TRLib是一个基于QT应用开发的可泛用DCI架构框架**，可以帮助开发者进行多层分布应用架构的设计，采用的是`事件（消息）驱动`的思想，应用`Broker模式`，设计了消息队列，同时利用QT的平台无关性，可以移植到Linux、Windows、Mac等平台。

目前，TRLib里面最重要的角色就是：`TRBaseControl`、`TRBaseAction`两个组件：

- 其中`TRBaseControl`，内部封装了`TRData`类，每一个`TRData`对象通过智能指针管理，不需要关注其的销毁，会自动释放。数据分发通过**异步收集、同步分发**，避免了使用源语锁，也就是说它收集消息是绝对线程安全的、分发消息是按照收到消息的先后顺序来的，对于不是运行在单独线程的模块，由**TRBaseControl对象本身所在线程**调用各个模块本身的消息关注接口运行，避免了同时消费两个消息的情况。
- **TRBaseAction模块可以通过对消息的订阅来配置Control的分发规则**，上层应用开发过程中，只需要基于`TRBaseAction`模块实现各个功能模块即可。
- 框架本体采用抽象工厂、订阅发布者两种设计模式，`TRBaseControl`、`TRBaseAction`的组合实现了DCI架构的基本功能，`TRBaseActionEx`是`TRBaseAction`的异步派生（线程上），包括：对象注册、消息订阅、消息请求。

![image.png](https://note.youdao.com/yws/public/resource/935ec7d49d584ef69ea61d56d53e8857/WEBRESOURCEaa2e89313816d626827074b53ba64848?ynotemdtimestamp=1645270008568)

**未来发展**：

- TRLib目前是一个单进程程序的架构，不适用多进程的情况，可以利用`socket`和`管道`通信等，建立多进程程序架构，这个多进程架构可以作为插件扩展平台。
- 同时，TRLib目前并没有一个合适的日志模块，这是一个`多生产者单消费者`场景，采用单例模型的情况下，比较容易造成性能问题（因为日志模块的加入，造成对应模块的运行造成效率下降），比较推荐使用`线程池`的方式。
- 如果有需要，对于消息队列可以改造升级，比如建立延时队列、优先队列等等。

## 使用

- 后面开发只需要派生`TRBaseAction`、`TRBaseActionEx`实现对应的功能模块即可，每一个模块（组件）通过`RequestExecution() / RequestExecution(TRData::Ptr data)`向其他模块发送消息，每个模块通过`Execute()`和`Execute(TRData::Ptr data)`来接收，筛选和处理消息。

```
// 接入TRLib
#include "StereoCamera_global.h"
#include "TRBaseAction.h"
#include "TRBaseControl.h"

……

// 产生消息
TRData::Ptr data = TRData::CreateDate(cmd);
// 消息参数填充
data->SetArgument(ARG_POINT_X, 0);
data->SetArgument(ARG_POINT_Y, 0);
data->SetArgument(ARG_POINT_Z, 0);
// 发送消息，
TR_REQUESTEXECUTION(data); 
```

> 上面为一个模块消息发送的代码，按照目前的情况，事先要定义cmd，订阅这个cmd的组件都会收到这个消息，ARG_POINT_X这些都是字符串类型的参数说明，TR_REQUESTEXECUTION(data)向Control发送消息，然后内部自动对data进行分发消费。

![image.png](https://note.youdao.com/yws/public/resource/935ec7d49d584ef69ea61d56d53e8857/WEBRESOURCE120aaf391a35c584eacdd663b072fdd4?ynotemdtimestamp=1645270008568)

- 目前采用全局定义的方式来定义消息，需要手动定义好消息key（后期可以采用每个模块自主定义注册，架构生成全局定义的方法来实现更加灵活的定义）。 对于消息来说，采用64位无符号长整形来表示操作指令。

```
/// NET消息Key
#define CMD_SERVER_REQUEST_PIC			0x0003000100000000ULL		
#define CMD_SERVER_ROI_CALC				0x0003000200000000ULL
#define CMD_SERVER_REQUEST_SICPIC		0x0003000300000000ULL

/// argument
#define ARG_ROI_RECT_L					"leftRect"					// 左相机手动框选ROI
#define ARG_ROI_RECT_R					"rightRect"					// 右相机手动框选ROI
```

- 其余的，都在代码里面，注释都已经写好。

使用TRLib之后，每个模块可以单独分离，可以指定人员负责指定模块，多人参与同一个项目开发，类似流水线化开发。

# 一些其他文件

https://note.youdao.com/s/AxrXm9mC



### 个人理解

**TRBaseAction对象**

+ 属性：**控制对象**，命令列表，行为名字



**TRBaseActionEx对象**

行为执行

+ 属性：**控制对象**  ，   **线程对象**
+ 初始化： 绑定信号槽，ToExecute(Data) -------> OnExecuteEx(Data)
+ 槽函数： 行为执行  ， 登记注册
+ 信号：toExecute（data），发送**data对象**进行执行



**TRData对象**

模块通信信息

+ 属性：信息ID ，  信息的分类、执行码，  消息的具体内容
+ 初始化：初始化各个属性
+ 函数：创建任务； 返回map的值  ；   创建命令



**TRPublicRegister对象**

订阅-发布模式

+ 属性： Action字典（消息的具体内容），action_cmd列表（命令的内容）
+ 初始化
+ 函数： 抽象注册 ；  抽象删除  ；  具体注册 ；  具体删除；
+ 其他函数： 检测订阅  ；   查找对象指针；  查找对象名字  ；   所有注册对象



**TRDataDistribution对象**

数据分发

+ 属性：消息队列索引列表（id）   ；   控制核心；   消息队列实体（id+data）；  队列锁；















































