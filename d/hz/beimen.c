// /u/beyond/hz/beimen.c 北门
#include <ansi.h>
#include <room.h>
inherit ROOM;
string look_gaoshi();
void create()
{
	set("short",HIY"北门"NOR);
	set("long", @LONG
这里就是杭州城的北门了，俗话说：上有天堂，下有苏杭。慕名而来的
游客络绎不绝，而站在城门口把守的官兵，也细细盘查过往的游客，他见你
走过来，连忙上前盘查。城门口贴着一张告示(gaoshi)。
LONG
	);
	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));
	set("exits",([
                  "north" : __DIR__"qsddao7",
                  "south" : __DIR__"qsddao6",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
	set("outdoors", "hz");
	set("coor/x",100);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n杭州知府\n王忠\n";
}

