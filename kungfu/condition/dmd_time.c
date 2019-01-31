// dmd_time.c  勇闯夺命岛有效时间计时
// Create By ilovemin@书剑怀旧 2013/8/15

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
       int i;

       if (duration < 1){
           tell_object(me,BLINK + HIC"你在岛上转悠半天，一无所获，心中不犹萌生退意。顺着原路返回，你搭乘快船回到了渡口。\n"NOR);
           me->move("/d/foshan/dukou");
           me->delete_temp("marks/勇闯夺命岛3");
           me->delete_temp("marks/勇闯夺命岛4");
           me->delete_temp("marks/陷阱");
           me->delete_temp("dmd/done");
           me->remove_all_enemy();
           me->remove_all_killer();
           return 0;
       }
       me->apply_condition("dmd_time", duration - 1);
      
       if ( strsrch(file_name(environment(me)), "/cmds/leitai/dmd") >= 0){
       switch(random(10)){
       case 0:
           me->add("combat_exp",(i=71+random(80)));
           tell_object(me,HIM"你在钓鱼岛上清剿倭寇，额外获得了"+HIW+chinese_number(i)+HIM+"点经验值奖励!\n"NOR);
           break;
       case 1:
           me->add("max_neili",(i=1+random(1)));
           tell_object(me,HIG"你在钓鱼岛上清剿倭寇，额外获得了"+HIW+chinese_number(i)+HIG+"点最大内力奖励!\n"NOR);
           break;
       default:
           break;
       }
     }

	return 1;
}

string query_type(object me)
{
       return "quest";
}
