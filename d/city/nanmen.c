// Room: /d/city/nanmen.c

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "南门");
	set("long", @LONG
这是南城门，城墙上贴着官府的告示(gaoshi)。官兵们正在认真地检查每
一个过往的行人，查看他们是否携带私盐。青石板大道向南北两边延伸。
LONG
	);
        set("outdoors", "扬州");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"south" : __DIR__"jiangbei",
                "north" : __DIR__"nandajie1",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));

	set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n扬州知府\n赵城之\n";
}

