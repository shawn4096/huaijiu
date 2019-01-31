#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me, int amount);
int perform(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("��ϣ�Ľ�����ֻ����ս����ʹ�á�\n");

        if((int)me->query_skill("zixia-gong", 1) < 120 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�ϣ�Ľ�������\n");
    
        if ((int)me->query_skill("huashan-jianfa", 1) < 120 )
                return notify_fail("��Ļ�ɽ����������죬�����������ӡ�ϣ�Ľ�������\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "huashan-jianfa"
         || me->query_skill_mapped("parry") != "huashan-jianfa")
                return notify_fail("�������޷�ʹ�á�ϣ�Ľ���������߷�������\n");
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("����������̫��������ʹ�á�ϣ�Ľ�������\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á�ϣ�Ľ�������\n");

        if ((int)me->query_temp("hsj_junzi"))
                return notify_fail("������ʹ�á����ӽ�����������\n"); 

        if ((int)me->query_temp("hsj_shunv"))
                return notify_fail("������ʹ�á���Ů������������\n"); 
    
        if ( (int)me->query_temp("hsj_xiyi") ) 
                return notify_fail("������ʹ�á�ϣ�Ľ�������\n");

    
        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("����ڹ������޷�ʹ�á�ϣ�Ľ�������\n");

        message_vision(HIC "$N��ʱһ����ȣ�����"+weapon->name()+HIC"����һ��,ʹ����ɽ���ڵմ���ϣ�Ľ�����\n"+
                           "������ʱ�����޷졣"+weapon->name()+"������������������������������ǰ���ε���ȫ������������ȴ������϶���롣\n"NOR, me);
        me->start_perform(1,"��ϣ�Ľ�����");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("huashan-jianfa", 1)/4;
        me->add_temp("apply/armor",  skill*2);
        me->add_temp("apply/parry",  skill*3);
        me->add_temp("apply/dodge",  skill*3);
        me->add_temp("apply/damage",  -skill);
        me->set_temp("hsj_xiyi", 1);

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
        skill = me->query_skill("huashan-jianfa", 1)/4;
 
        me->add_temp("apply/parry", -skill*3);
        me->add_temp("apply/dodge", -skill*3);
        me->add_temp("apply/armor",  -skill*2);
        me->add_temp("apply/damage",  skill);
        me->delete_temp("hsj_xiyi");
        if(living(me) && !me->is_ghost())
           message_vision(HIW"һ��ϣ�Ľ����ݱϣ�$N������ʽ,ϣ�Ľ����Ľ���������ʧ��\n"NOR, me);
        return 0;
}

