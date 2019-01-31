// fengyun.c

#include <ansi.h>

int exert(object me)
{       
        int improve;

        if( !me->is_fighting() )
            return notify_fail("��ֻ����ս���������ټ�ʮ��ׯ�ġ����ơ��־���\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
            return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ����ơ��־���\n");
        
        if((int)me->query_skill("linji-zhuang", 1) < 90)
            return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if((int)me->query("neili") < 200 )
            return notify_fail("�������������\n");
        
        if( me->query_temp("ljz/fengyun")   )
            return notify_fail("�����������ټ�ʮ��ׯ�ġ����ơ��־���\n");

        tell_object(me,MAG"�㰵�˷�����ׯ����˼����Ʈ��֮���л�����Ĭ���絴��֮Ѹ�ٽ���һ�ɵ���������ע��֫�ٺ�������������������ࡣ\n"NOR, me);
        tell_room(environment(me), MAG"ֻ��"+me->name()+"΢��˫�ۣ���������һȦ����˲Ϣ��һ���������������ָ�������\n"NOR,({ me }));
        improve = (int)me->query("dex") ;
        me->add_temp("apply/dexerity", improve);
        me->set_temp("ljz/fengyun", improve);  
        me->add("neili", - 150);    
        me->start_perform(2,"�����ơ��־�");
        me->start_exert(2,"�����ơ��־�");
        call_out("remove_effect", 1, me, (int)me->query_skill("dodge", 1)/2 );
        return 1;
}

void remove_effect(object me,int count)
{
        int i;
        if(!me || !me->query_temp("ljz/fengyun")) return;
        if( ! me->is_fighting()
         || count < 1){
          i = me->query_temp("ljz/fengyun");
          me->add_temp("apply/dexerity", -i);
          me->delete_temp("ljz/fengyun");
          tell_object(me, HIR"������й��Ѿã��Ծ����ĳ�����һЩ��\n"NOR);
          return;
        }
        call_out("remove_effect", 1, me,count - 1);
}
