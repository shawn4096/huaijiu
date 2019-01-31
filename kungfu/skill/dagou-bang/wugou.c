#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon = me->query_temp("weapon");
        object *ob;
        int i, skill, bang_jue,damage;

        if( !target ) target = offensive_target(me);
        if (!weapon || weapon->query("skill_type") != "stick"
        || me->query_skill_mapped("stick") != "dagou-bang")
                return notify_fail("�������޷�ʹ�������޹�������\n");

        if( !me->is_fighting())
                return notify_fail("������û����ս���У�\n");                          

        if( me->query("gender") == "����")
                return notify_fail("��һ�����в�Ů֮��������������޹���\n");

        if( (int)me->query("con") < 20 )
                return notify_fail("̫�ź���! ���������ʲ���, �Ⱳ������ʹ�������޹���\n");

        if( (int)me->query("max_neili") < 2000 )
                return notify_fail("���������ۺ���ʹ�������޹�������\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("������û���㹻������ʹ�������޹���\n");

        if ((int)me->query("jingli") < 100)
                return notify_fail("������û���㹻�ľ���ʹ�������޹���\n");

        if( (int)me->query_skill("dagou-bang", 1) < 120 )
                return notify_fail("��Ĵ򹷰�����û���������޹�ʹ��������\n");

        if( (int)me->query_skill("bangjue", 1) < 100 )
                return notify_fail("��Ծ����ķ�����ỹ����, �޷������޹���\n");

        if( environment(me)->query("no_fight") )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        skill = me->query_skill("dagou-bang", 1);
        bang_jue=me->query_skill("bangjue",1);

        me->add("neili", -500);
        me->receive_damage("jingli", 100);

        me->start_busy(2);
        message_vision(HIY "$Nʹ���������޹����ĵ����䣬ɲʱ����˷��ǰ�����\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( !living(ob[i]) || ob[i]==me ) continue;
                if( !ob[i]->is_fighting(me)) continue;
                if (userp(ob[i]) && me->query_condition("killer") > 100) continue;
                if(strsrch(file_name(environment(me)),"/d/wuguan/") >= 0 && !ob[i]->query_condition("killer")) continue;
                if (random(me->query("combat_exp",1)) > (ob[i]->query("combat_exp",1))/3
            && random(bang_jue) > (ob[i]->query_dex() )){
                        damage = skill * (int)me->query("combat_exp") / (int)ob[i]->query("combat_exp");
                        damage = damage / 2 + (random(damage)+(1+random(bang_jue/10))*(bang_jue/2));
                        damage = damage / 2 + random(damage);
                        if( damage > 1500 ) damage = 1501;
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_damage("neili", damage/2 , me);
                        tell_object(ob[i], "�������ǰһ����꣬���˲����¡�\n");       
    target->start_busy( 2+random(3));         
target->receive_wound("qi",damage/3,me);
                        if( !ob[i]->is_killing(me->query("id")) ) me->kill_ob(ob[i]);
                }
                else  message_vision( "$n��æ�������ӳ�$N�������֮�⡣\n",me,ob[i]);
                me->start_busy(random(2)+ 2); 
        }
       me->start_perform(6,"�������޹���");
        return 1;
}
