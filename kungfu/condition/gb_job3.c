#include <ansi.h>

int update_condition(object me, int duration)
{
	if( file_name(environment(me)) == "/d/xiangyang/xuanwumen" 
	&& me->query_temp("gb_job3") ) {
		message_vision("�״�����˹�����\n"
			"�״���$N˵��������������\n", me);
		write( "�״������������ɹŴ���ļ������ڣ�����\n"
			+  "�о�Ӫǰ��˵�����ҷ��о�ʿ�����޷����ڣ��Ժ�\n" 
			+  "�Ϳ�����ˡ�˵��ת���߿��ˡ�\n" );
		me->move("/d/gb/zhongjun1");
		me->set_temp("gb_job3_enter",1);
	}
	
/*	if( duration / 5 * 5 == duration 
		&& !present("zhongjun shiwei",environment(me) )
		&& me->query_temp("gb_job3_enter") )
	{
		new("/d/gb/npc/yuanbing-shiwei")->move(environment(me));
	}
*/	
	
	me->apply_condition("gb_job3", duration-1);

	if( duration < 2 )
	{
		if( me->query_temp("gb_job3_enter") )
		{
			message_vision(HIC "$N������Խ��Խ�࣬��֪�������Գɹ������ⰵ����\n"
				+  "��ս���ߣ��������˰�Χ��\n" NOR, me );
			me->move("/d/xiangyang/xuanwumen.c");
			me->delete_temp("gb_job3");
			me->delete_temp("gb_job3_enter");
			me->unconcious();
			me->set("qi",500);
			me->set("eff_qi",500);
			me->apply_condition("job_busy",10);
		}
		else if(me->query_temp("gb_job3"))
			write(HIY "��ʱ���ѹ�������ʧ�ܡ�\n" );
		return 0;
	}

	return 1;
}
