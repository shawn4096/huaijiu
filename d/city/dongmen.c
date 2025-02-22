// Room: /d/city/dongmen.c

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "东门");
	set("long", @LONG
这是东城门，城门正上方刻着“东门”两个楷书大字，城墙上贴着几张官
府告示(gaoshi)。官兵们警惕地注视着过往行人，你最好小心为妙。一条笔直
的青石板大道向东西两边延伸。东边是郊外，隐约可见一片一望无际的树林，
神秘莫测。西边是城里。
LONG
	);
        set("outdoors", "扬州");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"east" : __DIR__"eroad1",
        "south" : "/d/suzhou/yzyunhe",
        "north" : __DIR__"biaoju",
        "northeast" : __DIR__"guandimiao",
		"west" : __DIR__"dongdajie1",
	]));

	set("objects", ([
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
	]));

	set("coor/x",130);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n扬州知府\n赵城之\n";
}

