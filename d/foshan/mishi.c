// Room: /d/fuoshan/mishi.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "密室");
	set("long", @LONG
这里就是凤天南存放宝物的密室。
LONG
	);
	set("exits", ([
  "up" : __DIR__"shufang",
]));

        set("objects", ([
                __DIR__"obj/huangjingun" : 1,
                __DIR__"obj/tiancanjia" : 1,
        ]));


	setup();
}
