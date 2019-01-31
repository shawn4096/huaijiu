//fogang.c �������
// by snowman@SJ

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int damage, ap, dp, p;
        float at;
        string msg, dodge_skill;
 
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target))
            	return notify_fail("��������ա�ֻ����ս����ʹ�á�\n");

        if(objectp(me->query_temp("weapon")) )
            	return notify_fail("�������ֲ���ʹ�á�������ա���\n");

        if((int)me->query_skill("linji-zhuang", 1) < 180 )
            	return notify_fail("����ټ�ʮ��ׯδ�ɣ�����ʹ�á�������ա���\n");

        if((int)me->query("max_neili") < 2000 )
            	return notify_fail("���������Ϊ���㣬����ʹ�á�������ա���\n"); 

        if((int)me->query("neili") < 1000 )
            	return notify_fail("�������������㣬����ʹ�á�������ա���\n"); 

        if((int)me->query_skill("jieshou-jiushi", 1) < 150 )
            	return notify_fail("��Ľ��־�ʽ������죬����ʹ�á�������ա���\n");

        if((int)me->query_str() < 25)
            	return notify_fail("����������㣬�޷����ӡ�������ա������ơ�\n");

        if((int)me->query_con() < 32)
            	return notify_fail("��ĸ���Ƿ�ѣ��޷�ʹ�á�������ա���\n");
       
        if(me->query_skill_prepared("hand") != "jieshou-jiushi"
         || me->query_skill_mapped("hand") != "jieshou-jiushi"
         || me->query_skill_mapped("parry") != "jieshou-jiushi")
            	return notify_fail("�����ȫ�����ý��־�ʽ������ʹ�á�������ա���\n");

        if(me->query_skill_mapped("force") != "linji-zhuang")
            	return notify_fail("�㲻ʹ���ټ�ʮ��ׯ����ô��ʹ�á�������ա���\n");

        if(me->query_temp("huanying")) 
            	return notify_fail("������ʹ�����λ�Ӱ��������ʹ�á�������ա���\n");

        if(me->query_temp("shuangdao_hebi")) 
            	return notify_fail("������ʹ�á�˫����赡����޷�ʹ�á�������ա���\n");

        msg = MAG "\nֻ��$N����ׯ�ϣ�ͻȻ��ȫ������з����������ĵ���΢����֮���������������δ����һʽ��"HIY"�������"MAG"����\n"+
                  "��һ��������Ʈ����ϣ���������ƽ���һ���ھ����������ˣ������������Ƶ磬��һ���ĳ���\n"+
                  "����$n����ʽƽƽ������һ�ɲ��䣬��ȴ���޿ɵ������޿ɱܣ�\n"NOR;
        ap = (int)me->query_skill("jieshou-jiushi",1) * (int)me->query("neili") * (int)me->query_str();
        dp = (int)target->query_skill("force", 1) * (int)target->query("neili") * (int)target->query_con();
        ap *= (int)me->query("combat_exp")/200;
        dp *= (int)target->query("combat_exp")/200;    
        ap /= 1000;
        dp /= 1000;
                
        me->start_busy(1); 
        me->start_perform(6, "��������ա�");       
        if(random( ap ) > dp/2){
            	target->start_busy(random(2));
            	damage = me->query_skill("hand") + me->query_skill("force");
            	damage += me->query("jiali") * 15;
                
            	if(target->query("neili") < 10) at = 8;
              	else at = me->query("neili") / (target->query("neili")+1);
            	if(at < 1){
               		if(at < 0.5) damage /= 2;
               		damage /= 2;
            	}
            	else if (at < 2 ) at = 2;
            	
            	else damage *= at;
            	damage -= target->query_temp("apply/armor") * 2;
            	if (damage < 0) damage = 0;
            	damage = damage + random(damage / 2);
            	if (target->query_skill_mapped("force") == "jiuyang-shengong"
             	&& target->query_skill("jiuyang-shengong", 1) > 100){
              		tell_object(me, HIY"\n��֪��һ�ƴ���"+target->name()+"���ϣ�ȴ���罭���뺣������ˮ�齻�ڣ�������ʱ��Ӱ���٣�\n"NOR);
              		msg += "��������Ȼһ�����죬$N�Ѵ�����$n�ؿڣ�ֻ��$p��Ȼȫ��������顣��֪һ�ƹ�ȥ��\n"+
                     		"$n��¶��ɫ�����ö˶˵�վ�ţ�$Nȴ���������ң�����΢΢������\n";
              		target->start_busy(2);
              		message_vision(msg, me, target);
              		me->add("neili", -500);
              		me->add("jingli", -100);
              		return 1;
            	}
            	if((target->query_skill_mapped("force") == "yijin-jing"
             	|| target->query_skill_mapped("force") == "yinyun-ziqi")
             	&& target->query_temp("fanzhen")) 
              		damage /= 2;
              	
              	else if( target->query_skill_mapped("force") == "kurong-changong"
             	|| target->query_skill_mapped("force") == "qiantian-yiyang"
             	|| target->query_skill_mapped("force") == "huagong-dafa"
             	|| target->query_skill_mapped("force") == "huntian-qigong"
             	|| target->query_skill_mapped("force") == "yunu-xinjing" )
             		damage *= 2;
             		
              	if (damage > 5000) damage = 5000 + (damage-5000)/100;
              	target->receive_damage("qi", damage, me);
              	target->receive_wound("qi", random(damage), me);
              	target->receive_damage("neili", damage/4);
              	me->receive_damage("neili", damage/5);
              	if(damage >= 4000)
                     	msg += "��һ������ʹ����ȫ����˿��������أ�$n����������������������֮�䣡\n";
              	p = (int)target->query("qi")*100/(int)target->query("max_qi");
              	msg += damage_msg(damage, "����");
              	msg += "( $n"+eff_status_msg(p)+" )\n";
	}
        else {
            	dodge_skill = target->query_skill_mapped("dodge");
            	if( !dodge_skill ) dodge_skill = "dodge";
            	msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        me->add("neili", -400);
        me->add("jingli", -100);
        message_vision(msg, me, target);
        return 1; 
}
