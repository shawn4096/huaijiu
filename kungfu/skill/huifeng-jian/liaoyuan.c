// liaoyuan.c ��ԭ�ٻ�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      int lvl;
      object weapon;
      string name;
      weapon = me->query_temp("weapon");
      if (weapon) name = weapon->query("name");

      if( !target ) target = offensive_target(me);
     
      if( !target
       || !me->is_fighting(target) )
           return notify_fail("��ԭ�ٻ�ֻ����ս���жԶ���ʹ�á�\n");

      if (!weapon
       || weapon->query("skill_type") != "sword"
       || me->query_skill_mapped("sword") != "huifeng-jian")
           return notify_fail("������û�н����޷�ʹ����ԭ�ٻ���\n");             

      if( (int)me->query_skill("huifeng-jian",1) < 120 )
           return notify_fail("��Ļط������������죬����ʹ����ԭ�ٻ���\n");
      
      if( (int)me->query_skill("sword",1) < 120 )
           return notify_fail("��Ļ��������ȼ�����������ʹ����ԭ�ٻ���\n");  

      if( (int)me->query_skill("jieshou-jiushi", 1) < 120 )
           return notify_fail("��Ľ��־�ʽ�ȼ�����������ʹ����ԭ�ٻ���\n");
      
      if( (int)me->query_skill("linji-zhuang", 1) < 120 )
           return notify_fail("����ټ�ʮ��ׯ�ȼ�����������ʹ����ԭ�ٻ���\n");

      if (me->query_skill_mapped("force") != "linji-zhuang")
           return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

      if( (int)me->query("max_neili") < 1000 )
           return notify_fail("�������̫��������ʹ����ԭ�ٻ���\n");
      
      if( (int)me->query("neili") < 500 )
           return notify_fail("�������̫���ˣ��޷�ʹ�ó���ԭ�ٻ���\n"); 
   
      if (me->query_skill_prepared("hand") != "jieshou-jiushi"
       || me->query_skill_mapped("hand") != "jieshou-jiushi")
           return notify_fail("�㲻����־�ʽ�������޷�ʹ����ԭ�ٻ����й�����\n");

      lvl = ((int)me->query_skill("huifeng-jian", 1) + (int)me->query_skill("jieshou-jiushi", 1) ) /10;

      message_vision(HIW"\n$N��Хһ�����������߿���ȥ���պ���ס$n��������"+name+HIW"ɲ�Ǽ������ռ䡣\n"NOR, me,target);
      message_vision(HIW"����ʹ�����־�ʽ����������С������������Ȼ��ǿ��\n"NOR, me,target);
      me->add("neili", -350); 
      me->add("jingli", -150);      
      if( !me->query_temp("huifeng")){
        me->add_temp("apply/attack", lvl); 
        me->add_temp("apply/damage", lvl/2);
        me->set_temp("liaoyuan", 1);
      }
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

      if (present(target,environment(me)) && me->is_fighting(target))
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
      weapon->unequip(); 

      if (present(target,environment(me))
       && me->is_fighting(target)
       && me->query_skill("jieshou-jiushi",1) > 150)
      COMBAT_D->do_attack(me, target, 0, 1);  

      if (present(target,environment(me))
       && me->is_fighting(target)
       && random(me->query_skill("jieshou-jiushi", 1)) > 200)
      COMBAT_D->do_attack(me, target, 0, 0);

      if( me->query_temp("liaoyuan")){
        me->add_temp("apply/attack", -lvl);
        me->add_temp("apply/damage", -(lvl/2));
        me->delete_temp("liaoyuan");
      }
      weapon->wield();
      me->start_busy(2);
      me->start_perform(5, "��ԭ�ٻ�");
      return 1;
}
