//perform ku,���١��ִ�
//14/02/99

#include <ansi.h>

void check_fight(object me);
int exert(object me)
{
      if(! me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ�á��١��ִ󷨡�\n");

      if( (int)me->query_skill("kurong-changong", 1) < 140 )
                return notify_fail("��Ŀ���������Ϊ�������޷�ʹ�á��١��ִ󷨣�\n");

      if (me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("�����ڹ��С��١��ִ���\n");

/*      if (me->query_skill_mapped("strike") != "kurong-changong"
       || me->query_skill_prepared("strike") != "kurong-changong")
                return notify_fail("������ÿ���������Ϊ�Ʒ�������ʹ�á��١��ִ󷨡�\n");
      
      if (me->query_skill_mapped("parry") != "kurong-changong")
                return notify_fail("������ÿ���������Ϊ�мܣ�����ʹ�á��١��ִ󷨡�\n"); */

      if( (int)me->query_str() < 30 )
                return notify_fail("��ı���̫�ͣ������޷�ʹ�á��١��ִ󷨣�\n");
 
      if( (int)me->query("neili") < 600 )
                return notify_fail("�������̫���ˣ��޷�ʹ�ó����١��ִ󷨣�\n");   
    
      if( (int)me->query("max_neili") < 2000 )
                return notify_fail("���������Ϊ��ô�����ʹ�á��١��ִ󷨣�\n");   
                                                                                
      if( me->query_temp("pf_rong"))
                return notify_fail("���������á��١��ִ󷨣�\n"); 

      if( me->query_temp("pf_ku"))
                return notify_fail("���������á��ݡ��ִ󷨣�\n");

       message_vision(HIR"\n$N����һ�����������١��ִ�,�����ɻ�����,��ʼ��ת������˫������ɢ���Ź�â��\n\n" NOR, me);
       me->start_busy(1);
       me->set_temp("pf_rong",me->query_skill("kurong-changong",1)/3); 
       me->add_temp("apply/parry",me->query_skill("kurong-changong",1)/4);
       me->add_temp("apply/dodge", me->query_skill("kurong-changong",1)/5);
       me->add("neili", -200 + random(200));
       call_out("check_fight", 1, me);
       return 1;
}

void check_fight(object me)
{
       int i;
       if ( !me || !me->query_temp("pf_rong")) return;
       if( ! me->is_fighting() ){
           i = me->query_temp("pf_rong");
           me->delete_temp("pf_rong");
          me->add_temp("apply/parry", -(me->query_skill("kurong-changong",1)/4));
       me->add_temp("apply/dodge", -(me->query_skill("kurong-changong",1)/5));
           message_vision(WHT"\n$N�������������һ������ɢȥ��������˫�ֵ�������\n"NOR, me);
           return;
       }
       call_out("check_fight", 1, me);
}
