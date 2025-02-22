// sanwu.c 三无三不手
// By River@SJ 02/16/2001

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform3(object me,object target);
int perform2(object me,object target);

int perform(object me, object target)
{       
        string msg, dodge_skill;
        int i, damage, ap, dp;
        object weapon;
        
        if( !me->query("gmsanwu")) return notify_fail("你还不会「三无三不手」这项绝技。\n");
        if( !target ) target = offensive_target(me);
 
        if( !target 
         || !target->is_character()
         || !me->is_fighting(target))
                return notify_fail("「三无三不手」只能在战斗中使用。\n");

        if( !living(target))
                return notify_fail("对方已经晕过去了。\n");
                
        if( !objectp( weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "whip" )
                return notify_fail("你装备的武器不对，无法施展「三无三不手」。\n");

        if( (int)me->query_skill("yinsuo-jinling", 1) < 120 
         || (int)me->query_skill("meinu-quanfa", 1) < 120 
         || (int)me->query_dex() < 28)
                return notify_fail("你有的功夫还不够娴熟，不会使用「三无三不手」。\n");

        if(me->query_skill("yunu-xinjing", 1) < 120)
                return notify_fail("以你现在的内功修为还使不出「三无三不手」。\n");        
         
        if(me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("你所使用的内功不对。\n");

        if (me->query_skill_prepared("cuff") != "meinu-quanfa" 
         || me->query_skill_mapped("cuff") != "meinu-quanfa"
         || me->query_skill_mapped("whip") != "yinsuo-jinling" )
                return notify_fail("你现在无法使用「三无三不手」进行攻击。\n");

        if (me->query_skill_mapped("parry") != "yinsuo-jinling")
                return notify_fail("你所使用的招架不对。\n");

        if((int)me->query("max_neili") < 1300 )
                return notify_fail("你的内力修为太弱，不能使用「三无三不手」！\n");

        if((int)me->query("neili") < 800 )
                return notify_fail("你的真气不够！\n");
        
        if( target->query_temp("sanwu/wukong")
         || target->query_temp("sanwu/wusuo"))
                return notify_fail( target->name()+"已被你的三无三不手所伤，你可以放胆攻击了。\n");
                       
        me->start_perform(4, "三无三不手");

        msg = HIW"突然间只见鞭影幌动，身前身后都是"+weapon->query("name")+HIW"的影子。$N这一招「无孔不入」，乃是向$n周身\n"+
                 "百骸进攻，虽是一招，其实千头万绪，一招之中包含了数十招，竟是同时点$n全身各处大穴。\n"NOR;

        ap = (int)me->query("combat_exp") * me->query_per();
        dp = (int)target->query("combat_exp")* target->query_per();

        if( random(ap) > dp /2 ){
                damage = (int)me->query_skill("yinsuo-jinling", 1);
                damage *= 3;
                if( damage > 2000 ) damage = 2000;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                target->set_temp("sanwu/wukong", 1);
                me->add("neili", - 200);
                msg += damage_msg(damage, "卷伤")+
                "( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
                i = me->query_skill("yinsuo-jinling", 1) / 15;
                call_out("perform_bonus", 1, me, target, i);
        }
        else {
                me->add("neili", -100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }        
        message_vision(msg, me, target);
        if( me->query_skill("meinu-quanfa", 1) >= 140 
         && me->query_skill("yinsuo-jinling", 1) >= 140
         && me->query("neili") > 800 )
         perform2(me, target);
        return 1;
}

int perform2(object me, object target)
{
        int i,ap,dp;
        string msg,dodge_skill;
        
        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) ){
               tell_object(me, "你正要再发一招，却发现对手已经不用打了。\n");
               return 1;
        }

        ap = (int)me->query("combat_exp") * me->query_per();
        dp = (int)target->query("combat_exp")* target->query_per();             
        i = me->query_skill("meinu-quanfa", 1);

        msg = HIW"\n$N跟着一招「无所不至」，这一招点的是$n周身诸处偏门穴道。\n"NOR;
        if( random(ap) > dp/2 ){
                msg += HIR"$n躲闪不及，周身诸处的偏门穴道尽数被点中，全身竟然提不起一丝力气！\n"NOR;
                target->add_temp("apply/attack", -i/6);
                target->add_temp("apply/damage", -i/6);
                target->add_temp("apply/defense", -i/6);
                if( random(2))
                   target->apply_condition("no_exert", 2);
                else  
                   target->apply_condition("no_perform", 2);
                target->set_temp("sanwu/wusuo", i/6);
                call_out("check_fight", 1, me, target, i/20);
                me->add("neili", -200);
        }
        else{
                me->add("neili", - 100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
        if( me->query_skill("meinu-quanfa", 1) >= 160
         && me->query_skill("yinsuo-jinling", 1) >=160
         && me->query("neili") > 800 )
         perform3(me, target);
        return 1;
}

int perform3(object me, object target)
{
        object weapon;
        int i;

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) ){
               tell_object(me,"你正要再发一招，却发现对手已经不用打了。\n");
               return 1;
        }

        weapon = me->query_temp("weapon");

        i = me->query_skill("meinu-quanfa",1);
        i += me->query_skill("yinsuo-jinling", 1);
        i /= 10;

        message_vision(HIW"\n$N的第三手「无所不为」立即使出，这一招不再点穴，专打眼睛、咽喉、小腹、下阴等人身诸般\n"+
                          "柔软之处，是以叫作「无所不为」，阴狠毒辣。\n"NOR, me, target);

        if( !target->query_temp("sanwu/wusuo")){
                me->add_temp("apply/attack", i);
                me->add_temp("apply/whip", i);
                me->set_temp("sanwu/buwei", i);
        }

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        weapon->unequip(); 
        if (present(target,environment(me)) && me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        if (present(target,environment(me)) && me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        weapon->wield();

        if( me->query_temp("sanwu/buwei")){
                me->add_temp("apply/attack", -i);
                me->add_temp("apply/whip", -i);
                me->delete_temp("sanwu/buwei");
        }
        me->add("neili", -200);
        me->add("jingli", -100);
        me->start_perform(4, "三无三不手");
        return 1;
}

void check_fight(object me,object target,int amount)
{        
        int j;
        if( !target ) return;
        if( !me
         || !me->is_fighting(target)
         || amount < 1){
              j = target->query_temp("sanwu/wusuo");
              target->add_temp("apply/attack", j);
              target->add_temp("apply/damage", j);
              target->add_temp("apply/defense", j); 
              target->delete_temp("sanwu/wusuo");
              message_vision(HIW"\n$n穴道已解，精神不由为之一振。\n"NOR, me, target);
              return;
        }
        call_out("check_fight", 1, me, target, amount -1);
}

void perform_bonus(object me,object target,int amount)
{
        int j;
        object weapon;
        
        if( !target ) return;
        if( me
         && me->is_fighting(target)
         && me->query_skill_mapped("whip") =="yinsuo-jinling"
         && me->query_skill_mapped("cuff") =="meinu-quanfa"
         && me->query_skill_prepared("cuff") == "meinu-quanfa"
         && environment(me) == environment(target)
         && amount > 0){
                j = me->query_skill("yinsuo-jinling", 1);
                j += me->query_skill("meinu-quanfa", 1);
                weapon = me->query_temp("weapon");
                switch(random(4)){
                        case 0:
                              message_vision(HIR"\n$n只觉得全身周遭穴道受阻，如针刺般绞痛。\n"NOR,me,target);
                              target->receive_damage("jing", j);
                              target->receive_wound("jing", j);
                              break;
                        case 1:
                              message_vision(HIR"\n$n只觉得全身周遭穴道受阻，不由精神恍惚，只觉得内劲无法控制。\n"NOR,me,target);
                              target->add("neili", -j*3);
                              if(target->query("neili") < 0) target->set("neili", 0);
                              target->add("jingli", -j);
                              break;                          
                        case 2:
                              message_vision(HIR"\n$n只觉得全身周遭穴道受阻，身形不由一滞，行动不便。\n"NOR,me,target);
                              if(!target->is_busy())
                              target->start_busy(2+random(3));
                              break;
                        case 3:
                              message_vision(HIR"\n$n只觉得全身周遭穴道受阻，$N趁机连攻数招。\n"NOR,me, target);
                              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                              if (weapon) weapon->unequip(); 
                              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                              if (weapon) weapon->wield();
                              break;
                }
                me->start_perform(3, "三无三不手");
                call_out("perform_bonus", 3, me, target, amount - 3);
        }
        else {
                target->delete_temp("sanwu/wukong");
                return;
        }
}
