// by darken@SJ
#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;
 string perform_name(){ return HBBLU"��������"NOR; }
 int perform(object me, object target)
 {
         int j;
         string msg;
         j = me->query_skill("tiezhang-zhangfa", 1);

         if( !target ) target = offensive_target(me);

         if( !target 
           || !me->is_fighting(target)
           || !living(target)
           || environment(target)!= environment(me))
                 return notify_fail("���������ơ�ֻ����ս���жԶ���ʹ�á�\n");

         if( objectp(me->query_temp("weapon")) )
                 return notify_fail("�������ֲ���ʹ�á��������ơ���\n");

         if( (int)me->query_skill("tiezhang-zhangfa", 1) < 250 )
                 return notify_fail("������Ʋ�����죬ʹ�������������ơ�������\n");

         if( (int)me->query_skill("guiyuan-tunafa", 1) < 250 )
                 return notify_fail("���Ԫ���ɷ�������ʹ�������������ơ�������\n");

         if( (int)me->query("jiali") < 120 )
                 return notify_fail("�����������ʹ�������������ơ�������\n");

         if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                 return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

         if( (int)me->query_skill("force") < 250 )
                 return notify_fail("����ڹ��ȼ�����������ʹ�á��������ơ���\n");

         if( (int)me->query_str() < 40 )
                 return notify_fail("�������������ǿ����ʹ�������������ơ�����\n");

         if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
          || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
          || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                 return notify_fail("�������޷�ʹ�á��������ơ���\n");

         if( (int)me->query("max_neili") < 2000)
                 return notify_fail("����������̫����ʹ�������������ơ���\n");

         if( (int)me->query("neili") < 1500 )
                 return notify_fail("����������̫����ʹ�������������ơ���\n");
         
         if( target->query_temp("pushan") )
                 return notify_fail("����ô��������\n");

         msg = HIW "\n$N������һ���������һ����ʩ�������Ʒ��еġ��������ơ�����$n��\n"NOR;
          if ( target->query_int()/2 < random(me->query_int())) {
              msg += HIG"\n$n˫��һ����Ӳ�ǽ�����$N��һ�ƣ�\n"NOR;
              if (target->query_str()/2 > random(me->query_str())) {
                  target->add_temp("apply/strength",-me->query_str());
                  target->set_temp("pushan",me->query_str());
                  target->receive_wound("qi",j*2);
                  target->receive_damage("qi",j*4);
                  msg += HIR"\nֻ��������һ����$n����Ǿ�Ȼ��Ӳ����������ˣ�\n"NOR;
                  
              } else {
                  msg += HIR"\n$n�۵����һ����Ѫ���ƺ����˼��ص����ˣ�\n"NOR;
                 
                  target->receive_wound("qi",j*4);
                  target->receive_damage("qi",j*8);
              }
              message_vision(msg, me, target);
              COMBAT_D->report_status(target);
         } else {
             msg += HIY"\n$n���������ͣ�����Ӳ������æת��ܿ���\n"NOR;
             msg += HIR"\n��֪$N�Ѿ���������������������������֣�\n"NOR;
                 message_vision(msg, me, target);
             me->set_temp("tzzf",1);
                 if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->delete_temp("tzzf");
         }               

         me->add("neili", -1500);
         me->start_busy(random(2));
         
         me->start_perform(5,"���������ơ�");
         return 1;
 }

