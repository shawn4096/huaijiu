// /d/wudang/sanqingdan.c  三清殿
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY"三清殿"NOR);
        set("long", @LONG
这里是紫霄宫的三清殿，是武当派会客的地点。供着道德天尊、元始天尊
和灵宝天尊的神像。正中间是个敬香的大香案，靠墙放着几张太师椅，地上放
着几个蒲团。北边是练武的广场，南边是武当禁地。
LONG                           
        );
        set("exits", ([
                "south" : __DIR__"xiaolu1",
                "north" :__DIR__"guangchang",
        ]));

        set("objects",([
                "/kungfu/class/wudang/song" : 1,

        ]));

	set("valid_startroom", 1);

        set("coor/x",-20);
  set("coor/y",-70);
   set("coor/z",100);
   setup();
        "/clone/board/wudang_b"->foo();
}
/*
void init()
{
        object me;
	int lvl;
        mapping learned;

        me = this_player();

	lvl = me->query_skill("taiji-shengong", 1);
	learned = me->query_learned();
	me->delete_skill("taiji-shengong");
	if (lvl > 0) {
		me->delete_skill("yinyun-ziqi");
		me->set_skill("yinyun-ziqi", lvl);
		if (mapp(learned) && learned["taiji-shengong"] > 0)
			me->improve_skill("yinyun-ziqi",
				learned["taiji-shengong"], 1);
		write(HIG "系统已将您的「太极神功」转换为「氤氲紫气」。\n" NOR);
	}
	if (me->query_skill_mapped("force") == "taiji-shengong")
		me->map_skill("force", "yinyun-ziqi");
} */
