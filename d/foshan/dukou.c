
inherit ROOM;

void create()
{
        set("short", "渡口");
        set("long",
"你迎着阵阵海风来到了渡口，这里是一个规模不大的渡口。
由于朝廷禁海，曾经繁荣的渡口渐渐地衰败了。\n"
        );
	set("outdoors", "佛山");
	set("no_fight",1);
	set("exits",([
        "northwest" : __DIR__"shulin1",
]));
        set("objects", ([
        __DIR__"npc/chuanlaoda" : 1,
]));
	set("coor/x",30);
        set("coor/y",-550);
        set("coor/z",0);

	setup();
}
