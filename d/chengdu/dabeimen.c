// /d/chengdu/dabeimen.c
// By Jpei

#include <room.h>

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "大北门");
	set("long", @LONG
这是就是成都的北城门了。成都地处川中，一向少有战事困扰，所以很少
见到有士兵。城门的墙上张贴着一纸告示(gaoshi)。
LONG
	);

	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));

	set("exits", ([
		"south" : __DIR__"beidajie4",
	]));
        set("outdoors", "成都");
	set("coor/x",-150);
  set("coor/y",20);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
 	return FINGER_D->get_killer() + "\n益州刺史\n司马远\n";
}

