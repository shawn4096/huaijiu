// liangongfang.c (kunlun) 练功房

inherit ROOM;

void create()
{
	set("short", "练功房");
	set("long", @LONG
这里是练功房，地下凌乱地放着几个蒲团，正中烧着几柱香，轻烟袅袅升
起。几位昆仑派弟子正盘膝坐在上面打坐。
LONG
	);
	set("exits", ([
		"south" : __DIR__"sanshengtang",
		"north" : __DIR__"xiuxishi",
		"east"  : __DIR__"chufang",
	]));
	set("objects", ([
		BINGQI_D("zhujian") : 2,
	]));

	set("no_fight", 1);

	setup();
}
