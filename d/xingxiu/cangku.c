inherit ROOM;

void create()
{
        set("short", "天然石洞");
        set("long", @LONG
这里就是星宿派老巢的储藏处。从外面看只是一个开在石山上的普通天
然石洞，然因地点隐密而且洞中空气十分干燥，星宿派弟子将这里改造成了
一个绝佳的储藏库。
LONG);
        set("exits", ([
           "out" : __DIR__"xx2",
        ]));
        set("objects", ([
                FOOD_D("hulu") : 2,
                MEDICINE_D("menghan_yao") : 1,
                MEDICINE_D("dujing_1") : 1,
//add by caiji                MEDICINE_D("qxs") : 1,
                ARMOR_D("armor"): 2,
                __DIR__"obj/fire" : 2+random(2),
/*
                __DIR__"obj/yao" : 1+random(6),
                __DIR__"obj/yao1" : 1+random(6),
                __DIR__"obj/yao2" : 1+random(6),
                __DIR__"obj/yao3" : 1+random(6),
*/
//                   BINGQI_D("zh_biao"): 1,
        ]));
        setup();
}
