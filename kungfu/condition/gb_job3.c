#include <ansi.h>

int update_condition(object me, int duration)
{
	if( file_name(environment(me)) == "/d/xiangyang/xuanwumen" 
	&& me->query_temp("gb_job3") ) {
		message_vision("易大彪走了过来。\n"
			"易大彪对$N说道：请随我来。\n", me);
		write( "易大彪带着你混过了蒙古大军的几道岗哨，来到\n"
			+  "中军营前，说到：我非中军士兵，无法入内，以后\n" 
			+  "就看你的了。说完转身走开了。\n" );
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
			message_vision(HIC "$N见敌人越来越多，情知今日难以成功，退意暗生，\n"
				+  "切战且走，总算冲出了包围。\n" NOR, me );
			me->move("/d/xiangyang/xuanwumen.c");
			me->delete_temp("gb_job3");
			me->delete_temp("gb_job3_enter");
			me->unconcious();
			me->set("qi",500);
			me->set("eff_qi",500);
			me->apply_condition("job_busy",10);
		}
		else if(me->query_temp("gb_job3"))
			write(HIY "你时间已过，任务失败。\n" );
		return 0;
	}

	return 1;
}
