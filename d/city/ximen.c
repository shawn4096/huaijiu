// Room: /d/city/ximen.c

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "西门");
	set("long", @LONG
这是西城门，城墙上贴着几张通缉告示(gaoshi)。西门是往西域的必经之
地，官兵们戒备森严。一条笔直的青石板大道向东西两边延伸。西边是郊外，
骑马的、坐轿的、走路的，行人匆匆。东边是城里的西大街。
LONG
	);
	set("outdoors", "扬州");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"east" : __DIR__"xidajie1",
		"west" : __DIR__"wroad1",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
	set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n扬州知府\n赵城之\n";
}

