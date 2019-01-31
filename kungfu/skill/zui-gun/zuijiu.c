// zuijiu.c ���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{                                  
      int drunk, limit, i, lvl;
      object weapon;
      
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) || !living(target))
                return notify_fail("���������ֻ����ս���жԶ���ʹ�á�\n");

      if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "zui-gun")
                return notify_fail("�������޷�ʹ�á�������򡹡�\n");
                
      if( (int)me->query_temp("zui-gun") )
                return notify_fail("���ʹ��һ�顸������򡹣��ȵȾ�����˵�ɣ�\n");
            
      if( (int)me->query_skill("zui-gun",1) < 100 )
                return notify_fail("������������죬����ʹ�á�������򡹣�\n");
      
      if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("��������ʹ���ڹ��޷�ʹ����������򡹡�\n");

      if( (int)me->query_skill("yijin-jing",1) < 100 )
                return notify_fail("����׽�ȼ�����������ʹ�á�������򡹣�\n");  
       
      if( (int)me->query_str() < 25 )
                return notify_fail("��ı�������ǿ������ʹ�á�������򡹣�\n");
      
      if( (int)me->query("max_neili") < 1300 )
                return notify_fail("�������̫��������ʹ�á�������򡹣�\n");
            
      	drunk = me->query_condition("drunk");
      	limit = (me->query("con") + (int)me->query("max_neili") / 50) * 2;
      	lvl = (int)me->query_skill("zui-gun", 1);
      	if( drunk <= limit/4 && lvl < 180) 
                return notify_fail("��û��һ�����⣬��ôʹ�ó���������򡹣�\n");
      	if( drunk >= limit && lvl < 240) 
                return notify_fail("���������������������࣬�ƹ�\n");

      	lvl /= 20;
      	lvl--;
      	if(lvl > 8) lvl = 8;  
      	if(lvl < 1) return notify_fail("��ĵȼ�̫�ͣ��޷�ʹ�ó���������򡹣�\n");

      	if( (int)me->query("neili") < 100*lvl )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó���������򡹣�\n");
          
      	message_vision(HIY"\n$NͻȻһ�����ã���ʱ���žƾ��ʹ��������������\n"NOR,me);
      	me->set_temp("zuijiu", 1);
      	for(i=0; i < lvl; i++){
      	   	if(!me->is_killing(target->query("id")) 
      	   	&& !target->is_killing(me->query("id"))
      	   	&& !target->is_fighting(me))
      	   	break;
           	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?2:0);
           	me->add_temp("zuijiu", 1);
           	me->receive_damage("neili", 100);
      		me->receive_damage("jingli", 20);
      	}
      	me->delete_temp("zuijiu");
      	i = me->query_skill("club")/2;
      	me->set_temp("zui-gun", 1);
      	call_out("remove_effect", i, me);    
      	me->start_busy(3);

        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("zui-gun");
        tell_object(me, HIG"\n�㾭��һ��ʱ�䣬��������ˡ�\n"NOR); 
}

