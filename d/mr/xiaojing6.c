// /u/beyond/mr/xiaojing6.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
         set("short",GRN"小径"NOR);
         set("long",@long
一条曲曲折折用鹅卵石铺成的小径, 路两旁绿柳成阴, 一处处山石花木
点缀在其中。你走在石地上，啪嗒啪嗒的发出清脆的响声，往北面看去是一
片柳树林，南面和东面是小径的延伸。
long);
set("outdoors","mr");
         set("exits",([
             "east" : __DIR__"xiaojing7",
             "north" : __DIR__"liulin1",
             "west" : __DIR__"xiaojing5",
             "south" : __DIR__"xiaojing8",
]));
set("objects",([
__DIR__"npc/yahuan" : 2,
]));
	setup();
}
