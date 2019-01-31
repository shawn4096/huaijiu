// wudi.c 
// by emnil   98.8.12

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);
void remove_effect2(object me);
int exert(object me, object target)
{
        int skill;
        string s;

        if( target != me )
                return notify_fail("��ֻ���ö������������Լ���ս������\n");

        if((int)me->query_skill("dulong-dafa",1) < 100  )
                return notify_fail("��Ķ����󷨹����������޷�ʩ�á��޵С��󷨡�\n");

        if((int)me->query("max_neili") < 500 )
                return notify_fail("��������������޷�ʹ�á��޵С��󷨡�\n");
 
        if((int)me->query("eff_qi") < me->query("max_qi")/2 )
                return notify_fail("���������˹��أ�����ʹ�á��޵С��󷨡�\n");

        if( me->query_temp("sld/shougong"))
                return notify_fail("��ո��չ���ϣ�����Ъ����ʹ�á��޵С��󷨰ɡ�\n");

        if( me->query_temp("sld/wudi") && environment(me)->query("no_death"))
                return notify_fail("�������޷�ʹ���޵С�\n");

        if((int)me->query_temp("sld/wudi2"))
                return notify_fail("���Ѿ�������������Ǳ����\n");

        if((int)me->query("eff_qi") > me->query("max_qi"))
                return notify_fail("�������޷�ʹ�á��޵С��󷨡�\n");

        if((int)me->query("neili") < 800  )
                return notify_fail("��������������޷�ʹ�á��޵С��󷨡�\n");

        skill = me->query_skill("dulong-dafa", 1);
        if( me->query_temp("sld/wudi") && me->query("eff_qi") < me->query("max_qi")){

                s=RED"\n$N�����Ľе������������ͨ���ӣ��ڵ��������ٱ�����һ���٣��԰ٵ���\n"+
                "�������Ŀ��磬�����ķ����ҵ���ɱ�л��̣�������׼���Σ�����ʥְ��\n"+ 
                "�ҽ̵��ӻ��̶�����ͬ�����ã�����ͻȻ���һ����Ѫ���ƺ��Ѿ���������ʹ��\n\n"NOR;

                me->delete_temp("sld/wudi");
                me->add("max_neili", -1); // һ��max neili��Ϊ���۵õ��߹�����
                me->set("eff_qi",me->query("max_qi"));
                me->set("qi",me->query("eff_qi"));
                me->set("jingli",me->query("eff_jingli"));
                me->set("neili",me->query("max_neili"));
                me->add_temp("apply/attack", skill/2);
                me->set_temp("sld/wudi2", skill/2);
                me->start_call_out( (: call_other, __FILE__, "remove_effect2", me :), skill/3);
                me->start_perform(1,"���޵С�");
                me->start_exert(1,"���޵С�");
                message_vision(s, me);
                return 1;
        }
        if( !me->query_temp("sld/wudi2") && !me->query_temp("sld/wudi")){
                me->add("neili", - 500);
                s=HIR"\n$N�����е������������ͨ����ҽ�ս�޲�ʤ�����޲��ˣ��޼᲻�ݣ��޵в��ƣ�\n"+
                "�����������ң���֮زز������˫��ͻȻð��һ˿��⣬�ƺ�ͻȻ�����˹�����\n\n"NOR;

                if(! me->is_fighting()){
                        me->set_temp("sld/wudiqi",skill*2); 
                        me->add("max_qi", skill*2);
                        me->add("eff_qi", skill*2);
                        me->add("qi", skill*2);
                }
                me->add_temp("apply/attack", skill/4);
                me->set_temp("sld/wudi", skill/4);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), skill/2);
                me->start_perform(1,"���޵С�");
                me->start_exert(1,"���޵С�");
                message_vision(s, me);
                return 1;
        }
        return notify_fail("�������޷�ʹ�á��޵С��󷨡�\n");
}

void remove_effect(object me )
{
        int i;
        
        if(!objectp(me)) return;
        if(!intp(i = me->query_temp("sld/wudi")) ) return; 
        
        me->add("max_qi",- me->query_temp("sld/wudiqi"));
        me->add_temp("apply/attack", -i);
        me->delete_temp("sld/wudiqi");
        me->delete_temp("sld/wudi");
        message_vision(HIR"\n$N����������һ����ͻȻ����������\n\n"NOR,me);
        return;
}

void remove_effect2(object me)
{
        int amount;
        
        if(!objectp(me)) return;
        if(!intp(amount = me->query_temp("sld/wudi2")) ) return;
        
        if(me->is_ghost()){
                me->delete_temp("sld/wudi");
                me->add_temp("apply/attack", -amount/2*3);  
                me->add("max_qi",- me->query_temp("sld/wudiqi"));
                return;
        }
        message_vision(RED"\n$N����һ�ɣ���Ҳ֧�ֲ�����\n"NOR,me);                 
        
        me->add_temp("apply/attack", - amount/2*3);
        me->add("max_qi",- me->query_temp("sld/wudiqi"));
        if(me->query("eff_qi")>me->query("max_qi")) 
                me->set("eff_qi",me->query("max_qi"));
        if(me->query("qi")>me->query("eff_qi")) 
                me->set("qi",me->query("eff_qi"));
        me->delete_temp("sld");
//      me->unconcious();
}
