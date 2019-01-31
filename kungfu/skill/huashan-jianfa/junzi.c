#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me, int amount);
int perform(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("�����ӽ�����ֻ����ս����ʹ�á�\n");

        if((int)me->query_skill("zixia-gong", 1) < 140 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á����ӽ�������\n");
    
        if ((int)me->query_skill("huashan-jianfa", 1) < 140 )
                return notify_fail("��Ļ�ɽ����������죬�����������ӡ����ӽ�������\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("parry") != "huashan-jianfa"
         || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޷�ʹ�á����ӽ�����������˺�����\n");
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("����������̫��������ʹ�á����ӽ�������\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á����ӽ�������\n");

        if ((int)me->query_temp("hsj_junzi"))
                return notify_fail("������ʹ�á����ӽ�����������\n"); 

        if ((int)me->query_temp("hsj_shunv"))
                return notify_fail("������ʹ�á���Ů������������\n"); 
    
        if ( (int)me->query_temp("hsj_xiyi") ) 
                return notify_fail("������ʹ�á����ӽ�������\n");

    
        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("����ڹ������޷�ʹ�á����ӽ�������\n");

        message_vision(HIC "$N��ʱһ����ȣ�����"+weapon->name()+HIC"����һ��,ʹ����ɽ���ڵմ��ľ��ӽ�����\n"+
                           "��ʱ����������Ԧ����Ҫּ���ӵ����쾡�¡���ϼ�������߶�֮��"+weapon->name()+HIC"������������������������ʱ������\n"NOR, me);
        me->start_perform(8,"�����ӽ���");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("huashan-jianfa", 1)/8;
        me->add_temp("apply/damage",  skill*4);
        me->set_temp("hsj_junzi", skill);

        me->start_call_out( (: call_other, __FILE__, "check_fight", me, skill, weapon :), 1);
        return 1;
}

void check_fight(object me, int amount, object weapon)
{  
        object wep;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if(!me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep
         || weapon != wep )
           remove_effect(me, amount);
        else call_out("check_fight", 1, me, amount, weapon);
}

private int remove_effect(object me, int amount)
{         
        int skill;
        skill = me->query_temp("hsj_junzi");
 
        me->add_temp("apply/damage",  -skill*4);
        me->delete_temp("hsj_junzi");
        if(living(me) && !me->is_ghost())
           message_vision(HIW"һ�׾��ӽ����ݱϣ�$N������ʽ,���ӽ����Ľ���Ҳ������ʧ��\n"NOR, me);
        return 0;
}
