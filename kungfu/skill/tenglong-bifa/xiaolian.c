// guifei С�����
// created by olives@SJ
/*
     ��������Դ��������Լ��ؿ����䣬���˼ܾ��е�һ����Ȼ��գ���˳����
����һ����ڽ����������������ذ�׵����ֳ�ȭ������һȭ���ڽ������ģ�
ֻ�ǽ������ϡ���������ԵУ���һ����Ȼ�����˵��˱��ġ�ΤС���ִ��һ��
�����ã���

*/
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me, object target)
{
        object weapon;
        string msg;
        int lvl;

        if(!target) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("��С����¡�ֻ����ս��ʱʹ�ã�\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("��С����¡�ֻ�а��˽���������ã�\n");

        if(!objectp(weapon=me->query_temp("weapon"))
        || weapon->query("skill_type") != "dagger")
             return notify_fail("������û��ذ�ף����ʹ�á�С����¡���\n");
        
        if((int)(me->query("dex")+me->query_skill("dodge",1)/10) < 30 )
                return notify_fail("����������ʹ�á�С����¡������»��˵��Լ���\n");

        if((int)me->query_skill("tenglong-bifa", 1) < 150 )
                return notify_fail("�������ذ������������������ʹ�á�С����¡���\n");

        if((int)me->query_skill("huagu-mianzhang",1) < 150)
                return notify_fail("��Ļ������Ʋ�������������ʹ�á�С����¡���\n");

        if(me->query_skill_mapped("strike") != "huagu-mianzhang"
        || me->query_skill_prepared("strike") != "huagu-mianzhang")
                return notify_fail("������û������׼�����޷�ʹ�á�С����¡���\n");

        
        if(me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("ֻ��ʹ������ذ��ʱ����ʹ�á�С����¡���\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 150 )
                return notify_fail("��Ķ����󷨹������㣬�����á�С����¡���\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á�С����¡���\n");

        if((int)me->query("neili", 1) < 1500)
                return notify_fail("�������������㣬����ʹ�á�С����¡���\n");

        if(me->query("gender") == "����" )
                return notify_fail("����Ů����ô��ʹ�á�С����¡��أ�\n");

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ�������໥�ִ�������ʹ�á�С����¡���\n");

        msg = HIR"$N��$n��������֮����ƴ��ȫ��ʹ���շ��˲���֮����������С����¡�"NOR;
        msg +=MAG "\n$Nʹ��һ�С�С����¡����Դ�������Լ��ؿ����䣬˳���ڵ���һ��������\n��$n������������ű��������ֳ�ȭ��$n�����������¡�\n"NOR;
        lvl = me->query_skill("tenglong-bifa",1)/5;
        message_vision(msg,me,target);
        me->receive_damage("jingli",100);
        me->receive_damage("neili",300);
        me->add_temp("apply/attack",lvl*2);
        me->add_temp("apply/damage",lvl);
        me->set_temp("sld/pfm/xiaolian",1);
        COMBAT_D->do_attack(me,target,weapon,3);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip();
                COMBAT_D->do_attack(me,target,0,1);
                weapon->wield();
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me,target,weapon,1);
        if(objectp(target) && me->is_fighting(target))
        {
                if(random(me->query("combat_exp"))>target->query("combat_exp")/2)
                        COMBAT_D->do_attack(me,target,weapon,3);
                else
                        COMBAT_D->do_attack(me,target,weapon,1);
        }
        me->delete_temp("sld/pfm/xiaolian");
        me->add_temp("apply/attack",-lvl*2);
        me->add_temp("apply/damage",-lvl);

        me->start_busy(1+random(2));
        me->start_perform(2+random(2),"��С����¡�");
        return 1;
}

