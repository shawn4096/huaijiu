// shuangjue.c It's a "pfm" .
// by Looklove@SJ 2001/2/14 ...情人节

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int b, z;
        object weapon;
        b = me->query_skill("dagou-bang", 1)/2;
        z = me->query_skill("xianglong-zhang", 1)/2;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「棒掌双绝」只能在战斗中对对手使用。\n");

        if(!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "stick")
                return notify_fail("你手里没有棒，无法使用棒掌双绝！\n");

        if( me->query_temp("shuangjue"))
                return notify_fail("你正在使用「棒掌双绝」绝技。\n");
        
        if( me->query_skill("dagou-bang", 1) < 350 )
                return notify_fail("你的打狗棒法还不够娴熟，使不出「棒掌双绝」绝技。\n");

        if( (int)me->query_skill("xianglong-zhang", 1) < 350 )
                return notify_fail("你的降龙掌还未练成，不能使用棒掌双绝！\n");    

        if( me->query_skill_mapped("force") != "huntian-qigong"
          || (int)me->query_skill("huntian-qigong", 1) < 350 )
                return notify_fail("你的混天气功还没有学成，无法使用棒掌双绝！\n");

        if( (int)me->query_skill("force") < 350 )
                return notify_fail("你的内功等级不够，使不出「棒掌双绝」绝技。\n");

        if( me->query_skill_mapped("parry") != "dagou-bang")
                return notify_fail("你的招架功夫不对，无法使用棒掌双绝！\n");
                
        if( me->query_skill_mapped("strike") != "xianglong-zhang" 
         || me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你没有用降龙掌，无法使用棒掌双绝！\n");

        if( (int)me->query("max_neili") < 8000 )
                return notify_fail("你现在内力太弱，使不出「棒掌双绝」。\n");      

        if( (int)me->query("neili") < 2000 )
                return notify_fail("你现在真气太弱，使不出「棒掌双绝」。\n");

        if( me->query("gender")=="女性")
        msg = HIG"$N忽然斜挪一步，眼中灵光一闪，狡捷的笑容让人感觉她要使坏，不由得心生怯意。\n"NOR;
        else msg = HIW"$N招数突变，晃身错步，猛然一声长啸，舞起漫天棒影向$n身上打去！\n"NOR;

        me->start_perform(4,"「棒掌双绝」");
        me->add_temp("apply/attack", b/2); 
        me->add_temp("apply/damage", z/2);
        me->set_temp("shuangjue", 1);

        message_vision(msg, me, target);

        if (target->is_busy()){
                msg = HIR"$n眼前一花，分辨不出$N的招数，只觉头皮发麻，越战越是胆怯。\n"NOR;
                message_vision(msg, me, target);
        }
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->add("jingli", -10); 

        if( me->query("gender")=="女性")
        msg = HIY"$N一声轻啸：“看棒”！$n一惊，却是虚晃。不料$N棒中藏掌，刹那间拍到。\n"NOR;
        else msg = HIY"$N不等棒招用老，回身上步，大喝一声，猛然一掌拍出，端的是干净利落。\n"NOR;
        weapon->unequip(); 
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->add("neili", -100); 
        me->add("jingli", -10);

        weapon->wield();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        me->add("jingli", -10);

        if(random(me->query_skill("dodge")) > target->query_skill("dodge")/2)
        {          
                if( me->query("gender")=="女性")
                msg = HIW"棒影一收，$n只觉得眼花缭乱，只听$N一声娇喝：这个才是真的，看掌!\n"NOR;
                else msg = HIW"只听$N又一声龙吟，前棒刚至，突然换招，力发丹田，挟起掌风向$n拍去。\n"NOR;
                weapon->unequip();
                message_vision(msg, me, target);
                me->add_temp("apply/damage", 50);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                me->add("neili", -100); 
                me->add("jingli", -5);
                
                weapon->wield();
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                me->delete_temp("sj");
                me->add("neili", -100);
                me->add("jingli", -5);
                me->add_temp("apply/damage", -50);
        }

        me->add_temp("apply/attack", -b/2);
        me->add_temp("apply/damage", -z/2);
        me->delete_temp("shuangjue", 1);
        me->start_busy(1+random(2));
        return 1;
}

