inherit ROOM;
void create()
{
        set("short","赌场大厅");
        set("long", @LONG
你一走进这房间，只听到玎玲玲，玎玲玲骰子落碗之声，说不出的悦耳
动听。房里已聚着五六个人，都是一般的打扮，正在聚精会神的掷骰子，抬
头一望有匾（ｓｉｇｎ）一块。
LONG
        );
        set("exits", ([ /* sizeof() == 4 */
         "east" : __DIR__"duchang",
         "north" : __DIR__"duchang4",
  
]));
        set("item_desc", ([
                "sign": @TEXT


骰子的赌法：

ｂｅｔ　＜种类＞　＜数量＞

种类：　０，１，２，３到１８
０：　          赌小    （３－１０）    一赔一
１：            赌大    （１１－１８）  一赔一
２：　          赌围骰  （三粒骰子同点）一赔三十六
３－１８        赌单点                  一赔八

例子：
ｂｅｔ　０　５０
赌五十两在小上

TEXT
        ]) );
        set("no_fight",1);
        set("no_sleep",1);
        set("objects", ([
        __DIR__"npc/pingwei" : 1,
                        ]) );
        set("coor/x",80);
  set("coor/y",-20);
   set("coor/z",0);
   setup();
}
void init()
{
object me;
me = this_player();
if( me->query("gamble/amount")) {
me->delete("gamble/amount");
me->decrease_skill("betting",1);
}

        add_action("action", ({
                   "dazuo",
                   "du",
                   "exercise",
                   "lian",
                   "practice",
                   "respirate",
                   "study",
                   "tuna"
        }));
}

int action()
{
        write("你无法静下心来修炼。\n");
        return 1;
}


