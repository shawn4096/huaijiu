// sanhuan.c for tjj
// Created and Modified by snowman@SJ 23/02/2001

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIG"��������"NOR; }

int perform(object me, object target)
{
        object weapon;
        int i = me->query_skill("taiji-jian", 1)/5;
        int j = me->query("jiali")/4 + 10;
        
        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("���������¡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(me->query_temp("tjj/lian"))
        	return notify_fail("������ʹ������\n");
        if( (int)me->query_skill("taiji-jian", 1) < 120 )
                return notify_fail("���̫����������̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("sword", 1) < 120 )
                return notify_fail("��Ļ�����������̫ǳ���������ˡ�\n");
      	if((int)me->query_temp("tjj/chan"))
                 return notify_fail("����������ʹ�á������־���\n");

        if( (int)me->query_skill("yinyun-ziqi", 1) < 120 )
                return notify_fail("����ڹ�����̫ǳ���������ˡ�\n");
                
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("�������̫ǳ���������ˡ�\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("��������������������ˡ�\n");
        if (me->query_skill_mapped("force") != "yinyun-ziqi")
                return notify_fail("����ʲôΪ�ڹ�������ʹ���������¡�?\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("��ʹ���ˡ��������¡�ô?\n");
                 
        if( me->query_skill("taiji-jian", 1) > 450 )
        	j += random(j);
        	
        me->add("neili", -200);
        me->add("jingli", -40);
        me->set_temp("tjj/sanhuan", 3); 
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", j);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);        
        me->add_temp("apply/attack", -i);
        me->add_temp("apply/damage", -j);   
        me->start_busy(1);
        me->delete_temp("tjj/sanhuan"); 
        me->start_perform(4, "���������¡�");
        return 1;
}
