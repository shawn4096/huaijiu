// wdroad8.c 黄土路

inherit ROOM;

void create()
{
        set("short", "山脚下");
	set("long", @LONG
这里是武当山脚下，两旁是阴森森的树林。西边是一座高山, 东南方是一
茶亭。
LONG
	);
        set("outdoors", "wudang");

	set("exits", ([
		"east" : __DIR__"wdroad7",
                "southeast" : "/d/wudang/chating",
                "west" : __DIR__"xuanyuemen",
	]));
	set("objects", ([
		__DIR__"npc/yetu" : 2 ]));

	set("coor/x",30);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}

