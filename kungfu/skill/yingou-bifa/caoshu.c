//caoshu.c ����
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
      string msg; 
      int i,damage,p;
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("������û�бʣ��޷�д�����飡\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("����ֻ����ս���жԶ���ʹ�á�\n");
             
      if( (int)me->query_skill("yingou-bifa",1) < 120 )
         return notify_fail("��������ʷ���������죬����д���飡\n");
      
      if( (int)me->query_skill("literate",1) < 120 )
         return notify_fail("��Ķ���д�ֵȼ�����������д�����飡\n");  
      
      if( (int)me->query_skill("guiyuan-tunafa",1) < 140 )
         return notify_fail("��Ĺ�Ԫ���ɷ��ȼ�����������д�����飡\n");  

      if( (int)me->query("max_neili") < 1500 )
         return notify_fail("�������̫����д�������ɷ���Ĳ���! \n");
      
      if( (int)me->query("neili") < 500 )
         return notify_fail("�������̫���ˣ�д���Ĳ����޴����\n"); 
      
      if (me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("�������޷�д�������项��\n");

      i = random((int)(me->query_skill("yingou-bifa",1)/15));
      if(i < 1) i = 1;
      if(i > 10) i = 10;
      msg = HIM"$N������裬�񱼼��ߣ�����ȫȻ�����·���ֻ���������񲡢���������а��\n"+
               "�������죬�������ߣ�ԭ��$N��ʱ���飬�����ƴ�����ġ���������������ų�\n"+
  "����ʥ�����˲���֮ʥ��\n" NOR;
message_vision(msg,me,target);
msg="\n";
      me->add("neili", - 250);
      me->add("jingli", -80);
 me->add_temp("apply/strength", i*5);
me->add_temp("apply/brush",i*10);
me->add_temp("apply/attack",i*10);
 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
 me->add_temp("apply/strength", -i*5);
 me->add_temp("apply/attack", -i*10);
me->add_temp("apply/brush",-i*10);
      if( random(me->query_skill("literate", 1)) > target->query_skill("literate", 1)/4
 && random(me->query_skill("force")) > target->query_skill("force")/4
       && me->is_fighting(target)
       && present(target,environment(me))){
          me->start_busy(2);
          target->start_busy(1);             
          damage = (int)me->query_skill("yingou-bifa", 1);               
          damage = damage/2 + random(damage);
          damage = damage * i * 2 / 3;
 if (damage > 1500 ) damage = 1500;
          target->receive_damage("qi", damage);
          target->receive_wound("qi", damage/3);  
 msg += HIB"ͻȻ$N�ʷ��â������д�����������������Ǹ��������֣����һ�ʹ���������ֱ��\n"+
                    "����$n���ϣ���ʱ��Ѫֱ����$n���������˺ü�����\n"NOR;
          p = (int)target->query("qi")*100/(int)target->query("max_qi");
          msg += "( $n"+eff_status_msg(p)+" )\n";
      }
      else {
          me->start_busy(1);
          msg += HIG"$p���·�����Х���������䣬����һ�󼲷磬����$P��ȥ�������������������˲���\n"+
                    "�����ؽ������ᣬֻ��$p���в�ס����������ߺ��������$P���ǵͰ���������������\n"+
                    "$p���˸�����൱��\n"NOR;
         if (!(target->query("neili")< 200)) target->add("neili",- 100);
       }
       message_vision(msg, me, target);
       me->start_perform(4,"�����项");
       return 1;
}
