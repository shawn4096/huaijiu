#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string perform_name(){ return HBBLU"��������ץ"NOR; }
int perform(object me, object target)
{
        object room, ob;
       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("������ץ��ֻ����ս���жԶ���ʹ�á�\n");

       if( !userp(target))
            return notify_fail("�㲻�ܶ���ʹ�����������\n");

        if(!( room = find_object("/d/taishan/fengchan")) )
                room = load_object("/d/taishan/fengchan");
        if( objectp(ob = present("zhong shentong", room)) ) {
                if(target->query("id") == ob->query("winner"))
                        return notify_fail("�󵨣����Ҷ�����ͨ���û����󷨣�\n");
        }

       if( target->query("combat_exp")<me->query("combat_exp"))
            return notify_fail("��������˵ûʲô����������ȡ�ˡ�\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("�������ֲ���ʹ�á�����ץ����\n");

       if( (int)me->query_skill("sanyin-zhua", 1) < 250 )
            return notify_fail("������޶�ץ��������죬ʹ����������ץ��������\n");

       if( (int)me->query_skill("huagong-dafa",1) < 250 )
            return notify_fail("��Ļ�������Ϊ����������ʹ�á�����ץ����\n");

       if((int)me->query_skill("poison",1)<200)
           return notify_fail("����������޷�ʹ������ץ��\n"); 

       if (me->query_skill_prepared("claw") != "sanyin-zhua"
        || me->query_skill_mapped("claw") != "sanyin-zhua"
        || me->query_skill_mapped("parry") != "sanyin-zhua")
           return notify_fail("�������޷�ʹ�á�����ץ����\n");

       if( (int)me->query("max_neili") < 3000) 
           return notify_fail("������̫����ʹ����������ץ����\n");

       if( (int)me->query("neili") < 6000)
           return notify_fail("����������̫����ʹ����������ץ����\n");

     message_vision(HBBLU"$N���������ͻȻץ��$n�ĵ��\n"NOR,me,target);
     message_vision(HBBLU"$nֻ����$N�þ�ȫ����ȫ�������ǿ��ע�������У�\n"NOR,me,target);
       if (!target->is_killing(me))
         me->kill_ob(target);
       me->start_perform(8, "����ץ");
       target->add("neili",me->query("neili"));
       me->set("neili", 0);
       me->start_busy(random(2)+1);
       if (random(me->query("combat_exp")) > target->query("combat_exp")*2/3) {
     message_vision(HBRED"$n��ǿ������������£����ù�������������\n"NOR,me,target);
       me->add("combat_exp",me->query_skill("force")*10);
       target->add("combat_exp",-(me->query_skill("force")*10)); 
       target->apply_condition("xx_poison",random(5)+3);
	if (userp(me) && userp(target) && me->query_condition("killer") < 15)
		me->apply_condition("killer", 15);
       target->start_busy(1);
      } else {     message_vision(HBGRN"$nʹ�������ڹ��ķ�������ʹ��$N��������$N���˻�ȥ��\n"NOR,me,target);
      }
      return 1;
}

