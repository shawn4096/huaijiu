// leidong.c �׶�����
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int improve, improve2;
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�׶�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ���׶����죡\n");  
                
        if( (int)me->query_skill("poyu-quan", 1) < 100 )
                return notify_fail("��Ļ�Ԫ�Ʋ�����죬����ʹ���׶����죡\n");
                                
        if( (int)me->query_skill("zixia-gong", 1) < 80 )
                return notify_fail("�����ϼ�񹦲����ߣ������ó��׶������˵С�\n");

       if (me->query_skill_prepared("cuff") != "poyu-quan"
           || me->query_skill_mapped("cuff") != "poyu-quan")
               return notify_fail("�������޷�ʹ�á��׶����졹���й�����\n");                                                                                 

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������̫�����޷�ʹ���׶����졣\n");

        if( me->query_temp("leidong"))
                return notify_fail("������ʹ���׶����죡\n");

        msg = MAG"$Nʹ����ʯ����ȭ�ľ�ѧ�׶����죬��ʱ��յ���������\n"NOR;
      message_vision(msg, me); 
      
      improve = (int)me->query("dex");
      me->add_temp("apply/dexerity", improve);
      improve2 = (int)me->query("str");
      me->add_temp("apply/strength", improve2);
      me->set_temp("leidong",1);  
      me->add("neili", - 300);
	target->interrupt_me();
	target->start_busy(3);
	COMBAT_D->do_attack(me, target, 0, 1);
	if (random(me->query_skill("poyu-quan",1))>200)
	{
		COMBAT_D->do_attack(me, target, 0, 3);
	}
	call_out("check_fight", 1, me, improve, improve2, me->query_skill("dodge", 1));
	me->start_perform(me->query_skill("dodge", 1) / 2, "�׶�����");
      return 1;
}

void remove_effect(object me, int improve, int improve2)
{
	string msgfinish = MAG"$N�׶����쾢���ѹ������ܽ����ָ���Ȼ��\n"NOR;
       me->add_temp("apply/dexerity", - improve);
       me->add_temp("apply/strength", -improve2);
       message_vision(msgfinish, me); 
       me->delete_temp("leidong");
	me->start_perform(0);
//    if (!me->is_busy()) me->start_busy(2);
}

void check_fight(object me, int improve, int improve2, int t)
{
	if (!me) return;
	if (t && me->is_fighting()) call_out("check_fight", 1, me, improve, improve2, t-1);
	else remove_effect(me, improve, improve2);
}
