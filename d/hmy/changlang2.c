// /d/hmy/changlang2.c

inherit ROOM;

void create()
{
	set("short", "长廊");
	set("long", @LONG
一条长长的过道，左右两旁都是墙，每隔四五丈，墙上都点着一支明晃
晃的巨烛。
LONG
	);
	set("exits", ([ 
	  "east" : __DIR__"qianqiudian",
	  "south" : __DIR__"chengdedian",
	  "west" : __DIR__"qinglongtang",
]));
	setup();
}
