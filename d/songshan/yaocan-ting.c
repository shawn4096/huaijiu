// Room: /yaocan-ting.c
// Created by Numa 1999-11-21

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIG"遥参亭"NOR);
	set("long", @LONG
这是一座古色古香的亭台，由青砖整体铺构而成，亭上横卧一匾，
上写“遥参亭”三个隶书大字。向北边望去，远远能看见一座琉光璃
瓦的大殿，好不壮观。
LONG);
	set("exits", ([ 
            "north" : __DIR__"tianzhong-ge",
            "south" : __DIR__"shidao1",
        ]));
	set("outdoors", "嵩山");
	set("coor/x",40);
  set("coor/y",300);
   set("coor/z",110);
   setup();
}
