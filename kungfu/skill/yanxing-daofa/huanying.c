// huanying.c
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;
        if( !target ) target = offensive_target(me);

        if(!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "blade")
            return notify_fail("��ʹ�õ��������ԡ�\n");

        if( !target
         || !me->is_fighting(target) )
            return notify_fail("����Ӱ��ֻ����ս���жԶ���ʹ�á�\n");

        if((int)me->query_skill("linji-zhuang", 1) < 100 )
            return notify_fail("����ټ�ʮ��ׯ�ȼ����������ܺ�����Ӱ��\n");       

        if(me->query_skill_mapped("force") != "linji-zhuang")
            return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if((int)me->query_skill("yanxing-daofa", 1) < 100 )
            return notify_fail("������е����ȼ����������ܺ�����꣡\n");    

        if((int)me->query_skill("blade", 1) < 100 )
            return notify_fail("��Ļ���������������죬���ܺ�������Ļ�Ӱ��\n");    

        if( me->query_skill_mapped("blade") != "yanxing-daofa"
         || me->query_skill_mapped("parry") != "yanxing-daofa")
            return notify_fail("�������޷���������Ӱ���й�����\n"); 

        if((int)me->query("neili") < 300 )
            return notify_fail("����������̫�������ܺ�����Ӱ��\n");

        if((int)me->query("max_neili") < 1000 )
            return notify_fail("����������̫�������ܺ�����Ӱ��\n");

        if ((int)me->query_temp("��Ӱ", 1) ) 
            return notify_fail("���Ѿ����������Լ��Ļ�Ӱ��\n");
    
        message_vision(HIY"$Nǰ�����ߣ��������������иֵ�ԽʹԽ�죬�����������⻯���������Ρ�\n"+
                          "$n�������е���֮�����λ�Ӱ�����Ի������޴룬��֪�ĸ�$N���棬�ĸ��Ǽ١�\n"NOR, me, target);
        me->start_busy(2);
        me->add("neili", -(int)me->query_skill("yanxing-daofa", 1) *3/2);    
        skill = me->query_skill("yanxing-daofa", 1)/3;
        me->set_temp("��Ӱ", 1);
        me->start_perform(3,"�����λ�Ӱ��");
        call_out("remove_effect", 1, me, target, weapon, skill+1);
        return 1;
}

void remove_effect(object me,object target,object weapon, int count)
{
        if(! me) return;
        if( !target
         || !me->is_fighting(target)
         || me->query_skill_mapped("blade") != "yanxing-daofa"
         || !weapon
         || me->query_temp("weapon") != weapon
         || count < 1){
           message_vision("�Ǹ�"HIY"��Ӱ"NOR"�ڰ���ǻ���һ�󣬾���ʧ�ڵص��ˣ�\n", me);
           me->delete_temp("��Ӱ");
           return;
        }
        else {
          call_out("remove_effect", 1, me, target, weapon, count -1);
          me->start_perform(1,"�����λ�Ӱ��");
        }
}
