// longxiang.c ��������
//by xiaoyao 4/19/2k

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i, j, focus;
        object weapon;
        i = 1;
        j = me->query_skill("sword")/10;

        if(me->query("ss/pass_deng")) {
              j = me->query_skill("sword")/8;
              i = 3;
        }

        focus = me->query_temp("ss/focus") + 1;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("���������衹ֻ����ս���жԶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("�����ʹ�ý�����ʹ�á��������衹��\n");

        if(me->query_skill("songshan-jian", 1) < 180 )
                return notify_fail("�����ɽ������������죬ʹ�������������衹������\n");

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 180 )
                return notify_fail("��ĺ������������ߣ��޷�ʹ�á��������衹��\n");        

        if( (int)me->query_skill("force") < 150 )
                return notify_fail("����ڹ��ȼ�������ʹ�������������衹������\n");

        if( (int)me->query_str() < 31)
                return notify_fail("�������������ǿ����ʹ�������������衹������\n");

        if (me->query_skill_prepared("hand") != "songyang-shou"
        || me->query_skill_mapped("hand") != "songyang-shou")
                return notify_fail("���������衹��Ҫ�ô������ָ�����\n");

        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("����������̫����ʹ�������������衹��\n");      

        if( (int)me->query("neili") < 900 )
                return notify_fail("����������̫����ʹ�������������衹��\n");

        msg = HIR"\n$N�������Ĵָ��ʳָ����ָ������ָ����ס�˽��⣬����һ�ɣ�����ͻȻ���𣬽�����ǰ����ס�ػζ���\nͻȻ$N����$n���ٹ������˽���һ������һ�������ڿն����԰���к��������������ֱ��ٿ������$n��\n\n"NOR;

        me->add_temp("apply/attack", j+focus*10);
        me->add_temp("apply/damage", j/3+5*focus);
        message_vision(msg, me, target);

        if(me->query("ss/pass_deng")) message_vision(HIY"\n$N����֪��ɽ�����ľ������ڣ��������ߣ���ʱ��ʽ������\n"NOR, me);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);       

        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

        weapon->wield();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);

        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
        me->add("neili", -150);  
        me->add("jingli", -50);
        message_vision(HIR"                                                                   ����  "HIC"��"NOR  HIR"  ����\n"NOR,me);        
        weapon->wield();
        if(random(me->query_skill("songshan-jian",)) > 200 ){
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add("neili", -150);
        me->add("jingli", -50);
          }
        me->add_temp("apply/damage", -j/3-5*focus);
        me->add_temp("apply/attack", -j-focus*10);
        me->start_busy(1+random(2));
        target->start_busy(2);
        me->start_perform(5,"���������衹");
        return 1;
}

