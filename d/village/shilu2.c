// Room: /d/village/shilu2.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
这是一个宁静的小村子，稀稀落落的分布着几十间土坯泥房，看来村
中人家不多，而且大都生活很艰辛。这是一条南北向的碎石路，东面是间
铁匠铺，主人冯铁匠打铁为生。
LONG
        );
        set("exits", ([
  "east"  : __DIR__"tiejiangpu",
  "north" : __DIR__"zhongxin",
  "south" : __DIR__"shilu1",
]));
        set("no_clean_up", 0);
        set("outdoors", "华山");

        set("coor/x",0);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}


