// Room: /d/village/shilu4.c

inherit ROOM;

void create()
{
        set("short", "碎石路");
        set("long", @LONG
这是一个宁静的小村子，稀稀落落的分布着几十间土坯泥房，看来村
中人家不多，而且大都生活很艰辛。这是一条东西向的碎石路，北面是间
杂货铺，主要是卖一些游客上山用的东西。
LONG
        );
        set("exits", ([
	"east"  : __DIR__"shilu6",
	"west"  : __DIR__"zhongxin",
	"north" : __DIR__"zahuopu",
]));
        set("no_clean_up", 0);
        set("outdoors", "华山");

        set("coor/x",10);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}


