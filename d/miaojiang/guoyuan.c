// /u/dubei/miaojiang


inherit ROOM;

void create()
{
        set("short", "果园");
        set("long", @LONG
这里是苗人的果园，里面种满了水各种果。有几位苗家女子正在树下干活。
LONG
        );

        set("exits", ([
                "west" : __DIR__"jiedao5",
               
        ]));
        set("objects",([
//                __DIR__"npc/miaobing" : 1,

        ]));

        set("no_clean_up", 0);
        set("outdoors", "miaojiang");

        setup();

}
