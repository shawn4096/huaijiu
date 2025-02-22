// feijian.c for huashan-jianfa
// Modified by snowman@SJ 20/06/2000
// I dont like jianmang.c
// so changed to feijian.c
// Modified by darken@SJ

#include <ansi.h>

inherit F_SSERVER;

#include <combat_msg.h> 

string *xue_name = ({
"玉堂穴","大横穴","幽门穴","章门穴","晴明穴","紫宫穴","风池穴","百汇穴","太阳穴","长强穴","灵台穴"
});

int perform(object me, object target)
{       
        object weapon = me->query_temp("weapon");
        
        if( !target ) target = offensive_target(me);
 
        if( !target || !target->is_fighting(me) )
                return notify_fail("「飞剑」只能对战斗中的对手使用。\n");

        if (!weapon
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你现在无法使用「飞剑」攻击敌人。\n");

        if((int)me->query_skill("huashan-jianfa", 1) < 100
         ||(int)me->query_skill("sword", 1) < 100
         ||(int)me->query_str() < 25   
         ||(int)me->query_dex() < 25)  
                return notify_fail("你有的功夫还不够娴熟，不会使用「飞剑」。\n");

        if((int)me->query_skill("zixia-gong", 1) < 100)
                return notify_fail("你的紫霞功修为不够，无法领悟「飞剑」的精髓。\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("你的内力太弱，无法使用出「飞剑」！\n");
        
        if( (int)me->query("neili") < 700 )
                return notify_fail("你的真气不够！\n");

        me->start_perform(5, "飞剑");
        me->start_busy(1);
        message_vision(HIC"\n$N右手剑锋一转，手中"+weapon->query("name")+HIC"直斗，越舞越快，顿时使$P被一片剑辉所笼罩！\n"NOR, me, target);
        me->start_call_out( (: call_other, __FILE__, "jm_perform", me , target, weapon, random(3) :), 1+random(4));
        return 1;
}

int jm_perform(object me, object target, object weapon, int pfm)
{
        string name, msg, *limbs;
        int damage = 10;
        
        if( !me || !target || !weapon ) return 0;
        if( !living(me) || !living(target) ) return 0;
        if( environment(me) != environment(target) ) return 0;
        if( !me->is_fighting(target) ) return 0;
        if( me->query_temp("weapon") != weapon) return 0;
        
        if( me->query("combat_exp") > target->query("combat_exp")/2 )
                damage = 20;
        if( me->query("combat_exp") > target->query("combat_exp")/2 * 3 )
                damage = 15;
        if( target->is_busy() ) damage += 10;
        if( pfm > 2 ){
                damage += pfm;
                pfm = random(3)+2;
        }
        me->receive_damage("neili", 200);
        me->receive_damage("jingli", 50);
        switch(pfm){
                case 0:
                        name = xue_name[random(sizeof(xue_name))];  
                        msg = HIG"\n当中突然飞出一支剑芒，奔向$n的"+name+"，";
                        me->start_perform(5, "紫霞剑芒");
        
                        if (random(me->query_skill("dodge")) /10 * damage > target->query_skill("dodge") / 2
                        && me->query("combat_exp") > target->query("combat_exp")/2 ){
                                msg += HIR "结果$n一不留神被点中穴道，只觉得全身气脉通道阻塞，真气立受干挠！\n"NOR; 
                                target->start_busy(3+random(4));

                                if(me->query_skill("huashan-jianfa", 1) > 150
                                && (int)me->query("neili") > 400)
                                        call_out("jm_perform", 2, me , target, weapon, 4);
                        }
                        else {
                                msg += "其速快绝无比！\n";
                                name = target->query_skill_mapped("dodge");
                                if( !name ) name = "dodge";
                                msg += SKILL_D(name)->query_dodge_msg(target, 1);
                        }
                        message_vision(msg, me, target);
                        break;
                case 1:
                        me->start_perform(5, "紫霞飞剑");
                        msg = HIM"\n一时间$P身前剑光爆闪，数道光亮飞出，如天外流星，直向$p$l处刺去！\n"NOR;
                        if( random(me->query_str()) / 10 * damage > target->query_str()/2 ){
                                damage *= (int)me->query_skill("sword") + (int)me->query_skill("zixia-gong", 1);
                                damage /= 5;
                                if( damage > 2500 ) damage = 2500;
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage/2, me);
                                msg += damage_msg(damage, "刺伤")+
                                "( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n";
                                if(me->query_skill("huashan-jianfa", 1) > 250
                                && (int)me->query("neili") > 400)
                                        call_out("jm_perform", 2, me , target, weapon, 4);
                        }

                        else { 
                                name = target->query_skill_mapped("dodge");
                                if( !name ) name = "dodge";
                                msg += SKILL_D(name)->query_dodge_msg(target, 1);
                        }
                        limbs = target->query("limbs");
                        msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                        msg = replace_string(msg, "$w", weapon->name()); 
                        message_vision(msg, me, target);
                        break;
                case 2:
                        me->start_perform(4, "夺命三仙剑");
                        msg = HIW"\n紧跟着$P身前剑辉爆涨，扫向$n，正是剑宗绝技"HIR"「夺命三仙剑」"HIW"，连环数剑奋力击出！\n"NOR;
                        message_vision(msg, me, target);
                        me->add_temp("apply/attack", me->query_int()+damage);
                        me->add_temp("apply/damage", me->query_int()+damage);
                        COMBAT_D->do_attack(me, target, weapon, 1);
                        if( me->is_fighting(target) )
                                COMBAT_D->do_attack(me, target, weapon, 1);
                        if( me->is_fighting(target) )
                                COMBAT_D->do_attack(me, target, weapon, 1);
                        me->add_temp("apply/attack", -(me->query_int()+damage));
                        me->add_temp("apply/damage", -(me->query_int()+damage));
                        me->start_busy(1);
                        if(me->query_skill("huashan-jianfa", 1) > 350
                        && (int)me->query("neili") > 400)
                                call_out("jm_perform", 2, me , target, weapon, 4);
                        break;
                case 3:
                        msg = HIC"\n当中$P手中剑光一晃，在$n惊魂未定时，直奔$p丹田而去，";
                        me->start_perform(5, "紫霞剑气");
        
                        if (random(me->query_skill("sword")) /10 * damage > target->query_skill("parry") / 2
                        && me->query("combat_exp") > target->query("combat_exp")/2 ){
                                msg += HIR "结果一击中的，$n全身一震，提不起劲来了！\n"NOR; 
                                target->apply_condition("no_enforce", target->query_condition("no_enforce")+2+random(5));
                                target->delete("jiali");
                                if(random(me->query_skill("huashan-jianfa", 1)) > 150
                                && (int)me->query("neili") > 400)
                                        call_out("jm_perform", 2+random(3), me , target, weapon, 3);
                        }
                        else {
                                msg += "看来是想破掉$p的气门！\n";
                                name = target->query_skill_mapped("dodge");
                                if( !name ) name = "dodge";
                                msg += SKILL_D(name)->query_dodge_msg(target, 1);
                        }
                        message_vision(msg, me, target);
                        break;
                default: break;
        }
        
        return 1;
}

