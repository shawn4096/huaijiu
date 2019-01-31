// modified by darken@SJ

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i, focus;
        string str;
        
        focus = me->query_temp("ss/focus");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("���蹥��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("songshan-jian", 1) < 100 )
                return notify_fail("�����ɽ��������̫ǳ���޷�ʹ�÷��蹥����\n");

        if( (int)me->query_skill("sword", 1) < 100 )
                return notify_fail("��Ļ�����������̫ǳ���޷�ʹ�÷��蹥����\n");

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 100 )
                return notify_fail("����ڹ�����̫ǳ���޷�ʹ�÷��蹥����\n");
                
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("�������̫ǳ���޷�ʹ�÷��蹥����\n");

        if( (int)me->query("neili") < 400 )
                return notify_fail("����������㣬�޷�ʹ�÷��蹥����\n");

        if (me->query_skill_mapped("force") != "hanbing-zhenqi")
                return notify_fail("����ʲôΪ������ʹ��ɽ������ô?\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "songshan-jian")
                return notify_fail("��ʹ������ɽ������ô?\n");

        me->add("neili", -200);
        me->add("jingli", -40);
        me->start_perform(4,"����");
        message_vision(BLU"$N��Хһ�����ٽ�ͦ�̣��ڰ���л����������⣬����������������������$n��Ϯ��ȥ��\n" NOR,me,target);
        me->add_temp("apply/attack", me->query_skill("sword")/5 + 10*focus);
        me->add_temp("apply/damage", me->query_skill("sword")/6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);        
        if(me->is_fighting(target) && me->query_skill("songshan-jian",1) > 120 && me->query_skill("sword",1) > 120
        && me->query_skill("hanbing-zhenqi",1) > 120) {
             if(stringp(str = me->query_skill_mapped("hand"))
                && me->query_skill_prepared("hand") == str
                && str == "songyang-shou"
                && me->query_skill(str, 1) >= 180) {
                       weapon->unequip(); 
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                       weapon->wield();
                } else{
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                        me->start_busy(1+random(3));
                }
        }
        me->add_temp("apply/attack", -me->query_skill("sword")/5 - 10*focus);
        me->add_temp("apply/damage", -me->query_skill("sword")/6);   
        me->set_temp("ss_feiwu", 1);      
        i = (int)me->query_skill("sword")/30;
        if (i > 8) i = 8;
        if (!me->is_busy()) me->start_busy(1);
 
        return 1;
}

