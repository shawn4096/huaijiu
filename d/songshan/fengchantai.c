//Room fengchantai.c 封禅台

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"封禅台"NOR);
	set("long", @LONG
封禅台为大麻石所建，每块大石都凿得极是平整，当年帝皇为了祭天
祀福，不知驱使几许石匠，始成此巨构。封禅台下是可以容纳数千人的广
场，登临于此，可以望见大熊峰、小熊峰、双主峰、三尖峰和少林寺所在
的少室山，不禁让人想起杜甫“齐鲁青未了”的绝句。
LONG);
	set("exits", ([ 
	    "southdown" : __DIR__"peitian-fang",
   
	]));
	set("objects", ([ 
		CLASS_D("songshan") + "/zuo" : 1,
	      __DIR__"npc/ssdizi" : 3,
	]));
	set("outdoors", "嵩山");
	set("coor/x",40);
  	set("coor/y",370);
   	set("coor/z",150);
   	setup();
}

int do_enter(string arg)
{
	object me;

	me = this_player();
	if( !arg || arg=="" ) return 0;
	if( arg=="ri" ) {
		if (me->is_busy() || me->is_fighting())
			return notify_fail("你正忙着呢。\n");
		if (me->query("family/family_name")=="嵩山派") {
		       	message("vision",me->name()+"整了整衣服，向观日峰走了过去。\n",environment(me),({me}) );
		       	me->move("/d/songshan/guanrifeng");
		       	message("vision",me->name() + "从封禅台走了过来。\n",environment(me), ({me}) );
		       	return 1;
	   	}
     		return notify_fail("那边太阳好大，你不怕晒黑吗？\n");
	}
}

void init()
{
	add_action("do_enter","guan");
	add_action("do_qs","qi");
}
int do_qs(string arg)
{
	object me,ob;
	int shen,exp,pot;
	me = this_player();
	ob = present("shikuai",me);
	
	if( !arg || arg=="" ) return notify_fail("你要干什么？\n");
	
	if(!ob) return notify_fail("修整需要石料，你要用什么来砌？\n");
	
	if(!me->query_temp("ss_qs/taked")) return notify_fail("你还没去搬石头呢吧？\n");
	
	if(arg=="shikuai"){
		shen = me->query("max_pot")/2 + random(200);
		exp = me->query("max_pot")/2+random(20);
		pot = exp/6+random(exp/10);
		
		me->add("combat_exp",exp);
		if (me->add("potential",pot) > me->query("max_pot"))
			me->set("potential", me->query("max_pot"));
		me->add("shen",-shen);
		
	me->improve_skill("hanbing-zhenqi",me->query("int")*2);
		me->clear_condition("job_busy");
		me->apply_condition("job_busy",2+random(2));
		me->delete_temp("ss_qs");
		destruct(ob);
		message_vision("$N将一块石头砌在封禅台破损的一角上。\n",me);
		tell_object(me,HIW" 你得到了：\n" + 
	    	chinese_number(exp) + "点实战经验\n"+
	    	chinese_number(pot) + "点潜能和\n"+ 
	    	chinese_number(shen)+ "负神\n"NOR);
		return 1;
	}
	else return notify_fail("出现异常错误！请通知巫师！\n");
}
