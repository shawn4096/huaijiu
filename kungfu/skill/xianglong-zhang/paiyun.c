// ����˫��
// by snowman@SJ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int i,j,jl;
        i = me->query_skill("strike", 1)/3;
        j = me->query_skill("xianglong-zhang", 1)/3;
        jl= me->query("jiali");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("������˫�ơ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á�����˫�ơ���\n");

        if( (int)me->query_skill("xianglong-zhang", 1) < 150 )
                return notify_fail("��Ľ���ʮ���ƻ�������죬ʹ����������˫�ơ�������\n");
        if( (int)me->query_skill("huntian-qigong", 1) < 150 )
                return notify_fail("��Ļ��������ȼ���������ʹ����������˫�ơ�������\n");
        if (me->query_skill_mapped("force") != "huntian-qigong")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");
        if( (int)me->query_skill("force") < 230 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�����˫�ơ���\n");

        if( (int)me->query_str() < 36 )
                return notify_fail("�������������ǿ����ʹ����������˫�ơ�����\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang"
        || me->query_skill_mapped("strike") != "xianglong-zhang"
        || me->query_skill_mapped("parry") != "xianglong-zhang")
                return notify_fail("�������޷�ʹ�á�����˫�ơ���\n");                                                                                 

        if( (int)me->query("max_neili") < 2000)
                return notify_fail("����������̫����ʹ����������˫�ơ���\n");      

        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����ʹ����������˫�ơ���\n");
//        if(me->query_temp("htqg/powerup"))
//                return notify_fail("������ʹ�û���������\n");
        if((int)me->query_temp("xlz/xiao") && userp(me)) 
                return notify_fail("������ʹ�ý���Х��\n");

        message_vision(WHT"\n$Nһ���Ϻȣ�˫�������Ю�������ɳ��ʹ����������ĵ��⹦������˫�ơ���\n"NOR,me);
        if( jl < 200) me->set("jiali", 200);

        me->add_temp("apply/strike", i);
        me->add_temp("apply/damage", (j/3+i/3));
        me->add_temp("apply/attack", j);
        me->add_temp("apply/strength", j/5);
        me->set_temp("xlz/py");
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        if(me->is_fighting(target)) 
        {
        if( random(me->query("combat_exp"))>target->query("combat_exp")/3
          ||me->query_skill("xianglong-zhang")>350)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        else
                {
                if ( random(me->query("combat_exp"))>target->query("combat_exp")/4
                   ||me->query_skill("xianglong-zhang")>300)
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                else
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                }
        }
        me->add_temp("apply/strike", -i);
        me->add_temp("apply/damage", -(j/3+i/3));
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/strength", -j/5);
        me->delete_temp("xlz/py");
        me->add("neili", -800);
        me->add("jingli", -100);
        me->start_busy(1+random(2));
        me->start_perform(5,"������˫�ơ�");
        me->set("jiali", jl);
        return 1;
}
