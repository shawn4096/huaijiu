// feijian.c for huashan-jianfa
// Modified by snowman@SJ 20/06/2000
// I dont like jianmang.c
// so changed to feijian.c
// Modified by darken@SJ

#include <ansi.h>

inherit F_SSERVER;

#include <combat_msg.h> 

string *xue_name = ({
"����Ѩ","���Ѩ","����Ѩ","����Ѩ","����Ѩ","�Ϲ�Ѩ","���Ѩ","�ٻ�Ѩ","̫��Ѩ","��ǿѨ","��̨Ѩ"
});

int perform(object me, object target)
{       
        object weapon = me->query_temp("weapon");
        
        if( !target ) target = offensive_target(me);
 
        if( !target || !target->is_fighting(me) )
                return notify_fail("���ɽ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!weapon
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޷�ʹ�á��ɽ����������ˡ�\n");

        if((int)me->query_skill("huashan-jianfa", 1) < 100
         ||(int)me->query_skill("sword", 1) < 100
         ||(int)me->query_str() < 25   
         ||(int)me->query_dex() < 25)  
                return notify_fail("���еĹ��򻹲�����죬����ʹ�á��ɽ�����\n");

        if((int)me->query_skill("zixia-gong", 1) < 100)
                return notify_fail("�����ϼ����Ϊ�������޷����򡸷ɽ����ľ��衣\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("�������̫�����޷�ʹ�ó����ɽ�����\n");
        
        if( (int)me->query("neili") < 700 )
                return notify_fail("�������������\n");

        me->start_perform(5, "�ɽ�");
        me->start_busy(1);
        message_vision(HIC"\n$N���ֽ���һת������"+weapon->query("name")+HIC"ֱ����Խ��Խ�죬��ʱʹ$P��һƬ���������֣�\n"NOR, me, target);
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
                        msg = HIG"\n����ͻȻ�ɳ�һ֧��â������$n��"+name+"��";
                        me->start_perform(5, "��ϼ��â");
        
                        if (random(me->query_skill("dodge")) /10 * damage > target->query_skill("dodge") / 2
                        && me->query("combat_exp") > target->query("combat_exp")/2 ){
                                msg += HIR "���$nһ�����񱻵���Ѩ����ֻ����ȫ������ͨ���������������ܸ��ӣ�\n"NOR; 
                                target->start_busy(3+random(4));

                                if(me->query_skill("huashan-jianfa", 1) > 150
                                && (int)me->query("neili") > 400)
                                        call_out("jm_perform", 2, me , target, weapon, 4);
                        }
                        else {
                                msg += "���ٿ���ޱȣ�\n";
                                name = target->query_skill_mapped("dodge");
                                if( !name ) name = "dodge";
                                msg += SKILL_D(name)->query_dodge_msg(target, 1);
                        }
                        message_vision(msg, me, target);
                        break;
                case 1:
                        me->start_perform(5, "��ϼ�ɽ�");
                        msg = HIM"\nһʱ��$P��ǰ���ⱬ�������������ɳ������������ǣ�ֱ��$p$l����ȥ��\n"NOR;
                        if( random(me->query_str()) / 10 * damage > target->query_str()/2 ){
                                damage *= (int)me->query_skill("sword") + (int)me->query_skill("zixia-gong", 1);
                                damage /= 5;
                                if( damage > 2500 ) damage = 2500;
                                target->receive_damage("qi", damage, me);
                                target->receive_wound("qi", damage/2, me);
                                msg += damage_msg(damage, "����")+
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
                        me->start_perform(4, "�������ɽ�");
                        msg = HIW"\n������$P��ǰ���Ա��ǣ�ɨ��$n�����ǽ��ھ���"HIR"���������ɽ���"HIW"��������������������\n"NOR;
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
                        msg = HIC"\n����$P���н���һ�Σ���$n����δ��ʱ��ֱ��$p�����ȥ��";
                        me->start_perform(5, "��ϼ����");
        
                        if (random(me->query_skill("sword")) /10 * damage > target->query_skill("parry") / 2
                        && me->query("combat_exp") > target->query("combat_exp")/2 ){
                                msg += HIR "���һ���еģ�$nȫ��һ���᲻�����ˣ�\n"NOR; 
                                target->apply_condition("no_enforce", target->query_condition("no_enforce")+2+random(5));
                                target->delete("jiali");
                                if(random(me->query_skill("huashan-jianfa", 1)) > 150
                                && (int)me->query("neili") > 400)
                                        call_out("jm_perform", 2+random(3), me , target, weapon, 3);
                        }
                        else {
                                msg += "���������Ƶ�$p�����ţ�\n";
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

