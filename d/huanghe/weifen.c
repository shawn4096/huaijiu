// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "渭汾流域");
	set("long", @LONG
汾河和渭河汇入黄河，增大了其水势，也带来了更多的泥沙。这里
河东是晋，河西是陕。
LONG );
	set("exits", ([
		"south" : __DIR__"huanghe1",
		"north" : __DIR__"huanghe_1",
                "southwest" : "/d/shaolin/yidao4",
	]));
	set("no_clean_up", 0);
	set("outdoors", "黄河");
	set("coor/x",120);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}

