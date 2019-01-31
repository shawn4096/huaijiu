// wuwo.c
#include <ansi.h>
int check(object me);
int exert(object me)
{       
        int nh=me->query_skill("linji-zhuang", 1);

        if ((int)me->query_skill("linji-zhuang", 1) < 160)
            return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
            return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ����ҡ��־���\n");

        if( me->query_skill("medicine", 1) < 100 )
            return notify_fail("��ı�������ȼ�������\n");

        if( (int)me->query("neili") < 500 )
            return notify_fail("�������������\n");

        if( me->query_temp("ljz/wuwo")   )
            return notify_fail("�����������ټ�ʮ��ׯ�ġ����ҡ��־���\n");

        message_vision(HIW"ֻ��$N��������һ����������¶�������Ц�ݡ�\n"NOR, me);
        me->set_temp("ljz/wuwo", nh);  
        me->add("neili", - 200);
        check(me);
        me->start_exert(nh/3,"�����ҡ��־�");
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), nh/3);
        return 1;
}

int check(object me)
{    
        if (!me || !(int)me->query_temp("ljz/wuwo")) return 0;
        if(me->is_ghost() || !living(me))
           me->delete_temp("ljz/wuwo");
        if( me->query("jingli") < 100 
         || me->query("neili") < 120
         ||! me->is_fighting()
         ||(userp(me) && me->query_skill_mapped("force") != "linji-zhuang")){
            message_vision(HIC"$N�ݻ�������ֹͣ����Ϣ��������\n"NOR, me);
            me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), 1);
        }
        else {
          if(me->query("qi") < (int)me->query("max_qi")){
              message_vision(HIY"$N��ɫһ���ֻظ��������������ڵ�����Ϣ��\n"NOR,me);
              me->add("neili", - 50);
              me->add("eff_qi",me->query_skill("medicine", 1));
              if (me->query("eff_qi")>me->query("max_qi"))
                  me->set("eff_qi",me->query("max_qi"));
                me->add("qi",me->query_skill("force"));
          }
          call_out("check", 2+random(3), me);
        }
        return 1;
}       

void remove_effect(object me)
{
        int nh;
        if( !me || !me->query_temp("ljz/wuwo")) return;
        nh = me->query_temp("ljz/wuwo");
        me->start_exert(0);
        me->delete_temp("ljz/wuwo");
        message_vision(HIR"$Nɢȥ�ˡ����ҡ��ķ����ָֻ���ԭ����$N��\n\n"NOR,me);
}
