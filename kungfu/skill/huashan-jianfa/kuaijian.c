// kuaijian.c ���콣
// by darken@SJ
// modified olives@SJ
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
 
int perform(object me, object target)
{
        if( !target || target == me) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���콣ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_dex() < 60 )
                return notify_fail("�������������������㣬����ʹ�ÿ��콣��\n");
        
        if( me->query_skill("zixia-gong", 1) < 300 )
                return notify_fail("�����ϼ�����δ�����޷�ʩչ���콣��\n");

        if( me->query_skill("dodge") < 300 )
                return notify_fail("���콣��Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ�ÿ��콣��\n");

        if( me->query("neili") <= 5000 )
                return notify_fail("�����������ʹ�ÿ��콣��\n");

        if( me->query("jingli") <= 3000 )
                return notify_fail("��ľ�������ʹ�ÿ��콣��\n");

        if( me->query_temp("hsj_kf",))
                return notify_fail("���������ÿ��콣��\n");

          if(!me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("�������޽�����ʹ�ÿ��콣����\n");

        message_vision(HIG"$N����һ����Х��б�ж�ǰ����������ֱ����Ѹ���ޱȣ�δ�������У�
�������ѷ�������������$N����Խ��Խ�죬����Ҳ�ǽ��졣����һ��
����һ����������ķ���ҲԽ��Խǿ��һ�����ʽ�����콣����̼�
ȫ��$n�����к���\n"NOR, me, target);
        me->set_temp("hsj_kf",1);
        me->add("neili",-1000);
        me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/6);
        me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/10);
        call_out("kuangfeng", 0, me, target);
        me->start_perform(999);
        return 1;
}

void kuangfeng(object me, object target)
{
        int i;
        object weapon;
        
        if (!me) return;
        weapon= me->query_temp("weapon");
       
        if (me->is_fighting(target) &&
           !me->is_busy()          &&
            me->query("jingli") > 300 &&
            me->query("neili") > 500 &&
           objectp(target) && 
           !target->is_ghost() &&
           !me->is_ghost() && 
           me->query_temp("hsj_kf")<10 &&
           environment(me) == environment(target) &&
           weapon &&
           weapon->query("skill_type") == "sword"  
            ) {
          message_vision(HIG"�Թ�����ֻ���������ˣ����ϡ����ϱ�����ε��������ۣ����������ĺ��ˡ�\n"NOR, me);
          for (i = 0; i < 3; i++) {
           if (me->is_fighting(target)) {
            if (me->query("gender") == "����")
               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
            else
               COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
          }}
          me->add("neili", -200-random(50));
          me->add("jingli", -100-random(30));
          me->add_temp("hsj_kf",1);
          call_out("kuangfeng", 2, me, target);
          return;
        }
        message_vision(HIG"$N�ġ����콣��ίʵ�켫��һ�������Ƭ�̼����ʹ�ꡣ\n"NOR, me);
        me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/10);
        me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/6);
        me->delete_temp("hsj_kf");
        me->start_busy(3+random(3));
        me->start_perform(2+random(3));
}

