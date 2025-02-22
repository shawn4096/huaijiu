#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
       string msg;
       int i;

       if( !me->is_fighting())
            return notify_fail("你只能在战斗种使用诸天化身步。\n");

       if((int)me->query_skill("linji-zhuang",1) < 100 )
            return notify_fail("你的临济十二庄还不够火候，使不出诸天化身步。\n");  

       if((int)me->query_skill("anying-fuxiang",1) < 100 )
            return notify_fail("你的暗影浮香还不够火候，使不出诸天化身步。\n");  

       if((int)me->query("jingli", 1) < 500 )
            return notify_fail("你现在精力不够。\n");

       if((int)me->query("neili", 1) < 500 )
            return notify_fail("你现在内力不够。\n");

       if(me->query_temp("emei/parry"))
            return notify_fail("你正在使用诸天化身步。\n");

       msg = HBYEL"你使出暗影浮香的诸天化身步，身手登时更加灵巧！\n\n"NOR; 

       me->add("neili", -200 + random(100));
       me->add("jingli", -50);
       tell_object(me,msg);
       i = me->query_skill("linji-zhuang", 1)/5;
       me->add_temp("apply/dodge", i);
       me->add_temp("apply/parry",i);
       me->set_temp("emei/parry", i);
       me->start_perform(2,"诸天化身步");
       call_out("remove_effect", 1, me, (int)me->query_skill("force")/3);
       return 1;
}

void remove_effect(object me, int count)
{
       int i;
       if (!me) return;
       if( !me->is_fighting()
        || me->query_skill_mapped("dodge") !="anying-fuxiang" 
        || count < 1){
         i = me->query_temp("emei/parry");
         me->add_temp("apply/dodge", - i);
         me->add_temp("apply/parry", - i);
         me->delete_temp("emei/parry");
         tell_object(me,HIW"你停止了诸天化身步，深深的吸了口气。\n"NOR);
         return;
       }
       call_out("remove_effect", 1 ,me ,count -1);
}
