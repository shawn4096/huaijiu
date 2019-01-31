#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "渡口");
        set("long", @LONG
眼前就是辽阔无边的茫茫大海，海水波涛起伏，一浪接着一浪地朝岸边击
来，一眼望去，只见几羽海鸥在海面上飞翔，偶而也可见到远处有帆影掠过。
这里是钓鱼岛唯一可以停靠船舶的地方，这里的东西两边都是沙滩，往北则有
一个树林。
LONG
        );

        set("exits", ([
"north" : __DIR__"haitan1",
        ]));
		  set("objects", ([
   __DIR__"npc/chuanfu" :1,
	]));
	set("no_fight",1);
        set("outdoors", "钓鱼岛");
        set("coor/x",490);
  set("coor/y",420);
   set("coor/z",0);
   setup();
        
}

int valid_leave(object me, string dir)
{

        if ( dir == "north")
           return notify_fail(CYN"都到渡口了，就赶紧离开吧。\n"NOR);

        return ::valid_leave(me, dir);
}
