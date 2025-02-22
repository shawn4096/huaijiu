// room: /d/xingxiu/store.c

inherit ROOM;

void create()
{
        set("short", "商铺");
        set("long", @LONG
这是伊犁城最大的商铺, 本地维吾尔族称商铺为巴扎。巴扎上，
奇珍异宝，往往有之。牲畜果品，尤不可枚举。巴扎的主人坐在铺在
地上的地毯上，旁边堆着他的货。墙上有个牌子，是个价目表(sign)。
LONG);
        set("exits", ([ 
             "east" : __DIR__"yili2",
        ]));

        set("objects", ([
                __DIR__"npc/maimaiti": 1,
                __DIR__"npc/shangren": 1  
        ]));

        set("item_desc", ([ 
"sign" : "牌子上写道：
中原钱币通用。
        马奶酒壶(hu)       一百文
        火折(fire)         一百文
        冬不拉(dongbula)   一百文
        水囊(shuinang)     两百文
        大酒囊(jiunang)    两百五十文
        绵羊皮(yangpi)     三百文
        马鞭(mabian)       三百文
        羊皮袄(yangpi ao)  五百文        
        哈萨克袄裙(ao qun) 一千文        
        阿拉伯弯刀(wandao) 一千五百文
        马刀(ma dao)       一千五百文
        毛毯(maotan)       三千文
        寓意草(yuyi cao)   七千文
        硫磺(liu huang)    一百文
        坛子(tan zi)       五百文
        
        \n"
]));
    
        set("coor/x",-310);
  set("coor/y",160);
   set("coor/z",0);
   set("coor/x",-310);
 set("coor/y",160);
   set("coor/z",0);
   setup();
}

