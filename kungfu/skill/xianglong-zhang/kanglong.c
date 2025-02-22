// 亢龙有悔
// by snowman@SJ 16/10/99

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int kanglong_attack(object me);
int perform(object me)
{
        if( !me->is_fighting())
                return notify_fail("「亢龙有悔」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「亢龙有悔」！\n");

        if( (int)me->query_skill("xianglong-zhang", 1) < 200 )
                return notify_fail("你的降龙十八掌还不够娴熟，使不出「亢龙有悔」绝技。\n");
  
        if( (int)me->query_skill("huntian-qigong", 1) < 180 )
                return notify_fail("你的混天气功等级还不够，使不出「亢龙有悔」绝技。\n");
  
if(me->query_temp("htqg/powerup"))
return notify_fail("你正在使用混天气功。\n");
        if (me->query_skill_mapped("force") != "huntian-qigong")
                return notify_fail("你所使用的内功不对。\n");
  
        if( (int)me->query_skill("force") < 270 )
                return notify_fail("你的内功等级不够，不能使用「亢龙有悔」。\n");

        if( (int)me->query_str() < 40 )
                return notify_fail("你的膂力还不够强劲，使不出「亢龙有悔」来。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang"
         || me->query_skill_mapped("strike") != "xianglong-zhang"
         || me->query_skill_mapped("parry") != "xianglong-zhang")
                return notify_fail("你现在无法使用「亢龙有悔」！\n");                                                                                 

        if((int)me->query("max_neili") < 4000)
                return notify_fail("你现在内力太弱，使不出「亢龙有悔」。\n");      

        if((int)me->query("neili") < 1500 )
                return notify_fail("你现在真气太弱，使不出「亢龙有悔」。\n");

        if((int)me->query_temp("xlz/xiao") ) 
                return notify_fail("你已经开始了降龙啸。\n");

        if(!me->query("xlz/hang"))
                return notify_fail("你所学的第一招就是「亢龙有悔」，那是降龙掌中威力最小的一招。\n");
                
        tell_object(me, HIC"\n你缓缓将双掌提到胸前，内息在体内重重运转，越来越快，表面上却看不出任何动静...\n\n"NOR);

        me->start_busy(1+random(2));
        me->start_perform(10, "「亢龙有悔」");
        me->start_call_out( (: call_other, __FILE__, "kanglong_attack", me :), 2+random(4));
        return 1;
}

int kanglong_attack(object me)
{
        object target;
        int i;
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !living(target)
         || !me->is_fighting(target) 
         || environment(target)!=environment(me)){
                write("「亢龙有悔」只能在战斗中对对手使用。\n");
                return 0;
        }
        
        if( (int)me->query("neili") < 1500 ){
                write("你现在真气太弱，使不出「亢龙有悔」。\n");
                return 0;
        }
        if( (int)me->query("jingli") < 1000 ){
                write("你现在精力太弱，使不出「亢龙有悔」。\n");
                return 0;
        }

        if (me->query_skill_mapped("force") != "huntian-qigong"){
                write("你所使用的内功不对。\n");
                return 0;
        }
        
        if (me->query_skill_prepared("strike") != "xianglong-zhang"
         || me->query_skill_mapped("strike") != "xianglong-zhang"
         || me->query_skill_mapped("parry") != "xianglong-zhang"
         || me->query_temp("weapon")){
                write("你现在无法使用「亢龙有悔」！\n");                                                                                 
                return 0;
        }

        if((int)me->query_temp("xlz/xiao") ) 
                return notify_fail("你已经开始了降龙啸。\n");
       
       i = me->query_skill("xianglong-zhang", 1)*4/10;
        
if(me->query_temp("bishen_target"))
target->set_temp("xlz/hanglong",1);
else
        me->set_temp("xlz/hanglong", 1);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/strength", i);
        me->add_temp("apply/damage", i/2);
        me->add_temp("apply/strike", i/2);
        
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
         
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/strength", -i);
        me->add_temp("apply/damage", -i/2);
        me->add_temp("apply/strike", -i/2);
        
        me->receive_damage("neili", 1400);
        me->receive_damage("jingli", 200);
        me->start_perform(4,"「亢龙有悔」");
        return 1;
}
