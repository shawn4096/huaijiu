// Room: /d/village/zhongxin.c

inherit ROOM;

void create()
{
        set("short", "村中心");
        set("long", @LONG
这里是村子的中心，一个平坦的广场，每年秋收打谷就在这。广场东
角有棵大槐树，平日茶余饭後，村里的男女老少都爱聚在这里谈天说地。
角上有几个大谷堆。
LONG
        );
        set("exits", ([
		"northwest" : __DIR__"caidi",
		"northeast" : __DIR__"caidi",
		"south" : __DIR__"shilu2",
		"east"  : __DIR__"shilu4",
		"west"  : __DIR__"shilu3",
	]));

        set("objects", ([
                __DIR__"npc/boy": 1,
                __DIR__"npc/girl": 1,
        ]) );

        set("no_clean_up", 0);
        set("outdoors", "华山");

        set("coor/x",0);
  set("coor/y",100);
   set("coor/z",0);
   setup();

}
