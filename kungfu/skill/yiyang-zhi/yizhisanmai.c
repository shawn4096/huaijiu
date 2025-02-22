// Modified by snowman@SJ 05/12/2000

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
        
        if( !target ) target = offensive_target(me);

        if( !target 
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("「一指点三脉」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「一指点三脉」！\n");   

        if( (int)me->query_skill("yiyang-zhi", 1) < 160 )
                return notify_fail("你的一阳指还不够娴熟，使不出「一指点三脉」绝技。\n");

        if((int)me->query_skill("force") < 240 ) 
                return notify_fail("你的内功修为还不够，使不出「一指点三脉」绝技。\n");

        if(!me->query_skill("kurong-changong", 1))
          if(me->query_skill("qiantian-yiyang", 1) < 140)
                return notify_fail("以你现在的内功修为还使不出「一指点三脉」。\n");        

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("你现在无法使用「一指点三脉」！\n"); 

        if( (int)me->query("max_neili") < (me->query_skill("force")+1000) )
                return notify_fail("你现在内力太弱，使不出「一指点三脉」。\n");      

        if( (int)me->query("neili") < (me->query_skill("force")+1100) )
                return notify_fail("你现在真气太弱，使不出「一指点三脉」。\n");

        if( (int)me->query("jingli") < (me->query_skill("force")+ 800) )
                return notify_fail("你现在精力太少，使不出「一指点三脉」。\n");

	lev = (int)me->query_skill("yiyang-zhi", 1)/4;
        
        message_vision(RED"\n$N出指舒缓自如，收臂潇洒飘逸，手臂颤动，犹如蜻蜓点水，一指点出，竟分袭三道大脉，快捷无伦！\n"NOR,me,target);
        me->add_temp("apply/finger", lev);
        me->add_temp("apply/attack", lev);       
        me->set_temp("yyz/yz3m",3);
        COMBAT_D->do_attack(me, target, 0, 1);
        if( me->is_fighting(target) && me->query_skill("finger") > 300 ) 
         	COMBAT_D->do_attack(me, target, 0, 3);
        if( me->is_fighting(target) && me->query_skill("finger") > 375 ) 
      		COMBAT_D->do_attack(me, target, 0, 3);

        me->start_busy(1);
        me->delete_temp("yyz/yz3m");
        me->add_temp("apply/finger", -lev);
        me->add_temp("apply/attack", -lev);
        me->add("neili", -400);
        me->add("jingli", -100);
        me->start_perform(3+random(2),"「一指点三脉」");
        return 1;
}
