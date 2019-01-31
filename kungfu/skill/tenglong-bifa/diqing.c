// diqing.c ���ཱུ��
// created by Olives@SJ

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void back(object target);

int perform(object me, object target)
{
        int skill,ap,pp,time;
        object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("�����ཱུ����ֻ�а��˽���������ã�\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 120 )
                return notify_fail("�������ذ��������죬����ʹ�õ��ཱུ����\n");

    	if( (int)me->query("neili", 1) < 800 )
       		return notify_fail("�������������㣡\n");
       	if( (int)me->query("jingli", 1) < 500 )
       		return notify_fail("�����ھ������㣡\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       		return notify_fail("��������Ϊ���㣡\n");
        if( (int)me->query_dex() < 30  )
                return notify_fail("�����̫�ͣ�����ʹ�õ��ཱུ����\n");

        if (!weapon
        || me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("�������޷�ʹ�õ��ཱུ����\n");

        if(target->query_temp("sld/pfm/diqing")
        || target->query_temp("block_msg/all"))
                return notify_fail("�����۾��Ѿ�Ϲ�ˣ��������õ��ཱུ���ˣ�\n");
         if(me->query("gender")!="����")
             return notify_fail("�㲻�����ӣ����ʹ�õ��ཱུ����\n");
        skill = (int)me->query_skill("tenglong-bifa", 1);

	ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
        pp = COMBAT_D->skill_power(me,"parry",SKILL_USAGE_ATTACK);
        if(target->is_busy())
        	pp /= 2;

        me->add("neili", -350);
        me->add("jingli", -200);
        message_vision(HIY "\n$Nʹ��һ�С����ཱུ������������ײ��ʮָ��$n�ؿ���ץ���������֮�ʣ�ͻȻһ����������������Ծ��˫��һ�֣�������$n��ͷ��ͬʱ˫��Ĵָѹס$n̫��Ѩ��ʳָ��ü����ָ���ۡ�\n"NOR,me,target);

        message_vision(HIY"$nһ����æ˫�ۻ�ת���뻤ס˫�ۣ�\n"NOR, me, target);;

  	if(random(ap+pp)>pp)
         {
                message_vision(HIR"\nֻ��$n�ҽ�һ����$N����֧��ָ�Ѿ�����$n���ۿ���ֻ��$n���۽���Ѫֱ����\n"NOR, me, target);
                target->set_temp("sld/pfm/diqing", skill);
                target->add_temp("apply/attack", - skill/3);
                target->add_temp("apply/defense", -skill/3);
                target->receive_damage("qi", skill*5);
                target->receive_wound("qi", skill*5/2);
                COMBAT_D->report_status(target);
                target->kill_ob(me);
                target->set_temp("block_msg/all",1);
                me->start_perform(10,"���ཱུ��");
                time = 3+skill/10;
                if(time>60) time = 60;
                call_out("back", time, target);
                }

  	else {
                message_vision(HIY"$n��ͷ����һ������������㿪��$N��һ�С�\n"NOR, me, target);
                me->start_perform(2+random(3),"���ཱུ��");
                me->start_busy(3);
                target->kill_ob(me);
        }

        return 1;
}

void back(object target)
{
        int lvl;
        if(!target) return;
        lvl = target->query_temp("sld/pfm/diqing");
        target->add_temp("apply/attack", lvl/3);
        target->add_temp("apply/defense", lvl/3);
        target->set_temp("block_msg/all", 0);
        if(living(target))
              tell_object(target, HIW "��������˫Ŀû�б�ץϹ�����ֿ��Կ�����������\n" NOR);
        target->delete_temp("sld/pfm/diqing");
}
