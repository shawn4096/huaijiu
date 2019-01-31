// �Ƶ�
// Modified by snowman@SJ 17/12/2000
#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HBBLU"�����Ƶ�"NOR; }
int perform(object me, object target)
{
        int skill;
	object weapon;
	
	if( !target ) target = offensive_target(me);

        if( !target
        || !target->is_character()
        || !me->is_fighting(target)
        || !living(target)
        || environment(target)!=environment(me) 
        || target == me )
                return notify_fail("�Ƶ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if((int)me->query("neili") < 1000  ) 
                return notify_fail("�������������\n");
	if((int)me->query("jingli") < 200  ) 
                return notify_fail("��ľ���������\n");
                
	if( me->query_temp("weapon") )
		return notify_fail("��������ʹ�á��Ƶ�����\n");
		
        if((int)me->query_temp("tzzf") ) 
                return notify_fail("���Ѿ����Ƶ����˹��С�\n");

          if((int)me->query_skill("tiezhang-zhangfa", 1) < 150 )
                return notify_fail("��������Ʒ���������죬ʹ�������Ƶ�������\n");

          if((int)me->query_skill("force") < 225 )
                return notify_fail("����ڹ��ȼ�������ʹ�������Ƶ�������\n");

        if((int)me->query_str() < 30 )
                return notify_fail("�������������ǿ����ʹ�������Ƶ�������\n");

          if( (int)me->query_skill("guiyuan-tunafa", 1) < 150 )
                return notify_fail("��Ĺ�Ԫ���ɷ��ȼ���������ʹ�������Ƶ���������\n");

        if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á��Ƶ�����\n");

	skill = me->query_skill("strike");
	skill = skill / 3 + random(skill/3);
	
	weapon = new(BINGQI_D("tz_noshow"));
	if( !weapon )
		return notify_fail("Error! �Ƶ�������֪ͨ��ʦ�� cannot load tiezhang ��\n");
	weapon->move(me);
	weapon->set("sharpness", me->query("str")/3);
	if( wizardp(me) )
		write("Skill = "+skill+"\n");
	me->set_temp("weapon", weapon);
        me->add("neili", -(me->query_skill("strike")+100));
        me->add("jingli", -100);
        me->add_temp("apply/damage", skill);
        me->add_temp("apply/attack", skill/2);
        message_vision(WHT"\n$NͻȻ��ɫ�԰ף�˫�ֲ������漴�������һ����һ˫������ɫ���"HIW"ѩ��"WHT"������һ����ֵĹ�â��\n" NOR, me, target);
        me->set_temp("tzzf/wp", weapon);
        me->set_temp("tzzf/damage", skill);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
        call_out("remove_effect", 1 , me, skill, weapon);
        me->start_perform(2, "�Ƶ�");
                me->start_busy(random(2));
        return 1;
}

void remove_effect(object me, int skill, object weapon)
{
        object wp; 
        int damage;
        
        if ( !me ) {
		return;
	}
        wp = me->query_temp("tzzf/wp"); 
        damage = me->query_temp("tzzf/damage");
        if( !wp ){
        	if( damage ) {
        		me->add_temp("apply/damage", -damage);
        		me->add_temp("apply/attack", -damage/2);
        	}
        	return;
	}
	
        if( me->query_temp("weapon") != wp 
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
        || skill < 1
        || !me->is_fighting()
        || me->query("neili") < 1000 ){
        	destruct(wp);
        	me->add_temp("apply/damage", -damage);
        	me->add_temp("apply/attack", -damage/2);
            	me->delete_temp("tzzf");
            	me->delete_temp("weapon");
            	tell_object(me, WHT"\n���Ƶ��˹���ϣ�˫���𽥻ָ���ԭ״��\n" NOR);
            	return;
        }
        me->add("neili", -100);
        call_out("remove_effect", 1, me, skill--);
}

int help(object me)
{
        write(WHT"\n�����Ʒ��������Ƶ�����"NOR"\n");
        write(@HELP
        ������ǧ�����ƹ��ľ��У�˫�Ƶ������ˣ���Ӳ�ޱȣ��Ƴ��絶������һ
        ����������
        
        Ҫ��  ���� 1000 ���ϣ�      
                ���� 200 ���ϣ�  
                �����Ʒ��ȼ� 140 ���ϣ�
                ��Ԫ���ɷ��ȼ� 140 ���ϣ�    
                ������� 30 ���ϣ�
                �����ޱ�����
HELP
        );
        return 1;
}
