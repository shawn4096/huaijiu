// zixu.c ����ٶ�
// created by Olives@SJ
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object target, int skill);
void check_fight(object me, object target, int improve);

int perform(object me, object target)
{
        int skill,ap,pp;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("������ٶ���ֻ�а��˽���������ã�\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 120 )
                return notify_fail("�������ذ��������죬����ʹ������ٶ���\n");

    	if( (int)me->query("neili", 1) < 800 )
       		return notify_fail("�������������㣡\n");
       	if( (int)me->query("jingli", 1) < 500 )
       		return notify_fail("�����ھ������㣡\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       		return notify_fail("��������Ϊ���㣡\n");
        if( (int)me->query_dex() < 30  )
                return notify_fail("�����̫�ͣ�����ʹ������ٶ���\n");
       if(target->query_temp("sld/pfm/zixu"))
              return notify_fail("���Ѿ���"+target->name()+"ʹ�á�����ٶ����ˣ�\n");

        if(!weapon
        || me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("�������޷�ʹ������ٶ���\n");
         if(me->query("gender")!="����")
             return notify_fail("�㲻�����ӣ����ʹ������ٶ���\n");


        skill = (int)me->query_skill("tenglong-bifa", 1);
	skill /=30;
	if(skill>7) skill = 7;
	ap = me->query("combat_exp");
        pp = target->query("combat_exp");

        me->add("neili", -350);
        me->add("jingli", -200);
  	message_vision(HIY"\nֻ��$N������Ȼ��ת����$n��Ҹ��ɦ��һ�ѡ�$n���һЦ����������������$N��������ס$nҸ�£����ֻ�ת��ץס$n��ڣ�����$n���ӣ������Լ�ͷ������Ȼ����ˤ����\n"NOR,me,target);
	
  	if(random(ap)>pp/2)
  	{
  		message_vision("\n�����ǵ���ʯ֮�䣬$N�Ѿ���ס��$n���ġ�С��Ѩ����Ҹ�¡���ȪѨ����$n��ˤ�ڵ��ϣ����Ƕ������á�\n",me,target);
                  target->start_lost(random(skill/30)+1);
                  target->add_temp("sld/pfm/zixu",target->query_dex()/2);
		target->add_temp("apply/dexerity",-target->query_dex()/2);
		target->set_temp("sld/pfm/zixu",1);
		me->start_perform(5,"������ٶ���");

	        target->start_call_out( (: call_other, __FILE__, "check_fight",  me, target, skill/5 :), 1);
		return 1;
  	}
  	else
  	{
  		message_vision("\nֻ��$N��ָ����������$n���ġ�С��Ѩ����Ҹ�¡���ȪѨ����$n��æ������Ѩ��������⼸�µ�Ѩ�����Ӹ�һ�ŵأ������˳�ȥ������ˮ�滬��Ư�С�\n",me,target);
  		me->start_perform(3+random(2),"������ٶ���");
  		return 1;
  	}
	return 1;
}

void check_fight(object me, object target, int improve)
{
       object weapon;

       if(!target) return;
       if(!me) {
          remove_effect(target,improve);
          return;
       }
       else
       if(!me->is_fighting(target) && target->query_temp("sld/pfm/zixu")){
          remove_effect(target, improve);
          return;
       }
       else if( (target->query_temp("qianshou"))
        && (!target->is_fighting()
        || !me->is_fighting()
        || !living(me)
        || target->is_ghost()
        || me->is_ghost()
        || !improve ))
        {
               remove_effect(target, improve);
               return;
        }
          else if(target->query_temp("sld/pfm/zixu"))
        {
        	weapon = me->query_temp("weapon");
        	if(!objectp(weapon)
        	|| weapon->query("skill_type")!= "dagger")
        	{
                	remove_effect(target, improve);
                	return;
                }
        }
        else{
            call_out("check_fight", 1, me, target, --improve);
            return;
        }
}

void remove_effect(object target, int skill)
{

          target->add_temp("apply/dexerity",target->query_temp("sld/pfm/zixu"));
        tell_object(target, HIB"�㽥����Ӧ�����ֱ仯��״̬�ָֻ��糣��\n"NOR);
}
