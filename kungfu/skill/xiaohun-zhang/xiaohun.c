// xiaohun-zhang perform xiaohun
// by dubei 

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string *pictures = ({"�ľ�����","�������","��������","�����ˮ","�ǻ��չ�","��������","��ʬ����", "ӹ������" });
int perform(object me)
{

      object target;
      string arg,picture;
      int i, j, z;       
     i = me->query_skill("xiaohun-zhang", 1)/2;
     j = me->query_skill("yunu-xinjing", 1)/2; 
     z = me->query_skill("force",1)/2; 
     picture = pictures[random(sizeof(pictures))];
 
 

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
           return notify_fail("�����꡹ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_skill_prepared("strike") != "xiaohun-zhang"
           || me->query_skill_mapped("strike") != "xiaohun-zhang"
                    || me->query_skill_mapped("parry") != "xiaohun-zhang"
                    || me->query_skill_mapped("force") != "yunu-xinjing")
           return notify_fail("����������ʹ�á����꡹������\n"); 

        if(me->query_skill("xiaohun-zhang", 1) < 150 )
                return notify_fail("��������Ʒ���򲻹���ʹ���������꡹������\n");

        if(me->query_skill("strike", 1) < 150 )
                return notify_fail("��Ļ�������������죬ʹ���������꡹������\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("����ڹ��ȼ�������ʹ���������꡹������\n");

 
        if( (int)me->query_str() < 30)
                return notify_fail("�������������ǿ����ʹ���������꡹������\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("�����������Ѹ�ͣ�ʹ���������꡹������\n");
 
       if(me->query_skill("yunu-xinjing", 1) < 150 )   
                return notify_fail("�����Ů�ľ���Ϊ�������޷�ʹ�á����꡹������\n");  

       if(me->query_temp("xhz_xiaohun")) 
       return notify_fail("����������ʹ�á����꡹������\n"); 

       if (me->query("eff_qi")*2 >=me->query("max_qi"))
        return notify_fail("�������ڵ��ľ�����ʹ�÷��ӳ����������\n"); 

        if (me->query("neili") < 800)
        return notify_fail("�������������\n");
        if (me->query("jingli") < 800)
        return notify_fail("��ľ���������\n");
        me->add("neili", -i*2);
        me->add("jingli", -i*2);
        me->add_temp("apply/strength", i);
        me->add_temp("apply/attack", j); 
        me->set_temp("xhz_xiaohun", 1);
        call_out("check_fight", 1, me, i, j, z);
        target->start_busy(2);
        message_vision(HIY"$N����������ݾ�����Ȼ����,����������,һ����Ȼ֮�����Ķ���.û����ɵĻ��������ĳ�һ��"+picture+",
�����Ʒ缤��,�л��㱣�����ԼԼ��ɲʱ��Ȼ��������������,�Ʋ��ɵ�.\n"NOR,me,target);
        return 1;
}
void remove_effect(object me, int i, int j)
{
    if(me->query_temp("xhz_xiaohun")){ 
    me->add_temp("apply/strength", -i);
    me->add_temp("apply/attack", -j);
         
    me->delete_temp("xhz_xiaohun");
    tell_object(me, HIR"�㡸���꡹����������ϣ����ص���.\n" NOR);
     }
//    else tell_object(me, "��\n" NOR);
}
void check_fight(object me, int i, int j, int z)
{
  

    if (!me) return;
    if (me->query_temp("weapon")
       || me->query_temp("secondary_weapon")
       || me->query("eff_qi")*2 > me->query("max_qi"))
    {
        remove_effect(me, i, j);
        return;
    }
    if (z < 1 || !me->is_fighting()) {
        remove_effect(me, i, j);
        return;
    }
    call_out("check_fight", 1, me, i, j, z-1);
}



