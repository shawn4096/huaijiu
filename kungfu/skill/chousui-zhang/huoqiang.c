// huoqiang.c ��ǽ
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
int start_huoqiang(object me);
int check_pfm(object me, object target, object ob);
int perform(object me, string target)
{
      	object ob, tar;
        if(!target|| !target->is_character()|| !me->is_fighting(target) )
             	return notify_fail("�������ս������������ǽ����\n");
        if(!objectp(tar = present(target, environment(me))))
             	return notify_fail("����û������Ը�������ˡ�\n");
        if(!tar->is_character()) 
                return notify_fail("�����һ�㣬�ǲ��������\n");
        if(!living(tar))
                return notify_fail(tar->name()+"�Ѿ��޷�ս���ˡ�\n"); 
        if(tar==me) return notify_fail("���Լ�ƴ������\n"); 
        if(me->is_busy())
             	return notify_fail("����æ����˵ƴ�����¡�\n");
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á���ǽ����\n");        
        if(!objectp(ob = present("huo yan", environment(me))))
                return notify_fail("û�л����ô��������ǽ�����й�����\n");
        if(me->query_temp("pfm_chousui"))
                return notify_fail("������������ѽ��й�����\n");
        if(environment(me)->query("no_fight"))
                return notify_fail("���������ʩչ������\n");

       	message_vision(BLU"\n$N��ɫ�ҵ������ִ򿪷��٣������´����������ϣ����ŵ�ȼ���׷ۣ�ҧ����⣬
һ��"RED"��Ѫ"BLU"���������ȥ��"HIR"�������һ�����漴��Ϊ"RED"����"HIR"��ҫ�������۾�Ҳ����������\n\n"NOR,me);

       	me->start_busy(1);
       	me->set_temp("pfm_chousui", 1);
       	me->start_perform(4,"��ǽ");
       	if(random(me->query_kar()) > 5)
             	check_pfm(me, tar, ob);
       	else 	call_out("check_pfm", 5, me, tar, ob);
       	return 1;
}

int check_pfm(object me, object target, object ob)
{
        string msg;
        int p;

        if(!me) return 0;
        me->delete_temp("pfm_chousui");
        me->start_busy(1);
        if(!living(me) || me->is_ghost()) return 1;
        
        if(!objectp(present(ob, environment(me)))){
           	message_vision(HIY"$N�ۿ����Ϩ��ɢ����Ϣ��\n"NOR,me);
           	return 1;
        }
        
        if( me->query_skill("chousui-zhang", 1) < 150 ){
                tell_object(me, "�㷢���Լ������޶��ƻ�������죬�޷�ʹ�á���ǽ�����й�����\n");
                return 1;
        }
        if( (int)me->query_skill("huagong-dafa",1) < 150 ){
                tell_object(me,"�㷢���Լ��Ļ�������Ϊ�������޷�ʹ�á���ǽ�����й�����\n");
                return 1;
        }
        if((int)me->query_skill("poison",1) < 120){
                tell_object(me,"�㷢���Լ����ھ۶��������޷�ʹ�á���ǽ�����й�����\n");         
                return 1;
        }
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang"){
                tell_object(me,"������ó����Ʋ���ʹ�á���ǽ�����й�����\n"); 
                return 1;
        }                                                                                
        if( me->query_skill_mapped("force") != "huagong-dafa"){
                tell_object(me,"�㷢���Լ����õ��ڹ��޷����С���ǽ��������\n");
                return 1;
        }          
        if( (int)me->query("max_neili") < 1000) {
                tell_object(me,"�㷢���Լ�����ʵ��̫�����޷���������ǽ�����й�����\n");
                return 1;
        }
        if(me->query("neili") < 800){
                tell_object(me,"�㷢���Լ���������ʵ��̫�����ٲ��𡸻�ǽ�����й�����\n");           
                return 1;
        }
        if(!target || !living(target) 
        || environment(me)!=environment(target)){
           	message_vision(HIY"$N�����ٷ�����̧���"HIR"��ǽ"HIY"ѹ�ػ���֮�С�\n"NOR,me);
           	return 1;
        }
        
        me->add("neili", -1000);
        me->add("jingli", -300);

        msg = BLU"\n$N�͵����Ӽ����������ݰ���ת��ʮ���Ȧ�ӣ�����$P���������"HIR"��������Ѷ��ز������
ȼ�գ�����һ��"RED"��ǽ"HIR"�㣬������ɽ����֮����$nѹ����\n"NOR;
        if(!target->is_killing(me->query("id"))) me->kill_ob(target);
       
        if(random(me->query_str()) > target->query_dex()/3){          
        	msg += HIY"����ӳ��֮��$p΢һ���ɣ��ǻ�ǽ���ÿ켫����Ҫ�˵����ϣ�$pֻ��˫�������
������������ͳ�������ķ�Ʈ�𣬾����������Ƕ���ɫ�Ĺ�ǽ��\n\n" NOR;
                target->add("neili", -1000);
                target->add("jingli", -200);  
                me->set_temp("huoqiang_target", target->query("id"));
                me->set_temp("huoqiang/period", 1);
                target->set_temp("huoqiang_target", me->query("id"));
                target->set_temp("huoqiang/period", 1);  
                me->start_busy((: start_huoqiang :));
                target->start_busy((: start_huoqiang :));
                message_vision(msg, me, target);
                return 1;     
        }                   
            
        else if(random(me->query_str()) > target->query_dex()/4){
                me->start_busy(4);
                target->start_busy(3);
                msg += HIY"\n$nֻ��Ŀ�ɿڴ���һ��֮�䣬��æԾ�𣬵�һ��"HIW"��"HIY"���䵽��ǰ���͵�һ���죬
�������϶Ǹ���$n��������һ����У���������������"HIR"���ǽ"HIY"Ҳ�����������С�\n" NOR;
                target->receive_damage("qi", me->query_skill("force")*2, me);  
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += damage_msg(me->query_skill("force"), "����");
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
                msg = replace_string(msg, "$l", "�Ǹ�");
                msg = replace_string(msg, "$w", HIW"��"NOR);
        }
      	else {
                me->start_busy(3);
                msg += HIY"$nֻ��Ŀ�ɿڴ���һ��֮�䣬"HIR"��ǽ"HIY"���䵽��ǰ����æԾ��"HIR"��ǽ"HIY"������$p����·ɹ���\n" NOR;
        }      
       	message_vision(msg, me, target);
       	return 1;
}       

int start_huoqiang(object me)
{
        string msg, tar;
        object target, ob;
        int neili_lost, period, neili, neili2;

        if(!me) return 0;
        tar = me->query_temp("huoqiang_target");
        target = present(tar, environment(me));
        if(!target || target->is_ghost() || environment(me)!=environment(target) || !target->is_busy() ){
            	message_vision(CYN"$N�����ھ�һ�գ���һ˫����㼴���£�ҡҡ�ϻϵ�վ��������\n"NOR, me);
            	return 0;
        }
        neili_lost = 15 + target->query_skill("force")/10 + me->query("jiali")/2 + target->query("jiali")/2;
        period = (int)me->query_temp("huoqiang/period"); 
        neili = me->query("neili");
        neili2 = target->query("neili");

        me->receive_damage("neili", neili_lost);
        me->receive_damage("jingli", 3+random(5));        
        me->improve_skill("force", random(2));

        if(me->is_ghost()) return 0;

        if(neili < neili_lost){
            	message_vision(HIY"$N�������Ĵ���������֧���أ�\n"NOR, me);
            	me->set_temp("last_damage_from", target); 
            	me->unconcious();
            	return 0;
        }
        if(!living(target) && living(me)){
            	msg = HIR"$N˫���ĳ���һ��"GRN"����"HIR"�³�������$n��$p�˿�����˿��������أ���վ��������������Ҳ�ޡ�
"GRN"����"HIR"һ�䵽$p���ϣ���ʱ��ͷ�����Ż𣬿�вҺ����У�ȫ������"RED"����"HIR"֮�С�\n"NOR;
            	target->set_temp("last_damage_from", "��"+me->name()+"ɱ");
            	msg += "���ֻ���������������죬$nһ���ҽУ���̲�����������ȥ����\n";
            	msg += "( "RED"$n���˹��أ��Ѿ�������в�����ʱ�����ܶ�����"NOR")\n";
            	message_vision(msg, me, target); 
            	target->set_temp("last_damage_from", me);
            	target->die();     
            	return 0;
        }        
        if(!living(me) && !living(target)){
            	message_vision(HIW"��ʱ$N���϶����ް��Ѫɫ�������Ѿ������;��ƿ�֮ʱ��\n"NOR,me);
            	me->set_temp("last_damage_from", "��"+target->name()+"ͬ���ھ�");
            	me->die();
            	return 0;
        }
        if(!objectp(ob = present("huo yan", environment(me)))){
           	message_vision(HIY"$N�ۿ����Ϩ��Ҳ�����չ���վ��������\n"NOR,me);
           	return 0;
        }

        switch(period) {   
        case 3: 
        case 9:
        case 15:
        case 21: 
        case 27:
        case 33:
        case 39:
        case 45:
        case 51:
        case 57:
        case 63:
        case 69:
        case 75:
        case 81:
        case 87:
        case 93:   
        case 99:     
        case 115:
        case 145:
        case 175:
        case 205:  
                if(neili > neili2){
                 	msg = random(2)?HIR"������һ�����$N�ķ����ƶ���\n"NOR:HIR"�ۿ�$Nʹ��ȫ������ͼ���ǲ����ƽ��ı����Ƶ���ȥ��\n"NOR;
                 	message_vision(msg,target);
                }
                break;
        case 12:       
        case 24:
        case 42:
        case 60:
        case 78:  
        case 96: 
        case 125:
        case 155:
        case 185:
                 if(neili > neili2){
                 	msg = random(2)?HIR"$N�ۿ�"GRN"����"HIR"$Nʹ��ȫ������ͼ���ǲ����ƽ��ı����Ƶ���ȥ��\n"NOR:HIR"$N�ۿ�"GRN"����"HIR"���Լ�������ȴ���ܿ���ͣ����������Ȼ�������������ʱ�ᱻ���������\n"NOR;
                 	message_vision(msg, target);
                 }
                 break; 
        case 36:
        case 54:
        case 72:        
        case 90:
        case 105:
        case 135:
        case 165:
        case 195:
                 if(me->query("jiali") > target->query("jiali")){
                 	msg = random(2)?HIR"��Ƭ"GRN"����"HIR"�ڿ�����һͣ�ͣ��㻺����$N��ǰ��ȥ��$N�󾪣��������
��һҧ��һ��"RED"��Ѫ"HIR"���������ȥ������һʢ�����˹�����\n"NOR:HIW"$N��ʱ�������ް��Ѫɫ��һ�ڿ�"RED"��Ѫ"HIW"��ס���������ȥ��Ҫ������ƻأ�\n"NOR;     
                 	message_vision(msg, me);
                 }
                 break;
        } 

        period++;
        me->set_temp("huoqiang/period", period);
        return 1;        
}
