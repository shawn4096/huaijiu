//by cool 98.6 for dalijob
// dali_songxin.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
	int time = me->query_temp("songxin_time");

	if (duration < 2) {
		if (me->query_temp("dali_songxin")) {
			tell_object(me, HIY "��ʱ���ѹ�������ʧЧ��\n" NOR);
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
		tell_object(me, HIY "�������Щ����ƺ����˸������ˣ�\n" NOR);
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
		tell_object(me,"����Լ�о�������Χ�˹�������!!! \n");
		me->set_temp("songxin_zuji", 1);
		if (random(10)>7) {
			//this is killer kill npc
			tell_object(me, RED "��⣡����Ҫ����!\n" NOR);
			obj = new("/d/dali/job/npc1");
			obj->set("target", me);
			obj->move(environment(me));
			if (random(me->query("combat_exp")) >= 300000) call_out("killer_clone", 1, me);
		} else {
			//this is stealer steal letter
			destruct(obj);
			tell_object(me, RED "���������������һ���´������ã��ű�͵��!\n" NOR);
			obj = new("/d/dali/job/snpc1");
			obj->set("target", me);
			obj->move(environment(me));
			if (me->query("combat_exp") >= 300000) call_out("stealer_clone", 1, me);
		}
	} else tell_object(me, "�����ͳ��������ҵĶ����һ��׷ɱ!\n");   
}

void killer_clone(object me)
{
	object obj;

	if (!me) return;
	tell_object(me, "��⣬�ֳ������˸��ˣ�\n");
	obj = new("/d/dali/job/npc2");
	obj->set("target", me);
	obj->move(environment(me));
}

void stealer_clone(object me)
{
	object obj;

	if (!me) return;
	tell_object(me, "��⣬�ֳ������˸��ˣ�\n");
	obj = new("/d/dali/job/snpc2");
	obj->set("target", me);
	obj->move(environment(me));
}

string query_type(object me)
{
	return "job";
}
