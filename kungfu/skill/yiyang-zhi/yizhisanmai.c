// Modified by snowman@SJ 05/12/2000

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
        
        if( !target ) target = offensive_target(me);

        if( !target 
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("��һָ��������ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�һָ����������\n");   

        if( (int)me->query_skill("yiyang-zhi", 1) < 160 )
                return notify_fail("���һ��ָ��������죬ʹ������һָ��������������\n");

        if((int)me->query_skill("force") < 240 ) 
                return notify_fail("����ڹ���Ϊ��������ʹ������һָ��������������\n");

        if(!me->query_skill("kurong-changong", 1))
          if(me->query_skill("qiantian-yiyang", 1) < 140)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ������һָ����������\n");        

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("�������޷�ʹ�á�һָ����������\n"); 

        if( (int)me->query("max_neili") < (me->query_skill("force")+1000) )
                return notify_fail("����������̫����ʹ������һָ����������\n");      

        if( (int)me->query("neili") < (me->query_skill("force")+1100) )
                return notify_fail("����������̫����ʹ������һָ����������\n");

        if( (int)me->query("jingli") < (me->query_skill("force")+ 800) )
                return notify_fail("�����ھ���̫�٣�ʹ������һָ����������\n");

	lev = (int)me->query_skill("yiyang-zhi", 1)/4;
        
        message_vision(RED"\n$N��ָ�滺���磬�ձ�����Ʈ�ݣ��ֱ۲������������ѵ�ˮ��һָ���������Ϯ����������������ף�\n"NOR,me,target);
        me->add_temp("apply/finger", lev);
        me->add_temp("apply/attack", lev);       
        me->set_temp("yyz/yz3m",3);
        COMBAT_D->do_attack(me, target, 0, 1);
        if( me->is_fighting(target) && me->query_skill("finger") > 300 ) 
         	COMBAT_D->do_attack(me, target, 0, 3);
        if( me->is_fighting(target) && me->query_skill("finger") > 375 ) 
      		COMBAT_D->do_attack(me, target, 0, 3);

        me->start_busy(1);
        me->delete_temp("yyz/yz3m");
        me->add_temp("apply/finger", -lev);
        me->add_temp("apply/attack", -lev);
        me->add("neili", -400);
        me->add("jingli", -100);
        me->start_perform(3+random(2),"��һָ��������");
        return 1;
}
