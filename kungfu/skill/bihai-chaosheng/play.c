// play.c �ࡰ�̺���������
// modified by darken@SJ
#include <ansi.h>
inherit F_CLEAN_UP;
void playing(object *ob, int skill, int damage, object me);
int exert(object me, object target)
{
        object *ob;
        object weapon;
        int skill, damage;
        if (me->query_skill("bihai-chaosheng", 1) < 100)
                return notify_fail("��ı̺���������û���ҡ�\n");
        if( environment(me)->query("no_fight") )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");
        if (!weapon = me->query_temp("weapon"))
                return notify_fail("��Ҫ��ʲô�����ࣿ\n");
       if (!weapon->id("xiao"))
                return notify_fail("������ı��������\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("�������������\n");
        skill = me->query_skill("bihai-chaosheng",1);

        me->add("neili", -300);
        damage = skill;
        me->start_busy(3);
me->start_exert(8,"�̺�������");
        message_vision(HIM"$N�������ʵش����𡰱̺���������������������������������ˡ�\n"NOR, me);
        ob = all_inventory(environment(me));
        call_out("playing",2,ob,skill, damage, me);
        return 1;
}

void playing(object *ob, int skill, int damage, object me)
{
        int i;
        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++) {
                if (!living(ob[i]) || ob[i] == me) continue;
                ob[i]->start_busy(3);
                if (ob[i]->query("age") >= 16) {
                if (ob[i]->query_skill("bihai-chaosheng",1)>50)
                        message_vision(HIW"$N�Ա̺�������ϰ��Ϊ����ûʲô��Ӧ��\n"NOR, ob[i]);
                else if (ob[i]->query("class") == "bonze" ) {
                        if (random(10)>6)
                        message_vision(HIW"$Nƽʱ���Ĺ���������û�ж��Ч����\n"NOR, ob[i]);
                        else {
                                message_vision(HIR"$N�������ŵ��ķ����ң�ʧȥ�˿�������\n"NOR, ob[i]);
                        if ((skill*20) > ((int)ob[i]->query("neili")/2)) {
                                       if( damage > 0 ) {
                                             ob[i]->receive_damage("jing", damage + random(damage), me);
                                       if( (int)ob[i]->query("neili") < (int)me->query("neili")*2)
                                             ob[i]->receive_wound("jing", damage, me);
              message_vision(HIR"$N�����������࣬�������ţ����ҡ�����������١�\n"NOR, ob[i]);}
                        }
                     }
                 }                         
                else if (random((skill*20)) < ((int)ob[i]->query("neili")/2))
                {
                        message_vision(HIY"$N���������ֿ�������ûʲô��Ӧ��\n"NOR, ob[i]);
                        ob[i]->add("neili",-skill*3);
                }
                else
                {
                        if( damage > 0 ) {
                                ob[i]->receive_damage("jing", damage+random(damage), me);
                        if( (int)ob[i]->query("neili") < (int)me->query("neili")*2)
                                ob[i]->receive_wound("jing", damage, me);
          message_vision(HIR"$N�����������࣬�������ţ����ҡ�����������١�\n"NOR, ob[i]);
                        }

                        if (userp(ob[i])) ob[i]->fight_ob(me);
                        else if (!ob[i]->is_killing(me)) ob[i]->kill_ob(me); }
                }
                else
                        tell_object(ob[i], "��������С������һ��û��ʲô�ر�ĸ��ܡ�\n");
        }
          if (!me->query_temp("thd/play1") && me->query_skill("qimen-bagua",1)>=200) {
        message_vision(HBYEL"$N���²��Ű��Է�λ����Ϣ������������Ȼ�θߡ�\n"NOR, me);
        me->start_busy(3);
        me->set_temp("thd/play1",1);
          call_out("playing",3,ob,skill+random(skill/2), damage, me); } else
          if (!me->query_temp("thd/play2") && me->query_skill("taoism",1)>=200) {
    message_vision(HBMAG"$N��ͨ��������֮������Ϣ�ڵ�����תһ�ܣ�������������Ѫ�����š�\n"NOR, me);
        me->start_busy(3);
        me->set_temp("thd/play2",1);
        call_out("playing",3,ob,skill+random(skill), damage, me); } else {
        me->delete_temp("thd/play1");
        me->delete_temp("thd/play2"); }
}

