// Room: xiaolu1.c

inherit ROOM;

void create()
{
	set("short", "湖边小路");
	set("long", @LONG
天湖湖边的一条小路，向前望不到尽头，不知道通向那里。路边野花芬芳，
蝴蝶飞舞，除了你自己的脚步声，四下里只听见一声高一声低的鸟鸣。
LONG
	);

	set("exits", ([
		"southeast" : __DIR__"xiaolu2",
		"northeast" : __DIR__"tianhu",
	]));
        set("outdoors", "雪山");
	set("coor/x",-260);
  set("coor/y",130);
   set("coor/z",0);
   setup();
}
