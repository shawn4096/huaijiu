// Room: /d/village/shilu5.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
这是一个宁静的小村子，稀稀落落的分布着几十间土坯泥房，看来村
中人家不多，而且大都生活很艰辛。北面是间小庙，每年发生灾害的时候
村民门都到这里来祈求老天保佑。
LONG
        );
        set("exits", ([
  "east"  : __DIR__"shilu3",
  "south" : __DIR__"miaoyu",
]));
        set("no_clean_up", 0);
        set("outdoors", "华山");

        set("coor/x",-20);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}
