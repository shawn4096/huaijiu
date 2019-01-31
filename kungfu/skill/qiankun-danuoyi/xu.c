// xu.c Ǭ����Ų�ơ���־�

#include <ansi.h>
inherit F_SSERVER;
int check_fight(object me);

int perform(object me, string arg)
{
        object ob;
        int i, jiali;
        
        if(!me->is_fighting())
                return notify_fail("��û��ս�����أ�\n");

        if(me->query_temp("weapon"))
                return notify_fail("����־��˿��־������������������ʹ�ó���\n");
                
        if(me->query_temp("qkdny/xu") > 1)
        {
        	if(arg && !objectp(ob = present(arg, environment(me))))
                	return notify_fail("��û��ս�����أ�\n");
                else    ob = offensive_target(me);

		if(!ob 
		|| !ob->is_character() 
		|| !me->is_fighting(ob) 
      		|| environment(ob) != environment(me) 
      		|| !living(ob))
         		return notify_fail("����־������������ֻ�ܶ�ս���ж���ʹ�á�\n");
         	
         	i = me->query_temp("qkdny/xu");
         	
         	if(me->query("neili") < i)
         		i = me->query("neili");
         		
         	jiali = me->query("jiali");
         	
         	if(jiali > i)
         		i = jiali;
         		
         	if(i < 10)
         		return notify_fail("�㡸��־������������̫�٣�ֻ��û��ʲô���ã�\n");
         	
         	me->set("jiali", i+jiali);
         	if(wizardp(me))
         		tell_object(me, "����־����� = "+i+"\n");

                me->add_temp("apply/attack", 50);
                message_vision(HIY"\n$NͻȻ����һ�������������ʮ���Ƶ������鲢��Ϊһ���ĳ�������һ�������ɽ�鱬��ʱ�����˺�ˮ���͵�����̱�������ˮ�������������ԭ����˴�����$n������ʵ�ˣ�������ʱ��ǡ��۹ǡ���ǡ��߹�һ���۶ϣ���ѪҲ�粻������������Ϊһ��Ѫ��ģ�������òҲ����ԣ�\n"NOR, me, ob);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
                
                me->add_temp("apply/attack", -50);
                me->set("jiali", jiali);
                me->delete_temp("qkdny/xu");
                me->reset_action();
                me->start_busy(2);
                ob->start_busy(ob->query_busy()+2);
                return 1;
        }
        
        if(me->query_skill("qiankun-danuoyi", 1) < 200 )
                return notify_fail("���Ǭ����Ų�ƻ�δ�������߲㣬����ʹ�á���־���\n");
        if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("��û��ʹ��Ǭ����Ų����Ϊ�н����޷�ʹ�á���־���\n");
                 
        if((int)me->query("neili") < 300 )
                return notify_fail("��Ŀǰ������������\n");
        if((int)me->query_skill("force") < 300 )
                return notify_fail("����־���Ҫ�����ڹ�����������������󻹲�����\n");
        
        if((int)me->query_temp("qkdny/yi") )
                return notify_fail("������ʩչ���ơ��־��أ�\n");
                
        me->add("neili", -200);
        tell_object(me, BLU"\n�㰵������Ǭ����Ų���ķ��е��߲㹦��ʩչ����־������Է���������������������\n\n"NOR); 
        me->set_temp("qkdny/xu", 1);    
        check_fight(me); 
        return 1;
}

int check_fight(object me)
{    

        if (!me || !me->query_temp("qkdny/xu")) return 0;

        else if(me->is_ghost() || !living(me))
                me->delete_temp("qkdny/xu");      
        
        else if(!me->is_fighting()){
                tell_object(me, BLU"\n���˳���ս�����㽫�������������ɢ�˳�ȥ��\n"NOR);
                me->delete_temp("qkdny/xu");
                }
        
        else if(me->query("neili") <= 100){
                tell_object(me, BLU"\n��ͻȻ���ֱ���������Ѿ�Ҫ�ݽ�����æ�ѻ��������ɢ�˳�ȥ��\n"NOR);
                me->delete_temp("qkdny/xu");
                }
                  
        else if (me->query_skill_mapped("parry") != "qiankun-danuoyi"
                || me->query_temp("weapon")){
                tell_object(me, BLU"\n������һת���ı���ս�����ѻ��������ɢ�˳�ȥ��\n"NOR);
                me->delete_temp("qkdny/xu");
                }   
        
       else call_out("check_fight", 1, me);
       return 1;
}       
