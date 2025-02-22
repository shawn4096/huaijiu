#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(RED"信件"NOR, ({ "letter","xin","secret letter" }));
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "封");
		set("long","这是一封信件，镇南王亲笔手谕，信封的很严实，封口盖着红漆印戳。\n");
		set("value", 0);
		set("material", "paper");
		set("no_drop",1);
	 }
}

void init()
{	
	call_out("dest",random(200)+1200);
	add_action("do_send", "songxin");
	add_action("do_look", "kan");
	add_action("do_look", "chakan");
}

int do_look(string arg)
{
	int now_time, time;
	object me;

	me = this_player();
	now_time = me->query_condition("dali_songxin"); 
	time = me->query_temp("songxin_time");

	if(!arg) return 0;
	if((arg=="letter"||arg=="xin")
	 && me->query_temp("dali_songxin")) {
		write("\n这是一封由大理国镇南王发出的信件，上面写着\n\n"
		"    「"HIR+me->query_temp("songxin_where")+HIR"   "+me->query_temp("songxin_target_name")+NOR"」 亲启。\n\n"NOR);
		if(now_time > time*3/4) write("你现在有充足的时间去送信。\n");
		if(now_time > time/2 && now_time <= time*3/4) write("已经过去一小半时间了。\n");
		if(now_time > time/4 && now_time <= time/2) write("你还有一半的时间去送信。\n");
		if(now_time > time/8 && now_time <= time/4) write("你的时间已经不多了。\n");
		if(now_time > 0 && now_time <= time/8) write("时间将至，任务即将失败。\n");
	}
	else{
	  if(( arg=="letter" || arg=="xin")&&!me->query_temp("dali_songxin")) 
	    write("这是一封密函，镇南王亲笔手谕，信封的很严实，封口盖着红漆印戳。\n");
	}
	return 1;
}

int do_send(string arg)
{
	int exp,pot,job_time,i;
	object me,target;
	string t_name;
	
	me=this_player();
	if( me->is_busy() || me->is_fighting() ) 
		return notify_fail("你正忙着呢。\n");
	if( !arg ) return notify_fail("你要送给谁？\n");
	if(!objectp(target = present(arg, environment(me)))) 
		return notify_fail("你要送给谁？\n");
		
	t_name = target->query("name");
	job_time = me->query_temp("songxin_time");

	if( !living(target) ) 
		return notify_fail("看清楚点，那是活人吗？！\n");
	if( userp(target) ) 
		return notify_fail("嘿嘿，想作弊？！\n");
	if( me->query_temp("dali_songxin_late"))
		return notify_fail("你任务已经失败了，重新再领一个吧。\n");
	if( !wizardp(me) && !me->query_temp("dali_join") )
		return notify_fail(t_name+"道：你不是大理国的随从，怎么会送镇南王手谕的信给我？\n");
	if( !me->query_temp("dali_songxin"))
		return notify_fail(t_name+"道：这是大理国镇南王府亲自交给你,要你送的？你是不是从别人那里抢来的？\n");
	if (me->query_temp("songxin_areab") != target->query("startroom"))
		return notify_fail(t_name+"奇怪道：你看清楚，是否送错人了，和我同名的人可不少哦。\n");
	if(me->query_temp("songxin_target_name") != t_name)
		return notify_fail(t_name+"道：这封信不是给我的，你是不是送错了？\n");

	me->start_busy(2); // hehe, 防止利用bug，简单有效 :) snowman@SJ
	message_vision(HIY"$N擦了一把额头的汗，从怀中掏出信交给$n说道，这是段王爷让在下送给您的信，请您收好。\n"NOR, me, target);
	message_vision(HIY "$N接过信看了看，点了点头说道：这位"+RANK_D->query_respect(me)+"辛苦你了。\n"NOR, target, me);
	if (target->query("no_quest"))
		destruct(target);
	if (!me->query_temp("zuji")) 
	   exp=(4+random(6))* 10 + job_time/8;
	else
	   exp=(7+random(7))* 25 + job_time/3;

	if(exp > 350) exp=300+random(50);
	pot = exp/5 + random(exp/6);
	me->add("potential",pot);
	if(me->query("potential") > me->query("max_pot")) 
		me->set("potential",me->query("max_pot"));
	me->add("combat_exp",exp);
	me->add("dali_job",1);
	if(!me->query_temp("multi_login"))
		me->add("balance", (1+random(2))*10000);
	log_file( "job/dali_songxin",
		sprintf("%s %s(%s)第%d次送信奖励%d点经验，%d点潜能，受阻：%d\n",
			ctime(time())[4..15],
			me->query("name"),
			me->query("id"),
			me->query("dali_job"),
			exp,
			pot,
			me->query_temp("zuji")
		)
	);

	tell_object(me,HIW"好！任务完成，你被奖励了：\n" + 
		       chinese_number(exp) + "点实战经验\n" +
		       chinese_number(pot) + "点潜能\n"+
		       "你为镇南王府做了"+me->query("dali_job")+"次工作。\n"
		       NOR);
	i = job_time - me->query_condition("dali_songxin");
	if ( i > 8 )
		i = 8;
	 me->apply_condition("job_busy", 9-i);
	me->apply_condition("dali_songxin", exp/50 + random(7));
	me->delete_temp("dali_songxin");
	me->delete_temp("songxin_time");
	me->delete_temp("songxin_area");
	me->delete_temp("songxin_target_name"); 
	me->delete_temp("songxin_where");  
	me->delete_temp("letter_steal"); 
	me->delete_temp("zuji");
	me->set_temp("songxin_ok",1);
	me->delete_temp("songxin_zuji");     
	destruct(this_object());
	return 1;
}

void dest()
{
	message_vision("$N忽然掉落在路上不见了。\n", this_object());  
	destruct(this_object());
}
