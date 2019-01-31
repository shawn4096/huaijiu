// kuangfeng.c �����
 
#include <ansi.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("dugu-jiujian",1);

        if( !(me->is_fighting() ))
                return notify_fail("������ء�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (!objectp(weapon2 = target->query_temp("weapon")))
                return notify_fail("�Է�û��ʹ�ñ��������޷�ʹ�á�����ء���\n");

        if( skill < 120)
                return notify_fail("��Ķ��¾Ž��ȼ�����, ����ʹ�á�����ء���\n");

        if( me->query("neili") < 500 )
                return notify_fail("��������������޷����á�����ء���\n");
 
        msg = HIC "$Nһ���Ϻȣ�ʹ�����¾Ž�������ء��ƽ�$n������"+weapon->name()+HIC "�ó����ؽ�Ӱ������˿����$n��ȥ��\n";
        message_vision(msg, me, target);
        me->start_perform(4,"�����");
        damage = random(skill)+1;
        ap = me->query_skill("sword") + skill;
        ap = ap/10*ap*ap;
        dp = (int)target->query("combat_exp");
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp)
        {
                if(userp(me))
                        me->add("neili",-300);
                msg = "$n��ʱ����ѹ������������һ�飬����";
                msg += weapon2->name();
                msg += "���ֶ�����\n" NOR;

                target->receive_damage("qi", damage);
                target->add_busy(2);
                weapon2->move(environment(me));
		if (weapon2->query("unique")) destruct(weapon2);
        }
        else
        {
                if(userp(me))
                        me->add("neili",-300);
                msg = "����$n������$N�Ľ�·�����̲�ȡ���ƣ�ʹ$N�ġ�����ء�û�����κ����á�\n"NOR;
                me->start_busy(3);
        }
        message_vision(msg, me, target);

        return 1;
}
