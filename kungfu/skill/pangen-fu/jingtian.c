//  jingtian.c ������Ƹ� 
//  by Leontt 2000.6.11

#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
      int lvl;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("pangen-fu", 1)/3;
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
        return notify_fail("��������Ƹ���ֻ����ս���жԶ���ʹ�á�\n");
    
      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "pangen-fu")
        return notify_fail("��ʹ�õı��в��ԣ��޷�ʹ�á�������Ƹ�����\n");             

      if( (int)me->query_skill("pangen-fu",1) < 120 )
        return notify_fail("����̸�����������죬����ʹ�á�������Ƹ�����\n"); 
      
      if( (int)me->query_skill("axe",1) < 100 )
        return notify_fail("��Ļ��������ȼ�����������ʹ�á�������Ƹ�����\n");  
     
      if( (int)me->query_skill("qiantian-yiyang", 1) < 100 )
        return notify_fail("���Ǭ��һ�����ȼ�����������ʹ�á�������Ƹ�����\n");

      if( (int)me->query("max_neili") < 1000 )
        return notify_fail("�������̫��������ʹ�á�������Ƹ�����\n");
      
      if( (int)me->query("neili") < ( me->query_skill("force")+ lvl ))
        return notify_fail("�������̫���ˣ��޷�ʹ�ó���������Ƹ�����\n");   
      
      message_vision(HIY"\n$NͻȻͻȻ���һ�����羪��һ�㣬������"+weapon->query("name") +HIY"б���Ͼ���Ȼ���ڰ���л���һ"+
                          "��Բ�����漴��ֱб��ն��$n����һ˲�䣬$nֻ���ú������ѣ�\n"NOR, me,target);
      me->add("neili", - (300+random(200)));
      me->add("jingli", -80);      
      lvl= lvl/3 + me->query("con")/2 + me->query("str");
      me->add_temp("apply/axe", lvl);
      me->add_temp("apply/attack", lvl);
      me->set_temp("jingtian", 1);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
      if (present(target,environment(me)) && me->is_fighting(target))
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);  
      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("pangen-fu", 1) > 150){
       if(random(me->query("combat_exp")) > target->query("combat_exp")/2)     
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       else 
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
      }
      me->add_temp("apply/axe", -lvl);
      me->add_temp("apply/attack", -lvl);
      me->delete_temp("jingtian");
      me->start_busy(random(2));
      me->start_perform(5,"��������Ƹ���");
      return 1;
}
