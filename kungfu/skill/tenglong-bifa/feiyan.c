// beauty �������
// 19991002001

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>


int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int dex,urdex,damage;

        if(!target) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��������衹ֻ����ս��ʱʹ�ã�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("��������衹ֻ�а��˽���������ã�\n");

        if(!objectp(weapon=me->query_temp("weapon"))
        || weapon->query("skill_type") != "dagger")
             return notify_fail("������û��ذ�ף����ʹ�á�������衹��\n");

        if( (int)(dex=me->query("dex")+me->query_skill("dodge",1)/10) < 30 )
                return notify_fail("����������ʹ�á�������衹�����»��˵��Լ���\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 150 )
                return notify_fail("�������ذ������������������ʹ�á�������衹��\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("ֻ��ʹ������ذ��ʱ����ʹ�á�������衹��\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("��Ķ����󷨹������㣬�����á�������衹��\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á�������衹��\n");

        if((int)me->query("neili", 1) < 1500)
                return notify_fail("�������������㣬����ʹ�á�������衹��\n");

        if(me->query("gender") == "����" )
                return notify_fail("����Ů����ô��ʹ�á�������衹�أ�\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ�������໥�ִ�������ʹ�á�������衹��\n");

        damage = 4 * (int)me->query_skill("tenglong-bifa", 1);
        damage = damage / 2 + random(damage / 2) + 5*me->query("jiali");
        damage *=2;
        if(damage >4000) damage = 4000+random(damage-4000)/5;
	if(wizardp(me))
		tell_object(me,sprintf("damage = %O\n",damage));
        msg = HIR"$N��$n��������֮����ƴ��ȫ��ʹ���շ��˲���֮����������������衹"NOR;
        msg +=MAG "\n$Nʹ��һ�С�������衹������˳��һ�����ڱ�����һ�㣬����������$N�ʺ����˹�ȥ��\n"NOR;
	me->receive_damage("jingli",200+random(100));
	me->receive_damage("neili",400+random(200));
	if(userp(target) && userp(me) && !random(dex))
		{
			msg+= MAG"\n$Nһ�������񣬾�Ȼû�ж�������Լ��ʺ��ذ�ף�ֻ��ذ������$N�ʺ�\n";
			message_vision(msg,me);
			me->set("eff_qi",-1);
			COMBAT_D->report_status(me,1);
			return 1;
		}
	urdex = target->query("dex")+target->query_skill("dodge",1)/10;
        if(random(dex+urdex)>urdex  )
        {
 		msg += MAG"$N��������һ�����Ǳ�������$n"NOR;
 		if(random(me->query("kar")+me->query("pur")+me->query("per"))>target->query("kar")+target->query("pur")+target->query("per"))
 		{
 			target->set("eff_qi",-1);
 			msg += MAG"�ʺ�$n���������������һ�������ʺ�$n�ʺ��з�������ʹ������������۷��׾͵��ڵ��ϡ�\n"NOR;
                	message_vision(msg,me,target);
 			COMBAT_D->report_status(target,1);
 			me->start_busy(3+random(3));
 			me->start_perform(3+random(4),"��������衹");
 			return 1;
 		}
 		else
 		{
                	target->receive_damage("qi",damage,me);
                	target->receive_wound("qi",damage/2-target->query_temp("apply/armor"),me);
                	msg += MAG"�ؿڣ�$n������������������ؿڡ�\n"NOR;
                	result = damage_msg(damage,"����");
	                result = replace_string( result, "$l", "�ؿ�" );
	                result = replace_string( result, "$w", weapon->name() );
        	        msg += result;
	               	message_vision(msg,me,target);
                	COMBAT_D->report_status(target,1);
                	me->start_busy(1);
                	me->start_perform(2+random(3),"��������衹");
                	return 1;
                }
        }
        else {
                msg += "\n$n��$N��ס������Σ���ң���������סҪ����ͬʱ�߸�Ծ�𣬷�����ͷײ�أ���$Nײ�˳�ȥ��\n";
                message_vision(msg,me,target);
                me->start_busy(2);
                me->start_perform(1+random(3),"��������衹");
        }
        return 1;
}

