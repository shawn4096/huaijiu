// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "杂货店");
        set("long", @LONG
这是一个简陋的杂货店，但是东西却很齐全。老板常亲自去中原采购一些
物品回来贩卖。
LONG
        );

        set("exits", ([
                 "west" : __DIR__"jiedao1",
        ]));
        set("objects",([
                __DIR__"npc/laoban" : 1,

        ]));

    
//        set("outdoors", "miaojiang");

        setup();

}
