// /d/city/yuelaoting.c
// update by beyond

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "月老亭");
	set("long", @LONG
这里是扬州城的月老亭。亭子四周柱子上贴满了字条，也有些人物肖
像画，看来有不少人留了名字在这里，希望能找个如意佳偶。有几张字条
被人用红笔勾了出来，十分显眼。有情人在这里都找月下老人去结婚登记。
LONG
        );

	set("exits", ([
		"west" : __DIR__"yueqidian",
		"north" : __DIR__"yltw",
        ]));
	set("objects",([
		__DIR__"npc/yuelao" : 1,
                __DIR__"npc/shuang" : 1,
        ]));
	set("no_fight", 1);
	set("no_sleep_room", 1);
	set("coor/x",130);
  set("coor/y",-30);
   set("coor/z",0);
   setup();
       call_other("/clone/board/yuelao_b", "???");
}
