// wofo.c yizhi-chan perform ����ҷ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	string msg;
	int exp,exp1,busy,lvl,lvl1;

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
	  return notify_fail("������ҷ�ֻ����ս���жԶ���ʹ�á�\n");
	     
      if( objectp(me->query_temp("weapon")) )
	  return notify_fail("��������ʹ�á�����ҷ𡹣�\n");
      
      if( (int)me->query_skill("yizhi-chan",1) < 100 )
	  return notify_fail("���һָ��������죬����ʹ�á�����ҷ𡹣�\n");

      if( (int)me->query_skill("yijin-jing",1) < 100 )
	  return notify_fail("����׽�ڹ��ȼ�����������ʹ�á�����ҷ𡹣�\n");  
      
      if( (int)me->query_str() < 25 )
	  return notify_fail("��ı�������ǿ������ʹ�á�����ҷ𡹣�\n");
      
      if( (int)me->query("max_neili") < 1000 )
	  return notify_fail("�������̫��������ʹ�á�����ҷ𡹣�\n");
      
      if( (int)me->query("neili") < 350 )
	  return notify_fail("�������̫���ˣ��޷�ʹ�ó�������ҷ𡹣�\n");   
										 
      if (me->query_skill_prepared("finger") != "yizhi-chan"
       || me->query_skill_mapped("finger") != "yizhi-chan")
	  return notify_fail("�������޷�ʹ�á�����ҷ𡹽��й�����\n");										 
      if( me->query_temp("wofo"))
	  return notify_fail("������ʹ��һָ�������⹥��������ҷ𡹣�\n");

	if (target->is_busy()) return notify_fail("�Է����Թ˲�Ͼ���ŵ������ɣ�\n");
       
      msg = HIY"$NͻȻ���������գ�������ָ�������͵�һ����һ�ɾ����������������$n�����Ѩ��\n" NOR;
      message_vision(msg, me, target);   
//      me->start_perform(6,"������ҷ�");								
	exp=me->query("combat_exp");
	exp1=target->query("combat_exp");
	lvl=me->query_skill("finger");
	lvl1=target->query_skill("dodge");
	busy=3;
	busy=busy+random(lvl)/100;
	if(busy>4) busy=4;
	if(exp1==0 || lvl1==0) busy=10;
	else if( exp>exp1) busy=busy*exp/100*lvl/(exp1/100*lvl1);
	if(busy>6) busy=6;
	if( wizardp(me)) tell_object(me,sprintf("busy=%d\n",busy));
	if( random(exp/100*lvl)>exp1/100*lvl1/3){
		msg = HIW"$nֻ�е�Ѩ��һ�飬��������ɢ���������á�\n"NOR;
		message_vision(msg, me, target); 
		me->set_temp("wofo",1);  
		me->add("neili", -350);    
		target->start_busy(busy);
		me->start_busy(1+random(2));
		call_out("remove_effect", me->query_skill("yizhi-chan") / 20 + 2, me);
      }
      else {
		msg = HIY"$n����$N����ͼ��һ�������ݵض����$N����һ�У�\n"NOR;	  
		message_vision(msg, me, target);					
		me->start_busy(2+random(3));
		me->add("neili", - 100);
      }
      return 1;
}

void remove_effect(object me)
{
	if (!me) return;
	me->delete_temp("wofo");
	message_vision(HIR"$N�ġ�����ҷ��˹���ϣ���ɫ�ÿ����ˡ�\n"NOR, me);
}
