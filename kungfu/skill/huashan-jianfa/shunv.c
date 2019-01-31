#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me, int amount);
int perform(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("����Ů������ֻ����ս����ʹ�á�\n");

        if((int)me->query_skill("zixia-gong", 1) < 130 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á���Ů��������\n");
    
        if ((int)me->query_skill("huashan-jianfa", 1) < 130 )
                return notify_fail("��Ļ�ɽ����������죬�����������ӡ���Ů��������\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("parry") != "huashan-jianfa"
         || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޷�ʹ�á���Ů����������������ʡ�\n");
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("����������̫��������ʹ�á���Ů��������\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á���Ů��������\n");

        if ((int)me->query_temp("hsj_junzi"))
                return notify_fail("������ʹ�á����ӽ�����������\n"); 

        if ((int)me->query_temp("hsj_shunv"))
                return notify_fail("������ʹ�á���Ů������������\n"); 
    
        if ( (int)me->query_temp("hsj_xiyi") ) 
                return notify_fail("������ʹ�á���Ů��������\n");

    
        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("����ڹ������޷�ʹ�á���Ů��������\n");

        message_vision(HIC "$N��ʱһ����ȣ�����"+weapon->name()+HIC"����һ��,ʹ����ɽ���ڵմ�����Ů������\n"+
                           "����Ů���״��񼼺����˵á�����"+weapon->name()+HIC"��������ɺ磬���۶�����Ų��Ծ�������мܣ�ȴʼ���Ѳ���$N�Ľ������֣�\n"NOR, me);
        me->start_perform(1,"����Ů������");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("huashan-jianfa", 1)/5;
        me->add_temp("apply/dexerity",  skill);
        me->set_temp("hsj_shunv", skill);

        call_out("check_fight", 1, me, weapon);
        return 1;
}

void check_fight(object me, object weapon)
{  
        object wep;
        int i;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep
         || weapon != wep ){
	   i = me->query_temp("hsj_shunv");
           me->add_temp("apply/dexerity", -i);
           me->delete_temp("hsj_shunv");
           if(living(me) && !me->is_ghost())
              message_vision(HIW"һ����Ů�����ݱϣ�$N������ʽ,��Ů�����Ľ���������ʧ��\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me, weapon);
}
