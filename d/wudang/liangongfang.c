// liangongfang.c 练功房 lgf.c

inherit ROOM;

void create()
{
	set("short", "练功房");
	set("long", @LONG
这里是练功房，地下凌乱地放着几个蒲团，几位武当弟子正盘膝坐在上面打坐。
LONG
	);
	set("exits", ([
                "east" : __DIR__"xiaolu7",
	]));
	set("objects", ([
    BINGQI_D("zhujian") : 1,
                            __DIR__"obj/mudao" : 1,
                  "/kungfu/class/wudang/chenyun" : 1,
        ]));
	
	set("coor/x",-50);
  set("coor/y",-70);
   set("coor/z",100);
   setup();
}
