//    /kungfu/skill/xingyi-zhang/daoying.c pfm daoying
// by leontt /22/6/2000

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j = me->query_skill("murong-daofa", 1)/3+me->query_skill("xingyi-zhang",1)/4;
        object weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");                

        if( (int)me->query_skill("shenyuan-gong", 1) < 100 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�õ�Ӱ�ƣ�\n");    

        if( (int)me->query_skill("murong-daofa", 1) < 100 )
                return notify_fail("��ĵ�����δ���ɣ�����ʹ�õ�Ӱ�ƣ�\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("������û�е����޷�ʹ�õ�Ӱ�ƣ�\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 100 )
                return notify_fail("����Ʒ���δ���ɣ�����ʹ�õ�Ӱ�ƣ�\n");  

        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("����ڹ�������Ԫ�����޷�ʹ�õ�Ӱ�ƣ�\n");      

        if(me->query_skill_mapped("strike") != "xingyi-zhang" 
         || me->query_skill_prepared("strike") != "xingyi-zhang")
                return notify_fail("��û�����ƣ��޷�ʹ�õ�Ӱ�ƣ�\n");

        if(me->query_skill_mapped("parry") != "xingyi-zhang")
         if(me->query_skill_mapped("parry") != "murong-daofa")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�õ�Ӱ�ƣ�\n");

        if((int)me->query("max_neili") < 1200 )
                return notify_fail("������������Ϊ����������ʹ�õ�Ӱ�ƣ�\n");      

        if((int)me->query("neili") < 600 )
                return notify_fail("�������������㣬����ʹ�õ�Ӱ�ƣ�\n");      

        if((int)me->query_skill("blade", 1) < 100 )
                return notify_fail("��Ļ�������������죬�����ڵ����м���ʹ�õ�Ӱ�ơ�\n");

        if((int)me->query_skill("strike", 1) < 100 )
                return notify_fail("��Ļ����Ʒ�������죬�����ڵ����м���ʹ�õ�Ӱ�ơ�\n");     

        message_vision(HIR"\n$N���һ��ʹ��Ľ�ݾ�������Ӱ�ơ���ֻ��$P���浶�ߣ�ƬƬ�����м����������Ʒ�һ����$n��\n"NOR, me,target);
        me->add("neili", -200); 
        me->add("jingli", -50);
        me->start_perform(4,"��Ӱ��");  
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/dodge",j);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
                weapon->wield(); 
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
                weapon->wield();
        }
        if(objectp(target) && me->is_fighting(target) && random((int)me->query_str()) > 30)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        me->add_temp("apply/dodge",-j);
        me->add_temp("apply/attack", -j);
        me->start_busy(2+random(2));
        me->start_perform(2+random(2),"��Ӱ��");
        return 1;
}

