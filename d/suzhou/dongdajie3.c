inherit ROOM;
void create()
{
	set("short", "东大街");
	set("long", @LONG
	你走在东大街上，踩着坚实的青石板地面。东边是东大街的延
伸，南面是苏州城里一个老字号的当铺，北面是一条小胡同。
LONG
	);
        set("outdoors", "suzhou");    
        set("objects",([
        __DIR__"npc/kid" : 2,
        ]));
        	set("exits", ([
		"east" : __DIR__"dongdajie2",
		"southwest" : __DIR__"baodaiqiao",
		"northwest" : __DIR__"canglangting",
		"north" : __DIR__"hutong",
                "south" : __DIR__"baoheji",
	]));
	set("coor/x",120);
  set("coor/y",-220);
   set("coor/z",0);
   setup();
}

