// sjsz_time.c  试剑山庄寻宝有效时间计时
// Create By lsxk@hsbbs 2008/6/20

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
       int i;

       if (duration < 1 && strsrch(file_name(environment(me)), "/cmds/leitai/bwdh") >= 0){
           tell_object(me,BLINK + HIC"突然从边上窜出两个彪形大汉，一把抗起你，丢到了城隍庙。你顿时郁闷了半天。\n"NOR);
           me->move("/d/city/chmiao");
           me->clear_condition("killer");
           me->remove_all_enemy();
           me->remove_all_killer();
           if (me->query("no_pk_recover")){
               tell_object(me,BLINK + HIG"您离开了试剑山庄，系统自动恢复了您的洗手状态！\n"NOR);
               me->set("no_pk",me->query("no_pk_recover"));
               me->delete("no_pk_recover");
           }
           return 0;
       }
       me->apply_condition("sjsz_time", duration - 1);
      
       if ( strsrch(file_name(environment(me)), "/cmds/leitai/bwdh") >= 0){
       switch(random(10)){
       case 0:
           me->add("combat_exp",(i=71+random(80)));
           tell_object(me,HIM"你正在试剑山庄中探险，额外获得了"+HIW+chinese_number(i)+HIM+"点经验值奖励!\n"NOR);
           break;
       case 1:
           me->add("max_neili",(i=1+random(1)));
           tell_object(me,HIG"你正在试剑山庄中探险，额外获得了"+HIW+chinese_number(i)+HIG+"点最大内力奖励!\n"NOR);
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
