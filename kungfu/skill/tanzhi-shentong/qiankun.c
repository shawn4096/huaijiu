inherit F_SSERVER;
#include <ansi.h>
int perform(object me, object target)
{
        string msg;
        int neili, qi;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("��Ǭ��һָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 150 )
                return notify_fail("��ı̺���������Ϊδ�����޷�ʹ��Ǭ��һָ��\n");
        if( (int)me->query_skill("suibo-zhuliu", 1) < 150 )
                return notify_fail("����沨������Ϊδ�����޷�ʹ��Ǭ��һָ��\n");
        if( (int)me->query_skill("tanzhi-shentong", 1) < 150 )
                return notify_fail("��ĵ�ָ��ͨ��Ϊδ�����޷�ʹ��Ǭ��һָ��\n");
        if( (int)me->query_skill("finger",1) < 120 )
                return notify_fail("���ָ����Ϊ���㣬ʹ����Ǭ��һָ��\n");
        if( (int)me->query("neili") < 3000 )
                return notify_fail("����������̫�������ܳ�Ǭ��һָ��\n");
        if (target->query_temp("thd/qiankun"))
                return notify_fail("���Ѿ��������ˣ����Ĺ����ɡ�\n");
                
        me->start_perform(4,"Ǭ��һָ");
        neili = target->query("max_neili");
        qi = target->query("max_qi");
        msg = HIG"\n$N��ָһ�죬һ�ɾ�����֮��$nϮȥ��\n"NOR;
        if (random(me->query("dex") + me->query_skill("dodge", 1)/ 10) > (target->query("dex")+target->query_skill("dodge", 1)/10))
        {
                msg += HIR"$n����һָ���ص�������Ѩ�����̴�С�����Ѩ��Ϣ��Ҳ�޷�˳��ͨ�С�\n"NOR;
                me->start_busy(2);
                target->start_busy(random(4)+1);
                target->set_temp("thd/qiankun",1);
                target->set("max_qi",qi/2);
                target->set("eff_qi",qi/2);
// set for condition
                target->set("qiankun/qi",qi);
                target->set("qiankun/neili",neili);
                if (target->query("qi")>target->query("eff_qi")) 
                       target->set("qi",target->query("eff_qi"));
                target->set("max_neili",neili/2);
                if (target->query("neili")>target->query("max_neili"))
                       target->set("neili",target->query("max_neili"));
                target->apply_condition("qiankun_wound",(int)me->query_skill("finger")/50);
        }
        else {
                me->start_busy(3);
                msg += HIY"$n���ΰ�����$N��ͷһ�㣬����������һ�С�\n"NOR;
        }
        me->add("neili",-(300+random(100)));
        message_vision(msg, me, target);
        return 1;
}

