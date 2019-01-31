// riyun.c
// by snowman@SJ 27/01/2000

#include <ansi.h>
int check_fight(object me, int nh);

void remove_effect(object me, int nh);

int exert(object me)
{       
        int nh, neili;
       
        if( !me->is_fighting() )
             return notify_fail("�����¡��־�������ս����ʹ�á�\n");

        if((int)me->query_skill("linji-zhuang", 1) < 150)
             return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
            return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ����¡��־���\n");

        if((int)me->query("neili") < 1000 )
             return notify_fail("�������������\n");
        
        if( me->query_temp("ljz/riyue"))
             return notify_fail("�����������ټ�ʮ��ׯ�ġ����¡��־���\n");

        tell_object(me,MAG"\n���������죬Ǳ�����¶�ׯ����������������Ǳ����������������ض�����̩�����پ��Լ�����ԴԴ��ֹ�ˡ�\n"NOR);
        message_vision(HIW"\nֻ��$N���Ϻ��ʱ��ʱ�֣�һ�±��������ġ�\n\n"NOR, me);

        nh = (int)me->query_skill("linji-zhuang", 1)/10;

        if( me->query("emjiuyin")) {
             tell_object(me,HIB"\n�㽫�����ܾ��ں����ټ�ʮ��ׯ֮��,����������Ȼ��������\n"NOR);
             message_vision(HIB"\nֻ��$Nʹ������������������Ѹ���ޱȵ��������У�һ�б�һ��������\n\n"NOR, me);
             me->add_temp("apply/attack",nh/2);
             me->add_temp("apply/damage",nh/3);
             }

        neili = (int)me->query("neili");
        me->set_temp("ljz/riyue", neili);
        me->add("neili", -nh*20);    
        check_fight(me, nh);
        me->start_exert(nh, "�����¡�");
        return 1;

}

int check_fight(object me, int nh)
{    

        if( !me || !(int)me->query_temp("ljz/riyue")) return 0;

        if( me->is_ghost()|| !living(me))
          me->delete_temp("ljz/riyue");
          
        if( !me->is_fighting()
         || me->query("neili") <= 10
         || (userp(me)
         && me->query_skill_mapped("force") != "linji-zhuang"))
		call_out("remove_effect", 1, me, nh);
        else {
           if(me->query("neili") < (int)me->query_temp("ljz/riyue")){
             tell_object(me, "����������֮����ת��Ϣ��ʹ��о������κ����������ģ�\n");
             me->set("neili", me->query_temp("ljz/riyue"));
           }
           call_out("check_fight", 1, me, nh);
        }       
        return 1;
}       

void remove_effect(object me, int nh)
{
        if( !me || !me->query_temp("ljz/riyue")) return;
	me->start_exert(0);
	me->delete_temp("ljz/riyue");
	message_vision(HIR"$N�������֮������ɢ������֮�䣬$N�ָֻ���ԭ�е��������ġ�\n\n"NOR, me);

        if( me->query("emjiuyin")) {
             message_vision(HIY"$N�Ķ��Ҿ����ܾ��޷�άϵ����ʽ��������������\n"NOR, me);
             me->add_temp("apply/attack",-nh/2);
             me->add_temp("apply/damage",-nh/3);
             }

}
