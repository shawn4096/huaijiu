// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "寺间小路");
	set("long", @LONG
你举步入寺，只听得叮叮两声清磬，悠悠从后院传出，霎时之间，只感遍
体清凉，意静神闲。
LONG
	);
        set("outdoors", "大理");
	set("exits", ([ /* sizeof() == 1 */
	    "out" : __DIR__"nianhuasimen",
	    "north" : __DIR__"yuan1",
        ]));
       
	set("no_clean_up", 0);

	set("coor/x",-200);
  set("coor/y",-430);
   set("coor/z",10);
   setup();
}
