// shuangjue.c It's a "pfm" .
// by Looklove@SJ 2001/2/14 ...���˽�

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int b, z;
        object weapon;
        b = me->query_skill("dagou-bang", 1)/2;
        z = me->query_skill("xianglong-zhang", 1)/2;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("������˫����ֻ����ս���жԶ���ʹ�á�\n");

        if(!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "stick")
                return notify_fail("������û�а����޷�ʹ�ð���˫����\n");

        if( me->query_temp("shuangjue"))
                return notify_fail("������ʹ�á�����˫����������\n");
        
        if( me->query_skill("dagou-bang", 1) < 350 )
                return notify_fail("��Ĵ򹷰�����������죬ʹ����������˫����������\n");

        if( (int)me->query_skill("xianglong-zhang", 1) < 350 )
                return notify_fail("��Ľ����ƻ�δ���ɣ�����ʹ�ð���˫����\n");    

        if( me->query_skill_mapped("force") != "huntian-qigong"
          || (int)me->query_skill("huntian-qigong", 1) < 350 )
                return notify_fail("��Ļ���������û��ѧ�ɣ��޷�ʹ�ð���˫����\n");

        if( (int)me->query_skill("force") < 350 )
                return notify_fail("����ڹ��ȼ�������ʹ����������˫����������\n");

        if( me->query_skill_mapped("parry") != "dagou-bang")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�ð���˫����\n");
                
        if( me->query_skill_mapped("strike") != "xianglong-zhang" 
         || me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("��û���ý����ƣ��޷�ʹ�ð���˫����\n");

        if( (int)me->query("max_neili") < 8000 )
                return notify_fail("����������̫����ʹ����������˫������\n");      

        if( (int)me->query("neili") < 2000 )
                return notify_fail("����������̫����ʹ����������˫������\n");

        if( me->query("gender")=="Ů��")
        msg = HIG"$N��ȻбŲһ�����������һ�����ƽݵ�Ц�����˸о���Ҫʹ�������ɵ��������⡣\n"NOR;
        else msg = HIW"$N����ͻ�䣬���������Ȼһ����Х�����������Ӱ��$n���ϴ�ȥ��\n"NOR;

        me->start_perform(4,"������˫����");
        me->add_temp("apply/attack", b/2); 
        me->add_temp("apply/damage", z/2);
        me->set_temp("shuangjue", 1);

        message_vision(msg, me, target);

        if (target->is_busy()){
                msg = HIR"$n��ǰһ�����ֱ治��$N��������ֻ��ͷƤ���飬ԽսԽ�ǵ��ӡ�\n"NOR;
                message_vision(msg, me, target);
        }
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->add("jingli", -10); 

        if( me->query("gender")=="Ů��")
        msg = HIY"$Nһ����Х������������$nһ����ȴ����Ρ�����$N���в��ƣ�ɲ�Ǽ��ĵ���\n"NOR;
        else msg = HIY"$N���Ȱ������ϣ������ϲ������һ������Ȼһ���ĳ����˵��Ǹɾ����䡣\n"NOR;
        weapon->unequip(); 
        message_vision(msg, me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->add("neili", -100); 
        me->add("jingli", -10);

        weapon->wield();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        me->add("jingli", -10);

        if(random(me->query_skill("dodge")) > target->query_skill("dodge")/2)
        {          
                if( me->query("gender")=="Ů��")
                msg = HIW"��Ӱһ�գ�$nֻ�����ۻ����ң�ֻ��$Nһ�����ȣ����������ģ�����!\n"NOR;
                else msg = HIW"ֻ��$N��һ��������ǰ��������ͻȻ���У��������Ю���Ʒ���$n��ȥ��\n"NOR;
                weapon->unequip();
                message_vision(msg, me, target);
                me->add_temp("apply/damage", 50);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                me->add("neili", -100); 
                me->add("jingli", -5);
                
                weapon->wield();
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                me->delete_temp("sj");
                me->add("neili", -100);
                me->add("jingli", -5);
                me->add_temp("apply/damage", -50);
        }

        me->add_temp("apply/attack", -b/2);
        me->add_temp("apply/damage", -z/2);
        me->delete_temp("shuangjue", 1);
        me->start_busy(1+random(2));
        return 1;
}

