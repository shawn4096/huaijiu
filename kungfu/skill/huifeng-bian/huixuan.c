
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void do_huixuan(object me, object target, object weapon, int times);

int perform(object me, object target)
{
        string msg;
        object weapon;
        int time,exp;

       if( !target ) target = offensive_target(me);


      weapon = me->query_temp("weapon");
	if( !target || !target->is_character() || !me->is_fighting(target) )
       return notify_fail("[����ʮ��ʽ]ֻ����ս����ʹ�á�\n");
       if (me->is_busy())
       return notify_fail("����æ���ء�\n");
      if (!weapon || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "huifeng-bian")
          return notify_fail("������û�бޣ��޷�ʹ�á�����ʮ��ʽ����\n");             
        if( !target || !target->is_character()|| !me->is_fighting(target) )
       return notify_fail("������ʮ��ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if( (int)me->query_skill("huifeng-bian", 1) < 100 )
                return notify_fail("��Ļط�޷�������죬����ʹ�á�����ʮ��ʽ��������\n");

        if( (int)me->query_skill("huntian-qigong", 1) < 100 )
                return notify_fail("��Ļ�������������񣬲���ʹ�á�����ʮ��ʽ����\n");

        if( (int)me->query("neili")<300)
                return notify_fail("����������̫��������ʹ�á�����ʮ��ʽ����\n");

       if(me->query_skill_mapped("force") != "huntian-qigong")
              return notify_fail("������ʹ�õ��ڹ���ط�޷���ִ�������ʹ�á�����ʮ��ʽ����\n");

        me->add("neili", -200);
        me->set_temp("huixuan",1);
        msg = HIY+"\n$N"+HIY+"ͻȻ���������ݰ㼱ת��Ȧ�����е�"+weapon->query("name")+HIY+"���������ǿ��\n";
		msg+="�Ļ�������������ʮ���ֻû�Ī�����ʽ������$n��\n"NOR;
        message_vision(msg,me,target);
        exp=random(me->query("combat_exp")*16/10);
        if ( exp > random( target->query("combat_exp")))
        {      msg +=HIR+"$nһ��û���񣬱�$N���Ī�����ʽ����,���ڻ����ı�Ӱ�\n"NOR;
                me->start_busy(1);
                target->start_busy(1);
                time = me->query_skill("whip")/40 +1 ;  
             message_vision(msg,me,target);
              me->start_call_out( (: call_other, __FILE__, "do_huixuan", me, target , weapon, time:), 1);
        }
        else {
                msg += CYN+"����$n�������أ����й�ֱ�������ݲ����������ա�\n"NOR;
                me->start_busy(random(8)+1);
              message_vision(msg,me,target);
		}
		return 1;
}

void do_huixuan(object me, object target, object weapon, int times)
{
        int force;
        if(!me->is_fighting(target)) {
       message_vision(HIY+"\n$N"+HIY+"�����Ѿ���"+weapon->query("name")+HIY+"������Ĵ���������\n"NOR,me);
	me->delete_temp("huixuan");	 
         return ;
        }
        if( !living( me ) || me->is_ghost() ) 
       {
         me->delete_temp("huixuan");  
         return;
       }
        if(times<=0) {
       message_vision(HIY+"\n$N"+HIY+"�����Ѿ���"+weapon->query("name")+HIY+"������Ĵ���������\n"NOR,me);
        me->delete_temp("huixuan");	 
                 return ;
        }
      
        force=random(me->query_skill("whip")*13/10);
         if(force  > random(target->query_skill("dodge")) ) {
           if (weapon->query("id")=="po budai")
		   { 
			message_vision( HIR+me->query("name")+"�����е�"+weapon->query("name")+"��$nͷ��һ�֡�\n"NOR,me,target);
            tell_object(target,BLU"���������һ���ʹ�������㱻Ы��ҧ�ˡ�\n"NOR);
			target->receive_wound("qi",me->query_skill("whip",1)/4);
            target->receive_wound("jing",me->query_skill("whip",1)/4);
target->apply_condition("scorpion_poison", 10+target->query_condition("scorpion_poison"));
           }
         	message_vision( HIR"$n"+HIR+"����Ӱ��ȫ�Ի�$N�˻���������\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
                call_out("do_huixuan",4,me,target,weapon,times-1);
        }
        else
       call_out("do_huixuan",3,me,target,weapon,times-1);

}
