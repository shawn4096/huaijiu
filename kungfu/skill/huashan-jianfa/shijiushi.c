// shijiushi.c ��Ůʮ��ʽ

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#define MAX_HITS    19
 
int perform(object me, object target)
{
        string weapon;
        int i;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��Ůʮ��ʽֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_dex() < 60 )
                return notify_fail("�������������������㣬����ʹ����Ůʮ��ʽ��\n");
        
        if( me->query_skill("zixia-gong", 1) < 300 )
                return notify_fail("�����ϼ�����δ�����޷�ʩչ��Ůʮ��ʽ��\n");

        if( me->query_skill("dodge") < 300 )
                return notify_fail("��Ůʮ��ʽ��Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ����Ůʮ��ʽ��\n");

        if( me->query("neili") <= 5000 )
                return notify_fail("�����������ʹ����Ůʮ��ʽ��\n");

        if( me->query("jingli") <= 3000 )
                return notify_fail("��ľ�������ʹ����Ůʮ��ʽ��\n");

        if( me->query_temp("hsj_19"))
                return notify_fail("������������Ůʮ��ʽ��\n");

        if( !me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("�������޽�����ʹ����Ůʮ��ʽ����\n");

        weapon = (me->query_temp("weapon"))->query("name");

        message_vision(HIC "\n$N�˽���磬����ǳ��ġ���Ů��ʮ��ʽ��һʽʽʩչ������" + weapon + HIC"����������,���������⣡\n" +
        "���֮�䣬$N������Ůʮ�Ž�������ʮ��ʽ��������һ���ǳɵ�ʹ�˳������������б���һ�У�����֮�죬ֱ�Ƿ�����˼��\n\n" NOR, me, target);
        me->set_temp("hsj_19",1);
          me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1));
 
    for( i = 0; i < MAX_HITS; i ++ ) {
        if( random( MAX_HITS ) >= i ) {
          if (me->query("gender") == "Ů��")
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          else
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
          me->add("neili",-100);
          }
        else {
            break;
        }
    }
        me->add("neili", -300);
          me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1));
        me->add("jingli", -100);
        me->delete_temp("hsj_19");
        me->start_perform(2+random(3));

        return 1;
}

