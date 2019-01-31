// Room: /d/fuzhou/beimen.c

inherit ROOM;
string look_gaoshi();

void create()
{
	set("short", "北门");
	set("long", @LONG
这里是福州的北门。出此门向北可抵江浙一带。城门的墙上张贴
着一纸告示(gaoshi)。
LONG
	);

	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));

	set("exits", ([
                "north" : __DIR__"road5",
                "south" : __DIR__"zhongxin",
	]));

	set("outdoors", "福州");
	set("coor/x",100);
  set("coor/y",-460);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
 	return FINGER_D->get_killer() + "\n福州巡府\n王舜成\n";
}