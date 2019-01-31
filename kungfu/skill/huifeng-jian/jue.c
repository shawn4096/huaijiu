#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        object weapon;
        string msg;
        int i;

        weapon = me->query_temp("weapon");

        if(!me->is_fighting() )
                return notify_fail("����ֻ���ڶ�ս����ʹ�á�\n");

        if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽����������á��������ķ�����\n");

        if( (int)me->query_skill("linji-zhuang",1) < 150 )
                return notify_fail("����ټ�ʮ��ׯ�������ʹ����������\n");  

        if( me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("�����ڲ���ʹ�á��������ķ���\n");

        if( (int)me->query_skill("huifeng-jian",1) < 150 )
                return notify_fail("��Ļط�������������ʹ����������\n");  

        if( me->query_temp("huifeng/jue"))
                return notify_fail("���Ѿ���ʹ���ˡ�\n");
 
        if(me->query_temp("emei/parry"))
            return notify_fail("������ʹ�����컯����\n");
 
        if( (int)me->query("jingli", 1) < 500 )
                return notify_fail("�����ھ���������\n");

        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("����������������\n");

        me->start_perform(3,"��������");
        msg = HIW"$N����һ��������������ټ�ʮ��ׯʹ������������";
        me->add("neili", -200+random(100));
        me->add("jingli", -100);
        me->start_busy(1+random(2));
        i = me->query_skill("linji-zhuang",1) + me->query_skill("huifeng-jian", 1);
        i /= 10;
        me->add_temp("apply/parry", i);
        me->add_temp("apply/dodge", i);
        me->set_temp("huifeng/jue", i);
// �𡢾��������
        if (me->query_temp("huifeng/mie"))
        {
               msg += "�𽣡�����������ϣ�����������\n"NOR;
               me->add_temp("apply/damage",i/2);
               me->add_temp("apply/defence", i/2);
               me->set_temp("huifeng/miejue",i);
        }
        else msg +="\n"NOR;
        message_vision(msg, me);
        call_out("check_fight", 1, me, weapon, i);
        call_out("remove_effect", (int)me->query_skill("linji-zhuang",1)/4, me, i);
        return 1;
}

void remove_effect(object me, int i)
{
        if (!objectp(me)) return;
        if( !me->query_temp("huifeng/jue")) return;
        me->delete_temp("huifeng/jue", 1);
        me->add_temp("apply/parry", -i);
        me->add_temp("apply/dodge", -i);
        if (me->query_temp("huifeng/miejue")){
               me->add_temp("apply/damage",-(i/2));
               me->add_temp("apply/defence", -(i/2));
               me->delete_temp("huifeng/miejue");
        }
        message_vision(HIW"$N����������ʹ��ϣ��ָ���ƽ���Ĺ�����\n"NOR, me);
}

void check_fight(object me,object weapon,int i)
{
        if(!me) return;
        if(!me->query_temp("huifeng/jue")) return;
        if(!me->is_fighting()
         || me->query_skill_mapped("sword") !="huifeng-jian"
         ||! weapon
         || weapon->query("skill_type") != "sword"){
            me->delete_temp("huifeng/jue", 1);
            me->add_temp("apply/parry", -i);
            me->add_temp("apply/dodge", -i);
            if (me->query_temp("huifeng/miejue")) {
               me->add_temp("apply/damage",-(i/2));
               me->add_temp("apply/defence", -(i/2));
               me->delete_temp("huifeng/miejue");
            }
            return;
        }
        call_out("check_fight", 1, me, weapon, i);
}
