// renmu-daofa 燃木刀法
// by snowman@SJ 05/12/1999

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「焚我」攻击只能对战斗中的对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "blade"
           || me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("你现在无法使出「焚我」绝技！\n");

        if (weapon->query("sharpness") > 3)
                return notify_fail("你手中之刀已是锋利之极，使用「焚我」绝技没有什么作用！\n");

        if (weapon->query("unique"))
                return notify_fail("你手中之刀已是锋利之极，使用「焚我」绝技没有什么作用！\n");
                
        if(me->query_skill("ranmu-daofa", 1) < 150 )
                return notify_fail("你的燃木刀法火候不够，使不出「焚我」绝技。\n");

        if(me->query_skill("blade", 1) < 150 )
                return notify_fail("你的基本功还不够娴熟，使不出「焚我」绝技。\n");

        if( (int)me->query_skill("yijin-jing", 1) < 120 )
                return notify_fail("你的易筋经等级不够，使不出「焚我」绝技。\n");

        if( (int)me->query_str() < 34)
                return notify_fail("你的膂力还不够强劲，使不出「焚我」绝技。\n");

        if( (int)me->query_int() < 30)
                return notify_fail("没有大智慧大般若，是使不出「焚我」绝技的。\n");
 
        if ( me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("没有易筋经作为根基，是无法使出「焚我」绝技的！\n"); 

        if(me->query_temp("ranmu")) 
                return notify_fail("你现在正在使用「焚心」绝技。\n"); 

        if (me->query_temp("fumo"))
                return notify_fail("你现在正在使用「金刚伏魔」神功。\n"); 

        if (me->query("max_neili") < 1000)
                return notify_fail("你的内力修为不够。\n");

        if (me->query("neili") < 650)
                return notify_fail("你的内力不够。\n");

        if (me->query("jingli") < 200)
                return notify_fail("你的精力不够。\n");

        me->add("neili", -600);
        me->add("jingli", -150);        

//fenwo's damage depends on how many times u pfmd       

        i = me->query("fenwo");
        if (i > me->query_skill("blade")) i = me->query_skill("blade");
	
//and it will not be over ur enable blade skill

	me->add_temp("apply/damage",i);
	me->add_temp("apply/attack",i/2);
        me->set_temp("fenwo_hit", 1);
        
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
        
        weapon->add("fenwo", 1);
        if (weapon 
        && !weapon->query("unique")
        && weapon->query("rigidity") < 2
        && weapon->query("fenwo") >= (3+weapon->query("rigidity"))) {
           	message_vision(HIY"\n只听“咔咔”几声，$N手中的$n"HIY"在熊熊火焰中裂成了碎片！\n"NOR,me,weapon);
           	weapon->unequip();
           	weapon->move(environment(me));
           	weapon->set("name", "碎裂的" + weapon->query("name"));
           	weapon->set("value", 49);
           	weapon->set("weapon_prop", 0);
           	me->reset_action();
        }
        me->add_temp("apply/damage", -i);
        me->add_temp("apply/attack", -i/2);
        me->delete_temp("fenwo_hit");
       me->start_busy(1);
         me->start_perform(3,"焚我");
        me->add("fenwo", 1);
        return 1;
}
