// Room: nan-room.c
// Created by Numa 1999-11-21

inherit ROOM;

void create()
{
	set("short", "男弟子休息室");
	set("long", @LONG
这里是供男弟子休息的房间，里面摆着几张大床。
LONG);
	set("exits", ([ 
            "north" : __DIR__"qindian",
        ]));
        set("no_clean_up",0);
	set("no_fight", 1);
	set("sleep_room", 1);
    set("indoors", "嵩山");
	set("coor/x",60);
  set("coor/y",330);
   set("coor/z",120);
   setup();
}
