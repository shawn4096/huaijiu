// leiting �������
// Created by Numa@Sj 19991118

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, damage, p, p1, p2, p0;
        int focus = me->query_temp("ss/focus");
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("�����������ֻ����ս����ʹ�á�\n");
        
        if( (int)me->query_skill("songshan-jian", 1) < 160 )
                return notify_fail("�����ɽ������������죬�޷�ʹ���������������\n");
        if( (int)me->query_skill("hanbing-zhenqi", 1) < 160 )
                return notify_fail("��ĺ��������ȼ����������޷�ʹ���������������\n");
        if (me->query_skill_mapped("force") != "hanbing-zhenqi")
                return notify_fail("��Ŀǰ���ڹ��޷�ʹ���������������\n");

        if (!objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "songshan-jian")
                return notify_fail("���޷�ʹ���������������\n");
        if (me->query_temp("ss/leiting"))
                return notify_fail("���ʹ���꡸�������������Ϣһ�°ɡ�\n"); 
                
        if( (int)me->query("max_neili") < 2500)
                return notify_fail("���������Ϊ̫��޷�ʹ���������������\n");
                
        if( (int)me->query("neili") < 500)
                return notify_fail("����������̫����ʹ�����������������\n");
         me->start_perform(4,"����");
        msg = YEL"\n$N��������������������ƳԱ��˷�ķ���һ�㣬ȫ���������е����ұ�֮�ϣ�ȫ������$n�̳���\n"NOR;
        
        p1 = me->query_skill("sword") + me->query_skill("force");
        p0 = me->query_skill("songshan-jian",1);
        p0 = p0/2 + random(p0/2);
        p0 *= (focus+2)/2;
        p2 = target->query_skill("parry") + target->query_skill("dodge");
        p1 *= me->query("combat_exp")*(focus+1)/1000;
        p2 *= target->query("combat_exp")/1000;
        
        if( p1 + p0 > random(p2/3)+p2/2 )
        {
                msg += CYN"$n������Ǭ��һ�����ͻ�����һײ����ʱ������Ѫ���������\n"NOR;
                damage = (int)me->query_skill("sword") + (int)me->query_skill("force");
                damage = damage*(focus+1);
                if( damage > 3000) damage = 2800 + random(300);
//                me->add_temp("apply/strength", p0);
//              me->add_temp("apply/attack", p0/2);
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                me->add("neili",-damage/3);
                if (wizardp(me))
                        tell_object(me,HIW"damage��"+damage+"��p0��"+p0+"��p1��"+p1+"��p2/2��"+p2/2+"��\n"NOR);
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "����");
                msg += "( $n" + eff_status_msg(p) + " )\n";
//                me->add_temp("apply/strength", -p0);
//              me->add_temp("apply/attack", -p0/2);
        } 
        else
        {
                me->add("neili", -100);
                msg += "ͻȻ֮�䣬��Ӱ���Σ�$n��󻬳����࣬��ʱ�ֻص���ԭ�ء�\n" NOR;
        }
        message_vision(msg, me, target);
       
        me->start_busy(1);
        me->set_temp("ss/leiting",1);
        i = 20 - p0/20;
        if (i<5)    i = 5;
        if (i>5)    i = 10;
        call_out("remove_effect", i, me);
        return 1;
}

void remove_effect(object me)
{
        if(!me) return;
        me->delete_temp("ss/leiting"); 
}
