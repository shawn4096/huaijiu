// pikong.c By Darken
// Modified by Numa@Sj 99-11-12 2:46

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int perform(object me, object target)
{
        int damage, p;
        string msg;
        
        if( !target ) target = offensive_target(me);
        if(!objectp(target)) return notify_fail("������˭��\n");
        if (wiz_level(me) < wiz_level(target))
                return notify_fail("�㲻�ܹ�����ʦ�ȼ�����ߵĶ��֡�\n");
        if(target==me)
                return notify_fail("�� suicide -f ָ���ȽϿ�Щ��\n");
        if( !target
            || !target->is_character())
                return notify_fail("���빥��˭��\n");


        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�������ƣ�\n");   
        if( environment(me)->query("no_fight") )
                return notify_fail("���ﲻ��ս����\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 150 )
                return notify_fail("��ı̺���������Ϊδ�����޷���������ơ�\n");
        if( (int)me->query_skill("luoying-zhang",1) < 120 )
                return notify_fail("����Ʒ���Ϊ���㣬ʹ���������ơ�\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫�������ܴ�������ơ�\n");
        if( (int)me->query("jiali") < 100 )
                return notify_fail("�����ڼ���̫�������ܴ�������ơ�\n");
        if (me->query_skill_prepared("strike") != "luoying-zhang"
            || me->query_skill_mapped("strike") != "luoying-zhang")
                return notify_fail("�������޷�ʹ�������ƽ��й�����\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("��ı̺���������Ϊ�������޷�ʹ�������ƽ��й�����\n");
                
        me->start_perform(4,"������");
        msg = HIB "\n$N��Хһ����һʽ��������$n��������Ӣ���Ʒ�Ю����������ӿ�ı̺���������ӵ�����������ⲻ�ɵ���\n"NOR;
        if (random(me->query_skill("dodge")*2) > target->query_skill("dodge")
        && me->query("combat_exp") > random(target->query("combat_exp")/2))
        {
                me->start_busy(1);
                target->start_busy(random(4));
                damage = (int)me->query_skill("bihai-chaosheng", 1) + (int)me->query_skill("luoying-zhang", 1);
                damage += random(me->query("jiali") * 8);
                damage *= 2;
                if(target->query("neili") > me->query("neili")) damage /= 2;

                if (damage > 1500) damage = 1500;  

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili", -damage/2);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HIG"������صĴ���$n���ؿڣ�$n��ʱ��Ѫ���硣\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
          me->kill_ob(target);   
     target->kill_ob(me);
        }
        else {
                me->start_busy(2);
                msg += CYN"$n���������ң���æ����һ�ã�$N��һ�Ʊ㼴��ա�\n"NOR;
        }
        message_vision(msg, me, target);
        return 1;
}
