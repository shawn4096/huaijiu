#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(RED"�ż�"NOR, ({ "letter","xin","secret letter" }));
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long","����һ���ż����������ױ����ͣ��ŷ�ĺ���ʵ����ڸ��ź���ӡ����\n");
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
		write("\n����һ���ɴ�����������������ż�������д��\n\n"
		"    ��"HIR+me->query_temp("songxin_where")+HIR"   "+me->query_temp("songxin_target_name")+NOR"�� ������\n\n"NOR);
		if(now_time > time*3/4) write("�������г����ʱ��ȥ���š�\n");
		if(now_time > time/2 && now_time <= time*3/4) write("�Ѿ���ȥһС��ʱ���ˡ�\n");
		if(now_time > time/4 && now_time <= time/2) write("�㻹��һ���ʱ��ȥ���š�\n");
		if(now_time > time/8 && now_time <= time/4) write("���ʱ���Ѿ������ˡ�\n");
		if(now_time > 0 && now_time <= time/8) write("ʱ�佫�������񼴽�ʧ�ܡ�\n");
	}
	else{
	  if(( arg=="letter" || arg=="xin")&&!me->query_temp("dali_songxin")) 
	    write("����һ���ܺ����������ױ����ͣ��ŷ�ĺ���ʵ����ڸ��ź���ӡ����\n");
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
		return notify_fail("����æ���ء�\n");
	if( !arg ) return notify_fail("��Ҫ�͸�˭��\n");
	if(!objectp(target = present(arg, environment(me)))) 
		return notify_fail("��Ҫ�͸�˭��\n");
		
	t_name = target->query("name");
	job_time = me->query_temp("songxin_time");

	if( !living(target) ) 
		return notify_fail("������㣬���ǻ����𣿣�\n");
	if( userp(target) ) 
		return notify_fail("�ٺ٣������ף���\n");
	if( me->query_temp("dali_songxin_late"))
		return notify_fail("�������Ѿ�ʧ���ˣ���������һ���ɡ�\n");
	if( !wizardp(me) && !me->query_temp("dali_join") )
		return notify_fail(t_name+"�����㲻�Ǵ��������ӣ���ô�������������͵��Ÿ��ң�\n");
	if( !me->query_temp("dali_songxin"))
		return notify_fail(t_name+"�������Ǵ���������������Խ�����,Ҫ���͵ģ����ǲ��Ǵӱ������������ģ�\n");
	if (me->query_temp("songxin_areab") != target->query("startroom"))
		return notify_fail(t_name+"��ֵ����㿴������Ƿ��ʹ����ˣ�����ͬ�����˿ɲ���Ŷ��\n");
	if(me->query_temp("songxin_target_name") != t_name)
		return notify_fail(t_name+"��������Ų��Ǹ��ҵģ����ǲ����ʹ��ˣ�\n");

	me->start_busy(2); // hehe, ��ֹ����bug������Ч :) snowman@SJ
	message_vision(HIY"$N����һ�Ѷ�ͷ�ĺ����ӻ����ͳ��Ž���$n˵�������Ƕ���ү�������͸������ţ������պá�\n"NOR, me, target);
	message_vision(HIY "$N�ӹ��ſ��˿������˵�ͷ˵������λ"+RANK_D->query_respect(me)+"�������ˡ�\n"NOR, target, me);
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
		sprintf("%s %s(%s)��%d�����Ž���%d�㾭�飬%d��Ǳ�ܣ����裺%d\n",
			ctime(time())[4..15],
			me->query("name"),
			me->query("id"),
			me->query("dali_job"),
			exp,
			pot,
			me->query_temp("zuji")
		)
	);

	tell_object(me,HIW"�ã�������ɣ��㱻�����ˣ�\n" + 
		       chinese_number(exp) + "��ʵս����\n" +
		       chinese_number(pot) + "��Ǳ��\n"+
		       "��Ϊ������������"+me->query("dali_job")+"�ι�����\n"
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
	message_vision("$N��Ȼ������·�ϲ����ˡ�\n", this_object());  
	destruct(this_object());
}
