//by cool 98.6 for dalijob
// dali_songxin.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
	int time = me->query_temp("songxin_time");

	if (duration < 2) {
		if (me->query_temp("dali_songxin")) {
			tell_object(me, HIY "你时间已过，任务失效！\n" NOR);
			if (me->query("dali_job") > 0) me->add("dali_job", -1);
		}
		me->delete_temp("dali_songxin");
		me->delete_temp("songxin_name");
		me->delete_temp("songxin_zuji");
		me->delete_temp("songxin_target_name");
		me->delete_temp("letter_steal");
		me->delete_temp("zuji");
		me->set_temp("dali_songxin_late",1);
		if(present("secret letter", me)) destruct(present("secret letter", me));
		return 0;
	}

	if( duration >= time/7 && present("secret letter", me) && living(me)
	&& duration <= time * 9/10 && !me->query_temp("songxin_zuji") && random(10) > 3
	&& interactive(me) && !environment(me)->query("no_fight")) {
		tell_object(me, HIY "你觉得有些不妙，似乎被人跟踪上了！\n" NOR);
		me->add_busy(1);
		call_out("zuji", 1, me);    
	}

	me->apply_condition("dali_songxin", duration - 1);
	return 1;
}

void zuji(object me)
{
	object obj;

	if (!me) return;
	obj = present("secret letter", me);
	if (obj) {
		tell_object(me,"你隐约感觉到有人围了过来。。!!! \n");
		me->set_temp("songxin_zuji", 1);
		if (random(10)>7) {
			//this is killer kill npc
			tell_object(me, RED "糟糕！有人要抢信!\n" NOR);
			obj = new("/d/dali/job/npc1");
			obj->set("target", me);
			obj->move(environment(me));
			if (random(me->query("combat_exp")) >= 300000) call_out("killer_clone", 1, me);
		} else {
			//this is stealer steal letter
			destruct(obj);
			tell_object(me, RED "你紧张起来，不由一摸衣袋，不好！信被偷了!\n" NOR);
			obj = new("/d/dali/job/snpc1");
			obj->set("target", me);
			obj->move(environment(me));
			if (me->query("combat_exp") >= 300000) call_out("stealer_clone", 1, me);
		}
	} else tell_object(me, "信已送出，你庆幸的躲过了一次追杀!\n");   
}

void killer_clone(object me)
{
	object obj;

	if (!me) return;
	tell_object(me, "糟糕，又冲上来了个人！\n");
	obj = new("/d/dali/job/npc2");
	obj->set("target", me);
	obj->move(environment(me));
}

void stealer_clone(object me)
{
	object obj;

	if (!me) return;
	tell_object(me, "糟糕，又冲上来了个人！\n");
	obj = new("/d/dali/job/snpc2");
	obj->set("target", me);
	obj->move(environment(me));
}

string query_type(object me)
{
	return "job";
}
