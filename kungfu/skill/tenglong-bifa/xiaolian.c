// guifei 小怜横陈
// created by olives@SJ
/*
     蓦见夫人脑袋向着她自己胸口钻落，敌人架颈中的一刀自然落空，她顺势在
地下一个筋斗在教主胯下钻过，握着匕首的右手成拳，轻轻一拳击在教主后心，
只是剑尖向上。倘若当真对敌，这一剑自然插入了敌人背心。韦小宝又大叫一声
：“好！”

*/
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
        int lvl;

        if(!target) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("「小怜横陈」只能在战斗时使用！\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「小怜横陈」只有拜了教主后才能用！\n");

        if(!objectp(weapon=me->query_temp("weapon"))
        || weapon->query("skill_type") != "dagger")
             return notify_fail("你手上没有匕首，如何使用「小怜横陈」。\n");
        
        if((int)(me->query("dex")+me->query_skill("dodge",1)/10) < 30 )
                return notify_fail("你身法不够，使用「小怜横陈」，恐怕会伤到自己！\n");

        if((int)me->query_skill("tenglong-bifa", 1) < 150 )
                return notify_fail("你的腾龙匕法还不够熟练，不能使用「小怜横陈」！\n");

        if((int)me->query_skill("huagu-mianzhang",1) < 150)
                return notify_fail("你的化骨绵掌不够熟练，不能使用「小怜横陈」！\n");

        if(me->query_skill_mapped("strike") != "huagu-mianzhang"
        || me->query_skill_prepared("strike") != "huagu-mianzhang")
                return notify_fail("你现在没有做好准备，无法使用「小怜横陈」！\n");

        
        if(me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("只有使用腾龙匕法时才能使用「小怜横陈」！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("你的毒龙大法功力不足，不能用「小怜横陈」。\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用「小怜横陈」！\n");

        if((int)me->query("neili", 1) < 1500)
                return notify_fail("你现在内力不足，不能使用「小怜横陈」！\n");

        if(me->query("gender") == "男性" )
                return notify_fail("不是女人怎么能使用「小怜横陈」呢！\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法相互抵触，不能使用「小怜横陈」。\n");

        msg = HIR"$N乘$n稍稍走神之机，拼尽全力使出苏夫人不传之绝技－－「小怜横陈」"NOR;
        msg +=MAG "\n$N使出一招「小怜横陈」，脑袋蓦地向自己胸口钻落，顺势在地上一个斛斗，\n从$n胯下钻过，握着兵器的右手成拳向$n后心连捶数下。\n"NOR;
        lvl = me->query_skill("tenglong-bifa",1)/5;
        message_vision(msg,me,target);
        me->receive_damage("jingli",100);
        me->receive_damage("neili",300);
        me->add_temp("apply/attack",lvl*2);
        me->add_temp("apply/damage",lvl);
        me->set_temp("sld/pfm/xiaolian",1);
        COMBAT_D->do_attack(me,target,weapon,3);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip();
                COMBAT_D->do_attack(me,target,0,1);
                weapon->wield();
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me,target,weapon,1);
        if(objectp(target) && me->is_fighting(target))
        {
                if(random(me->query("combat_exp"))>target->query("combat_exp")/2)
                        COMBAT_D->do_attack(me,target,weapon,3);
                else
                        COMBAT_D->do_attack(me,target,weapon,1);
        }
        me->delete_temp("sld/pfm/xiaolian");
        me->add_temp("apply/attack",-lvl*2);
        me->add_temp("apply/damage",-lvl);

        me->start_busy(1+random(2));
        me->start_perform(2+random(2),"「小怜横陈」");
        return 1;
}

