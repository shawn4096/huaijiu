// kuangfeng.c  ������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int lvl;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!(me->query("thd/perform") & 4))
                return notify_fail("����Ȼ��˵���������������һ��������񼼣�����ȴδ��Ƶ������ڡ�\n");

        if( objectp(me->query_temp("weapon")) )
               return notify_fail("��������ʹ�á�����������\n");

        if( (int)me->query_skill("luoying-zhang", 1) < 100 )
                return notify_fail("�����Ӣ���Ʋ�����죬�޷�ʩչ����������\n");

        if( (int)me->query_skill("xuanfeng-tui", 1) < 100 )
                return notify_fail("�������ɨҶ�Ȳ�����죬�޷�ʩչ����������\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 100)
                return notify_fail("��ı̺���������򲻹����޷�ʩչ����������\n");
        if ( (int)me->query("max_neili") < 1000)
                return notify_fail("��������������޷�ʩչ����������\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ����������\n");
       if (me->query_temp("thd/is_fast"))
                return notify_fail("������ʹ��������ת��\n");

        if (me->query_skill_prepared("leg") != "xuanfeng-tui"
            || me->query_skill_mapped("leg") != "xuanfeng-tui"
            || me->query_skill_mapped("strike") != "luoying-zhang" )
                return notify_fail("�������޷�ʹ�ÿ��������й�����\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("��ı̺���������Ϊ�������޷�ʹ�ÿ��������й�����\n");
                
        me->start_perform(4, "������");
        lvl = (me->query_skill("xuanfeng-tui",1) + me->query_skill("luoying-zhang",1) )/2;
        lvl = lvl*5/7 + random(lvl*3/7);
        message_vision(HIG "$Nһ����Х��ȭ����ʩ��ʹ���һ�����������Ѹ�����׵ع���$n��\n"NOR,me, target);
 me->add_temp("apply/attack",lvl/6);
 me->add_temp("apply/leg",lvl/8);
        me->add("neili", -(200 +random(100)) );
        me->prepare_skill("leg");
        me->prepare_skill("strike","luoying-zhang");
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->prepare_skill("strike");
        me->prepare_skill("leg","xuanfeng-tui");
        if(me->is_fighting(target)){
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                me->prepare_skill("leg");
                me->prepare_skill("strike","luoying-zhang");
        }
        if(me->is_fighting(target) && me->query_skill("luoying-zhang", 1) > 150)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->prepare_skill("strike");
        me->prepare_skill("leg","xuanfeng-tui");
        if(me->is_fighting(target) && (me->query_skill("xuanfeng-tui",1)) > 180 ){
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                me->prepare_skill("leg");
                me->prepare_skill("strike","luoying-zhang");
        }
        if(me->is_fighting(target) && random(me->query_skill("luoying-zhang", 1)) > 200)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->prepare_skill("strike");
        me->prepare_skill("leg","xuanfeng-tui");
        if(me->is_fighting(target) && random(me->query_skill("xuanfeng-tui", 1)) > 220)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

        me->prepare_skill("leg","xuanfeng-tui");
        me->start_busy(random(2) + 1);
me->add_temp("apply/attack",- lvl/6);
me->add_temp("apply/leg",- lvl/8);
        return 1;
}
