// Exert: LifeHeal.c
// Date : AHA 97/06/22

#include <ansi.h>

int exert(object me, object target)
{
  string he;

  if(!objectp(target) || 
     (environment(me)!=environment(target)) ||
     !living(target)
    )
    return notify_fail("����û������ˡ�\n");
   
  if(target == me )
     return notify_fail("�������Լ����ˣ������˹��ķ������ԡ�\n");
  
  he = target->name();

  if( me->is_fighting() )
      return notify_fail("ս�����޷���������ˣ�\n");
  if( target->is_fighting() )
      return notify_fail(he+"����ս���У��޷����ˣ�\n");
  if( target->is_busy() )
      return notify_fail(he+"��æ���ء�\n");
  if ((int)me->query_skill("emei-jiuyang", 1) < 30)
      return notify_fail("��ľ�������Ϊ̫�ͣ����Ǻú������ɡ�\n");
  if( (int)me->query("neili") < 50 ) 
      return notify_fail("����������㡣\n");

  if( (int)target->query("eff_qi") >= (int)target->query("max_qi") )
      return notify_fail(he+"���ڲ�û������ѽ��\n");

  if( (int)target->query("eff_qi") < (int)target->query("max_qi") / 3 )
      return notify_fail(
               he+"����̫���ˣ�ֻ��һ�ܵ������𵴱��������Σ�գ�\n");
 
  if(target->query("gender") != "����" &&
     target->query("gender") != me->query("gender") &&
     me->query("class")=="bonze")
       command("say �����ӷ����գ����գ�Ϊ�˾��ˣ�"
               +RANK_D->query_self(me)+"Ҳ�˲�����Ů֮���ˡ�\n");

  write( HIW "���������£�һ�ְ���"+he+"��С������һ�ְ���"+he+"�ĺ�����\n"
             "���������ʼΪ"+he+"���ˡ�\n" NOR);
  message("vision",
     me->name() + HIR"����Խ��Խ�죬"+HIW"ͷ����ʼ���ְ�������Խ��ԽŨ��\n"
           "�𽥽�"+me->name()+"��"+he+"Χ��������\n"NOR     
          + me->name() + "�˹���ϣ�����������һ������"
          +he+"��ɫ������������ࡣ\n",
     environment(me), me);
  
  target->receive_curing("qi", 20 + (int)me->query_skill("force")/5 );
  me->add("neili", -50);
  return 1;
}

�
