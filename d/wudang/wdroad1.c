// wdroad1.c

inherit ROOM;

void create()
{
	set("short", "通知");
	set("long", @LONG
这里写着：去武当请走扬州西门！
LONG
	);
        set("outdoors", "wudang");

	set("exits", ([
		"north" : "/d/city/nanmen",
	]));

	setup();
}

