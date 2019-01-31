// dongjing.c ̫��ȭ������������
// by snowman@SJ 02/03/2000
// Modified by snowman@SJ 24/05/2001

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() { return 1;}
string perform_name(){ return HIR"������"NOR; }

int perform(object me, object target)
{ 
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( userp(me) 
        &&( me->query_skill_mapped("parry") != "taiji-quan"
        && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("������������������̫��ȭ��̫���������мܵ�����²���ʹ�á�\n");
        if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("����ڹ���ȭ�����ԣ��������ܷ��ӳ����������������ơ�\n");  
        if( !me->query_temp("tj/̫��") && me->query_skill("taiji-quan", 1) < 300 )
                return notify_fail("̫��ȭ��Ҫ���ڶ�����Ӧ���������棬��û�����á�̫�������������ʹ�á�����������\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("����������������ǿ��ʹ�á����������Ƿ��Ӳ������������ģ�\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     
        if( target->query_condition("no_exert") )
                return notify_fail("( �Է���Ϣ���ȣ��������Ѿ�����ʩ���ڹ��ˡ�)\n");
                        
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
        int damage = 1;
        string msg, force, str;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 300 || me->query("jingli") < 100 || me->query_temp("weapon"))
                return 0;     
                
        if(intp(me->query_temp("tjq/"+target->query("id")) > 3))
                me->add_temp("tjq/"+target->query("id"), -3);
        else me->delete_temp("tjq/"+target->query("id"));
        
        str = (string)me->query("env/���Ͼ�"); 
        if(str != "�귭" && str != "����" && str != "����" && str != "����" && str != "����" && str != "����")
                str = "��";
                
        msg = MAG"\n$Nʹ��̫��ȭ��"RED"����������"MAG"�Ĺ���";
        
        if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 100){
                msg += "ͻȻһ�³嵽$n��ǰ��Ҫץס$n��\n"NOR;
                str = "��";
        }        
        
        else msg += "��֮��ϣ��޹��������������죬��$n��ס�Լ���˫�֣�\n"NOR;
        
        if(TAIJI->check_force(target) == str || me->query_skill("taiji-quan", 1) > 350)
                damage = 3;
       
        me->start_perform(2, "����������");
        if(!stringp(force = to_chinese(target->query_skill_mapped("force"))))
                force = "�ڹ�";
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose")
                tell_object(me, "Str = "+str+"��Force = "+force+"��Damage = "+damage+"\n");
        
        if( random(me->query("combat_exp") * (me->query_str() + me->query_int())/ 100) 
        > (int)target->query("combat_exp") * (target->query_str() + target->query_dex()) / 200 
        || target->is_busy() ){
                msg += HIY"$p����һЦ����Ҫ������$P���䣡\n"NOR;
                me->start_perform(3+random(2), "����������");
                me->start_busy(1);
                if(!target->is_busy()) target->start_busy(3);
                call_out("hurt",1+random(2),  me, target, damage, str, force);  
        }
        
        else{
                msg += HIY"��$p�Ͼ��о����ԣ������˺�ſ���$P������\n"NOR;
                me->start_busy(1+random(2));
        }

        message_vision(msg, me, target);
        return 1;
}

int hurt(object me, object target, int damage, string str, string force)
{
        object weapon;
        string msg;
        int p;
        
        if( !me || !living(me) || me->is_ghost() || !me->is_fighting()) return 0;
        
        if( !target || !target->is_character() || !me->is_fighting(target) || damage < 1
        || environment(target)!=environment(me) )
                return 0;
        
        msg = MAG"\n̫���ߣ��޼���������֮��֣���֮��ϣ�";
        switch(str){
                case "�귭": msg += "$N˫��һ��������ס$n��̫��ȭ��"HIW"��"+str+"����"MAG"��Ȼ�忪"+force+"ʹ������$nһ�ͣ�˦�˳�ȥ��\n"NOR;break;
                case "����": msg += "$N����һ����ץס$n��"HIW"��"+str+"����"MAG"͸��$n�����"+force+"һŦ��ץ��$p�Ӽ米��˦�˳�ȥ��\n"NOR;break;
                case "����": msg += "$N��"HIW"��"+str+"����"MAG"һ�ͣ���ɢ��$p��"+force+"���պ�����$nҪ��������ʱһ��һ�ţ���$p�Լ�ˤ��һ�󽻣�\n"NOR;break;
                case "����": msg += "$N˫��һ�֣�����"HIW"��"+str+"����"MAG"����ײ$n����$p��"+force+"��������Ӧ��\n"NOR;break;
                case "����": msg += "$N˫�Ʋ�����ȫ��"HIW"��"+str+"����"MAG"�߶���һ���Ӿ��Ƶ���$n��"+force+"������$p���վ�����ȣ�\n"NOR;break;
                case "����": msg += "$N�����׼�����糵�֣�����"HIW"��"+str+"����"MAG"����$n��"+force+"һ�ͣ���$p�����ȣ�ȫ��������մ���\n"NOR;break;
                default: msg = MAG"\n$NͻȻ������ס$n˫��һ��һ������$p���ڹ�������\n"NOR;break;
        }    
        
        if (target->query("neili") <= 200){
                message_vision(msg, me, target);
                tell_object(target, "�㷢���Լ�������Ȼ�ݽߺľ��������޷��࿹�ˣ�\n");
                target->receive_damage("qi", (int)target->query("qi")+1, me);
                msg = RED"���$N���ֲ��������Լ��ľ������ͷ��Ŀѣ��ҡҡ��׹��\n"NOR;
                msg += damage_msg(target->query("max_qi"), "ˤ��") + "( $N"+status_msg(5)+" )\n"; 
                message_vision(msg, target, target);
                me->start_busy(1);
                return 1;
        }
        
        
        else if(me->query("neili")*3 < target->query("neili")) 
        {
                me->start_busy(2+random(3));
                target->start_busy(1+random(2));
                
                msg += HIR"����$p�����ۺ񣬾����ϵ���˳��һ�壬��$P��߲�������\n"NOR;   
                message_vision(msg, me, target);
                return 1;
        }
        
        p = (int)me->query_skill("force") + random(me->query_skill("force")*2);
        target->receive_damage("qi", p, me);
        target->receive_wound("qi", p/2, me);
        msg += damage_msg(p, "ˤ��")+
        "( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
        
        message_vision(msg, me, target);
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose") 
                tell_object(me, "Damage ="+p+"\n");

        if(random(2) == 1 && !wizardp(me)){
                if( !me->is_killing(target->query("id"))
                && !target->is_killing(me->query("id"))
                && !me->query("have_master")   // added by snowman
                && target->query("qi")*2 <= target->query("max_qi")) 
                        COMBAT_D->end_fight(me, target);
                return 1;
        }
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose") 
                tell_object(me, "Dongjing done.\n");
                
        force = target->query_skill_mapped("force");
        
        switch(force){
                case "huntian-qigong":
                        if( intp(p = target->query_temp("htqg/powerup")) ){
                                target->add_temp("apply/attack", - p);
                                target->add_temp("apply/dodge", - p);
                                target->delete_temp("htqg/powerup");
                                tell_object(target, HIR"��Ļ���������һ����ɢ��������ЧӦҲ��ʧ�ˣ�\n"NOR);
                                break;
                        }
        
                case "yijin-jing":
                        if( intp(p = target->query_temp("fanzhen")) ){
                                p = target->query_temp("fanzhen");
                                target->add_temp("apply/armor", - p);
                                target->delete_temp("fanzhen");
                                target->delete_temp("no_skill_hit_ob");
                                tell_object(target, HIR"��ġ���ղ������񹦡���һ����ɢ��ЧӦҲ��Ӧ����ʧ�ˣ�\n"NOR);
                                break;
                        }
        
                case "linji-zhuang":
                        if( target->query_temp("ljz/riyue") ){
                                target->delete_temp("ljz/riyue");
                                tell_object(target, HIR"��ġ����¡�ׯ��һ����ɢ��ЧӦҲ��ʧ�ˣ�\n"NOR);
                                break;
                        }
                        if( intp(p = target->query_temp("ljz/yinyang")) ){
                                target->add("max_qi", - p);
                                target->receive_wound("qi", p, "��������ׯ���ƣ�������");
                                target->delete_temp("ljz/yinyang");
                                tell_object(target, HIR"��ġ�������ׯ��һ����ɢ��������ЧӦҲ��ʧ�ˣ�\n"NOR);
                                break;
                        }
                        if( intp(p = target->query_temp("ljz/fengyun")) ){
                                target->add_temp("apply/dexerity", - p);        
                                target->delete_temp("ljz/fengyun");
                                tell_object(target, HIR"��ġ����ơ�ׯ��һ����ɢ��������ЧӦҲ��ʧ�ˣ�\n"NOR);
                                break;
                        }
                        if( intp(p = target->query_temp("ljz/wuwo")) ){
                                target->add_temp("apply/armor", -p);
                                target->add_temp("apply/defense", -p);
                                target->add_temp("apply/parry", -p);
                                target->delete_temp("ljz/wuwo");
                                tell_object(target, HIR"��ġ����ҡ��ķ���һ����ɢ��������ЧӦҲ��ʧ�ˣ�\n"NOR);
                                break;
                        }
                case "yinyun-ziqi":
                        if( target->query_temp("tj/̫��") ){
                                target->delete_temp("tj/̫��");
                                tell_object(target, HIR"���ڻ�æ֮�У�̫������������У�ЧӦҲ��ʧ�ˣ�\n"NOR);
                                break;
                        }
                case "dulong-dafa":
                        if( intp(p = target->query_temp("sld/wudi2") ) ){
                                target->add_temp("apply/attack", - p/2*3);
                                target->add("max_qi",- target->query_temp("sld/wudiqi"));
                                target->delete_temp("sld");
                                if(target->query("eff_qi") > target->query("max_qi")) 
                                        target->set("eff_qi",target->query("max_qi"));
                                tell_object(target, HIR"����⡸��������һ������һ�ɣ���Ҳ֧�ֲ�ס�ˣ���\n"NOR);
                                if(random( target->query("qi")) < 100) 
                                        target->unconcious();
                                break;
                        }
                        else if( intp(p = target->query_temp("sld/wudi")) ){
                                target->add("max_qi",- target->query_temp("sld/wudiqi"));
                                target->add_temp("apply/attack", -p);
                                target->delete_temp("sld/wudiqi");
                                target->delete_temp("sld/wudi");
                                if(target->query("eff_qi") > target->query("max_qi")) 
                                        target->set("eff_qi",target->query("max_qi"));
                                tell_object(target, HIR"����⡸��������һ������һ�ɣ�����������һ����ͻȻ������������\n"NOR);
                                break;
                        }
                case "hanbing-zhenqi":
                        if( objectp(weapon = target->query_temp("weapon")) 
                        && weapon->query("jianqi") == target){
                                weapon->create();
                                weapon->set("weapon_prop/damage", weapon->query("old_damage"));
                                weapon->delete("jianqi");
                                tell_object(target, HIR"����⡸��������һ������һ�ɣ��⡸��ɽ��������ʹ����ȥ�ˣ�\n"NOR);
                                break;
                        }
                case "huagong-dafa":
                        if( intp(p = target->query_temp("hgdf/judu")) ){
                                target->add_temp("apply/armor", -p);           
                                target->delete_temp("hgdf/judu");
                                tell_object(target, HIR"����⡸��������һ������һ�ɣ����۶���ȫ�����ˣ���\n"NOR);
                                break;
                        }
                        else if( intp(p = target->query_temp("hgdf/huadu")) ){
                                target->add_temp("apply/attack", -p); 
                                target->add_temp("apply/armor_vs_force", -p/2);           
                                target->delete_temp("hgdf/huadu");
                                tell_object(target, HIR"����⡸��������һ������һ�ɣ��������۶���ȫ�����ˣ���\n"NOR);
                                break;
                        }
                case "yunu-xinjing":
                        if( target->query_temp("xinjing") ){
                                p  = target->query_temp("xinjing/eff");
                                target->add_temp( target->query_temp("xinjing/bonus"), -p/5);
                                target->delete_temp("xinjing");
                                tell_object(target, HIR"��ġ��ľ����־�������ɢ��ЧӦҲ��ʧ�ˣ�\n"NOR);
                                break;
                        }
                case "longxiang-boruo":
                        if ( intp(p = target->query_temp("xs/shield")) ) {
                                target->add_temp("apply/dodge", -p);
                                target->add_temp("apply/armor", -p);
                                target->delete_temp("xs/shield");
                                tell_object(target, HIR"�㱻����������һ�����Ϻ��һ�����ǽ�žž���켸����ɢȥ�˻���������\n" NOR);
                                break;
                        }
                case "qiantian-yiyang":
                        if( intp(p = target->query_temp("dali_jing")) ){
                                target->add_temp("apply/intelligence", -p);
                                target->delete_temp("dali_jing");
                                tell_object(target, HIR"�㱻����������һ���޷�����Ǳ���ˡ�\n" NOR);
                                break;
                        }
                case "kurong-changong":
                        if( intp(p = target->query_temp("pf_ku")) ){
                                target->delete_temp("pf_ku");
                                target->add_temp("apply/armor", -p); 
                                tell_object(target, HIR"�㱻����������һ�𣬡��ݡ��ִ�������ɢ�ˣ�\n" NOR);
                                break;
                        }
                        else if( intp(p = target->query_temp("pf_rong")) ){
                                p = target->query_temp("pf_rong");
                                target->delete_temp("pf_ku");
                                target->add_temp("apply/strike", -p/5);
                                target->add_temp("apply/damage",-p/6);
                                tell_object(target, HIR"�㱻����������һ�𣬡��١��ִ�������ɢ�ˣ�\n" NOR);
                                break;
                        }
                case "bihai-chaosheng":
                        if ( intp(p = target->query_temp("thd/maze")) ){
                                target->add_temp("apply/defense", - (p/5));
                                target->delete_temp("thd/maze");
                                if(weapon = target->query_temp("thd/maze_target") && weapon->query_temp("thd/mazed")){
                                        weapon->delete_temp("thd/mazed");
                                        weapon->add_temp("apply/dexerity", p/10);
                                        weapon->add_temp("apply/dodge", p/10);
                                        weapon->add_temp("apply/damage", p/10);
                                        tell_object(weapon, target->name() + "���㲼�������Ѿ���"+me->name()+"�ġ�����������ɢ�ˡ�\n");
                                }
                                tell_object(target, HIR"�㱻����������һ�𣬲�������˲����ɢ�ˣ�\n" NOR);
                                break;
                        }
        }
        
        target->apply_condition("no_exert", me->query_skill("taiji-quan", 1)/15+1);
        if( !me->is_killing(target->query("id"))
        && !target->is_killing(me->query("id"))
        && !me->query("have_master")   // added by snowman
        && target->query("qi")*2 <= target->query("max_qi")) 
                COMBAT_D->end_fight(me, target);
        return 1;
}

int help(object me)
{
	write(WHT"\n̫��������������"NOR"\n");
	write(@HELP
	̫��ȭ��������֮��֣���֮��ϡ��޹��������������졣�����׼������
	���֣�ƫ�����棬˫�����͡�����������һ�Ծ��ƶ����Զ��ƾ�֮���У���
	�����ֽ�ǰ���Ż����ƣ������ܴ��˶��֣�������Ч���Ƴ��Է��ĸ����ڹ���
	
	Ҫ��	���� 1000 ���ϣ�      
		���� 200 ���ϣ�      
		����̫��ȭ�������ޱ�����
HELP
	);
	return 1;
}
