// Room: nan-room.c
// Created by Numa 1999-11-21

inherit ROOM;

void create()
{
	set("short", "�е�����Ϣ��");
	set("long", @LONG
�����ǹ��е�����Ϣ�ķ��䣬������ż��Ŵ󴲡�
LONG);
	set("exits", ([ 
            "north" : __DIR__"qindian",
        ]));
        set("no_clean_up",0);
	set("no_fight", 1);
	set("sleep_room", 1);
    set("indoors", "��ɽ");
	set("coor/x",60);
  set("coor/y",330);
   set("coor/z",120);
   setup();
}
