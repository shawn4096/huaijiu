// Room: /d/dzd/mudi.c

#include <ansi.h>
#include "dmd.h"
#define XJNO 3

void create()
{
	set("short","林间墓地");
	set("long",@LONG
这里是黑森林的中心地带，却一棵树也没有,孤零零座落着一个坟墓。墓碑(mubei)正面光秃秃的，
后边隐约有些字迹。让你不禁想仔细看(kan)一下。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([
		"east" : __DIR__"senlin5",
		"west" : __DIR__"senlin4",
		"north" : __DIR__"senlin7",
		"northeast" : __DIR__"senlin8",
		"northwest" : __DIR__"senlin6",
		"southeast" : __DIR__"senlin3",
		"southwest" : __DIR__"senlin2",	
	]));
	set("item_desc",([
		"mubei" : "这是一个墓碑，正面光秃秃的，后边隐约有些字迹。\n",
		"fenmu" : "一座不知名的坟墓，上面长满了野草。\n",
	]));
	setup();
}

void init()
{
        object me;
        me = this_player();
        add_action("do_jie", "jie");

        if (interactive(me) 
         && ! me->is_fighting()
         && me->query_temp("dmd/done") < 9
         && !random(3)
         && me->query_temp("marks/勇闯夺命岛3") == XJNO){
                remove_call_out("greeting");
                call_out("greeting", 0, me);
        }
}

int do_kan(string arg)
{
	object me = this_player();
	if(me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");
	if(!arg || arg=="" || arg!="mubei")
		return notify_fail("你要看什么?\n");
	message_vision(HIY"墓碑上写着两行字:\n\n"NOR HIW"十年生死两茫茫，不思量，自难忘。千里孤坟，无处话凄凉。
纵使相逢应不识，尘满面，鬓如霜。\n\n夜来幽梦忽还乡，小轩窗，正梳妆；相对无言，惟有泪千行！
料想年年肠断处，明月夜，短松岗。\n\n"NOR,me);
	message_vision(HIB"看着这首词，你不由的想起了自己的伤心往事，悲从中来,无以附加。\n"NOR,me);
	return 1;
}
