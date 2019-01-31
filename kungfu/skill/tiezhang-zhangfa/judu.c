// tianlei.c ����--�۶�

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

string perform_name(){ return HBBLU"��    ��"NOR; }
int perform(object me, object target)
{
        int damage,p;
        string msg,dodge_skill;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("���۶���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")))
              return notify_fail("�������ֲ���ʹ�á��۶�����\n");

        if((int)me->query_skill("guiyuan-tunafa", 1) < 100 )
              return notify_fail("��Ĺ�Ԫ���ɷ���δ���ɣ�����ʹ�á��۶�����\n");
                
        if((int)me->query("neili", 1) < 800 )
              return notify_fail("�������������㣬����ʹ�á��۶�����\n");       

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á��۶�����\n");                                                                                 

        if(me->query_temp("tzzf"))
              return notify_fail("������ʹ���Ƶ���\n");

        if((int)me->query_skill("tiezhang-zhangfa", 1) < 120 )
              return notify_fail("��������Ʒ�������죬����ʹ�á��۶�����\n");

        msg = HIB"\n$N΢΢������$n�������Ƴ�һ��,ֻ��һ��������ǰ��ȥ��\n"NOR;

        if (random(me->query("combat_exp", 1)) > target->query("combat_exp", 1)/3){
                damage = me->query_skill("tiezhang-zhangfa",1);
                damage *= 3;
                if (damage > 1000) damage = 1000 + (damage - 1000)/100;
                target->receive_damage("jing", damage);
                target->receive_wound("jing", damage/2);
                target->receive_damage("jingli", damage+me->query_skill("poison",1));
                msg += BLU"$n����ʧ��֮�䣬���㲻����һ�ɺ���ֻ��$n��ü��֮��Ϯȡ��\n"NOR;
                p = (int)target->query("jing")*100/(int)target->query("max_jing");
                msg += "( $n"+eff_status_msg(p)+" )\n";
        }
        else {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
        me->add("neili", -300);
        me->add("jingli", -50);
        me->start_busy(2);
        me->start_perform(4,"���۶���");
        return 1;
}

int help(object me)
{
        write(WHT"\n�����Ʒ����۶�����"NOR"\n");
        write(@HELP
        ������ǧ�����ƹ��ľ���֮һ���������۶�����ʹ�����Ƶ����ж�����Ϯ���Է���
        
        Ҫ��  ���� 800 ���ϣ�      
                ���� 50 ���ϣ�  
                �����Ʒ��ȼ� 120 ���ϣ�
                ��Ԫ���ɷ��ȼ� 120 ���ϣ�    
                �����ޱ�����
HELP
        );
        return 1;
}
