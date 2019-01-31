#include <ansi.h>
inherit F_SSERVER;
int check_fight(object me);

int perform(object me, object target)
{
        if(!me->is_fighting())
                return notify_fail("��û��ս�����أ�\n");

        if(!target) target = offensive_target(me);

        if(me->query_skill("qiankun-danuoyi", 1) < 210 )
                return notify_fail("���Ǭ����Ų�ƻ�δ�������߲㡣\n");

        if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("��û��ʹ��Ǭ����Ų����Ϊ�мܣ�\n");

        if((int)me->query("neili") > me->query("max_neili"))
                return notify_fail("��Ŀǰ������̫ǿ���޷�ʹ�û��־���\n");

        if((int)me->query("jiali") >= 10)
                return notify_fail("��Ŀǰ�ļ���̫�أ��޷�ʹ�û��־���\n");

        if((int)me->query_temp("qkdny/hua") )
                return notify_fail("������ʩչ�������־��أ�\n");

        if((int)me->query_temp("qkdny/yi") )
                return notify_fail("������ʩչ���ơ��־��أ�\n");

        if((int)me->query_temp("qkdny/xu") )
                return notify_fail("������ʩչ����־��أ�\n");

        if((int)me->query_temp("qkdny/yin") )
                return notify_fail("������ʩչ�������־��أ�\n");

        me->add("neili", -100-random(100));
        tell_object(me,HIW"����������˿���������������Ỻ����\n"NOR);
        me->set_temp("qkdny/hua", 1);
        target->apply_condition("no_perform",random(3)+1);
        check_fight(me); 
        return 1;
}

int check_fight(object me)
{    
        if (!me || !me->query_temp("qkdny/hua")) return 0;

        if(me->is_ghost() || !living(me))
            me->delete_temp("qkdny/hua");
        
        if(!me->is_fighting() 
         || me->query("jiali") > 9 
         || me->query("jingli") < 500
         || me->query("jing")<500){
           tell_object(me, HIW"\n��������ָ���ƽ����\n"NOR);
           me->delete_temp("qkdny/hua");
        }
        else call_out("check_fight", 1, me);
        return 1;
}
