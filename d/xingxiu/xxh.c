// Room: /d/xingxiu/xxh.c

#include <wanted.h>
inherit ROOM;

void create()
{
        set("short", "星宿海");
        set("long", @LONG
这里是天山脚下的星宿海海边。因方圆几百里都是一望无际的湖泊
和沼泽，当地牧羊人称之为“海”。一旦有几只离群的羊走迷在“海”里，
便再也找不着了。臭名昭著的星宿派总坛便设在海中央。
LONG
        );
        set("exits", ([
             "north" : __DIR__"xxh1",
             "south" : __DIR__"shanjiao",
             "southeast" : __DIR__"yili",
        ]));
        set("objects", ([
                __DIR__"npc/gushou"  : 1,
                __DIR__"npc/haoshou" : 1,
                __DIR__"npc/boshou" : 1,
                __DIR__"npc/azi" : 1,
        ]) );

        set("outdoors", "xingxiuhai");

        set("coor/x",-310);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (is_wanted(me) && dir == "north")
		return 0;
	return ::valid_leave(me, dir);
}
