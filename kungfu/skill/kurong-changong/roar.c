// roar.c tls ʨ�Ӻ�
//COOL@SJ 19990909

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
/*
        string force;
        mapping msg;
*/
        object *ob;
        
        int i, skill, damage;

        if( (int)me->query("neili") < 1500 )
                return notify_fail("�������������\n");

        if (me->query_skill_mapped("force") != "kurong-changong" )
                return notify_fail("�����ڵ��ڹ�û������ܡ�\n");     

        if( environment(me)->query("no_fight") )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        if( (int)me->query_skill("force") < 200 )
                return notify_fail("����ڹ���Ϊ������\n");
                
        if( (int)me->query_skill("buddhism",1) < 150 )
                return notify_fail("����������򲻹���\n");
        
        if( (int)me->query("jingli") < 150 )
                return notify_fail("��̫���ˣ�������Ϣһ�°ɡ�\n");      


        me->add("neili", -300);
        me->receive_damage("jingli", 100);

        me->start_busy(2);
     	me->start_exert(8,"ʨ�Ӻ�");

        message_vision(HIY"�����á��ػ���һ����ȣ����˶��о�����������졣$Nʹ��������һ��\n"+
                          "���ϳ˵Ĺ��򣬽�����ʨ�Ӻ𡯣�һ���Ϻ����������������\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
        	skill = me->query_skill("force") + me->query_skill("buddhism",1);
                if( wizardp(ob[i])||!living(ob[i]) || ob[i]==me ) continue;
		if( !me->can_kill_ob(me, ob[i]) ) continue;
                if( random(skill) < (int)ob[i]->query_skill("force")/3*2) continue;
                skill -= ob[i]->query_skill("force")/2;
                damage = skill - ((int)ob[i]->query("neili") / 20);
                damage += random(damage);
            	if( (int)ob[i]->query("neili") < (int)me->query("neili")*2)
             		damage+=damage;
                tell_object(ob[i], "�㱻��޺������ǰ���Σ�����һƬ�հף�����һ���㱡�\n");
                if (ob[i]->is_fighting()){
                    	ob[i]->remove_all_enemy();
                    	message_vision("\n$N����һ����ֹͣ��ս����\n", ob[i]); 
                }
/*
                else if ((int)ob[i]->query_temp("pending/exercise")){
                   	force = ob[i]->query_skill_mapped("force");
                   	if (force) msg = SKILL_D(force)->exercise_msg(ob[i]);
                   	if (!msg || undefinedp(msg["halt_msg"]))
                      		message_vision("$N��ֻ����Ϣ��˳��վ��������\n", ob[i]);
                   	else
                      		message_vision("$Nֻ����Ϣ��˳,"+msg["halt_msg"], ob[i]);
                }
                else if ((int)me->query_temp("pending/respirate") != 0) 
                	message_vision("$Nֻ����Ϣ��˳���������ڴ�����վ��������\n", me);
                ob[i]->interrupt_me();
		if(ob[i] && living(ob[i])) ob[i]->start_busy(random(3));
*/
		ob[i]->receive_damage("jing", damage, me);
        }
        return 1;
}
