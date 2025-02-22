// /d/hmy/shimen.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "石门");
        set("long", "
    走到一道大石门前，只见两旁刻着两行大字，右首是“文成武德”，左
首是“仁义英明”，横额上刻着

                "HIR"日   月   光   明"NOR"

四个大红字。\n");
	set("outdoors", "黑木崖");
	set("exits", ([
	"eastdown" : __DIR__"shijie2",
]));
	set("objects", ([ 
	  __DIR__"npc/jiabu" : 1,
]));

	setup();
}
void init()
{
        add_action("do_say", "say");
}

int do_say(string arg)
{

        if( !arg || arg=="" ) return 0;

        if( arg=="教主文成武德，一统江湖"
        ||  arg=="教主令旨英明，算无遗策")
        {
                write("只听贾布说了声：嗯。。是本教兄弟吧？请进来吧。\n");
                message("vision", "那道大石门缓缓移了开来，一个日月教徒说道：“请进。”\n", this_player());
                set("exits/westup", __DIR__"ryping");

                remove_call_out("close");
                call_out("close", 5, this_object());

                return 1;
        }
}

void close(object room)
{
        message("vision","只见那大石门乒地关上了。\n", room);
        room->delete("exits/westup");
}

int valid_leave(object me, string dir)
{
	mapping myfam;
	myfam = (mapping)me->query("family");

	if ((!myfam || myfam["family_name"] != "日月神教") && dir == "westup" &&
		objectp(present("jia bu", environment(me))))
	   return notify_fail("贾布喝道：站住！你不是日月神教弟子，不得入内。\n");
		
        return ::valid_leave(me, dir);
}
