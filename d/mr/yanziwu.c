// /u/beyond/mr/yanziwu.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "院门");
	set ("long",@long
燕子坞是幕容氏世居之地, 幕容氏乃夕日大燕国的后裔, 后来日见式微, 
但其弟子却一心一意想光复大燕。其武功见长于以彼之道, 还施彼身, 端的
十分厉害。
long);
	 set("exits",([
"south" : __DIR__"xiaojing1-2",
"west" : __DIR__"houyuan1",
	     "east" : __DIR__"wuchang",
]));
set("objects",([
	"/d/mr/npc/murong-fu" : 1,
]));
     "/clone/board/murong_b.c"->foo(); 
	 setup();
}

void init()
{
    object me=this_player();
  
	if( me->query("family/family_name") == "姑苏慕容" 
	&& me->query("mr/addtimes") < 1)
	{
	if(me->query("combat_exp") < 1000000 && me->query("combat_exp") > 500000)
	{       
		me->set("mr/addtimes", 1); 
		me->add("mr_job",300);
		tell_object(me, HIY "\n系统已经自动为您加上三百次的慕容任务。\n" NOR);
		return;
	}
		
	if(me->query("combat_exp") < 2000000 && me->query("combat_exp") > 1000000)
	{      
		me->set("mr/addtimes", 1); 
		me->add("mr_job",500);
		tell_object(me, HIY "\n系统已经自动为您加上五百次的慕容任务。\n" NOR);
		return;
	}
	
	if(me->query("combat_exp") < 3000000 && me->query("combat_exp") > 2000000)
	{
		me->set("mr/addtimes", 1); 
		me->add("mr_job",1000);
		tell_object(me, HIY "\n系统已经自动为您加上一千次的慕容任务。\n" NOR);
		return;
	}
	
	if(me->query("combat_exp") < 4000000 && me->query("combat_exp") > 3000000)
	{
		me->set("mr/addtimes", 1); 
		me->add("mr_job",1500);
		tell_object(me, HIY "\n系统已经自动为您加上一千五百次的慕容任务。\n" NOR);
		return;
	}
	
	if(me->query("combat_exp") > 4000000)
	{
		me->set("mr/addtimes", 1); 
		me->add("mr_job",2000);
		tell_object(me, HIY "\n系统已经自动为您加上二千次的慕容任务。\n" NOR);
		return;
	}
	return;
}
}
