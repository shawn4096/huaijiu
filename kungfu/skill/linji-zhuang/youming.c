// youming.c

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{       

        int nh=me->query_skill("linji-zhuang", 1);
        nh = nh/2;
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
             return notify_fail("����ڤ���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if((int)me->query_skill("linji-zhuang", 1) < 180)
             return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if((int)me->query("neili") < 1000 )
             return notify_fail("�������������\n");
        
        if( me->query_temp("yun_youming")   )
             return notify_fail("�����������ټ�ʮ��ׯ�ġ���ڤ���־���\n");

        tell_object(me,MAG"��Ǳ���ټ�ʮ��ׯ�ġ���ڤ���־�������\n"NOR);
        if( nh > 150 ) nh = 150 + (nh - 150)/10;
        me->set_temp("yun_youming", nh);  
        me->add("neili", - nh*3);
        me->add_temp("apply/armor",nh);
        if(random(me->query_skill("force")) > target->query_skill("force")/3 ) {
        message_vision(HIW"$N��ɫͻȻ�����ɭ�ɲ���$n��Ȼ�亹ֱð��\n"NOR, me, target);
           me->apply_condition("no_perform",nh/30);
           me->apply_condition("no_exert",nh/30);
           target->apply_condition("no_perform",nh/30);
           target->apply_condition("no_exert",nh/30);
        }
        me->start_perform(3,"����ڤ���־�");
        me->start_exert(3,"����ڤ���־�");
        call_out("remove_effect", 1, me, target, nh);
        return 1;
}

void remove_effect(object me,object target,int count)
{
        int i;
        if( !me ) return;
        if( !target
         || ! me->is_fighting("target")
         || count < 1){
          i = me->query_temp("yun_youming");
          me->add_temp("apply/armor",-i);
          me->delete_temp("yun_youming");
          message_vision(HIR"$Nɢȥ�ˡ���ڤ���ķ����ָ���������\n"NOR, me);
          return;
        }
        call_out("remove_effect", 1, me, count - 1);
}
