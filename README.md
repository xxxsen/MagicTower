# MagicTower
一个比较简单的魔塔, n年前的一个想法, 最近总算给写了出来, 整个工程由地图, 块资源(地图上的物品), 图片, 对话列表组成, 方便随意修改。(目前还缺个编辑器, 每次都要自己改配置文件确实很蛋疼。)

# 编译要求
* 编译器:g++5.0以上(代码中引用了codecvt头文件, 所以需要支持c++1y的编译器才行)
* 库:jsoncpp, sdl(1.2版本), sdl-image, sdl-ttf

库的安装可以自己下载编译或者使用apt-get(ubuntu)进行安装
```shell
sudo apt-get install libjsoncpp-dev libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev
```
另外代码中应该没有引用到平台相关的库, 所以也是可以在win下编译的。

# 如何配置?
## 目录结构
```
游戏根目录
├── config.json #主配置文件
├── font        #子图数据
├── img         #图片数据
├── map         #地图数据
├── res         #块资源数据
├── MagicTower  #游戏的主程序
└── wording     #对话资源
```

## 配置入口
入口文件为根目录下的config.json, 这个配置文件中大部分对用户来说是没必要的, 这里简单说下几项有用的.
* **basic_root**, 非常重要的配置, 它需要配置为游戏的根目录位置, 如果配置不对, 运行的时候会找不到资源。
* **log_level**, 日志等级, 开发的时候方便看日志, 日志级别, 0-TRACE, 1-DEBUG, 2-NORMAL, 3-ERROR, 4-FATAL。
* **log_file**, 日志文件, 默认不配置则是输出到控制台, 否则输出到指定的文件。

## 地图
存放于map目录中, map.json为入口, 在floor_layout_list 键中添加自己的地图文件的名称, 例如:map/floor_xxx.json, 文件名没有特意规定, 可以任意起
之后编辑对应文件名的json, 如刚刚的map/floor_xxx.json。
每个楼层json由up_index, down_index, map, 3部分组成, up_index为上到某个楼层后定位的位置, down_index则是下楼的位置(原先是自动查找地图里面的楼梯来实现的, 觉得有点蛋疼, 就换成了手动指定了。), map为地图的实际展示内容, 是一个15x15的矩阵, 由块资源中的id组成。
一个例子:
```json
{
    "up_index":[0, 0],
    "down_index":[1, 1],
    "map":[
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0]
    ]
}
```

## 块资源
res目录, 块资源就是地图中展示的数据, 数据格式为
```json
[
    {"id":0, "name":"第一个块", "desc":"这里是描述", "class":"这里是具体的实现类", "img":"这里是展示的图片"},
    {"id":1, "name":"第二个块", "desc":"这里是描述", "class":"这里是具体的实现类", "img":"这里是展示的图片"}
]
```
上面展示的json串中, 每一个object行都是一个块, 块的基础属性为id, name, desc, class, img, 其中的id需要唯一, name代表的是块的名称, desc是描述, 这2个都不重要, 可以任意填, class为块使用的类, 程序启动的时候会使用指定名称的类去初始化该块, img为块在地图中展示的图片, 按id#name 的形式填写, 具体的可以参考图片那一段。
一个比较详细的块的例子:
```json
{"id":24, "name":"岩浆", "desc":"踩上去会死人的", "class":"Lava", "img":"20#lava", "cost":100, "auto_delete":0}
```
除了基础的4个属性外, 还有一个cost和auto_delete, 这些都是特化的属性, 当然了, 这些也需要自己代码里面去实现它的含义。

## 图片
img目录, 这个地方主要存放图片的展示信息的, 基础json
```json
[
    {"id":1, "img":"img/door.png", "location":{"yellow_door":[0, 0], "blue_door":[0, 1],            "red_door":[0, 2], "stone_door":[0, 3]}}
]
```
每一行用于解析一张图片, 基础属性, id, img, location, id是唯一标记, img是图片的相对路径, location为每个块切割的位置, location的坐标比较奇怪, **采用(y, x)的存放方式**, 跟地图刚好相反。
在块资源中引用图片的形式为${id}#{location_name}, 例如 1#yellow_door, 1#blue_door, 1#stone_door

## 对话
wording目录, 为了避免在代码文件中写入一堆的对话, 所以将对话单独抽离出来, 代码中引用的时候直接使用对话id来表示。
wording 的json结构:
```json
[
    {"id":1, "list":[
        "勇者:你是什么人? 为什么会在这里? 这里很危险的, 你要快点离开这, 不然会被妖怪吃掉的。",
        "村民:我是个傻逼。我就不走, 你咬我啊？",
        "勇者:..."
    ]}
]    
```
其中, id, list都是必要属性, 同其他模块一样, id作为唯一标记, list为对话列表, list中的每一段为一页的对话内容。

# 开发
## 编写自己的块类(MagicObject)
基础块为MagicObject, 子类需要继承并实现对应的虚函数。
### 相关虚函数
```cpp
virtual void doCollision(Player &player);
virtual bool construct(const Json::Value &v);
virtual void backup(Json::Value &v);
```
### 函数说明
1. doCollision 为勇者触碰到时候触发, 可以在这个函数里面做相关的操作, 例如加血, 加攻, 也可以直接杀死勇者。
2. construct 为资源构造的时候使用, 传入数据为res.json中的一个object对象, 用户可以只关系自己自定义的数据, 对于基础的属性可以调用MagicObject::construct(v); 进行委托构造。
3. backup, 跟cnstruct相反, backup用于将对象的数据备份到json中去, 基础属性同样可以委托父类进行构造。 通常来说, 这个backup主要用于怪物类的生命数据的保存, 其他类数据如果没需求可以不实现。
### 类注册
每一个块资源都要进行注册才能在res.json中被引用到, 注册方式很简单, 只需要在类对应的cpp文件中加上一行REGIST_OBEJCT(${你的类名}); 即可, 例如 REGIST_OBJECT(MyKey);
### 一个例子
```cpp
//res.json
[
    {"id":2000, "name":"红钥匙", "desc":"红色的钥匙", "class":"Key", "img":"3#red_key", "cnt":1}
]

//key.h
class Key : public MagicObject
{
public:
    Key();
public:
    bool construct(const Json::Value &v) override;
    void doCollision(Player &player) override;
    int32_t getSize();
private:
    int32_t sz_;
};

//key.cpp
Key::Key() : MagicObject(MO_KEY) { }

bool Key::construct(const Json::Value &v)
{
    if(v.isMember("cnt"))
        sz_ = v["cnt"].asInt();                         //从配置中获得每次增加的钥匙数目
    else
        sz_ = 0;

    return MagicObject::construct(v);                   //生成基础属性
}

int32_t Key::getSize()
{
    return sz_;
}

void Key::doCollision(Player &player)
{
    player.setRedKey(player.getRedKey() + getSize());   //增加勇者的红钥匙数目
    player.killBlock();                                 //清理当前的红钥匙方块
}

REGIST_OBJECT(Key);
```
