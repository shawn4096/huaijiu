#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short",HIW"茶馆"NOR);
	set("long", @LONG
你一走进来，就闻到一股茶香沁入心脾，精神为之一爽。几张八仙桌一字
排开，坐满了客人，或高声谈笑，或交头接耳。几个店伙计在一旁伺候着客人
们，在台后坐着一位老板娘，正在弹着算盘。
LONG
	);
	set("resource/water", 1);
        set("objects",([
                 __DIR__"npc/shinv" : 1,
        ]));
	set("exits", ([
		"southwest" : __DIR__"nandajie1",
	]));

	set("coor/x",120);
  set("coor/y",-230);
   set("coor/z",0);
   setup();
}

